pa2:  main.o
	g++ -g -Wall main.o  -o pa2
main.o: main.cpp utility.h Binary_node.h Binary_tree.h Search_tree.h AVL_node.h AVL_tree.h Log.h
	g++ -g -c main.cpp
clean:
	rm -f *.o pa2