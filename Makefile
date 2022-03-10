CXX = g++
#CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = ./src/main.cpp ./src/obstaculo.cpp ./src/coche.cpp ./src/celda.cpp ./src/tablero.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = ./bin/exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)