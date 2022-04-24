#include <iostream>
#include <Windows.h>
#include "mmsystem.h"
#include "colors.h"
#include <stdio.h>
#include <filesystem>

#define LIGMA_SUGMA_JOE 2137

using namespace std;

string getPathFromUser();
void recordSound();
DWORD recordWAVEFile(DWORD ms);

int main() {
	char in;
	cout << "Do you want to record [y/N]: ";
	in = (char)getchar();
	if(in == 'y' || in == 'Y') {
//		recordSound();
		recordWAVEFile(10000);
	} else {
		string path = getPathFromUser();
		cout << path << '\n';
		PlaySound(TEXT(path.c_str()), NULL, SND_ASYNC);
		system("pause");
	}


	return LIGMA_SUGMA_JOE;


	cout << "\n\n\n\n\n\n\n";

    cout    << f_cyan << "What do ya wanna do?\n" << s_reset
            << "[1] Play some rly good stuff :)\n"
            << "[2] Hear the sound of Parostatek.\n"
            << "[3] Let's record mah sweet voice!\n"
            << "[4] Hear me ROAR!\n";

    LPCSTR fileName;
    bool ready = false;

    switch(getchar()) {
        case '2': { fileName = "Parostatek.wav"; break; }
        case '3': { ready = true; break; }
        case '4': { fileName = "record.wav"; break; }
        default: { fileName = "../TakeMeHome.wav"; cout << f_cyan << "Almost heaven, West Virginia...\n" << s_reset; break; }
    }

    if( ready == false ) {

        system("pause");
    }
    else {
		char ReturnString[300];
		int mci_error;

/* Rozpoczęcie procedury. */
		mci_error = mciSendString("open new type waveaudio alias xD", ReturnString, sizeof(ReturnString), NULL);

/* Ustawienie formatu czasu na milisekundy. */
		mci_error = mciSendString("set xD time format ms", ReturnString, sizeof(ReturnString), NULL);

/* Nagrywanie. */
		mci_error = mciSendString("record xD notify", ReturnString, sizeof(ReturnString), NULL);

		cout << f_cyan << "Now on air. Press a key to staph it...\n" << s_reset;
		getchar(); getchar();

/* Zatrzymanie nagrywania. */
		mci_error = mciSendString("stop xD", ReturnString, sizeof(ReturnString), NULL);

/* Zapisywanie do pliku WAV. */
		mci_error = mciSendString("save xD record.wav", ReturnString, sizeof(ReturnString), NULL);

/* Koniec procedury. */
		mci_error = mciSendString("close xD", ReturnString, sizeof(ReturnString), NULL);
		cout << f_green << "We're done here. Re-open capriciosa.exe and play your record. \n" << s_reset;
    }
	getchar();

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
	mciSendString("open new type waveaudio alias candice", ReturnString, sizeof(ReturnString), NULL);

	// Ustawienie formatu czasu na milisekundy.
	mciSendString("set candice time format ms", ReturnString, sizeof(ReturnString), NULL);

	// Nagrywanie.
	mciSendString("record candice notify", ReturnString, sizeof(ReturnString), NULL);
	cout << "Recording! Press any key to stop. \n";
	{ getchar(); getchar(); }

	//Zatrzymanie nagrywania.
	mciSendString("stop candice", ReturnString, sizeof(ReturnString), NULL);

	// Zapisywanie do pliku WAV.
	mciSendString("save candice ../sound_files/record.wav", ReturnString, sizeof(ReturnString), NULL);

	// Zamknięcie procedury.
	mciSendString("close candice", ReturnString, sizeof(ReturnString), NULL);
	cout << "Recording saved as record.wav\n";
}


// Uses the MCI_OPEN, MCI_RECORD, and MCI_SAVE commands to record and
// save a waveform-audio file. Returns 0L if successful; otherwise,
// it returns an MCI error code.

typedef struct {
	DWORD_PTR    dwCallback;
	MCIDEVICEID  wDeviceID;
	LPCSTR       lpstrDeviceType;
	LPCSTR       lpstrElementName;
	LPCSTR       lpstrAlias;
} MCI_OPEN_PARMS;

DWORD recordWAVEFile(DWORD dwMilliSeconds)
{
	UINT wDeviceID;
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;
	MCI_RECORD_PARMS mciRecordParms;
	MCI_SAVE_PARMS mciSaveParms;
	MCI_PLAY_PARMS mciPlayParms;

	// Open a waveform-audio device with a new file for recording.
	mciOpenParms.lpstrDeviceType = "waveaudio";
	mciOpenParms.lpstrElementName = "";
	if (dwReturn = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD) &mciOpenParms))
	{
		// Failed to open device; don't close it, just return error.
		return (dwReturn);
	}

	// The device opened successfully; get the device ID.
	wDeviceID = mciOpenParms.wDeviceID;

	// Begin recording and record for the specified number of
	// milliseconds. Wait for recording to complete before continuing.
	// Assume the default time format for the waveform-audio device
	// (milliseconds).
	mciRecordParms.dwTo = dwMilliSeconds;
	if (dwReturn = mciSendCommand(wDeviceID, MCI_RECORD,
								  MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &mciRecordParms))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return (dwReturn);
	}

	// Play the recording and query user to save the file.
	mciPlayParms.dwFrom = 0L;
	if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY,
								  MCI_FROM | MCI_WAIT, (DWORD)(LPVOID) &mciPlayParms))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return (dwReturn);
	}
	if (MessageBox(hMainWnd, "Do you want to save this recording?",
				   "", MB_YESNO) == IDNO)
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return (0L);
	}

	// Save the recording to a file named TEMPFILE.WAV. Wait for
	// the operation to complete before continuing.
	mciSaveParms.lpfilename = "tempfile.wav";
	if (dwReturn = mciSendCommand(wDeviceID, MCI_SAVE,
								  MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID) &mciSaveParms))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return (dwReturn);
	}

	return (0L);
}