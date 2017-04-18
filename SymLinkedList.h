#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

void initNode(struct Node *head, string s, string a);
Node* addNode(struct Node *head, string s, string a);
Node* parseSym(string fileName);
string getAddress(Node *head, string s);
string getSymbol(Node *head, string a);
