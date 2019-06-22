#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
pswd Program specification  :         2019-01-01    w. albert

Program : pswd is to generate a selection of character strings composed of randomly selected characters
suitable for use as computer passwords.

pswd is to be a command line program.

Usage: pswd password_length number_of_passwords [ optional list of special characters to be used ]


*/

// command line arguments are as follows

#define LENGTH_OF_PASSWORD_REQUESTED cmd_line_args[1]
#define NUMBER_OF_SAMPLES_REQUESTED cmd_line_args[2]
#define DESIGNATED_SPECIAL_CHARACTERS cmd_line_args[3]

// some constants

#define PW_PRINT_PER_LINE 4
#define N_CAP 5 /* number of time to include 26 capital letters */
#define N_LOW 7 /* number of times to include 26 lower case letters */
#define N_NUM 10 /* number of times to include 10 numeric characters */
#define N_SPL 7 /* number of times to include list of special characters */

#define MIN_PSWD_LENGTH 8 /* minimum length of a password */
#define MAX_PSWD_LENGTH 24 /* maximum length of a password */
#define MIN_PSWD_REQUESTS 1 /* minimum number of password requests */
#define MAX_PSWD_REQUESTS 20 /* maximum number of password requests */
#define MAX_OPTIONAL_SPECIAL_CHARACTERS 20 /* maximum length of optional special characters string */

#define ITERATIONS iterations

int main (int nof_args, char **cmd_line_args);

int main (int nof_args, char **cmd_line_args)

{
	//	 creating character strings	
	
	int i,j,k,l,m,n, total_string_length,  retc = 0, new_pw_length, iteration, iterations;
	char *string_A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	     *string_a = "abcdefghijklmnopqrstuvwkyz",
	     *string_0 = "0123456789",
	     *default_string_$ = "~!@#$^&*+=?-.[]{}",
	     *string_$ = default_string_$, 
	     *source_string;
	     
	int *sort_keys, sort_key_save; char char_save;
	
	// checking and processing the command line
	
	 if (4==nof_args)  
	 	if (strlen(DESIGNATED_SPECIAL_CHARACTERS) < 1 | strlen(DESIGNATED_SPECIAL_CHARACTERS) > MAX_OPTIONAL_SPECIAL_CHARACTERS)
	 	 {  printf("Number of special characters must be at least 1 and not more than %d\n", MAX_OPTIONAL_SPECIAL_CHARACTERS); return(1); }
	 	 else {	 	string_$ =  DESIGNATED_SPECIAL_CHARACTERS; 
	 			puts("Special Character list specified on command line");  }	
	
	
    if (3==nof_args | 4==nof_args) ; else { puts ("Enter number of characters desired for new password\nfollowed by number of keys to generate on command line"
    					"\nOptionally you may list your preferred special characters as the 3d argument on the command line\n"); return ( -1 ); }
    
    
    sscanf (LENGTH_OF_PASSWORD_REQUESTED, "%d", &new_pw_length);
    sscanf (NUMBER_OF_SAMPLES_REQUESTED, "%d", &iterations);
    
     printf("%d passwords requested; each to be  %d characters in length\n\n", iterations, new_pw_length);
     
     /* checking parameters */
     
     if(	new_pw_length < MIN_PSWD_LENGTH | new_pw_length > MAX_PSWD_LENGTH     ) 
        { printf ("Password length must be  %d  to  %d  characters\n", MIN_PSWD_LENGTH, MAX_PSWD_LENGTH); return(1);  }
        
     if( iterations < MIN_PSWD_REQUESTS | iterations > MAX_PSWD_REQUESTS ) 
     		{ printf("Number of passwords request must be at least %d and not more than %d\n", MIN_PSWD_REQUESTS,MAX_PSWD_REQUESTS); return(1); } 
		     
	
	printf ("%s\n\n"
	"%-32s%s\n%-32s%s\n%-32s%s\n%-32s%s\n\n",
	"Password Generator: Selections List: ", 
	"1. (Upper Case) ",string_A, "2. (Lower Case) ",string_a, "3. (Numbers) ",string_0,"4. (Special Characters) ", string_$);
	
	total_string_length = strlen(string_A) * N_CAP + strlen(string_a) * N_LOW + strlen(string_0) * N_NUM + strlen(string_$) * N_SPL;
	
	printf("Total available data: %d max. possible request: %d\n", 
	            strlen(string_A) * N_CAP + strlen(string_a) * N_LOW + strlen(string_0) * N_NUM + MAX_OPTIONAL_SPECIAL_CHARACTERS  * N_SPL, (MAX_PSWD_LENGTH+1)*MAX_PSWD_REQUESTS);
	

    
    if ((new_pw_length+1)*ITERATIONS>total_string_length)
    {printf("New password may not exceed %d characters in length\nReduce pswd length and/or number of samples\n\n", total_string_length/(ITERATIONS)-ITERATIONS); return( -1); }
	
	// allocating space for character strings and sort keys 
	
	source_string = malloc (total_string_length + 1 );
	sort_keys = malloc (total_string_length + 1);
	
	if (NULL == source_string | NULL == sort_keys)
	{ puts("Memory not allocated"); return ( -1 );	}
	else puts("memory allocation complete.");
	
	// loading characters
		
	 strcpy (source_string,string_A); // this gets it started
	 for ( i=1; i < N_CAP; i++) strcat (source_string,string_A); // add N_CAP - 1 copies */
	for ( i=1; i <= N_LOW; i++) strcat (source_string,string_a);
	for ( i=1; i <= N_NUM; i++) strcat (source_string,string_0);
	for ( i=1; i <= N_SPL; i++) strcat (source_string,string_$);
	
	// generating and loading random sort keys;    sorting character strings according to random sort keys
	
	srand(time(0)); /*use current time as seed for random generator */
	
		for (i=0; i<total_string_length; i++)
		{	sort_keys [i] = rand();		}
		
		for (i=0; i<total_string_length -1; i++)
		for (j=i; j<total_string_length; j++)
		{ if (sort_keys[j]<sort_keys[i])
		{	sort_key_save = sort_keys[i]; sort_keys[i]=sort_keys[j]; sort_keys[j]=sort_key_save;
            char_save=source_string[i]; source_string[i]=source_string[j]; source_string[j]=char_save;		}
		}
		
        
        // outputting the generated random passwords
       
        
        k = 0;
        
        for(iteration=1; iteration <= ITERATIONS; iteration++)
        {   i = iteration * (new_pw_length+1) -1; // 12 25 37
            j= (i-new_pw_length);            
            source_string[i]=0x00;
             if (0==k--)
             { printf("\nPasswords: ");    k=PW_PRINT_PER_LINE-1; /* note it prints this one and k more -- per line */  }
            printf("%s  ", &source_string[j]);  
        	}
        
        
        printf("\n\nTake your pick \n\n");
		

return(retc); }
