/// @file automata.cpp
/// @brief Class file for automata.h
/// @author Petra
/// @version 0.1
/// @date 2016-07-03

#include "automata.h"

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
			ant.direction = ANTI_CLOCKWISE_TURN(ant.direction);
			squares[npt] = Square_Colour::White;
		default:
			ant.direction = CLOCKWISE_TURN(ant.direction);
			squares[npt] = Square_Colour::Black;
	}
}
