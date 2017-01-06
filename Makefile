BINARY = todoer
CC = gcc
DEBUGOPT = -D_DEBUG

$(BINARY): main.c strext.c startup.c tdact.c
	$(CC) $(DEBUGOPT) -O2 -o $@ $^ 
