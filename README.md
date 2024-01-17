#BREAKOUT SDL PROJEKT

Breakout je arkádová video hra, kterou vyvíjela Atari, Inc. a vydalají v roce 1976.

Tento projekt je simulace této hry, vyvíjená v jazyce C s knihovnami SDL.
Hra má úvodní nabídku, kde můžete hru spustit, nastavit si hru a ukončit ji.

###Hra

Pomocí šípek doprava a doleva posunujete pádlo.
Odrážíte pomocí pádla míček, když vám míček spadne, ztrácíte život.
Snažíte se pomocí míčku zničit všechny bloky, bloky mají různý počet životů 1-5 a jejich počet poznáte podle barvy.
Vyhráváte, pokud zničíté všechny bloky.
Prohráváte, pokud příjdete o všechny životy.
Po ukončení hry se vám uloží nejvyšší skóre.

###Nastavení

V nastavení, lze měnit rychlost míčku a nechat si vygenerovat novou mapu.

###Exit

Ukončení hry, nebo pomocí klávesy ESC, se kterou se může vracet také v Menu zpět.


##Install

Je potřeba mít gcc
Nainstalované SDL, SDL_ttf a SDL2_gfxPrimitives
Pomocí bash skriptu, přeložte program.
V terminálu zadej: ```bash install.sh```
