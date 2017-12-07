#include "sys.h"
#include "oled.h"
#include "delay.h"
#include "codetab.h"

#define OLED_SCK PAout(0)
#define OLED_SDA PAout(1)
#define OLED_RST PAout(2)
#define OLED_DC  PAout(3)

#define X_WIDTH 	128
#define Y_WIDTH 	64

void OLED_WrDat(u8 dat)	 
{
	u8 i;
	OLED_DC=1;
	for(i=0;i<8;i++) //发送一个八位数据 
	{
		if((dat << i) & 0x80) OLED_SDA = 1;
		else OLED_SDA = 0;
		OLED_SCK = 0;
		OLED_SCK = 1;
	}
}
void OLED_WrCmd(u8 cmd)
{
	u8 i;
	OLED_DC=0;
	for(i=0;i<8;i++) //发送一个八位数据 
	{
		if((cmd << i) & 0x80) OLED_SDA = 1;
		else OLED_SDA = 0;
		OLED_SCK = 0;
		OLED_SCK = 1;
	}
}
void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}
void OLED_Fill(u8 bmp_dat)
{
	u8 y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
void OLED_Pin_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = 0xff;
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void OLED_Init(void)
{
	OLED_Pin_Init();
	OLED_SCK=1;
	OLED_RST=0;
	delay_ms(50);
	OLED_RST=1;      //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕   
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(0xcf);// Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
}
void OLED_P6x8Str(u8 x,u8 y,char *ch){
	u8 i=0,j;
	OLED_Set_Pos(x,y);
	while(ch[i]){
		for(j=0;j<6;j++) OLED_WrDat(F6x8[ch[i]-32][j]);
		x+=6;
		if(x>122){
			x=0;y++;
			OLED_Set_Pos(x,y);
		}
		i++;
	}
}
