all:
	gcc src/main.c -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./jogo