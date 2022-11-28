#include "Rook.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    if (start.first == end.first && start.second == end.second) {
        return false;
    }
    if (start.first == end.first || start.second == end.second) {
        return true;
    }
    return false;
  }
}