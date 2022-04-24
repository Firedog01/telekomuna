#include "ReaderWriter.h"
#include <ncurses\curses.h>
#include <iostream>
using namespace std;

int main(int argn, char** args){
	ReaderWriter readerWriter(args[1]);

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	scrollok(stdscr, TRUE);

	int x = 0, y = 0;

	int toWrite;
	int received;

	while(true){
		//nadawanie
		toWrite = getch();
		if(toWrite != ERR){
			if(toWrite == '\n')
				toWrite = '\r';
			readerWriter.write((unsigned char)toWrite);
		}

		//odbieranie i wypisywanie
		received = readerWriter.read();
		if(received != -1 && received != '\n'){
			unsigned char ch = (unsigned char)received;
			if(ch == '\b'){
				if(x > 0){
					x--;
					move(y, x);
					addch(' ');
					move(y, x);
				}
			}else if(ch == '\r'){
				if(y == LINES - 1){
					scrl(1);
				}else{
					y++;
				}
				x = 0;
				move(y, x);
			}else{
				addch(ch);
				if(x == COLS - 1){
					x = 0;
					if(y < LINES - 1)
						y++;
				}else{
					x++;
				}
			}
			refresh();
		}
	}
}
