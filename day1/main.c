#include <stdio.h>
#include <stdlib.h>

int main1()
{
    FILE *fp = fopen("input.txt", "r");

    int increases = 0;
    int previous = 999999;
    int current = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // Take measurement here
        current = atoi(line);
        if (current > previous)
        {
            increases++;
        }

        previous = current;
    }

    fclose(fp);
    free(line);

    printf("Increases: %d\n", increases);

    return 0;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");

    int increases = 0;
    int m1, m2, m3, m4 = -1;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        m1 = m2;
        m2 = m3;
        m3 = m4;
        m4 = atoi(line);

        if (m1 == -1 || m2 == -1 || m3 == -1)
            continue;

        int s1 = m1 + m2 + m3;
        int s2 = m2 + m3 + m4;

        if (s2 > s1)
        {
            increases++;
        }
    }

    fclose(fp);
    free(line);

    printf("Increases: %d\n", increases);

    return 0;
}