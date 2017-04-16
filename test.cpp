#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(){
    int val = 5;
    stringstream ss(val);
    string ffd;
    ss >> ffd;
    std::cout << ffd  << std::endl;
    
}

