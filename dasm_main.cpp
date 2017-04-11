#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

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
            cout<<"usage: "<<argv[0]<<" Files necessary for execution are not present\n"<<"Ensure you have <filename>.sym and <filename>.obj ready\n";
            exit(1); // 1 means that something abruptly went wrong
        }
        else{
            // now that we can open the files , its time for business
            string line;
            ofstream result_file;
            while(getline(object_file,line)){
                cout<<line<< "\n";
                // now we gonna process each line one by one 
                int length = line.size();
                int i = 0;
                while (i<length){
                    if(line.at(i) == 'H' ){
                        // we are in the header record now
                        // next thing is to read the next 6 characters
                        cout<<"Header\n";
                    }
                    else if(line.at(i) == 'T'){
                        cout<<"Text\n";
                    }
                    else if(line.at(i) == 'M'){
                        break;
                    }
                    else if(line.at(i) == 'E'){
                        cout<<"End\n";
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
    cout<<"Welcome back Captiain!I missed you\n";
    return 0;
}