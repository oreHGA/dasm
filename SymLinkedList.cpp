#include "SymLinkedList.h"

struct node {
  string symbol;
  string address;
  node *next;
}

void initNode(struct Node *head, string s, string a) {
  head->symbol = s;
  head->address = a;
  head->next = null;
}

void addNode(struct Node *head, string s, string a) {
  // Create the New Node to be inserted
  Node *newNode = new Node;
  head->symbol = s;
  head->address = a;
  head->next = null;

  Node *cur = head;
  while (cur) {
    if (cur->next == NULL) {
      cur->next = newNode
      return;
    }
    cur = cur->next;
  }
}

string getAddress(Node *head, string s) {
  Node *cur = head;

  while (cur) {
    if (cur->symbol == s) {
      return cur->address;
    }
    cur = cur->next;
  }
  return NULL;
}

string getSymbol(Node *head, string a) {
  Node *cur = head;

  while (cur) {
    if (cur->address == a) {
      return cur->symbol;
    }
    cur = cur->next;
  }
  return NULL;
}
