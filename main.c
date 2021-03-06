/*
 *
 * Zachary Lazow, Ethan Jones. 
	There is an issue with strdup(token) on line 30. The memory is never deallocated even though I call free on the words array that contains it.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>


char** tokenify(const char *s) {
    // input a constant string --> return an array of token strings (that were separated by whitespace)
	int count = 0;
	char *copy = strdup(s);
	char *token;
	char **words=malloc(sizeof(char*)*(strlen(s)));
	token = strtok(copy ," \n\t");
	while (token!=NULL){
		//Error case is null...so no redundancy needed 
		if (strstr(token, "#")==NULL){
		//if the line contains a #, ignore the rest of the tokens.
			words[count]=strdup(token);
			token = strtok(NULL, " \n\t");
			count++;	
		}
		else{
			if (token[0]=='#'){
				break;
			}
			//slice up to #
			char *token_hash=strtok(token, "#");
			words[count]=strdup(token_hash);
			count++;
			break;
		}
	}
	words[count]=NULL;
	free(copy);
	return words;
	
	
}

void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function

/* 
Basic Algorithm
0) Open file
1) Read through each line -- fgets().
2) Tokenify the line. Ignore comments (#) and blanklines.
	a) If not in comment-->if token == int --> add to link list.
	b) Else ignore.
3) Sort linked list.
4) Print to command line:
	a) Linked List
	b) CPU Resource Statistics (formatted)
		i) amount of time program spent executing in user space
		ii) amount of time spent executing in kernel space.

*/


	printf("Starting..\n");
	struct node *head=NULL;
	char line[1024];
	while (fgets(line, 1024, input_file)!=NULL){
		//printf("Line: ");
		//printf("%s", line);
		char ** tokens = tokenify(line);
		for (int i = 0; tokens[i]!=NULL; i++){
			//loop through all indexes in the token...isdigt then....		
			int is_int = 1;
			for (int j=0; j<strlen(tokens[i]); j++){
				if (j==0){
		//check if first char in a word is negative symbol.
					if (tokens[i][j]=='-'){
						continue;
					}
				}
				if (!isdigit(tokens[i][j])){
					//check negative numbers...
					is_int=0;
					break;
					
				}
			}
	
			if (is_int){
				//do not to worry if atoi=0 [can't convert] b/c we already check if its a number.
				int int_token = atoi(tokens[i]);
				list_append(int_token, &head);
			}
			
			
		}
		free(tokens);
	}
	printf("*** List Contents Begin ***\n");
	list_print(head);
	list_delete(head);

}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
	//time stuff;

	printf("*** List Contents End ***\n");
    	struct timeval user; 
    	struct timeval sys;        
    	struct rusage usage;
	//redundancy case
	if(getrusage(RUSAGE_SELF, &usage) != 0) {
        	printf("rusage children error: %s", strerror(errno));
        	exit(-1);
    	}
    	user = usage.ru_utime;
    	sys = usage.ru_stime;
	printf("User time: %f\n", (double)user.tv_sec		+(double)user.tv_usec/1000000);
    	printf("System time: %f\n", (double)sys.tv_sec+(double)sys.tv_usec/1000000);


    return 0;
}
#endif
