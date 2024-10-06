#ifndef BOT_HPP
#define BOT_HPP


#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>



enum class StackOrQueue {
  kNone = 0,
  kStack,
  kQueue,
  kHelp
};  // Mode{}

enum class Output {
  kNone = 0,
  kMap,  
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


struct Options {
    StackOrQueue mode = StackOrQueue::kNone;
    Output mode1 = Output::kNone;
};  // Options{}




class Map {
    private:
    size_t dimension, levels;
    std::vector<std::vector<std::vector<Square>>> map;
    SquareCoords start = {0, 0, 0};
    SquareCoords hanger = {0, 0, 0};


    public:
    
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
