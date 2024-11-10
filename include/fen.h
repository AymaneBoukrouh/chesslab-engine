#ifndef FEN_H
#define FEN_H

#include <string>
#include <unordered_map>

typedef std::string Notation;

enum PieceLetter {
    P = 'P', p = 'p',
    N = 'N', n = 'n',
    B = 'B', b = 'b',
    R = 'R', r = 'r',
    Q = 'Q', q = 'q',
    K = 'K', k = 'k'
};

typedef std::unordered_map<Notation, PieceLetter> Matrix;

struct FEN {
    std::string piecePlacement;
    bool sideToMove;
    std::string castlingAvailability;
    std::string enPassantTargetSquare;
    int halfMoveClock;
    int fullMoveCounter;

    FEN(const std::string& fen);
    Matrix toMatrix();
};

#endif
