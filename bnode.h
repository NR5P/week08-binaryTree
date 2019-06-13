#ifndef BNODE_H
#define BNODE_H

#include <iostream>

using namespace std;

template<typename T>
struct BNode {
    T data;
    BNode<T> *pLeft;
    BNode<T> *pRight;
    BNode<T> *pParent;
    BNode() : data(0), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {} 
    BNode(T t) : data(t), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {} 
};

/*
ads a node to the left of the current node. takes a template variable as a parameter,
a new node will be allocated. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addLeft(BNode<T> *pNode, const T &t) {
    // create a new node to add
    BNode<T> *newNode = new (nothrow) BNode<T>(t);

    if (newNode == nullptr) 
        throw "ERROR: unable to allocate";

    // put to left of the pnode
    pNode->pLeft = newNode;

    // give the node a parent
    newNode->pParent = pNode;
}

/*
ads a node to the left of the current node. takes a BNode * as a parameter,
the passed node will be used. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addLeft(BNode<T> *pNode, BNode<T> *pAdd) {
    pNode->pLeft = pAdd;
    pAdd->pParent = pNode;
}

/*
ads a node to the right of the current node. takes a template variable as a parameter,
a new node will be allocated. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addRight(BNode<T> *pNode, const T &t) {
    // create a new node to add
    BNode<T> *newNode = new (nothrow) BNode<T>(t);

    if (newNode == nullptr) 
        throw "ERROR: unable to allocate";

    // put to left of the pnode
    pNode->pRight = newNode;

    // give the node a parent
    newNode->pParent = pNode;
}

/*
ads a node to the right of the current node. takes a BNode * as a parameter,
the passed node will be used. pLeft of the current node will point to the new node,
and pParent of the new node will point to the current node. 
*/
template<typename T>
void addRight(BNode<T> *pNode, BNode<T> *pAdd) {
    pNode->pRight = pAdd;
    pAdd->pParent = pNode;

}

/*
Takes a BNode as a parameter makes a copy of the tree. The return value is the 
newly copied tree. This is a recursive function.
*/
template<typename T>
BNode<T>* copyBTree(const BNode<T> *pNode) {
    if (pNode == nullptr)
        return nullptr;

    BNode<T> *newTree = new (nothrow) BNode<T>(pNode->data);
    if (newTree == nullptr)
        throw "ERROR: could not allocate";
    newTree->pLeft = copyBTree(pNode->pLeft);
    if (newTree->pLeft = copyBTree(pNode->pLeft)) {
        newTree->pLeft->pParent = newTree;
    }
    newTree->pRight = copyBTree(pNode->pRight);
    if (newTree->pRight = copyBTree(pNode->pRight)) {
        newTree->pRight->pParent = newTree;
    }
    return newTree;
}

/*
Takes a BNode as a parameter and deletes all the children and itself. 
This is a recursive function.
*/
template<typename T>
void deleteBTree(BNode<T> *pNode) {
    /* not for entire tree WOOPS
    BNode<T> pIter = pHead; // make a new iter node that points to head at first
    if (pIter->pLeft == nullptr && pIter->pLeft == nullptr) {
        if (pIter->pParent == nullptr) {
            delete pIter;
            return;
        }
        BNode<T> pToDelete = pIter;
        pIter = pIter->pParent;
        delete pToDelete;
        deleteBTree(pIter);
    } else if(pIter->pLeft != nullptr) {
        deleteBTree(p->Left);
    } else {
        deleteBTree(p->right);
    }
    */
    if (pNode->pLeft != nullptr)
        deleteBTree(pNode->pLeft);
    if (pNode->pRight != nullptr)
        deleteBTree(pNode->pRight);
    delete pNode;
}

/*
Takes a constant BNode * as a parameter and displays the tree under 
the passed parameter. This is a recursive function traversing the tree in LVR order. 
A single space will be displayed after every element.
*/
template<typename T>
std::ostream &operator<<(std::ostream &out, BNode<T> *t) {
//    displayLVR(out, t);
    out << t->pLeft << t->data << " " << t->pRight;
    return out;
}

/*
template<typename T>
void displayLVR(std::ostream &out, const BNode<T> *pHead) {
    if (pHead != nullptr) {

    }
    displayLVR(out, pHead->pLeft);
    cout << pHead->data << " ";
    displayLVR(out, pHead->pRight);
}
*/

template<typename T>
int sizeBTree(const BNode<T> *pRoot) {
    int size = 1;
    if (!pRoot) 
        return size;
    if (pRoot->pLeft != nullptr) {
        size += sizeBTree(pRoot->pLeft);
    } 
    if (pRoot->pRight != nullptr) {
        size += sizeBTree(pRoot->pRight);
    }
    return size;
}


#endif