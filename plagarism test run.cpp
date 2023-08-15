#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

// Function to tokenize a string into individual words
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    istringstream iss(line);
    string word;
    while (iss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

// Function to calculate the hash value for a given vector of tokens
size_t hashTokens(const vector<string>& tokens) {
    size_t hash = 0;
    for (const string& token : tokens) {
        for (char c : token) {
            hash = hash * 31 + c;
        }
    }
    return hash;
}

// Function to detect plagiarism between two text files using a hash table
void detectPlagiarism(const string& file1, const string& file2) {
    ifstream file(file1);
    if (!file.is_open()) {
        cerr << "Failed to open " << file1 << ".\n";
        return;
    }

    unordered_map<size_t, vector<string>> hashTable;

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        vector<string> tokens = tokenize(line);
        size_t hash = hashTokens(tokens);
        hashTable[hash].push_back(line);
    }

    file.close();

    file.open(file2);
    if (!file.is_open()) {
        cerr << "Failed to open " << file2 << ".\n";
        return;
    }

    cout << "Plagiarized lines:\n";
    lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        vector<string> tokens = tokenize(line);
        size_t hash = hashTokens(tokens);
        if (hashTable.count(hash) > 0) {
            for (const string& pline : hashTable[hash]) {
                cout << "Match found in line " << lineNumber << " of " << file2 << ": " << pline << "\n";
            }
        }
    }

    file.close();
}

int main() {
    string filename1, filename2;
    cout << "Enter the first filename: ";
    cin >> filename1;
    cout << "Enter the second filename: ";
    cin >> filename2;

    detectPlagiarism(filename1, filename2);

    return 0;
}
