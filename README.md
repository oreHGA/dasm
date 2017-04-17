Nick Krisa
Ayessa Medrano - cssc0841
Oreoluwa Ogundipe - cssc0842
Elliott Watson - cssc1017
April 17, 2017
Class Information - CS 530, Spring 2017
Assignment Information - Programming Assignment #2, SIC/XE Disassembler
FileName: README

File manifest: OpTab.cpp findLabel.cpp dasm_main.cpp makefile README

Program Description: 
	This program will simulate a SIC/XE disassembler. The program will process the data of an object program, 
	and with the help of a SYMTAB for labels, translate this data into a listing of machine instructions
	that is readable to the user. 
		This program will take as input a <filename>.obj file and its accompanying <filename>.sym file to 
	generate a <filename>.sic file. 
		When the program executes, the <filename>.obj file and the <filename>.sym file will be opened
	and its contents extracted. dasm_main.cpp will process the individual object codes in the object program, 
	with the help of OpTab.cpp and findLabel.cpp, into machine instructions. To create the necessary 
	<filename>.sic file, OpTab.cpp was created. OpTab.cpp contains the mnemonic operation codes (opcodes) available
	on SIC/XE programming language and will be necessary when writing to the <filename>.sic file. The 
	<filename>.sym file's will contain the SYMTAB/LITTAB. The symbols and literals will be processed from the 
	file and used to find labels for the addresses they correspond to using findLabel.cpp.
		Each line of the object program is either a Header record, a Text record, a Modification record, or 
	an End record.dasm_main.cpp will seperate these lines and get the necessary information from them such as the 
	name of the program, its length, and its contents. The machine instructions are in the Text records and the program
	will indentify each individual object code in them and translate them into machine instructions.
	Each object code's bytes will be taken apart to determine its format (0, 1, 2, 3, or 4), the source statements
	(opcode and data constants or symbolic operands), and assembler directives needed to be written to the source file.
	Format 3 and 4 object codes will have special attention to process its nixbpe bits and dasm_main.cpp will 
	handle how these bits effect what is written to the source file. 
	After analyzing all object codes and getting their translations, the <filename>.sic file is complete and 
	will contain the listing of SIC/XE machine instructions of the <filename>.obj file. 
	
Compile instructions:
	To compile the program, enter "make dasm" in the directory that contains the files.
	This will execute the makefile we have created for this program which will compile the
	OpTab.cpp, findLabel.cpp, and dasm_main.cpp file for the user. The executable will be
	dasm 'disassembler'.

Operating instructions:
	To run the disassembler, the user shall provide a <filename>.obj file and its accompanying 
	<filename>.sym file. If neither the <filename>.obj or <filename>.sym are present, the dasm
	program will exit. 

Design Decisions:
	- Program was written in C++ 
	- Use of multiple files

Lesson Learned: 
	- SIC/XE machine features 
	- C++ language syntax and library
