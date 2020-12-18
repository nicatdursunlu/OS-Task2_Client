#include <Windows.h>
#include <iostream>

using namespace std;
#define buf_size 1024

int main() {

	HANDLE pipe1;
	char buffer[buf_size];
	DWORD num_byte;

	pipe1 = CreateNamedPipe(
		"\\\\.\\pipe\\pipe1",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		buf_size,
		buf_size,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL
	);

	cout << "pipe created" << endl;

	ConnectNamedPipe(
		pipe1,
		NULL
	);

	BOOL read1 = ReadFile(
		pipe1,
		buffer,
		sizeof(buffer),
		&num_byte,
		NULL
	);

	cout << "Message: " << buffer << endl;

	strcpy(buffer, "   comp_eng   ");

	BOOL write1 = WriteFile(
		pipe1,
		buffer,
		sizeof(buffer),
		&num_byte,
		NULL
	);

	CloseHandle(pipe1);


	HANDLE FileMap;
	BOOL Result;
	PCHAR lpBuffer = NULL;
	char Buffer[buf_size] = "Hello from Computer Engineering Server";
	size_t bufferSize = sizeof(Buffer);

	// Open File Mapping 
	FileMap = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		L"Local\\MyFileMap"
	);

	if (FileMap == NULL) {
		cout << "OpenFileMapping Failed  " << GetLastError() << endl;
	}

	cout << "OpenFileMapping Success  " << endl;

	cout << "Data from the server ->  " << lpBuffer << endl;

	if (lpBuffer == NULL) {
		cout << "MapViewOfFile Failed  " << GetLastError() << endl;
	}

	cout << "MapViewOfFile Success  " << endl;

	// UnmapViewOfFile
	Result = UnmapViewOfFile(lpBuffer);
	if (Result == FALSE) {
		cout << "UnmapViewOfFile Failed" << GetLastError() << endl;
	}

	cout << "UnmapViewOfFile Success" << endl;

	CloseHandle(FileMap);

}