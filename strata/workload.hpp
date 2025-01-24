#ifndef WORKLOAD_HPP
#define WORKLOAD_HPP
#include "inc/strata_types"
#include <iostream>
#include <strata/backend/impl.hpp>
#include <strata/sgui/sgui_widgets.hpp>
#include <cstddef>
#include <string>
#include <vector>
#include <strata/workload.hpp>

#include <stdint.h>

// From this file plugins can add app contribution;
// Each of these classes have their own scope

class contrib [
    std::vector<std::string> ;
    editor_widget w; 
];

class topbar_contrib{
    public:
    std::vector<> ; 
};
class taskbar_contrib{
    public:
    
};
class sidebar_contrib{
    public:
    left ;
    right ;
};
class widget_contrib{
    public:
    
};
class viewContrib{
    public:
    
};

class node_editor_contrib{
"T is time(task) , G is geom, V is vertex , F is frag , E is tessel, R is ray , pseudo eg TGVFERhumanInverseKinematic \n  Press \033[1m any \033[0m to close \n Press \033[1m Delete  \033[0m to never see this again "

};
class canvas_editor_contrib{

};
class video_editor_contrib{

};
class modelling_editor_contrib {

};

class workload {
    topbar_contrib topbar  ;
    taskbar_contrib taskbar  ;
    sidebar_contrib sidebar  ;
    widget_contrib widget  ;

    node_contrib node ;   

    virtual void undo();
    virtual void redo();


    workload(); 

}; // Workloads 
#define HISTROY_SIZE 100;
class modelling : workload {
    //  commands ;
    typedef struct selection {
        std::vector<uint > groups; 
    };
    typedef struct  {
        std::vector<uint> models;
        std::vector<uint> points; 
    }selectionPoints;
    typedef struct  {
        std::vector<uint> models;
        std::vector<uint> points; 
        std::vector<uint> starts;    
    }selectionSurufaces;
    typedef struct {
        std::vector<uint> pointgroups ; 
    }selectionPointGruops;
    typedef struct {
        std::vector<uint> pointgroups;    
    }selectionEntity;

    union selection {
        selection select;
        selectionPoints points;
        selectionSurfaces Surfaces ;
        selectionPointGroups PointGroups;
    };
    union instr {
        bool add;
        bool delete;
        glm::vec3 move;
        glm::vec3 rotate;
        float extrude;
        float chamfer;
        float fillet;
        int addpts; 
        float extend;
    };
    typedef struct action {
        enum type {
            add,
            delete,
            move,
            rotate,
            extrude,
            chamfer,
            fillet,
            addpts,
            extend,

        };
        
        uint8_t ty ;
        instr data;
        selection s;



        
    }action;

    std::array<action >


    uint historypoint;
    void Add();
    void del();
    
    void redoAction(uint16_t histpt){

    }; 
    void unDoAction(uint16_t histpt){

    };
    void undo();
    void redo();



    void selectGroupBy();
    void selectAllEntitiesWithAttributesBy();
    void selectEntityBy();

    void selectGroupByName();
    void selectAllEntitiesWithAttributesByName();
    void selectEntityByName(std::string name);

    // View commands 
    void ViewTriangleEnable();
    void ViewBonesToggle();
    void ViewHitBoxToggle();
    // 
    
};
    class command {
        public:
        struct schema {
            enum type {
                Class =0 , 
                Num=1 ,
                str=2 ,
                    
            };
        };  
        std::string name;

        static const std::string group ;
        std::vector<std::string> args ;
        void (*command)(std::string args)   ;
    typedef std::string posstr ; // FIrs char is pos; 
        virtual std::vector<posstr> arglist(std::string s){
            std::vector<index> res; int i =0;
            for(std::string arg : this->args){
                pos_t s = arg.find_str(s) ;
                if(s!=npos ){
                res.push_back(i);i++;
                };
            };
        } ;
        virtual void exec(std::string arg);
        
    };
    class wl_commsys {
        std::vector<command> commands;

    };
    struct comstr : public widget { 
        std::string path;
        std::string strbuf;
        unsigned int scroll;
        void clear(){this->strbuf.clear();};
        void operator<<(std::string s){this->strbuf+=s;};

    };
  
    class wingroup : command{
        public:
        static const std::string group = "window"; 
    };
    class reloadWindow : groupcom{
        std::string name = "reload" ;
        void exec(std::string s){
            gr.reload();
            canvas.reload();
        };
        
    };
    std::string parse_arg(std::string& s , pos_t p){

    };
    class workload_com : command { // Add Enable Disable
        static const group = "workload";  
        void enable();
        void disable();
        void add();  
        command::posstr arglist(std::string arg){
            pos_t s = arg.find("enable")
            if(s != std::string::npos ){
                std::string
                this->enable() 
            }
        };
        
    };
      
    struct pallette {
      std::vector<command> commands;
      std::vector<workload> workloads ; 
        void exec();
        void _init(){
            reloadWindow relwin ;
            this->commands.push_back(relwin);
        };
        
        void init(std::vector<workload*>){
            this->_init();
        };

    };
};

#endif