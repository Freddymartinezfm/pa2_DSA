TARGET = pa2
CC = g++
FLAGS = -g -Wall
OBJ = main.o
HEADERS = utility.h Binary_node.h Binary_tree.h Search_tree.h AVL_node.h AVL_tree.h Log.h
TYPE = win
WIN = del
LINUX = rm

pa2:  main.o
	$(CC) $(FLAGS) main.o  -o $(TARGET)

main.o: main.cpp $(HEADERS)
	$(CC) $(FLAGS) -c main.cpp

# clean:
# ifeq ($(TYPE), win)
# 	#del -f *.o pa2
# 	TYPE = $(WIN)
# else 
# 	# rm -f *.o pa2
# 	TYPE = $(LINUX)
# endif

clean:
ifeq ($(WILDCARD), win)
	#del -f *.o pa2
	TYPE = $(WIN)
else 
	# rm -f *.o pa2
	TYPE = $(LINUX)
endif


	
