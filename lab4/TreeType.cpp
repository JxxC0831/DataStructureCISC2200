/********************************************************
 * File : TreeType.cpp
 * Date : 10/10/08
 * Description : Impelementation file of TreeType class
 ********************************************************/

#include "TreeType.h"
#include <new>

TreeType::TreeType()
{
   root = NULL;
   
   preQue = NULL;
   postQue = NULL;
   inQue = NULL;
}

TreeType::TreeType(const TreeType& originalTree)
{
   CopyTree(root, originalTree.root);
}

void TreeType::operator=(const TreeType& originalTree)
{
    if (&originalTree == this)
       return;

    Destroy(root);
    CopyTree(root, originalTree.root);
}


void TreeType::CopyTree(TreeNode *&copy, const TreeNode* originalTree)
{

    if (originalTree == NULL)
        copy = NULL;
    else
    {
      copy = new TreeNode;
      copy->info = originalTree->info;
      CopyTree(copy->left, originalTree->left);
      CopyTree(copy->right, originalTree->right);
    }
}


TreeType::~TreeType()
{
   MakeEmpty();  

   if (preQue !=NULL)  delete preQue;
   if (postQue != NULL) delete postQue;
   if (inQue != NULL) delete inQue;
}

void TreeType::Destroy(TreeNode *& tree)
{
   if (tree!= NULL)
   {
     Destroy(tree->left);
     Destroy(tree->right);
     delete tree;
   } 
}

void TreeType::MakeEmpty()
{
   Destroy(root);
   root = NULL;
}



bool TreeType::IsFull() const
{

  TreeNode * location;
  try{
     location = new TreeNode;
     delete location;
     return false;
  }catch( std::bad_alloc e){
    return true;
  }
}


bool TreeType::IsEmpty() const
{
   return root == NULL;

}

int TreeType::GetLength() const
{
    return Count(root);    
}

int TreeType::Count(TreeNode * tree) const
{
   if (tree == NULL)
       return 0;
   else
       return Count(tree->left) + Count(tree->right) +1;
}



void TreeType::RetrieveItem(ItemType & item, bool & found) const
{
    Retrieve(root, item, found);
}


void TreeType::Retrieve(TreeNode* tree, 
              ItemType& item, bool& found) const
{
  if (tree == NULL)   found = false;                     

  else if (item.ComparedTo(tree->info) == LESS)      
    Retrieve(tree->left, item, found);
  else if (item.ComparedTo(tree->info) == GREATER)
    Retrieve(tree->right, item, found);
  else
  {
    item = tree->info;
    found = true;
  }
}   


void TreeType::InsertItem(ItemType item)
{
   Insert(root, item);
}

void TreeType::Insert(TreeNode* & tree, ItemType item)
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item.ComparedTo(tree->info) == LESS)
    Insert(tree->left, item);    
  else 
    Insert(tree->right, item);   
} 

void TreeType::GetPredecessor( TreeNode* tree, ItemType& data)
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

void TreeType::Print(ofstream & output) const
{
   PrintTree(root, output);
}

void TreeType::Print() const
{
   std::cout<<"Binary Search Tree: (in-order)"<<endl;
   PrintTree(root, std::cout);
   std::cout<<endl;
}

void TreeType::PrintTree(TreeNode* tree, ostream& output) const
{
  
  if (tree != NULL)
  {
    PrintTree(tree->left, output);   
    output << tree->info<<"  ";
    PrintTree(tree->right, output);  
  }
}



void TreeType::PreOrder(TreeNode * tree, queue<ItemType>* & preQue)
{

   if (tree != NULL)
   {
      preQue->push(tree->info);
      PreOrder(tree->left, preQue);
      PreOrder(tree->right, preQue);
   } 
}



void TreeType::InOrder(TreeNode * tree, queue<ItemType>*& inQue)
{

   if (tree != NULL)
   {
      InOrder(tree->left, inQue);
      inQue->push(tree->info);      
      InOrder(tree->right, inQue);
   } 
}



void TreeType::PostOrder(TreeNode * tree, queue<ItemType>* & postQue)
{

   if (tree != NULL)
   {
      PostOrder(tree->left, postQue);     
      PostOrder(tree->right, postQue);
      postQue->push(tree->info);       
   } 
}

void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree 
// elements in the desired order.
//the queue should be deleted after using it.
{
  switch (order)
  {
    case PRE_ORDER : preQue = new queue<ItemType>;
                     PreOrder(root, preQue);
                     break;
    case IN_ORDER  : inQue = new queue<ItemType>;
                     InOrder(root, inQue);
                     break;
    case POST_ORDER: postQue = new queue<ItemType>;
                     PostOrder(root, postQue);
                     break;
  }
} 


void TreeType::GetNextItem(ItemType & item, OrderType order, bool& finished)
{
   finished = false;
   switch(order)
   {
     case PRE_ORDER  : item = preQue->front();
                       preQue->pop( );
                      if (preQue->empty())
                       {
                         finished = true;
                         delete preQue;
                         preQue = NULL;
                       }
                      break;
    case IN_ORDER   : item = inQue->front();
                      inQue->pop();
                      if (inQue->empty())
                      {
                        finished = true;
                        delete inQue;
                        inQue = NULL;
                      }
                      break;
    case  POST_ORDER: item = postQue->front();
                      postQue->pop(); 
                      if (postQue->empty())
                      {
                        finished = true;
                         delete postQue;
                        postQue = NULL;
                      }
                      break;

   }
}

// int LeafCount( ) const
//Function Return the number of leaf nodes in the tree
//Precondition: The tree has been initialized.
//Postcondition: The tree has not been changed.
int TreeType::LeafCount() const
{
    return CountLeaf(root);
}

int TreeType::CountLeaf(TreeNode* tree) const
{
    //check if the tree is NULL, if yes, return 0
    if(tree == NULL)
    {
        return 0;
    }
    // check if the tree is a leaf by checking if the left and right is both NULl, if yes, this is a leaf and return 1. 
    if(tree->left == NULL && tree->right == NULL)
    {
        return 1;
    }
    // Recursive function to go to leaf
    return CountLeaf(tree->left)+CountLeaf(tree->right);
}

//Function: Search the tree and print the ancestors of a given node wherethe given item is saved.
//Precondition: The tree has been initialized. The item is in the tree.
//Postcondition The tree has not been changed. Do not print the node itself.
void TreeType::Ancestors(ItemType item)
{
    GetAncestors(root,item);
}

bool TreeType::GetAncestors(TreeNode* tree, ItemType item)
{
    if(tree == NULL)
    {
        return false;
    }
    if(tree->info.ComparedTo(item) == EQUAL)
    {
        return true;
    }
    if(GetAncestors(tree->left,item) || GetAncestors(tree->right,item))
    {
        cout << tree->info << " ";
        return true;
    }

    return false;

}

//Function Delete the node pointed to by tree. This function is similar to the one we discussed in class with one difference, the node having two children is replaced by its immediate successor instead of its predecessor.
//Precondition: The tree has been initialized. The node tree may have zero, one or two children.
//Postcondition:The node tree is no longer in the binary search tree. If tree is a leaf node or has only one non-NULL child node, tree isdeleted; otherwise, the info saved in tree is replaced by itslogical successor and the successor’s node is deleted
void TreeType::GetSuccessor( TreeNode* tree, ItemType& data)
{
    tree = tree->right;// take one step to the right
  while (tree->left != NULL)// allway to the left
    tree = tree->left;
  data = tree->info;
}

void TreeType::DeleteItem(ItemType item)
{
    Delete(root, item);
}

// first, find which node should be deleted.
void TreeType::Delete(TreeNode*& tree, ItemType item)
{
  if (item.ComparedTo(tree->info) == LESS)
     Delete(tree->left, item);   
  else if (item.ComparedTo(tree->info) == GREATER)
     Delete(tree->right, item);  
  else
     DeleteNode(tree);  // Node found
} 

void TreeType::DeleteNode(TreeNode*&  tree)
{
    ItemType data;
    TreeNode* tempPtr;

    tempPtr = tree;

    if ( tree->left == NULL) {
        tree = tree->right;
        delete tempPtr; 
    } 
    else if (tree->right == NULL){
        tree = tree->left;
        delete tempPtr;
    }
    else{
        GetSuccessor(tree, data);
        tree->info = data;
        Delete(tree->right, data);
    }
} 

//Function Swap the left and the right children of every node of the tree
//Precondition:These two trees have been initialized.
//Postcondition The original tree is unchanged. The newTree is the mirror image of the original tree.
void TreeType::Swap(TreeType & newTree)
{
    return Swapfunction(root);
}

void TreeType::Swapfunction(TreeNode* tree)
{
    if(tree != NULL)
    {
        TreeNode* temp = tree->left;
        tree->left = tree->right;
        tree->right = temp;
        Swapfunction(tree->left);
        Swapfunction(tree->right);
    }
}

