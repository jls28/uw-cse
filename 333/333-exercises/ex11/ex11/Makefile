CC = gcc
CXX = g++
CFLAGS = -Wall -g

HEADERS = Vector.h
OBJS = Vector.o ex11.o

all: ex11

ex11: $(OBJS) $(HEADERS)
	$(CXX) $(CFLAGS) -std=c++11 -o $@ $(OBJS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CFLAGS) -std=c++11 -c $< -o $@

clean:
	rm -rf *.o ex11 *~
