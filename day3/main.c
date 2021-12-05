#include "BTree.h"
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

/**
 * @brief kill me please
 *
 * Alright, here's the idea:
 *
 * A binary tree where the value of the nodes represents a single character in
 * the current binary value. The root node should be a 0, and should represent
 * a leading 0 in front of all values.
 *
 * As values are added to the tree, the value is split up by its characters and
 * is inserted one char at a time into the tree. On each node of the tree, we
 * should maintain a count of all the nodes container beneath this node so that
 * we can easily count the most common and least common digits at each step.
 *
 */
void part2()
{
    FILE *fp = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // The tree should always have 0 as its root value
    BTreeNode *tree = create_tree(0);
    int i, current;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        current = 0;
        for (i = 11; i >= 0; i--)
        {
            current <<= 1;
            current += line[i] == '1' ? 1 : 0;
        }

        insert_value(tree, current, 12);
    }

    unsigned int first = 0;
    unsigned int second = 0;

    determine_rating(tree, 1, &first);
    determine_rating(tree, 0, &second);
    free_tree(tree);
    printf("Solution to part 2: %u from %u, %u\n", (first * second), first, second);

    fclose(fp);
    free(line);
}

int main()
{
    part1();
    part2();

    return 0;
}