#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BingoCard
{
    int hasWon;
    int nums[25];
    int selected[25];
} BingoCard;

/**
 * @brief Is the current row the start of a new card?
 *
 * @param rowNum
 * @return int
 */
int is_new_card(int rowNum)
{
    return (rowNum - 1) % 6 == 0;
}

/**
 * @brief Parse the first line of numbers from the file
 *
 * @param line
 * @param nums
 * @return int
 */
int parse_called_nums(char *line, int *nums)
{
    char *buffer = (char *)calloc(256, sizeof(char));
    int counter = 0;
    char *start = line;
    char *end;

    while (*line != '\0')
    {
        if (*line == ',')
        {
            end = line;
            buffer[0] = '\0';
            strncat(buffer, start, (end - start));
            nums[counter] = atoi(buffer);
            start = end + 1;
            counter++;
        }

        line++;
    }

    buffer[0] = '\0';
    strncat(buffer, start, (line - start));
    nums[counter] = atoi(buffer);

    free(buffer);
    return ++counter;
}

/**
 * @brief Parse a single line in a bingo card input
 *
 * @param line
 * @param nums
 */
void parse_card_line(char *line, int *nums)
{
    // We have exactly 5 numbers to parse and we know exactly which positions
    // they'll be at - yay!

    int i;
    char buff[3] = {0};

    for (i = 0; i < 5; i++)
    {
        strncpy(buff, &line[i * 3], 2);
        nums[i] = atoi(buff);
    }
}

/**
 * @brief Calls a single number on a single card
 *
 * @param card
 * @param number
 * @return int
 */
int call_card_number(BingoCard *card, int number)
{
    int hasWon = 0;
    int hasNumber = 0;
    int i;
    int score = 0;

    for (i = 0; i < 25; i++)
    {
        if (card->nums[i] == number)
        {
            card->selected[i] = 1;
            hasNumber = 1;
        }
    }

    if (hasNumber)
    {
        int j;
        // Loop through rows and columns to see if we have any lines crossed off
        for (j = 0; j < 5; j++)
        {
            // check it as a row
            if (card->selected[(j * 5) + 0] && card->selected[(j * 5) + 1] && card->selected[(j * 5) + 2] &&
                card->selected[(j * 5) + 3] && card->selected[(j * 5) + 4])
            {
                hasWon = 1;
                break;
            }

            if (card->selected[j + (0 * 5)] && card->selected[j + (1 * 5)] && card->selected[j + (2 * 5)] &&
                card->selected[j + (3 * 5)] && card->selected[j + (4 * 5)])
            {
                hasWon = 1;
                break;
            }
        }
    }

    if (hasWon)
    {
        for (i = 0; i < 25; i++)
        {
            score += card->selected[i] ? 0 : card->nums[i];
        }
    }

    return hasWon ? score * number : 0;
}

/**
 * Naïve solution:
 *
 * Loop through array using rows and columns at the same time
 * Check to see if the row/column has the target number by looping through its
 * elements. If it does, mark off the element in the selected array. Proceed to
 * check the current row/column in the selected array to see if all the
 * elements are marked off as selected. If they are, then we know that this
 * bingo card has won first.
 *
 * Then, we can loop over all the elements within this bingo card in no
 * particular order, making sure to add the unselected ones as we go. Simply
 * multiply this sum by the last selected number and we're good.
 */
void part1()
{
    FILE *fp;

    fp = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int rowNum = 0;

    int calledNums[512] = {0};
    int cardCount = 0;
    int calledNumsCount;
    int innerCardCounter;

    BingoCard cards[512];
    int rowNums[5] = {0};

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (rowNum == 0) // If we're on the first row, we're reading in called numbers
        {
            calledNumsCount = parse_called_nums(line, calledNums);
        }
        else // If we're past the second row, we're reading in cards
        {
            if (is_new_card(rowNum))
            {
                innerCardCounter = 0;
                cardCount++;
                cards[cardCount - 1].hasWon = 0;
            }
            else
            {
                parse_card_line(line, rowNums);
                int i;

                // Loop through each number in the row and add it to the card
                for (i = 0; i < 5; i++)
                {
                    cards[cardCount - 1].nums[(innerCardCounter * 5) + i] = rowNums[i];
                    cards[cardCount - 1].selected[(innerCardCounter * 5) + i] = 0;
                }

                innerCardCounter++;
            }
        }

        rowNum++;
    }
    printf("Card count: %d\n", cardCount);

    // We have read in all the cards, now to perform bingo
    int i, j;
    int hasWon;
    int currentCalledNum;
    int lastBoardWon;
    for (i = 0; i < calledNumsCount; i++)
    {
        currentCalledNum = calledNums[i];
        for (j = 0; j < cardCount; j++)
        {
            if (!cards[j].hasWon)
            {
                hasWon = call_card_number(&cards[j], currentCalledNum);
                if (hasWon)
                {
                    lastBoardWon = j;
                    cards[j].hasWon = hasWon;
                }
            }
        }
    }

exit:

    printf("Has won: %d with called no. %d\n", cards[lastBoardWon].hasWon, currentCalledNum);

    fclose(fp);
    free(line);
}

int main()
{
    part1();
    return 0;
}