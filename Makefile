all:
	gcc src/main.c src/render.c src/bomba.c src/inimigo.c src/gameplay.c -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./jogo