#ifndef _FLASH_H
#define _FLASH_H



//需根据自己单片机的型号进行修改
#define BaseAddress ((uint32_t)0x080E0000) // 操作FLAH基地址


void wirteFlash();
void readFlash();



#endif
