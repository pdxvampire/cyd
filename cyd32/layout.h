#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>

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
    char name[50];
    int xcoord;
    int ycoord;
};


// 0 index not used since customers will count buttons
// starting at 1 and therefore when looking at code
// we won't have to take into account that 1=0, 2=1, etc.
// size 13 because of that
// currently not using anything in button IDs 11 & 12

static std::vector<Horn> horns({
    (struct Horn){},  // array index 0 not used, see above comment
    (struct Horn){ 1, 1, "A:/horn01.jpg", 13, 5 },
    (struct Horn){ 2, 1, "A:/horn02.jpg", 128, 5 },
    (struct Horn){ 3, 1, "A:/horn03.jpg", 13, 110 },
    (struct Horn){ 4, 1, "A:/horn04.jpg", 128, 110 },
    (struct Horn){ 5, 1, "A:/horn05.jpg", 13, 215 },
    (struct Horn){ 6, 1, "A:/horn06.jpg", 128, 215 },
    (struct Horn){ 7, 2, "A:/horn07.jpg", 13, 5 },
    (struct Horn){ 8, 2, "A:/horn08.jpg", 128, 5 },
    (struct Horn){ 9, 2, "A:/horn09.jpg", 13, 110 },
    (struct Horn){ 10, 2, "A:/settings.jpg", 128, 110 },
    (struct Horn){},  //(struct Horn){ 11, 2, "A:/horn11.jpg", 13, 215 },
    (struct Horn){}   //(struct Horn){ 12, 2, "A:/horn12.jpg", 128, 215 }
});

#endif  // LAYOUT_H