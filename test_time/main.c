/*
* delayMicroseconds, usleep 함수 지연시간 확인
*/

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define ECHO 7  // wiringPi 번호 정의
#define EOUT 8  // wiringPi 번호 정의
#define j 10



int main(void){

  if(wiringPiSetup()==-1){
    return 1;
  }

  pinMode(ECHO,INPUT);    // 입력 지연 확인용 
  pinMode(EOUT,OUTPUT);   // 출력 지연 확인용

  digitalWrite(EOUT,HIGH);

  //usleep(10);
  //delayMicroseconds(1);     // 최초 실행 추가 지연? 제거

  while(1){

    int time[j] = {0,};

    int a,b,c;

    time[0] = micros();
        delayMicroseconds(20);
    time[1] = micros();
        delayMicroseconds(20);
    time[2] = micros();
        delayMicroseconds(20);
    time[3] = micros();
        delayMicroseconds(20);
    time[4] = micros();

      a = digitalRead(ECHO);
    time[5] = micros();
      printf("a: %d\r\n\n", a);
    time[6] = micros();
      b = time[0] + time[1];
    time[7] = micros();
    time[8] = micros();

    printf("b: %d\r\n", b);

    for(int a=0;a<j;a++)
      printf("time %d: %d\r\n", a,time[a]);
    

    delay(1000);
  }
}
