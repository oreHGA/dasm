#include "OpTab.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;

const struct OpTab::instr OpTab::insTab[]= {
    {"add", "3/4"},
	{"addf", "3/4"}
	
	/*,
	{"addr", "2"},
	{"and", "3/4"},
	{"clear", "2"},
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
	mapTab["18"] = insTab[0];
	mapTab["58"] = insTab[1];
}


/*getInstr 
* takes in an opcode as a string and returns
* a pair (std::pair) of strings for the 
* mnemonic and the format
*/
pair<string, string> OpTab::getInstr(string op){
	pair<string, string> data;
	instr i = mapTab[op];
	
	data = std::make_pair(i.mnemonic, i.format);

	return data;	
}


int main(){
	OpTab optableInstance;
	
	string  opcodeExample = "18";
	
	pair<string, string> opData;
	
	opData = optableInstance.getInstr(opcodeExample);
	cout << opData.first << endl;
	cout << opData.second << endl;

	
	return 0;
}
