/*
 * @Description: 按键操作
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-03-02 17:33:59
 */
#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"

#define keyScan 0
u8 pressJudg(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
u8 pressJudg_R(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#if keyScan
u8 scanKey(void);
#endif

#endif
