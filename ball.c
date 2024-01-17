#include "main.h"

void drawBall() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);
}

int checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;            // Přiřazení hodnoty rohům koule
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;            // Přiřazení hdonoty rohům pádla
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;


    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) { // Kontrola zdali je koule, nebo mimo blok => nedojde ke kolizi
        return 0;  // Bez kolize
    }

    return 1;  // Kolize
}

void updateBall() {
    ballRect.x += ballSpeedX;
    ballRect.y += ballSpeedY;

    if (checkCollision(ballRect, paddleRect)) {
        // Posunout míček o malý krok směrem od pádla
        if (ballSpeedY > 0) {
            ballRect.y -= 10; 
        } else {
            ballRect.y += 10; 
        }
        ballSpeedY = -ballSpeedY;
    }


    // Detekce kolize se stěnou
    if (ballRect.x <= 0 || ballRect.x + ballRect.w >= SCREEN_WIDTH) {
        ballSpeedX = -ballSpeedX;
    }

    if (ballRect.y <= 0) {
        ballSpeedY = -ballSpeedY;
    }
    for (int i = 0; i < NUM_BLOCKS_X; ++i) {
        for (int j = 0; j < NUM_BLOCKS_Y; ++j) {
            if (blocks[i][j].rect.w > 0 && blocks[i][j].rect.h > 0) {
                if (checkCollision(ballRect, blocks[i][j].rect)) {  // pokud dojdeke kolizi s blokem 
                    score += 100;

                    // Zjistit oblast kolize z každé strany bloku
                    int overlapLeft = ballRect.x + ballRect.w - blocks[i][j].rect.x;
                    int overlapRight = blocks[i][j].rect.x + blocks[i][j].rect.w - ballRect.x;
                    int overlapTop = ballRect.y + ballRect.h - blocks[i][j].rect.y;
                    int overlapBottom = blocks[i][j].rect.y + blocks[i][j].rect.h - ballRect.y;

                    // Najít minimální překrytí => určení nelbižšího okraje k míčku
                    int minOverlap = min(min(overlapLeft, overlapRight), min(overlapTop, overlapBottom)); 

                    // Změna směru odrazu na základě minimálního překrytí
                    if (minOverlap == overlapLeft) {
                        // Kolize zleva
                        ballSpeedX = -fabs(ballSpeedX);
                    } else if (minOverlap == overlapRight) {
                        // Kolize zprava
                        ballSpeedX = fabs(ballSpeedX);
                    } else if (minOverlap == overlapTop) {
                        // Kolize shora
                        ballSpeedY = -fabs(ballSpeedY);
                    } else if (minOverlap == overlapBottom) {
                        // Kolize zdola
                        ballSpeedY = fabs(ballSpeedY);
                    }

                    // Pokud má blok stále životy
                    if (blocks[i][j].lives > 0) {
                        blocks[i][j].lives--; // Bloky příjde o život

                        // Nastaví se bloku barva
                        getColor(&blocks[i][j].color, blocks[i][j].lives);

                        // Kontrola, zda má bloky život
                        if (blocks[i][j].lives <= 0) {
                            // Blok existuje, ale nastavíme mu nulové rozměry
                            blocks[i][j].rect.w = 0;
                            blocks[i][j].rect.h = 0;
                        }
                    }

                    // Po první detekci kolize s blokem se smyčka ukončí
                    break;
                }
            }
        }
    }
}