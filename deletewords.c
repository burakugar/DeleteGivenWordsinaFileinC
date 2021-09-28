/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 2 
#define MAX 200 /* MAX SIZE OF THE ANY LINE */





int countDigit(char* str,int count){ /*recursive function which calculates and returns the number of characters in the given string */
	if(*str == '\0'){
		return count; 
	}
	else{
		count++;
		countDigit(str+1,count);
	}
}
int countchar (char* str) { /* function that counts the characters of the given string as strlen  recursively*/
    if (*str == 0) {
        return 0;
    }

    return countchar (str+1) +1;
}
int compareStrings1(const char *s1, const char *s2) {
    if (*s1 < *s2) /* if the first string is longer than second return -1 else +1 */ 
        return -1;
    if (*s1 > *s2)
        return +1;
    /* if two strings are matching together then put null character end of the first string */
    if (*s1 == '\0')
        return 0; /* if 2 strings are matching return 0 */
    return compareStrings1(s1 + 1, s2 + 1);
}

int controlSubstring(char *buffer, char *sub) /* FUNCTION THAT CONTROLS SUBSTRING IS IN THE BUFFER OR NOT BY INCREMENTING THE STRING 1 AT EVERY ITERATION*/
{
    if (*buffer == '\0' && *sub != '\0') 
        return 0;

    if (*sub == '\0')
        return 1;
  
    if (*buffer == *sub) 
        return controlSubstring(buffer + 1, sub + 1);
  
    return 0;
}


int isSubstring(char *text, char *sub)
{
    /* if the last chareacter reaches the null then return 0 */
    if (*text == '\0')	/* this function controls if a given string includes any substring such as BURAK and RAK are given to that it returns 1 since the RAK */
        return 0;
  	/* if two strings are identical control the first character*/
    if (*text == *sub)
        if(controlSubstring(text, sub))
            return 1; /* if the substring is in the buffer than this function returns 1 */
        else
          return isSubstring(text + 1, sub);
  
    // If current characters of pat and tex don't match
    return isSubstring(text + 1, sub); /* increment the string at every iteration by 1 and keep continue to find any substring */
    /* substring will not change in the next iteration since we control it */
}

char *copytheString(char *s, char *t) { /* recursive strcpy function to implementation of copy and paste two string */
 if ((*s = *t) != '\0') 
 copytheString(s+1, t+1); 
 return s; 
 }
 
 char* findFirstindex(char * string, char *substring) /* this function finds the first instance of the given char as an index as strstr recursively*/
{
   if (string == NULL  ) /* check if the given string is null */
      return NULL;

   if ( *string == '\0' ) /* check we are at the end of the string */
      return NULL;

   if (strncmp(string, substring, countchar(substring)) == 0)
      return string;

   return(findFirstindex(string+1, substring));
}
void removestr(char *str1, char *str2, int len) /* this function removes the second string in the given string */
{
    char *c=findFirstindex(str1,str2); 
    if(c!=0) {
      copytheString(c,c+len); 
      removestr(str2,str1,len); 
    }
    else
      return;  /* no substring has been found */
}

int findinDelete(char buffer[MAX],char* words_to_delete[WORDSIZE],int n){ /* this function is controlling the buffer that we read from file
whether does it include the deleted file or not */
		int len= countDigit(*words_to_delete,0);
		if(isSubstring(buffer,*words_to_delete)){
			removestr(buffer,*words_to_delete,len);
			return n;
		}
		if(n==WORDSIZE){
			return 0;
		}
		
		findinDelete(buffer,words_to_delete+1,n+1);
}
/* NUMBER OF WORDS VARIABLE IS THE NUMBER OF WORDS WILL BE DELETED IN THE FILE */
void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words){
	char buffer[MAX];
	fgets(buffer,MAX,infid); /* getting the whole line from the given file */
	findinDelete(buffer,words_to_delete,0);
	fprintf(outfid,"%s",buffer); /* PRINT THE DELETED BUFFER TO THE OUTPUT FILE */
	if(feof(infid)){ /* until the EOF get the line and write */
		return;
	}
	delete_words(infid,outfid,words_to_delete,number_of_words);
}


void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE* infid;
	infid=fopen(infile,"r"); /* the file pointer for the input text */
	FILE* outfid;
	outfid=fopen(outfile,"w+"); /* the file pointer for the output text */
	delete_words(infid, outfid, words_to_delete, 2);
	
}