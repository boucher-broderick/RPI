#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>




int main( int argc, char *argv[] ){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char variables[]={'1','1','1','1','1','1','1'};
    int var_num=0;
    int temp_tracker=0;


    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Read document in
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("# %s", line);
        unsigned int i;
    	int array_size=0;  
    	char **array;

    	// Finds the size of the array
        for (i = 0; i < strlen(line); i++)
    	{ if (line[i] == ' ' || line[i] == ';' || i == strlen(line) - 1) array_size++; }

    	// Creates the array
    	array_size--;
    	array=(char **)malloc(array_size * sizeof(char *));
    	for(int x =0; x < array_size; x++)
    		array[x]= (char*)malloc(5*sizeof(char));
    	
    	// Puts the contents of each line in the array
    	int end;
    	int start = 0;
    	int position=0;
    	for (i = 0; i < strlen(line); i++)
    	{
        	if (line[i] == ' ' || line[i] == ';' || i == strlen(line) - 1)
        	{
          		end = i;
          		strncpy(array[position], &line[start], end-start);
            	start = i + 1;       
            	//printf("%s\n", array[position]);
            	position++;
            	
        	}
        	if(line[i]==';') break;
    	}

    	//printf("%d", array_size);
    	int num_op=0;     // will tell the number of opertations
    	
    	for(int x= 0; x<array_size; x++){
    		//printf("%s", array[0]);
    		if(array[x][0]=='=' ||array[x][0]=='+' ||array[x][0]=='-' ||array[x][0]=='*' ||array[x][0]=='/' ||array[x][0]=='%' ){
    			num_op++;
    			if(array[x][0]=='-' && array[x][1]!='\0'){
    				num_op--;
       			}
    		}
    	}

    	for(int x =0; x< array_size; x++){
    		if(isalpha(array[x][0])){


    			int b = 0;
    			for(int j = 0; j < 7; j++){
    				if(array[x][0]==variables[j]){
    					b=1;
    					break;
    				}
    			}
    			if(b==0){
    				variables[var_num]= array[x][0];
    				var_num++;
    			}
    		}
    	}
    	
    	if(num_op == 1){
    		int reg;
    		for(int j = 0; j < 7; j++){
    			if(array[0][0]==variables[j]){
    				reg=j;
    				break;
    			}
    		}
    		printf("li $s%d,%s\n", reg, array[2]);

    	}
    	//else if(op_type == 0){
    		while(array_size!=3){

    			if(array[3][0] == '+'){
    				int pos1;
    				int pos2;
    				int first=0;
    				int second=0;
    				if(isalpha(array[2][0])){	
    					for(int j = 0; j < 7; j++){
    						if(array[2][0]==variables[j]){ pos1=j; first=1; break; }
    					}   			
    				}
    				if(array[2][0]=='$') { first =2; }

    				if(isalpha(array[4][0])) {
    					for(int j = 0; j < 7; j++){
    						if(array[4][0]==variables[j]){ pos2=j; second=1; break; }
    					}   				
    				}

    				if(second==1){
    					if(array_size==5){
	    					int pos3;
	    					for(int j = 0; j < 7; j++){
	    						if(array[0][0]==variables[j]){ pos3=j;  break; }
	    					} 
	    					printf("add $s%d,", pos3);

    					}
    					else{
    						printf("add $t%d,", temp_tracker);
    						temp_tracker++;
    					}
    					
    				}
    				else{
	    				if(array_size==5){
	    					int pos3;
	    					for(int j = 0; j < 7; j++){
	    						if(array[0][0]==variables[j]){ pos3=j;  break; }
	    					} 
	    					printf("addi $s%d,", pos3);

    					}
    					else if(first==2){
    						printf("addi %s,", array[2]);
    					}
    					else{
    						printf("addi $t%d,", temp_tracker);
    						temp_tracker++;
    						//printf("here");
    					}
    				}
    				if(first == 1){
    					printf("$s%d,",pos1);
    				}
    				else if(first == 2){
    					printf("%s,", array[2]);
    				}
    				else{
    					printf("%s,", array[2]);
    				}
    				if(second == 1){
    					printf("$s%d\n",pos2);
    				}
    				else{
    					printf("%s\n", array[4]);
    				}
    				array[2][0] = '$';
    				array[2][1] = 't';
    				char t[5];
    				sprintf(t, "%d", (temp_tracker-1));
    				array[2][2]=t[0];

    				for(int k = 3; k < array_size-2; k++){
    					array[k]=array[k+2];
    				}
    				
    				//for(int k = 0; k < array_size-2; k++){
    				//	printf("%s\n", array[k]);
    				//}
    				array_size-=2;


    			}
    			else if(array[3][0] == '-'){
    				int pos1;
    				int pos2;
    				int first=0;
    				int second=0;
    				if(isalpha(array[2][0])){	
    					for(int j = 0; j < 7; j++){
    						if(array[2][0]==variables[j]){ pos1=j; first=1; break; }
    					}   			
    				}
    				if(array[2][0]=='$') { first =2; }

    				if(isalpha(array[4][0])) {
    					for(int j = 0; j < 7; j++){
    						if(array[4][0]==variables[j]){ pos2=j; second=1; break; }
    					}   				
    				}

    				if(second==1){
    					if(array_size==5){
	    					int pos3;
	    					for(int j = 0; j < 7; j++){
	    						if(array[0][0]==variables[j]){ pos3=j;  break; }
	    					} 
	    					printf("sub $s%d,", pos3);

    					}
    					else{
    						printf("sub $t%d,", temp_tracker);
    						temp_tracker++;
    					}
    					
    				}
    				else{
	    				if(array_size==5){
	    					int pos3;
	    					for(int j = 0; j < 7; j++){
	    						if(array[0][0]==variables[j]){ pos3=j;  break; }
	    					} 
	    					printf("addi $s%d,", pos3);

    					}
    					else if(first==2){
    						printf("addi %s,", array[2]);
    					}
    					else{
    						printf("addi $t%d,", temp_tracker);
    						temp_tracker++;
    					}
    				}
    				if(first == 1){
    					printf("$s%d,",pos1);
    				}
    				else if(first == 2){
    					printf("%s,", array[2]);
    				}
    				else{
    					printf("%s,", array[2]);
    				}
    				if(second == 1){
    					printf("$s%d\n",pos2);
    				}
    				else{
    					printf("-%s\n", array[4]);
    				}
    				array[2][0] = '$';
    				array[2][1] = 't';
    				char t[5];
    				sprintf(t, "%d", (temp_tracker-1));
    				array[2][2]=t[0];

    				for(int k = 3; k < array_size-2; k++){
    					array[k]=array[k+2];
    				}
    				
    				//for(int k = 0; k < array_size-2; k++){
    				//	printf("%s\n", array[k]);
    				//}
    				array_size-=2;


    			}
    			else if(array[3][0] == '*'){


    				int pos1;
    				int pos2;
    				int first=0;
    				int second=0;
    				if(isalpha(array[2][0])){	
    					for(int j = 0; j < 7; j++){
    						if(array[2][0]==variables[j]){ pos1=j; first=1; break; }
    					}   			
    				}
    				if(array[2][0]=='$') { first =2; }

    				if(isalpha(array[4][0])) {
    					for(int j = 0; j < 7; j++){
    						if(array[4][0]==variables[j]){ pos2=j; second=1; break; }
    					}   				
    				}
    				if(array[4][0]=='$') { second =2; }

    				if(second==1 || second == 2){
    					if(first == 1){
    						printf("mult $s%d,", pos1);
    					}
    					else{
    						printf("mult %s,", array[2]);
    					}
    					if(second == 1){
    						printf("$s%d\n", pos2);
    					}
    					else{
    						printf("%s\n", array[4]);
    					}
    					if(array_size==5){
    						int pos3;
    						for(int j = 0; j < 7; j++){
    							if(array[0][0]==variables[j]){ pos3=j;  break; }
    						}  
							printf("mflo $s%d\n", pos3);
    					}
    					else{
    						printf("mflo $t%d\n", temp_tracker);
    					}
    					

    				}
    				else{         //for when there is a constant
	    					if(array[4][0]=='0'){
	    						int pos3;
    							for(int j = 0; j < 7; j++){
    								if(array[0][0]==variables[j]){ pos3=j;  break; }
    							}
    							printf("li $s%d,0\n",pos3);
	    					}
	    					if((array[4][0]=='1' && array[4][1]=='\0') || (array[4][0]=='-' && array[4][1]=='1' && array[4][2]=='\0') ){
	    						
	    						
	    							printf("move $t%d,", temp_tracker);
	    							if(first==1){
										printf("$s%d\n", pos1);
									}
									else{
										printf("%s\n", array[2]);
									}
	    						if(array_size==5){
	    							int pos3;
    								for(int j = 0; j < 7; j++){
    									if(array[0][0]==variables[j]){ pos3=j;  break; }
    								}
    								if(array[4][0]=='-') {
    									printf("sub $s%d,", pos3);
										printf("$zero,$t%d\n",temp_tracker);
    								}	 
    								else{
    									printf("move $s%d,", pos3);
										printf("$t%d\n",temp_tracker);
    								}
									
	    						}
	    					}


    				}
    				array[2][0] = '$';
    				array[2][1] = 't';
    				char t[5];
    				sprintf(t, "%d", (temp_tracker));
    				array[2][2]=t[0];
    				temp_tracker++;
    				for(int k = 3; k < array_size-2; k++){
    					array[k]=array[k+2];
    				}
    				
    				//for(int k = 0; k < array_size-2; k++){
    				//	printf("%s\n", array[k]);
    				//}
    				array_size-=2;


    			}
    			else if(array[3][0] == '/'){


    				int pos1;
    				int pos2;
    				int first=0;
    				int second=0;
    				if(isalpha(array[2][0])){	
    					for(int j = 0; j < 7; j++){
    						if(array[2][0]==variables[j]){ pos1=j; first=1; break; }
    					}   			
    				}
    				if(array[2][0]=='$') { first =2; }

    				if(isalpha(array[4][0])) {
    					for(int j = 0; j < 7; j++){
    						if(array[4][0]==variables[j]){ pos2=j; second=1; break; }
    					}   				
    				}
    				if(array[4][0]=='$') { second =2; }

    				if(second==1 || second == 2){
    					if(first == 1){
    						printf("div $s%d,", pos1);
    					}
    					else{
    						printf("div %s,", array[2]);
    					}
    					if(second == 1){
    						printf("$s%d\n", pos2);
    					}
    					else{
    						printf("%s\n", array[4]);
    					}
    					if(array_size==5){
    						int pos3;
    						for(int j = 0; j < 7; j++){
    							if(array[0][0]==variables[j]){ pos3=j;  break; }
    						}  
							printf("mflo $s%d\n", pos3);
    					}
    					else{
    						printf("mflo $t%d\n", temp_tracker);
    					}
    					

    				}
    				else{         //for when there is a constant
	    					int x;
	    					x=atoi(array[4]);
	    					if(x%2!=0){
	    						printf("li $t%d,%d\n",temp_tracker,x);
	    						printf("div $s%d,$t%d\n",pos1,temp_tracker);
	    						printf("mflo $t%d\n",temp_tracker+1);
	    						

	    					}
    				}
    				array[2][0] = '$';
    				array[2][1] = 't';
    				char t[5];
    				sprintf(t, "%d", (temp_tracker));
    				array[2][2]=t[0];
    				temp_tracker++;
    				for(int k = 3; k < array_size-2; k++){
    					array[k]=array[k+2];
    				}
    				
    				//for(int k = 0; k < array_size-2; k++){
    				//	printf("%s\n", array[k]);
    				//}
    				array_size-=2;


    			}
    			else if(array[3][0] == '%'){


    				int pos1;
    				int pos2;
    				int first=0;
    				int second=0;
    				if(isalpha(array[2][0])){	
    					for(int j = 0; j < 7; j++){
    						if(array[2][0]==variables[j]){ pos1=j; first=1; break; }
    					}   			
    				}
    				if(array[2][0]=='$') { first =2; }

    				if(isalpha(array[4][0])) {
    					for(int j = 0; j < 7; j++){
    						if(array[4][0]==variables[j]){ pos2=j; second=1; break; }
    					}   				
    				}
    				if(array[4][0]=='$') { second =2; }

    				if(second==1 || second == 2){
    					if(first == 1){
    						printf("div $s%d,", pos1);
    					}
    					else{
    						printf("div %s,", array[2]);
    					}
    					if(second == 1){
    						printf("$s%d\n", pos2);
    					}
    					else{
    						printf("%s\n", array[4]);
    					}
    					if(array_size==5){
    						int pos3;
    						for(int j = 0; j < 7; j++){
    							if(array[0][0]==variables[j]){ pos3=j;  break; }
    						}  
							printf("mfhi $s%d\n", pos3);
    					}
    					else{
    						printf("mfhi $t%d\n", temp_tracker);
    					}
    					

    				}
    				else{         //for when there is a constant
	    				
    				}
    				array[2][0] = '$';
    				array[2][1] = 't';
    				char t[5];
    				sprintf(t, "%d", (temp_tracker));
    				array[2][2]=t[0];
    				temp_tracker++;
    				for(int k = 3; k < array_size-2; k++){
    					array[k]=array[k+2];
    				}
    				
    				//for(int k = 0; k < array_size-2; k++){
    				//	printf("%s\n", array[k]);
    				//}
    				array_size-=2;


    			}

    		}


    	//}









    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

}