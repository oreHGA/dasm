#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
  string symbol;
  string address;
  string flag;
  Node *next;
};


void initNode(struct Node *head, string s, string a, string f);
Node* addNode(struct Node *head, string s, string a, string f);
Node* parseSym(string fileName);
string getAddress(Node *head, string s);
string getSymbol(Node *head, string a);
string getFlag(Node *head, string s);