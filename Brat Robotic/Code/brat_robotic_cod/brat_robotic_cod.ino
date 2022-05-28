

/************************************************************************************************************************
 * Autori: Cod MTHH scris de catre Matei Sebastian(elev Alexandru Ioan Cuza) cu ajutorul lui Matei Barbu(elev Tudor Vianu).
 * Descriere: Proiectul este destinat concursului InfoEducatie editia 2022,etapa judeteana,sectiunea roboti;
 * Date: 7/mai/2022
 * @matei.sebastian9   @mate.brb
 * Cost aproximativ proiect:400 RON
 *************************************************************************************************************************/

 
#include <MPU6050_tockn.h>
#include <HCPCA9685.h>
#include <Wire.h>
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);
MPU6050 mpu6050(Wire);
const int servoclawpos=6,servobaseinfpos=1,servobasesuppos=2,servocot1=3,servoinchieietura=4,servoclawtilt=5;
const int buzzer=9,dirPin = 4,stepPin = 5,stepsPerRevolution = 120,stepsPerRevolutionSmall = 60;
int stepDelay = 4500,stepDelaySmall = 9500,ok=0,inversez=0;
unsigned int Pos;
int pos=300,onoff,response_time = 5,response_time_4 = 2,loop_check = 0,response_time_fast = 20,action_delay = 600,potentiometru=0,potentiometru1=0;
const int spozbaseinf=200,spozbasesup=400,spozcot=420,spozwristz=120,spozwristspin=255;

void moveBaseSup(float degree)
{
 degree=degree*4;
 HCPCA9685.Servo(servobaseinfpos,degree);
}
void moveClaw(float degree)
{
    degree=degree*4;
 if(degree>25)HCPCA9685.Servo(servoclawpos,degree);
  
}
void movefrontback(int degreef)
{
  int degreef2;
  degreef2=degreef*4;
  inversez=degreef;
  HCPCA9685.Servo(servocot1,spozcot-(degreef2/2));
  HCPCA9685.Servo(servobasesuppos,spozbasesup-degreef2);
  
}
float potpercentage(int val)
{
  float percent=0;
  percent=val/1023.0;
  percent*=100;
  return percent;
}
void soundeffect(int buzztimes,int buzztone)
{
  for(int i=1;i<=buzztimes;i++)
  {
   tone(buzzer, buzztone);
  delay(200);
  noTone(buzzer);
  delay(50);
  }
}
void wakeupservos()
{
  if(ok==0)
  {
    soundeffect(2,1000);
    HCPCA9685.Servo(servobaseinfpos,spozbaseinf);
    delay(300);
    HCPCA9685.Servo(servobasesuppos,spozbasesup);
    delay(300);
    HCPCA9685.Servo(servocot1,spozcot);
    delay(300);
     HCPCA9685.Servo(servoinchieietura,spozwristz);
       delay(300);
     HCPCA9685.Servo(servoclawtilt,0);
       delay(1000);
     HCPCA9685.Servo(servoclawtilt,400);
     delay(1000);
     HCPCA9685.Servo(servoclawtilt,spozwristspin);
     delay(1000);
    ok=1;
  }
}
void movewristz(float degree4)
{
  degree4*=-3;
  degree4+=spozwristz;
  inversez*=2;
  degree4+=inversez;
  if(degree4>95 && degree4<350)
  HCPCA9685.Servo(servoinchieietura,degree4);
}

void parkare()
{
    HCPCA9685.Servo(servobaseinfpos,spozbaseinf);
    delay(300);
    HCPCA9685.Servo(servobasesuppos,spozbasesup);
    delay(300);
    HCPCA9685.Servo(servocot1,spozcot);
    delay(300);
     HCPCA9685.Servo(servoinchieietura,spozwristz);
       delay(300);
}

void movewristspin(float degree5)
{
  degree5*=4;
  degree5+=spozwristspin;
  HCPCA9685.Servo(servoclawtilt,degree5);
  Serial.print(degree5);
  Serial.print("      ");
}
void moveBase(float degree)
{
  degree*=2;
  degree+=spozbaseinf;
  HCPCA9685.Servo(servobaseinfpos,degree);
}
void readval()
{
  onoff=digitalRead(5);
  potentiometru=analogRead(A0);
  potentiometru1=analogRead(A1);
  mpu6050.update();
}
void miscari()
{
 moveClaw(potpercentage(potentiometru));
 moveBase(mpu6050.getAngleZ());
 movefrontback(potpercentage(potentiometru1));
 movewristspin(mpu6050.getAngleX());
 movewristz(mpu6050.getAngleY());
}
void setup()
{ 
  pinMode(buzzer, OUTPUT);
  soundeffect(1,5000);
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  mpu6050.calcGyroOffsets(true);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  delay(3000);
}
void loop() {
 readval();
 mpu6050.update();
 //Serial.print(onoff);
  if(onoff==1)
  {
wakeupservos();
miscari();
delay(35);
  }
  
  else if (onoff==0)
  {
    ok=0;
     parkare();
  }
}
