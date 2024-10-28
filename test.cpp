#include <iostream>
#include <string>
#include <stack>
#include <cctype> // For isdigit function

using namespace std;

bool CheckErrors(string &input);
int isOperator(char c);
int priority(char c);
string InfixToPostfix(string &input);
int Calculate(string &input);

int main() {
    string input;
    cout << "Please type the expression in the format of Infix Notation: " << endl;
    getline(cin, input);

    // Assuming CheckErrors function is correctly implemented
    if (!CheckErrors(input)) {
        cout << "Error in input expression." << endl;
        return 1;
    }

    string postfix = InfixToPostfix(input);
    cout << "The postfix notation: " << postfix << endl;

    int result = Calculate(postfix);
    cout << "The result: " << result << endl;

    return 0;
}

bool CheckErrors(string &input) {
    // Implementation of error checking logic
    // Placeholder - Implement as needed
    return true;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

string infixToPostfix(string &input) {
    stack<char> opStack;
    string postfix = "";
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (isdigit(c)) {
            postfix += c;
            // Check if next character is a digit
            while (i + 1 < input.length() && isdigit(input[i + 1])) {
                postfix += input[++i];
            }
            postfix += ' '; // Add space to separate numbers
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop(); // Remove '(' from stack
        } else if (isOperator(c)) {
            while (!opStack.empty() && priority(opStack.top()) >= priority(c)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

int Calculate(string &postfix) {
    stack<int> valStack;
    string number = "";
    for (size_t i = 0; i < postfix.length(); ++i) {
        char c = postfix[i];
        if (isdigit(c)) {
            number += c;
        } else if (c == ' ' && !number.empty()) {
            valStack.push(atoi(number.c_str()));
            number = "";
        } else if (isOperator(c)) {
            int val2 = valStack.top(); valStack.pop();
            int val1 = valStack.top(); valStack.pop();
            switch (c) {
                case '+': valStack.push(val1 + val2); break;
                case '-': valStack.push(val1 - val2); break;
                case '*': valStack.push(val1 * val2); break;
                case '/': valStack.push(val1 / val2); break;
            }
        }
    }
    return valStack.top();
}