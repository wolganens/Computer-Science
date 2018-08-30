#include "TestMaze.h"
#include <iostream>
#include <cstdlib>
#include <stack>

TestMaze :: TestMaze() {
}


bool TestMaze :: isIdx(int x, int y){
    if(x <= 0 || x >= dimx || y <= 0 || y >= dimy || (x >= dimx - 1 && y < dimy * 3 / 4) || (y >= dimy - 1 && x < dimx * 3 / 4))
        return false;
    
    return true;
}

void TestMaze :: generateMaze(int r){
    dimx = 20; dimy = 20;
    for(int i=0; i<dimy; i++)
        for(int j=0; j<dimx; j++)
        lab[i][j] = ' ';
    for(int i=0; i<dimx; i++){
        lab[0][i] = '*';
        lab[dimy-1][i] = '*';
        lab[i][0] = '*';
        lab[i][dimx-1] = '*';
    }

    lab[dimy-2][dimx-1] = ' ';
    
    robot = r;
    
    posIni = Point(1,1);
}

// Should load the maze from a text file
// Here is just creates boundaries with an exit at the bottom
void TestMaze :: loadMaze(string arquivo) {        
    int posInX, posInY, i, j, width, height;
    string token, lab_line;
    fstream fs (arquivo.c_str(), fstream::in);
    fs >> token;
    cout << token << endl;
    
    // Lê as dimensões do labirinto
    if (token.compare("dim") == 0) {
        //cout << "leu dim" << endl;
        fs >> height >> width;
        dimx = width;
        dimy = height;
        if(dimx > MAX_MAZE || dimy > MAX_MAZE){
            cerr << "error! maze size is greater than MAX_MAZE" << endl;
        }
    } else {
        exit(-1);
    }
    fs >> token;
    //Lê a posição inicial (x,y) do robô no lab
    if (token.compare("pos") == 0) {
        //cout << "leu pos" << endl;
        fs >> posInX >> posInY;
    } else {
        exit(-1);
    }
    fs >> token;
    // Lê o código identificador do robô
    if (token.compare("robo") == 0) {
        //cout << "leu robo" << endl;
        fs >> this->robot;
    } else {
        exit(-1);
    } 
    // Estava lendo uma linha a menos do lab, o ignore abaixo resolveu a questão
    fs.ignore();
    
    for ( i = 0 ; i < height ; i++) {
        getline(fs, lab_line);
        for (j = 0 ; j <  width; j++) {
            this->lab[i][j] = lab_line[j];            
        }
    }
    fs.close();
    this->posIni = Point(posInX, posInY);
    //cout << "Robo: " << robot << ", Inicial: [" << posInX << "," << posInY << "] Dim: [" << dimx << "," << dimy << "]";
}

// Returns true if the x,y pos is empty
bool TestMaze :: isEmpty(const Point& pos) const {
    if( pos.getX() <0 || pos.getX() >=dimx || pos.getY() < 0 || pos.getY() >= dimy) {
        return true;
    }
    return (lab[pos.getY()][pos.getX()] == ' ');
}

// Return the maze dimensions
int TestMaze :: getWidth() { return dimx; }
int TestMaze :: getHeight() { return dimy; }

int TestMaze::getRobot() { return robot; }

Point TestMaze::getIniPos() { return posIni; }
