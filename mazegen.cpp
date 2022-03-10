#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <stack>

using namespace std;

class mazePath{
    
    public:
    bool checkIfPathFound (int index, int NUM_ROWS, int NUM_COLUMBS);
    bool checkIfEmpty(vector <bool> &indexesOfPath);
    void addDotPath(int index, vector <bool>& indexesOfPath);
    void removeDotPath(int index, vector <bool> &indexesOfPath);
    vector<bool> returnPath(vector <bool>& indexesOfPath);
    bool returnTop(vector <bool>& indexesOfPath);

    
};

class coordinates{
    public:
    char possibleMovements(int NUM_ROWS, int NUM_COLUMNS, int& x, int&y, int& index, vector<bool>& isVisited, vector<pair<int,int> > gridCoordinates);
};

bool mazePath::checkIfEmpty(vector <bool>& indexesOfPath){
    if (indexesOfPath.empty() == false){
        return false;

    }
    else{
        return true;

    }
}

bool mazePath::returnTop(vector <bool>& indexesOfPath){
    if (indexesOfPath.empty()){
        cout << "Stack is empty" << endl;
        return 0;

    }
    else{
        return indexesOfPath.back();

    }
}

bool mazePath::checkIfPathFound(int index, int NUM_ROWS, int NUM_COLUMNS){
    if (index == (NUM_ROWS * NUM_COLUMNS)-1){
        return true;

    }
    else{
        return false;

    }
}

vector<bool> mazePath::returnPath(vector <bool> &indexesOfPath){
    return indexesOfPath;

}

void mazePath::addDotPath(int index, vector <bool> &indexesOfPath){
    indexesOfPath.at(index) = true;

}

void mazePath::removeDotPath(int index, vector <bool> &indexesOfPath){
    indexesOfPath.at(index) = false;

}


char coordinates::possibleMovements(int NUM_ROWS, int NUM_COLUMNS, int& x, int&y, int& index, vector<bool>& isVisited, vector<pair<int,int> > gridCoordinates){

    vector<char> movementPossibilities;
    int numberOfMovements;
    int randomNumber;
    char chosenMovement;
    bool noMovement = true;

    if (y != 0  && index - NUM_COLUMNS >= 0){ // UP
        
        if (isVisited.at(index - NUM_COLUMNS) == false){
            movementPossibilities.push_back('a');
            noMovement = false;
        }
    }

    if (y != NUM_ROWS-1 && index + NUM_COLUMNS <= gridCoordinates.size()){ // DOWN
    
        if (isVisited.at(index+NUM_COLUMNS) == false){
            movementPossibilities.push_back('b');
            noMovement = false;
        }
        
    } 

    if (x != 0 && index - 1 >= 0) { //LEFT
    
        if (isVisited.at(index-1)==false){
            movementPossibilities.push_back('c');
            noMovement = false;
        } 
    }

    if (x != NUM_COLUMNS-1 && index + 1 <= gridCoordinates.size()){ //RIGHT
    
        if (isVisited.at(index+1)==false){
            movementPossibilities.push_back('d');
            noMovement = false;
        }
    }

    if (noMovement){
        return 'e';
        
    }
    
    numberOfMovements = movementPossibilities.size();
    randomNumber = rand()%numberOfMovements;
    chosenMovement = movementPossibilities.at(randomNumber);
    
    return chosenMovement;
}
int pathFinder(int NUM_ROWS, int NUM_COLUMNS, vector<pair<int,int> > gridCoordinates, vector<bool>& isVisited, int& index, int& x, int& y, stack<string>& operatorsStack,vector<pair<int, int> >& currentCoordinates, vector<pair<string, string> >&maze, bool& stopStacking, mazePath& mazeRoute, vector <bool> &indexesOfPath) {
    
    coordinates mazeSolution;
    int randomNumber = 4;
    char chosenMovement;
    bool allVisited = false;
    stack<int> tempStack;


    isVisited.at(0) = true;
    
    while(allVisited == false){
        chosenMovement = mazeSolution.possibleMovements(NUM_ROWS,NUM_COLUMNS,x,y,index,isVisited, gridCoordinates);
        
        int totalChecked = 0;
        if (mazeRoute.checkIfPathFound(index,NUM_ROWS,NUM_COLUMNS) == true){
            stopStacking = true;
            
        }

        for (int i = 0; i < isVisited.size(); ++i){
            if (isVisited.at(i) == true){
                ++totalChecked;
                
            }
            if (totalChecked == (isVisited.size()) - 1){
                allVisited = true;
                
            }
        }
        
        switch (chosenMovement)
        {
            case ('a'): // Up
                --y;
                index -= NUM_COLUMNS;
                maze.at(index + NUM_COLUMNS).first = ("+   ");
                operatorsStack.push("a");
                isVisited.at(index) = true;
                
                if (stopStacking == false){
                    mazeRoute.addDotPath(index, indexesOfPath);
                }
                currentCoordinates.push_back(make_pair(x,y));
                continue;

            case ('b'): // Down
                ++y;
                index += NUM_COLUMNS;
                maze.at(index).first = ("+   ");
                operatorsStack.push("b");
                isVisited.at(index) = true;
                
                if (stopStacking == false){
                    mazeRoute.addDotPath(index, indexesOfPath);
                }
                currentCoordinates.push_back(make_pair(x,y));
                continue;

            case('c'): // Left
                --x;
                --index;
                maze.at(index + 1).second = ("    ");
                operatorsStack.push("c");
                isVisited.at(index) = true;
               
                if (stopStacking == false){
                    mazeRoute.addDotPath(index, indexesOfPath);
                }
                currentCoordinates.push_back(make_pair(x,y));
                continue;

            case('d'): // Right
                ++x;
                ++index;
                maze.at(index).second = ("    ");
                operatorsStack.push("d");
                isVisited.at(index) = true;
                
                if (stopStacking == false){
                    mazeRoute.addDotPath(index, indexesOfPath);
                }
                currentCoordinates.push_back(make_pair(x,y));
                continue;

            case('e'): // Backtracking
                int totalChecked = 0;
                bool runBacktracking = true;

                for (int i = 0; i < isVisited.size(); ++i){
                    if (isVisited.at(i) == true){
                        ++totalChecked;
                        
                    }
                    if (totalChecked == (isVisited.size()) - 1){
                        allVisited = true;
                        runBacktracking = false;

                    }
                }

                if (mazeRoute.checkIfEmpty(indexesOfPath) == false && stopStacking == false){
                    mazeRoute.removeDotPath(index, indexesOfPath);
                   
                }
                
                if (runBacktracking ){
                    if (operatorsStack.top() == "a"){
                        index += NUM_COLUMNS;
                        operatorsStack.pop();

                    }
                    else if(operatorsStack.top() == "b"){
                        index -= NUM_COLUMNS;
                        operatorsStack.pop();

                    }
                    else if (operatorsStack.top() == "c"){
                        ++index;
                        operatorsStack.pop();

                    }
                    else{
                        --index;
                        operatorsStack.pop();

                    }
        
                    currentCoordinates.pop_back();
                    x = currentCoordinates.back().first;
                    y = currentCoordinates.back().second;
                   
                    return pathFinder(NUM_ROWS,NUM_COLUMNS,gridCoordinates, isVisited, index, x, y, operatorsStack, currentCoordinates, maze, stopStacking, mazeRoute, indexesOfPath);
                }
        }
        

        

    }
    for (int i = 0; i < indexesOfPath.size(); ++i){
        if (indexesOfPath.at(i) == true){
            maze.at(i).second.at(2) = '.';
        }
    }

    return 0;
}
void printMaze(int NUM_ROWS, int NUM_COLUMNS, vector<pair<string,string> >cellWalls, vector<pair<string, string> >& maze, mazePath& mazeRoute){
    int ticker = 0;
    bool switchPrinting = true;
    
    for (int i = 0; i < (NUM_COLUMNS * NUM_ROWS) + 1 ; ++i){
        if (i != ticker && i % NUM_COLUMNS == 0 ){
            if (switchPrinting){
                cout << "+" << endl;
                i = ticker;
                cout << maze.at(i).second;
                switchPrinting = false;
                
            }
            else{
                if (i < (NUM_COLUMNS*NUM_ROWS)){
                    cout << "|" << endl;
                    cout << maze.at(i).first;

                }
                else {
                    break;

                }

                switchPrinting = true;
                ticker += NUM_COLUMNS;
            }
            
            
        }
        else{
             if (switchPrinting){
                cout << maze.at(i).first;

             }
             else{
                cout << maze.at(i).second;

             }
        }
    }
    cout << "|" << endl;
    
    for (int j = 0; j < NUM_COLUMNS; ++j){
        cout << cellWalls.at(0).first;

    }

    cout << "+";

}

int main(int argc, char* argv[]){
    
    vector<pair<int, int> > currentCoordinates;
    int NUM_COLUMNS;
    int NUM_ROWS;
    int SEED;
    vector<pair< int, int> > gridCoordinates;
    stack<string> operatorsStack;
    int index = 0;
    int x = 0,y = 0;
    vector<pair<string, string> >cellWalls (1, make_pair("+---", "|   "));
    vector<pair<string, string> > maze;
    bool stopStacking = false;
    mazePath mazeRoute;
    
    NUM_ROWS = atoi(argv[1]);
    NUM_COLUMNS = atoi(argv[2]);
    if (argc == 4){
        SEED = atoi(argv[3]);
        srand(SEED);

    }
    else{
        srand(time(0));

    }

    vector <bool> indexesOfPath ((NUM_COLUMNS * NUM_ROWS), false);

    indexesOfPath.at(0) = true;
    for (int i = 0; i < (NUM_COLUMNS * NUM_ROWS); ++ i){
        maze.push_back(make_pair(cellWalls.at(0).first,cellWalls.at(0).second));

    }
    
    for (int i = 0; i < NUM_ROWS; ++i){
        for (int j = 0; j< NUM_COLUMNS; ++j){
            gridCoordinates.push_back(make_pair(j,i));

        }
    }
    vector<bool> isVisited (gridCoordinates.size(), false);
    
    pathFinder(NUM_ROWS, NUM_COLUMNS, gridCoordinates, isVisited, index, x, y, operatorsStack, currentCoordinates, maze, stopStacking, mazeRoute, indexesOfPath);
    printMaze(NUM_ROWS, NUM_COLUMNS, cellWalls, maze, mazeRoute);

    return 0;
}