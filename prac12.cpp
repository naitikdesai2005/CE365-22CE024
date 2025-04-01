#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

// Function to evaluate a simple binary expression
int evaluate(int a, char op, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0; // Avoid division by zero
    }
    return 0;
}

// Function to perform constant folding
string optimizeExpression(string expr) {
    stringstream ss(expr);
    vector<string> tokens;
    string token;

    // Tokenizing the input expression
    while (ss >> token) {
        tokens.push_back(token);
    }

    vector<string> optimized;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i + 2 < tokens.size() && isdigit(tokens[i][0]) && isdigit(tokens[i + 2][0])) {
            int num1 = stoi(tokens[i]);
            char op = tokens[i + 1][0];
            int num2 = stoi(tokens[i + 2]);

            // Evaluate the constant expression
            int result = evaluate(num1, op, num2);
            optimized.push_back(to_string(result));
            i += 2; // Skip next two tokens as they are already processed
        } else {
            optimized.push_back(tokens[i]);
        }
    }

    // Reconstructing the optimized expression
    string result;
    for (const string &part : optimized) {
        result += part + " ";
    }
    return result.substr(0, result.length() - 1); // Remove trailing space
}

int main() {
    int test;
    cout<<"Test cases:";
    cin>>test;
    while(test--){
        string expression;
        cout << "Enter an arithmetic expression: ";
        getline(cin, expression);

        string optimizedExpr = optimizeExpression(expression);
        cout << "Optimized Expression: " << optimizedExpr << endl;
    }


    return 0;
}
