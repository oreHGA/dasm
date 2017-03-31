#include "OpTabB.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;

const struct OpTab::instr OpTab::insTab[]= {
    {"18", {"add", "3/4"}},
	{"58", {"addf", "3/4"}},
	{"90", {"addr", "2"}},
	{"40", {"and", "3/4"}},
	{"B4", {"clear", "2"}}
	
	/*,
	{"comp", "3/4"},
	{"compf", "3/4"},
	{"compr", "2"},
	{"div", "3/4"},
	{"divf", "3/4"},
	{"divr", "2"},
	{"fix", "1"},
	{"float", "1"},
	{"hio", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
	{"add", "3/4"},
    {"divr", "2"}
	*/
};

OpTab::OpTab(){
	for (int i = 0; i < sizeof(insTab)/sizeof(instr); i++)
		mapTab[insTab[i].opcode] = insTab[i].data;
	
}


/*getInstr 
* takes in an opcode as a string and returns
* a pair (std::pair) of strings for the 
* mnemonic and the format
*/
pair<string, string> OpTab::getInstr(string op){
	pair<string, string> dataPair;
	instr i;
	i.data = mapTab[op];
	
	dataPair = std::make_pair(i.data.mnemonic, i.data.format);

	return dataPair;	
}


int main(){
	OpTab optableInstance;
	
	string  opcodeExample = "B4";
	
	pair<string, string> opData;
	
	opData = optableInstance.getInstr(opcodeExample);
	cout << opData.first << endl;
	cout << opData.second << endl;

	
	return 0;
}
