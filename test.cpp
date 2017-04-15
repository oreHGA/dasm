#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(){
    
    string val = "000000";
    int temp = hex_to_int(val);
    
    cout<<temp;
    return 0; 
}

int  hex_to_int(string address){
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
    return value;
}