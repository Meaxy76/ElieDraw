
#include <stddef.h>
typedef struct {
    int x;
    int y;
    int h;
    int w;
    const char *title;
} ElieDraw_WinT;

typedef struct {
	size_t cur_x;
	size_t cur_y;
} ElieTerm;

void print_title(int x, int y, char const *s);
void print_cmdterm(char const *s, ...);
void print_cmd(char const *s, ...);
void print_str(char const *s, ...);
void DrawStrings(int x, int y, char const *s);
int init_sdl_win(int x, int y, const char *s);
int eliedraw_update();
int Elie_Window(int x, int y, int h, int w, char const *title);
