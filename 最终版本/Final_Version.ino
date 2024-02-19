/*---------------------------------------------------------------------------------------------------*/
/*简介：本代码对应硬设大作业电子琴的琴键演奏模块，能实现内置曲谱、Midi弹奏、独立弹奏（分为旋律乐器与打击乐器）的功能*/
                                     /*开发板：Aruino Mego 2560*/
                                      /*Finish Time:2022/9/2*/
                                       /*Completed by: 李沐晟*/
                                /*Group Members: 甘冀韬，王昊宇，李沐晟*/
                                      /*All Rights Reserved.(x)/*
/*---------------------------------------------------------------------------------------------------*/




#include <Bounce2.h>
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

Bounce debouncer=Bounce();
const int rs=13,en=12,d4=11,d5=8,d6=7,d7=4;
LiquidCrystal LCD(rs,en,d4,d5,d6,d7);
SoftwareSerial mySerial(5,6);



//控制摇杆的定义
const int interruptSW=2;
const int CtrlX=A12,CtrlY=A13;
int x=512,y=512;


//MIDI模块的相关定义
byte note=0;
byte resetMIDI=3;
byte ledPin=10;
int instrument=0;//在音乐部分为0，在Perc部分为30


//菜单选择相关参数
int menu1=0,menu2=0;
int menu_memory=1,inside_memory=1;
int once0=1,once1=1,once2=1,once3=1,once4=1;//用于Mode刚进入时的一次显示
int choose_memory=1;


//弹奏模式的相关参数
const int  KEY1=A0,KEY2=A1,KEY3=A2,KEY4=A3,KEY5=A4,KEY6=A5,KEY7=A6,KEY8=A7,KEY9=A8,KEY10=A9,KEY11=A10,KEY12=A11;
const int SW1=22,SW2=24,SW3=26,SW4=28,SW5=30,SW6=32,SW7=34,SW8=36,SW9=38,SW10=40,SW11=42,SW12=44;
int previous1=0,previous2=0,previous3=0,previous4=0,previous5=0,previous6=0;
int previous7=0,previous8=0,previous9=0,previous10=0,previous11=0,previous12=0;
int nprevious1=0,nprevious2=0,nprevious3=0,nprevious4=0,nprevious5=0,nprevious6=0;
int nprevious7=0,nprevious8=0,nprevious9=0,nprevious10=0,nprevious11=0,nprevious12=0;
int key1=0,key2=0,key3=0,key4=0,key5=0,key6=0,key7=0,key8=0,key9=0,key10=0,key11=0,key12=0;
int sw1,sw2,sw3,sw4,sw5,sw6,sw7,sw8,sw9,sw10,sw11,sw12;
int scale=0;//每次进入模式前要相应初始化



///////////////////////////////////////////////////////////////////////////////////
//几个音乐谱和BPM
int memory1=0,memory2=0,memory3=0,memory4=0;//在进入每一首歌最好初始化一下
//①校歌
int music11[130]={0,
60,1,1,1,  60,1,64,1,  67,1,1,1,  67,1,1,1,  69,1,1,1,  72,1,69,1,  67,1,1,1,  67,1,1,1,  
64,1,1,1,  64,1,1,1,  67,1,64,1,  60,1,1,1,  57,1,1,1,  60,1,62,1,  67,1,1,1,  1,1,1,1,
69,1,1,1,  69,1,1,1,  69,1,72,1,  67,1,1,1,  64,1,1,1,  62,1,1,1,  64,1,62,1,  60,1,1,1, 
62,1,1,1,  67,1,1,1,  67,1,66,1,  67,1,1,1,  69,1,1,1,  69,1,1,1,  71,1,69,1,  67,1,1,1,  2};

int music12[130]={0,
60,1,1,1,  60,1,1,1,  64,1,1,1,  64,1,1,1,  65,1,1,1,  62,1,1,1,  64,1,1,1,  62,1,1,1,
60,1,1,1,  60,1,1,1,  64,1,60,1,  57,1,1,1,  57,1,1,1,  57,1,60,1,  59,1,1,1,  1,1,1,1,
65,1,1,1,  65,1,1,1,  65,1,1,1,  64,1,1,1,  60,1,1,1,  59,1,1,1,  60,1,59,1,  57,1,1,1,
60,1,1,1,  59,1,1,1,  62,1,1,1,  62,1,1,1,  64,1,1,1,  64,1,1,1,  66,1,1,1,  62,1,1,1,  2};

int music13[130]={0,
53,1,1,1,  53,1,57,1,  60,1,1,1,  60,1,1,1,  60,1,1,1,  59,1,1,1,  60,1,1,1,  59,1,1,1,  
60,1,1,1,  57,1,1,1,  55,1,1,1,  57,1,1,1,  55,1,1,1,  53,1,52,1,  55,1,1,1,  1,1,1,1,
60,1,1,1,  60,1,1,1,  60,1,1,1,  60,1,1,1,  48,1,1,1,  57,1,1,1,  57,1,55,1,  57,1,1,1,
53,1,1,1,  55,1,1,1,  57,1,1,1,  55,1,1,1,  60,1,1,1,  57,1,1,1,  60,1,1,1,  59,1,1,1,  2};

int music14[130]={0,
48,1,1,1,  48,1,1,1,  48,1,1,1,  48,1,1,1,  65,1,1,1,  55,1,1,1,  55,1,1,1,  43,1,1,1,
45,1,1,1,  45,1,1,1,  47,1,1,1,  48,1,1,1,  50,1,1,1,  50,1,1,1,  50,1,1,1,  55,1,1,1,
53,1,1,1,  53,1,1,1,  53,1,57,1,  60,1,1,1,  48,1,1,1,  53,1,1,1,  52,1,1,1,  45,1,1,1,
45,1,1,1,  43,1,1,1,  48,1,1,1,  47,1,1,1,  48,1,1,1,  48,1,1,1,  50,1,1,1,  55,1,1,1,  2};

const int len1=130,bpm1=90;

//②车尔尼
int music21[98]={0,
77,69,72,69,77,69,  77,69,72,69,77,69,  79,70,72,70,79,70,  77,69,72,69,77,69,
76,67,72,67,76,67,  76,67,72,67,76,67,  77,69,72,69,77,69,  77,69,72,69,77,69,  
81,72,77,72,81,72,  81,72,77,72,81,72,  82,72,79,72,82,72,  81,72,77,72,81,72,
79,78,79,84,79,76,  74,73,74,79,77,74,  72,76,79,76,79,76,  72,1,0,0,0,0,  2};

int music22[98]={0,
53,60,57,60,53,60,  53,60,57,60,53,60,  52,60,55,60,52,60,  53,60,57,60,53,60,
52,58,55,58,52,58,  52,58,55,58,52,58,  53,60,57,60,53,60,  53,60,57,60,53,60,
53,60,57,60,53,60,  53,60,57,60,53,60,  52,60,55,60,52,60,  53,60,57,60,53,60,
55,64,60,64,55,64,  55,64,59,64,55,64,  60,0,60,0,60,0, 60,1,0,0,0,0 ,  2};

const int len2=98,bpm2=105;

//③马里奥
int music31[82]={0,
76,76,0,76,  0,72,76,0,  79,0,0,0,  0,0,0,0,  72,0,0,67,  0,0,64,0,  0,69,0,71,  0,70,69,0,
67,0,76,79,  81,0,77,79,  0,76,0,72,  74,71,0,0,  72,0,0,67,  0,0,64,0,  0,69,0,71,  0,70,69,0,
67,0,76,79,  81,0,77,79,  0,76,0,72,  74,71,0,0,  2};

int music32[82]={0,
66,65,0,65,  0,65,65,0,  71,0,0,0,  67,0,0,0,  64,0,0,60,  0,0,55,0,  0,60,0,62,  0,61,60,0,
60,0,67,71,  72,0,69,71,  0,69,0,64,  65,62,0,0,  64,0,0,60,  0,0,55,0,  0,60,0,62,  0,61,60,0,
60,0,67,71,  72,0,69,71,  0,69,0,64,  65,62,0,0,  2};

int music33[82]={0,
50,50,0,50,  0,50,50,0,  55,0,0,0,  55,0,0,0,  55,0,0,52,  0,0,52,0,  0,53,0,55,  0,54,53,0,
52,0,59,64,  65,0,62,64,  0,60,0,57,  59,55,0,0,  55,0,0,52,  0,0,52,0,  0,53,0,55,  0,54,53,0,
52,0,59,64,  65,0,62,64,  0,60,0,57,  59,55,0,0,  2}; 

const int len3=82,bpm3=100;

int i;//"唱针"
///////////////////////////////////////////////////////////////////////////////////



void setup() {
  // put your setup code here, to run once:
  //中断控制
  pinMode(interruptSW,INPUT_PULLUP);
  attachInterrupt(0,changemenu,LOW);
  //消抖器
  debouncer.attach(interruptSW);
  debouncer.interval(500);//interval in ms
  
  LCD.begin(16,2);
  //SW定义引脚
  pinMode(SW1,INPUT_PULLUP);pinMode(SW2,INPUT_PULLUP);pinMode(SW3,INPUT_PULLUP);pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);pinMode(SW6,INPUT_PULLUP);pinMode(SW7,INPUT_PULLUP);pinMode(SW8,INPUT_PULLUP);
  pinMode(SW9,INPUT_PULLUP);pinMode(SW10,INPUT_PULLUP);pinMode(SW11,INPUT_PULLUP);pinMode(SW12,INPUT_PULLUP);

  
}

void loop() {
  // 如果menu1是初始状态0，则选择第一级菜单；
  
  //选择一级菜单模式
  if(menu1==0)
  {
    if(once0==1)
    {
      once0=0;LCD.clear();
      LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.Solo Perc");}   
    }
    x=analogRead(CtrlX),y=analogRead(CtrlY);
    if(x<200)
    {
      menu_memory=menu_memory-1;if(menu_memory<1) menu_memory=1;
      LCD.clear();LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.Solo Perc");}
      delay(500);
    }
    if(x>800)
    {
      menu_memory=menu_memory+1;if(menu_memory>4) menu_memory=4;
      LCD.clear();LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.Solo Perc");}
      delay(500);
    }
    if(y>800)
    {
      menu1=menu_memory;
      //接下来mode123均各自显示菜单内情况
      delay(500);
    }//选定这个模式了
    
  }



  //////////////////////////////////////////////////////////////////////////////////////////
  //Mode1：内置谱模式
  if(menu1==1)
  {
    //选择二级菜单
    if(menu2==0)
    {
      if(once1==1)
      {
        Serial.begin(115200);
        
        once1=0;LCD.clear();LCD.setCursor(0,0);LCD.print("Choose Songs:");
        if(choose_memory==1){LCD.setCursor(0,1);LCD.print("1.School Song");}
        else if(choose_memory==2){LCD.setCursor(0,1);LCD.print("2.Czerny");}
        else if(choose_memory==3){LCD.setCursor(0,1);LCD.print("3.Mario");}
        do{memory1=0,memory2=0,memory3=0,memory4=0,i=0;}while(0);//在选择歌曲时清空记忆
        delay(500);
      }
      x=analogRead(CtrlX),y=analogRead(CtrlY);
      if(x<200)
      {
        choose_memory=choose_memory-1;if(choose_memory<1) choose_memory=1;
        LCD.clear();LCD.setCursor(0,0);LCD.print("Choose Songs:");
        if(choose_memory==1){LCD.setCursor(0,1);LCD.print("1.School Song");}
        else if(choose_memory==2){LCD.setCursor(0,1);LCD.print("2.Czerny");}
        else if(choose_memory==3){LCD.setCursor(0,1);LCD.print("3.Mario");}
        delay(500);
      }
      if(x>800)
      {
        choose_memory=choose_memory+1;if(choose_memory>3) choose_memory=3;
        LCD.clear();LCD.setCursor(0,0);LCD.print("Choose Songs:");
        if(choose_memory==1){LCD.setCursor(0,1);LCD.print("1.School Song");}
        else if(choose_memory==2){LCD.setCursor(0,1);LCD.print("2.Czerny");}
        else if(choose_memory==3){LCD.setCursor(0,1);LCD.print("3.Mario");}
        delay(500);
      }
      if(y>800) 
      {
        menu2=choose_memory;LCD.clear();
        LCD.setCursor(0,0);LCD.print("Chosen:");
        if(choose_memory==1){LCD.setCursor(0,1);LCD.print("1.School Song");}
        else if(choose_memory==2){LCD.setCursor(0,1);LCD.print("2.Czerny");}
        else if(choose_memory==3){LCD.setCursor(0,1);LCD.print("3.Mario");}
        delay(500);
      }
      
    }

    
    //第一首歌:校歌
    if(menu2==1)
    {
      //触发部
      trigger1(i,music11,&memory1);
      trigger2(i,music12,&memory2);
      trigger3(i,music13,&memory3);
      trigger4(i,music14,&memory4);
      //时间控制部  
      delay(15000/bpm1);//每个十六分音符的时间
      //关闭部
      closer1(i,music11,&memory1);
      closer2(i,music12,&memory2);
      closer3(i,music13,&memory3);
      closer4(i,music14,&memory4);
      //操控部
      i=i+1;
      if(i==len1){i=0;}      
    }
    //第二首歌:上课铃
    if(menu2==2)
    {
      //触发部
      trigger1(i,music21,&memory1);
      trigger2(i,music22,&memory2);
      //时间控制部  
      delay(15000/bpm2);//每个十六分音符的时间
      //关闭部
      closer1(i,music21,&memory1);
      closer2(i,music22,&memory2);
      //操控部
      i=i+1;
      if(i==len2){i=0;}      
    }
    //第三首歌:马里奥
    if(menu2==3)
    {
      //触发部
      trigger1(i,music31,&memory1);
      trigger2(i,music32,&memory2);
      trigger3(i,music33,&memory3);      
      //时间控制部  
      delay(15000/bpm3);//每个十六分音符的时间
      //关闭部
      closer1(i,music31,&memory1);
      closer2(i,music32,&memory2);
      closer3(i,music33,&memory3);
      //操控部
      i=i+1;
      if(i==len3){i=0;}      
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////
  


  //////////////////////////////////////////////////////////////////////////////////////////
  //Mode2:Midi演奏模式
  if(menu1==2)
  {
    if(once2==1)
      {
        once2=0;LCD.clear();
        LCD.setCursor(0,0);LCD.print("Midi Playing");
        delay(2000);
        Serial.begin(115200);
        LCD.clear();
        LCD.setCursor(0,0);
        LCD.print("Scale Range:");
        LCD.setCursor(0,1);
        LCD.print(0);
        scale=0;
      }
    //功能代码区
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
    if(x>=800){
    LCD.clear();delay(500);
    scale=scale+12;if(scale>48){scale=48;}
    LCD.setCursor(0,0);
    LCD.print("Scale Range:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }
    if(x<=200){
    LCD.clear();delay(500);
    scale=scale-12;if(scale<-48){scale=-48;}
    LCD.setCursor(0,0);
    LCD.print("Scale Range:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }   
  }
  //////////////////////////////////////////////////////////////////////////////////////////




  //////////////////////////////////////////////////////////////////////////////////////////
  //Mode3:外部演奏乐器模式
  if(menu1==3)
  {
    if(once3==1)
      {
        once3=0;LCD.clear();
        LCD.setCursor(0,0);LCD.print("Solo Instrument");
        delay(2000);
        
        instrument=1;scale=0;
        Serial.begin(57600);
        mySerial.begin(31250);
        pinMode(resetMIDI,OUTPUT);
        digitalWrite(resetMIDI,LOW);
        delay(100);
        digitalWrite(resetMIDI,HIGH);
        talkMIDI(0xB0,0x07,120);//初始化输出channel
        talkMIDI(0xB0,0,0x00);//选择GM1库
        talkMIDI(0xC0,instrument,0);//选择默认乐器       

        LCD.clear();delay(500);
        LCD.setCursor(0,0);
        LCD.print("Scale & Instru:");
        LCD.setCursor(0,1);
        LCD.print(scale/12);
        LCD.setCursor(9,1);
        LCD.print(instrument);
      }
    //功能代码区
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
    if(key1>800){MiNoteon(&previous1,60,scale);}if(key2>800){MiNoteon(&previous2,61,scale);}
    if(key3>800){MiNoteon(&previous3,62,scale);}if(key4>800){MiNoteon(&previous4,63,scale);}
    if(key5>800){MiNoteon(&previous5,64,scale);}if(key6>800){MiNoteon(&previous6,65,scale);}
    if(key7>800){MiNoteon(&previous7,66,scale);}if(key8>800){MiNoteon(&previous8,67,scale);}
    if(key9>800){MiNoteon(&previous9,68,scale);}if(key10>800){MiNoteon(&previous10,69,scale);}
    if(key11>800){MiNoteon(&previous11,70,scale);}if(key12>800){MiNoteon(&previous12,71,scale);}
  
    if(key1<200){MinNoteon(&nprevious1,72,scale);}if(key2<200){MinNoteon(&nprevious2,73,scale);}
    if(key3<200){MinNoteon(&nprevious3,74,scale);}if(key4<200){MinNoteon(&nprevious4,75,scale);}
    if(key5<200){MinNoteon(&nprevious5,76,scale);}if(key6<200){MinNoteon(&nprevious6,77,scale);}
    if(key7<200){MinNoteon(&nprevious7,78,scale);}if(key8<200){MinNoteon(&nprevious8,79,scale);}
    if(key9<200){MinNoteon(&nprevious9,80,scale);}if(key10<200){MinNoteon(&nprevious10,81,scale);}
    if(key11<200){MinNoteon(&nprevious11,82,scale);}if(key12<200){MinNoteon(&nprevious12,83,scale);}

    if(sw1==0&&key1<800&&key1>200){MiNoteon(&previous1,60,scale);MinNoteon(&nprevious1,72,scale);} 
    if(sw2==0&&key2<800&&key2>200){MiNoteon(&previous2,61,scale);MinNoteon(&nprevious2,73,scale);}
    if(sw3==0&&key3<800&&key3>200){MiNoteon(&previous3,62,scale);MinNoteon(&nprevious3,74,scale);}
    if(sw4==0&&key4<800&&key4>200){MiNoteon(&previous4,63,scale);MinNoteon(&nprevious4,75,scale);}
    if(sw5==0&&key5<800&&key5>200){MiNoteon(&previous5,64,scale);MinNoteon(&nprevious5,76,scale);}
    if(sw6==0&&key6<800&&key6>200){MiNoteon(&previous6,65,scale);MinNoteon(&nprevious6,77,scale);}
    if(sw7==0&&key7<800&&key7>200){MiNoteon(&previous7,66,scale);MinNoteon(&nprevious7,78,scale);}
    if(sw8==0&&key8<800&&key8>200){MiNoteon(&previous8,67,scale);MinNoteon(&nprevious8,79,scale);}
    if(sw9==0&&key9<800&&key9>200){MiNoteon(&previous9,68,scale);MinNoteon(&nprevious9,80,scale);}
    if(sw10==0&&key10<800&&key10>200){MiNoteon(&previous10,69,scale);MinNoteon(&nprevious10,81,scale);}
    if(sw11==0&&key11<800&&key11>200){MiNoteon(&previous11,70,scale);MinNoteon(&nprevious11,82,scale);}
    if(sw12==0&&key12<800&&key12>200){MiNoteon(&previous12,71,scale);MinNoteon(&nprevious12,83,scale);}
  
  
    //Note-Off
    if(key1<800&&sw1==1){MiNoteoff(&previous1,60,scale);}if(key2<800&&sw2==1){MiNoteoff(&previous2,61,scale);}
    if(key3<800&&sw3==1){MiNoteoff(&previous3,62,scale);}if(key4<800&&sw4==1){MiNoteoff(&previous4,63,scale);}
    if(key5<800&&sw5==1){MiNoteoff(&previous5,64,scale);}if(key6<800&&sw6==1){MiNoteoff(&previous6,65,scale);}
    if(key7<800&&sw7==1){MiNoteoff(&previous7,66,scale);}if(key8<800&&sw8==1){MiNoteoff(&previous8,67,scale);}
    if(key9<800&&sw9==1){MiNoteoff(&previous9,68,scale);}if(key10<800&&sw10==1){MiNoteoff(&previous10,69,scale);}
    if(key11<800&&sw11==1){MiNoteoff(&previous11,70,scale);}if(key12<800&&sw12==1){MiNoteoff(&previous12,71,scale);}
  
    if(key1>200&&sw1==1){MinNoteoff(&nprevious1,72,scale);}if(key2>200&&sw2==1){MinNoteoff(&nprevious2,73,scale);}
    if(key3>200&&sw3==1){MinNoteoff(&nprevious3,74,scale);}if(key4>200&&sw4==1){MinNoteoff(&nprevious4,75,scale);}
    if(key5>200&&sw5==1){MinNoteoff(&nprevious5,76,scale);}if(key6>200&&sw6==1){MinNoteoff(&nprevious6,77,scale);}
    if(key7>200&&sw7==1){MinNoteoff(&nprevious7,78,scale);}if(key8>200&&sw8==1){MinNoteoff(&nprevious8,79,scale);}
    if(key9>200&&sw9==1){MinNoteoff(&nprevious9,80,scale);}if(key10>200&&sw10==1){MinNoteoff(&nprevious10,81,scale);}
    if(key11>200&&sw11==1){MinNoteoff(&nprevious11,82,scale);}if(key12>200&&sw12==1){MinNoteoff(&nprevious12,83,scale);}

    if(sw1==1&&key1<800&&key1>200){MiNoteoff(&previous1,60,scale);MinNoteoff(&nprevious1,72,scale);}
    if(sw2==1&&key2<800&&key2>200){MiNoteoff(&previous2,61,scale);MinNoteoff(&nprevious2,73,scale);}
    if(sw3==1&&key3<800&&key3>200){MiNoteoff(&previous3,62,scale);MinNoteoff(&nprevious3,74,scale);}
    if(sw4==1&&key4<800&&key4>200){MiNoteoff(&previous4,63,scale);MinNoteoff(&nprevious4,75,scale);}
    if(sw5==1&&key5<800&&key5>200){MiNoteoff(&previous5,64,scale);MinNoteoff(&nprevious5,76,scale);}
    if(sw6==1&&key6<800&&key6>200){MiNoteoff(&previous6,65,scale);MinNoteoff(&nprevious6,77,scale);}
    if(sw7==1&&key7<800&&key7>200){MiNoteoff(&previous7,66,scale);MinNoteoff(&nprevious7,78,scale);}
    if(sw8==1&&key8<800&&key8>200){MiNoteoff(&previous8,67,scale);MinNoteoff(&nprevious8,79,scale);}
    if(sw9==1&&key9<800&&key9>200){MiNoteoff(&previous9,68,scale);MinNoteoff(&nprevious9,80,scale);}
    if(sw10==1&&key10<800&&key10>200){MiNoteoff(&previous10,69,scale);MinNoteoff(&nprevious10,81,scale);}
    if(sw11==1&&key11<800&&key11>200){MiNoteoff(&previous11,70,scale);MinNoteoff(&nprevious11,82,scale);}
    if(sw12==1&&key12<800&&key12>200){MiNoteoff(&previous12,71,scale);MinNoteoff(&nprevious12,83,scale);}

    //To set the scale
    if(x>=800){
    LCD.clear();delay(500);
    scale=scale+12;if(scale>48){scale=48;}
    LCD.setCursor(0,0);
    LCD.print("Scale & Instru:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    LCD.setCursor(9,1);
    LCD.print(instrument);
    }
    if(x<=200){
    LCD.clear();delay(500);
    scale=scale-12;if(scale<-48){scale=-48;}
    LCD.setCursor(0,0);
    LCD.print("Scale & Instru:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    LCD.setCursor(9,1);
    LCD.print(instrument);
    }
  
  
    //To set the instruments
    if(y<=200){
    LCD.clear();delay(500);
    instrument=instrument+1;if(instrument>127){instrument=127;}
    talkMIDI(0xC0,instrument,0);//选择默认乐器
    LCD.setCursor(0,0);
    LCD.print("Scale & Instru:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    LCD.setCursor(9,1);
    LCD.print(instrument);  
    }
    if(y>=800){
    LCD.clear();delay(500);
    instrument=instrument-1;if(instrument<1){instrument=1;}
    talkMIDI(0xC0,instrument,0);//选择默认乐器
    LCD.setCursor(0,0);
    LCD.print("Scale & Instru:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    LCD.setCursor(9,1);
    LCD.print(instrument);
    } 
  }
  //////////////////////////////////////////////////////////////////////////////////////////





  //////////////////////////////////////////////////////////////////////////////////////////
  //Mode4:外部演奏鼓组模式
  if(menu1==4)
  {
    if(once4==1)
    {
      once4=0;LCD.clear();
      LCD.setCursor(0,0);LCD.print("Solo Percussion");
      delay(2000);

      scale=-24,instrument=30;
      Serial.begin(57600);
      mySerial.begin(31250);
      /*pinMode(resetMIDI,OUTPUT);
      digitalWrite(resetMIDI,LOW);
      delay(100);
      digitalWrite(resetMIDI,HIGH);*/
      talkMIDI(0xB0,0x07,120);//初始化输出channel  
      talkMIDI(0xB0,0,0x78);
      talkMIDI(0xC0,instrument,0);//选择默认乐器（30）

      LCD.clear();delay(500);
      LCD.setCursor(0,0);
      LCD.print("Scale:");
      LCD.setCursor(0,1);
      LCD.print(scale/12);
    }
    //功能代码区
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
    if(key1>800){MiNoteon(&previous1,60,scale);}if(key2>800){MiNoteon(&previous2,61,scale);}
    if(key3>800){MiNoteon(&previous3,62,scale);}if(key4>800){MiNoteon(&previous4,63,scale);}
    if(key5>800){MiNoteon(&previous5,64,scale);}if(key6>800){MiNoteon(&previous6,65,scale);}
    if(key7>800){MiNoteon(&previous7,66,scale);}if(key8>800){MiNoteon(&previous8,67,scale);}
    if(key9>800){MiNoteon(&previous9,68,scale);}if(key10>800){MiNoteon(&previous10,69,scale);}
    if(key11>800){MiNoteon(&previous11,70,scale);}if(key12>800){MiNoteon(&previous12,71,scale);}
  
    if(key1<200){MinNoteon(&nprevious1,72,scale);}if(key2<200){MinNoteon(&nprevious2,73,scale);}
    if(key3<200){MinNoteon(&nprevious3,74,scale);}if(key4<200){MinNoteon(&nprevious4,75,scale);}
    if(key5<200){MinNoteon(&nprevious5,76,scale);}if(key6<200){MinNoteon(&nprevious6,77,scale);}
    if(key7<200){MinNoteon(&nprevious7,78,scale);}if(key8<200){MinNoteon(&nprevious8,79,scale);}
    if(key9<200){MinNoteon(&nprevious9,80,scale);}if(key10<200){MinNoteon(&nprevious10,81,scale);}
    if(key11<200){MinNoteon(&nprevious11,82,scale);}if(key12<200){MinNoteon(&nprevious12,83,scale);}

    if(sw1==0&&key1<800&&key1>200){MiNoteon(&previous1,60,scale);MinNoteon(&nprevious1,72,scale);} 
    if(sw2==0&&key2<800&&key2>200){MiNoteon(&previous2,61,scale);MinNoteon(&nprevious2,73,scale);}
    if(sw3==0&&key3<800&&key3>200){MiNoteon(&previous3,62,scale);MinNoteon(&nprevious3,74,scale);}
    if(sw4==0&&key4<800&&key4>200){MiNoteon(&previous4,63,scale);MinNoteon(&nprevious4,75,scale);}
    if(sw5==0&&key5<800&&key5>200){MiNoteon(&previous5,64,scale);MinNoteon(&nprevious5,76,scale);}
    if(sw6==0&&key6<800&&key6>200){MiNoteon(&previous6,65,scale);MinNoteon(&nprevious6,77,scale);}
    if(sw7==0&&key7<800&&key7>200){MiNoteon(&previous7,66,scale);MinNoteon(&nprevious7,78,scale);}
    if(sw8==0&&key8<800&&key8>200){MiNoteon(&previous8,67,scale);MinNoteon(&nprevious8,79,scale);}
    if(sw9==0&&key9<800&&key9>200){MiNoteon(&previous9,68,scale);MinNoteon(&nprevious9,80,scale);}
    if(sw10==0&&key10<800&&key10>200){MiNoteon(&previous10,69,scale);MinNoteon(&nprevious10,81,scale);}
    if(sw11==0&&key11<800&&key11>200){MiNoteon(&previous11,70,scale);MinNoteon(&nprevious11,82,scale);}
    if(sw12==0&&key12<800&&key12>200){MiNoteon(&previous12,71,scale);MinNoteon(&nprevious12,83,scale);}
  
  
    //Note-Off
    if(key1<800&&sw1==1){MiNoteoff(&previous1,60,scale);}if(key2<800&&sw2==1){MiNoteoff(&previous2,61,scale);}
    if(key3<800&&sw3==1){MiNoteoff(&previous3,62,scale);}if(key4<800&&sw4==1){MiNoteoff(&previous4,63,scale);}
    if(key5<800&&sw5==1){MiNoteoff(&previous5,64,scale);}if(key6<800&&sw6==1){MiNoteoff(&previous6,65,scale);}
    if(key7<800&&sw7==1){MiNoteoff(&previous7,66,scale);}if(key8<800&&sw8==1){MiNoteoff(&previous8,67,scale);}
    if(key9<800&&sw9==1){MiNoteoff(&previous9,68,scale);}if(key10<800&&sw10==1){MiNoteoff(&previous10,69,scale);}
    if(key11<800&&sw11==1){MiNoteoff(&previous11,70,scale);}if(key12<800&&sw12==1){MiNoteoff(&previous12,71,scale);}
  
    if(key1>200&&sw1==1){MinNoteoff(&nprevious1,72,scale);}if(key2>200&&sw2==1){MinNoteoff(&nprevious2,73,scale);}
    if(key3>200&&sw3==1){MinNoteoff(&nprevious3,74,scale);}if(key4>200&&sw4==1){MinNoteoff(&nprevious4,75,scale);}
    if(key5>200&&sw5==1){MinNoteoff(&nprevious5,76,scale);}if(key6>200&&sw6==1){MinNoteoff(&nprevious6,77,scale);}
    if(key7>200&&sw7==1){MinNoteoff(&nprevious7,78,scale);}if(key8>200&&sw8==1){MinNoteoff(&nprevious8,79,scale);}
    if(key9>200&&sw9==1){MinNoteoff(&nprevious9,80,scale);}if(key10>200&&sw10==1){MinNoteoff(&nprevious10,81,scale);}
    if(key11>200&&sw11==1){MinNoteoff(&nprevious11,82,scale);}if(key12>200&&sw12==1){MinNoteoff(&nprevious12,83,scale);}

    if(sw1==1&&key1<800&&key1>200){MiNoteoff(&previous1,60,scale);MinNoteoff(&nprevious1,72,scale);}
    if(sw2==1&&key2<800&&key2>200){MiNoteoff(&previous2,61,scale);MinNoteoff(&nprevious2,73,scale);}
    if(sw3==1&&key3<800&&key3>200){MiNoteoff(&previous3,62,scale);MinNoteoff(&nprevious3,74,scale);}
    if(sw4==1&&key4<800&&key4>200){MiNoteoff(&previous4,63,scale);MinNoteoff(&nprevious4,75,scale);}
    if(sw5==1&&key5<800&&key5>200){MiNoteoff(&previous5,64,scale);MinNoteoff(&nprevious5,76,scale);}
    if(sw6==1&&key6<800&&key6>200){MiNoteoff(&previous6,65,scale);MinNoteoff(&nprevious6,77,scale);}
    if(sw7==1&&key7<800&&key7>200){MiNoteoff(&previous7,66,scale);MinNoteoff(&nprevious7,78,scale);}
    if(sw8==1&&key8<800&&key8>200){MiNoteoff(&previous8,67,scale);MinNoteoff(&nprevious8,79,scale);}
    if(sw9==1&&key9<800&&key9>200){MiNoteoff(&previous9,68,scale);MinNoteoff(&nprevious9,80,scale);}
    if(sw10==1&&key10<800&&key10>200){MiNoteoff(&previous10,69,scale);MinNoteoff(&nprevious10,81,scale);}
    if(sw11==1&&key11<800&&key11>200){MiNoteoff(&previous11,70,scale);MinNoteoff(&nprevious11,82,scale);}
    if(sw12==1&&key12<800&&key12>200){MiNoteoff(&previous12,71,scale);MinNoteoff(&nprevious12,83,scale);}

    //To set the scale//可能可以做一个所有音符停止的操作
    if(x>=800){
    LCD.clear();delay(500);
    scale=scale+12;if(scale>48){scale=48;}
    LCD.setCursor(0,0);
    LCD.print("Scale:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }
    if(x<=200){
    LCD.clear();delay(500);
    scale=scale-12;if(scale<-48){scale=-48;}
    LCD.setCursor(0,0);
    LCD.print("Scale:");
    LCD.setCursor(0,1);
    LCD.print(scale/12);
    }
    
  }
  //////////////////////////////////////////////////////////////////////////////////////////


  
}



void changemenu(){
  if(menu2!=0){menu2=0;once1=1;
  //用delay完美解决bounce按键问题
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);}
 
  
  //退出2的选择（重新选择menu2）
  else{menu1=0;once0=1,once1=1,once2=1,once3=1,once4=1;choose_memory=1;}//退出1的选择（重新选择menu1）
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);

}




//////////////////////////////////////////////////////////////////////////////////////////
//内置曲谱专用读谱函数和音符触发函数
void trigger1(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];InNoteon1(a[i]);}
  }
}

void closer1(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) InNoteoff1(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) InNoteoff1(a[i]);}
    }
  }
}
void trigger2(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];InNoteon2(a[i]);}
  }
}

void closer2(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) InNoteoff2(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) InNoteoff2(a[i]);}
    }
  }
}
void trigger3(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];InNoteon3(a[i]);}
  }
}

void closer3(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) InNoteoff3(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) InNoteoff3(a[i]);}
    }
  }
}
void trigger4(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];InNoteon4(a[i]);}
  }
}

void closer4(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) InNoteoff4(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) InNoteoff4(a[i]);}
    }
  }
}
void InNoteon1(int tune){
  Serial.write(B10010000);
  Serial.write(tune);
  Serial.write(100);
}
void InNoteoff1(int tune){
  Serial.write(B10000000);
  Serial.write(tune);
  Serial.write(0);
}
void InNoteon2(int tune){
  Serial.write(B10010001);
  Serial.write(tune);
  Serial.write(100);
}
void InNoteoff2(int tune){
  Serial.write(B10000001);
  Serial.write(tune);
  Serial.write(0);
}
void InNoteon3(int tune){
  Serial.write(B10010010);
  Serial.write(tune);
  Serial.write(100);
}
void InNoteoff3(int tune){
  Serial.write(B10000010);
  Serial.write(tune);
  Serial.write(0);
}
void InNoteon4(int tune){
  Serial.write(B10010011);
  Serial.write(tune);
  Serial.write(100);
}
void InNoteoff4(int tune){
  Serial.write(B10000011);
  Serial.write(tune);
  Serial.write(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////
//MIDI演奏模式的相应触发函数
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
/////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////
//独立演奏模块使用的函数
//Note Functions(Tune range:60~82)
//第一个八度
void MiNoteon(int *previous,int tune,int scale){
  if(*previous==1){}
  if(*previous==0)
  {
    note=tune+scale;
    noteOn(0,note,120);
    *previous=1;
  }
}
void MiNoteoff(int *previous,int tune,int scale){
  if(*previous==0){}
  if(*previous==1)
  {
    note=tune+scale;
    noteOff(0,note,120);
    *previous=0;
  }
}
//第二个八度
void MinNoteon(int *previous,int tune,int scale){
  if(*previous==1){}
  if(*previous==0)
  {
    note=tune+scale;
    noteOn(0,note,120);
    *previous=1;
  }
}
void MinNoteoff(int *previous,int tune,int scale){
  if(*previous==0){}
  if(*previous==1)
  {
    note=tune+scale;
    noteOff(0,note,120);
    *previous=0;
  }
}


//这里是开源的代码
//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}
//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}
//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);
  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
//////////////////////////////////////////////////////////////////////////////////////////////
