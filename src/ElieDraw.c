#ifdef _WIN32
#include "Include/SDL.h"
#include "Include/SDL_image.h"
#include "Include/SDL_test_log.h"
#include "Include/SDL_ttf.h"
#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "SDL_Base.h"
#include "ElieDraw.h"
#include "test.h"

SDL_Renderer *renderer = NULL;
SDL_Event event;
SDL_Window *window = NULL;

int win_x;
int win_y;

#define WINDOW_WIDTH 1366
#define POSX 10
#define POSY 10


static ElieTerm term = {0, 67};

int eliedraw_update(){
    SDL_RenderPresent(renderer);
}

void draw_rect(int x, int y, int h, int w){
    int i;
    for(i = 40; i < WINDOW_WIDTH - 40; ++i){
        SDL_RenderDrawPoint(renderer, i, 40);
    }
}

void term_puts(char const *s)
{
	while (*s)
	{
		if (*s == '\n')
		{
			term.cur_y = term.cur_y + 15;
			term.cur_x = term.cur_x;
			s++;
		}
	}
}

void draw_pixels(){
	size_t x = 0;
	size_t y = 0;

	for (y = 0; y < TEST_HEIGHT; y++)
	{
		for (x = 0; x < TEST_WIDTH; x++)
		{
			if ((test[TEST_HEIGHT + y] >> x) & 1)
			{
				//draw_pixel(xpos + x, ypos + y, color);
                SDL_RenderDrawPoint(renderer, 5, 5);
			}
		}
	}
}

static void print_chr(size_t xpos, size_t ypos, uint8_t c)
{
	size_t x = 0;
	size_t y = 0;

	for (y = 0; y < FONT_HEIGHT; y++)
	{
		for (x = 0; x < FONT_WIDTH; x++)
		{
			if ((font[(c * FONT_HEIGHT) + y] >> x) & 1)
			{
				//draw_pixel(xpos + x, ypos + y, color);
                SDL_RenderDrawPoint(renderer, xpos + x, ypos + y);
			}
		}
	}
}


void print_str(char const *s, ...)
{
	size_t cur_x = term.cur_x;
	size_t cur_y = term.cur_y;

	while (*s)
	{
		if (*s == '\n')
		{
			cur_y += FONT_HEIGHT;
			cur_x = 0;
		}
		else
		{
			print_chr(cur_x, cur_y, *s);
			cur_x += FONT_WIDTH;
		}

		s++;
	}
	cur_x = 0;
    term_puts("\n");
}


void print_cmd(char const *s, ...)
{
	size_t cur_x = term.cur_x + 22;
	size_t cur_y = 695;

	while (*s)
	{
		if (*s == '\n')
		{
			cur_y += FONT_HEIGHT;
			cur_x = 0;
		}
		else
		{
			print_chr(cur_x, cur_y, *s);
			cur_x += FONT_WIDTH;
		}

		s++;
	}
}


void print_cmdterm(char const *s, ...)
{
	size_t cur_x = term.cur_x + 12;
	size_t cur_y = 695;

	while (*s)
	{
		if (*s == '\n')
		{
			cur_y += FONT_HEIGHT;
			cur_x = 0;
		}
		else
		{
			print_chr(cur_x, cur_y, *s);
			cur_x += FONT_WIDTH;
		}

		s++;
	}
    //term_puts("\n");
}


void print_title(int x, int y, char const *s)
{
	int title_y;
	int title_x;
	int slen;
	int stitle;
	int stitle1;
	//win_x = x - 25;
	win_x = x / 2;
	win_y = y;

	slen = strlen(s);
	printf("Title is = %s\n", s);
	printf("length = %d\n", slen);
	printf("x = %d\n", win_x);
	printf("y = %d\n", win_y);
	stitle = (slen * FONT_HEIGHT) / 2;
	stitle1 = stitle / 2;
	title_y = win_y + 5;
	title_x = win_x - stitle1;
	printf("titlex = %d\n", title_x);
	printf("titless = %d\n", stitle1);



	while (*s)
	{
		if (*s == '\n')
		{
			//cur_y += FONT_HEIGHT;
			title_x = 0;
		}
		else
		{
			print_chr(title_x, title_y, *s);
			title_x += FONT_WIDTH;
		}

		s++;
	}
}

void DrawStrings(int x, int y, char const *s)
{
	int title_y;
	int title_x;
	int slen;
	int stitle;
	int stitle1;
	//win_x = x - 25;
	win_x = x / 2;
	win_y = y;

	slen = strlen(s);
	printf("Title is = %s\n", s);
	printf("length = %d\n", slen);
	printf("x = %d\n", win_x);
	printf("y = %d\n", win_y);
	stitle = (slen * FONT_HEIGHT) / 2;
	stitle1 = stitle / 2;
	title_y = win_y + 5;
	title_x = win_x - stitle1;
	printf("titlex = %d\n", title_x);
	printf("titless = %d\n", stitle1);



	while (*s)
	{
		if (*s == '\n')
		{
			//cur_y += FONT_HEIGHT;
			title_x = 0;
		}
		else
		{
			print_chr(title_x, title_y, *s);
			title_x += FONT_WIDTH;
		}

		s++;
	}
}

int Create_ElieWindow(int x, int y, int h, int w, const char *title){

	term.cur_x = x + 12;
	term.cur_y = y + 27;
	win_x = w + x;
	win_y = y;
	SDL_SetRenderDrawColor(renderer, 160, 159, 191, 255); // Background color
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Border window color

    SDL_Rect r1; // Main window frame
    r1.x = x;
    r1.y = y;
    r1.w = w;
    r1.h = h;
    SDL_RenderDrawRect(renderer, &r1);   


    SDL_SetRenderDrawColor( renderer, 204, 204, 204, 255 ); // Window frame color

    SDL_RenderFillRect( renderer, &r1 ); // fill the window

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 ); // white border effect


    SDL_Rect r11; // white border rect
    r11.x = x + 1;
    r11.y = x + 1;
    r11.w = w - 2;
    r11.h = h - 1;
    SDL_RenderDrawRect(renderer, &r11);   


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Title

    print_title(win_x,win_y, title); // Print the title centered


    SDL_SetRenderDrawColor( renderer, 230, 230, 230, 255 ); // Content box of the window

    SDL_Rect re1; // content
    re1.x = x + 8;
    re1.y = y + 24;
    re1.w = w - 16;
    re1.h = h - 33;
    SDL_RenderDrawRect(renderer, &re1);
    SDL_RenderFillRect( renderer, &re1 );

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderDrawRect(renderer, &r);   

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);

    SDL_Rect re2; // border effect
    re2.x = x + 7;
    re2.y = y + 23;
    re2.w = w - 14;
    re2.h = h - 32;
    SDL_RenderDrawRect(renderer, &re2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Rect re; // border
    re.x = x + 8;
    re.y = y + 24;
    re.w = w - 16;
    re.h = h - 33;
    SDL_RenderDrawRect(renderer, &re);
	draw_pixels();

}

int init_sdl_win(int x, int y, const char *s){

    SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(s,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,x,y,SDL_WINDOW_OPENGL);
    IMG_Init(IMG_INIT_PNG);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

int Elie_Window(int x, int y, int h, int w, char const *title){
	Create_ElieWindow(x, y, h, w, title);
	eliedraw_update();
}
	
