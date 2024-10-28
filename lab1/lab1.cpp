/*
    @Lab1
    @Author: Jiaxuan Cao
    @Last Modify time: Oct, 2nd
    @Know Bug: None    
*/

#include <iostream>
#include <string>
#include <sstream>
#include "UnsortedListByArray.h"
using namespace std;

int main(){
    UnsortedListByArray list, newlist, listOne, listTwo;
    ItemType item, item2;
    string input, word;

    cout << "Please type a sequence of strings with a word repeated at least three times, please use white space as the delimiter:" << endl;
    getline(cin, input);

    stringstream ss(input);
    while (ss >> word) {
        item.Initialize(word);
        list.InsertItem(item);
    }
    cout << "You typed: ";
    list.PrintList();
    cout << endl;
    cout <<endl;

    // Call the old InsertItem function
    cout << "Call the old insert item function:" << endl;
    cout <<endl;
    cout << "The list created: " << endl;
    list.PrintList();
    cout << endl;
    cout << endl;

    // Call the old DeleteItem function
    cout << "Call the old Delete Item function:" << endl;
    item.Initialize("is"); 
    list.DeleteItem(item);
    cout << "After delete the repeated word: " << endl;
    list.PrintList();
    cout << endl;
    cout << endl;

    // Call the new DeleteAllItems function
    cout << "Call the new DeleteAllItems function:" << endl;
    list.DeleteAllItems(item);
    cout << "After delete all repeated words: " << endl;
    list.PrintList();
    cout << endl;
    cout << endl;

    // Call the new insert item function 
    cout << "Call the new insert item function to insert all words into a new list again: " << endl;
    stringstream ss2(input);
    while (ss2 >> word) {
        ItemType item2;
        item2.Initialize(word);
        newlist.NewInsertItem(item2);
    }
    cout << "The listed created: " << endl;
    newlist.PrintList();
    cout << endl;
    cout << endl;

    // long list
    string input2;
    cout << "The long list is " << endl;
    UnsortedListByArray longlist;
    getline(cin, input2);
    stringstream ss3(input2);
    while (ss3 >> word) {
        ItemType item3;
        item3.Initialize(word);
        longlist.NewInsertItem(item3);
    }
    cout <<endl;
    cout << endl;


    // split list
    ItemType item4;
    string splitchar;

    // split character
    cout << "Split with ";
    cin >> splitchar;
    
    item4.Initialize(splitchar);
    cout << "After split with item :" << splitchar << endl;
    longlist.SplitList(item4, listOne, listTwo);
    
    //list one 
    cout << "List one is: ";
    listOne.PrintList();
    cout << endl;
    cout << endl;

    //list two
    cout << "List two is: ";
    listTwo.PrintList();
    cout << endl;
    cout << endl;

    // original list
    cout << "After split, original list is: " << endl;
    longlist.PrintList();





    return 0;


}