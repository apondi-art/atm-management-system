CC = gcc
CFLAGS = -I./sqlite
LDFLAGS = sqlite/sqlite3.c -lpthread -ldl

atm: src/main.c src/system.c src/checkcases.c src/print.c
	$(CC) $(CFLAGS) -o atm src/main.c src/system.c src/checkcases.c src/print.c $(LDFLAGS)