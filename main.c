#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>

#include "GL/freeglut.h"

#define PI 3.14159265

void DoDisplay();
void getRot();
double dist(double a,double b);
double  degrees(double radian);

double  ROT_X=0.0;
double ROT_Y=0.0;

int MPU_9250;

int ACCEL_X;
int ACCEL_Y;
int ACCEL_Z;

int ACCEL_X_SCALED;
int ACCEL_Y_SCALED;
int ACCEL_Z_SCALED;

int GYRO_X;
int GYRO_Y;
int GYRO_Z;
 
int GEOMAG_X;
int GEOMAG_Y;
int GEOMAG_Z;


int main(int argc, char** argv) {

	MPU_9250=wiringPiI2CSetup(0x68);	//sensor address
	wiringPiI2CWriteReg8(MPU_9250,0x6b,0); //power management 1
	
	glutInit(&argc,argv);
	glutCreateWindow("Remote Control");
	glutDisplayFunc(DoDisplay);
	glutIdleFunc(DoDisplay);
	glutMainLoop();
	
}

void getRot(){
	ACCEL_X=wiringPiI2CReadReg8(MPU_9250,0x3b);
	ACCEL_X=ACCEL_X<<8|wiringPiI2CReadReg8(MPU_9250,0x3c);
	ACCEL_X_SCALED=ACCEL_X/16384.0;
	
	ACCEL_Y=wiringPiI2CReadReg8(MPU_9250,0x3d);
	ACCEL_Y=ACCEL_X<<8|wiringPiI2CReadReg8(MPU_9250,0x3e);
	ACCEL_Y_SCALED=ACCEL_Y/16384.0;
	
	ACCEL_Z=wiringPiI2CReadReg8(MPU_9250,0x3f);
	ACCEL_Z=ACCEL_X<<8|wiringPiI2CReadReg8(MPU_9250,0x40);
	ACCEL_Z_SCALED=ACCEL_Z/16384.0;
	
	/*
	GYRO_X=wiringPiI2CReadReg8(MPU_9250,0x43);
	GYRO_X=GYRO_X<<8|wiringPiI2CReadReg8(MPU_9250,0x44);
	
	GYRO_Y=wiringPiI2CReadReg8(MPU_9250,0x45);
	GYRO_Y=GYRO_X<<8|wiringPiI2CReadReg8(MPU_9250,0x46);
	
	GYRO_Z=wiringPiI2CReadReg8(MPU_9250,0x47);
	tGYRO_Z=GYRO_X<<8|wiringPiI2CReadReg8(MPU_9250,0x48);
	*/
	
	ROT_X=degrees(atan2(ACCEL_Y_SCALED,dist(ACCEL_X_SCALED,ACCEL_Z_SCALED)));
	ROT_Y=-degrees(atan2(ACCEL_X_SCALED,dist(ACCEL_Y_SCALED,ACCEL_Z_SCALED)));
	printf("%f\n",ROT_X);
}

double dist(double a,double b){
	return sqrt((a*a)+(b*b));
}
void DoDisplay(){
	getRot();	//ROT_X, ROT_Y
	
	glRotatef(1,1.0,0.0,0.0);
//	glRotatef(ROT_Y,0.0,1.0,0.0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);

		glColor3f(1.0,1.0,1.0);
		glVertex3f(-0.2,0.4,0.1);	//left
		glVertex3f(-0.2,-0.4,0.1);
		glVertex3f(-0.2,-0.4,-0.1);
		glVertex3f(-0.2,0.4,-0.1);

		glVertex3f(0.2,-0.4,0.1);	//right
		glVertex3f(0.2,0.4,0.1);
		glVertex3f(0.2,0.4,-0.1);
		glVertex3f(0.2,-0.4,-0.1);

		glVertex3f(-0.2,-0.4,0.1);	//rear
		glVertex3f(0.2,-0.4,0.1);
		glVertex3f(0.2,-0.4,-0.1);
		glVertex3f(-0.2,-0.4,-0.1);

		glVertex3f(-0.2,0.4,-0.1);	//bottom
		glVertex3f(0.2,0.4,-0.1);
		glVertex3f(0.2,-0.4,-0.1);
		glVertex3f(-0.2,-0.4,-0.1);

		glColor3f(1.0,0.0, 0.0);	//red_front
		glVertex3f(-0.2,0.4,0.1);
		glVertex3f(0.2,0.4,0.1);
		glVertex3f(0.2,0.4,-0.1);
		glVertex3f(-0.2,0.4,-0.1);

		glColor3f(0.0,1.0,0.0);		//green_top
		glVertex3f(-0.2,0.4,0.1);
		glVertex3f(0.2,0.4,0.1);
		glVertex3f(0.2,-0.4,0.1);
		glVertex3f(-0.2,-0.4,0.1);
		

	glEnd();
	glFlush();
	
//	glRotatef(ROT_X,1.0,0.0,0.0);
//	glRotatef(ROT_Y,0.0,1.0,0.0);
//	glFlush();
	
	for(int i=0;i<10000000;i++){	}	
}

double degrees(double radian){
	return radian*180.0/PI;
}


