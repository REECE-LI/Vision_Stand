/*
 * @Description: 测试使用
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-16 10:44:02
 */
#ifndef _TESTAPP_H
#define _TESTAPP_H

#include "lvgl.h"

extern lv_indev_t *indev_keypad;

static void event_callback(lv_obj_t *obj, lv_event_t event);
void app_test(void);

#endif
