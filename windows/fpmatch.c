/* Copyright (C) 2021, Brian Ejike, MIT License */

/* Make sure to link the necessary ARTH_DLL.dll
 * Use this with gcc linker options:
 * 		-L"<DLLPath>" -Xlinker --enable-stdcall-fixup -m32
 
 * e.g. (untried) gcc -o fpmatch.exe fpmatch.c -I..\common -L..\common -lARTH_DLL -Xlinker --enable-stdcall-fixup -m32
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include <Windows.h>

#include "templates.h"

/* (apparent) size of a single feature file (aka character file) 
 * after the sensor processes a single image */
#define FPM_CHAR_SIZE           256

/* Size of a single template stored within the sensor's flash library
 * this varies from sensor to sensor, each template seems to hold multiple feature files
 * one file per image captured either during enrollment or verification */
#define FPM_TEMPLATE_SIZE       512

/* arbitrary score/confidence threshold */
#define FPM_MATCH_THRESHOLD		50

/* DLL exported function(s) */
int WINAPI Match2Fp(unsigned char* Src,unsigned char* Dst);
int WINAPI GenChar(unsigned char* FingerData, unsigned char* CharData);

void search_database(unsigned char * input, unsigned char ** db, uint16_t db_size);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
    
    /* template database we want to search */
	unsigned char *database[] = {correctMatch, template1, template2};

	/* perform a bunch of matches and check how long they take */
	clock_t begin, end;
	begin = clock();
	
	search_database(userInput, database, sizeof(database)/sizeof(database[0]));
	
	end = clock();

	printf("Took %lf secs.\n", (double)(end - begin) / CLOCKS_PER_SEC);

	return 0;
}

/* search a given database for an input feature file and print all scores */
void search_database(unsigned char * input, unsigned char ** db, uint16_t db_size) 
{ 
    for (int i = 0; i < db_size; i++)
    {
        unsigned char * template = db[i];
        
        /* match user input against first character file in the template */
        int first = Match2Fp(input, template);
        
        /* match user input against second character file */
        int second = Match2Fp(input, template + FPM_CHAR_SIZE);
        
        /* use the average to arrive at some final score, whatever you like */
        int avg_score = (first + second) / 2;
        
        printf("First: %d, Second: %d, Average: %d\n", first, second, avg_score);
        printf("%s\n\n", avg_score > FPM_MATCH_THRESHOLD ? "Templates match." : "Templates do not match!");
    }
}
