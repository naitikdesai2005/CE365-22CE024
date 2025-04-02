#include <bits/stdc++.h>

using namespace std;

bool isValidDataType(const string& dataType) {
    const vector<string> validTypes = {"int", "float", "char", "double", "long", "short"};
    return find(validTypes.begin(), validTypes.end(), dataType) != validTypes.end();
}

bool isValidVariableName(const string& variableName) {
    if (variableName.empty() || (!isalpha(variableName[0]) && variableName[0] != '_')) {
        return false;
    }
    for (char ch : variableName) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

bool isValidArray(const string& array) {
    size_t pos = array.find('[');
    if (pos == string::npos || array.back() != ']') {
        return false;
    }
    string baseName = array.substr(0, pos);
    return isValidVariableName(baseName);
}

bool isValidVariable(const string& variable) {
    if (variable.find('[') != string::npos) {
        return isValidArray(variable);
    } else {
        return isValidVariableName(variable);
    }
}

vector<string> tokenize(const string& statement) {
    istringstream stream(statement);
    string token;
    vector<string> tokens;
    while (stream >> token) {
        if (token.back() == ',') {
            tokens.push_back(token.substr(0, token.size() - 1));
            tokens.push_back(",");
        } else if (token.back() == ';') {
            tokens.push_back(token.substr(0, token.size() - 1));
            tokens.push_back(";");
        } else {
            tokens.push_back(token);
        }
    }
    return tokens;
}

string analyzeDeclaration(const string& statement) {
    vector<string> tokens = tokenize(statement);

    if (tokens.size() < 3 || tokens.back() != ";") {
        return "Error: Invalid declaration or missing semicolon.";
    }

    string dataType = tokens[0];
    if (!isValidDataType(dataType)) {
        return "Error: Invalid data type.";
    }

    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        if (tokens[i] != "," && !isValidVariable(tokens[i])) {
            return "Error: Invalid variable or array '" + tokens[i] + "'.";
        }
    }

    return "Syntax is correct.";
}

int main() {
    int test;
    cin>>test;
    while(test--){
        string declaration;
        cout << "Enter a C variable declaration: ";
        getline(cin, declaration);

        string result = analyzeDeclaration(declaration);
        cout << result << endl;
    }


    return 0;
}
