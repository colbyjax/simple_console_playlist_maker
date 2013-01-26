#include "scpm.h"

using namespace std;


// Variables

int main(int argc, char *argv[])
{
	string input;
	bool exit = false;

	// Handle the Ini File
	handleIni();

	if(!handleCommandLine(argc, argv)) {
		return 1;
	}

	pathStack.push(startingPath);

	// Initialize List
	vector<FileWrapper> currentList = displayList(pathStack.top(), true);
	
	// Input Capture
	while(!exit) {
		cin >> input;
		
		if(isdigit(input[0])) {
			// Input is a Number
			int selection = atoi(&input[0]);

			if(selection < currentList.size()) {
				// Valid Selection
				// If directory, browse directory, if file, add file to playlist
				if(currentList.at(selection).getIsDir()) {
					// directory
					screenNumber = 0;
					string newDir = pathStack.top();
					newDir += currentList.at(selection).getFileName() + "/";
					pathStack.push(newDir);
					currentList = displayList(pathStack.top(), true);
				} else {
					// add to playlist
					playList.push_back(currentList.at(selection));
					displayList(pathStack.top(), false);
				}
			} else {
				cout << "Your selection must be a valid selection from the list above" << endl;
			}
		} else if(input == "n") {
			// Move Down
			currentList = displayList(pathStack.top(), true);
		} else if(input == "u") {
			// Go up a directory
			string top = pathStack.top();
			if(!(top == startingPath)) {
				pathStack.pop();
				currentList = displayList(pathStack.top(), true);
			} else {
				cout << "Cannot go further up than your Music Home" << endl;
			}
		} else if((input == "h") || (input == "home")) {
			// Move Home
			screenNumber = 0;
			// Clear Stack
			while(!pathStack.empty()) {
				pathStack.pop();
			}
			pathStack.push(startingPath);
			currentList = displayList(pathStack.top(), true);
		} else if(input == "s") {
			// Convert Playlist into vector of strings
			vector<string> playFile;
			for(int i=0; i < playList.size(); i++) {
				string fullFileName = playList.at(i).getPath() + playList.at(i).getFileName();
				playFile.push_back(fullFileName);
			}
			// Now Save File
			FileManager* fm;
			fm->Instance();
			bool saved = fm->saveFileOut(playlistFile, playFile);
			if(saved) {
				cout << "Playlist Saved!!" << endl;
				return 0;
			} else {
				cout << "Error saving the Playlist" << endl;
				return 2;
			}

		} else if(input == "?") {
			displayHelp();
		} else if((input == "quit") || (input == "exit") || (input == "q")) {
			// quit
			exit = true;
		}
	}
}

/* Called to Show Inital Screen and Screen Refresh */
vector<FileWrapper> displayList(string path, bool forward) {
	cout << string(100, '\n');
	FileManager* fm;
	fm = fm->Instance();
	vector<FileWrapper> fileList = fm->getFileList(path,extensionList);
	int startCount = 0;
	int endCount = MAX_LIST_SIZE;

	// How Many Screens
	int screenCount = fileList.size() / MAX_LIST_SIZE;

	if(forward) {
		/* Move forward through the screens */
		// Check what Screen we are on
		if(screenNumber == screenCount) {
			// We are at the last screen cannot move forward
			//screenNumber--;
			startCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber) : fileList.size() );
			screenNumber++;
			endCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber) : fileList.size() );			
		} else if(screenNumber < screenCount) {
			// Adjust Loop Factors
			startCount = screenNumber * MAX_LIST_SIZE;
			screenNumber++;
			endCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber) : fileList.size() );
		} else {
			// Cycle to beginning
			screenNumber = 0;
			startCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber) : fileList.size() );
			screenNumber++;
			endCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber) : fileList.size() );		
		}
	} else {
		/* Don't Move */
		if(screenNumber == 0) {
			startCount = 0;		
			endCount = (fileList.size() > MAX_LIST_SIZE) ? MAX_LIST_SIZE : fileList.size();
		} else if(screenNumber > 0) {
			endCount = ( (fileList.size() > MAX_LIST_SIZE * screenNumber) ? (MAX_LIST_SIZE * screenNumber)  : fileList.size() );
			screenNumber--;
			startCount = screenNumber * MAX_LIST_SIZE;
			screenNumber++;
		}
	}
	
	
	// Display Music List
	cout << " --------------------------------------------------------------- " << endl;
	cout << " ---------------------- Choose Music --------------------------- " << endl;
	cout << " --------------------------------------------------------------- " << endl << endl;
	cout << " Path: " << path << endl << endl;

	int i = 0;
	for(i=startCount; i < endCount; i++) {
		string listName;
		if(fileList.at(i).getIsDir()) {
			listName = "<+> " + fileList.at(i).getFileName();
		} else {
			listName = fileList.at(i).getFileName();
		}
		cout << i << " - " << listName << endl;
	}
	startCount = i;

	if(screenCount > 0) {
		cout << endl << "=======================> n for next page <=====================" << endl;
	}
	cout << endl << endl;

	cout << " --------------------------------------------------------------- " << endl;
	cout << " ------------------- Current Playlist -------------------------- " << endl;
	cout << " --------------------------------------------------------------- " << endl;
	for(int i=0; i < playList.size(); i++) {
		cout << i << " - " << playList.at(i).getFileName() << endl;
	}

	cout << endl << endl << "Enter Command (h,n,#,d #,s,q,?): ";
	return fileList;
}

void displayHelp() 
{
	cout << string(100, '\n');
	cout << "Welcome to SCPM (Simple Console Playlist Maker) Help, press 'h' to go home" << endl;
	cout << " ---------------------------------------------------------------" << endl;
	cout << "h   - (Home) Go to Home Screen with your Starting Path at any time" << endl << endl;
	cout << "u   - (Up) Go up a directory" << endl;
	cout << "n   - (Next) This will scroll through the next page of Entries in " << endl;
	cout << "      the directory if more exist.  Will scroll through the beginning again." << endl << endl;
	cout << "d # - (Delete) Where '#' is the number in the playlist.  This" << endl;
	cout << "      will remove entry from playlist" << endl << endl;
	cout << "#   - Where '#' is the number in the Music Directory.  This will" << endl;
	cout << "      add an entry to the playlist if a file.  If the entry is a" << endl;
	cout << "      directory, it will navigate to the directory and show its entries" << endl << endl;
	cout << "s   - (Save) Saves the Playlist" << endl << endl;
	cout << "q   - (Quit) Exits the Program" << endl << endl;
	cout << " --------------------------------------------------------------- " << endl << endl;
	cout << "Press h to go home: ";
}

void handleIni() {

	// Retrieve Key/Value from the ini file
	FileManager* fm;
	fm = fm->Instance();
	vector<KeyValue> iniList = fm->handleIni(iniFileName);

	// Cycle through and initialize variables
	for(int i=0; i < iniList.size(); i++) {
		if(iniList.at(i).key == "MUSIC_DIR") {
			startingPath = iniList.at(i).value;
		} else if(iniList.at(i).key == "DEFAULT_PLAYLIST") {
			playlistFile = iniList.at(i).value;
		} else if(iniList.at(i).key == "MAX_LIST_SIZE") {
			MAX_LIST_SIZE = atoi(iniList.at(i).value.c_str());
		} else if(iniList.at(i).key == "MUSIC_TYPES") {
			string extensions = iniList.at(i).value;
			// Parse the comma seperated list
			int prior = 0;
			for(int j=0; j < extensions.length(); j++) {
				if(extensions[j] == ',') {
					string extension = extensions.substr(prior,j);
					prior = j;
					extensionList.push_back(extension);
				} else if(j == extensions.length()-1) {
					string extension = extensions.substr(prior,extensions.length()-1);
					extensionList.push_back(extension);
				}
			}
		}
	}

}

bool handleCommandLine(int argc, char* argv[])
{
	bool status = true;

	// Check for the correct number of arguments - must be odd
	if((argc % 2) != 1) {
		cout << "Incorrect Number of Arguments - Try again. Correct Usage: " << endl;
		displayCorrectUsage();
		status = false;
	} else {
		for(int i=1; i < argc; i++) {
			if(string(argv[i]) == "-m") {
				// music directory
				if(i+1 < argc) {
					startingPath = argv[i+1];
				} else {
					cout << "Incorrect Syntax, try again." << endl;
					displayCorrectUsage();
					status = false;
				}
			} else if(string(argv[i]) == "-f") {
				// playlist file
				if(i+1 < argc) {
					playlistFile = argv[i+1];
				} else {
					cout << "Incorrect Syntax, try again." << endl;
					displayCorrectUsage();
					status = false;
				}

			}
		}
	}

	return status;
}

void displayCorrectUsage()
{
	cout << string(100, '\n');
	cout << "scpm [option] target" << endl;
	cout << "Arguments: "<< endl;
	cout << "-m <directory Name> - Music Directory - Default: Current Directory" << endl;
	cout << "-f <playlist file>  - Playlist File - Default: playlist.m3u" << endl;
	cout << endl << "i.e. To specify music directory and playlist file:" << endl;
	cout << "scpm -m /home/music -f /home/my_playlist.m3u" << endl;

}

