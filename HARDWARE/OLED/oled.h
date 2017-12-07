#include "sys.h"

void OLED_WrDat(u8 dat);
void OLED_WrCmd(u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Fill(u8 bmp_dat);
void OLED_Init(void);
void OLED_P6x8Str(u8 x,u8 y,char *ch);
