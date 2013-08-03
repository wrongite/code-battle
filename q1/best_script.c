// gcc -Wall -O3 -o best_script best_script.c 

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define A2I(c)		((c) - '0')

#include <stdint.h>
#include <stdio.h>

typedef uint32_t (*data_ptr)[2];

data_ptr result_ptr;
uint32_t result_header_index = 0;
uint32_t result_data[10000][2] = {{0}};
data_ptr result_header_ptr = result_data;
char result_line[6] = "\0\0\0\0\n";

int main(int argc, char** argv)
{
	FILE* fNumbers = fopen("numbers.txt", "r");
	FILE* fresult = fopen("run_result.txt", "w");

	uint32_t result_index;
	uint32_t current_number;
	
	int ch;

	while((ch = getc(fNumbers)) != EOF) {
		data_ptr current_ptr;
		if(ch == '\n' || ch == '\r') {
			continue;
		}
		current_number = A2I(ch) * 1000 + A2I(getc(fNumbers)) * 100 + A2I(getc(fNumbers)) * 10 + A2I(getc(fNumbers));
		current_ptr = result_data + current_number;

		if(current_ptr > result_header_ptr){
			data_ptr prev_ptr = current_ptr - (*current_ptr)[1] - 1;
			data_ptr next_ptr = current_ptr + (*current_ptr)[0] + 1;

			(*prev_ptr)[0] = (next_ptr - prev_ptr - 1);
			(*next_ptr)[1] = (*prev_ptr)[0];
		}
		else if(current_ptr == result_header_ptr) {
			result_header_ptr += (*result_header_ptr)[0] + 1;
		}
	}

	result_index = result_header_ptr - result_data;
	result_ptr = result_header_ptr;

	while(result_index < 10000) {
		uint32_t next_offset = (*result_ptr)[0] + 1;

		result_line[0] = ('0' + result_index /1000 % 10);
		result_line[1] = ('0' + result_index /100 % 10);
		result_line[2] = ('0' + result_index /10 % 10);
		result_line[3] = ('0' + result_index  % 10);

		fputs(result_line, fresult);

		result_ptr += next_offset;
		result_index += next_offset;
	}

	fclose(fresult);
	fclose(fNumbers);
	
	return 0;
}
