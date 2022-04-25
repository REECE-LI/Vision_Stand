/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:12
 */
#ifndef _PAGE_H
#define _PAGE_H

#include "lvgl.h"
#include "main.h"

// 页面窗口
extern lv_obj_t *appWindow;

// 菜单页面的名称
extern lv_obj_t *labelTitle;

// 菜单页面的logo
extern lv_obj_t *imgLogo;

// 菜单页面的控制组
extern lv_group_t *appGroup;

typedef enum
{
    /*保留*/
    PAGE_NONE = 0,
    /*用户页面*/
    PAGE_CONTROL,
    PAGE_REMEMBER,
    PAGE_ROLL,
    PAGE_ABOUT,
    /*保留*/
    PAGE_MAX
} Page_Type;

typedef struct
{
    const void *src_img;
    const char *name;
    // lv_obj_t * img; 
    u8 pageID;
} PageApp;


extern PageApp pagesApp[];



void pageControl(void);
void pageRemember(void);
void creatImg(const void * src_img, int8_t offSetX, int8_t offSetY);
void creatTitle(const char *text, int8_t offSetX, int8_t offSetY);
//void event_callback(void);
void pageSwitch(u8 idFrom, u8 idTo);

#endif
