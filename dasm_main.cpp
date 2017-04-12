#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

int char_to_int(char val){
    if(val == '1')
        return 1;
    else if( val == '2')
        return 2;
    else if( val == '3')
        return 3;
    else if( val == '4')
        return 4;
    else if( val == '5')
        return 5;
    else if( val == '6')
        return 6;
    else if( val == '7')
        return 7;
    else if( val == '8')
        return 8;
    else if( val == '9')
        return 9;
    else if( val == 'A')
        return 10;
    else if( val == 'B')
        return 11;
    else if( val == 'C')
        return 12;
    else if( val == 'D')
        return 13;
    else if( val == 'E')
        return 14;
    else if( val == 'F')
        return 15;    
}
char int_to_char(int val){
    if(val == 1)
        return '1';
    else if( val == 2)
        return '2';
    else if( val == 3)
        return '3';
    else if( val == 4)
        return '4';
    else if( val == 5)
        return '5';
    else if( val == 6)
        return '6';
    else if( val == 7)
        return '7';
    else if( val == 8)
        return '8';
    else if( val == 9)
        return '9';
    else if( val == 10)
        return 'A';
    else if( val == 11)
        return 'B';
    else if( val == 12)
        return 'C';
    else if( val == 13)
        return 'D';
    else if( val == 14)
        return 'E';
    else if( val == 15)
        return 'F';    
}

int main(int argc,char *argv[]){
    if(argc != 2){
        //throw an error if the program is not executed properly throw an error
        cout<<"usage: "<<argv[0]<<" <filename>.obj\n";
        exit(1); // 1 means that something abruptly went wrong
    }
    else{
        // first we need to read in the object file and them process it line by line
        string filename = argv[1];
        filename.erase(filename.size()-4,4);
        string obj = filename;
        obj.append(".obj"); // now we have filename.obj
        string sym = filename;
        sym.append(".sym");   // now we have filename.sym

        ifstream object_file(obj.c_str()); // object file ready
        ifstream symtab(sym.c_str()); // symtab ready 

        // we check if we can open the files
        if( !symtab.is_open() || !object_file.is_open() ){
            cout<<"usage: "<<argv[0]<<" Files necessary for execution are not present\n";
            cout<<"Ensure you have <filename>.sym and <filename>.obj ready\n";
            exit(1); // 1 means that something abruptly went wrong
        }
        else{
            // now that we can open the files , its time for business
            string line;
            ofstream result_file;
            while(getline(object_file,line)){
                // cout<<line<< "\n";
                // now we gonna process each line one by one 
                int length = line.size();
                int i = 0;
                while (i<length){
                    if(line.at(i) == 'H' ){
                        // we are in the header record now
                        // 
                        // cout<<"Header\n";
                        // next thing is to read the next 6 characters
                        string programname = line.substr(i+1,6) ;
                        cout<<programname<<"\n"; // eventually we will have to write the name into the new file we are trying to create
                        //now continue
                        break;

                    }
                    else if(line.at(i) == 'T'){
                        // cout<<"Text\n";
                        // now for the text record.. this is where things actually get interesting because we want taking in strings we 
                        // like without actually specifying values rather using a counter
                        // ah ah .. what we do in this case is that we should basically have a new loop and get the  
                        int index = i + 6;
                        while(true){
                            //read the first two 
                            
                            string first_two = line.substr(index+1,2);
                            int temp_val = char_to_int( first_two[1] );
                            //we need to convert the char value to its hexadecimal representation
                            // then perform the bit modification stuff to get the n,i values and also get the opcode
                            int n_i = temp_val & ( (2 << 1) - 1 );  // so now we have our N AND I values from here
                            bool n_flag = false;
                            bool i_flag = false;
                            // performing some bit shifting to get the N AND 1 values from variable n_i
                            if( (n_i & 1) == 1 ){
                                i_flag = true;
                            }   
                            else if( (n_i >> 1) == 1){
                                n_flag = true; 
                            }    
                            // we now have our n and i flag    
                            temp_val = temp_val - n_i ;// this is the second part of the opcode
                            // we need to get our opcode from variable first_two
                            stringstream ss;
                            string opcode;
                            ss << first_two[0] << int_to_char(temp_val);
                            ss >> opcode;
                            cout<< opcode<<"\n";
                            break;
                        }
                    }
                    else if(line.at(i) == 'M'){
                        break;
                    }
                    else if(line.at(i) == 'E'){
                        // cout<<"End\n";
                    }
                    break;
                }
            }
            object_file.close();
            symtab.close();
            // ifstream 
            // to open and read to it
            // resultfile.open("name of file");
            // close file using 
            // resultfile.close();
        }   
    }
    // cout<<"Welcome back Captiain!I missed you\n";
    return 0;
}