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

void qTh::run(){



}
