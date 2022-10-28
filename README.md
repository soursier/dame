# dame

un fichier make file contenant 

CC ?= gcc
CFLAGS += -Wall --pedantic -Werror

all:
	$(CC) $(LDFLAGS) -o dames $(CFLAGS) lib/dames.c main.c

devrait fonctionner
