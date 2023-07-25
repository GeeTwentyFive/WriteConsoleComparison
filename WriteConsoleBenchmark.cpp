#include <Windows.h>




#define WRITECONSOLEA_FIRST 0

#define WRITECONSOLEW_FIRST 1




#define TEST_ORDER WRITECONSOLEW_FIRST	// You can configure test order here




long long BenchmarkA();

long long BenchmarkB();




HANDLE hStdOut = NULL;


int main() {

	SetThreadAffinityMask(GetCurrentThread(), 0);


	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);




	long long AExecTime = NULL;

	long long WExecTime = NULL;

	if (TEST_ORDER == WRITECONSOLEA_FIRST) {

		AExecTime = BenchmarkA();

		WExecTime = BenchmarkB();

	}

	else {

		WExecTime = BenchmarkB();

		AExecTime = BenchmarkA();

	}




	char AExecTime_str[256] = { 0 };
	_itoa_s(AExecTime, AExecTime_str, 10);

	char AResultOut[1024] = { "\nWriteConsoleA execution time:\t" };
	strcat_s(AResultOut, AExecTime_str);
	strcat_s(AResultOut, "\tclock cycles\n");


	char WExecTime_str[256] = { 0 };
	_itoa_s(WExecTime, WExecTime_str, 10);

	char WResultOut[1024] = { "\nWriteConsoleW execution time:\t" };
	strcat_s(WResultOut, WExecTime_str);
	strcat_s(WResultOut, "\tclock cycles\n");




	WriteConsoleA(hStdOut, AResultOut, strlen(AResultOut), NULL, NULL);

	WriteConsoleA(hStdOut, WResultOut, strlen(WResultOut), NULL, NULL);




	while (!(GetKeyState(VK_ESCAPE) & 0x8000)) {}




	return 0;

}








long long BenchmarkA() {

	// Pre- declaring/defining/reserving so that the measured time is more accurate
	LARGE_INTEGER AStartTime = { 0 };
	LARGE_INTEGER AEndTime = { 0 };


	QueryPerformanceCounter(&AStartTime);


	for (int i = 0; i < 100000; i++) {

		WriteConsoleA(hStdOut, "Hello World! ", 13, NULL, NULL);

	}


	QueryPerformanceCounter(&AEndTime);


	return (AEndTime.QuadPart - AStartTime.QuadPart);

}








long long BenchmarkB() {

	// Pre- declaring/defining/reserving so that the measured time is more accurate
	LARGE_INTEGER WStartTime = { 0 };
	LARGE_INTEGER WEndTime = { 0 };


	QueryPerformanceCounter(&WStartTime);


	for (int i = 0; i < 100000; i++) {

		WriteConsoleW(hStdOut, L"Hello World! ", 13, NULL, NULL);

	}


	QueryPerformanceCounter(&WEndTime);


	return (WEndTime.QuadPart - WStartTime.QuadPart);

}
