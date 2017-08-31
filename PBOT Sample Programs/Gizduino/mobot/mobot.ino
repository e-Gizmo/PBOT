/*
P-BOT Demo Program

>>-     Maze Navigation/Obstacle Avoidance     -<<
       >>-by e-Gizmo Mechatronix Central-<<

I/O Usage

- collision sensor inputs
2- colision1 as input
3- colision2 as input
4- colision3 as input

-line sensor inputs (not used in this demo)
5- linesense1 as input low on black
6- linesense2 as input
7- linesense3 as input

-motor control output
8 - mot2 dir as output high=fwd
9 - mot2 run as output
11 - mot1 dir as output high= fwd
10 - mot1 run as output
 
 */

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



// The setup() method runs once, when the sketch starts

void setup()   {                

  pinMode(col1, INPUT);
  pinMode(col2, INPUT);
  pinMode(col3, INPUT);  
  pinMode(ls1, INPUT);
  pinMode(ls2, INPUT);
  pinMode(ls3, INPUT);
  pinMode(m2dir, OUTPUT);
  pinMode(m2run, OUTPUT);
  pinMode(m1dir, OUTPUT);
  pinMode(m1run, OUTPUT);
}

// the loop() method runs over and over again,
// as long as the Arduino has power

int  colsense = 0;
int stuckdetect;

void loop()                     
{
  runBot(70,HIGH);    // run robot
  
  
  // read the status of colision sensors
  colsense=0;
  if(digitalRead(col1)==LOW) colsense=1;
  if(digitalRead(col2)==LOW) colsense=colsense+2;
  if(digitalRead(col3)==LOW) colsense=colsense+4;
  
  // stuck detect timer
  // if always sense, increment timer
  if(colsense==0) 
    stuckdetect=0;
    else
    stuckdetect=stuckdetect+1;

  // if there is no obstruction, continue moving forward
  if(colsense==0) runBot(150,HIGH);
  
  // Obstruction up front or stuckdetect for more than 2 secs
  if((colsense==2) | stuckdetect>20)
  {
    //reverse for 500mS
    runBot(150,LOW);
    delay(500);
    
    // change direction in random manner
    
    if(random(1,1000)>500)
      digitalWrite(m2dir,HIGH);
      else
      digitalWrite(m1dir,HIGH);
    delay(500);
    
    // move forward again
    runBot(70 ,HIGH);
  }
  
  //Obstruction 1
  if(colsense==1)
  {
        analogWrite(m2run, 150);
        delay(100);
  }
  
  if(colsense==3)
  {
        analogWrite(m2run, 100);
        delay(100);
  }
  
    if(colsense==4)
  {
        analogWrite(m1run, 150);
        delay(100);
  }
  
      if(colsense==6)
  {
        analogWrite(m1run, 100);
        delay(100);
  }
  
}

void runBot(int speed, boolean direction )
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,direction);
    analogWrite(m2run, speed);
    analogWrite(m1run, speed); 
}

void Stop(void)
{
    analogWrite(m2run, 0);
    analogWrite(m1run, 0); 
}
