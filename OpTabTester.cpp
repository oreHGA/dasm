#include "OpTabB.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;



int main(){
	OpTab optableInstance;
	string  opcodeExample;
	pair<string, string> opData;
	
	while(opcodeExample.compare("exit")){
		
		cout << "enter opcode: ";
		cin >> opcodeExample;
		cout << endl;
		
		opData = optableInstance.getInstr(opcodeExample);
		
		cout << "mnemonic: " << opData.first << endl;
		cout << "format: "<< opData.second << endl 
		<< endl << "**********" << endl;
	};

	
	return 0;
}