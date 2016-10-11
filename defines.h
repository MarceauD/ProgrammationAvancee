#ifndef DEFINES_H
#define DEFINES_H

#define GAME_TITLE "GAME_TITLE"

//GLOBAL SETTINGS
    #define SCREEN_WIDTH 800
    #define SCREEN_HEIGHT 480

    #define TOP_HEIGHT 100
    #define BOTTOM_HEIGHT 75
    #define BACKGROUND_HEIGHT SCREEN_HEIGHT - TOP_HEIGHT
    #define BACKGROUND_WIDTH 1600

    #define TIME_BTW_ANIMATIONS 200

//SPRITE RELATED
    #define SPRITE_WIDTH 30
    #define SPRITE_HEIGHT 65

    #define DEFAULT_SPRITE_POSITION_X ( SCREEN_WIDTH / 2 ) - SPRITE_WIDTH
    #define DEFAULT_SPRITE_POSITION_Y SCREEN_HEIGHT - SPRITE_HEIGHT - BOTTOM_HEIGHT
    #define DEFAULT_SPRITE_HEIGHT 100
    #define DEFAULT_SPRITE_WIDTH 30

    #define DEFAULT_ENEMY_POSITION_X - 2 * SPRITE_WIDTH
    #define DEFAULT_ENEMY_POSITION_Y SCREEN_HEIGHT - SPRITE_HEIGHT

//LIMITS AND DEFAUTLS POSITION OF SOURCES RECT FOR THE SPRITES AND IMAGES
    #define SOURCE_POS_PLAYER_KNELT_LEFT_X 108
    #define SOURCE_POS_PLAYER_KNELT_RIGHT_X 0
    #define SOURCE_POS_PLAYER_KNELT_Y SPRITE_HEIGHT * 2 + 10

    #define SOURCE_POS_PLAYER_STANDING_RIGHT_X 0
    #define SOURCE_POS_PLAYER_STANDING_RIGHT_Y 0
    #define SOURCE_POS_PLAYER_STANDING_RIGHT_ACC SPRITE_WIDTH + 2
    #define SOURCE_POS_PLAYER_STANDING_RIGHT_LIMIT_X SPRITE_WIDTH * 4 + 2
    #define SOURCE_POS_BG_RIGHT_LIMIT_X BACKGROUND_WIDTH - SCREEN_WIDTH
    #define RECT_POS_PLAYER_RIGHT_LIMIT_X SCREEN_WIDTH - SPRITE_WIDTH

    #define SOURCE_POS_PLAYER_STANDING_LEFT_X 3 * SPRITE_WIDTH + 5
    #define SOURCE_POS_PLAYER_STANDING_LEFT_Y SPRITE_HEIGHT + 7
    #define SOURCE_POS_PLAYER_STANDING_LEFT_ACC - SPRITE_WIDTH
    #define SOURCE_POS_PLAYER_STANDING_LEFT_LIMIT_X 0
    #define SOURCE_POS_BG_LEFT_LIMIT_X 0
    #define RECT_POS_PLAYER_LEFT_LIMIT_X 0

    #define SOURCE_POS_PLAYER_JUMP_RIGHT_X 1
    #define SOURCE_POS_PLAYER_JUMP_RIGHT_Y 215
    #define SOURCE_POS_PLAYER_JUMP_RIGHT_X_ACC 30
    #define SOURCE_POS_PLAYER_JUMP_RIGHT_X_LIMIT 5 * SPRITE_WIDTH

    #define SOURCE_POS_PLAYER_JUMP_LEFT_X 167
    #define SOURCE_POS_PLAYER_JUMP_LEFT_Y 283
    #define SOURCE_POS_PLAYER_JUMP_LEFT_X_ACC - 30
    #define SOURCE_POS_PLAYER_JUMP_LEFT_X_LIMIT 40

    #define JUMP_HEIGHT 8

//DEFAULTS STRUCTURES SETTINGS
    #define DEFAULT_LIFEPOINTS 10
    #define DEFAULT_HITDAMAGE 10

#endif //DEFINES_H
