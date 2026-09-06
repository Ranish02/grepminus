#include "files.h"
#include "consolelog.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansicolors.h"

typedef struct {
  int isFound;
  int stringLength;
  int lineNumber;
  int columnNumber;
  char *charLocation;
  char *lineStart;
} Loc_T;

Loc_T searchWithinFile(char *buff, char *searchString) {
  int score = 0;
  char *lineStart = buff;
  int len = strlen(searchString);
  int lineNumber = 0;
  for (int i = 0; buff[i] != '\0'; i++) {
    if (buff[i] == '\n') {
      lineStart = &buff[i + 1];
      lineNumber++;
    }
    if (tolower(buff[i]) ==
        tolower(
            searchString[0])) { // is|r|anish i = 2 searchString[0] = |r|anish
      // first char match
      // loop for string until it end and see if that matches or not
      for (int j = 1; searchString[j]; j++) {
        // printf(" cmp %c and %c \n", buff[i+ j], searchString[j]);
        if (tolower(buff[i + j]) !=
            tolower(searchString[j])) { // if NOT r|a|nish i = 3 r|a|nish j = 1
          break;
        } else {
          score++;
        }
      }

      if (score == len - 1) {
        Loc_T location = {.isFound = 1,
                          .charLocation = &buff[i],
                          .lineStart = lineStart,
                          .stringLength = len,
                          .lineNumber = lineNumber,
                          .columnNumber = &buff[i] - lineStart};
        return location;
      } else {
        score = 0;
      }
    }
  }
  Loc_T location = {.isFound = 0};
  return location;
}

char *fileExtension(char *buff, struct dirent *entry) {
  int lastDotIndex = entry->d_namlen;
  for (int i = 1; i < entry->d_namlen; i++) {
    if (entry->d_name[i] == '.') {
      lastDotIndex = i;
    }
  }
  buff[entry->d_namlen - lastDotIndex - 1] =
      '\0'; // -1 accounting for index starting from 0 vs len starting count
            // from 1
  for (int i = lastDotIndex + 1, j = 0; i < entry->d_namlen; i++, j++) {
    buff[j] = entry->d_name[i];
  }
  return buff;
}

void searchStringInFile(char *filename, char *searchString) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printError("file does not exists");
  }
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  char *buff = malloc(file_size + 1);
  rewind(fp);
  fread(buff, 1, file_size, fp);
  buff[file_size] =
      '\0'; // adding null terminator of file at the nth ( end of file)
  Loc_T location = searchWithinFile(buff, searchString);
  if (location.isFound == 1) {
    printf("\n");
    printLineHighlighted(location.lineStart, location.columnNumber,
                         location.stringLength);
    printf("Found at line %d:%d at %s", location.lineNumber + 1, location.columnNumber + 1,filename);
    printf("\n");
  }
  fclose(fp);
}

void fileReader(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printError("file does not exists");
  }


  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  char *buff = malloc(file_size + 1);
  rewind(fp);
  printf("The size of the file is "YELHB" %ld bytes \n"reset"\n", file_size);
  fread(buff, 1, file_size, fp);
  buff[file_size] =
      '\0'; // adding null terminator of file at the nth ( end of file)
  printf("%s \n",buff);
  fclose(fp);
}

void scanDirectoryItemsForSearch(const char *dir_path , char *searchString) {
  // Pointer to the directory stream
  DIR *dir = opendir(dir_path);

  // Check if the directory could be opened
  if (!dir || dir == NULL) {
    return;
  }

  struct dirent *entry;
  // Read directory entries sequentially
  while ((entry = readdir(dir)) != NULL) {
    // Skip current (".") and parent ("..") directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

    if (entry->d_type == DT_DIR) {
      scanDirectoryItemsForSearch(path,searchString);
    } else if (entry->d_type == DT_REG) {
      char buff[24];
      fileExtension(buff, entry);
        searchStringInFile(path, searchString);
    }
  }
  // Close the directory stream
  closedir(dir);
}

void printDirectoryItems(const char *dir_path) {
  // Pointer to the directory stream
  DIR *dir = opendir(dir_path);

  // Check if the directory could be opened
  if (!dir || dir == NULL) {
    return;
  }

  struct dirent *entry;
  // Read directory entries sequentially
  while ((entry = readdir(dir)) != NULL) {
    // Skip current (".") and parent ("..") directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

    if (entry->d_type == DT_DIR) {
      printf("path: %s/%s >>>>>>\n", dir_path, entry->d_name);
      printDirectoryItems(path);
    } else if (entry->d_type == DT_REG) {
      printf("path: %s/%s >>>>>>\n", dir_path, entry->d_name);
    }
  }

  // Close the directory stream
  closedir(dir);
}
