
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int file_line_couner(char* file){ // Opens the file and finds the number of lines
	char * line = NULL;
    size_t len = 0;
    FILE * fp;
    ssize_t read;
	fp = fopen(file, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int counter=0;
    while ((read = getline(&line, &len, fp)) != -1) { //opens up and counts
    	counter++;
    }
    fclose(fp);
    if (line)
    free(line);
	return counter;
}

int main( int argc, char *argv[] ){

	int array_size = file_line_couner(argv[1]);  //allocates necessary mem
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char first[20];
    char second[20];
    char third[20];   
    int i=0;	
    while ((read = getline(&line, &len, fp)) != -1) {  //goes through and reads each line and sets to level


    	if(i==0){
    		strcpy(first, line);
    		for (int j = 0; j < sizeof(first); j++) { //get rid of newline char
	            if(first[j] == '\n') {
	                first[j] = '\0';
	            }
        	}
    	}
    	if(i==1){
			strcpy(second, line);
			for (int j = 0; j < sizeof(second); j++) { //get rid of newline char
	            if(second[j] == '\n') {
	                second[j] = '\0';
	            }
        	}
    	}
    	if(i==2){
			strcpy(third, line);
			for (int j = 0; j < sizeof(third); j++) { //get rid of newline char
	            if(third[j] == '\n') {
	                third[j] = '\0';
	            }
        	}
    	}
    	i++;
    }


    int* position;
    position= (int *)malloc(array_size *sizeof(int));  //creates an array for the position within the process
    for (int i = 0; i < array_size; ++i)
    {
    	position[i]=0;
    }
    char **arr = (char**) calloc(9,sizeof(char*));  //array to help print out
	for (int i = 0; i < 9; i++ )
	{
	    arr[i] = (char*) calloc(10, sizeof(char));
	    for(int x = 0; x < array_size;x++){
	    	arr[i][x]='0';
	    }
	}

	
    printf("START OF SIMULATION\n");  //sets the position through each run
    for(int i =0; i < 9; i++){
    	for(int k =0;k<array_size;k++){
    		if(position[k]==0){
    			position[k]+=1;
    			break;
    		}
    		else{
    			if(position[k]==5){
    				position[k]=9;
    			}
    			else{
    				if(position[k]!=9)
    					position[k]+=1;
    			}
    		}
    	}
    	for(int k =0;k<array_size;k++){
    	//printf("%d ",position[k]);
    	arr[i][k]=position[k]+'0';
    }

    
      if(position[2]==9){  //to end early
      	
    	break;
    }
    printf("\n");						// print header
    printf("CPU Cycles ===>");
    printf("\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
    for (int i = 0; i < array_size; i++ )
	{
		if(i==0){
    		printf("%s\t", first);
    	}
    	if(i==1){
			printf("%s\t", second);
    	}
    	if(i==2){
			printf("%s\t", third);
    	}
		
		for (int j = 0; j < 9; j++){    //check and print stage
			if(arr[j][i]=='0' || arr[j][i]=='9'){
				printf(".");
			}
			else if(arr[j][i]=='1')
				printf("IF");
			else if(arr[j][i]=='2')
				printf("ID");
			else if(arr[j][i]=='3')
				printf("EX");
			else if(arr[j][i]=='4')
				printf("MEM");
			else if(arr[j][i]=='5')
				printf("WB");
			if(j<8){
				printf("\t");
			}

			
		}

			printf("\n");
    }
    

  


	}
	printf("\nEND OF SIMULATION");

    printf("\n");      //free
		free(position);
		for(int i= 0; i<9; i++){
			free(arr[i]);
		}
		free(arr);
  
    return 0;
}
