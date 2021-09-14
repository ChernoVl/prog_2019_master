CFLAGS = -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = app

all : $(OUTPUT)

$(OUTPUT): main.o  arraylist.o
	gcc $(CFLAGS) main.o arraylist.o -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

arraylist.o: arraylist.c arraylist.h
	gcc $(CFLAGS) -c arraylist.c -o arraylist.o

clean:
	rm -rf *.o $(OUTPUT)

cppcheck:
	cppcheck --enable=warning,performance,unusedFunction --error-exitcode=1 arraylist.c main.c