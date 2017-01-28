/*
	game.h
	Proiectarea cu microprocesoare 2013
*/

#include <avr/io.h>
#include "T6963c.h"

#ifndef GAME_H_
#define GAME_H_


#define MAX_NUM_BRICKS 25

#define X1_LIMIT 89
#define X2_LIMIT 239
#define Y1_LIMIT 0
#define Y2_LIMIT 126

#define PAD_LENGTH 32

#define PAD_INITX (X1_LIMIT + (X2_LIMIT - X1_LIMIT - PAD_LENGTH) / 2)
#define PAD_INITY (Y2_LIMIT)

#define BALL_XSPEED 1
#define BALL_YSPEED 1

#define BALL_INITX (PAD_INITX + PAD_LENGTH / 2 - 30)
#define BALL_INITY (PAD_INITY - 30)

#define HIT_VERT 1
#define HIT_HORIZ 2
#define HIT_LOST 3


extern int brick_length, brick_height;
extern int bricks[MAX_NUM_BRICKS][5];
extern int num_bricks, remaining_bricks;
extern int max_brick_ypos;

extern float xspeed, yspeed;		// Ball speed
extern float x_pad, y_pad;
extern float x, y; 
extern int win;



void draw_bricks(void);
void draw_brick(uint8_t , uint8_t , uint8_t , uint8_t , uint8_t );
void draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t ink);
void draw_ball(uint8_t x, uint8_t y, uint8_t ink);
void draw_pad(uint8_t x, uint8_t y, uint8_t ink);
void draw_margins(void);

void init_game(void);

int check_bricks(int xpos, int ypos);
int check_pad(float xpos, float ypos, float x_pad, float y_pad);
int check_margins(int xpos, int ypos);

#endif
