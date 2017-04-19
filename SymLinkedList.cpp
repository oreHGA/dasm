#include "SymLinkedList.h"


struct Node {
  string symbol;
  string address;
  string flag;
  Node *next;
};


void initNode(struct Node *head, string s, string a, string f) {
  head->symbol = s;
  head->address = a;
  head->flag = f;
  head->next = NULL;
}

Node* addNode(struct Node *head, string s, string a,string f) {
  // Create the New Node to be inserted
  Node *last = new Node();
  last->symbol = s;
  last->address = a;
  last->flag = f;
  last->next = NULL;
  
  if(head == NULL){
  	cout << "reached" << endl;
  	head = last;
  }
  else{
    Node *temp = new Node();
    temp = head;
    
    while(temp->next !=NULL){
      temp = temp->next;
    }
    temp->next = last;
  }
  return head;
}
//returns linked list with symbols
Node* parseSym(string filename){
  
	ifstream in(filename.c_str());
	if(!in){
		cout << "Cannot open input file.\n";
	}
	//getting all lines from file
	char str[255];
	string lines[255];
	int index = 0;
	while(in){
		in.getline(str, 255);
		if(in){
			lines[index] = str;
			index++;
		}
	}
	in.close();
	
	//getting only symbols
	string symbols[index];
	int index2 = 0;
	for(int i=0; i<index;i++){
		string line = lines[i];
		char letter = line[1];
		if(letter >= 'A' && letter <= 'Z'){
			symbols[index2] = lines[i];
			index2++; //keeps track of elements in symbols array
		}		
	}
	
	//Splitting the symbol Name, Value, and Flag into separate arrays
	string symbolName[index2];
	string symbolValue[index2];
	string symbolFlag[index2];
	
	int counter = 0;
	int index3 = 0;
	string s = symbols[0];
	string delimiter = " ";	
	size_t pos = 0;
	string token;
	
	for(int i = 0; i < index2; i++){
		string s = symbols[i];
		while((pos = s.find(delimiter)) !=string::npos){
			token = s.substr(0, pos);
			if(token.compare("")){
				if(counter == 0){
					symbolName[index3] = token;
				}
				if(counter == 1){
					symbolValue[index3] = token;
				}	
			counter++;
			}
			s.erase(0, pos + delimiter.length());
		}
		symbolFlag[index3] = s;
		counter = 0;
		index3++;
	}
	//CREATING LINKED LIST WITH VALUES
	Node *root = new Node();
	initNode(root, symbolName[0], symbolValue[0], symbolFlag[0]);
	
	for(int i=1; i<index3;i++){ //start at index 1 because already handled index 0
		if(root == NULL){
			cout << "Symbol Table is Empty" << endl;
		}
		else{
			root = addNode(root, symbolName[i], symbolValue[i], symbolFlag[i]);
		}
	}
	
	
	return root;

	
	
	
	
}

string getAddress(Node *head, string s) {
  Node *cur = head;

  while (cur) {
     if (cur->symbol.compare(s) == 0) {
      return cur->address;
    }
    cur = cur->next;
  }
  return NULL;
}

string getSymbol(Node *head, string a) {
  Node *cur = head;

  while (cur) {
    if (cur->address.compare(a) == 0) {
      return cur->symbol;
    }
    cur = cur->next;
  }
  return NULL;
}
//Pass in label name to get flag type
string getFlag(Node *head, string s) {
  Node *cur = head;
  while (cur) {
    if(cur->symbol.compare(s)==0){
      return cur->flag;
    }
    cur = cur->next;
  }
  return NULL;
}
int main(){
	string filename = "sample.sym";
	Node *symlist = parseSym(filename); 
	Node *pointer = symlist;
	//looping through linked list
	string address = getAddress(symlist, "TABLE");
	string name = getSymbol(symlist, "00000B");
	string flag = getFlag(symlist, "TABLE");
	cout << " works: " << address << endl;
	cout << " works: " << name << endl;
	cout << " works: " << flag << endl;
	while(pointer != NULL){
		cout << pointer->symbol << endl;
		cout << pointer->address << endl;
		cout << pointer->flag << endl;
		pointer = pointer->next;
	}
	
}
