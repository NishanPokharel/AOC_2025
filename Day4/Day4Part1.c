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

    int accessible_rolls = 0;
    for (int r = 0; r < ROWS; r++) 
    {
        for (int c = 0; c < COLUMNS; c++) 
        {
            if(grid[r][c] == '@')
            {
                int adj = count_adjacent(grid, ROWS, COLUMNS, r, c);
                if (adj < 4)
                {
                    accessible_rolls++;
                }
            }
        }
    }

    printf("Accessible rolls: %d\n", accessible_rolls);

    for (int i = 0; i < ROWS; i++)
    {
        free(grid[i]);
    }
    free(grid);
}