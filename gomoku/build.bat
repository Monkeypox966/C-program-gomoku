@echo off
echo Compiling gomoku...

gcc main.c -o gomoku.exe -O2 -Iinclude -I ..\raylib\include -L ..\raylib\lib -lraylib -lgdi32 -lwinmm

if errorlevel 1 (
    echo Compilation failed! Please check your code.
    pause
) else (
    echo Compilation successful! Starting up...
    gomoku.exe
)