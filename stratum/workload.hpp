#ifndef WORKLOAD_HPP
#define WORKLOAD_HPP
#include <stdint.h>
#include <iostream>
#include "inc/strata_types"
#include <strata/backend/impl.hpp>
#include <strata/sgui/sgui_widgets.hpp>
#include <cstddef>
#include <string>
#include <vector>
#include <strata/workload.hpp>
#include <strata/modules.hpp>
#include <tuple>
// From this file plugins can add app contribution;
// Each of these classes have their own scope


void getEntity();
void getEntityByName();


class nodeIndex {
    auto t ;  
    void size();
    template <size_t pos, typename Node>
    void regNode()
    template<size_t pos>
    void get(){
        this->t get ;
    };
    
    auto getNode(uint nodeInd ){

    } ;
    
    template<size_t pos>auto get_vert();
    template<size_t pos>auto get_frag();
    template<size_t pos>auto get_geom();
    template<size_t pos>auto get_tesc();
    template<size_t pos>auto get_tese();
    template<size_t pos>auto get_comp();
    template<size_t pos>auto get_task();
    template<size_t pos>auto get_mesh();
    template<size_t pos>auto get_rgen();
    template<size_t pos>auto get_rint();
    template<size_t pos>auto get_rahit();
    template<size_t pos>auto get_rchit();
    template<size_t pos>auto get_rmiss();
    template<size_t pos>auto get_rcall();
    
    auto all_vert();
    auto all_frag();
    auto all_geom();
    auto all_tesc();
    auto all_tese();
    auto all_comp();
    auto all_task();
    auto all_mesh();
    auto all_rgen();
    auto all_rint();
    auto all_rahit();
    auto all_rchit();
    auto all_rmiss();
    auto all_rcall();
    
    static const init(){

    };

};

// TODO TimeLine node (animation, audio and video)
class widgetIndex {


};


class contrib [
    std::string name ;
    widget w; 
    virtual void func();
];

class topbarContrib : contrib {
    public:
     
};
class taskbarContrib{
    public:


};

class sidebarContrib{ // Sidebar with modes and status
    public:
    sideBarTab* sideBarTab;
    left ;
    right ;
};

class sideBarTab {
    std::string name ;
    imicon icon ;    
    std::vector<uint> nodeIndex; 

};

class widgetContrib{
    public:
    
};
class viewContrib{
    public: 

};
class nodeContrib{
    public:
    
    bool exec ;
    std::tuple<variable> modIn ;
    std::tuple<variable> eventIn ; 
    std::tuple<variable> resorceIn ; 
    std::tuple<variable> modOut  ;
    std::tuple<variable> eventOut  ;
    std::tuple<variable> resorceOut  ; 

    std::string expression ;

};
class workload {
    std::vector<topbarContrib> topbars  ;
    std::vector<taskbarContrib> taskbars  ;
    std::vector<sidebarContrib> sidebars  ;
    std::vector<sideBarTab> sidebartab;
    std::vector<widgetContrib> widgets  ;
    std::vector<viewContrib> views;
    std::vector<nodeContrib> nodes ;   

    std::vector<pos_t> sideBarTabIndex;
    
     
    void addTopBarContrib(topbarContrib cb);
    void addTaskbar(taskbarContrib cb);
    void addsideBarTab(taskbarContrib cb);
    void addSidebar(sidebarContrib cb);
    void addView(viewContrib vc);

    virtual void update();
    virtual void resolveAction();
    virtual void stateupdate();
    virtual void undo();
    virtual void redo();
    virtual void nowdo();


    workload(); 

}; // Workloads 
#define HISTORY_SIZE 100;
#define HISTORY_MIN 40;
template <typename action>
struct state {
    std::vector<action> s;
    virtual void optim();
     state<action> operator<<(action& a){
        this->s.push_back(a);
    };
    void operator<<(state<action>& a)final{
      *this<<a; 
    };
    virtual void operator>>(action& a);
    void operator>>(state<action>& a) final {
        *this>> a;
    };
    state(action as){this->s=new std::vector<action>{as};};
};
template<typename instr>
struct actionBase {
    instr data;
    uint ty;
        bool operator!=(action<instr>& lhs , action<instr>& rhs) final{
            return (lhs.ty != rhs.ty);
        };
         bool operator==(action<instr>& lhs , action<instr>& rhs)final {
            return (lhs.ty ==rhs.ty); 
         };
         virtual bool operator<=(action& lhs , action& rhs);
        virtual void operator+(actionBase<instr>& lhs,actionBase<instr>& rhs){};
};
template <typename action,size_t size>
class histvec {
    action data[size];
    uint startpt;
    uint endpt;
    uint laststart;
    uint lastend;

    state<action> sysstate;
    void update(){// Get all actions up to point and updates;
        this->laststart = this->startpt;
        this->lastend=this->endpt;
    };
    std::vector<action> get(){
        state<action> s;
        s.push_back(this->data[this->startpt]);
        for(int i =this->startpt+1; i<this->endpt;i++ ){
            s.begin()<<this->data[i];
        };
    };
    void updateState(std::vector<action>& s){
        this->get()
    };  
    state get(){
       state vec  ;
    };


    void undo(){this->point--;};
    void redo(){this->point++;};
    void nowdo(action act){
        this->point++;
        if(this->point>size){

        };
        this->data[this->point]=act;
    };
};

struct selectContext {

};

template <typename tool>
struct action {
    tool::option
};
struct tool {
    image icon ;
    using ty = defT ; 
    struct action ;
    virtual void exec( selectContext* selection ,action act  );
};  
struct move {
    image icon = ;
};


class node_wl : public workload {
//"T is time(task) , G is geom, V is vertex , F is frag , E is tessel, R is ray , eg TGVFERhumanInverseKinematic \n  Press \033[1m any \033[0m to close \n Press \033[1m Delete  \033[0m to never see this again "
    enum type {
            erase,
            copy,
            cut,
            paste,
            move,
            connect,
            // edit,
    };
    
    typedef union {
        uint copy;
        uint cut ;
        glm::vec2 move;
        snode::edit edit;
         
    }instr ; 
    struct action : actionBase<instr> {
        instr data;
        uint ty;
        void operator<=()
    };
    std::vector<nodeEditor> nodeEditors ;
    
    selectContext selection; 
};
node_wl node_worker;
void contributeNode(uint nodety,  node s);

class widgetux_wl : workload {
    typedef struct {
        std::vector<uint > groups; 
    }selection ;
    typedef union {
        pos_t add;
        pos_t erase ;
        pos_t copy; 
        glm::vec2 cut;
        glm::vec2 paste;
        glm::vec2 move;
        glm::vec2 resize;
        float rotate;
    }instr;
     struct action {
        enum type {
            add,
            erase,
            copy,
            cut,
            paste,
            rotate,
            resize,
            resizeW,
            resizeN,
            resizeE,
            resizeS,
            resizeNW,
            resizeNE,
            resizeSE,
            resizeSW,            
            move,
            selection
        };
        instr data;
        uint ty;
        

        virtual bool operator<=(){
            switch()
        };
        virtual bool operator>=();
        virtual bool operator<();
        virtual bool operator>();

    };
    canvas base ; // Base location
    canvas current;
    std::array<action,HISTORY_SIZE> history;
    uint historyPt;
    void nowdo(action a){
        if(this->historypt>HISTROY_SIZE){
            uint hispt = this->historypt;
            this->base.update(this->history,HISTORY_MIN) ;
            
        };
        this->historypt++;
        this->history[this->historypt]= a ;};
};


class modelling : workload { // Includes: animation ,destruction, physics
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
    enum ptType {
        vertex,
        
    };

   typedef union  {
        glm::vec3 move;
        glm::vec3 rotate;
        glm::vec2 lineSet;        
        glm::vec3 angleSet;

        typedef struct  {
            uint16_t size ;
            glm::vec2* paintPath;
        } paint ;
        float extrude;
        float fillet;
        uint16_t index; 
        float extend;
    }instr;
    typedef struct {
        enum type {
            //Start  * These take primitives as well :
            addPt,
            addSurface,
            addShape,
            erasePt,
            eraseSurface,
            eraseShape,
            coptPt,
            copyeSurface,
            copyeShape,
            cutPt,
            cutSurface,
            cutShape,
            pastePt,
            pasteSurface,
            pasteShape,
            rotate,
            // End
            lineSet,
            angleSet,
            resize,
            move,
            extrude,
            fillet,
            addpts,
            extend,
            paint, // For painting Modelling action
            select
        };
        
        uint8_t ty ;
        instr data;
        selection s;
    }action;

    std::array<action,HISOTRY_SIZE> history; 


    uint historypoint;
    void resolveAction(action act );

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
struct terrain_wl : workload { // Includes foliage, waters, destruction, physics
    typedef struct {
        enum type {
            addPoint, 
            ad
        };
    }action;
};
struct image_wl : workload { // Include animation ,

};
struct video_wl : workload { // 

};
struct scene_wl : workload { // This is for light, camera(with effects) and actor management 

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


class plwl {// Plugin Workload ;

};  

class worklaodMan {
    std::tuple<node_wl,widgetux_wl,modelling,terrain_wl,scene_wl,image_wl,video_wl> workloads;
    std::vector<uint16_t> enables ; 
    std::vector<plwl> plugins ;

    void addWorkload(plwl* work_load) [this->plugins.push_back(work_load);];
};


workloadMan wlm;

void addWorkload(plwl work_load){wlm.addWorkload(work_load);};



#endif