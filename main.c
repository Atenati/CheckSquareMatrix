/**
 * Atenati Weber-Morrison
 * May 4, 2020
 * PROG2007 Assignment #4
 */

#include "CheckSquare.h"

int main() {

    /**
     *  -- IMPORTANT --
     *  File pathing on CLion is set to the cmake-build-debug folder
     *  because of this I must use linux relative pathing to leave folder
     *  and use regular .c folder where files are for program consistency
     *  I believe it consistent if the files the program reads and creates
     *  are with the rest .c files as it does in windows
     */

    /* open file, give new file name for creation, run all three test files */
    RunFile("../Test Matrix 1.txt", "../Magic Matrix 1.txt");
    RunFile("../Test Matrix 2.txt", "../Magic Matrix 2.txt");
    RunFile("../Test Matrix 3.txt", "../Magic Matrix 3.txt");
    return 0; // return nothing
}
