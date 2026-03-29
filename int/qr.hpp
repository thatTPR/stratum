#include "ansi.hpp"
#include <ostream>
#include <cstddef>


class qrCode {
    enum size {
        _21,
        _25,
        _29
    };
    size_t s ;
    bool** qr ;
    friend ostream operator<<(ostream& os , const qrCode qr){
        os<<bg(BG_WHITE) ;
        os<<fg(FG_WHITE) ;
        for(int i = 0 ; i < this->s  ; i++){
            for(int j= 0 ; j < this->s ; j++ ){
                if(qr[i][j]){
                    os<< 
                } ;
            };
                
        };
    };
};