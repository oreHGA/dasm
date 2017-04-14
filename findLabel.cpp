#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;


//function declaration
 string searchSym(string fileName, string address);
 int main(){
	
	string fileName = "sample.sym";
	string address = "000003"; //address has 6 characters
	
	string label = searchSym(fileName, address);
	cout << "label: " << label << endl;
	
	return 0;
	
}
//function that will open file (symtab) to search if an address matches a label
 string searchSym(string fileName, string address){
 	//open symbol file
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
	 //separating symbols and literals into separate arrays
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
	
	//separating symbol information into different arrays
	string symbolName[indexSym];
	string symbolValue[indexSym];
	string symbolFlag[indexSym];
	//A symbol's name, value, and flag are linked by location in arrays
	int index2=0;
	int counter2 = 0;
	for(int i = 0; i < indexSym; i++){
		string s(symbols[i]);
		istringstream iss(s);
		do{
			string sub;
			iss >> sub;
			if(counter2 == 0){
				symbolName[index2] = sub;
				counter2++;
			}
			else if(counter2 == 1){
				symbolValue[index2] = sub;
				counter2++;
			}
			else if(counter2 == 2){
				symbolFlag[index2] = sub;
				counter2++;
			}
			else{
				counter2=0;
				index2++;
			}
			
		}while(iss);
	}
	
	//check to see if address passed is the SYMTAB
	for(int i = 0; i < index2;i++){
		if(address.compare(symbolValue[i]) == 0){
			return symbolValue[i];
		}
	}
	
	//separating literal information into different arrays
	string literalName[indexLit];
	string literalLength[indexLit];
	string literalAddress[indexLit];
	//a literal's name, length, and address are linked by location in arrays
	int index3=0;
	int counter3=0;
	
	for(int i = 0; i < indexLit; i++){
		string s(literals[i]);
		istringstream iss(s);
		do{
			string sub;
			iss >> sub;
			if(counter3 == 0){
				literalName[index3] = sub;
				counter3++;
			}
			else if(counter3 == 1){
				literalLength[index3] = sub;
				counter3++;
			}
			else if(counter3 == 2){
				literalAddress[index3] = sub;
				counter3++;
			}
			else{
				counter3=0;
				index3++;
			}
			
		}while(iss);
	}
	
	//checking to see if address passed is in the LITTAB
	for(int i = 0; i < index3;i++){
		if(address.compare(literalAddress[i]) == 0){
			return literalName[i];
		}
	}
	
	//return 0 if address does not match any address in SYMTAB or LITTAB
	return "0";
}

