#include <iostream>
#include <cstdlib>
#include <stack>
#include "FileManager.h"

// Function Definitions
vector<FileWrapper> displayList(string path, bool forward);
void handleIni();
bool handleCommandLine(int argc, char* argv[]);

void displayHelp();
void displayCorrectUsage();


// Variables
int MAX_LIST_SIZE = 15;
const char* clearScreen= "cls";
const char* iniFileName = "scpm.conf";
string startingPath ="./";
string playlistFile ="playlist.m3u";
vector<FileWrapper> playList;
vector<string> extensionList;
stack<string> pathStack;
int screenNumber = 0;





