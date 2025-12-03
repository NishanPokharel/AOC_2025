#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void find12DigitNum(const char* value, char* output)
{
    int size = strlen(value);
    int pos = 0;
    int start = 0;

    for(int pick = 0; pick < 12; pick++)
    {
        int remaining = 12 - pick - 1;
        int end = size - remaining;

        char best = '0' - 1;
        int best_index = start;

        for(int i = start; i < end; i++)
        {
            if(value[i] > best)
            {
                best = value[i];
                best_index = i;
            }
        }

        output[pos++] = best;
        start = best_index + 1;
    }

    output[pos] = '\0';
}

int main()
{
    FILE* file = fopen("./Day3/Day3.txt", "r");
    if(file == NULL)
    {
        perror("Error while opening the file");
        return 69;
    }

    char line[512];
    long long total_sum = 0;
    char output[64];

    while(fgets(line, sizeof(line), file) != NULL)
    {
        char value[512];
        if(sscanf(line, "%511s", value) == 1)
        {
            find12DigitNum(value, output);
            total_sum += atoll(output);
        }
        else
        {
            printf("Encountered invalid line. ABORTING.........\n");
            return 1;
        }
    }

    printf("Answer: %lld\n", total_sum);
    fclose(file);
}
