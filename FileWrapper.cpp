#include "FileWrapper.h"
#include <stdio.h>
FileWrapper::FileWrapper(string in_fileName, bool in_isDir, string in_path)
{
	fileName = in_fileName;
	isDir = in_isDir;
	path = in_path;
	extension = parseExtension();
}



string FileWrapper::parseExtension()
{
	string extension = "";
	int idx = 0;

	for(int i=fileName.length()-1; i >= 0; i--) {
		if(fileName[i] == '.') {
			idx = i;
			continue;
		}
	}
	if(idx > 0) {
		extension = fileName.substr(idx+1, fileName.length()-1);
	}

	return extension;
}

