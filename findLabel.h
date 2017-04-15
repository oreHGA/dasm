// header file for getting the label from a symtab given an address
#ifndef FINDLABEL_H
#define FINDLABEL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

pair<string, int>  searchSym(string fileName, string address);

#endif