
Lcd4_Init();
Lcd4_Command(unsigned char);
Lcd4_Write(unsigned char,unsigned char);
Lcd4_Display(unsigned char ,const char [],unsigned char);
Lcd4_Decimal2(unsigned char ,unsigned char);
Lcd4_Decimal3(unsigned char ,unsigned int);
Lcd4_Decimal4(unsigned char ,unsigned int);
Lcd4_Decimal5(unsigned char ,unsigned int);
Lcd4_Decimal6(unsigned char ,unsigned int);
delay(unsigned char  ,unsigned int );

#define rs RB2
#define en RB3

#define data_port PORTB


Lcd4_Init()
{
	Lcd4_Command(0x02);
	Lcd4_Command(0x28);
	Lcd4_Command(0x0c);
	Lcd4_Command(0x01);

	return(0);
}


Lcd4_Command(unsigned char x)
{
	unsigned char a,b,t;
	a= x & 0xf0;
	b= (x<<4) & 0xf0;
	
	t=data_port & 0x0f;
	data_port=t|a;
	rs=0;
	//RB2=0;
	en=1;
	delay(1,250);
	en=0;

	t=data_port & 0x0f;
	data_port=t|b;
	rs=0;
    //RB2=0;
	en=1;
	delay(1,250);
	en=0;
	
	return(0);	
}


Lcd4_Write(unsigned char y,unsigned char x)
{
	unsigned char a,b,t;
	Lcd4_Command(y);
	a= x & 0xf0;
	b= (x<<4) & 0xf0;
	
	t=data_port & 0x0f;
	data_port=t|a;
	rs=1;
    //RB2=0;
	en=1;
	delay(1,250);
	en=0;

	t=data_port & 0x0f;
	data_port=t|b;
	rs=1;
    //RB2=0;
	en=1;
	delay(1,250);
	en=0;

	return(0);
}

 
Lcd4_Display(unsigned char a,const char b[],unsigned char c)
{
	unsigned char i;
	for(i=0;i<c;i++)
		Lcd4_Write(a+i,b[i]);
	
	return(0);
}

 
Lcd4_Decimal2(unsigned char a,unsigned char b)
{
	unsigned char x,y;
	x=b%100/10;
	y=b%10;
	Lcd4_Write(a,x+0x30);
	Lcd4_Write(a+1,y+0x30);
	
	return(0);
}

 
Lcd4_Decimal3(unsigned char a,unsigned int b)
{
	unsigned char c[3],k;
	c[0]=b%1000/100;
	c[1]=b%100/10;
	c[2]=b%10;
	for(k=0;k<3;k++)
		Lcd4_Write(a+k,c[k]+0x30);
	
	return(0);			
}

 
Lcd4_Decimal4(unsigned char a,unsigned int b)
{
	unsigned char c[4],k;
	c[0]=b%10000/1000;
	c[1]=b%1000/100;
	c[2]=b%100/10;
	c[3]=b%10;
	for(k=0;k<4;k++)
		Lcd4_Write(a+k,c[k]+0x30);
	
	return(0);			
}


Lcd4_Decimal5(unsigned char a,unsigned int b)
{
	unsigned char c[5],k;
	c[0]=b%100000/10000;
	c[1]=b%10000/1000;
	c[2]=b%1000/100;
	c[3]=b%100/10;
	c[4]=b%10;
	for(k=0;k<5;k++)
		Lcd4_Write(a+k,c[k]+0x30);
	
	return(0);			
}
 
Lcd4_Decimal6(unsigned char a,unsigned int b)
{
	unsigned char c[6],k;
	c[0]=b%1000000/100000;
	c[1]=b%100000/10000;
	c[2]=b%10000/1000;
	c[3]=b%1000/100;
	c[4]=b%100/10;
	c[5]=b%10;
	for(k=0;k<6;k++)
		Lcd4_Write(a+k,c[k]+0x30);
	
	return(0);			
}


delay(unsigned char x,unsigned int y)
{
	while(x--)while(y--);
	return(0);
}


 
void Delay(unsigned int del)
{
	while(del--);
}     


