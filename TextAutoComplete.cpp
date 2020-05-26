// #include "TrieNode.h"
#include <string>
#include <vector>
#include<iostream>
#include<algorithm>
using namespace std;

class TrieNode {
	public :
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};

class Trie {
	TrieNode *root;

	public :
	int count;

	Trie() {
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}

    void printComplete(TrieNode *root,string temp) {
        temp+=root->data;
        if(root->isTerminal) {
            cout<<temp<<endl;
        }
        for(int i=0;i<26;i++) {
            if(root->children[i]!=NULL) {
                printComplete(root->children[i],temp);
            }
        }
    }

    void autoComplete(TrieNode *root, string pattern,string temp) {
        if(pattern.size()==0) {
            if(root->isTerminal) {
            	cout<<temp<<endl;
            }
            for(int i=0;i<26;i++) {
            	if(root->children[i]!=NULL) {
                	printComplete(root->children[i],temp);
            	}
        	}
            return;
        }
        int index=pattern[0]-'a';
        if(root->children[index]==NULL) {
        	return;
        }
        TrieNode* child=root->children[index];
        temp+=root->children[index]->data;
        autoComplete(child,pattern.substr(1),temp);
    }

    void autoComplete(vector<string> input, string pattern) {
        // Complete this function
        // Print the output as specified in question
        for(int i=0;i<input.size();i++) {
            insertWord(input.at(i));
        }
        string temp;
        autoComplete(root,pattern,temp);
    }
};


int main() {
	Trie t;
    int N;
    cin >> N;
    string pattern;
    vector<string> vect;
    for (int i=0; i < N; i++) {
        string word;
        cin >> word;
        vect.push_back(word);
    }
    cin >> pattern;
    t.autoComplete(vect, pattern);
}
