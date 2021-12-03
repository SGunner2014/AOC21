#include <stdio.h>
#include <stdlib.h>

void part1()
{
    FILE *fp = fopen("input.txt", "r");

    int positions[12] = {0};
    int i;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // Logic here
        for (i = 0; i < 12; i++)
        {
            positions[i] += line[i] == '1' ? 1 : -1;
        }
    }

    int gamma = 0;
    int epsilon = 0;

    for (i = 0; i < 12; i++)
    {
        gamma <<= 1;
        epsilon <<= 1;
        gamma += positions[i] > 0 ? 1 : 0;
        epsilon += positions[i] > 0 ? 0 : 1;
    }

    printf("Solution to part 1: %d from %d, %d\n", (gamma * epsilon), gamma, epsilon);

    fclose(fp);
    free(line);
}

void part2()
{
    FILE *fp = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fclose(fp);
    free(line);
}

int main()
{
    part1();
}