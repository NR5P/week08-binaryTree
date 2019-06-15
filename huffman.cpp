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

void getTwoLowest(std::vector<huffmanTree *> trees, huffmanTree *&lowest, huffmanTree *&secondLowest)
{

   for (std::vector<huffmanTree *>::iterator it = trees.begin(); it != trees.end(); ++it)
   {
      huffmanTree *p = *it;

      if (secondLowest == nullptr || p->getValue() < secondLowest->getValue())
      {
         if (lowest == nullptr || p->getValue() < lowest->getValue())
         {
            huffmanTree *pOldLowest = lowest;
            lowest = p;

            if (pOldLowest != nullptr)
            {
               secondLowest = pOldLowest;
            }
         }
         else
         {
            secondLowest = p;
         }
      }
   }
}

void deleteTrees(std::vector<huffmanTree *> trees)
{
   while (trees.size() > 0)
   {
      huffmanTree *tree = trees[0];
      delete tree;
      trees.erase(trees.begin());
   }
}

std::vector<huffmanTree *> readTreesFromFile(const string &fileName)
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
}

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string &fileName)
{

   std::vector<huffmanTree *> trees = readTreesFromFile(fileName);

   huffmanTree *pLowest;
   huffmanTree *pSecondLowest;

   while (trees.size() > 1)
   {
      getTwoLowest(trees, pLowest, pSecondLowest);

      //TODO: now we have to combine the two lowest into a new tree, and remove
      //the two from "trees", and add the new one. (or collapse one into the other)
      //this needs to happen until there is only one tree left in trees.

      //combining the trees might be tricky, because only "leaf" nodes are "real".
      //probably the "huffmanTree.getValue" method isn't that useful here, because
      //the value should be calculated from the leaves under it?
   }

   //TODO: print the results

   deleteTrees(trees);
}
