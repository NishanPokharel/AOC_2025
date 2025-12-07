#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    unsigned long long start;
    unsigned long long end;
} Range;

int main() 
{
    FILE* file = fopen("./Day5/Day5.txt", "r");
    if (!file) 
    {
        perror("Error opening file");
        return 69;
    }

    Range* ranges = NULL;
    size_t range_count = 0;

    unsigned long long* values = NULL;
    size_t value_count = 0;

    char* line = NULL;
    size_t len = 0;
    int reading_ranges = 1;

    while (getline(&line, &len, file) != -1) 
    {
        if (line[0] != '\0' && line[strlen(line)-1] == '\n') 
        {
            line[strlen(line)-1] = 0;
        }

        if (line[0] == '\0') 
        {
            reading_ranges = 0;
            continue;
        }

        if (reading_ranges) 
        {
            unsigned long long start, end;
            if (sscanf(line, "%llu-%llu", &start, &end) == 2) 
            {
                ranges = realloc(ranges, (range_count + 1) * sizeof(Range));
                ranges[range_count].start = start;
                ranges[range_count].end = end;
                range_count++;
            }
        } 
        else 
        {
            unsigned long long val;
            if (sscanf(line, "%llu", &val) == 1) 
            {
                values = realloc(values, (value_count + 1) * sizeof(unsigned long long));
                values[value_count++] = val;
            }
        }
    }

    fclose(file);
    if (line) 
    {
        free(line);
    }

    size_t fresh_count = 0;
    for (size_t i = 0; i < value_count; i++) 
    {
        unsigned long long id = values[i];
        int fresh = 0;
        for (size_t j = 0; j < range_count; j++) 
        {
            if (id >= ranges[j].start && id <= ranges[j].end) 
            {
                fresh = 1;
                break;
            }
        }
        if (fresh) 
        {
            fresh_count++;
        }
    }

    printf("Number of fresh ingredients: %zu\n", fresh_count);

    free(ranges);
    free(values);
}
