# define the commands we will use for compilation
CC = gcc

# define useful flags to cc/ld/etc.
CFLAGS += -Wall -g -std=c11

# define common dependencies
OBJS = vector.o ex5.o
HEADERS = vector.h

all: ex5

ex5: $(OBJS) $(HEADERS) FORCE
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HEADERS) FORCE
	$(CC) $(CFLAGS) -c -std=c11 $< -o $@

clean: FORCE
	/bin/rm -f *.o ex5 *~

FORCE:
