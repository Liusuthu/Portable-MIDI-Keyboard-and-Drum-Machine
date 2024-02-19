/*---------------------------------------------------------------------------------------------------*/
/*简介：本代码对应硬设大作业电子琴的鼓机模块，内置八套鼓组（实际能启用7套），实现演奏过程中配上打击乐器、氛围声的功能*/
                                     /*开发板：Aruino UNO*/
                                    /*Finish Time:2022/9/1*/
                                     /*Completed by: 李沐晟*/
                                /*Group Members: 甘冀韬，王昊宇，李沐晟*/
                                    /*All Rights Reserved.(x)/*
/*---------------------------------------------------------------------------------------------------*/



const int Vib1=A0,Vib2=A1,Vib3=2,Vib4=A3,Vib5=A4,Vib6=A5;
const int interruptPin=2;//即int.0
const int K1=6,K2=7,K3=8,K4=9,K5=10,K6=11,K7=12,K8=13;
int k1,k2,k3,k4,k5,k6,k7,k8;
const int B=4,W=5;
int flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0;
int V1=0,V2=0,V3=0,V4=0,V5=0,V6=0;
int kit1=1,kit2=0,kit3=0,kit4=0,kit5=0,kit6=0,kit7=0,kit8=0;//默认采用鼓组1
int flag=0;



void setup() {
  Serial.begin(9600);
  Serial.print("AF:30");//音量设置

  pinMode(B,OUTPUT);pinMode(W,OUTPUT);

  pinMode(K1,INPUT_PULLUP);pinMode(K2,INPUT_PULLUP);pinMode(K3,INPUT_PULLUP);
  pinMode(K4,INPUT_PULLUP);pinMode(K5,INPUT_PULLUP);pinMode(K6,INPUT_PULLUP);
  pinMode(K7,INPUT_PULLUP);pinMode(K8,INPUT_PULLUP);
  
  pinMode(interruptPin,INPUT_PULLUP);
  attachInterrupt(0,ChangeKit,FALLING);

  digitalWrite(W,LOW);
  digitalWrite(B,HIGH);
}



//因为MP3模块本身的局限性，在这里不能实现同时触发的功能，先按哪个就哪个响//

void loop() {

  if(flag==1)
  {
    ChangeLight_in();
    while(flag==1){
    
    //采集按钮数据
    k1=digitalRead(K1);k2=digitalRead(K2);k3=digitalRead(K3);
    k4=digitalRead(K4);k5=digitalRead(K5);k6=digitalRead(K6);
    k7=digitalRead(K7);/*k8=digitalRead(K8);*/
    //具体是1还是0需要实验看看
    if(k1==0){kit1=1;flag=0;kit2=0,kit3=0,kit4=0,kit5=0,kit6=0,kit7=0,kit8=0;Serial.print("kit1");}
    if(k2==0){kit2=1;flag=0;kit1=0,kit3=0,kit4=0,kit5=0,kit6=0,kit7=0,kit8=0;Serial.print("kit2");}
    if(k3==0){kit3=1;flag=0;kit1=0,kit2=0,kit4=0,kit5=0,kit6=0,kit7=0,kit8=0;Serial.print("kit3");}
    if(k4==0){kit4=1;flag=0;kit1=0,kit2=0,kit3=0,kit5=0,kit6=0,kit7=0,kit8=0;Serial.print("kit4");}
    if(k5==0){kit5=1;flag=0;kit1=0,kit2=0,kit3=0,kit4=0,kit6=0,kit7=0,kit8=0;Serial.print("kit5");}
    if(k6==0){kit6=1;flag=0;kit1=0,kit2=0,kit3=0,kit4=0,kit5=0,kit7=0,kit8=0;Serial.print("kit6");}
    if(k7==0){kit7=1;flag=0;kit1=0,kit2=0,kit3=0,kit4=0,kit5=0,kit6=0,kit8=0;Serial.print("kit7");}
    /*if(k8==0){kit8=1;flag=0;kit1=0,kit2=0,kit3=0,kit4=0,kit5=0,kit6=0,kit7=0;}*/
    delay(100);
    }
    ChangeLight_out();
  }

  //数据采集区
  V1=analogRead(Vib1);
  V2=analogRead(Vib2);
  V3=analogRead(Vib3);
  V4=analogRead(Vib4);
  V5=analogRead(Vib5);
  V6=analogRead(Vib6);
  flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0; 


  //控制触发哪一个//不知道if有没有比while好用
  if(V1>1000) {flag1=1;V1=analogRead(Vib1);}
  if(V2>1000) {flag2=1;V2=analogRead(Vib2);}
  if(V3>1000) {flag3=1;V3=analogRead(Vib3);}
  if(V4>1000) {flag4=1;V4=analogRead(Vib4);}
  if(V5>1000) {flag5=1;V5=analogRead(Vib5);}
  if(V6>1000) {flag6=1;V6=analogRead(Vib6);}

  
  //操控哪一组鼓：
  if(kit1==1){
    if(flag1==1){Serial.print("A7:00001");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00002");delay(100);}
    if(flag3==1){Serial.print("A7:00003");delay(100);}
    if(flag4==1){Serial.print("A7:00004");delay(100);}
    if(flag5==1){Serial.print("A7:00005");delay(100);}
    if(flag6==1){Serial.print("A7:00006");delay(100);}
  }
  if(kit2==1){
    if(flag1==1){Serial.print("A7:00007");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00008");delay(100);}
    if(flag3==1){Serial.print("A7:00009");delay(100);}
    if(flag4==1){Serial.print("A7:00010");delay(100);}
    if(flag5==1){Serial.print("A7:00011");delay(100);}
    if(flag6==1){Serial.print("A7:00012");delay(100);}
  }
  if(kit3==1){
    if(flag1==1){Serial.print("A7:00013");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00014");delay(100);}
    if(flag3==1){Serial.print("A7:00015");delay(100);}
    if(flag4==1){Serial.print("A7:00016");delay(100);}
    if(flag5==1){Serial.print("A7:00017");delay(100);}
    if(flag6==1){Serial.print("A7:00018");delay(100);}
  }
  if(kit4==1){
    if(flag1==1){Serial.print("A7:00019");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00020");delay(100);}
    if(flag3==1){Serial.print("A7:00021");delay(100);}
    if(flag4==1){Serial.print("A7:00022");delay(100);}
    if(flag5==1){Serial.print("A7:00023");delay(100);}
    if(flag6==1){Serial.print("A7:00024");delay(100);}
  }
  if(kit5==1){
    if(flag1==1){Serial.print("A7:00025");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00026");delay(100);}
    if(flag3==1){Serial.print("A7:00027");delay(100);}
    if(flag4==1){Serial.print("A7:00028");delay(100);}
    if(flag5==1){Serial.print("A7:00029");delay(100);}
    if(flag6==1){Serial.print("A7:00030");delay(100);}
  }
  if(kit6==1){
    if(flag1==1){Serial.print("A7:00031");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00032");delay(100);}
    if(flag3==1){Serial.print("A7:00033");delay(100);}
    if(flag4==1){Serial.print("A7:00034");delay(100);}
    if(flag5==1){Serial.print("A7:00035");delay(100);}
    if(flag6==1){Serial.print("A7:00036");delay(100);}
  }
  if(kit7==1){
    if(flag1==1){Serial.print("A7:00037");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00038");delay(100);}
    if(flag3==1){Serial.print("A7:00039");delay(100);}
    if(flag4==1){Serial.print("A7:00040");delay(100);}
    if(flag5==1){Serial.print("A7:00041");delay(100);}
    if(flag6==1){Serial.print("A7:00043");delay(100);}
  }
  if(kit8==1){
    if(flag1==1){Serial.print("A7:00043");delay(100);}//delay能比较好的处理回弹现象
    if(flag2==1){Serial.print("A7:00044");delay(100);}
    if(flag3==1){Serial.print("A7:00045");delay(100);}
    if(flag4==1){Serial.print("A7:00046");delay(100);}
    if(flag5==1){Serial.print("A7:00047");delay(100);}
    if(flag6==1){Serial.print("A7:00048");delay(100);}
  }
  
}





//切换鼓组的外部中断函数
void ChangeKit()
{
  flag=1;
    Serial.print("change");
}

//切换鼓组时的灯光改变
void ChangeLight_in(){digitalWrite(W,HIGH);digitalWrite(B,LOW);}
void ChangeLight_out(){digitalWrite(W,LOW);digitalWrite(B,HIGH);}


//总结性质：压电模块反应时间迅速，一次归一次；而压力模块有“保持性”。
