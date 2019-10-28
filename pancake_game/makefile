# makefile
CXX = g++-8.2.0
CXXFLAGS = -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract \
		  -fstack-clash-protection -g -fno-omit-frame-pointer
LDFLAGS = -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract \
		  -fstack-clash-protection -g -fno-omit-frame-pointer
LIBS = -lncurses++ -lmenu -lpanel -lform -lutil -lncurses

all: game test

Screens.o: Screens.cpp 
	$(CXX) $(CXXFLAGS) -c Screens.cpp

Engine.o: Engine.cpp
	$(CXX) $(CXXFLAGS) -c Engine.cpp

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c Main.cpp

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp

aiTree.o: aiTree.cpp
	$(CXX) $(CXXFLAGS) -c aiTree.cpp

node.o: node.cpp
	$(CXX) $(CXXFLAGS) -c node.cpp

Pancake.o: Pancake.cpp
	$(CXX) $(CXXFLAGS) -c Pancake.cpp

# exectuables
game: Screens.o Main.o Engine.o aiTree.o node.o Pancake.o find_solution.o
	$(CXX) $(LDFLAGS) -o game Screens.o Main.o Engine.o aiTree.o node.o Pancake.o find_solution.o $(LIBS)

test: Screens.o Test.o Engine.o aiTree.o node.o Pancake.o find_solution.o
	$(CXX) $(LDFLAGS) -o test Screens.o Test.o Engine.o aiTree.o node.o Pancake.o find_solution.o $(LIBS)

# clean directory
clean:
	rm Screens.o Engine.o Main.o Test.o aiTree.o node.o Pancake.o game test
