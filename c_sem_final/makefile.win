CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi 
OBJ = main.o hashtable.o input.o bayes.o
BIN = spamid.exe

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

.c.o:
	$(CC) $(CFLAGS) -c $^

clean :
	rm $(BIN) $(OBJ)

clean_win :
	del $(BIN) $(OBJ)