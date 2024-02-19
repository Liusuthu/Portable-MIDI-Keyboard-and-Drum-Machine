//初步构思:用数组存曲谱，以16分音符为最小单元，可组成任何2整数的节拍类型
//曲谱细节：1表示延音，0表示休止，如果后一个音符与前一个音符不同，则休止并触发新的音符，音符的音名用C5=60这样的数字表示，最末尾统一加上结束码2，开头统一加上休止符0
//BPM：用delay的毫秒数来控制
//多轨道功能：可以弹奏和弦哦（难点，delay的时间是线性叠加的！！）
//触发函数：编写专门的函数用来读曲谱，采用汉堡包结构——（触发）/（delay一个16分音符的时间）/（停止），这样多个触发和停止函数中间夹着delay可以实现和弦
//函数初步模型 void trigger(int i,int a[]),触发验证本位与前一位的关系，停止验证和后一位的关系，i代表当前读到哪一个16分音符
//原本的Noteon与Noteoff函数的模型在这里可以作为触发和关闭音符使用，有几层和弦层就要几个On/Off函数，一般是四声部


//触发：本个数字是什么
//停止：后一个数字是什么

int memory1,memory2,memory3,memory4;

int i=0;
int music1[98]={0,
77,69,72,69,77,69,  77,69,72,69,77,69,  79,70,72,70,79,70,  77,69,72,69,77,69,
76,67,72,67,76,67,  76,67,72,67,76,67,  77,69,72,69,77,69,  77,69,72,69,77,69,  
81,72,77,72,81,72,  81,72,77,72,81,72,  82,72,79,72,82,72,  81,72,77,72,81,72,
79,78,79,84,79,76,  74,73,74,79,77,74,  72,76,79,76,79,76,  72,1,0,0,0,0,  2};

int music2[98]={0,
53,60,57,60,53,60,  53,60,57,60,53,60,  52,60,55,60,52,60,  53,60,57,60,53,60,
52,58,55,58,52,58,  52,58,55,58,52,58,  53,60,57,60,53,60,  53,60,57,60,53,60,
53,60,57,60,53,60,  53,60,57,60,53,60,  52,60,55,60,52,60,  53,60,57,60,53,60,
55,64,60,64,55,64,  55,64,59,64,55,64,  60,0,60,0,60,0, 60,1,0,0,0,0 ,  2};






int len=98;
int bpm=105;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //触发部
  trigger1(i,music1,&memory1);
  trigger2(i,music2,&memory2);



  //时间控制部
  
  delay(15000/bpm);//每个十六分音符的时间

  //关闭部
  closer1(i,music1,&memory1);
  closer2(i,music2,&memory2);



  //操控部
  i=i+1;
  if(i==len){i=0;}
  /*Noteon1(60);
  delay(1000);
  Noteon1(70);
  Noteoff1(60);
  delay(1000);
  Noteoff1(70);*/
}





void trigger1(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];Noteon1(a[i]);}
  }
}

void closer1(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) Noteoff1(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) Noteoff1(a[i]);}
    }
  }
}
void trigger2(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];Noteon2(a[i]);}
  }
}

void closer2(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) Noteoff2(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) Noteoff2(a[i]);}
    }
  }
}
void trigger3(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];Noteon3(a[i]);}
  }
}

void closer3(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) Noteoff3(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) Noteoff3(a[i]);}
    }
  }
}
void trigger4(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0){*memory=0;/*休止符，不需要触发,仅把memory清除*/}
    else if(a[i]==1||a[i]==2){/*延续符&终止符，不需要操作*/}
    else{*memory=a[i];Noteon4(a[i]);}
  }
}

void closer4(int i,int a[],int *memory){
  if(i==0){/*doing nothing*/}
  else{
    if(a[i]==0||a[i]==2){/*doing nothing*/}
    else{
      if(a[i]==1){if(a[i+1]!=1) Noteoff4(*memory);/*若下一位为1则无需关闭*/}
      else {if(a[i+1]!=1) Noteoff4(a[i]);}
    }
  }
}







//四声部的开关琴键函数
void Noteon1(int tune){
  Serial.write(B10010000);
  Serial.write(tune);
  Serial.write(100);
}
void Noteoff1(int tune){
  Serial.write(B10000000);
  Serial.write(tune);
  Serial.write(0);
}
void Noteon2(int tune){
  Serial.write(B10010001);
  Serial.write(tune);
  Serial.write(100);
}
void Noteoff2(int tune){
  Serial.write(B10000001);
  Serial.write(tune);
  Serial.write(0);
}
void Noteon3(int tune){
  Serial.write(B10010010);
  Serial.write(tune);
  Serial.write(100);
}
void Noteoff3(int tune){
  Serial.write(B10000010);
  Serial.write(tune);
  Serial.write(0);
}
void Noteon4(int tune){
  Serial.write(B10010011);
  Serial.write(tune);
  Serial.write(100);
}
void Noteoff4(int tune){
  Serial.write(B10000011);
  Serial.write(tune);
  Serial.write(0);
}
