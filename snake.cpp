#include <SDL2/SDL.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para inicializar rand()
#include <SDL2/SDL_test_font.h>
#include <string>

int main(int argc, char* argv[]) {

    int contador=0;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error inicializando SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    if (!window || !renderer) {
        std::cerr << "Error creando ventana o renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Event e;
    enum direction { UP, DOWN, LEFT, RIGHT, PAUSE };
    bool running = true;
    int dir = 0;

    // Cabeza de la serpiente
    SDL_Rect head{500, 500, 10, 10};

    // Cuerpo de la serpiente
    std::deque<SDL_Rect> rq;
    int size = 1;

    // Manzana activa
    SDL_Rect apple;
    srand(static_cast<unsigned int>(time(nullptr)));  // Inicializa rand()
    apple.x = (rand() % 69+1) * 10;
    apple.y = (rand() % 69+1) * 10;
    apple.w = 10;
    apple.h = 10;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP: dir = UP; break;
                    case SDLK_DOWN: dir = DOWN; break;
                    case SDLK_LEFT: dir = LEFT; break;
                    case SDLK_RIGHT: dir = RIGHT; break;
                    case SDLK_SPACE: dir = PAUSE; break;
                    default: break;
                }
            }
        }

        // Mover
        switch (dir) {
            case DOWN: head.y += 10; break;
            case UP: head.y -= 10; break;
            case LEFT: head.x -= 10; break;
            case RIGHT: head.x += 10; break;
            case PAUSE: break;
        }

        // Colisión con la manzana
        if (head.x == apple.x && head.y == apple.y) {
            size += 10;  // Crece la serpiente
            apple.x = (rand() % 69+1) * 10;  // Genera nueva posición para la manzana
            apple.y = (rand() % 69+1) * 10;
            contador++;
        }
     

        // Colisión consigo mismo
        std::for_each(rq.begin(), rq.end(), [&](SDL_Rect& snake_segment) {
            if (head.x == snake_segment.x && head.y == snake_segment.y) {
                size = 1;  // Reinicia la longitud
                contador =0;
            }
        });

        // Nueva cabeza
        rq.push_front(head);
        while (rq.size() > size) {
            rq.pop_back();
        }

        // Limpiar ventana
        SDL_SetRenderDrawColor(renderer, 40, 100, 30, 255);
        SDL_RenderClear(renderer);

        // Dibujar serpiente
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        std::for_each(rq.begin(), rq.end(), [&](SDL_Rect& snake_segment) {
            SDL_RenderFillRect(renderer, &snake_segment);
        });

        // Dibujar manzana
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &apple);

           //texto
        std::string puntuacion = "puntos "+std::to_string(contador);
        SDLTest_DrawString(renderer, 10,10, puntuacion.c_str());

        SDL_RenderPresent(renderer);
        SDL_Delay(40);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
