// *******************************************************************************************************************************************
//                                                               DAY 1 PART 1  
// *******************************************************************************************************************************************
// You arrive at the secret entrance to the North Pole base ready to start decorating. 
// Unfortunately, the password seems to have been changed, so you can't get in. A document taped to the wall helpfully explains:
// "Due to new security protocols, the password is locked in the safe below. Please see the attached document for the new combination."
// The safe has a dial with only an arrow on it; around the dial are the numbers 0 through 99 in order. 
// As you turn the dial, it makes a small click noise as it reaches each number. 
// The attached document (your puzzle input) contains a sequence of rotations, one per line, which tell you how to open the safe. 
// A rotation starts with an L or R which indicates whether the rotation should be to the left (toward lower numbers) or to the right (toward higher numbers). 
// Then, the rotation has a distance value which indicates how many clicks the dial should be rotated in that direction.
// So, if the dial were pointing at 11, a rotation of R8 would cause the dial to point at 19. After that, a rotation of L19 would cause it to point at 0.
// Because the dial is a circle, turning the dial left from 0 one click makes it point at 99. Similarly, turning the dial right from 99 one click makes it point at 0.
// So, if the dial were pointing at 5, a rotation of L10 would cause it to point at 95. After that, a rotation of R5 could cause it to point at 0.
// The dial starts by pointing at 50.
// You could follow the instructions, but your recent required official North Pole secret entrance security training seminar taught you that the safe is actually a decoy. 
// The actual password is the number of times the dial is left pointing at 0 after any rotation in the sequence.


#include <stdio.h>
#include <stdlib.h>

void calculatePosition(int* arr, int size, int** currentIndex, int moveStep, int* counter)
{
    for(int i = 0; i < abs(moveStep); ++i)
    {
        if(moveStep > 0)
        {
            (*currentIndex)++;
            if(*currentIndex >= arr + size)
            {
                *currentIndex = arr;
            }
        }
        else
        {
            (*currentIndex)--;
            if(*currentIndex < arr)
            {
                *currentIndex = arr + size - 1;
            }
        }

        if(**currentIndex == 0)
        {   
            (*counter)++;
        }
    }
} 

int main()
{
    int arr[100];

    for(int i = 0; i < 100; ++i)
    {
        arr[i] = i;
    }

    // point to 50
    int* ptr = &arr[50];
    int counter = 0;
    char line[256];
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    // read form file line by line
    FILE* file = fopen("./Day1/Day1Part1.txt", "r");
    if(file == NULL)
    {
        perror("Error opening file");
        return 69;
    }
    // while reading, if we encounter 0, we add the counter by 1
    while(fgets(line, sizeof(line), file) != NULL)
    {
        // parse the value by direction and number
        char side;
        int value;

        if(sscanf(line, " %c%d", &side, &value) == 2)
        {
            if(side == 'L')
            {
                value = value * -1;
            }
            calculatePosition(arr, arrSize, &ptr, value, &counter);
        }
        else
        {
            printf("Encountered Invalid Line. ABORTING.......\n");
            return 1;
        }
    }

    printf("The password is %d\n", counter);
    fclose(file);
}
