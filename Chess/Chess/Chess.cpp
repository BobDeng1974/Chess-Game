//
//  Chess.cpp
//  Chess
//
//  Created by Ricardo Martins on 28/02/2017.
//  Copyright © 2017 Ricardo Martins. All rights reserved.
//

#include "Chess.hpp"

Chess::Chess(SDL_Renderer* renderer, CellTexture* cellTexture, int screenWidth, int screenHeight)
{
    this->renderer_ = renderer;
    this->cellTexture_ = cellTexture;
    
    // TODO review sizing
    
    int smallerSize = (screenHeight<screenWidth)? screenHeight: screenWidth;
    
    cellSize_ = smallerSize/9;
    
    cellTexture_->setDimensions(cellSize_, cellSize_);
    
    boardHeight_ = (cellSize_*horizontalCellNo);
    boardWidth_ = boardHeight_;
    
    createBoard();
    initiatePieces();
}

// Creates the board
void Chess::createBoard()
{
    for (int i=0; i<horizontalCellNo; i++){
        for (int j=0; j<verticalCellNo; j++){
            bool isDark = ((i%2==0 && j%2==0)||((i%2==1 && j%2==1)))? false:true;
            board_.push_back( Cell(renderer_, cellTexture_, (cellSize_/2 + (j*cellSize_)), cellSize_/2 + (i*cellSize_) , cellSize_, i, j, isDark ));
        }
    }
}

void Chess::initiatePieces(){
    //Set Opponents Pieces
    for (int i=0; i<horizontalCellNo; i++){
        if(i == 0 || i== horizontalCellNo-1)
            board_[i].setPiece( new Rook(false));
        else if( i==1 || i == horizontalCellNo-2)
            board_[i].setPiece( new Knight(false));
        else if( i==2 || i== horizontalCellNo-3)
            board_[i].setPiece( new Bishop(false));
        else if( i==3)
            board_[i].setPiece( new Queen(false));
        else
            board_[i].setPiece( new King(false));;
    }
    
    
    //Set Opponents pawns
    for (int i=0; i<horizontalCellNo-2; i++){
        board_[horizontalCellNo + i].setPiece( new Pawn(false));
    }
    
    board_[(2*horizontalCellNo) + 6].setPiece( new Pawn(false));
    
    board_[(3*horizontalCellNo) + 7].setPiece( new Pawn(false));
    Pawn* pawn = static_cast<Pawn*>(board_[(3*horizontalCellNo) + 7].getPiece());
    pawn->setDoubleJumpTurn(0);
    
    
    
    // Set players pieces
    int row = ((verticalCellNo-1)*horizontalCellNo);
    for (int i=0; i<horizontalCellNo; i++){
        if(i == 0 || i== horizontalCellNo-1)
            board_[row + i].setPiece( new Rook(true));
        else if( i==1 || i == horizontalCellNo-2)
            board_[row + i].setPiece( new Knight(true));
        else if( i==2 || i== horizontalCellNo-3)
            board_[row + i].setPiece( new Bishop(true));
        else if( i==3)
            board_[row + i].setPiece( new Queen(true));
        else
            board_[row + i].setPiece( new King(true));
    }
    row-=horizontalCellNo;
    //Set Players pawns
    for (int i=0; i<horizontalCellNo; i++){
        board_[row + i].setPiece( new Pawn(true));
    }
    
    verifier_.verifyBoardState(board_,1);
}

// Renders the board
void Chess::render()
{
    // Render each cell
    for (int i=0; i<horizontalCellNo; i++){
        for (int j=0; j<verticalCellNo; j++){
            board_[(i*horizontalCellNo) + j].render();
        }
    }
    
    if(focusedCell!=nullptr){
        cellTexture_->render(mousePosition.x - cellSize_/2, mousePosition.y- cellSize_/2 , focusedPiece_->getType());
    }
    
    SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xFF );
    
    //Render black outlined quad
    SDL_Rect outlineRect = { cellSize_/2, cellSize_/2, boardWidth_, boardHeight_ };
    SDL_RenderDrawRect( renderer_, &outlineRect );
 
}

Handler Chess::handleEvent(SDL_Event *e)
{
    // return Handler
    Handler handler(Handler::EVENT_IGNORE);
    
    // bool for valid piece movement
    bool updateConditions;
    
    //If mouse event happened
    if( e->type == SDL_MOUSEBUTTONDOWN)
    {
        int row=0, col=0;
        bool inside = false;
        for (int i=0; i<verticalCellNo; i++){
            for (int j=0; j<horizontalCellNo; j++){
                if( (inside= board_[ (i*horizontalCellNo)+j].handleEvent(e)) ){
                    row = i;
                    col = j;
                    i=horizontalCellNo;
                    j=horizontalCellNo;
                }
            }
        }
        
        //Mouse clicked inside cell
        if(inside){
            if( board_[(row*horizontalCellNo)+col].getPiece() != nullptr){ // && board_[(row*9)+col].getPiece()->isControlled() ){    @@ FOR DEBUG @@
                focusedCell = &board_[(row*horizontalCellNo)+col];
                focusedPiece_ = focusedCell->getPiece();
                focusedCell->setClicked(true);
                handler.setEvent(Handler::EVENT_INPUT);
                SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
                updatePossibleMoves();
            }
        }
    }
    else if( e->type == SDL_MOUSEMOTION && focusedCell!=nullptr){
        SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
        handler.setEvent(Handler::EVENT_INPUT);
    }
    else if( e->type == SDL_MOUSEBUTTONUP && focusedCell!=nullptr ) // input events, only affect focused cell
    {
        int row=0, col=0;
        bool inside = false;
        bool found = false;
        for (int i=0; i<verticalCellNo; i++){
            for (int j=0; j<horizontalCellNo; j++){
                if( !found && (inside= board_[ (i*horizontalCellNo)+j].handleEvent(e)) ){
                    row = i;
                    col = j;
                    found=true;
                }
                else{
                    board_[ (i*horizontalCellNo)+j].setLegalMove(false);
                }
            }
        }
        
     
        if( inside){
            if( !focusedPiece_->isControlled()){
                board_[(row*horizontalCellNo)+col].setPiece(focusedPiece_);
                board_[(row*horizontalCellNo)+col].setLegalMove(false);
                focusedCell->setPiece(nullptr);
                focusedPiece_->setMoved();
                logger(focusedCell->getPosition(), board_[(row*horizontalCellNo)+col].getPosition(), focusedPiece_->isControlled());
                
                if(verifier_.verifyBoardState(board_,1) == BoardVerifier::STATE_CHECKMATE)
                    concludeGame(false);

                
            }
            else if( board_[(row*horizontalCellNo)+col].isLegalMove()){
                
                if( focusedPiece_->getType() == CellTexture::PIECE_PAWN && board_[(row*horizontalCellNo)+col].getPiece()==nullptr && focusedCell->getPosition().x != col){
                    board_[((row+1)*horizontalCellNo)+col].deletePiece();
                }
                if (focusedPiece_->getType() == CellTexture::PIECE_KING && verifier_.isCastleMove((row*horizontalCellNo)+col)) {
                    Piece* rook;
                    if( ((row*horizontalCellNo)+col) == (horizontalCellNo*horizontalCellNo -2)){
                        // Right rook for castle
                        rook = board_[(horizontalCellNo*horizontalCellNo -1)].getPiece();
                        board_[(horizontalCellNo*horizontalCellNo -1)].setPiece(nullptr);
                        board_[(row*horizontalCellNo)+col-1].setPiece(rook);
                    }
                    else{
                        // Left rook for castle
                        rook = board_[(horizontalCellNo*(horizontalCellNo-1))].getPiece();
                        board_[(horizontalCellNo*(horizontalCellNo-1))].setPiece(nullptr);
                        board_[(horizontalCellNo*(horizontalCellNo-1)) + 3].setPiece(rook);
                    }
                }
                board_[(row*horizontalCellNo)+col].setPiece(focusedPiece_);
                board_[(row*horizontalCellNo)+col].setLegalMove(false);
                focusedCell->setPiece(nullptr);
                focusedPiece_->setMoved();
                logger(focusedCell->getPosition(), board_[(row*horizontalCellNo)+col].getPosition(), focusedPiece_->isControlled());
                
                if(verifier_.verifyBoardState(board_,1)  == BoardVerifier::STATE_CHECKMATE)
                    concludeGame(false);

            }
            if(focusedCell!=nullptr){
                focusedCell->setClicked(false);
                focusedCell = nullptr;
                focusedPiece_ =nullptr;
                handler.setEvent(Handler::EVENT_INPUT);
            }
        }
        else{
            if(focusedCell!=nullptr){
                focusedCell->setClicked(false);
                focusedCell = nullptr;
                focusedPiece_ =nullptr;
                handler.setEvent(Handler::EVENT_INPUT);
            }
        }
        
    }
    return handler;
}

void Chess::updatePossibleMoves()
{
    SDL_Point cellPoint = focusedCell->getPosition();
    int cellPos = horizontalCellNo*cellPoint.y + cellPoint.x;
    std::queue<int>pieceMoves = verifier_.getPieceMoves(cellPos);
    while( !pieceMoves.empty()){
        int index = pieceMoves.front();
        pieceMoves.pop();
        board_[index].setLegalMove(true);
    }
}


void Chess::logger(SDL_Point src, SDL_Point dest, bool isPlayer)
{
    std::cout << (isPlayer? "Player: ": "Opponent: ");
    std::cout << "(" << src.y << "," << src.x << ")";
    switch (focusedPiece_->getType()) {
        case CellTexture::PIECE_PAWN:
            std::cout << " Pawn to ";
            break;
        case CellTexture::PIECE_ROOK:
            std::cout << " Rook to ";
            break;
        case CellTexture::PIECE_KNIGHT:
            std::cout << " Knight to ";
            break;
        case CellTexture::PIECE_BISHOP:
            std::cout << " Bishop to ";
            break;
        case CellTexture::PIECE_QUEEN:
            std::cout << " Queen to ";
            break;
        case CellTexture::PIECE_KING:
            std::cout << " King to ";
            break;
        default:
            break;
    }
    std::cout << "(" << dest.y << "," << dest.x << ") \n";
}

void
Chess::concludeGame(bool wonGame)
{
    if(wonGame)
        std::cout << "You won the game\n";
    else
        std::cout << "You lost the game\n";
}

