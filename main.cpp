#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "globals.cpp"
using namespace std;


void checkKeyDown(SDL_Keycode key);
bool checkMouseButtonDown(char button);
bool createNewSand(int x, int y, Color *c);
void updateSand();
void drawSand(SDL_Renderer *renderer);
void drawRendererBackground(SDL_Renderer *renderer);
void printScreen();


// Screen array
sand screen[rows][cols]; 


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
    int mouseX = 0, mouseY = 0;
    float frameTime = 0, deltaTime = 0;
    int prevTime = 0, currTime = 0;
    unsigned char currColorIndex = 0;

    cout << rows << "\t" << cols << endl;

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
                case SDL_MOUSEMOTION:
                    mouseX = (int)event.button.x;
                    mouseY = (int)event.button.y;
                    // cout << mouseX << "\t" << mouseY << endl;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    isLeftMouseDown = checkMouseButtonDown(event.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    isLeftMouseDown = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            cout << "Up" << endl;
                            break;
                        case SDLK_DOWN:
                            cout << "Down" << endl;
                            break;
                        case SDLK_LEFT:
                            cout << "Left" << endl;
                            if (currColorIndex == 0) currColorIndex = numColors-1;
                            else currColorIndex--;
                            break;
                        case SDLK_RIGHT:
                            cout << "Right" << endl;
                            if (currColorIndex+1 == numColors) currColorIndex = 0;
                            else currColorIndex++;
                            break;
                    }
                    break;
            }

            if (isLeftMouseDown) {
                createNewSand(mouseX, mouseY, &colors[currColorIndex]);
            }
        }

        frameTime += deltaTime;
        if (frameTime >= 0.25f){
            frameTime = 0;
            drawRendererBackground(renderer);
            // printScreen();
            updateSand();
            drawSand(renderer);
            // SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, bg.R, bg.G, bg.B, 255);
            SDL_RenderDrawRect(renderer, NULL);
        }
    }
}

void printScreen() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (screen[i][j].isActive) {
                cout << i << j;
            }
            cout << endl;
        }
    }
}

void drawSand(SDL_Renderer *renderer) {
    sand currSand;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (screen[i][j].isActive) {
                sand currSand = screen[i][j];
                SDL_SetRenderDrawColor(renderer, currSand.color->R, currSand.color->G, currSand.color->B, 255);
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}


void updateSand() {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            sand currSand = screen[x][y];
            // no sand at current location
            if (!currSand.isActive) continue;
            // if no sand below, go down
            else if (y+1 < rows && !screen[x][y+1].isActive) { // TODO
                screen[x][y+1] = sand(screen[x][y]);
                screen[x][y].isActive = false;
            }
            // else if no sand left diagonal, go there
            else if (x-1 >= 0 && y+1 < rows && !screen[x-1][y+1].isActive) { // TODO
                screen[x-1][y+1] = sand(screen[x][y]);
                screen[x][y].isActive = false;
            }
            // else if no sand right diagonal, go there
            else if (x+1 < cols && y+1 < rows && !screen[x+1][y+1].isActive) { // TODO
                screen[x+1][y+1] = sand(screen[x][y]);
                screen[x][y].isActive = false;
            }
            // else, leave it be
        }
    }
}


// Assumes valid x, y coordinates
bool createNewSand(int x, int y, Color *c) {
    // Sand already exists
    cout << x << "\t" << y << endl;
    if (screen[x][y].isActive) return false;
    screen[x][y] = sand(c);
    return true;
}

void drawRendererBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, bg.R, bg.G, bg.B, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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
                SDL_RenderSetLogicalSize(renderer, rows, cols);
                // start game loop if not errors
                gameLoop(window, renderer);
            }
        }
    }

    // Delete pointers
    SDL_DestroyRenderer(renderer); renderer = nullptr;
    SDL_DestroyWindow(window); window = nullptr;
    SDL_Quit();

    return 0;
}
