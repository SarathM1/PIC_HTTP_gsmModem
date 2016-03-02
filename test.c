#include<pic.h>
#include"pic_lcd4.h"
#include"Delay.h"
#include"string.h"


char val[20],day[15],th[5],tl[5];
int u=0,flg=0,dis=0,ver=0;
void interrupt uart(void)
{

if(RCIF)
{
val[u]=RCREG;
RCIF=0;

if(ver==10&&val[0]==':')
ver=11;

if(ver==8&&val[0]==':')
ver=9;

if(ver==7&&val[0]==':')
ver=8;

if(ver==5&&val[0]==':')//get date here
ver=6;

if(ver==4&&val[0]==',')
ver=5;

if(ver==3&&val[0]=='{')
ver=4;

if(ver==2&&val[0]=='{')
ver=3;

if(ver==1&&val[0]=='{')
ver=2;

if(flg==1&&val[0]=='[')
ver=1;

if(ver==6)
day[u]=val[u];

if(ver==9)
th[u]=val[u];

if(ver==11)
tl[u]=val[u];

if(ver==6||ver==9||ver==11)
u++;
else
u=0;

if(u>11&&ver==6)
{
u=0;
ver=7;
val[0]='N';
}

if(u>3&&ver==9)
{
u=0;
ver=10;
val[0]='N';
}

if(u>3&&ver==11)
{
u=0;
ver=12;
val[0]='N';
}

if(ver==12)
{
flg=0;
u=0;
ver=0;
dis=1;
//val[0]='N';
}

}

}

void gsm(char m[])
{
	int k=strlen(m);
	for(int n=0;n<k;n++)
	{
	TXREG=m[n];
       while(!TXIF);
	}
}

void delay11()
{
DelayMs(999);
DelayMs(999);
}

void main()
{
char dat[20];
TRISB=0X00;
TRISC=0X80;
RCSTA=0X90;
TXSTA=0X24;
SPBRG=0x33;;
Lcd4_Init();

GIE=1;
PEIE=1;
RCIE=1;

Lcd4_Display(0X80,"WETHER",6);
delay11();
Lcd4_Command(0x01);

gsm("AT\r\n");
delay11();
gsm("AT\r\n");
delay11();

gsm("ATE0\r\n");
delay11();

gsm("AT+CGATT=1\r\n");

delay11();delay11();
gsm("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");
delay11();delay11();

gsm("AT+SAPBR=3,1,\"APN\",www\r\n");
	
delay11();delay11();delay11();delay11();
gsm("AT+SAPBR=1,1\r\n");
delay11();delay11();delay11();delay11();
delay11();delay11();delay11();

gsm("AT+HTTPINIT\r\n");
delay11();delay11();delay11();delay11();delay11();delay11();
gsm("AT+HTTPPARA=\"URL\",\"http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22nome%2C%20ak%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys\"\r\n");
delay11();delay11();
gsm("AT+HTTPACTION=0\r\n");
DelayMs(999);
delay11();delay11();delay11();delay11();delay11();delay11();
delay11();delay11();delay11();delay11();delay11();delay11();
delay11();delay11();delay11();delay11();
gsm("AT+HTTPREAD\r\n");
flg=1;

while(1)
{
if(dis==1)
{


Lcd4_Display(0Xc2,th,4);
Lcd4_Display(0Xc8,tl,4);

Lcd4_Write(0xc1,'H');
Lcd4_Write(0xc3,' ');

Lcd4_Write(0xc7,'L');
Lcd4_Write(0xc9,' ');

Lcd4_Display(0X82,day,12);
Lcd4_Display(0X82,"  ",2);

delay11();
gsm("AT+HTTPTERM\r\n");
while(8);
}
}
}




