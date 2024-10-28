// SPECIFICATION FILE		( SortedType.h )
#ifndef SORTEDLISTBYARRAY_H
#define SORTEDLISTBYARRAY_H

#include "ItemType.h"
#include "UnsortedListByArray.h"


class  SortedListByArray		// declares a class data type
{				
public : 			

  SortedListByArray();

  void MakeEmpty( );             // 8 public member functions
  void InsertItem( ItemType  item ); 	
  void DeleteItem( ItemType  item ); 	

  bool IsFull( ) const;
  bool IsEmpty( ) const;              
  int  GetLength( ) const;  // returns length of list
  void RetrieveItem( ItemType &  item, bool&  found );

  void ResetList( );
  void GetNextItem( ItemType&  item ); 	

  void MergeList(UnsortedListByArray &listone, UnsortedListByArray &listtwo); // Merge two unsored lists into one sored list
  void PrintList() const;

private :
   int length;  
   ItemType info[MAX_ITEM]; 
   int currentPos;
};


#endif