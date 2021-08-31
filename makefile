SRC_FOLDER = ./src
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(SRC:.cpp=.o)
CC = g++
TARGET = binary

all: out
	./$(TARGET)

check: out
	valgrind ./$(TARGET)

out: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) 

bin: $(OBJ)
	$(CC) -o3 -s $(OBJ) -o $(TARGET)
	make clean

clean: 
	rm -f $(OBJ)

fclean: 
	rm -f $(OBJ) $(TARGET)
