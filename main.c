#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DHT11        7


 
int read_dht11(){
  
  int DHT_data[40] = {0,};
  int ready_signal = 0;

  delayMicroseconds(1); // 최초 지연 에러 제거

  pinMode(DHT11, OUTPUT);
  digitalWrite(DHT11,LOW);
  delay(18);
  digitalWrite(DHT11,HIGH);
  pinMode(DHT11,INPUT);
  delayMicroseconds(30);

  while(digitalRead(DHT11) == LOW){     // response signal 
    delayMicroseconds(1);
  }

  while(digitalRead (DHT11) == HIGH){   // pulled ready to output (80us)
    delayMicroseconds(1);
    ready_signal++;
    if(ready_signal > 100){
      return -1;                        // no start - 80us / err (-1)
    }
  }
    
  for(int i=0;i<40;i++){                // data read (40bit)

    while(digitalRead(DHT11) == LOW){
      delayMicroseconds(1);
    }
    delayMicroseconds(29);
    DHT_data[i]=digitalRead(DHT11);
    
    if(digitalRead(DHT11) == HIGH){     // HIGH bit delay
      delayMicroseconds(40);
    }
  }

  pinMode(DHT11, OUTPUT);
  digitalWrite(DHT11,HIGH);


  for(int i=0;i<5;i++){       // 프로토콜 확인
    for(int j=0;j<8;j++){
      printf("%d",DHT_data[j+i*8]);
    }
    printf(" ");
  }
  printf("\r\n");
  

  return 0;
}
 



int main( void )
{

  if(wiringPiSetup()==-1){
    return 1;
  }

  printf("< DHT11 > \r\n");

  while(1){

    read_dht11();
    delay(1000);

  }
 
  return 0;
}

