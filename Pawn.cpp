#include "Pawn.h"

namespace Chess
{
    bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
        if (start.first == end.first && start.second == end.second) {
            return false;
        }
        if(Pawn::is_white()){
            if(start.second == '2'){
                if((end.second - start.second == 2 || end.second - start.second == 1) && start.first == end.first){
                    return true;
                }
            } else {
                if(end.second - start.second == 1 && start.first == end.first){
                    return true;
                }
            }
            return false;
        }else {
            if(start.second == '7'){
                if((start.second - end.second == 2 || start.second - end.second == 1) && start.first == end.first){
                    return true;
                }
            } else {
                if(start.second - end.second == 1 && start.first == end.first){
                    return true;
                }
            }
            return false;
        }   
    } 
    bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
        if (start.first == end.first && start.second == end.second) {
            return false;
        }
        if(Pawn::is_white()){
            if(end.second - start.second == 1 && abs(end.first - start.first) == 1){
                return true;
            }
            return false;
        }else {
            if(start.second - end.second == 1 && abs(end.first - start.first) == 1){
                return true;
            }
            return false;
        }  
    }
}