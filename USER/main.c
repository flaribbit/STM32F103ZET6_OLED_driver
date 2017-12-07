#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "oled.h"
#include "stdio.h"

void disp(){
	char buf[32];
	int i;
	while(1){
		delay_ms(20);
		sprintf(buf,"%02d:%05.2f",i/3000,i%3000/100.);
		OLED_P6x8Str(0,0,buf);
		OLED_P6x8Str(0,1,buf);
		OLED_P6x8Str(0,2,buf);
		OLED_P6x8Str(0,3,buf);
		OLED_P6x8Str(0,4,buf);
		OLED_P6x8Str(0,5,buf);
		OLED_P6x8Str(0,6,buf);
		OLED_P6x8Str(0,7,buf);
		i++;
	}
}
int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000000/900=80Khz
	OLED_Init();
	//OLED_P6x8Str(0,0,"Hello, world!");
	//OLED_P6x8Str(0,1,"QWERTYUIOP");
	//OLED_P6x8Str(0,2,"ASDFGHJKL");
	//OLED_P6x8Str(0,3,"ZXCVBNM");
	//OLED_P6x8Str(0,1,"wdawdwadwadfsajlkdjwlkajdlkwajdlkajsdha");
	disp();
}
