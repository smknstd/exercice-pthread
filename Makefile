#
# Variables:
#
CC = gcc
BIN = exec_cuisinieres
SRC = cuisinieres.c
OBJ = cuisinieres.o


#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic


#
# Flags pour le compilateur:
#
CFLAGS = $(ERROR_FLAGS) -D_REENTRANT -DLinux


#
# Flags pour l'editeur de liens:
#
LDFLAGS = $(ERROR_FLAGS) -pthread


#
# Construction du programme:
#
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)


#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
