/*
P-BOT Demo Program

>>-     Line following Mobot     -<<
>>-by e-Gizmo Mechatronix Central-<<

This demo program will make the P-BOT detect to follow
a black line path laid out on a light colored surface.
track width is 15-19mm wide.



I/O Usage

- collision sensor inputs (not used in this demo)
2- colision1 as input
3- colision2 as input
4- colision3 as input

-line sensor inputs
5- linesense1 as input low on black
6- linesense2 as input
7- linesense3 as input

-motor control output
8 - mot2 dir as output high=fwd
9 - mot2 run as output
11 - mot1 dir as output high= fwd
10 - mot1 run as output
 
 */

int  col1= 16;
int  col2= 15;
int  col3= 14;
int  ls1 = 12;
int  ls2 = 11;
int  ls3 = 10;
int  m2dir = 7;
int m2run = 6;
int m1run = 5;
int m1dir = 4;
long int rtc;

// Initialization routine
void setup()   {                
  pinMode(m2dir, OUTPUT);
  pinMode(m2run, OUTPUT);
  pinMode(m1dir, OUTPUT);
  pinMode(m1run, OUTPUT);
  pinMode(13, OUTPUT);
  rtc=millis()+10;
}

int  colsense = 0;
int  linesense=0;
int giveup=0;
int lastsense;
int runspeed;
int runtime=1000;

//timers
char  retry_dly=0;
char  ledflsh=25;

void Mrun(int motor,int ontime, int offtime)
{
    digitalWrite(motor,HIGH); 
    delayMicroseconds(ontime);
    digitalWrite(motor,LOW); 
    delayMicroseconds(offtime);
}

void runBot(int spd1,int spd2, char direction )
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,direction);
    Mrun(m1run,spd1,runtime-spd1);
    Mrun(m2run,spd2,runtime-spd2);
}

void dirfwd(void)
{
    digitalWrite(m2dir,HIGH);
    digitalWrite(m1dir,HIGH);
}    

void rotBot(int speed, char direction)
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,~direction);
    Mrun(m1run,speed,runtime-speed);
    Mrun(m2run,speed,runtime-speed);
}

void Stop(void)
{
    Mrun(m1run,0,runtime);
    Mrun(m2run,0,runtime);
}

// Main Line following program loop
void loop()                     
{
    digitalWrite(13,HIGH);
    digitalWrite(13,LOW);
//    digitalWrite(m2dir,HIGH);
//    digitalWrite(m1dir,HIGH);
//    digitalWrite(m2dir,LOW);
//    digitalWrite(m1dir,LOW);
  
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
				PORTC ^= 0x04;
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
	if(linesense==0)// & (retry_dly==0))
		{
			runspeed = 500;
			runBot(runspeed,runspeed,LOW);
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
	Mrun(m1run,0,runtime);
   runspeed = 980; 
   Mrun(m2run,runspeed,runtime-runspeed);
//        digitalWrite(m1dir,LOW);
//        delay(50);
  }
  
 // centered
	if((linesense==2)|(linesense==7))
	{
		runspeed = 800;
      runBot(runspeed,runspeed,HIGH);
//      delay(50);
	}      
 
 // skewed left
	if(linesense==3)
	{
      Stop();
      dirfwd();
		runspeed = 980;
		Mrun(m2run,runspeed,runtime-runspeed);
//    delay(50);
	}
  
 // extreme right
	if(linesense==4)
	{
      //Stop();
      dirfwd();
		runspeed = 980;
		Mrun(m1run,runspeed,runtime-runspeed);
		Mrun(m2run,0,runtime);
//        digitalWrite(m2dir,LOW);
//        delay(50);
	}

// skewed right
	if(linesense==6)
	{
      Stop();
      dirfwd();
		runspeed = 980;
		Mrun(m1run,runspeed,runtime-runspeed);
//        analogWrite(m1run, runspeed*12/10);
//        delay(50);
	}
}
