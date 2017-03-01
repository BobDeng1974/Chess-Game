//
//  Chess.hpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#ifndef Chess_hpp
#define Chess_hpp

#include <vector>

#include "Cell.hpp"
#include "CellTexture.hpp"
#include "Handler.hpp"

#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

class Chess
{
    public:
        Chess(SDL_Renderer* renderer, CellTexture* font,  int screenWidth, int screenHeight);

        // Handle event on sudoku board
        virtual Handler handleEvent( SDL_Event* e );
        
        // Renders the board
        virtual void render();
        
        // Reset board
        //virtual void reset(bool eraseAll);
    
    protected:
        virtual void updatePossibleMoves();

    
    private:
        // Board thick line size
        static const int thickLineSize=4;
        
        // Sudoku Screen Position
        int xOffset_;
        int yOffset_;
        int boardWidth_;
        int boardHeight_;
        int cellSize_;

        // SDL variables
        SDL_Renderer* renderer_ = nullptr;
        CellTexture* cellTexture_ = nullptr;
        
        // Number of Cells per line
        const static int horizontalCellNo = 8;
        const static int verticalCellNo = 8;

        // Pointer to clicked cell
        Cell *focusedCell = nullptr;
        Piece* focusedPiece_ = nullptr;
        SDL_Point mousePosition;
    
        std::vector<Cell> board_;
    
    
    
        // Creates the board (all cells)
        void createBoard();
        // Puts pieces onto the board (initial state)
        void initiatePieces();
    
        void logger( SDL_Point src, SDL_Point dest, bool isPlayer );
        void rookValidMoves(int row, int col);
        void knightValidMoves(int row, int col);
        void bishopValidMoves(int row, int col);


};

#endif /* Chess_hpp */
