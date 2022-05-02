/*
 * @Description: 电机驱动的外接函数
 * @Version: 
 * @Author: 李明骏
 * @Date: 2022-04-28 17:10:17
 */

#ifndef _MOTOR_H
#define _MOTOR_H
#include "main.h"
#include "rocker.h"

void switchDir(u8 which, u8 dir);
void controlMotor(void);


#endif