#include<IRremote.h>
#define choose 2 //1为测试键值

//小车控制
void run();
void forward();
void backward();
void turn_left();
void turn_right();
void stop();

//红外测试
void test();


int receive_pin=6;
IRrecv irrecv(receive_pin);//设置红外接收端口
decode_results results;//变量results用来存放测试结果


void setup()
{
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);//pin2-5控制电机
  irrecv.enableIRIn();
  analogWrite(10,120);
  delay(10);
  analogWrite(9,120);
}

void loop()
{
  if(choose==1) test();
  else run();
}



void test()
{
  if(irrecv.decode(&results))
  {
    Serial.print("Code:");
    Serial.print(results.value,DEC);//显示编码
    Serial.print("   Bits:");
    Serial.println(results.bits);//编码位数
    irrecv.resume();// 继续等待接收下一组信号
  }
  if(results.value==0x16)
    digitalWrite(9, HIGH);  
    delay(600); //延时600毫秒，做一个简单的消抖
}


void run()
{
  if(irrecv.decode(&results))
  {
    if(results.value==16734375  ) {forward();delay(500);stop();}
    else if(results.value==16775175  ) {turn_right();delay(500);stop();}
    else if(results.value==16767015  ) {turn_left();delay(500);stop();}
    else if(results.value==16742535  ) {backward();delay(500);stop();}
    irrecv.resume();
  }
}
void forward()
{
  digitalWrite(2,0);
  digitalWrite(3,1);
  digitalWrite(4,1);
  digitalWrite(5,0);
}
void backward()
{
  digitalWrite(2,1);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,1);
}
void turn_left()
{
  digitalWrite(2,1);
  digitalWrite(3,0);
  digitalWrite(4,1);
  digitalWrite(5,0);
}
void turn_right()
{
  digitalWrite(2,0);
  digitalWrite(3,1);
  digitalWrite(4,0);
  digitalWrite(5,1);
}
void stop()
{
  digitalWrite(2,0);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,0);
}
