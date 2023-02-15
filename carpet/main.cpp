/* Mystery carpet
 *
 * Desc:
 *   This program implements a mystery carpet applying pattern matching.
 * The carpet consists of squares of different colors, which also holds
 * true for the pattern, but the size of the pattern is always 2 x 2, i.e.
 * it has four colored squares. The program searches for pattern
 * occurrences from the carpet.
 *   At first, the program asks for the size of the carpet (width and heigth).
 * The user is also asked for if the carpet (grid) will be filled with
 * randomly drawn colors, or with user-given ones. In the first option,
 * a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input as many colors as the
 * there are squares in the carpet, whereupon the user lists the first
 * letters of the colors as one long string.
 *   On each round, the user is asked for a pattern to be searched for
 * (a string consisting of four letters/colors). The program prints, how
 * many occurrences was found and from which coordinates they were found.
 *   The program checks if the user-given colors are among accepted ones.
 * The program terminates when the user gives a quitting command ('q' or 'Q').
 *
 * Program author
 * Name: Merituuli Pirttilä
 * Student number: 1016491
 * UserID: sxmepi
 * E-Mail: merituuli.pirttila@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */

#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>


bool isValidGrid(std::string inputColor);

enum Color{RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};

Color parseColor(char character){
    character = toupper(character);
    if (character == 'R' ){
        return Color::RED;
    }
    if ( character == 'G'){
        return GREEN;
    }
    if ( character == 'B'){
        return BLUE;
    }
    if (character == 'Y'){
        return YELLOW;
    }
    if (character == 'W'){
        return WHITE;
    }
    return NUMBER_OF_COLORS;
}

Color parseColor(int randomColor){
    if (randomColor == 0){
        return RED;
    }
    if (randomColor == 1){
        return GREEN;
    }
    if (randomColor == 2){
        return BLUE;
    }
    if (randomColor == 3){
        return YELLOW;
    }
    if (randomColor == 4){
        return WHITE;
    }
    return NUMBER_OF_COLORS;
}


struct Grid{
    std::vector<std::vector<Color>> grid;
};

struct Pattern{
    std::vector<std::vector<Color>> pattern;
};



std::string userInputString;
void isPatternInGrid(const Grid& grid, const Pattern& pattern);

void initGrid(Grid& grid, int width, int height, bool userInput) {
    // Creates  the grid after user chooses starting mode.
    // Adds vectors called rows to grid
    std::default_random_engine random_generator;
    if (!userInput){
        unsigned long seedValue =0;
        std::cout << "Enter a seed value: ";
        std::cin >> seedValue;
        std::cin.ignore();
        random_generator.seed(seedValue);
        std::uniform_int_distribution<int> distribution(0,4);
        for (int y=0; y < height; ++y){
            std::vector<Color> row;
            for (int x=0; x < width; ++x){
                Color newColor= parseColor(distribution(random_generator));
                row.push_back(newColor);
            }
            grid.grid.push_back(row);
        }

 } else {
        int charInString =0;
        for (int y=0; y<height; ++y){
            std::vector<Color> row;
            for (int x=0; x<width; ++x){
                row.push_back(parseColor(userInputString[charInString]));
                charInString +=1;
            }
            grid.grid.push_back(row);
        }
    }
}


void printGrid(const Grid& grid, int width, int heigth){
    //prints grid by changing the color value of to a char
    char colorPrint = ' ';
    for(int y=0; y< heigth; ++y){
        for( int x=0; x< width; ++x){
            if (grid.grid[y][x]==Color::RED){
                colorPrint = 'R';
            }
            else if (grid.grid[y][x]==Color::GREEN){
                colorPrint = 'G';
            }
            else if (grid.grid[y][x]==Color::BLUE){
                colorPrint = 'B';
            }
            else if (grid.grid[y][x]==Color::YELLOW){
                colorPrint ='Y';
            }
            else if (grid.grid[y][x]==Color::WHITE){
                colorPrint = 'W';
            }
            else {
                std::cout << grid.grid[y][x];
            }
            std::cout << " " << colorPrint;
        } std::cout << std::endl;
    }
}

void askColorPattern(Pattern& pattern, const Grid& grid){
    //Asks user input until four acceptable colors are given
    //Quits if Q or q are given
    std::string fourColors;
    while(true){
        pattern.pattern.clear();
        std::cout << "Enter 4 colors, or q to quit: ";
        std::cin >> fourColors;
        std::cin.ignore();
        int size = fourColors.length();
        if (size == 1 and (fourColors[0]=='Q' or fourColors[0]=='q')){
            return;
        }
        else if (size != 4){
            std::cout << " Error: Wrong amount of colors."<< std::endl;
            continue;
        }

        if(isValidGrid(fourColors)){
            // create pattern vector
            int iterator =0;
            for (int x=0; x<2; ++x){
                std::vector<Color> row;
                for (int y=0; y<2; ++y){
                    Color newColor = parseColor(fourColors[iterator]);
                    row.push_back(newColor);
                    iterator +=1;
                }
                pattern.pattern.push_back(row);
            }
        isPatternInGrid(grid, pattern);
        }

    }

}

bool isPattern(const Grid& grid, const Pattern& pattern, int x, int y){
    bool patternFound = true;
    for (std::vector<Color>::size_type i=0; i < pattern.pattern.size(); ++i){
        for (std::vector<Color>::size_type j=0; j< pattern.pattern[0].size(); ++j){
            if (pattern.pattern[i][j] != grid.grid[x+i][y+j]){
                patternFound = false;
            }
        }
    }
    return patternFound;
}

void isPatternInGrid(const Grid& grid, const Pattern& pattern){
    //finds pattern in grid. iterating through too many for loops
    //is there any way to optimize this
    // calls isPattern
    int matchesFound = 0;
    int gridWidth = grid.grid.size();
    int gridHeight = grid.grid[0].size();
    int patternWidth = pattern.pattern.size();
    int patternHeight = pattern.pattern[0].size();
    for (int x=0; x <= gridWidth - patternWidth; ++x){
        for (int y=0; y <= gridHeight - patternHeight; ++y){
            if(isPattern(grid, pattern, x, y)){
                std::cout<< " - Found at (" << y+1<<", "
                << x+1 << ")" << std::endl;
                matchesFound = matchesFound +1;
            }
        }
    }
    std::cout << " = Matches found: " << matchesFound << std::endl;
    return;
}



bool isValidGrid(std::string inputColor){
    //Checks if user gave valid colors as input
    for (std::string::size_type i=0; i< inputColor.length(); ++i) {
        inputColor[i] = toupper(inputColor[i]);
        if (not (inputColor[i]=='R' or inputColor[i]=='G' or inputColor[i]=='B'
            or inputColor[i]=='Y' or inputColor[i]=='W')){
            std::cout << " Error: Unknown color."<< std::endl;
            return false;
        }
    }
    return true;
}

bool userInputCheck(int gridSize){
    //Asks for starting mode until acceptable input has been given. Calls IsValidGrid if user
    // chooses to input the colors
    while(true){
        std::string startingMode;
        std::cout << "Select start (R for random, I for input): ";
        getline(std::cin, startingMode);
        if (startingMode == "R" or startingMode == "r"){
            std::string randomizeBoard = "randomize";
            return false;
        }
        if (startingMode == "I" or startingMode== "i"){

                std::string inputColor = "";
                std::cout<< "Input: ";
                getline(std::cin, inputColor);
                int size = inputColor.length();
                if (size != gridSize ){
                    std::cout <<" Error: Wrong amount of colors."<< std::endl;
                    continue;
                }
                if(!isValidGrid(inputColor)){
                    continue;
            }
            userInputString = inputColor;
            return true;

        }
    }
}


int main(){
    //asks the width and heigth after which calls appropriate functions for game to work

    int width = 0;
    int height = 0;
    std::cout << "Enter carpet's width and height: ";
    std::cin >> width and std::cin >> height;
    std::cin.ignore();
    int gridSize = width * height;
    if (width < 2 or height < 2){
       std::cout <<" Error: Carpet cannot be smaller than pattern.";
       return EXIT_FAILURE;

     } else {
         Grid grid;
         initGrid(grid, width, height, userInputCheck(gridSize));
         printGrid(grid, width, height);
         Pattern pattern;
         askColorPattern(pattern, grid);

}
}
