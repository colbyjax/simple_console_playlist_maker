#include "FileManager.h"

FileManager* FileManager::pInstance = NULL;

FileManager* FileManager::Instance()
{
	if(!pInstance) 
	{
		pInstance = new FileManager();
	}

	return pInstance;
}

vector<FileWrapper> FileManager::getFileList(string path, vector<string> extensionList)
{
	DIR *dir;
	vector<FileWrapper> fileList;

	struct dirent *ent;

	dir = opendir(path.c_str());
	if(dir!= NULL) {
		ent = readdir(dir);
		while(ent != NULL) {
			bool dirStatus = false;
			string fileName = ent->d_name;
			string fullFileName = path + fileName;

			if(isDir(fullFileName)) {
				// Directory
				dirStatus = true;
				FileWrapper fileWrapper = FileWrapper(fileName, dirStatus, path);

				// Add Directories except for directory navigators
				if((fileWrapper.getFileName() != ".") && (fileWrapper.getFileName() != "..")) {
					fileList.push_back(fileWrapper);
				}
			} else {
				// File
				FileWrapper fileWrapper = FileWrapper(fileName, false, path);

				bool extensionFound = false;
				// Make sure valid extension
				for(int i=0; i < extensionList.size(); i++) {
					if(fileWrapper.getExtension() == extensionList.at(i)) {
						extensionFound = true;
						continue;
					}
				}

				if(extensionFound) {
					// Valid File Extension - Add it
					fileList.push_back(fileWrapper);
				}

			}
			ent = readdir(dir);
		}
		closedir(dir);
	}
	return fileList;
}

bool FileManager::isDir(string path) 
{	
	bool isdir = false;

	struct stat st;
    if(stat(path.c_str(), &st) == 0) {;
    	isdir = S_ISDIR(st.st_mode);
    }

    return isdir;
}

vector<struct KeyValue> FileManager::handleIni(string fileName)
{
	struct KeyValue ini;
	vector<struct KeyValue> iniList;
	// Open Ini file
	ifstream iniFile (fileName.c_str());

	string line;

	if(iniFile.is_open()) {
		while(iniFile.good()) {
			getline(iniFile, line);

			// Process the line
			int idx = 0;
			for(int i=0; i < line.length(); i++) {
				if(line[i] == '=') {
					idx = i;
				}
			}

			if(idx > 0){
				ini.key = line.substr(0,idx);
				ini.value = line.substr(idx+1, line.length()-1);
				iniList.push_back(ini);
			}

		}
	}

	iniFile.close();
	iniList.push_back(ini);
	return iniList;
}

bool FileManager::saveFileOut(string outFile, vector<string> stringList) {
	bool status = true;
	ofstream out (outFile.c_str());
	if(out.is_open()) {
		// Cycle through vector and output to file
		for(int i=0; i < stringList.size(); i++) {
			out << stringList.at(i) << endl;
		}
		out.close();
	} else {
		status = false;
	}

	return status;

}

