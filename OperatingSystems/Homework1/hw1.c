#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


int main(int argc, char **argv)
{

    // check to see the correct number of arguments
    if (argc < 3){
        fprintf(stderr, "ERROR: Invalid arguments\n");
        return EXIT_FAILURE;
    }

    setvbuf( stdout, NULL, _IONBF, 0 );

    // check that the first argument is a number
    int size = atoi(*(argv+1));
    if(size < 1 ){
         fprintf(stderr, "ERROR: Invalid cache argument\n");
        return EXIT_FAILURE;
    }

    unsigned int** hash = calloc(size, sizeof(void*));
    unsigned int* hashSize = calloc(size, sizeof(unsigned int));

    // loop through if there are multiple files
    FILE* file;
    int ch;
    for(int x = 2; x < argc; x++){
        file = fopen(*(argv+x), "r");
        if(file == NULL){
            perror( "open() failed" );
            return EXIT_FAILURE;
        }

        // loop through characters in file
        unsigned int num;
        do{
            ch = fgetc(file);
            if(isdigit(ch))
            {
                fseek(file,-1,SEEK_CUR);
                fscanf(file,"%u",&num);
                int hashIndex = num % size;

                // check duplicates if the index is not empty
                if(*(hash+hashIndex) != NULL){
                    int duplicate = 0;
                    for(int i = 0; i< *(hashSize+hashIndex); i++)
                    {
                        if((*(*(hash+hashIndex)+i)) == num){
                            duplicate = 1;
                            break;
                        }
                    }
                    // skip the number or reallocate to make more space
                    if(duplicate == 1){
                        printf("Read %u => cache index %d (skipped)\n", num, hashIndex);
                    }
                    else{
                         *(hash+hashIndex) = realloc(*(hash+hashIndex), sizeof(unsigned int)*(*(hashSize+hashIndex)+1));
                        *(*(hash+hashIndex)+(*(hashSize+hashIndex)))= num;
                        *(hashSize+hashIndex) += 1;
                        printf("Read %u => cache index %d (realloc)\n", num, hashIndex);
                    }
                }
                // allocate memory if the index is empty
                else{
                    *(hash+hashIndex) = calloc(1 , sizeof(unsigned int));
                    (*(*(hash+hashIndex)+0)) = num;
                    *(hashSize+hashIndex) = 1;
                    printf("Read %u => cache index %d (calloc)\n", num, hashIndex);
                }
            }
        }
        while(ch != EOF);
        fclose(file);
    }
   


    printf("========================================\n");
    for(int i =0; i < size; i++){
        if(*(hashSize+i)==0){

        }
        else{
            printf("Cache index %d => %c",i, 0x5b);
            for(int j=0; j<*(hashSize+i); j++){
                printf(" %u", *(*(hash+i)+j));
                if((j+1)==*(hashSize+i)){
                    printf(" ");
                }
                else{
                    printf(",");
                }
            }
             printf("%c\n", 0x5d);
             // free memory inside hash
             if (*(hashSize + i) > 0) {
                free(*(hash + i));
              }

        }
       
    }


    free(hash);
    free(hashSize);


    return EXIT_SUCCESS;
      
}