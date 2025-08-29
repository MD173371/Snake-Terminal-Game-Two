CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -g
OBJ = main.o memory.o gameboard.o gameplay.o random.o terminal.o newsleep.o linkedlist.o
EXEC = eat

ifdef DEBUG
CFLAGS += -D DEBUG=1
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c memory.h gameboard.h gameplay.h random.h terminal.h newsleep.h macros.h linkedlist.h gamestate.h
	$(CC) -c main.c $(CFLAGS)

memory.o : memory.c memory.h
	$(CC) -c memory.c $(CFLAGS)

gameboard.o : gameboard.c gameboard.h random.h macros.h newsleep.h
	$(CC) -c gameboard.c $(CFLAGS)

gameplay.o : gameplay.c gameplay.h random.h macros.h terminal.h gamestate.h linkedlist.h
	$(CC) -c gameplay.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

newsleep.o : newsleep.c newsleep.h
	$(CC) -c newsleep.c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) -c linkedlist.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
