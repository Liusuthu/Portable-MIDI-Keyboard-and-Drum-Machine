#include <Bounce2.h>
#include <LiquidCrystal.h>

Bounce debouncer=Bounce();

const int rs=13,en=12,d4=11,d5=8,d6=7,d7=4;
LiquidCrystal LCD(rs,en,d4,d5,d6,d7);

const int interruptSW=2;
const int CtrlX=A12,CtrlY=A13;
int x,y;
int menu1=0,menu2=0;

int menu_memory=1,inside_memory=1;

int once0=1,once1=1,once2=1,once3=1,once4=1;//用于Mode刚进入时的一次显示
int choose_memory=1;


void setup() {
  // put your setup code here, to run once:
  pinMode(interruptSW,INPUT_PULLUP);
  attachInterrupt(0,changemenu,LOW);

  debouncer.attach(interruptSW);
  debouncer.interval(500);//interval in ms

  LCD.begin(16,2);
  
}

void loop() {
  // 如果menu1是初始状态0，则选择第一级菜单；
  if(menu1==0)
  {
    if(once0==1)
    {
      once0=0;LCD.clear();
      LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.SOlo Perc");}   
    }
    x=analogRead(CtrlX),y=analogRead(CtrlY);
    if(x<200)
    {
      menu_memory=menu_memory-1;if(menu_memory<1) menu_memory=1;
      LCD.clear();LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.SOlo Perc");}
      delay(500);
    }
    if(x>800)
    {
      menu_memory=menu_memory+1;if(menu_memory>4) menu_memory=4;
      LCD.clear();LCD.setCursor(0,0);LCD.print("Mode:");
      if(menu_memory==1){LCD.setCursor(0,1);LCD.print("1.Inside Music");}
      else if(menu_memory==2){LCD.setCursor(0,1);LCD.print("2.Midi Playing");}
      else if(menu_memory==3){LCD.setCursor(0,1);LCD.print("3.Solo Instru");} 
      else if(menu_memory==4){LCD.setCursor(0,1);LCD.print("4.SOlo Perc");}
      delay(500);
    }
    if(y>800)
    {
      menu1=menu_memory;
      //接下来mode123均各自显示菜单内情况
      delay(500);
    }//选定这个模式了
    
  }




  //Mode1：内置谱模式
  if(menu1==1)
  {
    //选择二级菜单
    if(menu2==0)
    {
      if(once1==1)
      {
        once1=0;LCD.clear();LCD.setCursor(0,0);LCD.print("Choose Songs:");
        if(choose_memory==1){LCD.setCursor(0,1);LCD.print("1.School Song");}
        else if(choose_memory==2){LCD.setCursor(0,1);LCD.print("2.Czerny");}
        else if(choose_memory==3){LCD.setCursor(0,1);LCD.print("3.Mario");}
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

    
    //第一首歌
    if(menu2==1){}
    //第二首歌
    if(menu2==2){}
    //第三首歌
    if(menu2==3){}
  }


  //Mode2:Midi演奏模式
  if(menu1==2)
  {
    if(once2==1)
      {
        once2=0;LCD.clear();
        LCD.setCursor(0,0);LCD.print("Midi Playing");
      }
    //功能代码区



    
  }


  //Mode3:外部演奏乐器模式
  if(menu1==3)
  {
    if(once3==1)
      {
        once3=0;LCD.clear();
        LCD.setCursor(0,0);LCD.print("Solo Instrument");       
      }
    //功能代码区


    
  }


  //Mode4:外部演奏鼓组模式
  if(menu1==4)
  {
    if(once4==1)
    {
      once4=0;LCD.clear();
      LCD.setCursor(0,0);LCD.print("Solo Percussion");
    }
    //功能代码区


    
  }


  
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
