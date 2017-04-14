#include<iostream>
#include<fstream>
#include<string>
using namespace std;


//function declaration
 string searchSym(string fileName, string address);
 int main(){
	
	string fileName = "sample.sym";
	string address = "000000"; //address has 6 characters
	
	string label = searchSym(fileName, address);
	cout << "label: " << label << endl;
	
	return 0;
	
}
//function that will open file (symtab) to search if an address matches a label
 string searchSym(string fileName, string address){
 	
 	ifstream in(fileName.c_str());
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
	
	//separating symbols and literals
	string symbols[index];
	string literals[index];
	int indexSym = 0;
	int indexLit = 0;
	for(int i=0; i<index;i++){
		string line = lines[i];
		char letter = line[1];//Labels are all in caps
		if(!line.empty()){
			//takes off significant markers for the symtab and littab
			if(letter >= 'A' && letter <= 'Z'){
				symbols[indexSym] = lines[i];
				indexSym++; //keeps track of elements in symbols array
			}
			else if(!(letter >= 'a' && letter <= 'z') && letter != '-'){
				literals[indexLit] = lines[i];
				indexLit++;
			}
		}
				
	}
	
	//Splitting the symbol Name, Value, and Flag into separate arrays
	string symbolName[indexSym];
	string symbolValue[indexSym];
	string symbolFlag[indexSym];
	int counter = 0;
	int indexS = 0;
	string s = symbols[0];
	string delimiter = " ";	
	size_t pos = 0;
	string token;
	
	for(int i = 0; i < indexSym; i++){
		string s = symbols[i];
		while((pos = s.find(delimiter)) !=string::npos){
			token = s.substr(0, pos);
			if(token.compare("")){
				if(counter == 0){
					symbolName[indexS] = token;
				}
				if(counter == 1){
					symbolValue[indexS] = token;
				}	
			counter++;
			}
			s.erase(0, pos + delimiter.length());
		}
		symbolFlag[indexS] = s;
		counter = 0;
		indexS++;
	}
	for(int i = 0; i < indexS; i++){
		if(address.compare(symbolValue[i]) == 0){
			return symbolName[i];
		}
	}
	
	//Working on separating literal values NOT YET DONE
	//string literalName[indexLit];
	//string literalLength[indexLit];
	//string literalAddress[indexLit];
	//int counterL = 0;
	//int indexL = 0;
	//string l = symbols[0];
	//string delimiterl = " ";	
	//size_t posl = 0;
	//string tokenl;
	
	//for(int i = 0; i < indexLit; i++){
	//	string l = literals[i];
	//	while((posl = l.find(delimiterl)) !=string::npos){
	//		tokenl = l.substr(0, pos);
	//		if(tokenl[0] == ' '){
	//			cout << "token: " << tokenl << endl;
	//		}
	//		else{
	//			if(counterL == 0){
	//				literalName[indexL] = tokenl;
	//			}
	//			if(counterL == 1){
	//				literalLength[indexL] = tokenl;
	//			}	
	//		counterL++;
	//		}
	//		l.erase(0, posl + delimiterl.length());
	//	}
	//	literalAddress[indexL] = l;
	//	counterL = 0;
	//	indexL++;
	//}
	
	//cout << "indexL: " << indexL << endl;
	//cout << literalName[0] << endl;
	
	//for(int i = 0; i < indexL; i++){
		//if(address.compare(literalAddress[i]) == 0){
			//return literalName[i];
		//}
	//}
	

	return "0";
}
