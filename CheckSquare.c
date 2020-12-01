/**
 * Atenati Weber-Morrison
 * May 4, 2020
 * PROG2007 Assignment #4
 */

#include "CheckSquare.h"

/**
 * Sets standard sum to diagonal sum
 * Checks each column for each row, if that sum does not match initial sum = fail
 * Checks each row for each column, if that sum does not match initial sum = fail
 * returns true if col/row sums did not vary from initial sum
 * @param matrix
 * @param maxrow
 * @param maxcol
 * @return
 */
_Bool CheckSquare(int **matrix, int maxrow, int maxcol) {
    _Bool isSquare = 1; // default is square
    int standardSum = GetStandard(matrix, maxrow, maxcol); // get standard sum

    /* Check sums of columns */
    for(int row = 0; row < maxrow; row++) { // for each row
        int colSum = 0; // initialize that columns base sum
        for(int col = 0; col < maxcol; col++) { // for each column
            colSum += matrix[row][col]; // add to base
        }
        if(colSum != standardSum) { // if at end of column is not equal to standard
            isSquare = 0; // is not square
        }
    } // go to next row and reset column base

    /* check standardSum against other rows and columns sums */
    for(int row = 0; row < maxrow; row++) {// for each row
        int rowSum = 0; // initialize row sum
        for(int col = 0; col < maxcol; col++) { // for each column
            rowSum += matrix[col][row]; // index backwards so checks down columns for each row
        }
        if(rowSum != standardSum) { // if sum of that row index's column is not standard
            isSquare = 0; // is not square
        }
    }

    if(isSquare) { // if hasn't changed (all rows and cols are equal)
        return 1; // return true
    } else { // else
        return 0; // return false
    }
}

/**
 * takes in matrix and maxcolumns and maxrows
 * determins maximum sum
 * gathers sum of diagonal values
 * @param matrix
 * @param maxrow
 * @param maxcol
 * @return
 */
int GetStandard(int **matrix, int maxrow, int maxcol) {
    int standardSum = 0; // initialize to 0
    if(maxrow > maxcol) { // if more row than col
        for(int i = 0; i < maxrow; i++) { // loop per many rows
            standardSum += matrix[i][i]; // set standardSum to sum of all diagonal numbers
        }
    } else { // else more col than row, or equal
        for(int i = 0; i < maxcol; i++) { // loop per many columns
            standardSum += matrix[i][i]; // set standardSum to sum of all diagonal numbers
        }
    }
    return standardSum;
}

void RunFile(char *fileName, char *newFileName) {
    int** matrix;
    char months[12][10] = {
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
    };

    FILE *inputFile; // declare pointer to file
    if ((inputFile = fopen(fileName, "r")) == NULL) { // if file does not exist
        fprintf(stderr, "File does not exist"); // error file does not exist
        exit(EXIT_FAILURE); // exit program
    }

    int year = 0, month = 0, maxrow = 0, maxcol = 0; // initialize variables
    fscanf(inputFile, "%d", &maxrow); // intake next integer, set to maxrow
    fscanf(inputFile, "%d", &maxcol); // intake next integer, set to maxcol (fscanf skips ' ')


    fscanf(inputFile, "%d", &month); // get next integer, set to month
    char monthstr[10]; // declare string monthstr
    strcpy(monthstr, months[month - 1]); // str monthstr to array index of month -1 to offset

    fscanf(inputFile, "%d", &year); //multiply by 10 to add a empty tens place, then add int to that

    /* Matrix creation */
    matrix = (int**)malloc(sizeof(int*) * maxrow); // allocate row space for matrix (2d array)
    /* allocate column space for each row */
    for (int i = 0; i < maxrow; i++) { // index through rows (for each row)
        matrix[i] = (int*)malloc(sizeof(int) * maxcol); // allocate column space for row index
    }
    /* allocating more than available memory test */
    if(matrix == NULL) { // more memory allocated than available
        fprintf(stderr, "malloc failed\n"); // print error
        exit(EXIT_FAILURE); // exit program
    }

    int c = 0; // set and initialize integer c
    int rc = 0; // initialize row count
    int cc = 0; // initialize col count
    for (int i = 0; i < maxrow * maxcol; i++) { // for each item in array
        if (cc == maxcol) { // if column count reaches end of column
            rc++; // increase to next row count
            cc = 0; // reset column count back to 0
        }
        fscanf(inputFile, "%d", &c); // scan in next integer from file
        matrix[rc][cc] = c; // set integer to array index position of [rowcount][colcount]
        cc++; // increase colcount
    }
    fclose(inputFile); // close input file

    /* Write out to new file */
    FILE *outputFile; // declare new pointer to file
    if ((outputFile = fopen(newFileName, "w")) == NULL) { // if file does not exist
        fprintf(stderr, "File does not exist"); // print error does not exist
        exit(EXIT_FAILURE); // exit program
    }

    fprintf(outputFile, "%s, %d\n", monthstr, year); // write out month and year
    for(int row = 0; row < maxrow; row++) { // for each row
        for(int col = 0; col < maxcol; col++) { // for each column
            fprintf(outputFile, "%d ", matrix[row][col]); // write out data in index plus space
        }
        fprintf(outputFile, "\n"); // write out carriage return
    }
    int sum = GetStandard(matrix, maxrow, maxcol); // set sum = standard sum of matrix
    if(CheckSquare(matrix, maxrow, maxcol)) { // if is magic square
        fprintf(outputFile, "Is a magic square (the sums are all %d)", sum); // writeout is magic square
    } else { // else
        fprintf(outputFile, "Is not a magic square"); // write out is not magic square
    }
    fclose(outputFile); // close output file
    /* free space and exit */
    for (int row = 0; row < maxrow; row++) { // for each row
        free(matrix[row]); // free memory in space
    }
    free(matrix); // free matrix
}
