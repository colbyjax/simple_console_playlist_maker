#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <sys/stat.h>
#include <fstream>
#include "stdio.h"
#include "dirent.h"
#include "FileWrapper.h"

using namespace std;

class FileManager
{
public:
	static FileManager* Instance();
	FileManager() {};
	~FileManager() {};

	vector<FileWrapper> getFileList(string path, vector<string> extensionList);
	vector<struct KeyValue> handleIni(string path);
	bool saveFileOut(string outFile, vector<string> stringList);

private:
	static FileManager* pInstance;
	bool isDir(string path);


};

struct KeyValue {
	string key;
	string value;
};
