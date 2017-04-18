#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
#include "OpTab.h"
#include "findLabel.h"

using namespace std;

int char_to_int(char val){
    if(val == '1')
        return 1;
    else if(val == '0')
        return 0;    
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
    if(val == 0)
        return '0';
    else if(val == 1)
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
// this is used to get the register name based onn its value     
string get_register(char val){
    switch(val){
        case 0:
            return "A";
        case 1:
            return "X";
        case 2:
            return "L";
        case 3:
            return "B";
        case 4:
            return "S";
        case 5:
            return "T";
        case 6:
            return "F";
        case 8:
            return "PC";
        case 9:
            return "SW";
        default:
            return "NOT VALID";
    }
}
int  hex_to_int(string address,bool p = false){
    // so we first get the length of the address
    // and then, for every character in the address
    
    int length = address.length();
    int value = 0 ;
    for(int i=length-1;i>=0;i--){
        int temp = char_to_int(address[i]);
        int exponent = length - (i + 1);
        temp = temp * (pow(16,exponent));
        value = value + temp;
        
    }
    if(value > 2047 && (p == true)){
        for(int i=length;i< 8;i++){
            address.insert(address.begin(),'F');
        }
        unsigned int x;
        std::stringstream ss;
        ss << std::hex << address;      
        ss >> x;                       
        value = static_cast<int>(x);
    }
    return value;
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
            int prog_counter;
            string loc_counter;
            int target_addr_int = 0 ;
            int base = 0;
            int start_address_val;
            string first_instruction;
            string line;
            ofstream result_file;
            stringstream result_line;
            OpTab opTable;
            pair<string , string> opData;
            int index;
            int object_length;
            while(getline(object_file,line)){
                // cout<<line<< "\n";
                // now we gonna process each line one by one 
                int length = line.size();
                int i = 0;
                if(line.at(i) == 'H' ){
                    // we are in the header record now
                    // cout<<"Header\n";
                    // next thing is to read the next 6 characters
                    string programname = line.substr(i+1,6) ;
                    result_line<<programname<<"\t"; // eventually we will have to write the name into the new file we are trying to create
                    i = 6;
                    string start_addr = line.substr(i+1,6);
                    i = i+6;
                    string obj_length = line.substr(i+1,6);
                    object_length = hex_to_int(obj_length);
                    cout<<object_length;
                    // cout<< start_addr;
                    pair<string,int> first_label = searchSym(sym,start_addr);
                    first_instruction = first_label.first;
                    opData = opTable.getInstr(start_addr);
                    if( start_addr == "000000" ){
                        start_addr.erase( start_addr.begin()+1,start_addr.end() ) ;
                    }
                    result_line<<"START\t"<<start_addr<<"\n";
                    start_address_val = hex_to_int(start_addr);
                    prog_counter = start_address_val;  
                    cout << result_line.str();
                    // write the resut line to the string
                    continue;
                }
                else if(line.at(i) == 'T'){
                    if(i == 0){
                        index = i + 8;
                    }
                    bool flag = true;
                    while(index+1 < line.length()){ 
                        stringstream loc_ss;
                        loc_ss << std::uppercase << hex <<  prog_counter;
                        loc_ss >> loc_counter; 

                        string target_addr;
                        string opcode;
                        bool is_literal = false;
                        // this is to print the label if any in front of the lines
                        pair<string,int> front_label;
                        // cout<<"Location counter is " << loc_counter<<endl;
                        front_label = searchSym(sym,loc_counter);
                        if(front_label.first == "NOT FOUND"){
                            front_label.first = "      ";
                        }
                        //read the first two 
                        string first_two = line.substr(index+1,2);
                        // cout <<"value to be read in"<<first_two<< endl;
                        index += 2; // since we just read in two variables we need to increment index
                        int temp_val = char_to_int( first_two[1] );
                        int n_i = temp_val % 4;  // so now we have our N AND I values from here
                        bool n_flag = false;
                        bool i_flag = false;
                        if( (n_i & 1) == 1 ){
                            i_flag = true;
                        }   
                        if( (n_i >> 1) == 1){
                            n_flag = true; 
                        }    
                        // we now have our n and i flag    
                        temp_val = temp_val - n_i ;// this is the second part of the opcode
                        // we need to get our opcode from variable first_two
                        stringstream ss;
                        ss << first_two[0] << int_to_char(temp_val);
                        ss >> opcode;
                        opData = opTable.getInstr(opcode);

                        if(opData.second == "NOT FOUND"){
                            // this means we have a format 1 or 2 instruction
                            cout<<"Incorrect Object file :("<<endl;
                            exit(1);
                        }
                        if(opData.second == "1"){
                            result_line<<"      \t"<<opData.first;
                            prog_counter = prog_counter + 1;
                        }
                        else if(opData.second == "2"){
                            // get register 1 and register 2
                            // read in the next 2 bytes and then get the register from the get_registers function
                            string registers = line.substr(index+1,2);
                            index += 2;  // since we just read in two bytes, we need to increment the index
                            string r1 = get_register(registers[0]);
                            string r2 = get_register(registers[1]);
                            result_line<<"      \t"<<opData.first<<"\t"<<r1<<","<<r2;
                            prog_counter = prog_counter + 2;                 
                        }
                        else{
                            string mnemonic  = opData.first;
                            bool x_flag = false;
                            bool b_flag = false;
                            bool p_flag = false;
                            bool e_flag = false;
                            // now we need to get the next the next byte and then get the x,b,p,e flags from it
                            temp_val = char_to_int(line[index+1]);
                            // cout<<"The value being used for xbpe is "<< temp_val << endl;
                            index = index + 1;
                            if((temp_val & 1) == 1 ){
                                e_flag = true;
                            }
                            if( ((temp_val >> 1) & 1 ) == 1){
                                p_flag = true;
                            }
                            if( ((temp_val >> 2) & 1 ) == 1){
                                b_flag = true;
                            }
                            if( ((temp_val >> 3) & 1 ) == 1){
                                x_flag = true;
                            }
                            // this is to increment the program counter
                            if(e_flag == true){
                                prog_counter = prog_counter + 4;
                            }else{
                                prog_counter = prog_counter + 3;
                            }
                            // cout<<"Your flags are "<<n_flag<<" "<<i_flag<<" "<<x_flag<<" "<<b_flag<<" "<<p_flag<<" "<<e_flag<<"\n";
                            // now to get data for the labels from the symtab
                            pair <string,int> labelData;

                            // now we have our nixbpe flags the next thing to do is to get the actual stuff based on the flags
                            if( (b_flag == true) && (p_flag == false) && (e_flag == false)){
                                string disp = line.substr(index+1,3);
                                index += 3;
                                int disp_int = hex_to_int(disp);
                                target_addr_int = disp_int + base;
                                stringstream new_s;
                                new_s << std::uppercase << hex << target_addr_int;
                                new_s >> target_addr;
                            }
                            else if( (b_flag == false) && (p_flag == true) && (e_flag == false) ){
                                string disp = line.substr(index+1,3);
                                index += 3;
                                int disp_int = hex_to_int(disp,true);
                                // cout << "The result is :: \t"<< disp_int<<endl;
                                target_addr_int = disp_int + prog_counter;
                                stringstream new_s;
                                new_s << std::uppercase <<  hex << target_addr_int;
                                new_s >> target_addr;
                            }
                            else if ( (b_flag == false) && (p_flag == false) && (e_flag == true) ){
                                target_addr = line.substr(index+1,5);
                                target_addr_int = hex_to_int(target_addr);
                                index += 5;
                                // put a plus in front of the mnemonic stuff
                                mnemonic.insert(mnemonic.begin(),'+');
                            }
                            else if( (b_flag == false) && (p_flag == false) && (e_flag == false) ){
                                target_addr = line.substr(index+1,3);
                                index += 3;
                            }

                            // handling immediate/indexed/simple addressing
                            if(n_flag == true && i_flag == false){
                                labelData = searchSym(sym, target_addr);
                                if(labelData.first == "NOT FOUND"){
                                    labelData = searchLit(sym, target_addr);
                                    if(labelData.first == "NOT FOUND"){
                                        cout<<"LABEL DOES NOT EXIST"<<endl;
                                        exit(1);
                                    }else{
                                        is_literal = true;
                                    }
                                }
                                target_addr = labelData.first;
                                target_addr.insert(target_addr.begin(),'@');
                            }
                            else if(i_flag == true && n_flag == false){
                                // decimal value of target address 
                                if(b_flag == false && p_flag == false && e_flag == false){
                                    int temp = hex_to_int(target_addr);
                                    // convert to temp to the string value of the same thing
                                    stringstream new_s;
                                    new_s << std::uppercase << temp;
                                    new_s >> target_addr;
                                    target_addr.insert(target_addr.begin(),'#');
                                }
                                else if(e_flag == true){
                                    labelData = searchSym(sym, target_addr);
                                    if(labelData.first == "NOT FOUND"){
                                        int temp = hex_to_int(target_addr);
                                        // convert to temp to the string value of the same thing
                                        stringstream new_s;
                                        new_s << std::uppercase << temp;
                                        new_s >> target_addr;
                                        target_addr.insert(target_addr.begin(),'#');
                                    }                                
                                    else{
                                        target_addr = labelData.first;
                                        target_addr.insert(target_addr.begin(),'#');
                                    }
                                }
                                else{
                                    labelData = searchSym(sym, target_addr);
                                    if(labelData.first == "NOT FOUND"){
                                        cout<<"ERROR!! DOES NOT EXIST"<<endl;
                                        exit(1);
                                    }                                
                                    else{
                                        target_addr = labelData.first;
                                        target_addr.insert(target_addr.begin(),'#');
                                    }
                                }
                            }
                            else{ // if both n and i are on or off

                                labelData = searchSym(sym, target_addr);
                                if(labelData.first == "NOT FOUND"){
                                    labelData = searchLit(sym, target_addr);
                                    if(labelData.first == "NOT FOUND"){
                                        cout<<"ERROR! LABEL NOT FOUND"<<endl;
                                        exit(1);
                                    }
                                    else{
                                        is_literal = true;
                                    }
                                }
                                target_addr = labelData.first;
                            }

                            if(x_flag == true){
                                target_addr.append(",X");
                            }
                            if( mnemonic.find("RSUB") != std::string::npos ){
                                target_addr.clear();
                            }
                            result_line.str(std::string());
                            result_line<<front_label.first<<"\t" << mnemonic << "\t"<<target_addr<<"\n";
                            cout << result_line.str();
                            if( mnemonic.find("LDB") != std::string::npos ){
                                result_line.str(std::string());
                                result_line<<"      \t"<<"BASE\t"<<labelData.first<<"\n";
                                base = target_addr_int;
                                cout << result_line.str();
                            }
                            if( is_literal == true ){
                                result_line.str(std::string());
                                result_line<<"      \t"<<"LTORG\n";
                                index = index +  (2 * labelData.second);
                                prog_counter = prog_counter + labelData.second;
                                cout<< result_line.str();
                            }
                            target_addr.clear();
                        }
                     }
                     continue;
                }
                else if(line.at(i) == 'M'){                                                                                                                                                  
                    continue;
                }
                else if(line.at(i) == 'E'){
                    stringstream loc_ss;
                    loc_ss << std::uppercase << hex <<  prog_counter;
                    loc_ss >> loc_counter;

                    

                    result_line.str(std::string());
                    result_line <<"      \tEND\t"<<first_instruction<<endl;
                    cout<< result_line.str();
                    break;
                }
            }
            object_file.close();
            symtab.close();
            
        }   
    }
    // cout<<"Welcome back Captiain!I missed you\n";
    return 0;
}