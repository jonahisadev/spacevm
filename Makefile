CC = g++
LDFLAGS =
CFLAGS = -I include -g -c
SRC = $(wildcard *.cpp src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = main

all: $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o src/*.o $(EXEC)