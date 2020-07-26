#include <iostream>
#include <windows.h>

using namespace std;

int main() {
	HWND hwnd = FindWindowA(NULL, "Minesweeper");
	//cout << "hi";
	if (!hwnd)
		cout << "no hwnd" << endl;
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (!pid)
		cout << "no pid" << endl;
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	//int error = GetLastError();
	//cout << error << endl;
	if (!h)
		cout << "no h" << endl;
	int value;
	int i = 0;
	int n = 0x0e;  // flag
	// DWORD address = 0x01005340;
	for (int address = 0x01005340; address <= 0x01005660; address++) {
		ReadProcessMemory(h, (LPVOID)address, &value, 1, 0);
		value = value & 0xff;
		if (value == 0x8f)  // bomb
			WriteProcessMemory(h, (PBYTE*)address, &n, 1, 0);
		/*
		if ((i % 2 != 0) && (value != 0x10))
			cout << std::hex << value << " ";
		if (value == 0x10) {
			cout << endl;
			i++;
		}
		*/
	}
	cin.get();
}
