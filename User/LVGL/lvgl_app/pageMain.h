/*
 * @Description: 
 * @Version: 
 * @Author: 李明骏
 * @Date: 2022-04-20 09:52:09
 */
#ifndef _PAGEMAIN_H
#define _PAGEMAIN_H
#include "lvgl.h"

typedef struct
{
   lv_obj_t * Control;
   lv_obj_t * Remember;
   lv_obj_t * Roll;
   lv_obj_t * About;
} ImgLogo;


extern lv_indev_t * indev_keypad;
static void event_callback(lv_obj_t * obj, lv_event_t event);
void creatPageMain(void);



#endif
