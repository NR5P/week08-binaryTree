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
#include <deque>

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
   typedef custom::pair<std::string, float> PairType;
   typedef BNode<PairType> NodeType;

public:
   huffmanTree()
       : pRoot(nullptr)
   {
   }
   huffmanTree(const std::string &value, float frequency)
   {
      pRoot = new NodeType(custom::pair<std::string, float>(value, frequency));
   }
   huffmanTree(const PairType &pair)
   {
      pRoot = new NodeType(pair);
   }
   huffmanTree(NodeType *root)
   {
      pRoot = root;
   }
   ~huffmanTree()
   {
      if (pRoot != nullptr)
      {
         deleteBTree(pRoot);
         pRoot = nullptr;
      }
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
      return 0;
   }

   void mergeLeft(huffmanTree *oldTree)
   {
      addLeft(pRoot, oldTree->pRoot);
      //since we took ownership of the root
      //we don't want destructor for huffmanTree
      //to delete our child nodes. So set it to null.
      oldTree->pRoot = nullptr;
   }

   void mergeRight(huffmanTree *oldTree)
   {
      addRight(pRoot, oldTree->pRoot);
      //since we took ownership of the root
      //we don't want destructor for huffmanTree
      //to delete our child nodes. So set it to null.
      oldTree->pRoot = nullptr;
   }

   std::string getHuffmanCode(std::string value)
   {
      std::string code;
      getHuffmanCode(pRoot, code, value);
      return code;
   }

private:
   NodeType *pRoot;
   //I'm SURE there's a better way to do this. seems way to complicated.
   bool getHuffmanCode(NodeType *pNode, std::string &code, string value)
   {
      if (pNode == nullptr)
         return false;

      if (pNode->data.first == value)
         return true; //found it!

      if (pNode->pLeft != nullptr)
      {
         code.push_back('0');
         if (getHuffmanCode(pNode->pLeft, code, value))
            return true;
         //get rid of the value we added
         code.pop_back();
      }

      if (pNode->pRight != nullptr)
      {
         code.push_back('1');
         if (getHuffmanCode(pNode->pRight, code, value))
            return true;
         code.pop_back();
      }

      return false;
   }
};

void getTwoLowest(std::vector<huffmanTree *> trees, huffmanTree *&lowest, huffmanTree *&secondLowest)
{
   for (std::vector<huffmanTree *>::iterator it = trees.begin(); it != trees.end(); ++it)
   {
      huffmanTree *p = *it;

      if (secondLowest == nullptr || (p->getValue() < secondLowest->getValue()))
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

std::vector<huffmanTree::PairType> readPairsFromFile(const string &fileName)
{
   std::ifstream infile(fileName);
   std::string line;
   std::vector<huffmanTree::PairType> pairs;

   while (std::getline(infile, line))
   {
      std::istringstream iss(line);
      std::string word;
      float frequency;
      if (!(iss >> word >> frequency))
      {
         break;
      } // error
      pairs.push_back(huffmanTree::PairType(word, frequency));
   }
   return pairs;
}
/*
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
   return trees;
}
*/

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string &fileName)
{
   //get the pairs, rather than build trees immediately so we have
   //the original values and order
   std::vector<huffmanTree::PairType> pairs = readPairsFromFile(fileName);

   //then convert the pairs into trees. I honestly wouldn't do this normally,
   //because you could start with just the pairs. But the description of the
   //assignment says to make a class to encapsulate the btree and to start
   //with trees, then combine them until there is one. So we'll do that.
   std::vector<huffmanTree *> trees;
   for (std::vector<huffmanTree::PairType>::iterator it = pairs.begin(); it != pairs.end(); ++it)
   {
      trees.push_back(new huffmanTree(*it));
   }

   //now loop through, getting the two lowest by value, and combine them until
   //there's only one tree left
   huffmanTree *pLowest = nullptr;
   huffmanTree *pSecondLowest = nullptr;

   while (trees.size() > 1)
   {
      getTwoLowest(trees, pLowest, pSecondLowest);

      huffmanTree *pNewTree = new huffmanTree("", pLowest->getValue() + pSecondLowest->getValue());
      pNewTree->mergeLeft(pLowest);
      pNewTree->mergeRight(pSecondLowest);

      //remove the two old trees from the list
      std::vector<huffmanTree *>::iterator it = trees.begin();
      while (it != trees.end())
      {
         if ((pLowest != nullptr) && (*it == pLowest))
         {
            //replace the lowest with the new tree
            *it = pNewTree;
            delete pLowest;
            pLowest = nullptr;
         }
         else if ((pSecondLowest != nullptr) && (*it == pSecondLowest))
         {
            //erase this one.
            it = trees.erase(it);
            delete pSecondLowest;
            pSecondLowest = nullptr;
         }
         else
         {
            ++it;
         }
      }
   }

   huffmanTree *finalTree = trees[0];

   //TODO: print the results
   for (std::vector<huffmanTree::PairType>::iterator it = pairs.begin(); it != pairs.end(); ++it)
   {
      std::cout << it->first << " = " << finalTree->getHuffmanCode(it->first) << std::endl;
   }

   deleteTrees(trees);
}
