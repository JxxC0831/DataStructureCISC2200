#include "SortedListByArray.h"


SortedListByArray::SortedListByArray()
{
  length = 0;
}


bool SortedListByArray::IsFull() const
{
  return (length == MAX_ITEM);
}

int SortedListByArray::GetLength( ) const
{
  return length;
}


bool SortedListByArray::IsEmpty() const
{
  return (length == 0);
}

void SortedListByArray::InsertItem(ItemType item) 
{
   bool moreToSearch; 
   int location = 0;
   moreToSearch = (location < length);
   while (moreToSearch)
   {
      switch(item.ComparedTo(info[location]))
      {
         case LESS : moreToSearch = false; break;
         case GREATER : location++;
                        moreToSearch = (location < length);
                        break;
        case EQUAL : break;
      }
   }

   for ( int index = length; index > location; index--)
        info[index] = info[index-1];

   info[location] = item;
   length++;
}


void SortedListByArray::RetrieveItem(ItemType& item, bool& found) 
// Pre:  Key member(s) of item is initialized. 
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item; 
//       otherwise, item is unchanged. 
{
  int midPoint;
  int first =0;
  int last = length -1;
  
  bool moreToSearch = (first <= last);
  found = false;
  while (moreToSearch && !found) 
  {
    midPoint = (first+last)/2;
    switch (item.ComparedTo(info[midPoint]))
    { 
      case LESS    : last = midPoint -1;
                     moreToSearch = (first <= last);
                     break;
      case GREATER : first = midPoint +1;
                     moreToSearch = (first <= last);
                     break;
      case EQUAL   : found = true;
                     item = info[midPoint];
                     break;
    }
  }
}


void SortedListByArray::DeleteItem(ItemType item) 
// Pre: item’s key has been inititalized.
//	One and only one element in the list has a key that matches item’s.
// Post: No element in the list has a key that matches item’s.
{
   int location = 0;
   while(item.ComparedTo(info[location])!= EQUAL)
       location++;

   for ( int index = location +1; index < length; index++)
        info[index-1] = info[index];
   
   length--;
}


void SortedListByArray::MakeEmpty()
// Pre:  N/A   
// Post: the list is empty
{
   length = 0;
}



void SortedListByArray::ResetList ( )  
// Pre:  List has been inititalized.
// Post: Current position is prior to first element.
{    
  currentPos  =  -1 ;
}


void SortedListByArray::GetNextItem ( ItemType&  item )  
// Pre:  List has been initialized. Current position is 
//       defined. 
//       Element at current position is not last in list.
// Post: Current position is updated to next position.
// 	  item is a copy of element at current position.
{
  currentPos++  ;
  item = info [currentPos] ;
}



void SortedListByArray::MergeList(UnsortedListByArray &listone, UnsortedListByArray &listtwo)
// Pre: List has been initialized. listOne and listTwo have been initialized
// Post: List contains all items from listOne and listTeo, if there are duplicates items, only keep one copy in the merged list. 
{
  ItemType item;
  listone.ResetList(); // reset the listone

  for(int i=0; i < listone.GetLength(); i++)
  {
    listone.GetNextItem(item); // get the next item from listone

    int midPoint;
    int first = 0;
    int last = length-1;
    int location = length; 
    
    bool found = false;
    if(length == 0)
    {
      info[0] = item;
      length++;
    }
    else{
      while (first <= last && !found) 
      {
        midPoint = (first + last) / 2;
        switch (item.ComparedTo(info[midPoint]))
        { 
          case LESS    : last = midPoint -1;
                        found = false;
                        break;
          case GREATER : first = midPoint +1;
                        found = false;
                        break;
          case EQUAL   : found = true;
                        break;
        }
      }
      location = first;
    }
    if(!found)
      {
        for (int index = length; index > location; index--)
        {
        info[index] = info[index-1];
        }

        info[location] = item;
        length++;
      }
  }

  listtwo.ResetList(); // reset the listtwo

  for(int i=0; i < listtwo.GetLength(); i++)
  {
    listtwo.GetNextItem(item); // get the next item from listtwo

    int midPoint;
    int first = 0;
    int last = length-1;
    int location = -1;
    
    
    bool found = false;
    while (first <= last && !found) 
    {
      midPoint = (first+last)/2;
      switch (item.ComparedTo(info[midPoint]))
      { 
        case LESS    : last = midPoint -1;
                      found = false;
                      break;
        case GREATER : first = midPoint +1;
                      found = false;
                      break;
        case EQUAL   : found = true;
                      break;
        }
        location = first;
    }

    if(!found)
    {
      for (int index = length; index > location; index--)
        info[index] = info[index-1];

      info[location] = item;
      length++;
    }
  }
  length--; // clear the last item: space
}


void SortedListByArray::PrintList() const
// Pre: List has been initialized.
// Post: List has been printed to the screen.
{
    for(int i = 0; i < length; i++)
    {
        info[i].Print();
        cout << " ";
    }
}