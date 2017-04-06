CC = g++
LDFLAGS =
CFLAGS = -I include -g -c -std=c++11
SRC = $(wildcard *.cpp src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = spc

all: $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o src/*.o $(EXEC) *.vmc