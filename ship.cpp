#include "bot.hpp"
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

//READING FUNCTION
void Map::readMap(char typeMap1) {

    // MAP MODE
if (typeMap1 == 'M') {
    size_t level = 0, row = 0;
    string line;
    
    // Read input until all levels and rows are processed
    while (level < levels) {
        row = 0;
        while (row < dimension) {
            // Read a line from input
            if (!getline(cin, line)) {
                cerr << "Error: Unexpected end of input while reading level " << level << ", row " << row << endl;
                exit(1);
            }

            // Skip comments and empty lines
            if (line.empty() || line[0] == '/') {
                continue;
            }

         

            // Process each column in the current row
            size_t column = 0;
            while (column < dimension) {
                char inputChar = line[column];

                // Validate the input character
                if (inputChar != 'S' && inputChar != 'H' && inputChar != 'E' &&
                    inputChar != '.' && inputChar != '#') {
                    cerr << "Invalid map character" << endl;
                    exit(1);
                }

                // Assign the character to the map
                map[level][row][column].value = inputChar;

                // If it's the start ('S'), save the start square
                if (inputChar == 'S') {
                    map[level][row][column].cameFrom = 'C';
                    start = {level, row, column}; 
                }

                ++column;
            }

            ++row;
        }
        ++level;
    }
}

    //COORDINATE MODE
     else if (typeMap1 == 'L') {
        char inputChar;
        while (cin >> inputChar){
            // 'ignore //comments' w/ getline
        if (inputChar == '/') {
            string ignoreLine;
            getline(cin, ignoreLine);  // Skip the rest of the line
        }else{
            size_t level, row, column;
            char comma;

            // Read coords and the character
            cin >> level >> comma >> row >> comma >> column >> comma >> inputChar >> comma;
            // Check for valid characters (S, H, E, etc)
            if (inputChar != 'S' && inputChar != 'H' && inputChar != 'E' &&
                inputChar != '.' && inputChar != '#') {
                cerr << "Invalid map character" << endl;
                exit(1);
            }

                if (level > levels - 1) {

                    cerr << "Invalid map level" << endl;
                    exit(1);

                } else if (row > dimension - 1) {

                    cerr << "Invalid map row" << endl;
                    exit(1);

                } else if (column > dimension - 1) {

                    cerr << "Invalid map column" << endl;
                    exit(1);

                }

            if (level < levels && row < dimension && column < dimension) {
                map[level][row][column].value = inputChar;
                map[level][row][column].cameFrom = ' '; // Set default value for 'cameFrom'

                if (inputChar == 'S') {
                    map[level][row][column].cameFrom = 'C'; // Set start
                    start = {level,row,column}; // Set starting coordinates
                } 
                if (inputChar == 'H') {
                    map[level][row][column].cameFrom = ' '; // Set start
                    hanger = {level, row, column}; // Set starting coordinates
                } 
            }

        }
    }
  }
}

//Bounds checking function
bool Map::inBounds(size_t x, size_t y, size_t z) {
    return static_cast<int>(x) >= 0 && x < levels && static_cast<int>(y) >= 0 && y < dimension && z < dimension;
}

//Search container function
bool Map::search(Map &mappy, char s_q, char outputMode) { 

    deque<SquareCoords> searchContainer;
    bool hangerFound = false;

    searchContainer.push_back(mappy.start); // Push starting coordinates

    while (!searchContainer.empty() && !hangerFound) {
        SquareCoords currentCoords;
        if (s_q == 'q') {
            currentCoords = searchContainer.front();
            searchContainer.pop_front();
        } else {
            currentCoords = searchContainer.back();
            searchContainer.pop_back();
        }

        // Get current row, column, level
        size_t row = currentCoords.row;
        size_t column = currentCoords.column;
        size_t level = currentCoords.level;

       const Square &currentSquare = mappy.map[level][row][column];
        // Explore North (N): (row - 1, column)
        if (mappy.inBounds(level, row - 1, column) && mappy.map[level][row - 1][column].cameFrom == ' ' && mappy.map[level][row - 1][column].value != '#') {
            mappy.map[level][row - 1][column].cameFrom = 'n'; // Mark as discovered
            // If we found the hangar ('H'), stop searching
            if (mappy.map[level][row - 1][column].value == 'H') {
            // (" << level << "," << row << "," << column << ")" << std::endl;
                hangerFound = true;
                
                mappy.hanger.row = row - 1;
                mappy.hanger.column = column;
                mappy.hanger.level = level;

                break;
            }
            searchContainer.push_back(SquareCoords{level, row - 1, column}); // Push coordinates to searchContainer
        }

        // Explore East (E): (row, column + 1)
        if (mappy.inBounds(level, row, column + 1) && mappy.map[level][row][column + 1].cameFrom == ' ' && mappy.map[level][row][column + 1].value != '#') {
            mappy.map[level][row][column + 1].cameFrom = 'e'; // Mark as discovered
            // If we found the hangar ('H'), stop searching
        if (mappy.map[level][row][column + 1].value == 'H') {
          // (" << level << "," << row << "," << column << ")" << std::endl;
            hangerFound = true;
            
          //  cout << "hanger found" << endl;
            mappy.hanger.row = row;
            mappy.hanger.column = column + 1;
            mappy.hanger.level = level;

            break;
        }
            searchContainer.push_back(SquareCoords{level, row, column + 1}); // Push coordinates to searchContainer
        }

        // Explore South (S): (row + 1, column)
        if (mappy.inBounds(level, row + 1, column) && mappy.map[level][row + 1][column].cameFrom == ' ' && mappy.map[level][row + 1][column].value != '#') {
            mappy.map[level][row + 1][column].cameFrom = 's'; // Mark as discovered
            // If we found the hangar ('H'), stop searching
        if (mappy.map[level][row + 1][column].value == 'H') {
          // (" << level << "," << row << "," << column << ")" << std::endl;
            hangerFound = true;

            mappy.hanger.row = row + 1;
            mappy.hanger.column = column;
            mappy.hanger.level = level;

            break;
        }
            searchContainer.push_back(SquareCoords{level, row + 1, column}); // Push coordinates to searchContainer

        }
        // Explore West (W): (row, column - 1)
        if (mappy.inBounds(level, row, column - 1) && mappy.map[level][row][column - 1].cameFrom == ' ' && mappy.map[level][row][column - 1].value != '#') {
            mappy.map[level][row][column - 1].cameFrom = 'w'; // Mark as discovered
            // If we found the hangar ('H'), stop searching
        if (mappy.map[level][row][column - 1].value == 'H') {
            hangerFound = true;
            
            mappy.hanger.row = row;
            mappy.hanger.column = column - 1;
            mappy.hanger.level = level;

            break;
        }
            searchContainer.push_back(SquareCoords{level, row, column - 1}); // Push coordinates to searchContainer
        }


        // Check for elevators ('E') on other levels
        if (currentSquare.value == 'E') {
            for (size_t otherLevel = 0; otherLevel < mappy.levels; ++otherLevel) {
                if (otherLevel != level && mappy.map[otherLevel][row][column].value == 'E' && mappy.map[otherLevel][row][column].cameFrom == ' ') {
                    mappy.map[otherLevel][row][column].cameFrom = to_string(level)[0]; // Mark as discovered
                    searchContainer.push_back(SquareCoords{otherLevel, row, column}); // Push elevator coordinates
                }
            }
        }
    }

    if (!hangerFound) {

          if (outputMode == 'm') {
        cout << "Start in level " << start.level << ", row " << start.row << ", column " << start.column << "\n";
            for (size_t level1 = 0; level1 < levels; ++level1) {
                cout << "//level " << level1 << "\n";
                for (size_t row1 = 0; row1 < dimension; ++row1) {
                    for (size_t col1 = 0; col1 < dimension; ++col1) {

                            cout << map[level1][row1][col1].value;
                    }
                    cout << "\n"; 
                }
            }
        }           
    
        else if (outputMode == 'c') {
     // Output the path
            cout << "//path taken\n";
        }
    }
    return hangerFound;
}




void Map::backtrack_map() {
    size_t level = hanger.level;
    size_t row = hanger.row;
    size_t column = hanger.column;

    // Keep track of the previous direction
    char prevValue = map[level][row][column].cameFrom;

    // Do not overwrite the hangar ('H')
    while (prevValue != 'C') {  // Backtrack until you reach the start 'C'
        // Set the direction on the map according to the previous step
        if (prevValue == 'n') {
            row++;  // Came from North, move back South
            map[level][row][column].value = prevValue;
        } else if (prevValue == 'e') {
            column--;  // Came from East, move back West
            map[level][row][column].value = prevValue;
        } else if (prevValue == 's') {
            row--;  // Came from South, move back North
            map[level][row][column].value = prevValue;
        } else if (prevValue == 'w') {
            column++;  // Came from West, move back East
            map[level][row][column].value = prevValue;
        } else if (isdigit(prevValue)) {
            size_t l = level;
            // Handle elevator transitions (levels are stored as digits)
            level = static_cast<size_t>(prevValue - '0'); // Go back to the previous level
            map[level][row][column].value = to_string(l)[0];
        }            


        // Move to the next previous direction
        prevValue = map[level][row][column].cameFrom;
    }

    // Overwrite the start ('S') with the first move direction
    // Check in which direction the next step after start was made
    if (row > start.row) {

        map[start.level][start.row][start.column].value = 'n';  // Move North to the next step
    } else if (row < start.row) {
        map[start.level][start.row][start.column].value = 's';  // Move South to the next step
    } else if (column > start.column) {
        map[start.level][start.row][start.column].value = 'w';  // Move West to the next step
    } else if (column < start.column) {
        map[start.level][start.row][start.column].value = 'e';  // Move East to the next step
    }

    // PRINT SECTION
    cout << "Start in level " << start.level << ", row " << start.row << ", column " << start.column << "\n";
    for (size_t level1 = 0; level1 < levels; ++level1) {
        cout << "//level " << level1 << "\n";
        for (size_t row1 = 0; row1 < dimension; ++row1) {
            for (size_t col1 = 0; col1 < dimension; ++col1) {
                // Skip 'S', display the direction instead
                if (map[level1][row1][col1].value == ' ') { //OR ISBLANK
                    cout << '.';  // Or some other representation of an empty floor space
                } else {
                    cout << map[level1][row1][col1].value;
                }
            }
            cout << "\n";
        }
    }
}


void Map::backtrack_coords() {
    // Start at the hangar location
    size_t currL = hanger.level;
    size_t currR = hanger.row;
    size_t currC = hanger.column;
    // cout << "backtrack accessed" << endl;

    deque<pair<SquareCoords, char>> path; // Store both coordinates and the direction

    // Get the value of cameFrom for the current square
    char prevValue = map[currL][currR][currC].cameFrom;
    size_t temp = 0;
    // Backtrack from the hangar to the start
    while (prevValue != 'C') {  // 'C' represents the start ('S')
        // Store the current coordinates and direction in the path
        if (prevValue == 'n') {
            currR++; // Came from the North, move South
        } else if (prevValue == 'e') {
            currC--; // Came from the East, move West
        }  else if (prevValue == 's') {
            currR--; // Came from the South, move North
        } else if (prevValue == 'w') {
            currC++; // Came from the West, move East
        } else {
            temp = currL;
            currL = size_t(prevValue - '0');
        }

        if(isdigit(prevValue)){
            path.push_front({{currL, currR, currC}, to_string(temp)[0]});
        }else{
            path.push_front({{currL, currR, currC}, prevValue});
        }

        // Update prevValue to the next cameFrom direction
        prevValue = map[currL][currR][currC].cameFrom;
    }

    // Output the path
    cout << "//path taken\n";
    for (const auto& entry : path) {
        auto coord = entry.first;
        char direction = entry.second;
        cout << "(" << coord.level << "," << coord.row << "," << coord.column << "," << direction << ")\n";
    }
}




// Print help for the user when requested.
// argv[0] is the name of the currently executing program
void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " [-s | -q] [-o M|L] | -h\n";
    cout << "This program is for navigating a space station maze using BFS or DFS.\n";
    cout << "Options:\n";
    cout << "  -s, --stack         Use DFS (stack-based search)\n";
    cout << "  -q, --queue         Use BFS (queue-based search)\n";
    cout << "  -o, --output M|L    Specify output format: M for map, L for coordinate list\n";
    cout << "  -h, --help          Display this help message\n";
    exit(0);
}  // printHelp()


void getOptions(int argc, char *argv[], Options &options) { 
  // These are used with getopt_long()
  opterr = false; // Let us handle all error output for command line options
  int choice;
  int index = 0;
  option long_options[] = {
    {"stack", no_argument, nullptr, 's'},
    {"queue", no_argument, nullptr, 'q'},
    {"output", required_argument, nullptr, 'o'},
    {"help", no_argument, nullptr, 'h'},
    { nullptr, 0, nullptr, '\0' }  // Marks the end of the array
  };

  // Process options
  while ((choice = getopt_long(argc, argv, "sqo:h", long_options, &index)) != -1) {
    switch (choice) {
      case 'h':
        printHelp(argv);
        exit(0);

      case 's':
        if (options.mode == StackOrQueue::kQueue) {
          cerr << "Multiple routing modes specified" << endl;
          exit(1);
        }
        options.mode = StackOrQueue::kStack;
        options.mode1 = Output::kMap;
        break;

      case 'q':
        if (options.mode == StackOrQueue::kStack) {
          cerr << "Multiple routing modes specified" << endl;
          exit(1);
        }
        options.mode = StackOrQueue::kQueue;
        options.mode1 = Output::kMap;
        break;
    
      case 'o': {
        string arg{optarg};
        if (arg == "M") {
          options.mode1 = Output::kMap;
        } else if (arg == "L") {
          options.mode1 = Output::kCoordinateList;
        } else {
          cerr << "Invalid output mode specified" << endl;
          exit(1);
        }
        break;
      }

      default:
        options.mode1 = Output::kMap;
    }
  }

  // Check if a search strategy was chosen (either stack or queue)
  if (options.mode == StackOrQueue::kNone) {
    cerr << "No routing mode specified" << endl;
    exit(1);
  }
}


int main(int argc, char *argv[]) {
  // This should be in all of your projects, speeds up I/O
  ios_base::sync_with_stdio(false);
  // Set two digits of precision on output

  // Get the mode from the command line and read in the data
    Options options;
    getOptions(argc, argv, options);

    char s_q;
    char typeMap;
    size_t levels, dimension;


    // Read dimensions and levels from input
    cin >> typeMap >> levels >> dimension; // Read the dimension size
    // Create Map instance with dimensions and levels
    Map mappy(dimension, levels);
    bool found = true;
    // Read the map data
    mappy.readMap(typeMap);

    char outputMode = 'm';
    
     if (options.mode1 == Output::kCoordinateList) {
        outputMode = 'c';
    } 

    if (options.mode == StackOrQueue::kStack) {
        s_q = 's';
        found = mappy.search(mappy, s_q, outputMode); // Use s_q to determine the search strategy
    }
     else if (options.mode == StackOrQueue::kQueue) {
        s_q = 'q';
        found = mappy.search(mappy, s_q, outputMode); // Use s_q to determine the search strategy
    } 


    if (!found) {
        return 0;
    } else {
        if (outputMode == 'm') {
        mappy.backtrack_map();
    } 
    
    else if (outputMode == 'c') {
        mappy.backtrack_coords();
    }
    }
    return 0;
}


