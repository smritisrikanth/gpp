#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    if (abs(start.first-end.first) <= 1 && abs(start.second-end.second) <= 1) {
        return true;
    }
    return false;
  }
}