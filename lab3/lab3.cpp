/*
    @Lab3: this lab is to check if the brackets in the string are matched
    @Author: Jiaxuan Cao
    @Date: Oct 30, 2023
    @Last Modified: Oct 30, 2023
    @Known Bugs: none
*/
#include <iostream>
#include <stack> // include stack library!!
#include <string>
using namespace std;

bool CheckIfMatched(string &input)
{
    stack <char> mystack; //Formula for stack

    //use loop to check every item in the string
    for(int i=0; i < input.size(); i++)
    {
        if(input[i] == '(' || input[i] == '{' || input[i] == '[') // if the item is a left bracket, then push it into the stack
        {
            mystack.push(input[i]);
        }

        else if(input[i] == ')' || input[i] == '}' || input[i] == ']') // we need to ignore the useless character. if it is a right bracket, then check if it is matched with the top of the stack
        {
            if(mystack.empty()) // first, we need to check if the stack is empty, if it is empty, then return false
            {
                return false;
            }

            // if the stack is not empty, then check if the right bracket is matched with the top of the stack(left bracket)
            // if it is not matched, then return false
            if(input[i] == ')' && mystack.top() != '(' || input[i] == '}' && mystack.top() != '{' || input[i] == ']' && mystack.top() != '[')
            {
                return false;
            }
            
            else
                mystack.pop();// if it is matched, then pop the top of the stack
        }
    }
   
    return mystack.empty();// if the stack is empty, then return true, else return false
}

int main()
{
    string input;
    
    cout << "Enter a string: ";
    getline(cin,input); // get the string from the user

    if(CheckIfMatched(input))
    {
        cout << "The string is matched" << endl;
    }
    else
    {
        cout << "The string is not matched" << endl;
    }
       
  



    return 0;
}