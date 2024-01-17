#include "main.h"

void drawPaddle() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect);
}

void handleInput(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                if (paddleRect.x - 10 >= 0) {
                    paddleRect.x -= 25;             // posun o 25 do leva
                }
                break;
            case SDLK_RIGHT:
                if (paddleRect.x + paddleRect.w + 10 <= 800) {
                    paddleRect.x += 25;             // posun o 25 do prava
                }
                break;
            case SDLK_r:
                lives = 0;      // r - reset hry
                break;
        }
    }
}
