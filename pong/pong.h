#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_render.h>
#include <string.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480

int winw,winh,pad1y,pad2y;

SDL_Window * win=NULL;
SDL_Renderer * renderer=NULL;


typedef struct {
  SDL_Rect rect;
  int xvel,yvel;
}Obj;

Obj newObj(int x,int y,int w,int h,int xvel,int yvel){
  Obj new;
  new.rect.w=w;   //width
  new.rect.h=h;   //height
  new.rect.x=x;   //x position of the left topmost point
  new.rect.y=y;   //y position of the left topmost point
  new.xvel=xvel;  //x velocity
  new.yvel=yvel;  //y velocity
  return new;
}

void server();
int client(int argc, char *argv[]);
