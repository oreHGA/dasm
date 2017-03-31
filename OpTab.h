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
			string mnemonic;
			string format;
		};
		
		static const instr insTab[2];
		
		pair<string, string> getInstr(string op);
		
	private:
		map<string, instr> mapTab;	
};	
#endif