/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:01
 */
#include "lvgl.h"
#include "Page.h"
/*此页面窗口*/
static lv_obj_t *appWindow;

/*标题栏*/
static lv_obj_t *labelTitle;

/*标题栏分隔线*/
static lv_obj_t *lineTitle;

static lv_obj_t *imgLogo;

static void creatImg(void);


extern lv_obj_t *barStart;
extern lv_obj_t *Logo;

void pageControl(void)
{
#if 0
    appWindow = lv_scr_act();
#endif // 1
		lv_obj_del(barStart);
		lv_obj_del(Logo);
    //lv_obj_move_foreground(appWindow);
    creatTitle("CONTROL");
    creatImg();
}

void creatTitle(const char *text)
{
    // LV_FONT_DECLARE(HandGotn_20);
    labelTitle = lv_label_create(lv_scr_act(), NULL);

    /* static lv_style_t style_label;
     style_label = *lv_label_get_style(labelTitle, LV_LABEL_STYLE_MAIN);
     style_label.text.font = &HandGotn_20;
     style_label.text.color = LV_COLOR_WHITE;
     lv_label_set_style(labelTitle, LV_LABEL_STYLE_MAIN, &style_label);*/

    lv_label_set_static_text(labelTitle, text);
    lv_obj_align(labelTitle, NULL, LV_ALIGN_CENTER, 0, 80);
    lv_obj_set_auto_realign(labelTitle, true);

    /* lineTitle = lv_line_create(appWindow, NULL);
     static lv_point_t line_points[] = { {0, 0}, {APP_WIN_WIDTH, 0} };
     lv_line_set_points(lineTitle, line_points, 2);
     static lv_style_t style_line;
     style_line = *lv_line_get_style(lineTitle, LV_LINE_STYLE_MAIN);
     style_line.line.color = LV_COLOR_RED;
     style_line.line.width = 2;
     style_line.line.rounded = 1;
     lv_line_set_style(lineTitle, LV_LINE_STYLE_MAIN, &style_line);
     lv_obj_align(lineTitle, labelTitle, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);*/
}

void creatImg(void)
{
    LV_IMG_DECLARE(imgControl);

    imgLogo = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(imgLogo, &imgControl);
    lv_obj_align(imgLogo, labelTitle, LV_ALIGN_OUT_TOP_MID, 0, -10);
    // lv_obj_set_style_local_opa_scale(imgLogo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
}
