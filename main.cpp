#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

//SDL2 PIDE ARGC Y ARGV
int main(int argc, char *argv[]){
    //inicializa todo
    SDL_Init(SDL_INIT_EVERYTHING);
    // Crea la ventana, pide el titulo, la posicion x e y (undefined), la largura y altura,
    // sdl_window_allow_high_dpi mayor densidad display
    SDL_Window *window = SDL_CreateWindow("Hello world owo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    //checkea si hay ventana
    if(window = NULL){
        std::cout<<"error"<< SDL_GetError() << std::endl;
        return 1;
    }
    //window event son las acciones en las ventanas, en un while infinito checkea si hubo alguna interaccion con la ventana
    //si el tipo de evento es de cerrar, termina el ciclo
    SDL_Event windowEvent;
    while(true){
        if(SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT){
                break;
            }
        }
    }

    //cierra la ventana
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}