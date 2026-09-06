#include "consolelog.h"
#include <stdio.h>
#include <string.h>
#include "files.h"
#include "ansicolors.h"

#define FILEPATH 3;
#define SEARCH_ACTION 2; 
void search(char *searchString, char *dir){
    scanDirectoryItemsForSearch(dir, searchString);
}

void parseArguments(int argc, char *argv[]){
    // for(int i = 0; i < argc; i++){
    char cmd[1024];
    int i = 1;
    if(argc > 2){
        if(strcmp(argv[i], "search") == 0){
            if(argv[i+1]== NULL){
                snprintf(cmd, 1024, "Please provide a string \n grepminus search string filepath");
                printError("Please provide a string to search \n");
            }else if(argv[i+2]== NULL){
                snprintf(cmd, 1024, "Please provide a filepath and use . to look for in current directory\ngrepminus search %s filepath",argv[i+1]);
                printError(cmd);
            }else{
                search(argv[i+1], argv[i+2]);
            }
    return;
        }
    }
    printf(BLU"* Use the following syntaxt to start searching *\n"reset);
    printf("\t grepminus "UCYN"search "UYEL"string"MAG" filepath \n"reset);
}