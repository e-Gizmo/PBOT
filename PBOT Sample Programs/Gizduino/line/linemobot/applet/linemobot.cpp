/*
Mobot IV Demo Program

-- line follower ----

I/O Usage
2- colision1 as input
3- colision2 as input
4- colision3 as input
5- linesense1 as input low on black
6- linesense2 as input
7- linesense3 as input
8 - mot2 dir as output high=fwd
9 - mot2 run as output
11 - mot1 dir as output high= fwd
10 - mot1 run as output
 
 */

#include "WProgram.h"
void setup();
void loop();
void runBot(int spd1,int spd2, boolean direction );
void dirfwd(void);
void rotBot(int speed, boolean direction);
void Stop(void);
int  col1= 2;
int  col2= 3;
int  col3= 4;
int  ls1 = 5;
int  ls2 = 6;
int  ls3 = 7;
int  m2dir = 8;
int m2run = 9;
int m1dir = 11;
int m1run = 10;
long int rtc;



// The setup() method runs once, when the sketch starts

void setup()   {                

  //pinMode(col1, INPUT);
  //pinMode(col2, INPUT);
  //pinMode(col3, INPUT);  
  //pinMode(ls1, INPUT);
  //pinMode(ls2, INPUT);
  //pinMode(ls3, INPUT);
  pinMode(m2dir, OUTPUT);
  pinMode(m2run, OUTPUT);
  pinMode(m1dir, OUTPUT);
  pinMode(m1run, OUTPUT);
  pinMode(13, OUTPUT);
  rtc=millis()+10;
}

// the loop() method runs over and over again,
// as long as the Arduino has power

int  colsense = 0;
int  linesense=0;
int giveup=0;
int lastsense;
int runspeed=90;

//timers
byte  retry_dly=0;
byte  ledflsh=25;

void loop()                     
{
  
  // Hardware Timer service
  if(millis()>=rtc)
  {
      rtc=rtc+10;
      if(retry_dly>0) retry_dly--;
      if(ledflsh>0)
      {
        ledflsh--;
        if(ledflsh==0)
        {
          ledflsh=25;
          PORTB ^= 0x20;
        }
      }        
          
  }      

  
  // read the status of colision and line sensors
  colsense=0;
  linesense=0;
  if(digitalRead(col1)==LOW) colsense=1;
  if(digitalRead(col2)==LOW) colsense=colsense+2;
  if(digitalRead(col3)==LOW) colsense=colsense+4;
  if(digitalRead(ls1)==LOW) linesense=1;
  if(digitalRead(ls2)==LOW) linesense=linesense+2;
  if(digitalRead(ls3)==LOW) linesense=linesense+4;
  
  
  // if no line is detected (all high)
  if((linesense==0) & (retry_dly==0))
    {
     if(giveup<10)
     {
          //reverse for 20mS
        if(lastsense==1) runBot(runspeed*15/10,runspeed,LOW);
        if(lastsense==3) runBot(runspeed*12/10,runspeed,LOW);
        if(lastsense==4) runBot(runspeed,runspeed*15/10,LOW);
        if(lastsense==6) runBot(runspeed,runspeed*12/10,LOW);
        
        delay(40);
        giveup++;
      }
      else
      Stop();
      //delay(1000);
    }
 
 // if line is detected
  if(linesense!=0)
     {
        lastsense=linesense;
        giveup=0;
        retry_dly=50;  // retry delay=500ms
     }        
    
// extreme left

  if(linesense==1)
  {
        //Stop();
        dirfwd();
        analogWrite(m2run, runspeed);
        analogWrite(m1run, 0);
//        digitalWrite(m1dir,LOW);
        delay(50);
        
  }
  
 // centered
  
  if((linesense==2)|(linesense==7))
  {
      runBot(runspeed,runspeed,HIGH);
      delay(50);
  }      
 
 
 // skewed left
 
  if(linesense==3)
  {
        Stop();
        dirfwd();
        analogWrite(m2run, runspeed*12/10);
        delay(50);
        
  }
  
 // extreme right
  if(linesense==4)
  {
        //Stop();
        dirfwd();
        analogWrite(m1run, runspeed);
        analogWrite(m2run, 0);
//        digitalWrite(m2dir,LOW);
        delay(50);
       
  }

// skewed right
  if(linesense==6)
  {
        Stop();
        dirfwd();
        analogWrite(m1run, runspeed*12/10);
        delay(50);
       
  }
  
  

  
}


void runBot(int spd1,int spd2, boolean direction )
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,direction);
    analogWrite(m1run, spd1);
    analogWrite(m2run, spd2); 
}

void dirfwd(void)
{
    digitalWrite(m2dir,HIGH);
    digitalWrite(m1dir,HIGH);
}    

void rotBot(int speed, boolean direction)
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,~direction);
    analogWrite(m2run, speed);
    analogWrite(m1run, speed); 
}

void Stop(void)
{
    analogWrite(m2run, 0);
    analogWrite(m1run, 0); 
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

