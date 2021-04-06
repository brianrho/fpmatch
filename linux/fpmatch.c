/* Copyright (C) 2021, Brian Ejike, MIT License */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/* from loadlibrary */
#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"

#include "templates.h"

/* (apparent) size of a single feature file (aka character file) 
 * after the sensor processes a single image */
#define FPM_CHAR_SIZE           256

/* size of a single template stored within the sensor's flash library
 * this varies from sensor to sensor, each template seems to hold multiple feature files,
 * one file per image captured either during enrollment (or successful verification).
 * So, in this case:
 * [[----- FEATUTE FILE (256 B) -----][----- FEATURE FILE (256 B) -----]]
 * [------------------------ TEMPLATE (512 B) --------------------------]
 */
#define FPM_TEMPLATE_SIZE       512

/* arbitrary score/confidence threshold */
#define FPM_MATCH_THRESHOLD		50

/* DLL exported function(s) */
int WINAPI (*Match2Fp)(unsigned char* Src, unsigned char* Dst);
int WINAPI (*GenChar)(unsigned char* FingerData, unsigned char* CharData);

void search_database(unsigned char * input, unsigned char ** db, uint16_t db_size);

int main(void) 
{
	setvbuf(stdout, NULL, _IONBF, 0);
	
	struct pe_image image = {
        .entry  = NULL,
        .name   = "../common/ARTH_DLL.dll",
    };
    
    /* Load the library */
    if (pe_load_library(image.name, &image.image, &image.size) == false) {
        printf("You must provide the DLL.\n");
        return 1;
    }
    
    /* Handle relocations, imports, etc. */
    link_pe_images(&image, 1);
    
    /* get the function needed for matching */
    if (get_export("Match2Fp", &Match2Fp) == -1) {
        printf("Failed to resolve Match2Fp.\n");
        return 1;
    }
    
    /* boilerplate that's probably unnecessary for this example */
    setup_nt_threadinfo(NULL);
    
    /* construct the template database we want to search */
    unsigned char *database[] = {correctMatch, template1, template2};

    /* search the database for some user input print and and see how long it takes */
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

