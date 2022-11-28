#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    if (abs(start.first - end.first) == abs(start.second - end.second)) {
        return true;
    }
    return false;
  }
}
