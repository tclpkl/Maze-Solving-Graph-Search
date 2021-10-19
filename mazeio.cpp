/* 
mazeio.cpp

Author: Timothy Lin

Short description of this file: Creates read_maze function
that parses input file for maze and allocates to 2d array.
Print_maze function simply prints out the maze in its
current state.
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
  //Opening the file 
  ifstream file;
  file.open(filename);
  if (file.fail()) {
    cout << "Unable to open the file..." << endl;
    return NULL;
  }
  
  //Taking in rows and columns
  int var_rows, var_cols;
  file >> var_rows >> var_cols;
  if (file.fail()) {
    cout << "Unable to read first two numbers..." << endl;
    return NULL;
  }
  *rows = var_rows;
  *cols = var_cols;
  
  //Allocating 2d array for maze
  char** maze = new char*[var_rows];
  for (int i = 0; i < var_rows; i += 1) {
    maze[i] = new char [var_cols];
  }
  
  //Filling in array with file values
  for (int i = 0; i < var_rows; i += 1) {
    for (int j = 0; j < var_cols; j += 1) {
      file >> maze[i][j]; 
    }
  }
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
  cout << rows << " " << cols << endl;
  for (int i = 0; i < rows; i += 1) {
    for (int j = 0; j < cols; j += 1) {
      cout << maze[i][j];
    }
    cout << endl;
  }
}

