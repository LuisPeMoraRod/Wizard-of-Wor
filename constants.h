#ifndef CONSTANTS_H
#define CONSTANTS_H

//images paths
#define GAME_BG_PATH "resources/black_bg.jpeg"
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

#define ENEMY_R0 "resources/enemies/enemy_r0.png"
#define ENEMY_R1 "resources/enemies/enemy_r1.png"
#define ENEMY_R2 "resources/enemies/enemy_r2.png"
#define ENEMY_R3 "resources/enemies/enemy_r3.png"
#define ENEMY_L0 "resources/enemies/enemy_l0.png"
#define ENEMY_L1 "resources/enemies/enemy_l1.png"
#define ENEMY_L2 "resources/enemies/enemy_l2.png"
#define ENEMY_L3 "resources/enemies/enemy_l3.png"
#define ENEMY_U0 "resources/enemies/enemy_u0.png"
#define ENEMY_U1 "resources/enemies/enemy_u1.png"
#define ENEMY_U2 "resources/enemies/enemy_u2.png"
#define ENEMY_U3 "resources/enemies/enemy_u3.png"
#define ENEMY_D0 "resources/enemies/enemy_d0.png"
#define ENEMY_D1 "resources/enemies/enemy_d1.png"
#define ENEMY_D2 "resources/enemies/enemy_d2.png"
#define ENEMY_D3 "resources/enemies/enemy_d3.png"


#define WIN_WIDTH 960 //window frame width
#define WIN_HEIGHT 600 //window frame height
#define MAX_PATH 30
#define DELAY 40

//position Press Key image
#define PK_X 100
#define PK_Y 560
#define PK_WIDTH 400
#define PK_HEIGHT 40

#define PK_BLINK 0.3 //blink time of Press Key image

//blocks
#define B_WIDTH 10
#define B_HEIGHT 10

//bullets
#define BLLT_WIDTH 10
#define BLLT_HEIGHT 4

//initial warrior position
#define WOR_X0 0
#define WOR_Y0 211

//enemies position range
#define X_MIN 70
#define X_MAX 845
#define Y_MIN 20
#define Y_MAX 400

//Doors
#define R_DOOR 940
#define L_DOOR -20

//extra worriors intial positions
#define W_LIVE0_X 72 
#define W_LIVE0_Y 460 

//warrior image dimentions
#define WOR_WIDTH 44
#define WOR_HEIGHT 48

//warrior velocity
#define MOVE 5

//enemies' velocity
#define MOVE_ENM 5

//Bullets' velocity
#define MV_BLLT 5

//Amount of enemies
#define ENEMIES 6

//handle movement effects by alternating sprites
enum sprites_num{
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