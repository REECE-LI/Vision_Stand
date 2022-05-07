/*
 * @Description: FLASH保存 数据保存在最后一片扇区
 * @Author: 李明骏
 * @Date: 2022-05-06 22:07:50
 */
#ifndef _FLASH_H
#define _FLASH_H

#include "main.h"


//需根据自己单片机的型号进行修改






static void eraseFlash(void);
void wirteHWFlash(u16* data, u8 len);
//void wirteWFlash();
void readHWFlash(u16* data, u8 len);



#endif
