#include "fen.h"
#include <sstream>
#include <stdexcept>


FEN::FEN(const std::string& fen) {
    // initialize variables
    std::string _piecePlacement;
    std::string _sideToMove;
    std::string _castlingAvailability;
    std::string _enPassantTargetSquare;
    std::string _halfMoveClock;
    std::string _fullMoveCounter;

    // split the FEN string
    std::stringstream ss(fen);
    ss >> _piecePlacement;
    ss >> _sideToMove;
    ss >> _castlingAvailability;
    ss >> _enPassantTargetSquare;
    ss >> _halfMoveClock;
    ss >> _fullMoveCounter;

    // convert to the correct types
    piecePlacement = _piecePlacement;
    sideToMove = (_sideToMove == "w");
    castlingAvailability = _castlingAvailability;
    enPassantTargetSquare = _enPassantTargetSquare;
    halfMoveClock = std::stoi(_halfMoveClock);
    fullMoveCounter = std::stoi(_fullMoveCounter);
}


Matrix FEN::toMatrix() {
    Matrix matrix;
    char file = 'a';
    int rank = 8;

    for (char c : piecePlacement) {
        if (isalpha(c)) {
            matrix[std::string(1, file) + std::to_string(rank)] = static_cast<PieceLetter>(c);
        } else if (isdigit(c)) {
            file += c - '0'; // increment file by the number of empty squares
        } else if (c == '/') {
            rank--;
            file = 'a';
        }
        if (!isdigit(c) && c != '/') {
            file++;
        }
    }

    return matrix;
}
