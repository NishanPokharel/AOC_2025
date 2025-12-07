#include "stdio.h"
#include <string.h>
#include <stdlib.h>

int count_adjacent(char** grid, int ROWS, int COLUMNS, int r, int c)
{
    int dirs[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        { 0,-1},       { 0,1},
        { 1,-1},{ 1,0},{ 1,1}
    };

    int count = 0;

    for (int i = 0; i < 8; i++) 
    {
        int nr = r + dirs[i][0];
        int nc = c + dirs[i][1];

        if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLUMNS)
        {
            if (grid[nr][nc] == '@')
            {
                count++;
            }
        }
    }

    return count;
}

int main()
{
    FILE* file = fopen("./Day4/Day4.txt", "r");
    if(!file)
    {
        perror("Error while opening file.\n");
        return 69;
    }

    char line[512];
    char* lines[512];
    int ROWS = 0, COLUMNS = 0;

    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        lines[ROWS] = strdup(line);
        ROWS++;
    }

    fclose(file);

    COLUMNS = strlen(lines[0]);
    char** grid = malloc(ROWS * sizeof(char*));
    for(int i = 0; i < ROWS; ++i)
    {
        grid[i] = lines[i];
    }

    int total_removed = 0;

    while(1)
    {
        int to_remove_capacity = ROWS * COLUMNS;
        int to_remove_count = 0;
        int (*to_remove)[2] = malloc(to_remove_capacity * sizeof *to_remove);

        for(int r = 0; r < ROWS; r++)
        {
            for(int c = 0; c < COLUMNS; c++)
            {
                if(grid[r][c] == '@')
                {
                    int adjacent_count = count_adjacent(grid, ROWS, COLUMNS, r, c);
                    if(adjacent_count < 4)
                    {
                        to_remove[to_remove_count][0] = r;
                        to_remove[to_remove_count][1] = c;
                        to_remove_count++;
                    }
                }
            }
        }

        if(to_remove_count == 0)
        {
            free(to_remove);
            break;
        }

        for (int i = 0; i < to_remove_count; i++)
        {
            int rr = to_remove[i][0];
            int cc = to_remove[i][1];
            grid[rr][cc] = '.';
        }

        total_removed += to_remove_count;
        free(to_remove);
    }

    printf("Total rolls removed: %d\n", total_removed);

    for(int i = 0; i < ROWS; i++)
    {
        free(grid[i]);
    }
    free(grid);
}