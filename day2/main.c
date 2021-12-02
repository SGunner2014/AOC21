#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main1()
{
    FILE *fp = fopen("input.txt", "r");

    int horizontal = 0;
    int depth = 0;
    int current;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // String comparison here
        if (strncmp(line, "up", 2) == 0)
        {
            current = atoi(&line[3]);
            depth -= current;
        }
        else if (strncmp(line, "down", 4) == 0)
        {
            current = atoi(&line[5]);
            depth += current;
        }
        else if (strncmp(line, "forward", 7) == 0)
        {
            current = atoi(&line[8]);
            horizontal += current;
        }
    }

    fclose(fp);
    free(line);

    printf("Value: %d\n", (horizontal * depth));

    return 0;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");

    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    int current;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // String comparison here
        if (strncmp(line, "up", 2) == 0)
        {
            current = atoi(&line[3]);
            // depth -= current;
            aim -= current;
        }
        else if (strncmp(line, "down", 4) == 0)
        {
            current = atoi(&line[5]);
            // depth += current;
            aim += current;
        }
        else if (strncmp(line, "forward", 7) == 0)
        {
            current = atoi(&line[8]);
            horizontal += current;
            depth += (aim * current);
        }
    }

    fclose(fp);
    free(line);

    printf("Value: %d\n", (horizontal * depth));

    return 0;
}