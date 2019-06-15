/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream> // for CIN and COUT
#include <fstream>  // for IFSTREAM
#include <cassert>  // for ASSERT
#include <string>   // for STRING: binary representation of codes
#include <sstream>
#include <vector>

#include "bnode.h"   // for BINARY_NODE class definition
#include "vector.h"  // for VECTOR container
#include "pair.h"    // for PAIR container
#include "huffman.h" // for HUFFMAN() prototype

using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using namespace custom;

class huffmanTree
{

public:
   typedef BNode<custom::pair<std::string, float>> NodeType;
   huffmanTree()
   {
   }
   huffmanTree(const std::string &value, float frequency)
   {
      pRoot = new NodeType(custom::pair<std::string, float>(value, frequency));
   }
   ~huffmanTree()
   {
      deleteBTree(pRoot);
   }

   void printCodes();
   NodeType *getRoot() { return pRoot; }
   float getValue()
   {
      if (pRoot)
      {
         //maybe we should walk the whole tree, but I'm
         //not sure that's necessary yet.
         return pRoot->data.second;
      }
   }

private:
   NodeType *pRoot;
};

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string &fileName)
{
   std::ifstream infile(fileName);
   std::string line;
   std::vector<huffmanTree *> trees;

   while (std::getline(infile, line))
   {
      std::istringstream iss(line);
      std::string word;
      float frequency;
      if (!(iss >> word >> frequency))
      {
         break;
      } // error
      huffmanTree *tree = new huffmanTree(word, frequency);
      trees.push_back(tree);
   }

   for (std::vector<huffmanTree *>::iterator it = trees.begin(); it != trees.end(); ++it)
   {
      huffmanTree *p = *it;
      }

   while (trees.size() > 0)
   {
      huffmanTree *tree = trees[0];
      delete tree;
      trees.erase(trees.begin());
   }
   return;
}
