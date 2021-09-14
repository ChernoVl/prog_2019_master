CFLAGS = -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = ps4

all : $(OUTPUT)

$(OUTPUT): main.o hof.o k.o ui.o
	gcc $(CFLAGS) main.o hof.o k.o ui.o -lm -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

backpack.o: backpack.c backpack.h
	gcc $(CFLAGS) -c backpack.c -o backpack.o

command.o: command.c command.h
	gcc $(CFLAGS) -c command.c -o command.o

container.o: container.c container.h
	gcc $(CFLAGS) -c -lcurses container.c -o container.o

game.o: game.c game.h
	gcc $(CFLAGS) -c game.c -o game.o

item.o: item.c item.h
	gcc $(CFLAGS) -c item.c -o item.o

parser.o: parser.c parser.h
	gcc $(CFLAGS) -c parser.c -o parser.o

room.o: room.c room.h
	gcc $(CFLAGS) -c room.c -o room.o

world.o: world.c world.h
	gcc $(CFLAGS) -c world.c -o world.o

clean:
	rm -rf *.o $(OUTPUT)