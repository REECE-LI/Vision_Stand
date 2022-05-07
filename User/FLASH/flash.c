/*
 * @Description: FLASH保存
 * @Author: 李明骏
 * @Date: 2022-05-06 22:07:43
 */
#include "flash.h"

#define BaseAddress ((uint32_t)0x08079000) // 操作FLAH基地址



/**
 * @Name: eraseFlash
 * @Description: 擦除Flash最后一个扇区 注意这个函数并没有解锁FLASH 每次写入前进行擦除 这只是个调用函数
 * @Author: 李明骏
 * @Return: NULL
 * @Date: 2022-05-07 15:00:52
 */
static void eraseFlash(void) {

    FLASH_EraseInitTypeDef My_Flash;  //声明FLASH_EraseInitTypeDef 结构体为 My_Flash
    
    // HAL_FLASH_Unlock();               //解锁Flash

    My_Flash.TypeErase = FLASH_TYPEERASE_SECTORS;
    My_Flash.Sector = FLASH_SECTOR_7;
    // My_Flash.PageAddress = Flash_Add;  //声明要擦除的地址
    My_Flash.NbSectors = 7;                        //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值

    uint32_t PageError = 0;                    //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
    HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
   // HAL_FLASH_Lock();
}


/**
 * @Name: wirteHWFlash 16位
 * @Description: 解锁上锁FLASH在这个函数中进行 
 * @Author: 李明骏
 * @Return: 
 * @Date: 2022-05-07 15:03:14
 */
void wirteHWFlash(u16* data, u8 len) {
    HAL_FLASH_Unlock();               //解锁Flash
    // eraseFlash();
    // 进行函数写入 16位
    ;
    for (u8 i = 0; i < len; i++) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (BaseAddress + 2 * i), data[i]);
		}
        
    //锁住FLASH
    HAL_FLASH_Lock();
}


/**
 * @Name: readHWFlash
 * @Description: 
 * @Author: 李明骏
 * @Return: 
 * @Date: 2022-05-07 15:13:41
 * @param {u16*} data
 * @param {u8} len
 */
void readHWFlash(u16* data, u8 len) {
    for (u8 i = 0; i < len; i++) {
        data[i] = *(__IO uint16_t*) (BaseAddress + 2 * i);
    }
}