#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 64



int main(int argc, char *argv[]){

	char  inputfilename[BUFSIZE+1];
	char  outputfilename[BUFSIZE+1];
	int time;
	int iflag = 0;
	int oflag = 0;
	int c;
	char ch;
	FILE *fp;
	char newString[10][10];
	int i,j,ctr;
	char line[256];	
	int numberOfProcess;
	pid_t childpid = 0;
	while((c = getopt(argc, argv, "hi:o:t:")) != -1){
		
		switch(c){
			case 'h':
				printf("The program can take 4 command-line arguments such as;\n"); 
				printf("-h which displays the legal command-line options \n");
				printf("-i which takes another argument, inputfilename \"-i inputfilename\" as an example\n");
				printf("-o which takes another argument, outputfilename \"-o outputfilename\" as an example\n");
				printf("-t which takes another argument, time in seconds \"-t 15\" as an example\n");
				break;
			case 'i':
				//inputfilename = optarg;
				snprintf( inputfilename, BUFSIZE, "%s", optarg );
				printf("-i option: %s \n", inputfilename);
				iflag = 1;
				break;
			case 'o':
				//outputfilename = optarg;
				snprintf(outputfilename, BUFSIZE, "%s", optarg );
				printf("-o option: %s \n", outputfilename);
				oflag = 1;
				break;
			case 't':
				time = atoi(optarg);		
				printf("-t option: %d \n", time);
				break;
			default: 
				printf("Not a valid command-line argument");
				break;

		}	

	}

	if(iflag){
		fp = fopen(inputfilename,"r");	
		printf("in the inputfilename\n");
		if (fp == NULL){
      			perror("Error while opening the file.\n");
      			exit(EXIT_FAILURE);
   		}
	}
	else{
		fp = fopen("input.dat", "r");
		printf("in the input.dat\n");
		if (fp == NULL){
      			perror("Error while opening the file.\n");
      			exit(EXIT_FAILURE);
   		}
	}	

	
          
 	j = 0;
	ctr = 0;	
	while (!feof(fp)){
		fgets(line, 256, fp);
		for(i=0;i<=(strlen(line));i++){
			if(line[i]==' '|| line[i]=='\0'){
            			newString[ctr][j]='\0';
            			ctr++;  //for next word
            			j=0;    //for next word, init index to 0
        		}
        		else{
            			newString[ctr][j]=line[i];
           	 		j++;
        		}

		}
		//printf("the data line by line is: %s\n", line);
	
	}
	
	//convert first character of the input file to integer to be able to determine the number of processes needed	
	numberOfProcess = newString[0][0] - '0';
		
	
	printf("\n Strings or words after split by space are :\n");
    	for(i=0;i < ctr;i++)
        printf(" %s\n",newString[i]);

	printf("number of process: %d\n\n", numberOfProcess);
	printf("number of ctr: %d\n", ctr);
	//fork();
	//printf("hey\n");
	for(i = 0; i < numberOfProcess; i++){
		if ((childpid = fork()) <= 0){
         		break;	
		}
			
	}
	fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
           i, (long)getpid(), (long)getppid(), (long)childpid);

	fclose(fp);
	return 0;
}



