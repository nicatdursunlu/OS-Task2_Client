#include <Windows.h>
#include <iostream>

using namespace std;

#define buf_size 1024

int main() {

	HANDLE pipe1;
	char buffer[buf_size];
	DWORD num_byte;

	pipe1 = CreateFile(
		"\\\\.\\pipe\\pipe1", 
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	cin >> buffer;

	BOOL write1 = WriteFile(
		pipe1,
		buffer,
		sizeof(buffer),
		&num_byte,
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

	CloseHandle(pipe1);

	return 0;
}