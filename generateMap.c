#include "main.h"

void generujMapu() {
    FILE * file = fopen("data/mapa.gaura","w");

    if (!file) {
        printf("Chyba při načítání mapy.\n");
        return;
    }

    for (int i = 0; i < NUM_BLOCKS_X; ++i) {
        for (int j = 0; j < NUM_BLOCKS_Y; ++j) {
            blocks[i][j].rect.x = i * (blockWidth + 10) + 50; // 10 mezera mezi bloky + 50 odstup od levého okraje
            blocks[i][j].rect.y = j * (blockHeight + 10) + 50; // 10 mezera mezi bloky + 50 odstup od horního okraje

            blocks[i][j].lives = rand() % 6;    // náhodné generování životů 0-5
            printf("%d %d %d\n", blocks[i][j].rect.x, blocks[i][j].rect.y, blocks[i][j].lives);
            fprintf(file, "%d %d %d\n", blocks[i][j].rect.x, blocks[i][j].rect.y, blocks[i][j].lives);
        }
    }

    fclose(file);
}