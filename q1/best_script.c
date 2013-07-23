// gcc -O3 best_script.c 

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define A2I(c)		((c) - '0')

#include <stdint.h>
#include <stdio.h>
int32_t g_header = 0;
int32_t g_result[10000][2] = {{0}};
char resultLine[6] = "\0\0\0\0\n";

int main(int argc, char** argv)
{
	FILE* fNumbers = fopen("numbers.txt", "r");
	FILE* fresult = fopen("run_result.txt", "w");

	int32_t resultIndex;
	int32_t currentNumber;
	int32_t ch;
	

	while((ch = getc(fNumbers)) != EOF) {
		if(ch == '\n' || ch == '\r') {
			continue;
		}
		currentNumber = A2I(ch) * 1000 + A2I(getc(fNumbers)) * 100 + A2I(getc(fNumbers)) * 10 + A2I(getc(fNumbers));
		
		if(currentNumber <= g_header) {
			g_header += g_result[g_header][0] + 1;
		}
		else {
			int32_t prevIndex = currentNumber + g_result[currentNumber][1] - 1;
			int32_t nextIndex = currentNumber + g_result[currentNumber][0] + 1;

			g_result[prevIndex][0] = nextIndex - prevIndex - 1;
			g_result[nextIndex][1] = -g_result[prevIndex][0];
		}
	}


	resultIndex = g_header;

	while(0 <= resultIndex  && resultIndex < 9999) {
		resultLine[0] = (resultIndex /1000 % 10 + '0');
		resultLine[1] = (resultIndex /100 % 10 + '0');
		resultLine[2] = (resultIndex /10 % 10 + '0');
		resultLine[3] = (resultIndex  % 10 + '0');

		fputs(resultLine, fresult);

		resultIndex += g_result[resultIndex][0] + 1;
	}


	fclose(fresult);
	fclose(fNumbers);
	
	return 0;
}
