//This only works with the Symbol table, not the Literal table, for now..Still working on that
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


//function declaration
 string searchSym(string fileName, string address);
 int main(){
	
	string fileName = "sample.sym";
	string address = "00000B"; //address has 6 characters
	
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
	for(int i = 0; i < index3; i++){
		if(address.compare(symbolValue[i]) == 0){
			return symbolName[i];
		}
	}
	return "0";
}
