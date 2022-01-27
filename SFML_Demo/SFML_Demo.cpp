#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);
   
    
  
    
   
   
    //loading board
    Board* board1 = new Board;
    board1 = randomMines(board1);
    
   
    
   
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                //left click
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 25; j++) {
                            if ((*board1).board[i][j].tile.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)&& !board1->board[i][j].mine) {
                                if (board1->board[i][j].adjacent.size() == 0) {
                                    emptyTile(*board1, tileCoords(sf::Mouse::getPosition(window), *board1));
                                }
                                else {
                                    (*board1).board[i][j].tile.setTexture(TextureManager::getTexture("tile_revealed"));
                                    (*board1).board[i][j].topper.setTexture(TextureManager::getTexture(rightNumber((*board1).board[i][j])));
                                    (*board1).board[i][j].revealed = true;
                                }
                            }
                            //game over
                            else if ((*board1).board[i][j].tile.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && board1->board[i][j].mine) {
                                board1 = gameOver(board1);


                                }

                            }

                        }


                        if ((*board1).face.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                            board1 = randomMines(board1);
                            
                        }
                        else if ((*board1).debug.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                            
                           
                                    if ( !(*board1).debugFlag) {
                                        
                                        for (int x = 0; x < 16; x++) {
                                            for (int y = 0; y < 25; y++) {
                                                if ((*board1).board[x][y].mine) {
                                                    (*board1).board[x][y].tile.setTexture(TextureManager::getTexture("tile_revealed"));
                                                    (*board1).board[x][y].topper.setTexture(TextureManager::getTexture("mine"));
                                                    (*board1).debugFlag = true;
                                                }
                                            }
                                        }
                                    }
                                    else {
                                        
                                        for (int x = 0; x < 16; x++) {
                                            for (int y = 0; y < 25; y++) {
                                                if ((*board1).board[x][y].mine) {
                                                    (*board1).board[x][y].tile.setTexture(TextureManager::getTexture("tile_hidden"));
                                                    (*board1).board[x][y].topper.setTexture(TextureManager::getTexture("tile_hidden"));
                                                    (*board1).debugFlag = false;
                                                }
                                            }
                                        }
                                    }
                                
                            
                        }
                        else if ((*board1).test1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                            
                            board1 = loadTest("boards/testboard1.brd", board1);
                        }
                        else if ((*board1).test2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                            board1 = loadTest("boards/testboard2.brd", board1);
                        }
                        else if ((*board1).test3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                            board1 = loadTest("boards/testboard3.brd", board1);
                        }
                           
                    }
                    //right click
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        for (int i = 0; i < 16; i++) {
                            for (int j = 0; j < 25; j++) {
                                if ((*board1).board[i][j].tile.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
                                    && !(*board1).board[i][j].revealed && !(*board1).board[i][j].flag) {

                                    (*board1).board[i][j].topper.setTexture(TextureManager::getTexture("flag"));
                                    (*board1).board[i][j].flag = true;
                                    (*board1).board[i][j].topper.setPosition((*board1).board[i][j].tile.getPosition());
                                }
                                else if ((*board1).board[i][j].tile.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
                                    && !(*board1).board[i][j].revealed && (*board1).board[i][j].flag) {

                                    (*board1).board[i][j].topper.setTexture(TextureManager::getTexture("tile_hidden"));
                                    (*board1).board[i][j].flag = false;
                                    (*board1).board[i][j].topper.setPosition((*board1).board[i][j].tile.getPosition());
                                }
                            }
                        }

                    }
                }
            }

            window.clear();
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {

                    window.draw((*board1).board[i][j].tile);
                    window.draw((*board1).board[i][j].topper);
                    window.draw((*board1).face);
                    window.draw((*board1).debug);
                    window.draw((*board1).test1);
                    window.draw((*board1).test2);
                    window.draw((*board1).test3);
                }
            }

            window.display();
        }
    
    
    delete board1;
    return 0;
}
