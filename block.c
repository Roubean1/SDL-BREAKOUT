#include "main.h"

void initBlocks() {
    FILE* file = fopen("data/mapa.gaura", "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(1);
    }


    for (int i = 0; i < NUM_BLOCKS_X; ++i) {
        for (int j = 0; j < NUM_BLOCKS_Y; ++j) {
            if (fscanf(file, "%d %d %d", &blocks[i][j].rect.x, &blocks[i][j].rect.y, &blocks[i][j].lives) != 3) {
                fprintf(stderr, "Error reading block positions from file\n");
                exit(1);
            }

            if(blocks[i][j].lives >0){      // pokud má blok životy nastaví se mu rozměry
                blocks[i][j].rect.w = blockWidth;
                blocks[i][j].rect.h = blockHeight;
            }
            else{
                blocks[i][j].rect.w = 0;    // pokud blok nemá životy rozměry zmizí
                blocks[i][j].rect.h = 0;
            }

            getColor(&blocks[i][j].color, blocks[i][j].lives);  
        }
    }

    fclose(file);
}

void drawBlocks() {
    for (int i = 0; i < NUM_BLOCKS_X; ++i) {
        for (int j = 0; j < NUM_BLOCKS_Y; ++j) {
            if (blocks[i][j].rect.w > 0 && blocks[i][j].rect.h > 0) {
                // Vykreslení bloků
                SDL_SetRenderDrawColor(renderer, blocks[i][j].color.r, blocks[i][j].color.g, blocks[i][j].color.b, 255);
                SDL_RenderFillRect(renderer, &blocks[i][j].rect);

                // Ohraničení bloků
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &blocks[i][j].rect);
            }
        }
    }
}

void getColor(SDL_Color * colorBlocks, int lives) { //barvy pro bloky podle životů
    if(lives == BLUE){
        colorBlocks->r = 0;
        colorBlocks->g = 0;
        colorBlocks->b = 255;
        colorBlocks->a = 255;
    }
    else if (lives == RED){
        colorBlocks->r = 255;
        colorBlocks->g = 0;
        colorBlocks->b = 0;
        colorBlocks->a = 255;
    }
    else if (lives == GREEN){
        colorBlocks->r = 0;
        colorBlocks->g = 255;
        colorBlocks->b = 0;
        colorBlocks->a = 255;
    }
    else if (lives == YELLOW){
        colorBlocks->r = 255;
        colorBlocks->g = 255;
        colorBlocks->b = 0;
        colorBlocks->a = 255;
    }
    else if (lives == GOLD){
        colorBlocks->r = 212;
        colorBlocks->g = 175;
        colorBlocks->b = 55;
        colorBlocks->a = 255;
    }
}

