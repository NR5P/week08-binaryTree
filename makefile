###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother JonesL, CS235
# Author:
#     Griffin Pope, Nathan Rigg, Dallen Cluff, Dan Worwood
# Summary:
#     Implementation of binary tree with Huffman Codes
# Time:
#     20 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g -std=c++11
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g -std=c++11

huffman.o: bnode.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g -std=c++11

