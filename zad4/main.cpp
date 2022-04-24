#include <iostream>
#include <Windows.h>
#include "mmsystem.h"
#include <cstdio>
#include <filesystem>

using namespace std;

string getPathFromUser();
void recordSound();

int main() {
	char in;
	cout << "Do you want to record [y/N]: ";
	in = (char)getchar();
	if(in == 'y' || in == 'Y') {
		recordSound();
	} else {
		string path = getPathFromUser();
		cout << "Playing " << path << '\n';
		PlaySound(TEXT(path.c_str()), NULL, NULL);
		system("pause");
	}
	return 0;
}

string getPathFromUser() {
	string path = "..\\sound_files";
	string s;
	vector<filesystem::path> dir_paths;
	uint8_t i = 0;
	for (const filesystem::directory_entry & entry : filesystem::directory_iterator(path)) {
		s = entry.path().string();
		cout << +i++ << ". " << s.substr(s.find_last_of('\\') + 1) << '\n';
		dir_paths.push_back(entry.path());
	}

	cout << "Choose number: ";

	cin >> s;
	int no_file = stoi(s);
	return dir_paths.at(no_file).string();
}

void recordSound() {
	char ReturnString[300];

	// Otwarcie procedury.
	mciSendString("open new type waveaudio alias rec", ReturnString, sizeof(ReturnString), NULL);

	// Ustawienie formatu czasu na milisekundy.
	mciSendString("set rec time format ms", ReturnString, sizeof(ReturnString), NULL);

	// Nagrywanie.
	mciSendString("record rec notify", ReturnString, sizeof(ReturnString), NULL);
	cout << "Recording! Press any key to stop. \n";
	{ getchar(); getchar(); }

	//Zatrzymanie nagrywania.
	mciSendString("stop rec", ReturnString, sizeof(ReturnString), NULL);

	// Zapisywanie do pliku WAV.
	mciSendString("save rec ../sound_files/record.wav", ReturnString, sizeof(ReturnString), NULL);

	// Zamknięcie procedury.
	mciSendString("close rec", ReturnString, sizeof(ReturnString), NULL);
	cout << "Recording saved as record.wav\n";
}
