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
//#include <SDL2/SDL_ttf.h>
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
          case SDLK_s:
	         choice[3] = 1;
	          break;
          case SDLK_w:
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
          case SDLK_s:
	         choice[3] = 0;
	         break;
          case SDLK_w:
	         choice[4] = 0;
	         break;
      }
        break;
    }
  }
}


void menu()
{
  //int counter = 0;
  SDL_Event event;
  do
    {
      printf("menu");

      SDL_SetRenderDrawColor(renderer,0,0,0,0);  
      SDL_RenderClear(renderer);


      /*
      TTF_Init();
      
      
      TTF_Font* Sans = TTF_OpenFont("arial.ttf", 24); //this opens a font style and sets a size
      
      SDL_Color White = {255, 255, 255, 120};
      
      
      

	
      SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
      
      SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
      
      SDL_Rect Message_rect; //create a rect
      Message_rect.x = 0;  //controls the rect's x coordinate
      Message_rect.y = 0; // controls the rect's y coordinte
      Message_rect.w = 100; // controls the width of the rect
      Message_rect.h = 100; // controls the height of the rect

      //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

      //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

      SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if yu don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
           

      TTF_CloseFont(Sans);
      TTF_Quit();
      SDL_FreeSurface(surfaceMessage);

      */

      
      SDL_RenderPresent(renderer);

      SDL_WaitEvent(&event);
      if(event.type == SDL_KEYDOWN)	
	{

	  
	  if(event.key.keysym.scancode == SDL_SCANCODE_UP)
	    {
	      printf("GO SERVER");
	      menuOp = 1;
	      break;
	    }
	  else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN)
	    {
	      printf("GO CLIENT");
	      menuOp = 2;
	      break;
	    }
	}
    }while(event.type != SDL_QUIT);

  
}




int main(int argc,char *argv[]){
  t_item pad1;
  t_item pad2;
  t_item ball;
  t_item cline;

  printf("------------- Main --------------\n");
  
  init_sdl();
  menu();

  if (menuOp == 1){
    server();
  }
  if (menuOp == 2){
    client(argc, argv);
  }
  
  //creation des objets
  pad1  = newObj("pad1",0,5,(window_height-100)/2,15,100,0,10);
  pad2  = newObj("pad2",0,window_Width-20,(window_height-100)/2,15,100,0,10);
  ball  = newObj("ball",0,window_Width/2,window_height/2,10,10,5,5);
  cline = newObj("line",0,(window_Width-2)/2,0,2,window_height,0,0);

  int terminate=0;
  int up=0;
  int down=0;
  int s=0;
  int w=0;

  int choice[5] = {0};
  while(!terminate)				//boucle
    {
      loop(choice);

      terminate     = choice[0];
      up            = choice[1];
      down          = choice[2];
      s             = choice[3];
      w             = choice[4];

      paddle_1=pad1.rectangle.y;				//copie position y des pads vers variable globale
      paddle_2=pad2.rectangle.y;
      status_up(&ball,1,0, &pad1,&pad2);                //update position de la balle
      SDL_SetRenderDrawColor(renderer,0,0,0,0);    //mettre la couleur du renderer sur black
      SDL_RenderClear(renderer);            //applique couleur noir

      if(up)
        status_up(&pad2,0,1, &pad1,&pad2);
      if(down)
        status_up(&pad2,0,0, &pad1,&pad2);
      if(s)
        status_up(&pad1,0,1, &pad1,&pad2);
      if(w)
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
