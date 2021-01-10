
#include <Servo.h>  //서보 오브젝트 불러옴


Servo myservo;  //서보 선언

 
float iTime;     //시간을 저장할 실수형 변수 선언

void setup() {
  Serial.begin(9600);        //시리얼 통신 시작
  pinMode(A1, INPUT_PULLUP);  //압력센서의 신호를 아날로그 신호로 받음
  myservo.attach(3);          //서보 핀을 3번에 설정
}

void loop() {
  int val = analogRead(A1);          //압력센서 값을 val에 저장
  int a = map(val, 0, 1023, 180, 0); //압력센서 값을 0~1023 에서 0~180까지 변환
/*
#숫자가 적을수록 근육이 많이 팽창한것#
 0          40          150         180
ㅣ          ㅣ          ㅣ          ㅣ   
                        ㅣ----------ㅣ   ㅡㅡ> if
            ㅣ----------------------ㅣ   ㅡㅡ> else if
ㅣ----------ㅣ                           ㅡㅡ> else 

<ㅡㅡㅡㅡㅡㅡ   근육팽창   ㅡㅡㅡㅡㅡ>
  많이팽창                   적게팽창
*/

  if (a > 150) {        //근육의 힘을 주지않았을때
    iTime += 1;         //시간을 나타내는 변수에 1을 저장

  } else if (a > 40) {   //근육의 힘을 주었을때
    myservo.attach(3);
    delay(10);
    myservo.write(a);    //압력센서 값만큼의 각도로 서보 작동
  } else {               //근육의 힘을 세게 주었을때 
    if (iTime<1000){
      myservo.attach(3);
      delay(10);         
      myservo.write(10); //서보를 10도의 각도로 움직임
      iTime=0;           //힘준 시간을 저장하는 변수 초기화
      delay(300);
    }
    myservo.detach();    //힘준 상태가 유지 될때, 서보의 전원을 차단
  }
Serial.print("힘준시간 : ");    //힘준 시간을 시리얼모니터로 출력
Serial.print(iTime);            //힘준 시간을 시리얼모니터로 출력
Serial.println("ms");           //힘준 시간을 시리얼모니터로 출력

delay(1000);       //시리얼모니터를 편하게 관측하도록 도와주는 딜레이



}
