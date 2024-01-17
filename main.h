#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <errno.h>


#define SCREEN_WIDTH 800    // Šířka okna
#define SCREEN_HEIGHT 600   // Výška okna
#define MENU_ITEMS 3    // Počet položek v menu
#define SETTINGS_ITEMS 3    // Počet položek v nastavení
#define MAX_SCORE_ENTRIES 5 // Maximální počet umístění v highScore
#define DEFAULTSPEED 3      // Základní rychlost míčků
#define NUM_BLOCKS_X 10 // Počet bloků na šířků
#define NUM_BLOCKS_Y 5  // Počet bloků na výšku


//prvky v menu
enum GameState {
    MENU,
    SETTINGS,
    GAME
};


//struktura pro bloky
typedef struct {
    SDL_Rect rect;      // velikost, pozice
    int lives;          // Počet životů bloku
    SDL_Color color;    // Barva bloku
} Block;


//druhy barev bloků
enum BlockColor{
    BLUE = 1,
    RED,
    GREEN,
    YELLOW,
    GOLD
};

// Stuktury pro práci s SDL
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;


extern SDL_Rect paddleRect; // Pádlo
extern SDL_Rect ballRect;   // Míček

extern Block blocks[NUM_BLOCKS_X][NUM_BLOCKS_Y];    // Pole bloků
extern int gameRun; // Info zda hra stále běží
extern int selectedOption;  // Index vybrané položky menu
extern enum GameState currentState;  // Aktuální stav aplikace
extern enum GameState previousState;  // Předchozí stav aplikace
extern int highScores[MAX_SCORE_ENTRIES];   // Pole pro highScore
extern float ballSpeedX;    // Rychlost míčku pro X
extern float ballSpeedY;    // Rychlost míčků pro Y
extern float ballSpeedSet; // Nastavená rychlost míčku
extern int blockWidth;  // Šířka bloku
extern int blockHeight; // Výška bloku
extern int lives;   // Počet životů hráče
extern int score;   // Score hráče



// Deklarace funkcí
void loadHighScores();  //  Načtení highScore ze souboru
void saveHighScores();  // Uložení highScore do souboru
void updateScore(); // Aktualizace highScore a uložení nového žebříčku do souboru
void drawText(const char* text, int x, int y, SDL_Color color); // Vykreslování textu
void drawFilledCircle(int x, int y, int radius, SDL_Color color); // Vykreslení tečky v menu
void performAction(int option); // Provedení akce ve výběru v menu
void drawMenu();    // Vykreslení menu
void drawSettings();    // Vykreslení nastavení
void getColor(SDL_Color * colorBlocks, int lives); // Přiřazení barvy bloků podle počtů životů
void generujMapu(); // Generátor nové mapy
void initBlocks();  // Inicializuje (vykreslí) bloky
void drawGame();    // Vykreslení hry
void initSDL(); // Inicializace SDL okna a rendereru
void drawPaddle();  // Vykreslení pádla
void drawBall();    // Vykreslení míčku
void drawBlocks();  // Vykreslení bloků
int checkCollision(SDL_Rect a, SDL_Rect b); // Detekci kolize- dotyky s bloky
int min(int a, int b);  // Porovnávání, která hodnota je menší
void updateBall();  // Aktualizace míčku
void updateGame();  // Aktualizace hry
void handleInput(SDL_Event event);  //Ovládání hry

#endif // FUNCTIONS_H