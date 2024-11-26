/*TEXTURE: struct que contiene representacion de pixel dara
basicamente es bueno para dibujar algo que puede que no entre en la pantalla
*/
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow(
                "Textures",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                1000,1000,0);
    auto renderer = SDL_CreateRenderer(window,-1,0);

    //create textures SDL_PIXELFORMAT_RGB8888 formato del pixel
    //SDL_TEXTUREACCESS_TARGET = render target vamos a poder dibujar a esta textura
    auto red_texture = SDL_CreateTexture(
                       renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                       1000,1000);

    auto blue_texture = SDL_CreateTexture(
                       renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                       1000,1000);
    //draw to textures
    //el renderer apunta a la textura, cambia el color y luego desapunta(?)
    SDL_SetRenderTarget(renderer, red_texture);
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderClear(renderer);

    //para el color azul
    SDL_SetRenderTarget(renderer, blue_texture);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);

    //limpiamos el renderer target
    SDL_SetRenderTarget(renderer, nullptr);

    //show textures
    //rendercopy: copia parte de la textura al current rendering target
    SDL_RenderCopy(renderer, red_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    
    SDL_RenderCopy(renderer, blue_texture, nullptr,nullptr);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    return 0;
}