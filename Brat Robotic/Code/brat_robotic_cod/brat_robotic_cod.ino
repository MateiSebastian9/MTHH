#include <MPU6050_tockn.h>
#include <HCPCA9685.h>
#include <Wire.h>
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);
MPU6050 mpu6050(Wire);
const int servoclawpos=6,servobaseinfpos=1,servobasesuppos=2,servocot1=3,servoinchieietura=4,servoclawtilt=5;
const int dirPin = 4,stepPin = 5,stepsPerRevolution = 120,stepsPerRevolutionSmall = 60;
int stepDelay = 4500,stepDelaySmall = 9500;
unsigned int Pos;
int pos=300,response_time = 5,response_time_4 = 2,loop_check = 0,response_time_fast = 20,action_delay = 600,potentiometru=0;

void setup()
{ 
  Serial.begin(9600);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  mpu6050.calcGyroOffsets(true);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  delay(3000);
}
void moveClaw(float degree)
{
    degree=degree*4;
  Serial.print(degree);
  Serial.print('\n');
  HCPCA9685.Servo(1,degree);
 
}

float potpercentage(int val)
{
  float percent=0;
  percent=val/1023.0;
  percent*=100;
  return percent;
}
void moveBase(float degree)
{
  if(degree<100 && degree>4)
  HCPCA9685.Servo(2,400);
}
void readval()
{
  potentiometru=analogRead(A0);
  mpu6050.update();
}
void miscari()
{
 moveClaw(potpercentage(potentiometru));
 //moveBase(mpu6050.getAngleZ());
}
void loop() {
readval();
miscari();
delay(100);
}
