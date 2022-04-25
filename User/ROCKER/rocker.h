/*
 * @Description: 摇杆毕设
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-14 22:55:50
 */
#ifndef _ROCKER_H
#define _ROCKER_H

#include "main.h"
#include "lcd.h"

#define DRIFT 15
#define MIDDLE 120
#define SWITCHJUDG 40

typedef enum  
{
    linear,         //线性
    noLinear,        //非线性
} mode_t;

typedef enum 
{
    middle,
    up,
    down,
    left,
    right,
    up_left,
    up_right,
    down_right,
    down_left,
    press,
    
} dir_t;

typedef struct
{
   float x_now;
   float y_now;
   float x_last;
   float y_last;
} Site;

extern Site screenSite;
mode_t modeJude(void);
void getAd(void);
dir_t keyDir(void);
void doSth(void);




#endif
