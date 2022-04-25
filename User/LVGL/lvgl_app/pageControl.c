/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:01
 */
#include "lvgl.h"
#include "Page.h"

extern lv_obj_t *barStart;
extern lv_obj_t *Logo;
static lv_obj_t *controlWindow;

void pageControl(void)
{

#if 1
    lv_obj_clean(appWindow);
#else
    lv_obj_del(barStart);
    lv_obj_del(Logo);
#endif 

    creatTitle("CONTROL");
    creatImg();
}

void creatTitle(const char *text)
{
    labelTitle = lv_label_create(appWindow, NULL);

    lv_label_set_static_text(labelTitle, text);
    lv_obj_align(labelTitle, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_obj_set_auto_realign(labelTitle, true);
}

void creatImg(void)
{
    LV_IMG_DECLARE(imgControl);

    imgLogo = lv_img_create(appWindow, NULL);
    lv_img_set_src(imgLogo, &imgControl);
    lv_img_set_zoom(imgLogo, 75);
    lv_obj_align(imgLogo, labelTitle, LV_ALIGN_OUT_TOP_MID, 0, 65);
    // lv_obj_set_style_local_opa_scale(imgLogo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
}
