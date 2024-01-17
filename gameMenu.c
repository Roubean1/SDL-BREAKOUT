#include "main.h"

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void drawFilledCircle(int x, int y, int radius, SDL_Color color) {
    filledCircleRGBA(renderer, x, y, radius, color.r, color.g, color.b, color.a);   // vyplnění kruhu  pro vybranou položku
}
    
void drawMenu() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Vykreslení herního menu
    SDL_Color textColor = {0, 0, 0, 255};
    const char* menuItems[MENU_ITEMS] = {"Play", "Settings", "Exit"};
    for (int i = 0; i < MENU_ITEMS; ++i) {
        int x = 50;
        int y = 50 + i * 50;

        // Vykreslit text
        drawText(menuItems[i], x, y, textColor);

        // Vykreslit kruh pro vybranou položku
        if (i == selectedOption) {
            int circleRadius = 5;
            int circleX = x - circleRadius - 10;
            int circleY = y + 20;

            SDL_Color circleColor = {255, 0, 0, 255};
            drawFilledCircle(circleX, circleY, circleRadius, circleColor);
        }


        // výpis herního menu
        SDL_Color scoreColor = {255, 127, 0, 255};
        drawText("High score:", 550, 250, scoreColor);  // výpis nadpisu High score
        for (int i = MAX_SCORE_ENTRIES-1; i  >= 0; --i) {
            int x = 600;
            int y = 300 + i * 50;

            char scoreText[50];
            sprintf(scoreText, "%d. %d", i+1, highScores[i]);   // výpis každé jendotlivé položky
            drawText(scoreText, x, y, scoreColor);
        }
    }

    SDL_RenderPresent(renderer);
}

void drawSettings() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Vykreslit rozhraní nastavení
    SDL_Color textColor = {0, 0, 0, 255};

    char retezec[20] = {'\0'}; 
    sprintf(retezec, "Ball speed:  %.1f", ballSpeedSet);
    const char* settingsItems[SETTINGS_ITEMS] = {retezec, "Generate new map", "Back to Menu"}; //poločky
    for (int i = 0; i < SETTINGS_ITEMS; ++i) {
        int x = 50;
        int y = 50 + i * 50;

        // Vykreslit text
        drawText(settingsItems[i], x, y, textColor);

        // Vykreslit kruh pro vybranou položku
        if (i == selectedOption) {
            int circleRadius = 5;
            int circleX = x - circleRadius - 10;
            int circleY = y + 20;

            SDL_Color circleColor = {255, 0, 0, 255};  // Červená barva kruhu
            drawFilledCircle(circleX, circleY, circleRadius, circleColor);
        }
    }

    SDL_RenderPresent(renderer);
}


void drawText(const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void performAction(int option) {
    printf("Akce pro položku %d\n", option);

    // Přechod do nastavení
    if (option == 1 && currentState == MENU) {
        previousState = currentState;  // Uložit předchozí stav
        currentState = SETTINGS;
        selectedOption = 0;  // Nastavit vybranou položku na začátek menu v nastavení
    }

    // Ukončit program v hlavním menu položka exit Exit
    if (currentState == MENU && option == 2) {
        printf("Ukončuji program.\n");
        SDL_Quit();
        exit(0);
    }

    // Přechod do hry
    if (currentState == MENU && option == 0) {
        currentState = GAME;
        gameRun = 1;
    }

    // Přechod zpět do původního menu
    if (currentState == SETTINGS && option == 2) {
        currentState = previousState;
    }
}