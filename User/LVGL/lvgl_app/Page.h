/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:12
 */
#ifndef _PAGE_H
#define _PAGE_H

#include "lvgl.h"

// 页面窗口
lv_obj_t *appWindow;

// 菜单页面的名称
lv_obj_t *labelTitle;

// 菜单页面的logo
lv_obj_t *imgLogo;

// 菜单页面的控制组
lv_group_t *appGroup;

void pageControl(void);
void pageRemember(void);
void creatTitle(const char *text);
void creatImg(const void * src_img);
void event_callback(void);

#endif
