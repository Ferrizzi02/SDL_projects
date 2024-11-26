#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int main(int argc, char *argv[]){

    //crear ventana
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    //event = click, teclado etc
    SDL_Event e;
    //inicializa todo
    SDL_Init(SDL_INIT_EVERYTHING);

    bool running = true;
    //rectangulo
    SDL_Rect r{10,10,250,250}; //crea un rectangulo en 10,10 con  width/height 250
    //crea la ventana
    SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);

    

    while(running){
        //event
        while(SDL_PollEvent(&e)){
            //SALIR DE LA APLICACION
            if(e.type==SDL_QUIT){
                running=false;
            }
           else if(e.type == SDL_KEYDOWN){  //ve que tipo de boton esta presionado
                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        cout<<"Derecha"<<endl;
                        r.x += 50;
                        break;
                }
            } //QUE BOTON SE LIBERO
            else if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        cout<<"eso se sintio muy bien"<<endl;
                        break;
                }
            }else if(e.type == SDL_MOUSEMOTION){
                //pasas 2 int que van a ser populated con la posicion x;y
                //lo que hace este codigo es que mueve la posicion del rectangulo a la posicion del mouse
                SDL_GetMouseState(&r.x, &r.y);


            }
        }
        SDL_SetRenderDrawColor(renderer, 50 ,120, 30, 255); //negro
        SDL_RenderClear(renderer);

        //punto blanco
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }


    return 0;
}