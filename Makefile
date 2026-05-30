all:
	gcc src/main.c src/render.c src/bomba.c src/inimigo.c src/gameplay.c src/score.c -Iinclude -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -o jogo.exe -lraylib -lopengl32 -lgdi32 -lwinmm
run:
	./jogo