#include<iostream>
#include<string>
#include<windows.h>
#include<winuser.h>
#include<TlHelp32.h>

using namespace std;
string wifiname = "";
DWORD pid;
int e;												//for catch statements

int colorset(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
	return 0;
}
string cmd(const char* command) {								//execute system commands and return them
	try {
		string result;
		char buffer[50];
		FILE *pipe = _popen(command, "r");					    //executes command and save to a ptr file names pipe
		if (!pipe) {
			cout << "[-]Error.....Exiting program.\n"; exit(EXIT_FAILURE);
		}
		result = fgets(buffer, sizeof(buffer), pipe);			//reads content inside pipe (gets only one line)
		return result;
	}
	catch (int e) {
		cout << "[!!!]Error @ command execution"<<e<<"\n";
	}
}

int wifiState(int status) {
	try {
		string command;
		if (status == 0) command = "netsh wlan disconnect";									//command to disconnect
		if (status == 1) command = "netsh wlan connect name=" + wifiname;					//command to connect to <network>
		cmd(command.c_str());																//execute command
		return 0;
	}
	catch (int e) { cout << "[!!!]Error @ WiFi State Change" << e << "\n"; }
}

int getProcID(const char* programName) {																				//get processID function
	try {
		PROCESSENTRY32 program;
		program.dwSize = sizeof(PROCESSENTRY32);
		auto snaps = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);													//take snapshot of precess(running)
		if (snaps == INVALID_HANDLE_VALUE) { cout << "[-]Error.....Exiting Program.\n"; exit(EXIT_FAILURE); }
		while (Process32Next(snaps, &program)) {																		//go through the processIDs
			if (!(strcmp(programName, program.szExeFile))) {															//check for a match (comparing with exe names)
				pid = program.th32ProcessID;																			//take processID value
				CloseHandle(snaps);																						//closing snap process
				return 0;
			}
		}
		return 0;
	}
	catch (int e) {
		cout << "[!!!]Error @ ProcessID" << e << "\n";
	}
}

int SusResProcess() {
	try {
		THREADENTRY32 thread;
		thread.dwSize = sizeof(THREADENTRY32);
		HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);													//taking snaps of all handles running
		if (handleSnap == INVALID_HANDLE_VALUE) { cout << "[-]Error.....Exiting Program.\n"; exit(EXIT_FAILURE); }
		if (!(Thread32First(handleSnap, &thread))) { cout << "[-]Thread capture error\n"; }									//access the first thread details				
		do {																												//check
			if (thread.th32OwnerProcessID == pid) {
				//do all suspend and resume operations here
				HANDLE hthread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, thread.th32ThreadID);
				SuspendThread(hthread);
				Sleep(7000);
				ResumeThread(hthread);
				CloseHandle(hthread);
				CloseHandle(handleSnap);
				return 0;
			}
		} while (Thread32Next(handleSnap, &thread));																		//goto next thread for checking
		return 0;
	}
	catch (int e) {
		cout << "[!!!]Error @ Program Threads" << e << "\n";
	}
}

int instructions() {
	try {
		Sleep(2500);
		colorset(11);//system("color c");
		cout << "\n[***]NOTE :\n\t[*]Keep program running while playing the game to use functions.\n\t[*]All HotKeys will be disabled on closing this program.\n\t[*]SUS/RES (suspend/resume) will first suspend and then resume program after 7 seconds.\n";
		colorset(14);//system("color 7");
		cout << "\nINSTRUCTIONS:\n\tWiFi OFF:\t[F5 KEY]\n\tWiFi ON\t:\t[F6 KEY]\n\tSUS/RES\t:\t[F7 KEY]\n\tEXIT\t:\t[F8 KEY]\n";
		cout << "\n[*]Program is now active...\n";
		return 0;
	}
	catch (int e) {
		cout << "[!!!]Error at instruction function." << e << "\n";
	}
}

int main() {
	try {
		LPCTSTR title = "SolPlay V0.1 by CipherKill";
		SetConsoleTitle(title);
		colorset(11);
		//intro
		cout << "SolPlay V0.1 by CipherKill\n\n";
		colorset(14);
		Sleep(1000);
		cout << "Hope your not scared of terminals.... \n\t\t(I'll make a GUI for the next version)\n\t\t\txd\n";
		Sleep(1500);
		cout << "\n[-]Acquiring System Assets.....\n\n";
		Sleep(1500);
		colorset(10);
		//initialization
		cout << "[!]Registered WiFi Name\n"; Sleep(500);
		if (RegisterHotKey(NULL, 1, NULL | 0x4000, 0x74)) { cout << "[!]Registered Hotkey: F5\n"; Sleep(500); }															//f5 for wifi off
		if (RegisterHotKey(NULL, 2, NULL | 0x4000, 0x75)) { cout << "[!]Registered HotKey: F6\n"; Sleep(500); }															//f6 for wifi on
		if (RegisterHotKey(NULL, 3, NULL | 0x4000, 0X76)) { cout << "[!]Registered Hotkey: F7\n"; Sleep(500); }															//f7 for kickstart process
		if (RegisterHotKey(NULL, 4, NULL | 0x4000, 0x77)) { cout << "[!]Registered Hotkey: F8\n"; Sleep(500); }
		string command, reply, input;
		int len;
		string programName = "GTA5.exe";
		cout << "\n[-]Initialization complete :)\n";
		Sleep(1500);
		system("cls");
		//name intro
		colorset(14);
		Sleep(1500);
		cout << "Using default game: GTA5.exe\n";
		Sleep(1500);
		cout << "Program Name (Press [RETURN] to use default):~ ";
		getline(cin, input);
		if (input.length() > 0) programName = input;
		cout << "\nSelected : " << programName << "\n\n";
		instructions();
		//extracting wifiname
		command = "netsh wlan show interfaces | find \"SSID\"";
		reply = cmd(command.c_str());										//executing the wifilist command
		len = strlen(reply.c_str());										//length of the output
		for (int i = 29; i < len - 1; i++) {									//to extract the name of the wifi from the string line
			wifiname += reply[i];
		}

		//main executions
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0) {
			if (msg.wParam == 1) { wifiState(0); }										//wifi off
			else if (msg.wParam == 2) { wifiState(1); }									//wifi on
			else if (msg.wParam == 3) {													//suspend/resume
				getProcID(programName.c_str());
				if (pid == 0) {
					cout << "\n[!!!]Could not find processID for program....Exiting....\n";
					system("pause");
					exit(0);
				}
				SusResProcess();
			}
			else if (msg.wParam == 4) { cout << "\n\n[!]Exiting program\n"; Sleep(1500); exit(0); }
		}

		return 0;
	}
	catch (int e) {
		cout << "[!!!!]Error at main function" << e << "\n";
	}
}
