#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define PIXEL_RATIO   5

void checkKeyDown(SDL_Keycode key);
void checkMouseButtonDown(char button);

int main(int argc, char *args[]) {
	SDL_Window   *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int mouseX = 0, mouseY = 0;
    float frameTime = 0, deltaTime = 0;
    int prevTime = 0, currTime = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        cout << "Video Initalization Error: " << SDL_GetError() << endl;
    else {
        window = SDL_CreateWindow("Hello World",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL)
            cout << "Video Creation Error: " << SDL_GetError() << endl;
        else {
            // Window Created
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            cout << "Renderer Creation Error: " << SDL_GetError() << endl;
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH/PIXEL_RATIO, SCREEN_HEIGHT/PIXEL_RATIO);
        SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 62, 44, 65, 255);

    // Game loop
    SDL_Event event;
    bool close = false;
    while (!close) {
        prevTime = currTime;
        currTime = SDL_GetTicks();
        deltaTime = (currTime - prevTime) / 1000.0f;

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    cout << "Close" << endl;
                    close = true;
                    break;
                case SDL_KEYDOWN:
                    checkKeyDown(event.key.keysym.sym);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    checkMouseButtonDown(event.button.button);
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = (int)event.button.x;
                    mouseY = (int)event.button.y;
                    SDL_RenderDrawPoint(renderer, mouseX, mouseY);
                    cout << "X: " << mouseX << "\tY: " << mouseY << endl;
                    break;
            }

        }

        frameTime += deltaTime;
        if (frameTime >= 0.01f){
            frameTime = 0;
            // SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer); renderer = nullptr;
    SDL_DestroyWindow(window); window = nullptr;
    SDL_Quit();

    return 0;
}

void checkKeyDown(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            cout << "Up" << endl;
            break;
        case SDLK_DOWN:
            cout << "Down" << endl;
            break;
        case SDLK_LEFT:
            cout << "Left" << endl;
            break;
        case SDLK_RIGHT:
            cout << "Right" << endl;
            break;
    }
}

void checkMouseButtonDown(char button) {
    switch (button) {
        case SDL_BUTTON_LEFT:
            cout << "Mouse Left" << endl;
            break;
        case SDL_BUTTON_RIGHT:
            cout << "Mouse Right" << endl;
            break;
    }
}
