#ifndef LAYOUT_H
#define LAYOUT_H

// Style for horn buttons when pressed
extern lv_style_t style_pr;

// Screens
extern lv_obj_t *screen1;
extern lv_obj_t *screen2;
extern lv_obj_t *settingsscreen;

// These need better names or to be gotten rid of if they aren't needed
extern lv_obj_t *btn1;
extern lv_obj_t *btn2;
extern lv_obj_t *label1;
extern lv_obj_t *label2;
extern lv_obj_t *label3;

// Flex containers
extern lv_obj_t *main_container;
extern lv_obj_t *brightness_container;
extern lv_obj_t *brightness_sliderandlabel_container;
extern lv_obj_t *darkmode_container;
extern lv_obj_t *titlebar_container;

// Brightness slider, printed value, and title
extern lv_obj_t *brightness_slider;
extern lv_obj_t *brightness_label;
extern lv_obj_t *brightness_title;

// Dark mode switch and title
extern lv_obj_t *darkmode_switch;
extern lv_obj_t *darkmode_title;

// Titlebar title and close button
extern lv_obj_t *main_title;
extern lv_obj_t *close_button;
extern lv_obj_t *labelX;
extern lv_obj_t *titlebar_leftside;
extern lv_obj_t *titlebar_rightside;

// Popup label for button testing
extern lv_obj_t *popuplabel;
extern lv_style_t popuplabelstyle;

#define MASK_WIDTH 150
#define MASK_HEIGHT 30

void generate_mask(lv_draw_buf_t *mask, int32_t w, int32_t h, const char *txt);
void CreateMainContainer();
void CreateTitleBar();
void CreateBrightness();
void CreateDarkMode();


/*
    Page 1                  Page 2
    ------                  ------

    /========\/========\    /========\/========\
    |  13,5  || 128,5  |    |  13,5  || 128,5  |
    |    1   ||    2   |    |    7   ||    8   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    | 13,110 || 128,110|    | 13,110 || 128,110|
    |    3   ||    4   |    |    9   ||   10   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    | 13,215 || 128,215|    | 13,215 || 128,215|
    |    5   ||    6   |    |   11   ||   12   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
*/

struct Horn
{
    int id;
    int page;
    const char *name; // I tried String/std::string/char[] and none would work with the image src function
    int xcoord;
    int ycoord;
};

// 0 index not used since customers will count buttons
// starting at 1 and therefore when looking at code
// we won't have to take into account that 1=0, 2=1, etc.
// size 13 because of that
// currently not using anything in button IDs 11 & 12

static std::vector<Horn> darkhorns({
    (struct Horn){},  // array index 0 not used, see above comment
    (struct Horn){ 1, 1, "A:/darkmode/horn01.jpg", 13, 5 },
    (struct Horn){ 2, 1, "A:/darkmode/horn02.jpg", 128, 5 },
    (struct Horn){ 3, 1, "A:/darkmode/horn03.jpg", 13, 110 },
    (struct Horn){ 4, 1, "A:/darkmode/horn04.jpg", 128, 110 },
    (struct Horn){ 5, 1, "A:/darkmode/horn05.jpg", 13, 215 },
    (struct Horn){ 6, 1, "A:/darkmode/horn06.jpg", 128, 215 },
    (struct Horn){ 7, 2, "A:/darkmode/horn07.jpg", 13, 5 },
    (struct Horn){ 8, 2, "A:/darkmode/horn08.jpg", 128, 5 },
    (struct Horn){ 9, 2, "A:/darkmode/horn09.jpg", 13, 110 },
    (struct Horn){ 10, 2, "A:/darkmode/settings.jpg", 128, 110 },
    (struct Horn){},  //(struct Horn){ 11, 2, "A:/horn11.jpg", 13, 215 },
    (struct Horn){}   //(struct Horn){ 12, 2, "A:/horn12.jpg", 128, 215 }
});

static std::vector<Horn> lighthorns({
    (struct Horn){},  // array index 0 not used, see above comment
    (struct Horn){ 1, 1, "A:/lightmode/horn01.jpg", 13, 5 },
    (struct Horn){ 2, 1, "A:/lightmode/horn02.jpg", 128, 5 },
    (struct Horn){ 3, 1, "A:/lightmode/horn03.jpg", 13, 110 },
    (struct Horn){ 4, 1, "A:/lightmode/horn04.jpg", 128, 110 },
    (struct Horn){ 5, 1, "A:/lightmode/horn05.jpg", 13, 215 },
    (struct Horn){ 6, 1, "A:/lightmode/horn06.jpg", 128, 215 },
    (struct Horn){ 7, 2, "A:/lightmode/horn07.jpg", 13, 5 },
    (struct Horn){ 8, 2, "A:/lightmode/horn08.jpg", 128, 5 },
    (struct Horn){ 9, 2, "A:/lightmode/horn09.jpg", 13, 110 },
    (struct Horn){ 10, 2, "A:/lightmode/settings.jpg", 128, 110 },
    (struct Horn){},  //(struct Horn){ 11, 2, "A:/horn11.jpg", 13, 215 },
    (struct Horn){}   //(struct Horn){ 12, 2, "A:/horn12.jpg", 128, 215 }
});

#endif  // LAYOUT_H