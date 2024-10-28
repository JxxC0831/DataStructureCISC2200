/*
    @Lab2
    @Author: Jiaxuan Cao
    @Last Modify time: Oct, 16
    @Know Bug: None    
*/
#include <iostream>
#include <string>
#include <sstream>
#include "SortedListByArray.h"
using namespace std;

int main()
{
    UnsortedListByArray listone;
    UnsortedListByArray listtwo;
    ItemType item;
    
    //initialize two list
    item.Initialize(0);
    listone.InsertItem(item);
    item.Initialize(1);
    listone.InsertItem(item);
    item.Initialize(10);
    listone.InsertItem(item);
    item.Initialize(3);
    listone.InsertItem(item);

    item.Initialize(12);
    listtwo.InsertItem(item);
    item.Initialize(10);
    listtwo.InsertItem(item);
    item.Initialize(5);
    listtwo.InsertItem(item);





    cout << "List one: ";
    listone.PrintList();
    cout << endl;
    cout << "List two: ";
    listtwo.PrintList();
    cout << endl;


    SortedListByArray Mergedlist;//merhe two list into one sorted list
    Mergedlist.MergeList(listone, listtwo);
    cout << "Merged list: ";
    for (int i = 0; i < Mergedlist.GetLength(); i++)
    {
        Mergedlist.GetNextItem(item);
        item.Print();
        cout << " ";
    }
    cout << endl;






    return 0;
}