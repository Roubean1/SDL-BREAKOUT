#include "main.h"

int min(int a, int b) {
    return (a < b) ? a : b;
}

void loadHighScores() {
    FILE* file = fopen("data/high_scores.geordi", "r");
    if (!file) {
        printf("Chyba při načítání nejlepších skóre.\n");
        return;
    }

    for (int i = 0; i < MAX_SCORE_ENTRIES; ++i) {
        if (fscanf(file, "%d", &highScores[i]) != 1) {  //načítání po řádku skóre
            break;
        }
    }

    fclose(file);
}

void saveHighScores() {
    FILE* file = fopen("data/high_scores.geordi", "w");
    if (!file) {
        printf("Chyba při ukládání nejlepších skóre.\n");
        return;
    }

    for (int i = 0; i < MAX_SCORE_ENTRIES; ++i){
        fprintf(file, "%d\n", highScores[i]);   // ukládání po řádku skóre
    }

    fclose(file);
}

void updateScore() {
    for(int i = 0; i < MAX_SCORE_ENTRIES; i++){ // pokud je větší skóre, než skore v seznamu, tak se vloží na poslední pozici v seznamu
        if(score > highScores[i]){
            highScores[MAX_SCORE_ENTRIES-1] = score;
            break;
        }
    }

    for(int i = 0; i < MAX_SCORE_ENTRIES; i++){
        printf("%d\n", highScores[i]);
    }

    for (int n = 0; n < MAX_SCORE_ENTRIES; n++){        // seřazení hodnot pomocí bubble sortu
        for (int i = 0; i < MAX_SCORE_ENTRIES - n - 1; i++) {
            if (highScores[i] < highScores[i + 1]) {
                int pom = highScores[i];
                highScores[i] = highScores[i + 1];
                highScores[i + 1] = pom;
            }
        }
    }
    saveHighScores();
}