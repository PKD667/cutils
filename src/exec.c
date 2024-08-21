#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../cutils.h"

// Function to execute a command and capture its output
char* exec(const char* cmd) {

  // Open the command for reading and capture its output
  FILE* fp = popen(cmd, "r");

  // Check if the command execution failed
  if (fp == NULL) {
    // Print an error message if execution fails
    printf("Failed to run command");
    exit(1);  // Exit the program with an error code
  }
  // Read the output a line at a time and store it
  char line[PATH_MAX];

  size_t result_alloced = 2048;
  // Initialize a result buffer to store the command's output
  char* result = (char*)calloc(result_alloced, sizeof(char));

  // Read the output from the command and append it to the result buffer
  while (fgets(line, sizeof(line), fp) != NULL) {
    dbg(3,"%s", line);

    // Calculate the current length of the result
    size_t result_len = strlen(result);

    // Calculate the length of the current line of output
    size_t path_len = strlen(line);

    // Check if the result buffer needs to be resized to accommodate the output
    if (result_len + path_len + 1 > result_alloced) {
      // Resize the result buffer to ensure it can hold the entire output
      result_alloced += result_len + path_len + 64;
      result = (char*)realloc(result, result_alloced);
    }

    // Append the current line of output to the result
    strcat(result, line);
  }

  // Close the command execution
  pclose(fp);

  // Return the captured output
  return result;
}
