#include <Arduino.h>
#include <lvgl.h>
#include "layout.h"
#include "logging.h"
#include "settings.h"
#include "uicallbacks.h"

// Style for horn buttons when pressed
lv_style_t style_pr;

// Screens
lv_obj_t *screen1;
lv_obj_t *screen2;
lv_obj_t *settingsscreen;

// These need better names or to be gotten rid of if they aren't needed
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;

// Flex containers
lv_obj_t *main_container;
lv_obj_t *brightness_container;
lv_obj_t *brightness_sliderandlabel_container;
lv_obj_t *darkmode_container;
lv_obj_t *titlebar_container;
lv_obj_t *ziploc_container;
lv_obj_t *test_container;

// Brightness slider, printed value, and title
lv_obj_t *brightness_slider;
lv_obj_t *brightness_label;
lv_obj_t *brightness_title;

// Dark mode switch and title
lv_obj_t *darkmode_switch;
lv_obj_t *darkmode_title;

// Titlebar title and close button
lv_obj_t *main_title;
lv_obj_t *close_button;
lv_obj_t *labelX;
lv_obj_t *titlebar_leftside;
lv_obj_t *titlebar_rightside;

// Test title and close button
lv_obj_t *test_title;
lv_obj_t *test_button;
lv_obj_t *ziploc_left;
lv_obj_t *ziploc_right;

// Popup label for button testing
lv_obj_t *popuplabel;
lv_style_t popuplabelstyle;

void generate_mask(lv_draw_buf_t *mask, int32_t w, int32_t h, const char *txt)
{
    /*Create a "8 bit alpha" canvas and clear it*/
    lv_obj_t *canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(canvas, mask);
    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_TRANSP);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    /*Draw a label to the canvas. The result "image" will be used as mask*/
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = lv_color_white();
    label_dsc.align = LV_TEXT_ALIGN_CENTER;
    label_dsc.text = txt;
    label_dsc.font = &lv_font_montserrat_30;
    lv_area_t a = { 0, 0, w - 1, h - 1 };
    lv_draw_label(&layer, &label_dsc, &a);

    lv_canvas_finish_layer(canvas, &layer);

    lv_obj_delete(canvas);
}

void CreateMainContainer()
{
    //
    // Create main container with COLUMN flex direction
    // brightness_container
    // darkmode_container
    //

    main_container = lv_obj_create(lv_screen_active());
    lv_obj_set_layout(main_container, LV_LAYOUT_FLEX);

    lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_COLUMN);  // reverse so the title can be created later and still ends up visually on top
    // Set width and height to 100% of the parent's content area
    lv_obj_set_size(main_container, LV_PCT(100), LV_PCT(100));

    // Comment this during testing to see the container border so you know it's what you want.
    lv_obj_set_style_border_width(main_container, 0, 0);

    lv_obj_set_style_pad_all(main_container, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_all(main_container, 0, LV_PART_MAIN);
}

void CreateTitleBar()
{
    titlebar_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(titlebar_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(titlebar_container, lv_pct(100));
    lv_obj_set_height(titlebar_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    lv_obj_set_style_pad_all(titlebar_container, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_all(titlebar_container, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_bottom(titlebar_container, 20, LV_PART_MAIN);

    titlebar_leftside = lv_obj_create(titlebar_container);
    titlebar_rightside = lv_obj_create(titlebar_container);

    // I could not get things to line up until I put an extra
    // container layer in, titlebar_leftside & titlebar_rightside.
    // LVGL's flexbox isn't quite the same as HTML/CSS's despite what
    // the documentation says because I've done this layout many
    // times in HTML/CSS without the extra layer.

    lv_obj_set_height(titlebar_leftside, LV_SIZE_CONTENT);
    lv_obj_set_height(titlebar_rightside, LV_SIZE_CONTENT);

    //lv_obj_set_style_pad_all(titlebar_leftside, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(titlebar_rightside, 0, LV_PART_MAIN);
    //lv_obj_set_style_margin_all(titlebar_leftside, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_all(titlebar_rightside, 0, LV_PART_MAIN);

    lv_obj_set_width(titlebar_leftside, LV_SIZE_CONTENT);
    lv_obj_set_width(titlebar_rightside, LV_SIZE_CONTENT);

    lv_obj_set_flex_grow(titlebar_leftside, 1);
    lv_obj_set_flex_grow(titlebar_rightside, 0);
    lv_obj_set_height(titlebar_leftside, LV_SIZE_CONTENT);

    logit("create title");
    // Create the mask of a text by drawing it to a canvas
    LV_DRAW_BUF_DEFINE_STATIC(mask, MASK_WIDTH, MASK_HEIGHT, LV_COLOR_FORMAT_L8);
    LV_DRAW_BUF_INIT_STATIC(mask);

    generate_mask(&mask, MASK_WIDTH, MASK_HEIGHT, "SETTINGS");

    // Create an object from where the text will be masked out.
    // Now it's a rectangle with a gradient but it could be an image too

    main_title = lv_obj_create(titlebar_leftside);
    lv_obj_set_size(main_title, MASK_WIDTH, MASK_HEIGHT);
    lv_obj_set_style_bg_color(main_title, lv_color_hex(0xff0000), 0);
    lv_obj_set_style_bg_grad_color(main_title, lv_color_hex(0x0000ff), 0);
    lv_obj_set_style_bg_grad_dir(main_title, LV_GRAD_DIR_HOR, 0);
    lv_obj_set_style_bitmap_mask_src(main_title, &mask, 0);

    close_button = lv_button_create(titlebar_rightside);
    labelX = lv_label_create(close_button);
    lv_label_set_text(labelX, LV_SYMBOL_CLOSE);
    lv_obj_center(labelX);  // Center the 'X' symbol within the button
    //lv_obj_set_style_pad_left(close_button, 4, LV_PART_MAIN);
    //lv_obj_set_style_pad_left(close_button, 0, LV_PART_MAIN);
    lv_obj_set_style_margin_right(close_button, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_right(close_button, 0, LV_PART_MAIN);

    // Comment this during testing to see the container border so you know it's what you want.
    lv_obj_set_style_border_width(titlebar_container, 0, 0);
    lv_obj_set_style_border_width(titlebar_leftside, 0, 0);
    lv_obj_set_style_border_width(titlebar_rightside, 0, 0);
    
}

void CreateZiploc()
{
    ziploc_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(ziploc_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(ziploc_container, lv_pct(100));
    lv_obj_set_height(ziploc_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    //ziploc_left = lv_label_create(ziploc_container);
    //lv_label_set_text(ziploc_left, "ziploc_left");
    ziploc_left = lv_slider_create(ziploc_container);
    lv_obj_set_flex_grow(ziploc_left, 1);

    ziploc_right = lv_label_create(ziploc_container);
    lv_label_set_text(ziploc_right, "ziploc_right");
    logit("#################################################%s", pct);
    lv_label_set_text(ziploc_right, pct.c_str());

    // Comment this during testing to see the container border so you know it's what you want.
    lv_obj_set_style_border_width(ziploc_container, 0, 0);
}

void CreateBrightness()
{
    enterfunction("CreateBrightness");

    logit("Create brightness_container");
    brightness_container = lv_obj_create(main_container);
    logit("set brightness_container flex flow to column");
    lv_obj_set_flex_flow(brightness_container, LV_FLEX_FLOW_COLUMN);
    logit("set brightness_container width");
    lv_obj_set_width(brightness_container, lv_pct(100));
    logit("set brightness_container height");
    lv_obj_set_height(brightness_container, LV_SIZE_CONTENT);  // grow/shrink based on content
    lv_obj_set_style_pad_bottom(brightness_container, 20, LV_PART_MAIN);
    lv_obj_set_style_margin_right(brightness_container, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(brightness_container, 0, LV_PART_MAIN);


    brightness_title = lv_label_create(brightness_container);
    lv_label_set_text(brightness_title, "Brightness");

    brightness_sliderandlabel_container = lv_obj_create(brightness_container);
    lv_obj_set_layout(brightness_sliderandlabel_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(brightness_sliderandlabel_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(brightness_sliderandlabel_container, lv_pct(100));
    lv_obj_set_height(brightness_sliderandlabel_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    lv_obj_set_style_margin_right(brightness_sliderandlabel_container, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_right(brightness_sliderandlabel_container, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_left(brightness_sliderandlabel_container, 30, LV_PART_MAIN);
    // moving this in, the slider doesn't want to register all the
    // way to the left without multiple presses
    //lv_obj_set_style_pad_left(brightness_sliderandlabel_container, 20, LV_PART_MAIN);
    //lv_obj_set_style_margin_left(brightness_sliderandlabel_container, 20, LV_PART_MAIN);

    brightness_slider = lv_slider_create(brightness_sliderandlabel_container);
    lv_slider_set_range(brightness_slider, 10, 100);  // don't allow turning completely off or there is no way to turn it back on
    lv_obj_add_event_cb(brightness_slider, HandleBrightnessSlider, LV_EVENT_ALL, NULL);
    //lv_obj_set_style_margin_left(brightness_slider, 20, LV_PART_MAIN);
    //lv_obj_set_style_margin_left(brightness_slider, 20, LV_PART_MAIN);
    //lv_obj_set_style_pad_left(brightness_slider, 0, LV_PART_MAIN);

    // make the knob and detected touch area larger so it's easier to slide
    lv_obj_set_ext_click_area(brightness_slider, 20);
    //lv_obj_set_style_pad_left(brightness_slider, 10, LV_PART_KNOB);
    //lv_obj_set_style_pad_right(brightness_slider, 6, LV_PART_KNOB);
    //lv_obj_set_style_pad_top(brightness_slider, 6, LV_PART_KNOB);
    //lv_obj_set_style_pad_bottom(brightness_slider, 6, LV_PART_KNOB);

    // make the bar a little larger
    lv_obj_set_height(brightness_slider, 20);

    logit("create slider label");
    brightness_label = lv_label_create(brightness_sliderandlabel_container);
    lv_label_set_text(brightness_label, pct.c_str());
    lv_obj_set_style_pad_left(brightness_label, 30, LV_PART_MAIN);
    lv_obj_set_style_pad_right(brightness_label, 0, LV_PART_MAIN);

    // SLIDER | LABEL
    lv_obj_set_flex_grow(brightness_slider, 2);
    lv_obj_set_flex_grow(brightness_label, 1);

    logit("############################################### int percentage: %d", percentage);
    lv_slider_set_value(brightness_slider, percentage, LV_ANIM_OFF);

    // Comment this during testing to see the container border so you know it's what you want.
    lv_obj_set_style_border_width(brightness_container, 0, 0);
    lv_obj_set_style_border_width(brightness_sliderandlabel_container, 0, 0);

    exitfunction("CreateBrightness");
}


void CreateTest()
{
    test_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(test_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(test_container, lv_pct(100));
    lv_obj_set_height(test_container, LV_SIZE_CONTENT);  // grow/shrink based on content
                                                         /*
    test_title = lv_label_create(test_container);
    lv_label_set_text(test_title, "FOO BAR BAZ");
    lv_obj_set_flex_grow(test_title, 1);

    test_button = lv_label_create(test_container);
    lv_label_set_text(test_button, "X");
    */
    brightness_slider = lv_slider_create(test_container);
    brightness_label = lv_label_create(test_container);
    lv_label_set_text(brightness_label, pct.c_str());
}

void CreateDarkMode()
{
    enterfunction("CreateDarkMode");
    //
    // Create darkmode container with COLUMN direction
    // TITLE
    // SWITCH
    //
    darkmode_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(darkmode_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_width(darkmode_container, lv_pct(100));
    //lv_obj_set_height(darkmode_container, LV_SIZE_CONTENT); // grow/shrink based on content
    lv_obj_set_flex_grow(darkmode_container, 1);  // fill remaining space

    //lv_obj_set_size(darkmode_container, 200, 150);
    //  lv_obj_align_to(darkmode_container, brightness_container, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    darkmode_title = lv_label_create(darkmode_container);
    lv_label_set_text(darkmode_title, "Dark Mode");

    darkmode_switch = lv_switch_create(darkmode_container);
    lv_obj_set_style_margin_left(darkmode_switch, 15, LV_PART_MAIN);

    //lv_obj_align_to(swdarkmode, slider, LV_ALIGN_BOTTOM_MID, 0, 80);
    lv_obj_add_event_cb(darkmode_switch, swdarkmode_event_handler, LV_EVENT_ALL, NULL);

    // Comment this during testing to see the container border so you know it's what you want.
    lv_obj_set_style_border_width(darkmode_container, 0, 0);

    exitfunction("CreateDarkMode");
}
