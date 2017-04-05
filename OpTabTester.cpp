#include "OpTab.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;



int main(){
	OpTab optableInstance;
	string  opcodeExample;
	pair<string, string> opData;
	
	while(opcodeExample.compare("exit") != 0){
		
		cout << "enter opcode: ";
		cin >> opcodeExample;
		cout << endl;
		
		cout << "in table?: " << boolalpha << optableInstance.isInTable(opcodeExample) << endl;
		
		opData = optableInstance.getInstr(opcodeExample);
		
		
		cout << "mnemonic: " << opData.first << endl;
		cout << "format: "<< opData.second << endl;
		//cout << "table size: " << optableInstance.tableSize()	
		cout << endl << "**********" << endl;
	};

	return 0;
}