#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data {
        /*  members for airport data in array */
        
        int airport_id;
        int arrival_counter;
        int depart_counter;
        char *name;
        char *city;
        char *country;
        char *iata;
        char *icao;
        
} TStoixeiouEvr;

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source);

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem);

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

char * readline(FILE *fp);

void lineByline(FILE * file,TStoixeiouEvr *Elem);

int countlines(FILE * file);

void parse_line(TStoixeiouEvr *Elem,char *buffer);
//void parse_line(TStoixeiouEvr *Elem,char *buffer/*,int *counter*/);
int read_routes_file(FILE * file,int *source_id,int *dest_id);

void parse_line_routes(char *buffer,int *source_id,int *dest_id);

void destruct_copies(int max_routes,TStoixeiouEvr *Elem);

void destruct_data(TStoixeiouEvr *Elem);

#endif
