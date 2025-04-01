#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet;
map<char, set<char>> followSet;
map<pair<char, char>, string> parsingTable;
set<char> nonTerminals;
char startSymbol;

void calculateFirst(char symbol);
void calculateFollow(char symbol);
void constructParsingTable();
bool isLL1Grammar();
bool validateString(string input);

void printSet(map<char, set<char>> &s) {
    for (auto &entry : s) {
        cout << entry.first << " : { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }
}

int main() {
    int n;
    cout << "Enter number of rules: ";
    cin >> n;
    cout << "Enter grammar rules (e.g., S -> aB or A -> @ for epsilon):\n";

    for (int i = 0; i < n; i++) {
        char left;
        string arrow, right;
        cin >> left >> arrow >> right;
        grammar[left].push_back(right);
        nonTerminals.insert(left);
    }
    startSymbol = grammar.begin()->first;

    for (char nt : nonTerminals) calculateFirst(nt);
    for (char nt : nonTerminals) calculateFollow(nt);

    cout << "\nFirst Sets:\n";
    printSet(firstSet);
    cout << "\nFollow Sets:\n";
    printSet(followSet);

    constructParsingTable();

    cout << "\nPredictive Parsing Table:\n";
    for (auto &entry : parsingTable) {
        cout << "M[" << entry.first.first << ", " << entry.first.second << "] = " << entry.second << endl;
    }

    if (isLL1Grammar()) {
        cout << "\nGrammar is LL(1)\n";
    } else {
        cout << "\nGrammar is NOT LL(1)\n";
        return 0;
    }

    string input;
    cout << "\nEnter input string: ";
    cin >> input;
    input += '$';

    if (validateString(input)) {
        cout << "\nValid string\n";
    } else {
        cout << "\nInvalid string\n";
    }
    return 0;
}

void calculateFirst(char symbol) {
    if (!isupper(symbol)) {
        firstSet[symbol].insert(symbol);
        return;
    }
    for (string production : grammar[symbol]) {
        if (production == "@") {
            firstSet[symbol].insert('@');
            continue;
        }
        int i = 0;
        while (i < production.size()) {
            char ch = production[i];
            calculateFirst(ch);
            bool hasEpsilon = false;
            for (char f : firstSet[ch]) {
                if (f == '@') hasEpsilon = true;
                else firstSet[symbol].insert(f);
            }
            if (!hasEpsilon) break;
            i++;
        }
        if (i == production.size()) firstSet[symbol].insert('@');
    }
}

void calculateFollow(char symbol) {
    if (symbol == startSymbol) followSet[symbol].insert('$');
    for (auto &rule : grammar) {
        char left = rule.first;
        for (string production : rule.second) {
            for (size_t i = 0; i < production.size(); i++) {
                if (production[i] == symbol) {
                    size_t j = i + 1;
                    while (j < production.size()) {
                        char next = production[j];
                        for (char f : firstSet[next]) {
                            if (f != '@') followSet[symbol].insert(f);
                        }
                        if (firstSet[next].count('@')) j++;
                        else break;
                    }
                    if (j == production.size() || firstSet[production[j]].count('@')) {
                        for (char f : followSet[left]) {
                            followSet[symbol].insert(f);
                        }
                    }
                }
            }
        }
    }
}

void constructParsingTable() {
    for (auto &rule : grammar) {
        char left = rule.first;
        for (string production : rule.second) {
            if (production == "@") {
                for (char f : followSet[left]) {
                    parsingTable[{left, f}] = production;
                }
            } else {
                for (char f : firstSet[production[0]]) {
                    parsingTable[{left, f}] = production;
                }
                if (firstSet[production[0]].count('@')) {
                    for (char f : followSet[left]) {
                        parsingTable[{left, f}] = production;
                    }
                }
            }
        }
    }
}

bool isLL1Grammar() {
    for (auto &rule : grammar) {
        set<char> seen;
        for (string production : rule.second) {
            for (char f : firstSet[production[0]]) {
                if (seen.count(f)) return false;
                seen.insert(f);
            }
        }
    }
    return true;
}

bool validateString(string input) {
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push(startSymbol);
    int i = 0;
    while (!parseStack.empty()) {
        char top = parseStack.top();
        parseStack.pop();
        if (top == input[i]) {
            i++;
        } else if (isupper(top)) {
            if (parsingTable.count({top, input[i]})) {
                string production = parsingTable[{top, input[i]}];
                if (production != "@") {
                    for (int j = production.size() - 1; j >= 0; j--) {
                        parseStack.push(production[j]);
                    }
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return i == input.size();
}