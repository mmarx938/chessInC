CC=gcc 
CFLAGS=-I. -g -w -pthread -lpthread
DEPS = chess.h
OBJ = chess.o capture.o crono.o move.o player.o show.o

%.o: %.c $(DEPS)
	$(CC)  -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)