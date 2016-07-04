/// @file automata.cpp
/// @brief Class file for automata.h
/// @author Petra
/// @version 1.0
/// @date 2016-07-03

#include "automata.h"
#include <cstdio>

Direction antiClockwiseTurn(Direction dir) {
	switch (dir) {
		case Direction::Up:
			return Direction::Left;
			break;
		case Direction::Left:
			return Direction::Down;
			break;
		case Direction::Down:
			return Direction::Right;
			break;
		case Direction::Right:
			return Direction::Up;
			break;
		default:
			fprintf(stderr, "WTF. dir = %d\n", (int)dir);
			return Direction::Up;
			break;
	}
}

Direction clockwiseTurn(Direction dir) {
	switch (dir) {
		case Direction::Up:
			return Direction::Right;
			break;
		case Direction::Right:
			return Direction::Down;
			break;
		case Direction::Down:
			return Direction::Left;
			break;
		case Direction::Left:
			return Direction::Up;
			break;
		default:
			fprintf(stderr, "WTF. dir = %d\n", (int)dir);
			return Direction::Up;
			break;
	}
}

void LangtonAutomata::Advance() {
	switch (ant.direction) {
		case Direction::Up:
			ant.y++;
			break;
		case Direction::Right:
			ant.x++;
			break;
		case Direction::Down:
			ant.y--;
			break;
		case Direction::Left:
			ant.x--;
			break;
	}
	point npt = std::make_pair(ant.x, ant.y);
	Square_Colour ncol = getSquare(npt);
	switch (ncol) {
		case Square_Colour::Black:
			ant.direction = antiClockwiseTurn(ant.direction);
			squares[npt] = Square_Colour::White;
			break;
		default:
			ant.direction = clockwiseTurn(ant.direction);
			squares[npt] = Square_Colour::Black;
			break;
	}
	turnNumber++;
}

void LangtonAutomata::Reverse() {
	point opt = std::make_pair(ant.x, ant.y);
	Square_Colour ocol = getSquare(opt);
	switch (ocol) {
		case Square_Colour::White:
			squares[opt] = Square_Colour::Black;
			ant.direction = clockwiseTurn(ant.direction);
			break;
		default:
			squares[opt] = Square_Colour::White;
			ant.direction = antiClockwiseTurn(ant.direction);
			break;
	}
	switch (ant.direction) {
		case Direction::Up:
			ant.y--;
			break;
		case Direction::Right:
			ant.x--;
			break;
		case Direction::Down:
			ant.y++;
			break;
		case Direction::Left:
			ant.x++;
			break;

	}
	turnNumber--;
}
