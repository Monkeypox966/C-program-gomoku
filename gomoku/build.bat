gcc main.c game.c aimove.c judge.c score.c -o gomoku.exe -O2 -I..\raylib\include -L..\raylib\lib -lraylib -lgdi32 -lwinmm

echo Compilation successful! Starting up...
gomoku.exe

