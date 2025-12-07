#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    unsigned long long start;
    unsigned long long end;
} Range;

int compareRange(const void* a, const void* b)
{
    Range* r1 = (Range*)a;
    Range* r2 = (Range*)b;
    if (r1->start < r2->start) 
    {
        return -1;
    }
    if (r1->start > r2->start) 
    {
        return 1;
    }
    return 0;
}

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
    }

    fclose(file);
    if (line) 
    {
        free(line);
    }

    qsort(ranges, range_count, sizeof(Range), compareRange);

    unsigned long long totalFreshIndegrientRange = 0;

    if(range_count > 0)
    {
        unsigned long long current_start = ranges[0].start;
        unsigned long long current_end = ranges[0].end;

        for (size_t i = 1; i < range_count; i++) 
        {
            if (ranges[i].start <= current_end + 1) 
            {
                if (ranges[i].end > current_end)
                {
                    current_end = ranges[i].end;
                }
            } 
            else 
            {
                totalFreshIndegrientRange += current_end - current_start + 1;
                current_start = ranges[i].start;
                current_end = ranges[i].end;
            }
        }
        totalFreshIndegrientRange += current_end - current_start + 1;
    }

    printf("Number of fresh ingredients: %llu\n", totalFreshIndegrientRange);

    free(ranges);
}
