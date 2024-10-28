/*
@Lab4.cpp with Leaf Count. Find ancestors of a node, delete a node from the tree, and swap the tree.
@Author:Jiaxuan Cao
@Last Modify Time: Nov 21.
@Know bug: None
*/
#include <iostream>
#include "TreeType.h"
#include "ItemType.h"
using namespace std;

int main(){
    TreeType tree;
    ItemType item;
    item.Initialize(1);
    tree.InsertItem(item);
    item.Initialize(0);
    tree.InsertItem(item);
    item.Initialize(10);
    tree.InsertItem(item);
    item.Initialize(3);
    tree.InsertItem(item);
    item.Initialize(2);
    tree.InsertItem(item);
    item.Initialize(12);
    tree.InsertItem(item);
    item.Initialize(11);
    tree.InsertItem(item);
    item.Initialize(5);
    tree.InsertItem(item);

    //Print out the tree we have now
    tree.Print();
    cout << endl;

    // LeafCount
    cout << "Number of leaf nodes: " << tree.LeafCount() << endl << endl;

    // Find the Ancestors
    ItemType key;
    key.Initialize(5); // define the key to find the ancestors
    cout << "Ancestors of the node " << key <<": ";
    tree.Ancestors(key);
    cout << endl;

    // delete
    ItemType deleteKey;
    deleteKey.Initialize(10);// define the key to delete
    tree.DeleteItem(deleteKey);
    cout << "Delete " << deleteKey << " from the tree" << endl;
    tree.Print();
    cout << endl;

    // Swap
    cout << "Swap the tree" << endl;
    tree.Swap(tree);
    cout << "Print the tree after swap:" <<endl;
    tree.Print();
    



    return 0;
}