#include <stdio.h>
#include "files.h"
#include "ansicolors.h"
#include "arguments.h"
#include "consolelog.h"
int main(int argc, char *argv[]) {
    printError("** Welcome to GrepMinus ** \n");
    parseArguments(argc,argv);
    return 0;
}



