#include <Servo.h>
#include <string.h>
Servo bazainf;
Servo bazasup;
Servo wrist;
Servo cot;
float infpos = 0,suppos=0,wristpos=0,cotpos=0;
float antinf=0,antsup=-20,antwrist=35,antcot=55;
float unghi[4]={0};
int cnt=0;
void setup() {
  Serial.begin(9600);
  bazainf.attach(2);
    bazasup.attach(3);
      wrist.attach(5);
        cot.attach(4);
  
}
void parcare()
{
     movewrist(35);
     movecot(55);
       movebazasup(-20);
} 
void citireserial()
{
  int poz = 0;
  if(1)
  {
    String str="3.8886535 | 17.365522 | -17.365522 | 0.0 ";
    Serial.print("lol");
    for(int i=0;str[i]!='\n';i++){
      float a=0,b=0;
      int power=1;
      if((str[i]>='0' && str[i]<='9')|| str[i]=='.'){
        while(str[i]>='0' && str[i]<='9'){
          a = a*10 + str[i]-'0';
        }
        if(str[i]=='.'){
        i++;
          while(str[i]>='0' && str[i]<='9'){
            b = b*10 + str[i]-'0';
            power*=10;
          }
          b/=power;
          a+=b;
          unghi[poz++] = -a;
          Serial.print(a);
          Serial.print("  "); 
        }
      }
      if(str[i]=='\n')
        break;
    }
 
  }
}

void movebazasup(float gradfinal)
{
         bazasup.write(antsup);
  if(antsup<gradfinal)
  antsup+=1;
  if(antsup>gradfinal)
  antsup-=1;
}
void movebazainf(float gradfinal)
{
  
  if(antinf<gradfinal)
  antinf+=1;
  if(antinf>gradfinal)
  antinf-=1;
}
void movecot(float gradfinal)
{
  cot.write(antcot);
  //Serial.print(antcot);
  //Serial.print("  ");
  if(antcot<gradfinal)
  antcot+=1;
  if(antcot>gradfinal)
  antcot-=1;
}
void movewrist(float gradfinal)
{
       wrist.write(antwrist);
  if(antwrist<gradfinal)
  antwrist+=1;
  if(antwrist>gradfinal)
  antwrist-=1;
}
  void miscari()
{
  movebazainf(antwrist+unghi[3]);
  movebazasup(antsup+unghi[0]);
  movecot(antcot+unghi[1]);
  movewrist(antwrist+unghi[2]);
  
} 
void loop() {
       cnt++;
       if(cnt<2){
       parcare();
       }
       citireserial();
       miscari();
       Serial.print("pppp");
       delay(100);
}
