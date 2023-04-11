
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



char** make_array(char* string){  // takes one line and separates it into an array
	//printf("%s", string);
	char **array;
	int array_row_length=0;

	// finds the size of the array
	for(int i =0;  i < strlen(string); i++){                          
		if(string[i]==' ' || string[i] == ',' || string[i]=='\n' || string[i]=='('){
			array_row_length++;
		}
	}

	// allocates memory for size of array
	array=(char **)malloc(array_row_length * sizeof(char *));
    for(int x =0; x < array_row_length; x++)
    array[x]= (char*)malloc(9*sizeof(char));
	
	// puts the elements of the line into the array
    int end;
	int start = 0;
	int position=0;
	for (int i = 0; i < strlen(string); i++)
	{
    	if (string[i] == ' ' || string[i] == ',' || string[i]== '\n' /*|| string[i]=='(' || string[i]==')'*/)
    	{
    		if(string[i]=='\n'){
    			end=i-2;
    		}
    		else{
    			end=i;
    		}
      		
      		strncpy(array[position], &string[start], end-start);
        	start = i + 1;       
        	position++;
    	}
	}
	return array;
}

int file_line_couner(char* file){ // Opens the file and finds the number of lines
	char * line = NULL;
    size_t len = 0;
    FILE * fp;
    ssize_t read;
	fp = fopen(file, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int counter=0;
    while ((read = getline(&line, &len, fp)) != -1) {
    	counter++;
    }
    fclose(fp);
    if (line)
    free(line);
	//printf("%d",counter);
	return counter;
}

int main( int argc, char *argv[] ){

	int array_size = file_line_couner(argv[1]);
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char **arr1 = (char**) malloc(array_size * sizeof(char*));
    char*** array;
    array =(char ***)malloc(array_size * sizeof(char **));
    int i = 0;
  	char * tru= NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
    	arr1[i] = (char*) malloc(20 *sizeof(char));
	    arr1[i]=line; 
	    //printf("%s", arr1[i]);
    	array[i] = make_array(line); i++;	
    }

   



    int* position;
    position= (int *)malloc(array_size *sizeof(int));
    for (int i = 0; i < array_size; ++i)
    {
    	position[i]=0;
    }
    char **arr = (char**) calloc(9,sizeof(char*));
	for (int i = 0; i < 9; i++ )
	{
	    arr[i] = (char*) calloc(10, sizeof(char));
	    for(int x = 0; x < array_size;x++){
	    	arr[i][x]='0';
	    }
	}

	
    printf("START OF SIMULATION\n");
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

      if(position[2]==9){
    	break;
    }
    printf("\n");
    printf("CPU Cycles ===>");
    printf("\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
    for (int i = 0; i < array_size; i++ )
	{
			//printf("%s", arr1[0]);
			printf("%s %s,",array[i][0],array[i][1]);
			if(isdigit(array[i][2][0])){
				printf("(%s)%s", array[i][2],array[i][3]);
			}
			else{
				printf("%s,%s\t",array[i][2],array[i][3]);
			}
		
		for (int j = 0; j < 9; j++){
			if(arr[j][i]=='0' || arr[j][i]=='9'){
				printf(".\t");
			}
			else if(arr[j][i]=='1')
				printf("IF\t");
			else if(arr[j][i]=='2')
				printf("ID\t");
			else if(arr[j][i]=='3')
				printf("EX\t");
			else if(arr[j][i]=='4')
				printf("MEM\t");
			else if(arr[j][i]=='5')
				printf("WB\t");
		}
		printf("\n");

    }
    

  


	}
	printf("\nEND OF SIMULATION");

    
  
    return 0;
}
