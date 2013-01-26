# scpm.mak
# executable file scpm
#
# first define target file : scpm
# 		dependencies are the object files that build the program
#

scpm: scpm.o FileManager.o FileWrapper.o
	g++ -o scpm scpm.o FileManager.o FileWrapper.o

# now define how each object file is a target and list dependencies

scpm.o: scpm.cpp scpm.h
	g++ -c scpm.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

FileWrapper.o: FileWrapper.cpp FileWrapper.h
	g++ -c FileWrapper.cpp

clean:
	rm scpm scpm.o FileManager.o FileWrapper.o


