#include <iostream>
#include "string.h"

using namespace std;

class FileWrapper
{
public:
	FileWrapper() {};
	~FileWrapper() {};
	FileWrapper(string fileName, bool isDir, string path);
	string getFileName() { return fileName; };
	string getPath() { return path; };
	string getExtension() { return extension; };
	bool getIsDir() { return isDir; };




private:
	string parseExtension();
	string fileName;
	bool isDir;
	string path;
	string extension;
};
