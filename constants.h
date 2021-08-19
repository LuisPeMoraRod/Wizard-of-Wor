#ifndef CONSTANTS_H
#define CONSTANTS_H

//images paths
#define GAME_BG_PATH "resources/game_bg.png"
#define TITTLE_WIN_PATH "resources/tittle.png"
#define PRESS_KEY "resources/press_key.png"

#define WARRIOR_R0 "resources/warrior/warrior_r0.png"
#define WARRIOR_R1 "resources/warrior/warrior_r1.png"
#define WARRIOR_R2 "resources/warrior/warrior_r2.png"
#define WARRIOR_R3 "resources/warrior/warrior_r3.png"
#define WARRIOR_L0 "resources/warrior/warrior_l0.png"
#define WARRIOR_L1 "resources/warrior/warrior_l1.png"
#define WARRIOR_L2 "resources/warrior/warrior_l2.png"
#define WARRIOR_L3 "resources/warrior/warrior_l3.png"
#define WARRIOR_U0 "resources/warrior/warrior_u0.png"
#define WARRIOR_U1 "resources/warrior/warrior_u1.png"
#define WARRIOR_U2 "resources/warrior/warrior_u2.png"
#define WARRIOR_U3 "resources/warrior/warrior_u3.png"
#define WARRIOR_D0 "resources/warrior/warrior_d0.png"
#define WARRIOR_D1 "resources/warrior/warrior_d1.png"
#define WARRIOR_D2 "resources/warrior/warrior_d2.png"
#define WARRIOR_D3 "resources/warrior/warrior_d3.png"

#define WIN_WIDTH 960 //window frame width
#define WIN_HEIGHT 600 //window frame height
#define MAX_PATH 30
#define DELAY 10

//position Press Key image
#define PK_X 100
#define PK_Y 560
#define PK_WIDTH 400
#define PK_HEIGHT 40

#define PK_BLINK 0.3 //blink time of Press Key image

//blocks
#define B_WIDTH 10
#define B_HEIGHT 10

//initial warrior position
#define WOR_X0 0
#define WOR_Y0 211

//extra worriors intial positions
#define W_LIVE0_X 72 
#define W_LIVE0_Y 460 

//warrior image dimentions
#define WOR_WIDTH 42
#define WOR_HEIGHT 48
#define MOVE 5

//handle movement effects by alternating sprites
enum WOR_Sprites{
    RIGHT_0, 
    RIGHT_1, 
    RIGHT_2,
    RIGHT_3,
    LEFT_0,
    LEFT_1, 
    LEFT_2,
    LEFT_3,
    UP_0,
    UP_1,
    UP_2,
    UP_3,
    DOWN_0,
    DOWN_1,
    DOWN_2,
    DOWN_3
};

enum direction{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

#endif //CONSTANTS_H