#include <Windows.h>

#include <time.h>




#define WRITECONSOLEA_FIRST 0

#define WRITECONSOLEW_FIRST 1




#define TEST_ORDER WRITECONSOLEW_FIRST	// You can configure test order here




clock_t BenchmarkA();

clock_t BenchmarkB();




HANDLE hStdOut = NULL;


int main() {

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);




	clock_t AExecTime = NULL;

	clock_t WExecTime = NULL;

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








clock_t BenchmarkA() {

	clock_t AEndTime = NULL; // Pre- declaring/defining/reserving this variable/memory region here so that the measured time is more accurate


	clock_t AStartTime = clock();

	for (int i = 0; i < 100000; i++) {

		WriteConsoleA(hStdOut, "Hello World! ", 13, NULL, NULL);

	}

	AEndTime = clock();

	return (AEndTime - AStartTime);

}








clock_t BenchmarkB() {

	clock_t WEndTime = NULL; // Pre- declaring/defining/reserving this variable/memory region here so that the measured time is more accurate


	clock_t WStartTime = clock();

	for (int i = 0; i < 100000; i++) {

		WriteConsoleW(hStdOut, L"Hello World! ", 13, NULL, NULL);

	}

	WEndTime = clock();

	return (WEndTime - WStartTime);

}