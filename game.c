#include "main.h"

void drawGame() {

    // Vykreslit rozhraní hry
    SDL_Color textColor = {0, 0, 255, 0};

    // Vykreslit informace o životech a skóre
    char livesText[20];
    sprintf(livesText, "Lives: %d", lives);
    drawText(livesText, SCREEN_WIDTH - 250, 0, textColor);

    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    drawText(scoreText, SCREEN_WIDTH - 250, 20, textColor);
}

void updateGame() {

    // Detekce kolize s dolní stěnou (hráč ztrácí život)
    if (ballRect.y + ballRect.h >= SCREEN_HEIGHT) {
        lives--;
        if(lives > 0){
            // Hráč má ještě životy, resetujte polohu kuličky
            ballRect.x = paddleRect.x + 25;
            ballRect.y = paddleRect.y - 25;
        }
    }

    int winGame = 1;
    for (int i = 0; i < NUM_BLOCKS_X; ++i) {
        for (int j = 0; j < NUM_BLOCKS_Y; ++j) {
            if(blocks[i][j].lives > 0){
                winGame = 0;
            }
        }
    }

    if (lives <= 0 || winGame == 1) {
        // Hráč ztratil všechny životy, hra se restartuje
        lives = 3; // Reset životy
        currentState = MENU; // Přesun do menu
        gameRun = 0;
        ballSpeedX = ballSpeedSet;
        ballSpeedY = ballSpeedSet;
        updateScore();
        initBlocks();
        paddleRect.x = SCREEN_WIDTH/2;
        ballRect.x = paddleRect.x + 25;
        ballRect.y = paddleRect.y - 25;

        score = 0; // Reset skóré
    }
}
