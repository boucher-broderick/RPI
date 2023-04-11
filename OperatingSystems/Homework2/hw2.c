#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <wait.h>

int* fd;
pid_t parent_pid;

typedef struct {
  int x_row, y_col;
} coordinates;

typedef struct {
  int row, column, num_steps;
  coordinates current;
  coordinates start;
  char** grid;
} board;

typedef struct {
  int o, c, m;
} statistics;

void freeboard(board *b){
	int i =0;
	while(i< (*b).row){
		free((*b).grid[i]);
		(*b).grid[i]=NULL;
		i++;
	}
	free((*b).grid);
	(*b).grid=NULL;

}

board populate_board( int m, int n, int r, int c){
  board b;
  b.grid = calloc(m, sizeof(char*));
    for(int i = 0; i < m; i++){
    *(b.grid+i) = calloc((n+1), sizeof(char));
    for(int j = 0; j < n+1; j++){
    	if(j==n){
      		*(*(b.grid+i)+j) = '\0';
    	}
    	else{
    		      *(*(b.grid+i)+j) = '0';
    	}

    }
  }
  *(*(b.grid+r)+c)='1';
  (b.start).x_row = r;
  (b.start).y_col = c;
  (b.current).x_row = r;
  (b.current).y_col = c;
  b.row=m;
  b.column=n;
  b.num_steps = 1;
return b;
}

void print_board(board b, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      printf("%c ",*(*(b.grid+i)+j));
    }
      printf("\n");
  }
}

coordinates* possible_moves(board *b){
  coordinates* possible = calloc(9, sizeof(coordinates));
  for(int i=0; i < 9; i ++){
    (*(possible+i)).x_row = -1;
    (*(possible+i)).y_col = -1;
  }

  int current_x = ((*b).current).x_row;
  int current_y = ((*b).current).y_col;
  int* cord_x = calloc(8, sizeof(int));
  *(cord_x+0) = -2;
  *(cord_x+1) = -1;
  *(cord_x+2) =  1;
  *(cord_x+3) =  2;
  *(cord_x+4) =  2;
  *(cord_x+5) =  1;
  *(cord_x+6) = -1;
  *(cord_x+7) = -2;

  int* cord_y = calloc(8, sizeof(int));
  *(cord_y+0) =  1;
  *(cord_y+1) =  2;
  *(cord_y+2) =  2;
  *(cord_y+3) =  1;
  *(cord_y+4) = -1;
  *(cord_y+5) = -2;
  *(cord_y+6) = -2;
  *(cord_y+7) = -1;

  int count = 0;
  for(int i=0; i < 8; i ++){
    int temp_x1 = current_x + *(cord_x+i);
    int temp_y1 = current_y + *(cord_y+i);
    if( temp_x1 >=0 && temp_x1 < (*b).row && temp_y1 >=0 && temp_y1 < (*b).column){
      if( *(*((*b).grid+temp_x1)+temp_y1) == '0' ){
        (*(possible+count)).x_row = temp_x1;
        (*(possible+count)).y_col = temp_y1;
        count +=1;
      }
    }
  }
  (*(possible+8)).x_row = count;
  (*(possible+8)).y_col = count;

  free(cord_x);
  free(cord_y);
  
  return possible;
} 


//void knights_tour(board b, statistics stats, int depth){
void knights_tour(board *b, int depth){
  coordinates* possible_steps = possible_moves(b);
  int num_moves = (*(possible_steps+8)).x_row;

  //End of recursion reached must write in here
  if(num_moves == 0){
  	free(possible_steps);
  //If the tour is completed
    statistics temp_return;
    temp_return.o = 0;
    temp_return.c = 0;
    temp_return.m = 0;
    if((*b).num_steps == ((*b).row * (*b).column)){
      *(*((*b).grid + ((*b).start).x_row) + ((*b).start).x_row) ='0';
      coordinates* check = possible_moves(b);
      if((*(check+8)).x_row == 1){
        #ifndef QUIET
          printf("PID %d: Sonny found an closed knight's tour; notifying top-level parent\n",getpid());
        #endif
        temp_return.c = 1;
      }
      else{
        #ifndef QUIET
          printf("PID %d: Sonny found an open knight's tour; notifying top-level parent\n",getpid());
        #endif
        
        temp_return.o = 1;
      }
      free(check);
    }
    //If the tour is not completed
    else{
      #ifndef QUIET
        printf("PID %d: Dead end at move #%d\n", getpid(), depth);
      	if(depth == 1){
        	printf("PID %d: Search complete; best solution(s) visited %d squares out of %d\n",getpid(), 1, ((*b).row*(*b).column));
      	}
      #endif
      temp_return.m = depth;
    }
    
		
    int rc =write(*(fd+1), &temp_return, sizeof(statistics));
      if(rc <0){
    perror("Error: <write failed>\n");
  }
    //printf("write: %d\n", rc);
    
    freeboard(b);
    free(fd);
    exit(EXIT_SUCCESS);

 
  }
  else if(num_moves == 1){

    int tempx = (*(possible_steps)).x_row;
    int tempy = (*(possible_steps)).y_col;
    *(*((*b).grid+ tempx)+ tempy)='1';
    ((*b).current).x_row = tempx;
    ((*b).current).y_col = tempy;
    (*b).num_steps += 1;
    free(possible_steps);
    knights_tour(b, depth+1);

    exit(EXIT_SUCCESS);
  
  }
  else {

    #ifndef QUIET
        printf("PID %d: %d possible moves after move #%d; creating %d child processes...\n",getpid(), num_moves, depth, num_moves );
    #endif

    
    for(int i=0; i< num_moves; i++){
      fflush(stdout);
      pid_t pid = fork();
      if(pid<0){
        perror("Error: < fork failed>\n");
      }
      else if(pid == 0){

        int tempx = (*(possible_steps+i)).x_row;
        int tempy = (*(possible_steps+i)).y_col;
        *(*((*b).grid+ tempx)+ tempy)='1';
        ((*b).current).x_row = tempx;
        ((*b).current).y_col = tempy;
        (*b).num_steps += 1;
        free(possible_steps);
        knights_tour(b, depth+1);
        exit(EXIT_SUCCESS);
      }
      else{
        #ifdef NO_PARALLEL
        int status;
        int wp = waitpid(-1, &status, 0);
          if(wp <0){
            perror("Error: <waitpid failed>\n");
          }
        //printf("waitpid %d\n", wp);
        #endif
      }
    }

      #ifndef NO_PARALLEL
      for(int i=0; i< num_moves; i++){
        wait(NULL);
      }
      #endif
      free(possible_steps);
      statistics stats;
      stats.o=0;
      stats.c=0;
      stats.m=0;
      for(int i =0; i < num_moves; i ++){
      statistics temp_stats;
          int rc =read(*(fd+0), &temp_stats, sizeof(statistics));
            if(rc <0){
          perror("Error:  <read failed>\n");
        }
          //printf("read %d", rc);
          stats.o +=temp_stats.o;
          stats.c +=temp_stats.c;
          if(stats.m<temp_stats.m){
            stats.m = temp_stats.m;
          }
      }
        if(parent_pid == getpid()){
          if(stats.o >0 || stats.c >0){
            printf("PID %d: Search complete; found %d open tours and %d closed tours\n",getpid(), stats.o, stats.c ); 
          }
          else{
        printf("PID %d: Search complete; best solution(s) visited %d squares out of %d\n",getpid(), stats.m, ((*b).row*(*b).column));
          }
        }
        else{
          int rc =write(*(fd+1), &stats, sizeof(statistics));
            if(rc <0){
           perror("Error: <fd write failed >\n");
           free(fd);
           //freeboard(b);
        }
      }


  }

  //free(possible_steps);
  freeboard(b);
  free(fd);

}

int main(int argc, char **argv){
  setvbuf( stdout, NULL, _IONBF, 0);
  if( argc != 5){
      fprintf(stderr, "ERROR: Invalid argument(s)\n");
      fprintf(stderr, "USAGE: hw2.out  <m> <n> <r> <c>\n");
      return EXIT_FAILURE;
  } 
  int m = atoi(*(argv+1));
  int n = atoi(*(argv+2));
  int r = atoi(*(argv+3));
  int c = atoi(*(argv+4));
  if(m < 3 || n < 3 || r >= m || c >=n || r<0 || c<0){
  	
  	fprintf(stderr, "ERROR: Invalid argument(s)\n");
  	fprintf(stderr, "USAGE: hw2.out  <m> <n> <r> <c>\n");
    return EXIT_FAILURE;
  }
  
  board bd=populate_board(m,n,r,c);
  
  //print_board(bd, m, n);
  //pid_t pid = getpid();
  printf("PID %d: Solving Sonny's knight's tour problem for a %dx%d board\n",getpid(),m,n);
  printf("PID %d: Sonny starts at row %d and column %d (move #%d)\n",getpid(),r,c,bd.num_steps);
  //statistics stats;
  //stats.o = 0;
  //stats.c = 0;
  //stats.m = 0;
  parent_pid = getpid();
  fd = calloc(2, sizeof(int));
  int rc = pipe(fd);
  if(rc <0){
    perror("Error: <pipe failed>\n");
    free(fd);
  }
 //knights_tour(bd, stats, 1);
  knights_tour(&bd, 1);

    return 0;
  

}

