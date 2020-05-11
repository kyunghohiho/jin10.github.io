//블루투스 모듈(HC-06)을 이용한 서보모터(SG90) 제어
#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include "Servo.h" //서보 라이브러리
 
int blueTx=15;   //Tx (블투 보내는핀 설정)
int blueRx=13;   //Rx (블투 받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
Servo myservo; //서보객체
 
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(13,OUTPUT);   //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
  myservo.attach(12);   //서보 시그널 핀설정
  myservo.write(0);     //서보 초기각도 0도 설정
}
 
void loop() {
  while(mySerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
    
    if(myString=="1")  //myString 값이 'on' 이라면
    {
      digitalWrite(13, HIGH); //LED ON
      myservo.write(60);     //각도 60도로 움직임
    } else if(myString=="2") {
      digitalWrite(13, LOW);  //LED OFF
      myservo.write(0);   //각도 0도로 움직임
    } else {
      for(int i=0;i<5;i++){
        digitalWrite(13, HIGH); //LED ON
        delay(300); 
        digitalWrite(13, LOW);  //LED OFF
        delay(300);
      }
    }
    myString="";  //myString 변수값 초기화
  }
}
