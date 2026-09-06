#include "consolelog.h"
#include <stdio.h>
#include "ansicolors.h"

void printError(char *str){
    // Print it in red (\033[0;31m) and reset to default (\033[0m)
    printf("\033[0;31m%s\033[0m\n",str);
    return;
}

void printLine( char *str){
    for(int i= 0; str[i] != '\0';i++){
        printf("%c",str[i]);
    }
    printf("\n");
    return;
}

void printLineHighlighted( char *line, int start, int len){
    for(int i= 0; line[i] != '\n' && line[i] != '\0';i++){
        if( i == start ){
            printf(UGRN"%c",line[i]);
            while( len != 1){
                i++;
                len--;
                printf("%c", line[i]);
            }
            printf(""reset);
        }
        else {
            printf("%c", line[i]);
        }         
    }
    printf("\033[0m\n");
    // for(int i = 0; i < start + 9; i++){
    //     printf(" ");
    // }
    printf("%*s^\n", start, "");
    return;

}

void printWhole(char *str , int len){
    for(int i= 0; i < len ;i++){
        if(str[i] == '\n'){
            printf("\n");
        }else{
            printf("%c",str[i]);
        }
    }
    printf("\n");
    return;
}

void printArguments ( int argc, char *argv[]){
    for( u_int32_t i = 0; i < argc; i++){
        printf("%d = %s \n", i, argv[i]); // argv[0] is the executable program name
    }
    return;
}