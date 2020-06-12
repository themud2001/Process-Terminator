#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

void killProcess(string pName) {
	HANDLE process;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(Process32First(snapshot, &pe32)) {
		while(Process32Next(snapshot, &pe32)) {
			if((string)pe32.szExeFile == (string)pName) {
				if(process = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID)) {
					TerminateProcess(process, 0);
					cout<<"Found it and closed it!"<<endl;
				} else {
					cout<<"Didn't find it!"<<endl;
				}
				break;
			}
		}

		CloseHandle(process);
		CloseHandle(snapshot);
	}
}

int main() {
	string processName;

	cout<<"Enter a process name to terminate: ";
	cin>>processName;

	killProcess(processName);
	system("pause");

	return 0;
}