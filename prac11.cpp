#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempCount = 1;

string generateTemp() {
    return "t" + to_string(tempCount++);
}

void addQuadruple(string op, string arg1, string arg2, string result) {
    quadruples.push_back({op, arg1, arg2, result});
}

string processExpression(string expr) {
    istringstream iss(expr);
    vector<string> tokens;
    string token;
    while (iss >> token) tokens.push_back(token);

    vector<string> stack;
    for (size_t i = 0; i < tokens.size(); i++) {
        if ((tokens[i] == "*" || tokens[i] == "/") && i + 1 < tokens.size()) {
            string t = generateTemp();
            addQuadruple(tokens[i], stack.back(), tokens[i+1], t);
            stack.pop_back();
            stack.push_back(t);
            i++;
        } else {
            stack.push_back(tokens[i]);
        }
    }

    string result = stack[0];
    for (size_t i = 1; i < stack.size(); i += 2) {
        if (i + 1 < stack.size()) {
            string t = generateTemp();
            addQuadruple(stack[i], result, stack[i+1], t);
            result = t;
        }
    }
    return result;
}

void printQuadruples() {
    cout << "Operator\tOperand 1\tOperand 2\tResult" << endl;
    for (auto &q : quadruples) {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << endl;
    }
}

int main() {
    int test;
    cout << "Test cases: ";
    cin >> test;
    cin.ignore(); // Clear the newline character

    while (test--) {
        string expression;
        cout << "Enter an arithmetic expression: ";
        getline(cin, expression);

        quadruples.clear(); // Clear previous quadruples
        processExpression(expression);
        printQuadruples();
    }
    return 0;
}
