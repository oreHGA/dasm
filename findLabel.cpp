//This only works with the Symbol table, not the Literal table, for now..Still working on that
#include  "findLabel.h"

//function that will open file (symtab) to search if an address matches a label
pair<string, int> searchSym(string fileName, string address){
 	int addr_len = address.length();
	 cout<<"Address before manipulation is:"<< address<<"\n";
	if(addr_len < 6){
		for(int i =0;i<6-(addr_len);i++){
			address.insert(address.begin(),'0');
		}
	}
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
	string literals[index];
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
			return std::make_pair(symbolName[i],0);
		}
	}

	//separating literal information into different arrays
	int indexLit = 0;
	string literalName[indexLit];
	string literalLength[indexLit];
	string literalAddress[indexLit];
	//a literal's name, length, and address are linked by location in arrays
	index3=0;
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
	int length;
	string label;
	for(int i = 0; i < index3;i++){
		if(address.compare(literalAddress[i]) == 0){

			label = literalName[i];
			if(literalName[i].at(1) == 'X'){
				// CONVERT THE LENGTH TO int then perform some operation and then turn it back to string
				stringstream i_val(literalLength[i]);
				i_val >> length;
				length = length / 2 ;
			}
			else if(literalName[i].at(1) == 'C'){
				stringstream i_val(literalLength[i]);
				i_val >> length;
				length = length * 2 ;
			}
			return std::make_pair(label,length);
		}
	}

	return std::make_pair("NOT FOUND",0);
}
