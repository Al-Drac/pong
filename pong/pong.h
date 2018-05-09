/*
** pong.h for pong in /home/samuel/tmp/pong/pong
**
** Made by THOMAS Samuel
** Login   <thomas_s@etna-alternance.net>
**
** Started on  Wed May  9 09:47:58 2018 THOMAS Samuel
** Last update Wed May  9 10:11:36 2018 THOMAS Samuel
*/

#ifndef PONG_H_
# define PONG_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480

int window_Width;
int window_height;
int paddle_1;
int paddle_2;

SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;


typedef struct s_item{
  SDL_Rect  rectangle;
  int       vector_x;
  int       vector_y;
  int       score;
  char*     name;
}t_item;

t_item newObj(char* std, int score,int x,int y,int w,int h,int vector_x,int vector_y){

  t_item new;

  new.name = std;
  new.score = score;
  new.rectangle.w=w;        //width
  new.rectangle.h=h;        //height
  new.rectangle.x=x;        //x position of the left topmost point
  new.rectangle.y=y;        //y position of the left topmost point
  new.vector_x=vector_x;    //x velocity
  new.vector_y=vector_y;    //y velocity

  return new;
}



void  server();
int   client(int argc, char *argv[]);
void  init_sdl();
void  loop(int choice[]);
int   main(int argc,char *argv[]);
void  status_up(t_item *obj,int ball,int u,t_item *pad1,t_item *pad2);

#endif /* !PONG_H_ */
