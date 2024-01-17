#include "main.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
SDL_Rect paddleRect;
SDL_Rect ballRect;

enum GameState currentState = MENU;
enum GameState previousState = MENU;
float ballSpeedX = DEFAULTSPEED;
float ballSpeedY = DEFAULTSPEED;
float ballSpeedSet = DEFAULTSPEED;
int score = 0;      
int gameRun = 0;
int blockWidth = 60;
int blockHeight = 20;
int highScores[MAX_SCORE_ENTRIES];
Block blocks[NUM_BLOCKS_X][NUM_BLOCKS_Y];
int lives = 3;
int selectedOption = 0;
    
int main() {

    initBlocks();
    loadHighScores();

    //  umístění a velikost pádla

    paddleRect.w = 100;
    paddleRect.h = 20;
    paddleRect.x = (800 - paddleRect.w) / 2;
    paddleRect.y = 600 - 30;

    // umstění a velikost míčku
    ballRect.w = 20;
    ballRect.h = 20;
    ballRect.x = paddleRect.x + 25;
    ballRect.y = paddleRect.y - 25;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Chyba při inicializaci SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "Chyba při inicializaci SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow("Breakout",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Chyba při vytváření okna: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Chyba při vytváření rendereru: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    font = TTF_OpenFont("font/Albertsthal Typewriter.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "Chyba při načítání fontu: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    int quit = 0;

    while (!quit) {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        selectedOption = (selectedOption - 1 + (currentState == MENU ? MENU_ITEMS : SETTINGS_ITEMS)) % (currentState == MENU ? MENU_ITEMS : SETTINGS_ITEMS); // posun o 1 v nabídce nahoru
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % (currentState == MENU ? MENU_ITEMS : SETTINGS_ITEMS);   // posun o 1 v nabídce dolů
                        break;
                    case SDLK_LEFT:
                        if(ballSpeedY > 0.5 && ballSpeedX > 0.5 && currentState == SETTINGS && gameRun == 0 && selectedOption == 0) { // nastavení rychlosti míčku -0,5
                            ballSpeedSet-= 0.5;
                            ballSpeedX = ballSpeedSet;
                            ballSpeedY = ballSpeedSet; 
                            printf("%f %f\n", ballSpeedX, ballSpeedY);
                        }
                        break;
                    case SDLK_RIGHT:
                        if(ballSpeedY < 10 && ballSpeedX < 10 && currentState == SETTINGS && gameRun == 0 && selectedOption == 0){  // nastavení rychlosti míčku + 0,5
                            ballSpeedSet+=0.5;
                            ballSpeedX = ballSpeedSet;
                            ballSpeedY = ballSpeedSet; 
                            printf("%f %f\n", ballSpeedX, ballSpeedY);
                        }
                        break;
                    case SDLK_RETURN:
                        // Zpracování volby menu podle selectedOption
                        performAction(selectedOption);
                        if(currentState == SETTINGS && selectedOption == 1 && gameRun == 0){    // vytvoření nové mapy
                            generujMapu();
                            initBlocks();
                        }
                        break;
                    case SDLK_ESCAPE:
                        // ESC (ukončení programu nebo návrat)
                        if (currentState == GAME){
                            currentState = previousState;
                        }
                        else if (currentState == SETTINGS) {
                            currentState = previousState;  // Návrat do předchozí stage
                        } else {
                            printf("Ukončuji program.\n");
                            quit = 1;
                        }
                        break;
                }
                if(currentState == GAME) handleInput(e);
            }
        }

        // Vykreslit scenu podle stavu
        if (currentState == MENU) { //menu
            drawMenu();
        } else if (currentState == SETTINGS) { // nastavení
            drawSettings();
        } else if (currentState == GAME) { // hra
            updateGame();
            drawGame();
            updateBall();

            drawPaddle();
            drawBall();
            drawBlocks();
        }
        SDL_RenderPresent(renderer);
            SDL_Delay(16);
    }

    saveHighScores();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}