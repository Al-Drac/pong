/*
** main.c for main in /home/samuel/tmp/pong/pong
**
** Made by THOMAS Samuel
** Login   <thomas_s@etna-alternance.net>
**
** Started on  Wed May  9 09:35:25 2018 THOMAS Samuel
** Last update Wed May  9 09:42:10 2018 THOMAS Samuel
*/

#include "pong.h"

void status_up(t_item * obj,int ball,int up, t_item *pad1, t_item *pad2){
if (ball==1){		//Verif obj = balle
  obj->rectangle.x+=obj->vector_x;
  obj->rectangle.y+=obj->vector_y;
  if( (obj->rectangle.x>window_Width-obj->rectangle.w) || (obj->rectangle.x<0) ){				//la balle sort de l'écran
    if (obj->rectangle.x>window_Width-obj->rectangle.w) {
        pad1->score = pad1->score + 1;
    }else {
        pad2->score = pad2->score + 1;
    }
    obj->vector_x=-obj->vector_x;
    obj->rectangle.x=window_Width/2;
    obj->rectangle.y=window_height/2;
    SDL_Delay(1000);
  }
  if(obj->rectangle.x>window_Width-20-obj->rectangle.w && obj->rectangle.y>paddle_2 && obj->rectangle.y<paddle_2+100){	//la balle touche le pad2
    obj->vector_x=-obj->vector_x;
    obj->rectangle.x=window_Width-20-obj->rectangle.w;
  }
  if(obj->rectangle.x<20 && obj->rectangle.y>paddle_1 && obj->rectangle.y<paddle_1+100){			//la balle touche le pad1
    obj->vector_x=-obj->vector_x;
    obj->rectangle.x=20;
  }
  if(obj->rectangle.y>window_height-obj->rectangle.h){								//La balle touche le bas de l'écran
    obj->vector_y=-obj->vector_y;
    obj->rectangle.y=window_height-obj->rectangle.h;
  }
  if(obj->rectangle.y<0){
    obj->vector_y=-obj->vector_y;
    obj->rectangle.y=0;
  }
}else {			//Si obj = un des pads
  if(up==1)
    obj->rectangle.y-=obj->vector_y;
  else
    obj->rectangle.y+=obj->vector_y;
  if(obj->rectangle.y>window_height-obj->rectangle.h){								//le pad touche bas de l'écran
    obj->rectangle.y=window_height-obj->rectangle.h;
  }
  if(obj->rectangle.y<0){										//le pad touche le haut de l'écran
    obj->rectangle.y=0;
  }
}
return;
}

void init_sdl(){
  printf("------------- initialisation SDL --------------\n");
  if(SDL_Init(SDL_INIT_VIDEO)!=0)
      printf("SDL error %s\n",SDL_GetError());
  window = SDL_CreateWindow("Pong",
			 SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			 WINDOW_WIDTH,WINDOW_HEIGHT,0);
  if(window==NULL)
    printf("Window cannot be created %s\n",SDL_GetError());
  SDL_GetWindowSize(window,&window_Width,&window_height);
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer==NULL)
    printf("Renderer cannot be created %s\n",SDL_GetError());
}


void loop(int choice[]){
  SDL_Event e;
  while(SDL_PollEvent(&e)!=0){
    switch (e.type){
      case SDL_QUIT:
        choice[0] = 1;
        continue;
        break;
      case SDL_KEYDOWN:
        switch(e.key.keysym.sym){
          case SDLK_ESCAPE:
          	choice[0] = 1;
          	break;
          case SDLK_UP:
	         choice[1] = 1;
	         break;
          case SDLK_DOWN:
	         choice[2] = 1;
	         break;
          case SDLK_w:
	         choice[3] = 1;
	          break;
          case SDLK_s:
	         choice[4] = 1;
	         break;
      }
        break;
      case SDL_KEYUP:
        switch(e.key.keysym.sym){
          case SDLK_UP:
          	choice[1] = 0;
          	break;
          case SDLK_DOWN:
	         choice[2] = 0;
	          break;
          case SDLK_w:
	         choice[3] = 0;
	         break;
          case SDLK_s:
	         choice[4] = 0;
	         break;
      }
        break;
    }
  }
}

int main(int argc,char *argv[]){
  t_item pad1;
  t_item pad2;
  t_item ball;
  t_item cline;
  int test;

  test = 0;

  printf("------------- Main --------------\n");

  if(argv[1]){
    if (!strcmp(argv[1], "-server")){
      server();
    }
    if (!strcmp(argv[1], "-client")){
     test = client(argc, argv);
    }
  }
  if (test) {
      return 1;
  }
  init_sdl();
  //creation des objets
  pad1  = newObj("pad1",0,5,(window_height-100)/2,15,100,0,10);
  pad2  = newObj("pad2",0,window_Width-20,(window_height-100)/2,15,100,0,10);
  ball  = newObj("ball",0,window_Width/2,window_height/2,10,10,5,5);
  cline = newObj("line",0,(window_Width-2)/2,0,2,window_height,0,0);

  int terminate=0;
  int up=0;
  int down=0;
  int w=0;
  int s=0;

  int choice[5] = {0};
  while(!terminate)				//boucle
    {
      loop(choice);

      terminate     = choice[0];
      up            = choice[1];
      down          = choice[2];
      w             = choice[3];
      s             = choice[4];

      paddle_1=pad1.rectangle.y;				//copie position y des pads vers variable globale
      paddle_2=pad2.rectangle.y;
      status_up(&ball,1,0, &pad1,&pad2);                //update position de la balle
      SDL_SetRenderDrawColor(renderer,0,0,0,0);    //mettre la couleur du renderer sur black
      SDL_RenderClear(renderer);            //applique couleur noir

      if(up)
        status_up(&pad2,0,1, &pad1,&pad2);
      if(down)
        status_up(&pad2,0,0, &pad1,&pad2);
      if(w)
        status_up(&pad1,0,1, &pad1,&pad2);
      if(s)
        status_up(&pad1,0,0, &pad1,&pad2);
      SDL_SetRenderDrawColor(renderer,255,255,255,0); //mettre couleur à blanc
      SDL_RenderFillRect(renderer,&(cline.rectangle));	//render ligne blanche
      SDL_RenderFillRect(renderer,&(ball.rectangle));	//render balle
      SDL_RenderFillRect(renderer,&(pad1.rectangle));	//render pad1
      SDL_RenderFillRect(renderer,&(pad2.rectangle));	//render pad2

      SDL_RenderPresent(renderer);			//render tous les elements sur l'écran
      SDL_Delay(1000/60);
    }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return (0);
}
