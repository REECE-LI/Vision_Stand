/*
 * @Descripttion: 
 * @version: 
 * @Author: 李明骏
 * @Date: 2021-01-17 13:20:58
 */
 
 
#include "main.h"

#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#define USE_HORIZONTAL 0 //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 240
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 240
#endif

//电阻屏芯片连接引脚
//#define TCLK PAout(5) //PA5  SCLK
//#define TDIN PAout(7) //PA7  MOSI
//#define DOUT PBin(6)  //PB6  MISO
//#define TCS PBout(8)  //PB8  CS2
//#define PEN PBin(9)   //PB9  INT
// #define DOUT HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin)
// #define PEN	 HAL_GPIO_ReadPin(PEN_GPIO_Port, PEN_Pin)

//-----------------LCD端口定义----------------
// HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)

#define LCD_SCLK_Clr() HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET) //SCL=SCLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, GPIO_PIN_RESET) //SDA=MOSI
#define LCD_MOSI_Set() HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, GPIO_PIN_SET)


#define LCD_RES_Clr() HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET) //RES
#define LCD_RES_Set() HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr() HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET) //DC
#define LCD_DC_Set() HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)

// #define LCD_CS2_Clr() HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET)
// #define LCD_CS2_Set() HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET)


// #define LCD_CS_Clr() HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET) //CS1
// #define LCD_CS_Set() HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET)

void LCD_Writ_Bus(uint8_t dat);                            
void LCD_WR_DATA8(uint8_t dat);                            //写入一个字节
void LCD_WR_DATA(uint16_t dat);                            //写入两个字节
void LCD_WR_REG(uint8_t dat);                              //写入一个指令
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); //设置坐标函数
void LCD_Init(void);                                  //LCD初始化
#endif
