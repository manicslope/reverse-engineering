#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <windows.h>

using namespace std;

/*
Finds mines, works better if some fields already opened
Old
*/

int main()
{
	char buffer;
	DWORD pid, line, loop;
	HWND hwnd = FindWindowA(NULL, "Minesweeper");
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE h = OpenProcess(PROCESS_VM_READ, FALSE, pid);
	string smth, collect = "", result = "";
	for (line = 0x01005340; line <= 0x01005660; line++) {
		ReadProcessMemory(h, (LPVOID)line, &buffer, sizeof(buffer), 0);
		smth = std::to_string((int)buffer);
		if (smth == "15")
			smth = "[#]";
		else if (smth == "-113")
			smth = "[X]";
		else if (smth == "16")
			smth = "[*]";
		else
			smth = "[ ]";
		collect += smth;
		if (smth == "[*]") {
			if (collect != "[*]") {
				collect = collect.substr(0, collect.size() - 3);
				if ((collect.length() != 63) && (collect.length() != 42))
					//cout << collect << endl;
					result += collect + "\n";
			}
			collect = "";
		}
	}
	cout << result;
	
	
	system("pause");
	return 0;

};
