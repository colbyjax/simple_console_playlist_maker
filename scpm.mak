# scpm.mak
# executable file scpm
#
# first define target file : scpm
# 		dependencies are the object files that build the program
#

bin/scpm: obj/scpm.o obj/FileManager.o obj/FileWrapper.o
	g++ -o bin/scpm obj/scpm.o obj/FileManager.o obj/FileWrapper.o

# now define how each object file is a target and list dependencies

obj/scpm.o: scpm.cpp scpm.h
	g++ -o obj/scpm.o -c scpm.cpp

obj/FileManager.o: FileManager.cpp FileManager.h
	g++ -o obj/FileManager.o -c FileManager.cpp

obj/FileWrapper.o: FileWrapper.cpp FileWrapper.h
	g++ -o obj/FileWrapper.o -c FileWrapper.cpp

clean:
	rm bin/scpm obj/scpm.o obj/FileManager.o obj/FileWrapper.o


