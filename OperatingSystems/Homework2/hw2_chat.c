#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXN 10

int board[MAXN][MAXN];
int n, start_x, start_y, closed_tours;

int is_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n && board[x][y] == -1;
}

void print_board() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void find_tours(int x, int y, int depth, int fd[]) {
    int i, j, k;
    int count = 0;
    int moves_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int moves_y[] = {1, 2, 2, 1, -1, -2, -2, -1};

    if (depth == n * n) {
        if (is_valid(x + 2, y + 1) && (x + 2 != start_x || y + 1 != start_y)) {
            count++;
        }
        if (is_valid(x + 2, y - 1) && (x + 2 != start_x || y - 1 != start_y)) {
            count++;
        }
        if (is_valid(x - 2, y + 1) && (x - 2 != start_x || y + 1 != start_y)) {
            count++;
        }
        if (is_valid(x - 2, y - 1) && (x - 2 != start_x || y - 1 != start_y)) {
            count++;
        }
        if (is_valid(x + 1, y + 2) && (x + 1 != start_x || y + 2 != start_y)) {
            count++;
        }
        if (is_valid(x + 1, y - 2) && (x + 1 != start_x || y - 2 != start_y)) {
            count++;
        }
        if (is_valid(x - 1, y + 2) && (x - 1 != start_x || y + 2 != start_y)) {
            count++;
        }
        if (is_valid(x - 1, y - 2) && (x - 1 != start_x || y - 2 != start_y)) {
            count++;
        }
        if (count == 0) {
            closed_tours++;
            print_board();
            return;
        }
    }

    for (k = 0; k < 8; k++) {
        i = x + moves_x[k];
        j = y + moves_y[k];
        if (is_valid(i, j)) {
            int pid = fork();
            if (pid == 0) {
                board[i][j] = depth;
                find_tours(i, j, depth + 1, fd);
                write(fd[1], &closed_tours, sizeof(int));
                exit(0);
            } else if (pid > 0) {
                wait(NULL);
               
            int child_tours;
            read(fd[0], &child_tours, sizeof(int));
            closed_tours += child_tours;
        } else {
            printf("Error: Failed to fork.\n");
            exit(1);
        }
        board[i][j] = -1;
    }
}

}

int main() {
int fd[2];
if (pipe(fd) == -1) {
printf("Error: Failed to create pipe.\n");
exit(1);
}
int i, j;
printf("Enter the size of the board (<= %d): ", MAXN);
scanf("%d", &n);
printf("Enter the starting position (x y): ");
scanf("%d %d", &start_x, &start_y);

for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
        board[i][j] = -1;
    }
}

board[start_x][start_y] = 0;

find_tours(start_x, start_y, 1, fd);

printf("Total number of closed tours: %d\n", closed_tours);

return 0;

}
