all:
	gcc src/main.c src/render.c -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./jogo