#ifndef BNODE_H
#define BNODE_H

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

#endif