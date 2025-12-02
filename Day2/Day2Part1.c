#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool hasRepeatedPattern(long long num)
{
    char str[32];
    sprintf(str, "%lld", num);
    int len = strlen(str);

    if(len % 2 != 0)
    {
        return false;
    }

    int half = len / 2;
    for(int i = 0; i < half; i++)
    {
        if(str[i] != str[i + half])
        {
            return false;
        }
    }

    return true;
}


void calculateAnswer(long long start, long long end, unsigned long long* answer)
{
    for(long long i = start; i <= end; i++)
    {
        if(hasRepeatedPattern(i))
        {
            *answer += i;
        }
    }
}

int main()
{
    FILE *file = fopen("Day2/Day2.txt", "r");
    if(!file)
    {
        perror("Error: While opening file");
        return 69;
    }

    unsigned long long answer = 0;
    size_t size = 1024;
    size_t len = 0;
    char* buffer = malloc(size);
    if(!buffer)
    {
        perror("malloc failed");
        return 420;
    }

    int c;
    while((c = fgetc(file)) != EOF)
    {
        if(len + 1 >=  size)
        {
            size *= 2;
            char* temp = realloc(buffer, size);
            if(!temp)
            {
                free(buffer);
                perror("realloc failed");
                return 420;
            }
            buffer = temp;
        }
        buffer[len++] = (char)c;
    }
    buffer[len] = '\0';

    char* token = strtok(buffer, ",");
    while(token)
    {
        long long start, end;
        if (sscanf(token, "%lld-%lld", &start, &end) == 2) 
        {
            calculateAnswer(start, end, &answer);
        } 
        else 
        {
            printf("Invalid entry: %s\n", token);
        }

        token = strtok(NULL, ",");
    }

    printf("Sum of all invalid IDs: %llu\n", answer);

    free(buffer);
    fclose(file);
}
