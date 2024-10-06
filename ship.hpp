// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#ifndef SHIP_HPP
#define SHIP_HPP


#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>


// These modes represent the different ways to process the input data.
// There are three modes and the state where no mode has been selected.
enum class StackOrQueue {
  kNone = 0,
  kStack,
  kQueue,
  kHelp
};  // Mode{}

enum class Output {
  kNone = 0,
  kMap,   //what is the k of kMap
  kCoordinateList,
};  // Mode{}



struct Square {
    char value;
    char cameFrom = ' ';
};

struct SquareCoords {
    size_t level;
    size_t row;
    size_t column;
};

// This struct is used to pass options read from the command line, to
// the functions that actually do the work. Project 0 is simple enough to
// not need this, but it is a technique that could be helpful in doing more
// complicated command-line processing in future projects.

struct Options {
    StackOrQueue mode = StackOrQueue::kNone;
    Output mode1 = Output::kNone;
};  // Options{}




class Map {
    private:
    // size_t hanger;
    size_t dimension, levels;
    std::vector<std::vector<std::vector<Square>>> map;
    SquareCoords start = {0, 0, 0};
    SquareCoords hanger = {0, 0, 0};


    public:
    //'make this a function'
    
    //constructor to resize map
    Map(size_t dim, size_t lvl) : 
    dimension(dim), 
    levels(lvl), 
    map(lvl, std::vector<std::vector<Square>>(dim, std::vector<Square>(dim, Square{'.', ' '}))) {} 

    void readMap(char typeMap); //reads in from cin

    bool search(Map &mappy, char s_q, char outputMode);  //search container 
    // void backtracking;
    bool inBounds(size_t x, size_t y, size_t z);

    void backtrack_map();

    void backtrack_coords();
    };

void getOptions(int argc, char * argv[], Options &options);


#endif