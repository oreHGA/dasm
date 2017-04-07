#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <iomanip>
#include "OpTab.h"
using namespace std;
	
int main(){
	OpTab optab;
	string obj = "1b2017";
	string firstByte = obj.substr(0, 2);
	string xbpeNib = obj.substr(2, 1);
	long int fbVal = strtol(firstByte.c_str(), NULL, 16);
	long int nibVal = strtol(xbpeNib.c_str(), NULL, 16);
	bool n = false, i = false, 
			x = false, b = false, 
			p = false, e = false;
	
	if((fbVal & 1) > 0)
		i = true;
	if((fbVal & 2) > 0)
		n = true;
	if((nibVal & 1) > 0)
		e = true;
	if((nibVal & 2) > 0)
		p = true;
	if ((nibVal & 4) > 0)
		b = true;
	if((nibVal & 8) > 0)
		x = true;
	
	//cout << "nibVal: " << nibVal << endl;
	cout << "nixbpe\n";
	cout << n << i << x << b << p << e << endl;
	
	long int fC = 0xfc; //dec value = 252
	long int three = 3;
	long int opVal =  fbVal &  fC;
	long int niVal = fbVal & three;
	long int opVal2 = fbVal - niVal;
	
	
	stringstream stream;
	stream << hex << opVal;
	string opcodeFC = stream.str();
	stream.str(string());
	stream << hex << opVal2;
	string opcodeNI = stream.str();
	pair<string,string> dataPair;
	dataPair = optab.getInstr(opcodeFC);
		
	cout << "First byte extraction: " << firstByte << endl;
	cout << "Opcode transformation; & FC method: " << opcodeFC << endl;
	cout << "Opcode transformation; - & three method: " << opcodeNI << endl;
	cout << "Mnemonic: " << dataPair.first << endl;
	cout << "Format: " << dataPair.second << endl;
	cout << "ni = " << niVal << "; ";
	
	switch(niVal){
		case 0:
			cout << "00: simple addressing (SIC basic)";
			break;
		case 1:
			cout << "01: immediate addressing";
			break;
		case 2:
			cout << "10: indirect addressing ";
			break;
		case 3:
			cout << "11: simple addressing (SIC/XE)";
			break;
		default:
			cout << "sucka em cee";
		
	}
	
	return 0;
}
