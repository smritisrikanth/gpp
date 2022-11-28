#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    //for vertical and horizonatal
    if (start.first == end.first || start.second == end.second) {
        return true;
    }
    // for diagonal 
    if (abs(start.first - end.first) == abs(start.second - end.second)) {
        return true;
    }
    return false;
  }
}
