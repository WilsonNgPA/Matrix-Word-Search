//Ng, Pei Aou Wilson, 100332292
//g++ -pedantic -Wall -Wextra -std=c++14 assign3.cpp -o assign3
//This program will look for a word in the matrix and print out the path as a matrix

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>


/*
inputs: m -  a 2d vector<char> containing the original letter matrix
s - a 2d vector<char> contains only '-' and will eventually contain the path of the word if it exists in m
word - a string containing the word to be looked for in the matrix
row - an unsigned int that represents current row in matrix
column - an unsigned int that represents current column in matrix
matchedLength - an unsigned int that represents the number of char in word matched
*/
//output: true if matched, false otherwise
//This method will look in 4 directions(up, down, left and right) from the current coordinates in the matrix to look for the word in the matrix
bool checkMatrix(std::vector<std::vector<char>> &m, std::vector<std::vector<char>> &s, const std::string &word, unsigned row, unsigned column, unsigned matchedLength) {
    if(matchedLength == word.size()) {
        return true;
    }
    if(row < m.size() && column < m[0].size()) {
        if(m[row][column] == word[matchedLength]) {
            if(checkMatrix(m, s, word, row + 1, column, matchedLength + 1)) {
                if(matchedLength == word.size() - 1) {
                    s[row][column] = '*';
                    return true;
                } 
                else {
                    s[row][column] = 'V';
                    return true;
                }
            }
            else if(checkMatrix(m, s, word, row - 1, column, matchedLength + 1)) {
                if(matchedLength == word.size() - 1) {
                    s[row][column] = '*';
                    return true;
                } 
                else {
                    s[row][column] = '^';
                    return true;
                }
            }
            else if(checkMatrix(m, s, word, row, column + 1, matchedLength + 1)) {
                if(matchedLength == word.size() - 1) {
                    s[row][column] = '*';
                    return true;
                } 
                else {
                    s[row][column] = '>';
                    return true;
                }
            }
            else if(checkMatrix(m, s, word, row, column - 1, matchedLength + 1)) {
                if(matchedLength == word.size() - 1) {
                    s[row][column] = '*';
                    return true;
                } 
                else {
                    s[row][column] = '<';
                    return true;
                }
            }
        }
    }
    return false;
}


/*
inputs: m - a 2d vector<char> containing the original letter matrix
s - a 2d vector<char> containing only '-'
word - a string entered by the user to be looked for
*/
//output: true if word is found, false otherwise
bool searchMatrix(std::vector<std::vector<char>> &m, std::vector<std::vector<char>> &s, const std::string &word) {
    unsigned currLength = word.size();
    if(currLength > m.size() * m[0].size()) {
        return false;
    }
    for(unsigned i = 0; i < m.size(); i++) {
        for(unsigned j = 0; j < m[i].size(); j++) {
            if(m[i][j] == word[0]) {
                if(checkMatrix(m, s, word, i, j, 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}


//inputs: word - a string entered by the user
//outputs: none
//This method converts a string to uppercase
void capitalize(std::string &word) {
    for(char &c : word) {
        c = std::toupper(c);
    }
}


//Referred from vectorEx.cpp from Array_Vector file by Ryan Zier-Vogel
//inputs: m - a 2d vector<char> to be printed
//outputs: none
//This method prints out a 2d vector to the console  
void print(std::vector<std::vector<char>> &m){
    for(unsigned i = 0; i < m.size(); i++){
        for(unsigned j =0; j < m[i].size(); j++){
             std::cout << std::setw(3) << m[i][j] << " " ;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}


//inputs: filename - a string containing the filename entered by the user
//outputs: a 2d vector<char> containing letters obtained from the file specified by user
//This method creates a 2d vector<char> with the size specified in the file, fills it with the characters(in uppercase) found in the file and returns it
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


//inputs: m - a 2d vector<char>
//outputs: a 2d vector<char> with the same size as m, but contains only 'm'
//This method creates a 2d vector<char> of the same size as m and fills it wiht '-'
std::vector<std::vector<char>> solutionMatrix(std::vector<std::vector<char>> &m) {
    std::vector<std::vector<char>> s(m.size(), std::vector<char> (m[0].size(),0));
    for(unsigned i = 0; i < m.size(); i++) {
        for(unsigned j = 0; j < m[i].size(); j++) {
            s[i][j] = '-';
        }
    }
    return s;
}


int main() {
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

    //Creating a the solution matrix that contains only '-' that will eventually contain the path if found
    std::vector<std::vector<char>> s = solutionMatrix(m);

    //If found, print the path
    if(searchMatrix(m, s, word)) {
        print(s);
    }
    //Else, print no path found
    else {
        std::cout << "No path found" << std::endl;
    }
    
}