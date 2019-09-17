# capablanca [![Build Status](https://travis-ci.com/Ozzyz/capablanca.svg?branch=master)](https://travis-ci.com/Ozzyz/capablanca)
An attempt to create a simple chess engine in c++.

## Why?
I am a fan of chess and programming, and this project is a perfect mix between the two. 

## TODO:
- Implement opening book and endgame books
- Create lichess bot


## In progress
- [ ] UCI-conformity (http://wbec-ridderkerk.nl/html/UCIProtocol.html)
- [ ] Complete evaluation function
- [ ] Implement Zobrist hashing and lookups
- [ ] Increase test coverage to include evaluation function and search, and verify Zobrist hashing
- [x] Fen parsing
- [x] Move generation
- [x] negamax implementation with alfa-beta pruning

## Tests
Currently there is a limited number of unit tests implemented in this project. They cover features such as move generation, castling rights, en passant, parsing of FEN strings and more. The test library used is Googletest, which is automatically downloaded by CMake.
