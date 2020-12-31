#include"qTh.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>

#define pi 3.141592
#define MPU6050_ADDR 0x68
#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define ACCEL_CONFIG  0x1C
#define INT_ENABLE    0x38
#define ACCEL_XOUT_H  0x3B
#define ACCEL_YOUT_H  0x3D
#define ACCEL_ZOUT_H  0x3F
#define TEMP_OUT_H    0x41
#define GYRO_XOUT_H   0x43
#define GYRO_YOUT_H   0x45
#define GYRO_ZOUT_H   0x47
//#AK8963 registers
#define AK8963_ADDR     0x0C
#define AK8963_ST1     0x02
#define HXH           0x04
#define HYH           0x06
#define HZH           0x08
#define AK8963_ST2    0x09
#define AK8963_CNTL   0x0A
#define mag_sens 4900.0 // magnetometer sensitivity: 4800 uT
#define sample_num_mdate  500


int fd_mpu6050_addr;
int fd_ak8963_addr;

float *Mxyz;
float *Axyz;
float *Gxyz;
float accXangle = 0.0;
float accYangle = 0.0;
float gyroXangle = 0.0;
float gyroYangle = 0.0;
float roll = 0.0;
float pitch = 0.0;
float yaw = 0.0;
long st;
float heading;
double dt = 0.0;

float past_yaw=0.0;
float past_roll=0.0;
float past_pitch=0.0;
float past_heading = 0.0;

double temp = 0.0;
float a = 0.2;


using namespace std;

qTh::qTh(QObject *parent):QThread(parent){

}
qTh::~qTh(){

}

int read_raw_bits(int fd, int addr)
{
  int val;
  val = wiringPiI2CReadReg8(fd, addr);
  val = val << 8;
  val += wiringPiI2CReadReg8(fd, addr+1);
  if (val >= 0x8000)
  val = -(65536 - val);

  return val;
}

float dist(float a, float b)
{
  return sqrt((a*a) + (b*b));
}

void MPU6050_start(){

    //# alter sample rate (stability)
    int samp_rate_div = 0; //# sample rate = 8 kHz/(1+samp_rate_div)
    wiringPiI2CWriteReg8(fd_mpu6050_addr, SMPLRT_DIV, 0);
    delay(100);

    //# reset all sensors
    wiringPiI2CWriteReg8(fd_mpu6050_addr,PWR_MGMT_1,0x01);
    delay(100);

    //# power management and crystal settings


    //#Write to Configuration register
    wiringPiI2CWriteReg8(fd_mpu6050_addr, CONFIG, 0);
    delay(100);


    wiringPiI2CWriteReg8(fd_mpu6050_addr, GYRO_CONFIG, 0);
    delay(100);


    wiringPiI2CWriteReg8(fd_mpu6050_addr, INT_ENABLE, 0x01);
    delay(100);



}

void AK8963_start(){
    wiringPiI2CWriteReg8(fd_ak8963_addr,AK8963_CNTL,0x00);
    delay(100);
    int AK8963_bit_res = 0b0001;// 0b0001 = 16-bit
    int AK8963_samp_rate = 0b0110;// 0b0010 = 8 Hz, 0b0110 = 100 Hz
    int AK8963_mode = (AK8963_bit_res <<4)+AK8963_samp_rate; // bit conversion
    wiringPiI2CWriteReg8(fd_ak8963_addr,AK8963_CNTL,AK8963_mode);
    delay(100);
}

int AK8963_reader(int reg){
    // read magnetometer values
    int low = wiringPiI2CReadReg8(fd_ak8963_addr, reg-1);
    int high = wiringPiI2CReadReg8(fd_ak8963_addr, reg);
    // combine higha and low for unsigned bit value
    int value = ((high << 8) | low);
    // convert to +- value

    return value;
}

float* AK8963_conv(){
    //# raw magnetometer bits
    float mag_x;
    float mag_y;
    float mag_z;

    int loop_count = 0;
    while (1){
      mag_x = AK8963_reader(HXH);
      mag_y = AK8963_reader(HYH);
      mag_z = AK8963_reader(HZH);

      //# the next line is needed for AK8963
      if (wiringPiI2CReadReg8(fd_ak8963_addr,AK8963_ST2)==0b10000){
          break;
      }
      loop_count+=1;
    }

    //convert to acceleration in g and gyro dps
    float *m = (float*)malloc(sizeof(float)*3);


    m[0] = (float) mag_x * 1200 / 4096;
    m[1] = (float) mag_y * 1200 / 4096;
    m[2] = (float) mag_z * 1200 / 4096;

    return m;
}

float *getAccel_Data(){
  int acclX, acclY, acclZ;
  float acclX_scaled, acclY_scaled, acclZ_scaled;
  acclX = read_raw_bits(fd_mpu6050_addr,0x3B);
  acclY = read_raw_bits(fd_mpu6050_addr,0x3D);
  acclZ = read_raw_bits(fd_mpu6050_addr,0x3F);

  acclX_scaled = acclX / 16384.0;
  acclY_scaled = acclY / 16384.0;
  acclZ_scaled = acclZ / 16384.0;

  float *a = (float*)malloc(sizeof(float)*3);
  a[0] = acclX_scaled;
  a[1] = acclY_scaled;
  a[2] = acclZ_scaled;

  return a;

}

float *getGyro_Data_cal(){
  int gyroX, gyroY, gyroZ;
  float gyroX_scaled, gyroY_scaled, gyroZ_scaled;

  gyroX = read_raw_bits(fd_mpu6050_addr,GYRO_XOUT_H);//- error_gyroX;
  gyroY = read_raw_bits(fd_mpu6050_addr,GYRO_YOUT_H);//- error_gyroY;
  gyroZ = read_raw_bits(fd_mpu6050_addr,GYRO_ZOUT_H);//- error_gyroZ;

  gyroX_scaled = gyroX / 131;
  gyroY_scaled = gyroY / 131;
  gyroZ_scaled = gyroZ / 131;

  float *g = (float*)malloc(sizeof(float)*3);
  g[0] = gyroX_scaled;
  g[1] = gyroY_scaled;
  g[2] = gyroZ_scaled;

  return g;

}

float *getGyro_Data(){
  int gyroX, gyroY, gyroZ;
  float gyroX_scaled, gyroY_scaled, gyroZ_scaled;

  gyroX = read_raw_bits(fd_mpu6050_addr,GYRO_XOUT_H);
  gyroY = read_raw_bits(fd_mpu6050_addr,GYRO_YOUT_H);
  gyroZ = read_raw_bits(fd_mpu6050_addr,GYRO_ZOUT_H);

  gyroX_scaled = gyroX / 131;
  gyroY_scaled = gyroY / 131;
  gyroZ_scaled = gyroZ / 131;

  float *g = (float*)malloc(sizeof(float)*3);
  g[0] = gyroX_scaled;
  g[1] = gyroY_scaled;
  g[2] = gyroZ_scaled;

  return g;

}



void get_calibration_Data ()
{
  int mx_max = 0;
  int my_max = 0;
  int mz_max = 0;

  int mx_min = 0;
  int my_min = 0;
  int mz_min = 0;

  float mx_sample[3] = {0.0,0.0,0.0};
  float my_sample[3] = {0.0,0.0,0.0};
  float mz_sample[3] = {0.0,0.0,0.0};

    printf("start calibrate\n");
    for (int i = 0; i < sample_num_mdate; i++)
    {
        float* Mxyz_this = AK8963_conv();
        mx_sample[2] = Mxyz_this[0];
        my_sample[2] = Mxyz_this[1];
        mz_sample[2] = Mxyz_this[2];
        delay(100);

        if(mx_sample[2] > 1200) mx_sample[2] = 0;
        if(my_sample[2] > 1200) my_sample[2] = 0;
        if(mz_sample[2] > 1200) mz_sample[2] = 0;

        if(mx_sample[2] < -1200) mx_sample[2] = 0;
        if(my_sample[2] < -1200) my_sample[2] = 0;
        if(mz_sample[2] < -1200) mz_sample[2] = 0;

        if (mx_sample[2] >= mx_sample[1])mx_sample[1] = mx_sample[2];
        if (my_sample[2] >= my_sample[1])my_sample[1] = my_sample[2]; //find max value
        if (mz_sample[2] >= mz_sample[1])mz_sample[1] = mz_sample[2];

        if (mx_sample[2] <= mx_sample[0])mx_sample[0] = mx_sample[2];
        if (my_sample[2] <= my_sample[0])my_sample[0] = my_sample[2]; //find min value
        if (mz_sample[2] <= mz_sample[0])mz_sample[0] = mz_sample[2];
    }
    mx_max = mx_sample[1];
    my_max = my_sample[1];
    mz_max = mz_sample[1];

    mx_min = mx_sample[0];
    my_min = my_sample[0];
    mz_min = mz_sample[0];

    //mx_centre = (mx_max + mx_min) / 2;
    //my_centre = (my_max + my_min) / 2;
    //mz_centre = (mz_max + mz_min) / 2;


}



float* getCompassDate_calibrated ()
{
    float* Mxyz = AK8963_conv();
    Mxyz[0] = Mxyz[0];// - mx_centre;
    Mxyz[1] = Mxyz[1];// - my_centre;
    Mxyz[2] = Mxyz[2];// - mz_centre;
    return Mxyz;
}

float getHeading(float m[3])
{
  float heading = 180 * atan2(m[1],m[0]) /pi;
  if (heading < 0) heading += 360;
  if (heading > 360) heading -= 360;
}
void qTh::run(){

    fd_mpu6050_addr = wiringPiI2CSetup (0x68);
    fd_ak8963_addr = wiringPiI2CSetup (0x0C);


      AK8963_start();
      MPU6050_start();

/*

      for(int i = 0; i < 100; i++){
        error_gyroX += read_raw_bits(fd_mpu6050_addr,GYRO_XOUT_H);
        error_gyroY += read_raw_bits(fd_mpu6050_addr,GYRO_YOUT_H);
        error_gyroZ += read_raw_bits(fd_mpu6050_addr,GYRO_ZOUT_H);

        error_acclX = read_raw_bits(fd_mpu6050_addr,0x3B);
        error_acclY = read_raw_bits(fd_mpu6050_addr,0x3D);
        error_acclZ = read_raw_bits(fd_mpu6050_addr,0x3F);

        delay(50);
      }
      error_gyroX /= 100;
      error_gyroY /= 100;
      error_gyroZ /= 100;

      error_acclX /= 100;
      error_acclY /= 100;
      error_acclZ /= 100;
#include <math.h>
*/


      //printf("end_1\n start_2\n");
      //get_calibration_Data ();
      //printf("end");
      cout <<"hel"<< endl;
      delay(1000);
      cout <<"hel89"<< endl;
      //printf("%f %f %f\n", mx_centre, my_centre, mz_centre);
      st= millis();
    float a=0.0;//angle


    for(;;){
        //receive a from sensor
        //Mxyz = getCompassDate_calibrated();
        //Axyz = getAccel_Data();
        Gxyz = getGyro_Data_cal();

        //Mxyz = getCompassDate_calibrated();
        //heading = getHeading(Mxyz);
          //printf("%f \n", heading);

        //accYangle = atan2(-Axyz[0], dist(Axyz[1], Axyz[2]))*(180.0 / pi);
        //accXangle = atan2(Axyz[1], dist(Axyz[0], Axyz[2]))*(180.0 / pi);

          //printf("mills: %ld  ", millis()-start);
        dt = (millis()-st)/1000.0;
        st = millis();


        //  gyroXangle = gyroXangle + Gxyz[0]*dt;
        //  gyroYangle = gyroYangle + Gxyz[1]*dt;

        //  pitch = (gyroXangle*0.96 + accXangle*0.04);
        //  roll = (gyroYangle*0.96 + accYangle*0.04);
        yaw = (yaw + Gxyz[2]*dt);


        a=(yaw)*pi/180.0;


        emit setAngle(-a);
        past_heading = heading;
        past_yaw=yaw;
        past_roll=roll;
        past_pitch=pitch;
        sleep(0.3);



    }

}
