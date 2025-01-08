rem set filename=arkanoid
rem set filename=asteroids
rem set filename=asteroids_survival
set filename=floppy
rem set filename=gold_fever
rem set filename=gorilas
rem set filename=missile_commander
rem set filename=platformer
rem set filename=pong
rem set filename=snake
rem set filename=space_invaders
rem set filename=tetris

rem gcc -o game.exe %filename%/%filename%.c -I.\include  -lraylib -lgdi32 -lwinmm
rem .\game.exe

emcc -o main.html %filename%/%filename%.c -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I.\include -I C:\raylib\src -I C:\raylib\src\external -L C:\raylib\src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file C:\raylib\src\shell.html C:\raylib\src\web\libraylib.web.a -DPLATFORM_WEB -s EXPORTED_RUNTIME_METHODS=ccall
