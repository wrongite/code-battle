// g++ -std=c++0x -Wall -O2 -o best_script best_script.cpp 

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define A2I(c)		((c) - '0')

#define I2A(chptr, data) do { \
	--chptr; \
	*chptr = (data % 10 + '0'); \
	data /= 10; \
} while(data > 0)


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map>

using std::unordered_map;

const uint32_t keymax2 = 4096;

struct Result 
{
	uint32_t data;
	uint32_t* countPtr;
	Result* nextPtr;

	Result(uint32_t _data, uint32_t* _countPtr, Result* _next=NULL) 
		: data(_data), countPtr(_countPtr), nextPtr(_next)
	{
	}
};

Result* resultHeader = NULL;

typedef Result* ResultPtr;
typedef unordered_map<uint32_t, uint32_t*> Dict;

char wLineBuffer[100];


int main(int argc, char** argv)
{
	Dict data;

	FILE* fNumbers = fopen("numbers.txt", "r");
	FILE* fresult = fopen("run_result.txt", "w");

	int32_t currentNumber = 0;
	int ch;


	while((ch = getc(fNumbers)) != EOF) {
		if(ch == '\n') {
			uint32_t key1 = currentNumber / keymax2;
			uint32_t key2 = currentNumber % keymax2;
			Dict::iterator kit = data.find(key1);
			uint32_t* &subarray = data[key1];
			if(kit != data.end()) {
				subarray[key2] += 1;

				if(subarray[key2] == 2) {
					resultHeader = new Result(currentNumber, &subarray[key2], resultHeader);
				}
			}
			else {
				subarray = new uint32_t[keymax2];
				memset(subarray, 0, sizeof(uint32_t) * keymax2);
				subarray[key2] = 1;
			}

			currentNumber = 1;
		}
		else if(ch == '\r') {

		}
		else {
			currentNumber = (currentNumber * 10) + A2I(ch);
		}
	}

	wLineBuffer[99] = 0;
	while(resultHeader != NULL) {
		char* chptr = &wLineBuffer[99];
		I2A(chptr, resultHeader->data);

		fputc('"', fresult);
		fputs(chptr + 1, fresult);
		fputs("\", ", fresult);

		chptr = &wLineBuffer[99];
		I2A(chptr, *resultHeader->countPtr);
		fputs(chptr, fresult);
		fputc('\n', fresult);

		Result* next = resultHeader->nextPtr;
		delete resultHeader;
		resultHeader = next;
	}

	fclose(fresult);
	fclose(fNumbers);
	

	for(Dict::iterator it = data.begin(); it != data.end(); it++) {
		delete[] it->second;
	}

	return 0;
}
