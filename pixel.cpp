#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr; 

    //inicializa video y crea la ventana
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640*3, 480*3, 0, &window, &renderer); //*4 = high dpi screen
    SDL_RenderSetScale(renderer, 3, 3);

    //color negro
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    //limpia el render
    SDL_RenderClear(renderer);
    //color blanco
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    //dibuja el punto
    SDL_RenderDrawPoint(renderer, 320, 240);
    //muestra
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

    return 0;
}