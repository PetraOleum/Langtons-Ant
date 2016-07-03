/// @file automata.h
/// @brief Holds the Langton's Ant automata independent of the display
/// @author Petra
/// @version 1.0
/// @date 2016-07-03

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <cstdint>
#include <map>
#include <utility>

/// @brief A pair of ints
using point = std::pair<int, int>;

/// @brief Colour of a square (default: black)
enum class Square_Colour : uint8_t {
	/// @brief Black (0)
	Black = 0,
	/// @brief White (1)
	White = 1
};

/// @brief Cardinal directions, underlying = degrees as uint16_t. **unsigned**
enum class Direction : uint16_t {
	/// @brief 0 degrees
	Up = 0,
	/// @brief 90 degrees
	Right = 90,
	/// @brief 180 degrees
	Down = 180,
	/// @brief 270 degrees
	Left = 270
};

/// @brief Calculate direction change
///
/// @param dir Starting direction
///
/// @return Direction 90 degrees anti-clockwise
Direction antiClockwiseTurn(Direction dir);

/// @brief Calculate direction change
///
/// @param dir Starting direction
///
/// @return Direction 90 degrees clockwise
Direction clockwiseTurn(Direction dir);

/// @brief Holds the ant itself
struct LangtonAnt {
	/// @brief Direction it's facing
	Direction direction;
	/// @brief X-cordinate (signed)
	int x;
	/// @brief Y-coordinate (signed)
	int y;
};

/// @brief Holds the state of the automata
class LangtonAutomata {
	private:
		/// @brief Hold the ant
		LangtonAnt ant;

		/// @brief Hold the square as a map
		std::map<point, Square_Colour> squares;

		/// @brief How many turns have passed
		unsigned int turnNumber = 0;

	public:
		/// @brief Constructor
		LangtonAutomata() {
			ant = {Direction::Up, 0, 0};
//			ant.x = ant.y = 0;
//			ant.direction = Direction::Up;
		}

		/// @brief Destructor
		~LangtonAutomata() {

		}

		/// @brief Expose the ant
		///
		/// @return const reference to the ant
		inline const LangtonAnt& getAnt() const {
			return ant;
		}

		/// @brief Get the value of a square (from x, y)
		///
		/// @param x x-coord
		/// @param y y-coord
		///
		/// @return The colour (by value)
		inline Square_Colour getSquare(int x, int y) const {
			return getSquare(std::make_pair(x, y));
		}

		/// @brief Get the value of a square (from a point)
		///
		/// @param pt The point
		///
		/// @return The colour (by value)
		inline Square_Colour getSquare(const point& pt) const {
			auto it = squares.find(pt);
			if (it != squares.end())
				return it->second;
			else 
				return Square_Colour::Black;
		}

		/// @brief Expose the turn number
		///
		/// @return The turn number (by value)
		inline unsigned int getTurnNumber() const {
			return turnNumber;
		}

		/// @brief Advance one turn
		void Advance();

};

#endif
