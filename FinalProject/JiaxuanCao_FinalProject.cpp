/*********************
@   1. This program work as a calculator which can do four basiccalculations. 
    2. The input of this calculator is in the format of infix notation, and the output is in the format of postfix notation. it also check the input expression to see if there is a syntax exception or semantic exception.
    3. the program will calculate the result of the expression, calcultaion is based on the postfix notation.
@Author: Jiaxuan Cao
@Last modify Time: Dec 15 2023
@Know bugs: none
*********************/
#include <iostream>
#include <string>
#include <stack>
#include <exception>

using namespace std;

bool CheckErrors(string &input);
bool isOprand(char c);
int isOperator(char c);
int priority(char c);
string infixToPostfix(string &input);
int Calculate(string &postfix);

//create two Exception classes for syntax exception and semantic exception
class SyntaxException : public exception
{
    public:
        const char* what() const throw()
        {
            return "Syntax Error";
        }
};

class SemanticException : public exception
{
    public:
        const char* what() const throw()
        {
            return "Semantic Error";
        }
};


int main()
{
    // input the infix expression
    string input;
    cout << "Please type the expression in the format of Infix Notation : " << endl;
    getline(cin,input);

    // check if there is a syntax exception or semantic exception using try...catch...
    try
    {
        if(CheckErrors(input))
        {
            // convert the infix notation to postfix notation
             string postfix = infixToPostfix(input);
             cout << "The postfix notation :" << postfix << endl;
   
            // calculate the result of the expression
             int result = Calculate(postfix);
            cout << "The result : " << result << endl;
        }
    }
    catch (SyntaxException &e)
    {
        cout << e.what() << endl;
        return 0;
    }
    catch (SemanticException &e)
    {
        cout << e.what() << endl;
        return 0;
    }
    
   return 0;
}

// check if there is a syntax exception or semantic exception
bool CheckErrors(string &input)
{
    // check the syntax exception
    stack<char> ch;
    // check if there is a syntax exception(which means there is a parenthesis that is not closed)
    for(int i = 0; i < input.length(); i++)
    {
        // check the parethesis using stack
        if (input[i] == '(')
        {
            ch.push(input[i]);
        }
        else if (input[i] == ')')
        {
            // if there is no '(' in the stack, then there is a syntax exception
            if (ch.empty() || ch.top() != '(')
            {
                throw SyntaxException();
                return false;
            }
            ch.pop();
        }
        // check the syntax exception(which means there is a operator that is not followed by an operand)
        else if (isOperator(input[i]))
        {
            // check if the operator is at the beginning or the end of the expression
            if ((i == 0 || i == input.length()-1) && isOperator(input[i]))
            {
                throw SyntaxException();
                return false;
            }
            // check if there is a operator followed by another operator
            else if (i < input.length() - 1 && isOperator(input[i+1]))
            {
                throw SyntaxException();
                return false;
            }
            else if(input[i] == '/' && input[i + 1] == '0')
            {
                throw SemanticException();
                return false;
            }
        }
    }
    return true;
}

// check if the character is an operand
// return true if it is an operand, return false if it is not an operand
bool isOprand(char c)
{
    return (c >= '0' && c <= '9');
}

// check if the character is an operator
// return true if it is an operator, return false if it is not an operator
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// check the priority of the operator
// return 1 if c is + or -
// return 2 if c is * or /
// return -1 if c is not an operator
int priority(char c)
{
    // return 1 if c is + or - 
    if (c == '+' || c == '-')
        return 1;
    // return 2 if c is * or /
    if (c == '*' || c == '/')
        return 2;
    // return -1 if c is not an operator
    return -1;
}


//convdert infix to postfix
string infixToPostfix(string &input)
{
    stack<char> ch;
    string postfix = ""; //set string postfix is empty
    // algorithm:
    // 1. Scan the given input from left to right,
    for( int i = 0; i < input.length(); i++)
    {
        // 2. For the next element in the input.
        //a. If it is an operand, output it.
        if (isOprand(input[i]))
        {
            postfix += input[i];
            // Check next character in input is an operand
            while (i + 1 < input.length() && isOprand(input[i + 1])) {
                postfix += input[++i];
            }
            postfix += ' '; // Add space to separate numbers
        }
        //b. If it is opening parenthesis, push it on the stack.
        else if (input[i] == '(')
        {
            ch.push(input[i]);
        }
        //c. If it is an operator
        else if (isOperator(input[i]))
        {
            while (!ch.empty() && priority(ch.top()) >= priority(input[i])) {
                postfix += ch.top();
                ch.pop();
            }
            ch.push(input[i]);
        }
        //     d. If it is a closing parenthesis, pop operators from the stack and output them until an opening parenthesis is encountered. Pop and discard the opening p arenthesis.
        else if (input[i] == ')')
        {
            while (ch.top() != '(')
            {
                postfix += ch.top();
                ch.pop();
            }
            ch.pop();
        }
    }
    // 3. If there are more inputs, go to step2, else unstack the remaining operators to output
    while (!ch.empty())
    {
        postfix += ch.top();
        ch.pop();
    }
    
    return postfix;
}

// calculate the result of the expression
// return the result
int Calculate(string &postfix)
{
    stack<int> numStack;
    // algorithm:
    // 1. Scan the given input from left to right,
    // 2. For the next element in the input.
    for(int i = 0;i < postfix.length(); i++)
    {
        //     a. If it is an operand, push it on the stack.
        if(isOprand(postfix[i]))
        {
            int operand = 0;
            // Check next character in input is an operand, and convert it to integer
            // it has to be a integer, so we need to convert it to integer
            // also, it could not beyond the length of the string
			while (isOprand(postfix[i]) && (i < postfix.length())){
				operand = (operand * 10) + (postfix[i] - '0');// convert the character to integer
				i++;// move to next character
			}
            i--;// revert the index to correct position
			numStack.push(operand);
        }
        //     b. If it is an operator, then
        else if(isOperator(postfix[i]))
        {
            //         i. Pop the top two elements from the stack. num2 has to be the top element and num1 has to be the second element.
            int num2 = numStack.top(); 
            numStack.pop();
            int num1 = numStack.top();
            numStack.pop();
            //         ii. Perform the operation on the two elements.
            //         iii. Push the result back on the stack.
            switch (postfix[i]) {
                case '+': 
                    numStack.push(num1 + num2); 
                    break;
                case '-': 
                    numStack.push(num1 - num2); 
                    break;
                case '*': 
                    numStack.push(num1 * num2); 
                    break;
                case '/': 
                    numStack.push(num1 / num2); 
                    break;
            }
        }
        else if (postfix[i] == ' ')
        {
            // if there is a space, then move to next character
            continue; 
        }
    } 
    return numStack.top();
}