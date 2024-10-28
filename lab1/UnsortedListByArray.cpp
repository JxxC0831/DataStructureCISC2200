#include "UnsortedListByArray.h"



UnsortedListByArray::UnsortedListByArray()
{
  length = 0;
}


bool UnsortedListByArray::IsFull() const
{
  return (length == MAX_ITEM);
}

int UnsortedListByArray::GetLength( ) const
{
  return length;
}


bool UnsortedListByArray::IsEmpty() const
{
  return (length == 0);
}



void UnsortedListByArray::InsertItem(ItemType item)
// Post: item is in the list.
{
  info[length] = item;
  length++;
}



void UnsortedListByArray::RetrieveItem(ItemType& item, bool& found) 
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item; 
//       otherwise, item is unchanged. 
{
  bool moreToSearch;
  int location = 0;
  found = false;
  moreToSearch = (location < length);
  while (moreToSearch && !found) 
  {
    switch (item.ComparedTo(info[location]))
    { case LESS    : 
      case GREATER : location++;
                     moreToSearch = (location < length);
                     break;
      case EQUAL   : found = true;
                     item = info[location];
                     break;
    }
  }
}


void UnsortedListByArray::DeleteItem ( ItemType  item ) 
// Pre: item’s key has been inititalized.
//	One and only one element in the list has a key that matches item’s.
// Post: No element in the list has a key that matches item’s.
{    
  int  location  =  0 ;

  while (item.ComparedTo (info[location])  !=  EQUAL)
         location++;
  // move last element into position where item was located

  info [location] = info [length - 1 ] ;
  length-- ; //the length of the list is decreased
}


void UnsortedListByArray::MakeEmpty()
// Pre:  N/A   
// Post: the list is empty
{
   length = 0;
}



void UnsortedListByArray::ResetList ( )  
// Pre:  List has been inititalized.
// Post: Current position is prior to first element.
{    
  currentPos  =  -1 ;
}


void UnsortedListByArray::GetNextItem ( ItemType&  item )  
// Pre:  List has been initialized. Current position is 
//       defined. 
//       Element at current position is not last in list.
// Post: Current position is updated to next position.
// 	  item is a copy of element at current position.
{
  currentPos++  ;
  item = info [currentPos] ;
}

bool UnsortedListByArray::NewInsertItem(ItemType newItem)
// Pre: List has been initialized.
// Post: List should have just one copy of the new item.
{
    for(int i = 0; i < length; i++)
    {
        if(newItem.ComparedTo(info[i]) == EQUAL)
        {
            return false;
        }

    }
    //add new value
    info[length] = newItem;
    length++;
    return true;
}

void UnsortedListByArray::DeleteAllItems(ItemType item)
// Pre:List has been initialized and is not empty. The list has at least one copyof the item.
// Post: List does not have any copies of the item.
{
    int i = 0;
    while(i<length)
    {
        if(item.ComparedTo(info[i]) == EQUAL)
        {
            for(int j = i; j < length; j++)
            {
                info[j] = info[j+1];
            }
            length--;
        }
        else i++;
    }
}

void UnsortedListByArray::SplitList(ItemType item, UnsortedListByArray &listOne, UnsortedListByArray &listTwo)
// Pre: List has been initialized and is not empty. listOne and listTwoare initialized but empty.
// Post: listOne contains all the items of list whose keys are less thanor equal to item’s key;listTwo contains all the items of the list whose keys are greaterthan the item's key
{
    for(int i=0; i < length; i++)
    {
        if(item.ComparedTo(info[i]) == LESS || item.ComparedTo(info[i]) == EQUAL)
        {
            listTwo.InsertItem(info[i]);
        }
        else
        {
            listOne.InsertItem(info[i]);
        }
    }


}


void UnsortedListByArray::PrintList() const
// Pre: List has been initialized.
// Post: List has been printed to the screen.
{
    for(int i = 0; i < length; i++)
    {
        info[i].Print();
        cout << " ";
    }
}
