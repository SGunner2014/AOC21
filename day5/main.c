#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int xS, yS, xF, yF;
} Line;

/**
 * @brief Parses a single line of input
 *
 * @param line
 * @return Line
 */
Line parse_line(char *line)
{
    Line toReturn;
    int parsed[4];
    char buffer[6];
    int counter = 0;
    char *start = line;
    int previousWasNumber = 1;

    while (*line != '\0')
    {
        if (*line == ',') // if we've reached the end of this first number
        {
            buffer[0] = '\0';
            strncat(buffer, start, (line - start));
            parsed[counter] = atoi(buffer);
            start = line + 1;
            counter++;
        }
        else if (*line == ' ') // We've either reached the midpoint or the start of the last two numbers.
        {
            if (previousWasNumber) // Have we reached the midpoint yet?
            {                      // no, we haven't
                buffer[0] = '\0';
                strncat(buffer, start, (line - start));
                parsed[counter] = atoi(buffer);
                counter++;
                previousWasNumber = 0;
            }

            start = line + 1;
        }

        line++;
    }

    buffer[0] = '\0';
    strncat(buffer, start, (line - start));
    parsed[counter] = atoi(buffer);

    toReturn.xS = parsed[0];
    toReturn.yS = parsed[1];
    toReturn.xF = parsed[2];
    toReturn.yF = parsed[3];

    return toReturn;
}

/**
 * @brief Parses input and then detects how many collisions there are.
 *
 */
void part1()
{
    FILE *fp = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Line lines[512];
    Line currentLine;
    int lineCount = 0;
    int xLimit = 0;
    int yLimit = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // Parse this line
        currentLine = parse_line(line);
        if (currentLine.xS == currentLine.xF || currentLine.yS == currentLine.yF)
        {
            lines[lineCount] = currentLine;
            printf("%d, %d -> %d, %d\n", lines[lineCount].xS, lines[lineCount].yS, lines[lineCount].xF,
                   lines[lineCount].yF);
            lineCount++;

            // Figure out what bounds we should have for the diagram
            if (currentLine.xF > xLimit)
            {
                xLimit = currentLine.xF;
            }
            else if (currentLine.xS > xLimit)
            {
                xLimit = currentLine.xS;
            }

            if (currentLine.yF > yLimit)
            {
                yLimit = currentLine.yF;
            }
            else if (currentLine.yS > yLimit)
            {
                yLimit = currentLine.yS;
            }
        }
    }

    // We use calloc so that each position has an initial value of 0 collisions
    int *diagram = (int *)calloc((xLimit + 1) * (yLimit + 1), sizeof(int));
    int i, j;

    for (i = 0; i < lineCount; i++)
    {
        // Add this line into the diagram
        currentLine = lines[i];

        // Figure out whether it's vertical or horizontal to save on loops
        if (currentLine.xS < currentLine.xF)
        {
            // Loop through the bounds of the line and increment the values in the diagram
            for (j = currentLine.xS; j < currentLine.xF + 1; j++)
            {
                diagram[(j * xLimit) + currentLine.yS]++;
            }
        }
        else if (currentLine.xF < currentLine.xS)
        {
            for (j = currentLine.xF; j < currentLine.xS + 1; j++)
            {
                diagram[(j * xLimit) + currentLine.yS]++;
            }
        }
        else if (currentLine.yS < currentLine.yF)
        {
            for (j = currentLine.yS; j < currentLine.yF + 1; j++)
            {
                diagram[(currentLine.xS * xLimit) + j]++;
            }
        }
        else if (currentLine.yF < currentLine.yS)
        {
            for (j = currentLine.yF; j < currentLine.yS; j++)
            {
                diagram[(currentLine.xS * xLimit) + j]++;
            }
        }
    }

    for (i = 0; i <= xLimit; i++)
    {
        for (j = 0; j <= yLimit; j++)
        {
            printf("%d", diagram[(i * xLimit) + j]);
        }

        printf("\n");
    }

    printf("xLimit: %d, yLimit: %d\n", xLimit, yLimit);

    free(diagram);

    fclose(fp);
    free(line);
}

int main()
{
    part1();
}