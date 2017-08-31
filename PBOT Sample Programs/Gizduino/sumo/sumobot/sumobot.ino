/*
P-BOT Demo Program

     >>-     Sumo Mobot     -<<
>>-by e-Gizmo Mechatronix Central-<<

I/O Usage

- collision sensor inputs
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

int  colsense;
int stuckdetect;
int linesense;
long timer=1000;
boolean randdec;
int  mode;

void loop()                     
{
  colsense=0;
  linesense=0;
  if(digitalRead(col1)==LOW) colsense=1;
  if(digitalRead(col2)==LOW) colsense=colsense+2;
  if(digitalRead(col3)==LOW) colsense=colsense+4;
  if(digitalRead(ls1)==LOW) linesense=1;
  if(digitalRead(ls2)==LOW) linesense=linesense+2;
  if(digitalRead(ls3)==LOW) linesense=linesense+4;
  
  // random decision maker
  if(random(1,1000)<500)
    randdec=LOW;
    else
    randdec=HIGH;
    
  
  // Check if black border is encountered, back off
  if(linesense !=0)
  {
    randomSeed(millis());    //randomize everything
    
    //rotate to keep within arena
    runBot(200,200,LOW);
    delay(500);
    rotBot(150,randdec);
    delay(500);
    
  }
  
  if(linesense ==0)
  {
    
    if(colsense==2)
      // enemy straight ahead, ram it
    {
    
      runBot(250,250,HIGH);
      delay(250);
    }
  
    //Obstruction 1
    if(colsense==1)
    {
        analogWrite(m1run, 250);
        delay(100);
    }
  
    if(colsense==3)
    {
        analogWrite(m1run, 150);
        delay(100);
    }
  
      if(colsense==4)
    {
        analogWrite(m2run, 250);
        delay(100);
    }
  
      if(colsense==6)
    {
        analogWrite(m2run, 150);
        delay(100);
    }
  }
  
  if((linesense==0) & (colsense==0))
  // search for enemy mode
  {
    mode=random(1,7);
    // chane search mode after random time
    if(timer<millis())
    {
      timer=millis()+ random(500,1000);  // change interval random at 1 to 5 sec
      //
      if(mode==1) rotBot(150,randdec);
      if(mode==2) runBot(150,100,HIGH);
      if(mode==3) runBot(100,150,HIGH);
      if(mode==4) runBot(100,100,HIGH);
      if(mode>4) Stop();
    }
      
  }
  
  
}

void runBot(int spd1,int spd2, boolean direction )
{
    digitalWrite(m2dir,direction);
    digitalWrite(m1dir,direction);
    analogWrite(m1run, spd1);
    analogWrite(m2run, spd2); 
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
