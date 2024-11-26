#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

const int texture_h =2000;
const int texture_w = 2000;
const int screen_h = 500;
const int screen_w = 500;

int main(int argc, char *argv[]){
    //rectangulo origen en la posicion 0,0 con ese widht y  altura
    //determina de que posicion en la textura va a ser el origen del data
    SDL_Rect source{0,0, screen_w/32, screen_h/32,};
    SDL_Rect dest{10,10,screen_w-20, screen_h-20};            //dislocado 10 pix, el -20 es es para compensar cuando se baja y sube
    SDL_Event e;
    auto window = SDL_CreateWindow(
                    "scroll", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    screen_w, screen_h, 0);
    auto renderer = SDL_CreateRenderer(window,-1,0);
    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, texture_w, texture_h);

    //crea vector de puntos con 100000 puntos 
    std::vector<SDL_Point> pv;
    for(int i=0; i<10000; i++){
        SDL_Point p = {rand()%texture_h, rand()%texture_w};
        pv.emplace_back(p);
    }
    auto running = true;
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
            if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    source.y -= 3;
                    break;
                case SDLK_DOWN:
                    source.y +=3;
                    break;
                case SDLK_LEFT:
                    source.x -= 3;
                    break;
                case SDLK_RIGHT:
                    source.x +=3;
                    break;
                case SDLK_1:
                    source.w *=2;
                    source.h *=2;
                    break;
                case SDLK_2:
                    source.w /=2;
                    source.h /=2;
                    break;
                default:
                    break;
                }
            }
        }
        //limpia textura
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 16,13,54,255);
        SDL_RenderClear(renderer);

        //tiggle los puntitos no se si se dice asi 
        std::for_each(pv.begin(), pv.end(), [](auto& item){
            item.x += rand()%3-1;
            item.y +=rand()%3 -1;
        });
        //dibuja los putos color negro
        SDL_SetRenderDrawColor(renderer, 250,220,90,255);
        SDL_RenderDrawPoints(renderer, pv.data(), pv.size());

        //copia seleccion de la textura a la pantalla
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        //el render apunta a la ventana, la textura a donde vamos a dibujar los pixeles
        //imagina el source apuntando a la textura y el dest al renderer, basicamente decimos dame un rectangulo de pixeles del tamanho de source
        //el dest dice donde en la ventana queres mostrar los pizeles
        SDL_RenderCopy(renderer, texture, &source, &dest);  
        SDL_RenderPresent(renderer);

        SDL_Delay(50);
    }

    return 0;
}