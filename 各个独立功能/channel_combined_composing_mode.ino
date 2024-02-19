#include <LiquidCrystal.h>
//删减了愚蠢的SW八度模式，极大的简化了代码

const int CtrlX=A12,CtrlY=A13;
const int  KEY1=A0,KEY2=A1,KEY3=A2,KEY4=A3,KEY5=A4,KEY6=A5,KEY7=A6,KEY8=A7,KEY9=A8,KEY10=A9,KEY11=A10,KEY12=A11;
const int SW1=22,SW2=24,SW3=26,SW4=28,SW5=30,SW6=32,SW7=34,SW8=36,SW9=38,SW10=40,SW11=42,SW12=44;
const int rs=13,en=12,d4=11,d5=8,d6=7,d7=4;
int previous1=0,previous2=0,previous3=0,previous4=0,previous5=0,previous6=0;
int previous7=0,previous8=0,previous9=0,previous10=0,previous11=0,previous12=0;
int nprevious1=0,nprevious2=0,nprevious3=0,nprevious4=0,nprevious5=0,nprevious6=0;
int nprevious7=0,nprevious8=0,nprevious9=0,nprevious10=0,nprevious11=0,nprevious12=0;
int key1=0,key2=0,key3=0,key4=0,key5=0,key6=0,key7=0,key8=0,key9=0,key10=0,key11=0,key12=0;
int sw1,sw2,sw3,sw4,sw5,sw6,sw7,sw8,sw9,sw10,sw11,sw12;
int x=512,y=512;
int scale=0;
LiquidCrystal LCD(rs,en,d4,d5,d6,d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Scale Range:");
  LCD.setCursor(0,1);
  LCD.print(0);

  pinMode(SW1,INPUT_PULLUP);pinMode(SW2,INPUT_PULLUP);pinMode(SW3,INPUT_PULLUP);pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);pinMode(SW6,INPUT_PULLUP);pinMode(SW7,INPUT_PULLUP);pinMode(SW8,INPUT_PULLUP);
  pinMode(SW9,INPUT_PULLUP);pinMode(SW10,INPUT_PULLUP);pinMode(SW11,INPUT_PULLUP);pinMode(SW12,INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  x=analogRead(CtrlX),y=analogRead(CtrlY);
  //说明：琴键有两个八度，当杆子上推弹较高的音，杆子下拉弹较低的音，按下弹两个同名音（八度）
  key1=analogRead(KEY1);key2=analogRead(KEY2);
  key3=analogRead(KEY3);key4=analogRead(KEY4);
  key5=analogRead(KEY5);key6=analogRead(KEY6);
  key7=analogRead(KEY7);key8=analogRead(KEY8);
  key9=analogRead(KEY9);key10=analogRead(KEY10);
  key11=analogRead(KEY11);key12=analogRead(KEY12);
  //SW实现八度音，不知道会不会变卡
  sw1=digitalRead(SW1);sw2=digitalRead(SW2);sw3=digitalRead(SW3);
  sw4=digitalRead(SW4);sw5=digitalRead(SW5);sw6=digitalRead(SW6);
  sw7=digitalRead(SW7);sw8=digitalRead(SW8);sw9=digitalRead(SW9);
  sw10=digitalRead(SW10);sw11=digitalRead(SW11);sw12=digitalRead(SW12);
  
  


  
  //Note-On
  if(key1>800){Noteon(&previous1,60,scale);}if(key2>800){Noteon(&previous2,61,scale);}
  if(key3>800){Noteon(&previous3,62,scale);}if(key4>800){Noteon(&previous4,63,scale);}
  if(key5>800){Noteon(&previous5,64,scale);}if(key6>800){Noteon(&previous6,65,scale);}
  if(key7>800){Noteon(&previous7,66,scale);}if(key8>800){Noteon(&previous8,67,scale);}
  if(key9>800){Noteon(&previous9,68,scale);}if(key10>800){Noteon(&previous10,69,scale);}
  if(key11>800){Noteon(&previous11,70,scale);}if(key12>800){Noteon(&previous12,71,scale);}
  
  if(key1<200){nNoteon(&nprevious1,72,scale);}if(key2<200){nNoteon(&nprevious2,73,scale);}
  if(key3<200){nNoteon(&nprevious3,74,scale);}if(key4<200){nNoteon(&nprevious4,75,scale);}
  if(key5<200){nNoteon(&nprevious5,76,scale);}if(key6<200){nNoteon(&nprevious6,77,scale);}
  if(key7<200){nNoteon(&nprevious7,78,scale);}if(key8<200){nNoteon(&nprevious8,79,scale);}
  if(key9<200){nNoteon(&nprevious9,80,scale);}if(key10<200){nNoteon(&nprevious10,81,scale);}
  if(key11<200){nNoteon(&nprevious11,82,scale);}if(key12<200){nNoteon(&nprevious12,83,scale);}

  if(sw1==0&&key1<800&&key1>200){Noteon(&previous1,60,scale);nNoteon(&nprevious1,72,scale);} 
  if(sw2==0&&key2<800&&key2>200){Noteon(&previous2,61,scale);nNoteon(&nprevious2,73,scale);}
  if(sw3==0&&key3<800&&key3>200){Noteon(&previous3,62,scale);nNoteon(&nprevious3,74,scale);}
  if(sw4==0&&key4<800&&key4>200){Noteon(&previous4,63,scale);nNoteon(&nprevious4,75,scale);}
  if(sw5==0&&key5<800&&key5>200){Noteon(&previous5,64,scale);nNoteon(&nprevious5,76,scale);}
  if(sw6==0&&key6<800&&key6>200){Noteon(&previous6,65,scale);nNoteon(&nprevious6,77,scale);}
  if(sw7==0&&key7<800&&key7>200){Noteon(&previous7,66,scale);nNoteon(&nprevious7,78,scale);}
  if(sw8==0&&key8<800&&key8>200){Noteon(&previous8,67,scale);nNoteon(&nprevious8,79,scale);}
  if(sw9==0&&key9<800&&key9>200){Noteon(&previous9,68,scale);nNoteon(&nprevious9,80,scale);}
  if(sw10==0&&key10<800&&key10>200){Noteon(&previous10,69,scale);nNoteon(&nprevious10,81,scale);}
  if(sw11==0&&key11<800&&key11>200){Noteon(&previous11,70,scale);nNoteon(&nprevious11,82,scale);}
  if(sw12==0&&key12<800&&key12>200){Noteon(&previous12,71,scale);nNoteon(&nprevious12,83,scale);}
  
  
  //Note-Off
  if(key1<800&&sw1==1){Noteoff(&previous1,60,scale);}if(key2<800&&sw2==1){Noteoff(&previous2,61,scale);}
  if(key3<800&&sw3==1){Noteoff(&previous3,62,scale);}if(key4<800&&sw4==1){Noteoff(&previous4,63,scale);}
  if(key5<800&&sw5==1){Noteoff(&previous5,64,scale);}if(key6<800&&sw6==1){Noteoff(&previous6,65,scale);}
  if(key7<800&&sw7==1){Noteoff(&previous7,66,scale);}if(key8<800&&sw8==1){Noteoff(&previous8,67,scale);}
  if(key9<800&&sw9==1){Noteoff(&previous9,68,scale);}if(key10<800&&sw10==1){Noteoff(&previous10,69,scale);}
  if(key11<800&&sw11==1){Noteoff(&previous11,70,scale);}if(key12<800&&sw12==1){Noteoff(&previous12,71,scale);}
  
  if(key1>200&&sw1==1){nNoteoff(&nprevious1,72,scale);}if(key2>200&&sw2==1){nNoteoff(&nprevious2,73,scale);}
  if(key3>200&&sw3==1){nNoteoff(&nprevious3,74,scale);}if(key4>200&&sw4==1){nNoteoff(&nprevious4,75,scale);}
  if(key5>200&&sw5==1){nNoteoff(&nprevious5,76,scale);}if(key6>200&&sw6==1){nNoteoff(&nprevious6,77,scale);}
  if(key7>200&&sw7==1){nNoteoff(&nprevious7,78,scale);}if(key8>200&&sw8==1){nNoteoff(&nprevious8,79,scale);}
  if(key9>200&&sw9==1){nNoteoff(&nprevious9,80,scale);}if(key10>200&&sw10==1){nNoteoff(&nprevious10,81,scale);}
  if(key11>200&&sw11==1){nNoteoff(&nprevious11,82,scale);}if(key12>200&&sw12==1){nNoteoff(&nprevious12,83,scale);}

  if(sw1==1&&key1<800&&key1>200){Noteoff(&previous1,60,scale);nNoteoff(&nprevious1,72,scale);}
  if(sw2==1&&key2<800&&key2>200){Noteoff(&previous2,61,scale);nNoteoff(&nprevious2,73,scale);}
  if(sw3==1&&key3<800&&key3>200){Noteoff(&previous3,62,scale);nNoteoff(&nprevious3,74,scale);}
  if(sw4==1&&key4<800&&key4>200){Noteoff(&previous4,63,scale);nNoteoff(&nprevious4,75,scale);}
  if(sw5==1&&key5<800&&key5>200){Noteoff(&previous5,64,scale);nNoteoff(&nprevious5,76,scale);}
  if(sw6==1&&key6<800&&key6>200){Noteoff(&previous6,65,scale);nNoteoff(&nprevious6,77,scale);}
  if(sw7==1&&key7<800&&key7>200){Noteoff(&previous7,66,scale);nNoteoff(&nprevious7,78,scale);}
  if(sw8==1&&key8<800&&key8>200){Noteoff(&previous8,67,scale);nNoteoff(&nprevious8,79,scale);}
  if(sw9==1&&key9<800&&key9>200){Noteoff(&previous9,68,scale);nNoteoff(&nprevious9,80,scale);}
  if(sw10==1&&key10<800&&key10>200){Noteoff(&previous10,69,scale);nNoteoff(&nprevious10,81,scale);}
  if(sw11==1&&key11<800&&key11>200){Noteoff(&previous11,70,scale);nNoteoff(&nprevious11,82,scale);}
  if(sw12==1&&key12<800&&key12>200){Noteoff(&previous12,71,scale);nNoteoff(&nprevious12,83,scale);}

  //To set the scale//可能可以做一个所有音符停止的操作
  if(y>=800){
    LCD.clear();delay(500);
    scale=scale+12;if(scale>48){scale=48;}
    LCD.setCursor(0,0);
    LCD.print("Scale Range:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }
  if(y<=200){
    LCD.clear();delay(500);
    scale=scale-12;if(scale<-48){scale=-48;}
    LCD.setCursor(0,0);
    LCD.print("Scale Range:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }
}


//Note Functions(Tune range:60~82)
//第一个八度
void Noteon(int *previous,int tune,int scale){
  if(*previous==1){}
  if(*previous==0)
  {
    Serial.write(B10010000);
    Serial.write(tune+scale);
    Serial.write(100);
    *previous=1;
  }
}
void Noteoff(int *previous,int tune,int scale){
  if(*previous==0){}
  if(*previous==1)
  {
    Serial.write(B10000000);
    Serial.write(tune+scale);
    Serial.write(0);
    *previous=0;
  }
}
//第二个八度
void nNoteon(int *previous,int tune,int scale){
  if(*previous==1){}
  if(*previous==0)
  {
    Serial.write(B10010001);
    Serial.write(tune+scale);
    Serial.write(100);
    *previous=1;
  }
}
void nNoteoff(int *previous,int tune,int scale){
  if(*previous==0){}
  if(*previous==1)
  {
    Serial.write(B10000001);
    Serial.write(tune+scale);
    Serial.write(0);
    *previous=0;
  }
}
