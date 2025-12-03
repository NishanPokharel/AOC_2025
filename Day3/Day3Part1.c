#include <stdio.h>
#include <string.h>

void find2DigitNum(const char* value, int* total_sum)
{
    int size = strlen(value);
    int best_tens = -1;
    int best_result = -1;

    for(int i = 0; i < size; i++)
    {
        int d = value[i] - '0';

        if(best_tens != -1)
        {
            int num = best_tens * 10 + d;
            if(num > best_result)
            {
                best_result = num;
            }
        }

        if(d > best_tens)
        {
            best_tens = d;
        }
    }
    
    *total_sum += best_result;
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
    int total_sum = 0;

    while(fgets(line, sizeof(line), file) != NULL)
    {
        char value[512];
        if(sscanf(line, "%511s", value) == 1)
        {
            find2DigitNum(value, &total_sum);
        }
        else
        {
            printf("Encountered invalid line. ABORTING.........\n");
            return 1;
        }
    }

    printf("Answer: %d\n", total_sum);
    fclose(file);
}
