
set filename=just_do.c  screen_level00.c  screen_level01.c  screen_level02.c screen_level03.c screen_level04.c screen_level05.c screen_level06.c screen_level07.c  screen_level08.c screen_level09.c  screen_level10.c screen_logo.c       

rem gcc -o game.exe %filename%   -lraylib -lgdi32 -lwinmm
rem .\game.exe

emcc -o main.html  %filename% -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I.\include -I C:\raylib\src -I C:\raylib\src\external -L C:\raylib\src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file resources --shell-file C:\raylib\src\shell.html C:\raylib\src\web\libraylib.web.a -DPLATFORM_WEB -s EXPORTED_RUNTIME_METHODS=ccall
