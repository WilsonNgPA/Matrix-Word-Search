//Ng, Pei Aou Wilson 100332292
//Assignment 8 main file

#include <iostream>
#include <fstream>
#include <iomanip>
#include "STACK.H"

//struct for state
struct state{
    unsigned length;
    int row;
    int col;
    std::string dir;
};

//Converts string to all uppercase
void capitalize(std::string &word) {
    for(char &c : word) {
        c = std::toupper(c);
    }
}

//Prints out the matrix
void print(std::vector<std::vector<char>> &m){
    for(unsigned i = 0; i < m.size(); i++){
        for(unsigned j =0; j < m[i].size(); j++){
             std::cout << std::setw(3) << m[i][j] << " " ;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}

//Create state from given parameters and return it
state createState(unsigned length, int row, int col, std::string dir) {
    state s = {length, row, col, dir};
    return s;
}

std::vector<std::vector<char>> visitedMatrix(std::vector<std::vector<char>> &m) {
    std::vector<std::vector<char>> visited(m.size(), std::vector<char> (m[0].size(),0));
    for(unsigned i = 0; i < m.size(); i++) {
        for(unsigned j = 0; j < m[i].size(); j++) {
            visited[i][j] = '-';
        }
    }
    return visited;
}

//Creates a matrix with the path of the word
std::vector<std::vector<char>> solutionMatrix(std::vector<std::vector<char>> &m, stack<state> s) {
    std::vector<std::vector<char>> path(m.size(), std::vector<char> (m[0].size(),0));
    for(unsigned i = 0; i < m.size(); i++) {
        for(unsigned j = 0; j < m[i].size(); j++) {
            path[i][j] = '-';
        }
    }
    path[s.peek().row][s.peek().col] = '*';
    s.pop();
    while(!s.isEmpty()) {
        if(s.peek().dir == "up") {
            path[s.peek().row][s.peek().col] = '^';
        }
        else if(s.peek().dir == "down") {
            path[s.peek().row][s.peek().col] = 'V';
        }
        else if(s.peek().dir == "left") {
            path[s.peek().row][s.peek().col] = '<';
        }
        else if(s.peek().dir == "right") {
            path[s.peek().row][s.peek().col] = '>';
        }
        s.pop();
    }
    return path;
}

//This method will look in 4 directions(up, down, left and right) from the current coordinates in the matrix to look for the word in the matrix
bool checkMatrix(std::vector<std::vector<char>> &m, std::vector<std::vector<char>> &v, const std::string &word, stack<state> s) {
    int row = s.peek().row;
    int col = s.peek().col;

    while(!s.isEmpty()) {
        if(s.peek().length == word.size() - 1) {
            std::vector<std::vector<char>> path = solutionMatrix(m, s);
            print(path);
            return true;
        }
        if(row + 1 < static_cast<int>(m.size()) && m[row + 1][col] == word[s.peek().length + 1] && v[row + 1][col] != 'X') {
            v[row + 1][col] = 'X';
            row += 1;
            unsigned length = s.peek().length;
            s.pop();
            s.push(createState(length, row - 1, col, "down"));
            s.push(createState(s.peek().length + 1, row, col, ""));
        }
        else if(row - 1 >= 0 && m[row - 1][col] == word[s.peek().length + 1] && v[row - 1][col] != 'X') {
            v[row - 1][col] = 'X';
            row -= 1;
            unsigned length = s.peek().length;
            s.pop();
            s.push(createState(length, row + 1, col, "up"));
            s.push(createState(s.peek().length + 1, row, col, ""));
        }
        else if(col + 1 < static_cast<int>(m[0].size()) && m[row][col + 1] == word[s.peek().length + 1] && v[row][col + 1] != 'X') {
            v[row][col + 1] = 'X';
            col += 1;
            unsigned length = s.peek().length;
            s.pop();
            s.push(createState(length, row, col - 1, "right"));
            s.push(createState(s.peek().length + 1, row, col, ""));
        }
        else if(col - 1 >= 0 && m[row][col - 1] == word[s.peek().length + 1] && v[row][col - 1] != 'X') {
            v[row][col - 1] = 'X';
            col -= 1;
            unsigned length = s.peek().length;
            s.pop();
            s.push(createState(length, row, col + 1, "left"));
            s.push(createState(s.peek().length + 1, row, col, ""));
        }
        else {
            s.pop();
            if(s.isEmpty()) {
                return false;
            }
            row = s.peek().row;
                col = s.peek().col;
        }
    }
    return false;
    
}

//Finds the every letter in m that matches first first letter in word and run checkMatrix, passing in the stack with the coordinate of the match
bool searchMatrix(std::vector<std::vector<char>> &m, const std::string &word) {
    unsigned currLength = word.size();
    if(currLength > m.size() * m[0].size()) {
        return false;
    }
    for(unsigned i = 0; i < m.size(); i++) {
        for(unsigned j = 0; j < m[i].size(); j++) {
            if(m[i][j] == word[0]) {
                stack<state> s;
                std::vector<std::vector<char>> visited = visitedMatrix(m);
                s.push(createState(0, i, j, "start"));
                if(checkMatrix(m, visited, word, s)) {
                    return true;
                }
            }
        }
    }
    return false;
}

//Creates a matrix from the specified file
std::vector<std::vector<char>> getMatrix(const std::string &filename) {
    std::ifstream in;
    int row = 0;
    int column = 0;
    char c;
    in.open(filename);
    if(in.is_open()) {
        in >> row;
        in >> column;
        std::vector<std::vector<char>> m(row, std::vector<char> (column,0));
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < column; j++) {
                in >> c;
                m[i][j] = std::toupper(c);
            }
        }
        in.close();
        return m;
    }
    else {
        std::cout << "The file specified does not exists" << std::endl;
        exit(0);
    }
}


int main() {
    //Create stack<state> that will store the solution/path
    stack<state> s = stack<state>();
    //Creating 2 string variable to store filename and the word to be looked for
    std::string filename;
    std::string word;

    //Prompting user to enter fila name and storing it
    std::cout << "Name of the file with the matrix" << std::endl;
    std::cin >> filename;

    //Create a 2d vector<char> from the file specified by the user using the getMatrix() method
    std::vector<std::vector<char>> m = getMatrix(filename);

    //Prints the matrix created from the file specified by the user
    print(m);

    //Prompting user to enter the word to be looked for in the matrix and storing it
    std::cout << "What word are you looking for" << std::endl;
    std::cin >> word;

    //Convert word to all uppercase
    capitalize(word);

    //If found, print print path found
    if(searchMatrix(m, word)) {
        std::cout << "Path found" << std::endl;
    }
    //Else, print no path found
    else {
        std::cout << "No path found" << std::endl;
    }
}