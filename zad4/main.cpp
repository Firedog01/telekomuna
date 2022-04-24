#include <iostream>
#include <windows.h>
#include "mmsystem.h"
#include <filesystem>

using namespace std;

string getPathFromUser();
void recordSound();
void playSound(string file_path);
string sendMci(string command);

int main() {
	char in;
	cout << "Do you want to record [y/N]: ";
	in = (char)getchar();
	if(in == 'y' || in == 'Y') {
		recordSound();
	} else {
		string path = getPathFromUser();
		cout << "Playing " << path << '\n';
		playSound(path);
	}
	system("pause");
	return 0;
}

string getPathFromUser() {
	string path = "..\\sound_files";
	string s;
	vector<filesystem::path> dir_paths;
	uint8_t i = 0;
	for (const filesystem::directory_entry & entry : filesystem::directory_iterator(path)) {
		s = entry.path().string();
		s = s.substr(s.find_last_of('\\') + 1);
		cout << +i++ << ". " << s << '\n';
		dir_paths.push_back(entry.path());
	}
	cout << "Choose number: ";
	cin >> s;
	int no_file = stoi(s);
	return dir_paths.at(no_file).string();
}

void playSound(string file_path) {
	sendMci("open waveaudio!" + file_path + " alias myaudio");
	sendMci("play myaudio wait");
	sendMci("close myaudio wait");
}

void recordSound() {
	sendMci("open new type waveaudio alias rec");
	sendMci("set rec time format ms");
	sendMci("record rec notify");
	cout << "Recording! Press any key to stop. \n";
	{ getchar(); getchar(); }

	sendMci("stop rec");
	sendMci("save rec ../sound_files/record.wav");
	sendMci("close rec");
	cout << "Recording saved as record.wav\n";
}

string sendMci(string command) {
	char ret[255];
	mciSendString(command.c_str(), ret, sizeof(ret), NULL);
	return {ret};
}
