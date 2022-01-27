#pragma once
#include <vector>
#include <ctime>
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <fstream>

using namespace std;
class Tile {
public:
	bool mine = false;
	bool flag = false;
    bool revealed = false;
	vector<Tile*> adjacent;
    sf::Sprite tile;
    sf::Sprite topper;

};

class Board {
public:
	Tile board[16][25];
    int flagCount = 0;
    bool debugFlag = false;
    sf::Sprite face;
    sf::Sprite number;
    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
};
sf::Vector2i tileCoords(sf::Vector2i mouse, Board& board) {
    sf::Vector2i coords;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (board.board[i][j].tile.getGlobalBounds().contains(mouse.x, mouse.y)) {
               coords.x = i;
               coords.y = j;
              
               return coords;
            }
        }
    }
}
void emptyTile(Board& board, sf::Vector2i coords) {
    int x = coords.x;
    int y = coords.y;
    board.board[x][y].tile.setTexture(TextureManager::getTexture("tile_revealed"));
    board.board[x][y].topper.setTexture(TextureManager::getTexture("tile_revealed"));
    board.board[x][y].revealed = true;
        if (board.board[x][y-1].adjacent.size() == 0 && x>=0 && x < 16 && y>0 && y < 25 && !board.board[x][y-1].revealed) {
           
            coords.y = y-1;
            emptyTile(board, coords);
        }
       
         
        if (board.board[x-1][y].adjacent.size() == 0 && x > 0 && x < 16 && y >= 0 && y < 25 && !board.board[x-1][y].revealed) {
           
            coords.x = x - 1;
            emptyTile(board, coords);
        }
       
          
        if (board.board[x][y+1].adjacent.size() == 0 && x >= 0 && x < 16 && y >= 0 && y < 24 && !board.board[x][y + 1].revealed) {
            coords.y = y + 1;
            
            emptyTile(board, coords);
        }
      
        
        if (board.board[x+1][y].adjacent.size() == 0 && x >= 0 && x < 15 && y >= 0 && y < 25 && !board.board[x+1][y].revealed) {
           
            coords.x = x + 1;
            emptyTile(board, coords);

        }
}

void populate(Board& board1) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            board1.board[i][j].adjacent.clear();
        }
    }
    //populating corners
   //0, 0
    if ((board1).board[0][1].mine) {
        (board1).board[0][0].adjacent.push_back(&board1.board[0][1]);
    }
    if ((board1).board[1][0].mine) {
        (board1).board[0][0].adjacent.push_back(&board1.board[1][0]);
    }
    if ((board1).board[1][1].mine) {
        (board1).board[0][0].adjacent.push_back(&board1.board[1][1]);
    }
    //0, 24
    if ((board1).board[0][23].mine) {
        (board1).board[0][24].adjacent.push_back(&board1.board[0][23]);
    }
    if ((board1).board[1][23].mine) {
        (board1).board[0][24].adjacent.push_back(&board1.board[1][23]);
    }
    if ((board1).board[1][24].mine) {
        (board1).board[0][24].adjacent.push_back(&board1.board[1][24]);
    }
    //15, 0
    if ((board1).board[14][0].mine) {
        (board1).board[15][0].adjacent.push_back(&board1.board[15][0]);
    }
    if ((board1).board[14][1].mine) {
        (board1).board[15][0].adjacent.push_back(&board1.board[1][0]);
    }
    if ((board1).board[15][1].mine) {
        (board1).board[15][0].adjacent.push_back(&board1.board[1][1]);
    }
    //15, 24
    if ((board1).board[14][24].mine) {
        (board1).board[15][24].adjacent.push_back(&board1.board[0][1]);
    }
    if ((board1).board[14][23].mine) {
        (board1).board[15][24].adjacent.push_back(&board1.board[1][0]);
    }
    if ((board1).board[15][23].mine) {
        (board1).board[15][24].adjacent.push_back(&board1.board[1][1]);
    }
    //populating edges
    //top
    for (int i = 1; i < 24; i++) {
        if ((board1).board[1][i - 1].mine) {
            (board1).board[0][i].adjacent.push_back(&board1.board[1][i - 1]);
        }
        if ((board1).board[1][i].mine) {
            (board1).board[0][i].adjacent.push_back(&board1.board[1][i]);
        }
        if ((board1).board[1][i + 1].mine) {
            (board1).board[0][i].adjacent.push_back(&board1.board[1][i + 1]);
        }
        if ((board1).board[0][i - 1].mine) {
            (board1).board[0][i].adjacent.push_back(&board1.board[0][i - 1]);
        }
        if ((board1).board[0][i + 1].mine) {
            (board1).board[0][i].adjacent.push_back(&board1.board[0][i + 1]);
        }

    }
    //bottom
    for (int i = 1; i < 24; i++) {
        if ((board1).board[14][i - 1].mine) {
            (board1).board[15][i].adjacent.push_back(&board1.board[14][i - 1]);
        }
        if ((board1).board[14][i].mine) {
            (board1).board[15][i].adjacent.push_back(&board1.board[14][i]);
        }
        if ((board1).board[14][i + 1].mine) {
            (board1).board[15][i].adjacent.push_back(&board1.board[14][i + 1]);
        }
        if ((board1).board[15][i - 1].mine) {
            (board1).board[15][i].adjacent.push_back(&board1.board[15][i - 1]);
        }
        if ((board1).board[15][i + 1].mine) {
            (board1).board[15][i].adjacent.push_back(&board1.board[15][i + 1]);
        }
    }
    //left
    for (int i = 1; i < 15; i++) {
        if ((board1).board[i - 1][1].mine) {
            (board1).board[i][0].adjacent.push_back(&board1.board[i - 1][1]);
        }
        if ((board1).board[i][1].mine) {
            (board1).board[i][0].adjacent.push_back(&board1.board[i][1]);
        }
        if ((board1).board[i + 1][1].mine) {
            (board1).board[i][0].adjacent.push_back(&board1.board[i + 1][1]);
        }
        if ((board1).board[i - 1][0].mine) {
            (board1).board[i][0].adjacent.push_back(&board1.board[i - 1][0]);
        }
        if ((board1).board[i + 1][0].mine) {
            (board1).board[i][0].adjacent.push_back(&board1.board[i + 1][0]);
        }
    }
    //right
    for (int i = 1; i < 15; i++) {
        if ((board1).board[i - 1][23].mine) {
            (board1).board[i][24].adjacent.push_back(&board1.board[i - 1][23]);
        }
        if ((board1).board[i][23].mine) {
            (board1).board[i][24].adjacent.push_back(&board1.board[i][1]);
        }
        if ((board1).board[i + 1][23].mine) {
            (board1).board[i][24].adjacent.push_back(&board1.board[i + 1][1]);
        }
        if ((board1).board[i + 1][24].mine) {
            (board1).board[i][24].adjacent.push_back(&board1.board[i + 1][24]);
        }
        if ((board1).board[i - 1][24].mine) {
            (board1).board[i][24].adjacent.push_back(&board1.board[i - 1][24]);
        }
    }
    //populating rest
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 24; j++) {

            //top left
            if ((board1).board[i - 1][j - 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i - 1][j - 1]);
            //top
            if ((board1).board[i - 1][j].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i - 1][j]);
            //top right
            if ((board1).board[i - 1][j + 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i - 1][j + 1]);
            //left
            if ((board1).board[i][j - 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i][j - 1]);
            //right
            if ((board1).board[i][j + 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i][j + 1]);
            //bottom left
            if ((board1).board[i + 1][j - 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i - 1][j]);
            //bottom
            if ((board1).board[i + 1][j].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i + 1][j]);
            //bottom right
            if ((board1).board[i + 1][j + 1].mine)
                (board1).board[i][j].adjacent.push_back(&board1.board[i + 1][j + 1]);



        }
    }

}

//generating new random boaard

Board* randomMines(Board* board1) {
   
   

   
    
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            (*board1).board[i][j].tile.setTexture(TextureManager::getTexture("tile_hidden"));
            (*board1).board[i][j].topper.setTexture(TextureManager::getTexture("tile_hidden"));
            (*board1).board[i][j].mine = false;
            (*board1).board[i][j].adjacent.resize(0);
            (*board1).board[i][j].revealed = false;
        }
    }
    (*board1).debugFlag = false;
    

    int xpos = 0;
    int ypos = 0;
    for (int i = 0; i < 16; i++) {

        for (int j = 0; j < 25; j++) {
            (*board1).board[i][j].tile.setPosition(xpos, ypos);
            (*board1).board[i][j].topper.setPosition(xpos, ypos);
            xpos = xpos + 32;
        }
        xpos = 0;
        ypos = ypos + 32;
    }
    //buttons

    (*board1).face.setTexture(TextureManager::getTexture("face_happy"));
    (*board1).face.setPosition(368, 512);
    (*board1).debug.setTexture(TextureManager::getTexture("debug"));
    (*board1).debug.setPosition(496, 512);
    (*board1).test1.setTexture(TextureManager::getTexture("test_1"));
    (*board1).test1.setPosition(560, 512);
    (*board1).test2.setTexture(TextureManager::getTexture("test_2"));
    (*board1).test2.setPosition(624, 512);
    (*board1).test3.setTexture(TextureManager::getTexture("test_3"));
    (*board1).test3.setPosition(688, 512);
    int mineCount = 0;
    int x;
    int y;
    srand(time(0));
    while (mineCount < 50) {
        x = (rand()% 16);
        y = rand()% 25;
        if (!(*board1).board[x][y].mine) {
            (*board1).board[x][y].mine = true;
            mineCount++;
        }
    }
    populate(*board1);
  

    return board1;
}

//turn toppers into bombs tiles into revealed
Board* gameOver(Board* board) {
    
    
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if ((*board).board[i][j].mine) {
                (*board).face.setTexture(TextureManager::getTexture("face_lose"));
                (*board).board[i][j].tile.setTexture(TextureManager::getTexture("tile_revealed"));
                (*board).board[i][j].topper.setTexture(TextureManager::getTexture("mine"));
                (*board).board[i][j].topper.setPosition((*board).board[i][j].tile.getPosition());
            }
        }
    }
    return board;
}
//load test 1-3
Board* loadTest(string fileName, Board* board) {
    ifstream file1(fileName);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            (*board).board[i][j].mine = false;
            (*board).board[i][j].flag = false;
            (*board).board[i][j].revealed = false;
        }
    }
    char data = 'a' ;
    
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 26; j++) {
            file1.read((char*)&data, 1);
            
            if (data != '\n') {
                if (data == '1') {
                    (*board).board[i][j].mine = true;
                }
                else {
                    (*board).board[i][j].mine = false;
                }
               
            }
            
        }
    }
    populate(*board);

 
    return board;
}

string rightNumber(Tile tile1) {
    if (tile1.adjacent.size() == 0) {
        //reveal function
        tile1.tile.setTexture(TextureManager::getTexture("tile_revealed"));
        tile1.topper.setTexture(TextureManager::getTexture("tile_revealed"));

    }
    for (int i = 1; i < 9; i++) {
        if (tile1.adjacent.size() == i) {
            return "number_" + to_string(i);
        }
       
    }
   
    return "tile_revealed";
}

