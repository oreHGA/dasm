// header file for getting the label from a symtab given an address
#ifndef FINDLABEL_H
#define FINDLABEL_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string searchSym(string fileName, string address);

#endif