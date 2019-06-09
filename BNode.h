#ifndef BNODE_H
#define BNODE_H

#include <iostream>

template<typename T>
struct BNode {
    T data;
    BNode *pLeft;
    BNode *pRight;
    BNode *pParent;
    BNode() : pLeft(nullptr), pRight(nullptr), pParent(nullptr) {} 
    BNode(T &t) : data(t), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {} 
};

/*
ads a node to the left of the current node. takes a template variable as a parameter,
a new node will be allocated. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addLeft(const T &t, BNode<T> *pNode) {

}

/*
ads a node to the left of the current node. takes a BNode * as a parameter,
the passed node will be used. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addLeft(BNode<T> *pNode, BNode<T> *pToAdd) {

}

/*
ads a node to the right of the current node. takes a template variable as a parameter,
a new node will be allocated. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addRight(const T &t, BNode<T> *pNode) {

}

/*
ads a node to the right of the current node. takes a BNode * as a parameter,
the passed node will be used. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addRight(BNode<T> *pNode, BNode<T> *pToAdd) {

}

/*
Takes a BNode as a parameter makes a copy of the tree. The return value is the 
newly copied tree. This is a recursive function.
*/
template<typename T>
BNode<T>* copyBTree(BNode<T> *pHead) {

}

/*
Takes a BNode as a parameter and deletes all the children and itself. 
This is a recursive function.
*/
template<typename T>
void deleteBTree(BNode<T> *pHead) {

}

/*
Takes a constant BNode * as a parameter and displays the tree under 
the passed parameter. This is a recursive function traversing the tree in LVR order. 
A single space will be displayed after every element.
*/
template<typename T>
std::ostream &operator<<(std::ostream &out, BNode<T> *t) {

}



#endif