

#include <stdio.h>
#include <string.h>


#include "ElieDraw.h"

int quit;
int run;

int main(){
    init_sdl_win(800, 600, "ElieDraw Test");
    Elie_Window(10, 10, 100, 200, "Window test");
    print_str("Hello World!");
    eliedraw_update();
    //Elie_Window(600, 25, 300, 500, "I'm a ElieDraw window2");
    while(1){ // bad i know
        
    }

}