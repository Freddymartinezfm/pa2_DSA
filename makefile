pa2:  main.o Log.o
	g++ -g -Wall main.o Log.o -o pa2

main.o: main.cpp utility.h Binary_node.h Binary_tree.h Search_tree.h AVL_node.h AVL_tree.h
	g++ -g -c main.cpp
Log.o: Log.cpp Log.h
	g++ -g -c Log.cpp
 clean:
	del -f *.o *.exe

# clean:
	# rm -f *.o pa?