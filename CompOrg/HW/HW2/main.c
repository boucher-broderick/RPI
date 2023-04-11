
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <ctype.h>

int main()
{
	char col1[10];
	printf("Enter the column 1 header: \n");
	scanf("%s", col1);
	printf("You Entered: %s\n", col1);

	char col2[10];
	printf("Enter the column 2 header: \n");
	scanf("%s", col2);
	printf("You Entered: %s\n", col2);

	char **array;
	array = (char **)malloc(10 * sizeof(char *)); 
	for( int i = 0; i < 10; i++ ) 
	array[i] = (char *)malloc(24 * sizeof(char));

	int *array_num;
	array_num = (int *)malloc(10* sizeof(int *)); 

	int arraysize = 10;
	int tracker =0;



	while(1){
		char string[56];
		char string1[24];
		char string2[23];
		printf("Enter Data: \n");
		scanf("%s", string);
		int count=0;
		if(string[0]=='-' && string[1]=='1'){
			break;
		}
		
		for(int i=0; i <56; i++){
		if(string[i]==',')
			count++;
		}
		if(count==0)
			printf("error too little\n");
		else if(count>1)
			printf("error too many\n");
		else{
			char * token = strtok(string, ",");
			//printf("%s\n", token);
			strcpy(string1, token);
			token = strtok(NULL, ",");
			//printf("%s\n", token);
			strcpy(string2, token);
			for (int i = 0; string2[i]!= '\0'; i++)
   			{
        	if (isdigit(string2[i]) == 0){
					printf("error");
					break;
				}
			}
			int number =atoi(string2);
			//printf("%d", number);

			if(tracker==arraysize-1){

			}

			array[tracker] = string1;
			array_num[tracker] = number;

			printf("%s    %d", array[0], array_num[0] );

		}

	}
	

}