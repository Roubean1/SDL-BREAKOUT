gcc -Wall -Wextra -pedantic -o game block.c game.c gameMenu.c generateMap.c highScore.c main.c paddle.c ball.c -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_gfx

if [ $? -eq 0 ]; then
  echo "Zkompilováno"
else
  echo "Chyba"
fi
