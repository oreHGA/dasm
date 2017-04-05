//OpTab header file
#ifndef OPTAB_H
#define OPTAB_H

#include <string>
#include <map>
using namespace std;

class OpTab{
	public:
		OpTab();
		
		struct instr{
			string opcode;
			struct data{
				string mnemonic;
				string format;
			} data;
		};
		
		static const instr insTab[59];
		
		pair<string, string> getInstr(string op);
		bool isInTable(string op);
		
		//for testing purposes only
		int tableSize();
		
	private:
		map<string, struct instr::data> mapTab;
	
};	
#endif