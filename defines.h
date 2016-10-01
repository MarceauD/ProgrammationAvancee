#ifndef DEFINES_H
#define DEFINES_H

#define GAME_TITLE "GAME_TITLE"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SPRITE_WIDTH 50
#define SPRITE_HEIGHT 150

#define TOP_HEIGHT 100
#define BOTTOM_HEIGHT 50
#define BACKGROUND_HEIGHT SCREEN_HEIGHT - TOP_HEIGHT
#define BACKGROUND_WIDTH SCREEN_WIDTH

#define DEFAULT_SPRITE_POSITION_X ( SCREEN_WIDTH / 2 ) - SPRITE_WIDTH
#define DEFAULT_SPRITE_POSITION_Y SCREEN_HEIGHT - SPRITE_HEIGHT - BOTTOM_HEIGHT

#define DEFAULT_ENEMY_POSITION_X - 2 * SPRITE_WIDTH
#define DEFAULT_ENEMY_POSITION_Y SCREEN_HEIGHT - SPRITE_HEIGHT


#define DEFAULT_LIFEPOINTS 10
#define DEFAULT_HITDAMAGE 10

#endif //DEFINES_H
