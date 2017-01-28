/*
	game.c 
	Proiectarea cu microprocesoare 2016
*/

#include "game.h"

// change to 0 for circles
#define USE_BRICK 1

#define min(x, y) ((x) < (y) ? (x) : (y))
#define pow2(x) ((x) * (x))

void draw_brick_rectangle(uint8_t x1, uint8_t y1, uint8_t length, uint8_t height, uint8_t ink)
{
	int x2, y2;
	x2 = x1 + length;
	y2 = y1 + height;
	// top margin
	draw_line(x1, y1, x2, y1, ink);
	// left margin
	draw_line(x1, y1, x1, y2, ink);
	// right margin
	draw_line(x2, y1, x2, y2, ink);
	// bottom margin
	draw_line(x1, y2, x2, y2, ink);
}

inline void DrawPixel(uint8_t x, uint8_t y, uint8_t ink) 
{
	if (ink)
		T6963cSetPixelXY(x, y);
	else
		T6963cResetPixelXY(x, y);
}

void draw_brick_circle(uint8_t x1, uint8_t y1, uint8_t length, uint8_t height, uint8_t ink)
{
	(void)x1; (void)y1;
	(void)length; (void)height;
	(void)ink;
	//TODO 6
	// draw a circular brick with radius min(length, height)/2
}

void draw_brick(uint8_t x1, uint8_t y1, uint8_t length, uint8_t height, uint8_t ink)
{
#if USE_BRICK
	draw_brick_rectangle(x1, y1, length, height, ink);
#else
	draw_brick_circle(x1, y1, length, height, ink);
#endif
}

void draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t ink) {
	//TODO 4
	// draw a vertical or a horizontal line from (x1, y1) to (x2, y2)
	// ink specifies if the pixels are set or reset
	//
	int i,j;
	if (y1 == y2)
		for (i=x1; i<x2; i++)
			if (ink ==1)
				T6963cSetPixelXY(i, y1);
			else
				T6963cResetPixelXY(i, y1);
	else if (x1 == x2)
		for (j=y1; j<y2; j++)
			if (ink == 1)
				T6963cSetPixelXY(x1, j);
			else
				T6963cResetPixelXY(x1, j);
	}
			

void draw_pad(uint8_t x, uint8_t y, uint8_t ink)
{
	draw_line(x, y, x+PAD_LENGTH, y,ink);
	draw_line(x+1, y-1, x+PAD_LENGTH-2, y-1,ink);
	draw_line(x+1, y+1, x+PAD_LENGTH-2, y+1,ink);
}

void draw_ball(uint8_t x, uint8_t y, uint8_t ink)
{
	if(ink==1)
	{
		T6963cSetPixelXY(x, y); 
		T6963cSetPixelXY(x+1, y); 
		T6963cSetPixelXY(x+2, y); 
		T6963cSetPixelXY(x-1, y); 
		T6963cSetPixelXY(x-2, y); 

		T6963cSetPixelXY(x, y+1); 
		T6963cSetPixelXY(x+1, y+1); 
		T6963cSetPixelXY(x+2, y+1); 
		T6963cSetPixelXY(x-1, y+1); 
		T6963cSetPixelXY(x-2, y+1); 

		T6963cSetPixelXY(x, y-1); 
		T6963cSetPixelXY(x+1, y-1); 
		T6963cSetPixelXY(x+2, y-1); 
		T6963cSetPixelXY(x-1, y-1); 
		T6963cSetPixelXY(x-2, y-1); 

		T6963cSetPixelXY(x, y-2); 
		T6963cSetPixelXY(x+1, y-2); 
		T6963cSetPixelXY(x-1, y-2); 

		T6963cSetPixelXY(x, y+2); 
		T6963cSetPixelXY(x+1, y+2); 
		T6963cSetPixelXY(x-1, y+2); 
	}
	else
	{
		T6963cResetPixelXY(x, y); 
		T6963cResetPixelXY(x+1, y); 
		T6963cResetPixelXY(x+2, y); 
		T6963cResetPixelXY(x-1, y); 
		T6963cResetPixelXY(x-2, y); 

		T6963cResetPixelXY(x, y+1); 
		T6963cResetPixelXY(x+1, y+1); 
		T6963cResetPixelXY(x+2, y+1); 
		T6963cResetPixelXY(x-1, y+1); 
		T6963cResetPixelXY(x-2, y+1); 

		T6963cResetPixelXY(x, y-1); 
		T6963cResetPixelXY(x+1, y-1); 
		T6963cResetPixelXY(x+2, y-1); 
		T6963cResetPixelXY(x-1, y-1); 
		T6963cResetPixelXY(x-2, y-1); 

		T6963cResetPixelXY(x, y-2); 
		T6963cResetPixelXY(x+1, y-2); 
		T6963cResetPixelXY(x-1, y-2); 

		T6963cResetPixelXY(x, y+2); 
		T6963cResetPixelXY(x+1, y+2); 
		T6963cResetPixelXY(x-1, y+2); 
	}

}

int brick_length, brick_height;
int bricks[MAX_NUM_BRICKS][5];
int num_bricks, remaining_bricks;
int max_brick_ypos;

float xspeed=0, yspeed=0;		// Ball speed
float x, y = 0; 
int win = 0;
float x_pad, y_pad;


void init_game(void)
{
	draw_margins();
	draw_bricks();

	win = 0;
	x = BALL_INITX;
	y = BALL_INITY;

	xspeed = BALL_YSPEED;
	yspeed = BALL_XSPEED;

	x_pad = PAD_INITX;
	y_pad = PAD_INITY;
}

void draw_bricks(void)
{
	uint8_t initial_xpos, initial_ypos, space, xpos, ypos;
	space = 2;
	initial_xpos = X1_LIMIT + space;
	initial_ypos = Y1_LIMIT + space;
	brick_length = 22;
	brick_height = 15;
	
	num_bricks = 0;
	
	int i = 0;
	for(i = 0; i < 4; i++)
	{
		xpos = initial_xpos + i*1;
		ypos = initial_ypos + i*brick_height+i*space;
		do{
			draw_brick(xpos, ypos, brick_length, brick_height,1);
			bricks[num_bricks][0] = xpos;
			bricks[num_bricks][1] = ypos;
			bricks[num_bricks][2] = xpos+brick_length;
            bricks[num_bricks][3] = ypos+brick_height;
			bricks[num_bricks][4] = 4;
			xpos += brick_length + space;
			num_bricks++;
			
		}while(xpos + brick_length < X2_LIMIT - 2);
		
	}
	
	max_brick_ypos = ypos + brick_height;
	remaining_bricks = num_bricks;
}

int check_hit_brick(int xpos, int ypos, int brick[])
{
	return (ypos +3 >= brick[1]) && (ypos - 3 <= brick[3]) &&
			(xpos +3 >= brick[0]) && (xpos - 3 <= brick[2]);
}

int check_hit_circle(int xpos, int ypos, int brick[])
{
	(void)xpos; (void)ypos;
	(void)brick;
	//TODO 6
	// hit condition to reflect the new brick shape
	return 0;
}

int check_bricks(int xpos, int ypos) 
{
	uint8_t hit = 0;
	int i = 0;
	
	/* first half of the board */
	if (ypos > max_brick_ypos+2) 
		return 1;
	 
	/* check every brick */
	for (i = 0; i < num_bricks; i++)
	{
		/* if number of shots left are > 0 and ball is inside the margins of the brick */
		if ( bricks[i][4] &&
#if USE_BRICK
			check_hit_brick(xpos, ypos, bricks[i])
#else
			check_hit_circle(xpos, ypos, bricks[i])
#endif
			)
		{		
			/* decrease number of shots left */
			if (!--bricks[i][4])
			{
				remaining_bricks--;
				/* erase brick */
				draw_brick(bricks[i][0], bricks[i][1], brick_length, brick_height, 0);				
			}			
			else hit = 1;
		}
	}
	return 1-hit;
}
int check_pad(float xpos, float ypos, float x_pad, float y_pad)
{
	(void)y_pad;

	if (!((xpos >= x_pad) && (xpos <= x_pad + PAD_LENGTH)))
		return -1;
	if (ypos > Y2_LIMIT-2 || ypos < Y2_LIMIT-3)
		return -1;

	return xpos - x_pad;
}
int check_margins(int xpos, int ypos)
{
	if (xpos <= X1_LIMIT+2)
		return HIT_HORIZ;
	if (xpos >= X2_LIMIT-2)
		return HIT_HORIZ;
	if (ypos <= Y1_LIMIT+2)
		return HIT_VERT;
	if(ypos >= Y2_LIMIT-2)
		return HIT_LOST;
	return 0;
}

void  draw_margins()
{
	// top margin
	draw_line(X1_LIMIT, Y1_LIMIT, X2_LIMIT, Y1_LIMIT, 1);
	// left margin
	draw_line(X1_LIMIT, Y1_LIMIT, X1_LIMIT, Y2_LIMIT, 1);
	// right margin
	draw_line(X2_LIMIT, Y1_LIMIT, X2_LIMIT, Y2_LIMIT, 1);
}
