CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=OpTab.cpp findLabel.cpp SymLinkedList.cpp dasm_main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dasm

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
