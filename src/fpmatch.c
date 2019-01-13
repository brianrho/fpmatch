/*
 ============================================================================
 Name        : fpmatch.c
 Author      : Brian Ejike (2018, brianrho94@gmail.com)
 Version     :
 Copyright   : MIT licence
 Description : Template matching
 ============================================================================
 */

/* Make sure to link the necessary ARTH_DLL.dll
 * On windows, use this with gcc linker options:
 * 		-L"C:\library-path" -Xlinker --enable-stdcall-fixup -m32
 *
 * The prototypes are in matching.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "matching.h"
#include "templates.h"

#define MATCH_THRESHOLD		50

void match_pair(unsigned char * one, unsigned char * two);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int score;

	/* perform a bunch of matches and check how long they take */
	clock_t begin, end;
	begin = clock();
	for (int i = 0; i < 1000; i++) {
		score = Match2Fp(template18, template16);
	}
	end = clock();

	printf("Match result: %d, took %lf secs.\n", score, (double)(end - begin) / CLOCKS_PER_SEC);
	if (score > MATCH_THRESHOLD)
		printf("Templates match.\n");
	else
		printf("Templates do not match!\n");

	return 0;
}

/* print scores from all possible combos */
void match_pair(unsigned char * one, unsigned char * two) {
	int score = Match2Fp(one, two);
	printf("Score 1: %d\r\n", score);

	score = Match2Fp(one, two+256);
	printf("Score 2: %d\r\n", score);

	score = Match2Fp(one+256, two);
	printf("Score 3: %d\r\n", score);

	score = Match2Fp(one+256, two+256);
	printf("Score 4: %d\r\n", score);
}
