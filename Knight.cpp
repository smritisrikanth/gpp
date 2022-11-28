#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    int num1 = abs(start.first - end.first);
    int num2 = abs(start.second - end.second);
    if ((num1 == 1 && num2 == 2) || (num1 == 2 && num2 == 1)) {
        return true;
    }
    return false;
  }
}