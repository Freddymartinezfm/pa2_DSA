# pa2: clean main.o OnOptionsMenu.o
# 	g++ -o pa1 main.o OnOptionsMenu.o
# main.o: main.cpp Binary_tree.h Search_tree.h errorcode.h
# 	g++ -c -g -Wall main.cpp
# OnOptionsMenu.o: OnOptionsMenu.h OnOptionsMenu.cpp
# 	g++ -c -g -Wall OnOptionsMenu.cpp

# # clean:
# # 	rm -f *.o  



pa2: main.o 
	g++ -g -Wall main.o -o pa2
main.o: main.cpp utility.h Binary_node.h Binary_tree.h Search_tree.h AVL_node.h AVL_tree.h
	g++ -g -c main.cpp

#include "h"
#include "h"
#include "h"
#include "h"
#include "h"
#include ""

#clean:
#	del -f *.o *.exe  