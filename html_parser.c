#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, const char *argv[]) {
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];
    FILE *fp;
    fp = fopen(inputFileName, "r");

    char* line = NULL;
    size_t len = 0;
    size_t read;
    char* buffer;

    fp = fopen(inputFileName, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    FILE *fptrOut = fopen(outputFileName, "w");

//char *open_tags[10]= {"<title>", "<body>", "<html>", "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>"};

    char *br = "<br>";

//char *close_tags[10]= {"</title>", "</body>", "</html>", "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>"};
    while ((read = getline(&line, &len, fp)) != -1) {

        int Flag = 0; //index of first closing tag

        //FOR FINDING THE INDEX OF THE FIRST CLOSING TAG
            for(int i = 0; i < read; i++){
  		        if(line[i] == '>'){
  			        Flag = i;
			        break;    	
 		    } 
	    }//for getting index of first '>'
       
            int i;
            int indexOfFirstDQuote = 0;
    	    for(i=0; i<Flag+1; i++){
                if(!isalpha(line[0])) {
                    if(strcmp(&line[i], "\"") == 0) {
                        indexOfFirstDQuote = i;
                        break;
                    }
                    line[i] = ' ';
                }//if(!isalpha(line[0])) 
            } //removes the header (fir) tag

            char* quote = "\"";
            char* brQuote = strstr(line, quote);
            if(brQuote != NULL) {
                    int idx = 0;
                    int opened = 0; // false
                    for(int i=indexOfFirstDQuote; i<Flag-1; i++){
                        if(line[i]=='"') {
                            opened = 1; // true
                        } else if (line[i] == '"') {
                        opened = 0; // false
                        } else if (!opened) {
                    line[idx++] = line[i];
                        }
                    }//for    
                    line[idx] = '\0';
                }//if brType != NULL
            
       
       /*    int i;
    	    for(i=0; i<Flag+1; i++){
                if(!isalpha(line[0])) {
                    printf("%c", line[i]);
                    line[i] = ' ';
                }
            } //removes the header (fir) tag
            */

        int countOpenTags = 0;
        int countExtraOpenTags = 0;
        for (int j = Flag+1; j < read; j++){
            if (line[j] == '<'){
                countOpenTags++;
            }
        } //count number of OPEN TAGS after removing first tag

        int secondOpenIndex = 0;
        //int* openIndexsExtra = NULL;
        if(countOpenTags == 1) { //if countOpenTags==1
            for(int i=Flag; i<read; i++){
                if(line[i] == '<') {
                    secondOpenIndex = i;
                    break;
                }
            }//FOR FINDING THE INDEX OF THE SECOND OPEN TAG

            for (int j = secondOpenIndex; j < read; j++){
               line[j] = ' '; 
            } //REPLACING THE ENDING TAG WITH BLANK SPACES (ONE ENDING TAG)

        } else if (countOpenTags > 1) { //if there are tags in middle
            int indexOfLastOpen = 0;
            for (int j = Flag+1; j < read; j++){
                if (line[j] == '<'){
                    countExtraOpenTags++; //gets the number of open tags including the ending tag
                    indexOfLastOpen = j;
                }//number of tags if there are more than one open tags in remaining line 
            }//for (finds the last index of '<')
            for(int k = indexOfLastOpen; k < read; k++) {
                line[k] = ' ';
            }//removes the ending tag with line having more than 2 tags in total originally

            //STRING WITHOUT BEGINNING AND ENDING TAGS 
            countExtraOpenTags-=1; //deleting the count of the ending tag
            if(countExtraOpenTags > 1) { //more than one opening tags after removing header
            //and header tags
                int j = Flag+1;
            //for(int i)
                char *copyofLine = line;
                int idx = 0;
                while (*copyofLine++ != '<') idx++; //idx: index of one first opening tag
                buffer = malloc(sizeof(char) * (idx - j));
                for (j = Flag+1; j < idx; j++){
                    if(line[j] != '<') {
                        buffer[j-(Flag+1)] = line[j]; //malloc inside for buffer initially 
                    } 
                }//for
                buffer[j+1] = '\0'; //end buffer with 

                //char* copyBuff = buffer;
                //middle tag

                char* brType = strstr(line, br);
                if(brType != NULL) {
                    int idx = 0;
                    int opened = 0; // false
                    for(int i=0; i<read; i++){
                        if(line[i]=='<') {
                            opened = 1; // true
                        } else if (line[i] == '>') {
                        opened = 0; // false
                        } else if (!opened) {
                    line[idx++] = line[i];
                        }
                    }//for    
                    line[idx] = '\0';
                }//if brType != NULL

                char *bStart = strstr(line, "<b>");
                if(bStart != NULL) {
                    int idx = 0;
                    int opened = 0; // false
                    for(int i=0; i<read; i++){
                        if(line[i]=='<') {
                            opened = 1; // true
                        } else if (line[i] == '>') {
                        opened = 0; // false
                        } else if (!opened) {
                    line[idx++] = line[i];
                        }
                    }//for    
                    line[idx] = '\0';
                }//if brType != NULL
            

               /* line = copyofLine;
                char *firstMiddleTag = NULL;
                int indexofFirstExtraClosingTag = 0;
                while (*line++ != '>') indexofFirstExtraClosingTag++; //idx: index of one extra closing tag
                firstMiddleTag = malloc(sizeof(char) * (indexofFirstExtraClosingTag - idx));

                for(int i=idx; i <= indexofFirstExtraClosingTag; i++) {
                    firstMiddleTag[i-(idx)] = line[j];
                    line[j] = ' ';
                }
                */
                
            } else if(countExtraOpenTags == 1) { //only one extra tag
                int indexofOneOpenTag = 0;
                for(int i=Flag; i<read; i++) {
                    if(line[i] == '<') {
                        indexofOneOpenTag = i;
                        break;
                    }
                }//for finding index of remaining open tag

                int idx2 = 0;
                char* copyOfLineOneExTag = line;
                while (*copyOfLineOneExTag++ != '>') idx2++; //idx: index of one extra closing tag
                char* bufferOne = malloc(sizeof(char) * (idx2 - indexofOneOpenTag));
                int j = indexofOneOpenTag;
                for (j = indexofOneOpenTag; j <= idx2; j++)
                {
                    //if(line[j] != '>') {
                        bufferOne[j-(indexofOneOpenTag)] = line[j]; //malloc inside for buffer initially 
                    //} 
                }//for
                 bufferOne[j+1] = '\0';
              //  printf(" \n SIZE OF BUFFER: %lu \n", sizeof(buffer));
                char* newBuff = bufferOne;
                if(strcmp(newBuff, br) == 0) {
                    for (int j = indexofOneOpenTag; j <= idx2; j++) {
                        line[j] = ' ';
                    }//for
                } else {
                     for (int k = indexofOneOpenTag; k <= idx2; k++) {
                        line[k] = ' ';
                    }//for
                }

             /*   int trueorFalse = 0; //true is 1 and false is 0
                for (int i = 0; i < sizeof(open_tags); i++)
                {
                    if(newBuff == )
                }
                */
                

            }
        }//else if (countTags > 1)
        //printf("countOpenTags after removing heading tag: %d \n", countOpenTags);
        //printf("countExtraOpenTags after removing heading and ending tag: %d \n", countExtraOpenTags);
         //free buffer right after using it
        fprintf(fptrOut, " %s \n", line);
        
    }//while

    fclose(fp);
    fclose(fptrOut);

}//main