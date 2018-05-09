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

void update(Obj * object,int isball,int up){
  if (isball==1){		//Verif obj = balle
    object->rect.x+=object->xvel;
    object->rect.y+=object->yvel;
    if( (object->rect.x>winw-object->rect.w) || (object->rect.x<0) ){				//la balle sort de l'écran
      SDL_Delay(1000);
      object->xvel=-object->xvel;
      object->rect.x=winw/2;
      object->rect.y=winh/2;
    }
    if(object->rect.x>winw-20-object->rect.w && object->rect.y>pad2y && object->rect.y<pad2y+100){	//la balle touche le pad2
      object->xvel=-object->xvel;
      object->rect.x=winw-20-object->rect.w;
    }
    if(object->rect.x<20 && object->rect.y>pad1y && object->rect.y<pad1y+100){			//la balle touche le pad1
      object->xvel=-object->xvel;
      object->rect.x=20;
    }
    if(object->rect.y>winh-object->rect.h){								//La balle touche le bas de l'écran
      object->yvel=-object->yvel;
      object->rect.y=winh-object->rect.h;
    }
    if(object->rect.y<0){
      object->yvel=-object->yvel;
      object->rect.y=0;
    }
  }else {			//Si obj = un des pads
    if(up==1)
      object->rect.y-=object->yvel;
    else
      object->rect.y+=object->yvel;
    if(object->rect.y>winh-object->rect.h){								//le pad touche bas de l'écran
      object->rect.y=winh-object->rect.h;
    }
    if(object->rect.y<0){										//le pad touche le haut de l'écran
      object->rect.y=0;
    }
  }
  return;
}

void initialize(){
  printf("Hello");
  //initialisation SDL
  if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
      printf("SDL error %s\n",SDL_GetError());
    }

  //crée window et renderer
  win = SDL_CreateWindow("Pong",
			 SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			 WINDOW_WIDTH,WINDOW_HEIGHT,0);
  if(win==NULL){
    printf("Window cannot be created %s\n",SDL_GetError());

  }
  SDL_GetWindowSize(win,&winw,&winh);
  renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer==NULL){
    printf("Renderer cannot be created %s\n",SDL_GetError());
  }
}


void loop(int choice[]){
  SDL_Event e;
  while(SDL_PollEvent(&e)!=0){            //gestion des events
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
  printf("hello");
  if(argv[1]){
    if (!strcmp(argv[1], "-server")){
      server();
    }
    if (!strcmp(argv[1], "-client")){
      client(argc, argv);
    }
  }
  initialize();
  //creation des objets
  Obj pad1 = newObj(5,(winh-100)/2,15,100,0,10);
  Obj pad2 = newObj(winw-20,(winh-100)/2,15,100,0,10);
  Obj ball = newObj(winw/2,winh/2,10,10,5,5);
  Obj cline = newObj((winw-2)/2,0,2,winh,0,0);
  int terminate=0,up=0,down=0,w=0,s=0;
  int choice[5] = {0};
  while(!terminate)				//boucle
    {
      loop(choice);
      terminate = choice[0];
      up = choice[1];
      down = choice[2];
      w  = choice[3];
      s  = choice[4];
      pad1y=pad1.rect.y;				//copie position y des pads vers variable globale
      pad2y=pad2.rect.y;
      update(&ball,1,0);				//update position de la balle
      SDL_SetRenderDrawColor(renderer,0,0,0,0);	//mettre la couleur du renderer sur black
      SDL_RenderClear(renderer);			//applique couleur noir

      if(up) update(&pad2,0,1);
      if(down) update(&pad2,0,0);
      if(w) update(&pad1,0,1);
      if(s) update(&pad1,0,0);
      SDL_SetRenderDrawColor(renderer,255,255,255,0); //mettre couleur à blanc
      SDL_RenderFillRect(renderer,&(cline.rect));	//render ligne blanche
      SDL_RenderFillRect(renderer,&(ball.rect));	//render balle
      SDL_RenderFillRect(renderer,&(pad1.rect));	//render pad1
      SDL_RenderFillRect(renderer,&(pad2.rect));	//render pad2
      SDL_RenderPresent(renderer);			//render tous les elements sur l'écran
      SDL_Delay(1000/60);
    }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
