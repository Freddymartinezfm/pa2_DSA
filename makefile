TARGET = pa2
CC = g++
FLAGS = -g -Wall
OBJ = main.o
HEADERS = utility.h Binary_node.h Binary_tree.h Search_tree.h AVL_node.h AVL_tree.h Log.h
TYPE = win

pa2: clean main.o
	$(CC) $(FLAGS) main.o  -o $(TARGET)

main.o: main.cpp $(HEADERS)
	$(CC) $(FLAGS) -c main.cpp
clean:
ifeq ($(TYPE), win)
	
	del *.o pa2
else 
	
	rm *.o pa2
endif
	
