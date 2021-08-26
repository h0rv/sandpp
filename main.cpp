#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define PIXEL_RATIO   5

void checkKeyDown(SDL_Keycode key);
bool checkMouseButtonDown(char button);

struct Color {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    
    Color(unsigned char R, unsigned char G, unsigned char B) {
        this->R = R;
        this->G = G;
        this->B = B;
    }
};

struct sand {
    int x;
    int y;
    Color *color;
    
    sand(int x, int y, Color *color) {
        this->x = x;
        this->y = y;
        this->color = color;
    }
};

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

// Handles mouse button events.
// Returns true if left mouse is down
bool checkMouseButtonDown(char button) {
    switch (button) {
        case SDL_BUTTON_LEFT:
            cout << "Mouse Left" << endl;
            return true;
            break;
        case SDL_BUTTON_RIGHT:
            cout << "Mouse Right" << endl;
            break;
    }
    return false;
}

void gameLoop(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 62, 44, 65, 255);
    int mouseX = 0, mouseY = 0;
    float frameTime = 0, deltaTime = 0;
    int prevTime = 0, currTime = 0;

    sand **screen[SCREEN_HEIGHT/PIXEL_RATIO][SCREEN_WIDTH/PIXEL_RATIO];

    SDL_Event event;
    bool close = false;
    bool isLeftMouseDown = false;
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
                    isLeftMouseDown = checkMouseButtonDown(event.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    isLeftMouseDown = false;
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = (int)event.button.x;
                    mouseY = (int)event.button.y;
                    // cout << "X: " << mouseX << "\tY: " << mouseY << endl;
                    break;
            }

            if (isLeftMouseDown)
                SDL_RenderDrawPoint(renderer, mouseX, mouseY);
        }

        frameTime += deltaTime;
        if (frameTime >= 0.01f){
            frameTime = 0;
            // SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT/PIXEL_RATIO; i++) {
        for (int j = 0; j < SCREEN_WIDTH/PIXEL_RATIO; j++) {
            delete screen[i][j];
        }
        delete [] *screen[i];
    }
    delete[] **screen; 
    **screen = NULL;
}

int main(int argc, char *args[]) {
	SDL_Window   *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // Initalize window and renderer
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
            // Window created successfully
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
                cout << "Renderer Creation Error: " << SDL_GetError() << endl;
            else {
                SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH/PIXEL_RATIO, SCREEN_HEIGHT/PIXEL_RATIO);
                SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);

                // start game loop if not errors
                gameLoop(window, renderer);
            }
        }
    }


    // Delete points
    SDL_DestroyRenderer(renderer); renderer = nullptr;
    SDL_DestroyWindow(window); window = nullptr;
    SDL_Quit();

    return 0;
}
