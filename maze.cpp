/* 
maze.cpp

Author: Timothy Lin

Short description of this file: Finding shortest path between
two points in a given maze.
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1], &rows, &cols);// FILL THIS IN
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze, rows, cols);

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
  for (int i = 0; i < rows; i += 1) {
    delete[] mymaze[i];
  }
  delete[] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  //Bool variable for whether path is found
  bool path_found = false;
  
  //Finding start/finish points and storing in respective locs
  Location start_point;
  Location finish_point;
  int num_of_starts = 0;
  int num_of_finishes = 0;
  for (int i = 0; i < rows; i += 1) {
    for (int j = 0; j < cols; j += 1) {
      if (maze[i][j] == 'S') {
        start_point.row = i;
        start_point.col = j;
        num_of_starts += 1;
      }
      else if (maze[i][j] == 'F') {
        finish_point.row = i;
        finish_point.col = j;
        num_of_finishes += 1;
      }
      else if (maze[i][j] != '.' and maze[i][j] != '#') {
        cout << "Error, input format incorrect." << endl;
        return -1;
      }
    }
  }
  
  //Checking there is only one starting point and one finishing point
  if (num_of_starts != 1 or num_of_finishes != 1) {
    return -1;
  }
  
  //Creating queue and storing start point into queue
  Queue queue(rows * cols);
  queue.add_to_back(start_point);
  
  //Creating predecessor_array and initializing values to -1,-1
  Location predecessor_initial;
  predecessor_initial.row = -1;
  predecessor_initial.col = -1;
  Location** predecessor_array = new Location* [rows];
  for (int i = 0; i < rows; i += 1) {
    predecessor_array[i] = new Location [cols];
  }
  for (int i = 0; i < rows; i += 1) {
    for (int j = 0; j < cols; j += 1) {
      predecessor_array[i][j] = predecessor_initial;
    }
  }
  
  //Creating 2d array to check whether points have been used
  //and initializing value to 0
  int** used = new int* [rows];
  for (int i = 0; i < rows; i += 1) {
    used[i] = new int [cols];
  }
  for (int i = 0; i < rows; i += 1) {
    for (int j = 0; j < cols; j += 1) {
      used[i][j] = 0;
    }
  }
  
  //Performing breadth-first search while queue isn't empty
  Location current_location; 
  used[start_point.row][start_point.col] = 1;
  while (queue.is_empty() == false) {
    current_location = queue.remove_from_front();
    
    //Checking north point
    Location north;
    north.row = current_location.row - 1;
    north.col = current_location.col;
    //Checking if point is valid and hasn't been used
    if (north.row >= 0 and north.row < rows and north.col >= 0 and 
        north.col < cols and used[north.row][north.col] == 0) {
      //If point is ".", adds to queue, records to its p_array
      //where current location is, and marks it as visited
      if (maze[north.row][north.col] == '.') {
        queue.add_to_back(north);
        predecessor_array[north.row][north.col] = current_location;
        used[north.row][north.col] = 1;
      }
      //If point is "F", changes current point in maze "*", changes 
      //current point to point stored in its p_array until current
      //point is start_point
      else if (maze[north.row][north.col] == 'F') {
        while (maze[current_location.row][current_location.col] != 'S') {
          maze[current_location.row][current_location.col] = '*';
          current_location = 
            predecessor_array[current_location.row][current_location.col];
        }
        path_found = true;
        break;
      }
    } 

    //Checking west point
    Location west;
    west.row = current_location.row ;
    west.col = current_location.col - 1;
    //Checking if point is valid and hasn't been used
    if (west.row >= 0 and west.row < rows and west.col >= 0 and 
        west.col < cols and used[west.row][west.col] == 0) {
      //If point is ".", adds to queue, records to its p_array
      //where current location is, and marks it as visited
      if (maze[west.row][west.col] == '.') {
        queue.add_to_back(west);
        predecessor_array[west.row][west.col] = current_location;
        used[west.row][west.col] = 1;
      }
      //If point is "F", changes current point in maze "*", changes 
      //current point to point stored in its p_array until current
      //point is start_point
      else if (maze[west.row][west.col] == 'F') {
        while (maze[current_location.row][current_location.col] != 'S') {
          maze[current_location.row][current_location.col] = '*';
          current_location = 
            predecessor_array[current_location.row][current_location.col];
        }
        path_found = true;
        break;
      }
    }    
    
    //Checking south point
    Location south;
    south.row = current_location.row + 1;
    south.col = current_location.col;
    //Checking if point is valid and hasn't been used
    if (south.row >= 0 and south.row < rows and south.col >= 0 and 
        south.col < cols and used[south.row][south.col] == 0) {
      //If point is ".", adds to queue, records to its p_array
      //where current location is, and marks it as visited
      used[south.row][south.col] = 1;
      if (maze[south.row][south.col] == '.') {
        queue.add_to_back(south);
        predecessor_array[south.row][south.col] = current_location;
      }
      //If point is "F", changes current point in maze "*", changes 
      //current point to point stored in its p_array until current
      //point is start_point
      else if (maze[south.row][south.col] == 'F') {
        while (maze[current_location.row][current_location.col] != 'S') {
          maze[current_location.row][current_location.col] = '*';
          current_location = 
            predecessor_array[current_location.row][current_location.col];
        }
        path_found = true;
        break;
      }
    } 
    
    //Checking east point
    Location east;
    east.row = current_location.row;
    east.col = current_location.col + 1;
    //Checking if point is valid and hasn't been used
    if (east.row >= 0 and east.row < rows and east.col >= 0 and 
        east.col < cols and used[east.row][east.col] == 0) {
      //If point is ".", adds to queue, records to its p_array
      //where current location is, and marks it as visited
      if (maze[east.row][east.col] == '.') {
        queue.add_to_back(east);
        predecessor_array[east.row][east.col] = current_location;
        used[east.row][east.col] = 1;
      }
      //If point is "F", changes current point in maze "*", changes 
      //current point to point stored in its p_array until current
      //point is start_point
      else if (maze[east.row][east.col] == 'F') {
        while (maze[current_location.row][current_location.col] != 'S') {
          maze[current_location.row][current_location.col] = '*';
          current_location = 
            predecessor_array[current_location.row][current_location.col];
        }
        path_found = true;
        break;
      }
    }
    
  }

  //Deallocating memory used for the 2d arrays on heap
  for (int i = 0; i < rows; i += 1) {
    delete[] predecessor_array[i];
    delete[] used[i];
  }
  delete[] predecessor_array;
  delete[] used;
  
  //Returning appropriate value
  if (path_found == false) {
    return 0;
  }
  else if (path_found == true) {
    return 1;
  }
}                                              