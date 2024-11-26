#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <SDL2/SDL.h>

//dibuja
void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i == red) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo para el índice activo
        else if (i == blue) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Azul para el segundo índice activo
        else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco para los demás
        SDL_RenderDrawLine(renderer, i, 100, i, 100 - v[i]);
    }
}
//merge sort --------------------
void merge(std::vector<int>&arr, int left, int mid, int right, SDL_Renderer* renderer){
    int n1 = mid-left+1;
    int n2 = right-mid;
    //vector temporal
    std::vector<int> L(n1), R(n2);
    //copiar vectores al temporal l y r
    for(int i =0; i<n1;i++){
        L[i] = arr[left+i];
    }
    for(int j=0; j<n2; j++){
        R[j]= arr[mid+1+j];
    }
    int i=0, j=0;
    int k = left;

    //merge siuu
    while (i<n1 && j<n2){
        if (L[i]<R[i]){
            arr[k]=L[i];
            //dibuja
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
        draw_state(arr, renderer, left, right);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
    
    //copia los elementos restantes de L si sobra
    while( i<n1){
        arr[k]=L[i];
        i++;
        k++;
        draw_state(arr, renderer, left, right);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    //copia los elementos de j si sobran
    while(j <n2){
        arr[k] = R[j];
        j++;
        k++;
        draw_state(arr, renderer, left, right);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
}

void mergesort(std::vector<int>& arr, int left, int right, SDL_Renderer* renderer){
    if(left >= right){
        return;
    }
    int mid = left + (right-left)/2;
    mergesort(arr, left, right, renderer);
    mergesort(arr, mid+1, right, renderer);
    merge(arr, left, mid, right, renderer);
   
}


int main(int argc, char* argv[]){
    //window render
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr<<"error "<<SDL_GetError()<<std::endl;
        return -1;
    }
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event e;
    bool running=1;
    SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10,10);
    if (!window || !renderer){
        std::cerr<<"error"<<SDL_GetError()<<std::endl;
        SDL_Quit();
        return -1;
    }
    std::random_device rd;
    std::uniform_int_distribution d(1,99); //genera numero de 1 a 99
    std::vector<int> v;

    for(int i=0;i<100; i++){
        v.push_back(d(rd));
    }


    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running =false;
            }
        }
        mergesort(v,0,v.size()-1, renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}