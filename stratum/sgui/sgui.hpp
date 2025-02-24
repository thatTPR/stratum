#pragma once
#include <strata/backend/impl.hpp>
#include <map>
#include <vector>
#include <glm/vec4.hpp>
using namespace std; 

#include <strata/sgui.hpp>
// TODO figure out correct usage
class canvasob : widget_base{
    bool has  
    std::vector<widget*> childs ; 

};

class canvas : public widget_base { // Uses SYS form backend to make dockign
        public:
        std::vector<canvasob> canvob; // Bound to wins accesses SYS
        uint get_pos_from_widget(widget* w){
            for(uint i = 0 ; i < this->mat.size(); i++){
                if(w==(*(this->mat[0]))[0]){
                    return i;
                };
            };
        };
        void _add_widget(uint paren_pos ,widget* w){
            this->mat[0]->push(w);
        };
        void _insert_widget(uint paren_pos,uint pos, widget* w){
            this->mat[paren_pos]->insert(pos,w);
        };

        struct ext {
            glm::ivec4 bg_col;
            glm::ivec4 fg_col;
        } ext ;
        SGUI_DECL void begin(widget* w){
            this->last_opened = w; 
        };
        SGUI_DECL void end(widget* w){
            this->opened =  this->last_opened;
        };
        void setFont(font f);
        canvas(font f, uint x, uint y, uint width , uint height){
            this->f = f; this->d.coord[0] =x; this->d.coord[1] = y; this->d.coord[2] = x+width;this->d.coord[3] = y+height ;
            this->d.wh_size[0] = width; this->d.wh_size[1] = height;
        };
        canvas(font f,uint x, uint y, uint xsec,uint ysec){
            this=new canvas(f,x,y,xsec-x,ysec-y);
        };
    canvas(font f, uint x, uint y, uint xs , uint ys){
        this->f = f; this->c[0]=x;this->c[1]=y;this->c[2]=xs;this->c[3]=ys;
        c_cur = this;
    };
    };
    #ifndef CANVAS_LIMIT
    #define CANVAS_LIMIT 10
    #endif
    canvas* canvas_arr[CANVAS_LIMIT];
    int c_cur=0;
    widget* w_cur;
    int add_canvas(canvas* c){cavas_arr[c_cur+1] = c; c_cur++; w_cur = c;};


canvas canv; 