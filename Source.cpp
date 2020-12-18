#include <Windows.h>
#include <iostream>

using namespace std;
#define buf_size 1024

int main() {

	HANDLE FileMap;
	BOOL Result;
	PCHAR lpBuffer = NULL;

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
