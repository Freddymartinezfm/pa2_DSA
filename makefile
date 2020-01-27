# pa2: clean main.o OnOptionsMenu.o
# 	g++ -o pa1 main.o OnOptionsMenu.o
# main.o: main.cpp Binary_tree.h Search_tree.h errorcode.h
# 	g++ -c -g -Wall main.cpp
# OnOptionsMenu.o: OnOptionsMenu.h OnOptionsMenu.cpp
# 	g++ -c -g -Wall OnOptionsMenu.cpp

# # clean:
# # 	rm -f *.o  

# clean:
# 	del -f *.o *.exe  


pa2: main.o
	g++ -g -Wall main.o -o pa2
