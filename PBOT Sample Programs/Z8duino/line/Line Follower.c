#include <ez8.h>

void forward(int ontime1, int offtime1);
void reverse(int ontime1, int offtime1);
void left(int ontime1, int offtime1);
void rotateL(int ontime1, int offtime1);
void right(int ontime1, int offtime1);
void rotateR(int ontime1, int offtime1);

int d;
int runspeed;
int runtime = 1200;
char input;

void read_line(void)
{
	input=PAIN;
	input = input << 3;
	input=input&0x70;
	input ^= 0x70;
}

#define STOP 	0x00		//0000 
#define L 		0x03		//0011 
#define REV 	0x06		//0110 
#define RL 		0x07		//0111 
#define R 		0x0C		//1100 
#define RR 		0x0E		//1110 
#define FWD 	0x0F		//1111 

void main()
{
	PCDD = 0xF0;	//outputs for motor controls

/*
	Sensor truth table:		hex value:
	000 = reverse				  	0x00
	001 = rotateL					0x02
	010 = forward					0x04
	011 = left						0x06
	100 = rotateR					0x08
	101 = reverse					0x0a
	110 = right						0x0c
	111 = reverse					0x0e
*/
	while(1)
	{
//		read_line();
		while(input==0x00)
		{	
			runspeed = 500;
			reverse(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x10)
		{
			runspeed = 500;
			rotateL(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x20)
		{
			runspeed = 500;
			forward(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x30)
		{
			runspeed = 800;
			left(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x40)
		{
			runspeed = 500;
			rotateR(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x50)
		{
			runspeed = 500;
			reverse(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x60)
		{
			runspeed = 800;
			right(runspeed,runtime - runspeed);
			read_line();
		}
		while(input==0x70)
		{
			runspeed = 500;
			forward(runspeed,runtime - runspeed);
			read_line();
		}
	}
}		

void reverse(int ontime1, int offtime1)
{
	PCOUT = REV;			// reverse
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				//	stop
	for(d=0;d<offtime1;d++){}
}

void left(int ontime1, int offtime1)
{
	PCOUT = L;				// left
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				//	stop
	for(d=0;d<offtime1;d++){}
}

void rotateL(int ontime1, int offtime1)
{
	PCOUT = RL;				// rotateL
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				//	stop
	for(d=0;d<offtime1;d++){}
}

void right(int ontime1, int offtime1)
{
	PCOUT = R;				//right
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				// stop
	for(d=0;d<offtime1;d++){}
}

void rotateR(int ontime1, int offtime1)
{
	PCOUT = RR;				// rotateR
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				// stop
	for(d=0;d<offtime1;d++){}
}

void forward(int ontime1, int offtime1)
{
	PCOUT = FWD;			// forward
	for(d=0;d<ontime1;d++){}
	PCOUT=0;				//	stop
	for(d=0;d<offtime1;d++){}
}

