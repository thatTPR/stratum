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
#include <petri/reflect.hpp>
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


class workload : public clss_refl{
    public:
    std::vector<topbarContrib> topbars  ;
    std::vector<taskbarContrib> taskbars  ;
    std::vector<sidebarContrib> sidebars  ;
    std::vector<sideBarTab> sidebartab;
    std::vector<widgetContrib> widgets  ;
    std::vector<viewContrib> views;
    std::vector<nodeContrib> nodes ;   

    std::vector<pos_t> sideBarTabIndex;
    template <typename T>
    void addFuncAction(std::string type,std::string name,T fptr){
        this->reflsys.add<T>(type,name,fp) ;
    };  
    auto getByName(std::string name){
        for(const auto& it : *this){
            if(it.name == name){return it.ptr;};
        };
        return NULL ;
    };

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
            compose,
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




    std::vector<snode::nodeCanvas> canvases ;
    uint active ;

    typedef void (*act)(glm::dvec4);
    typedef void (*pointact)(glm::dvec2) ; 
    typedef void (*baseact)(snode::nodeCanvas::selection) ;

    void erase(snode::nodeCanvas::selection){
        this->canvases[this->active].erase();
    };
    addFuncAction<baseact>("void (*pointact)(glm::dvec2)" , "erase", &erase);

    
    selectContext selection; 
};
node_wl node_worker;
void contributeNode(uint nodety,  node s);



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
struct image_wl : public workload { // Include animation ,

    std::vector<image_canvas> ;
    uint activeCanavas ;

    typedef void(*addShape)(glm::dvec2);
    
    
    void addRect(glm::dvec2 pos){

    };
    addFuncAction<addShape>("void addShape(glm::dvec2)","addRect",&addRect);

    

    
};


class widgetux_wl : public image_wl {
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
        glm::vec4 resize; // zw points to place z{w:-1 e: 1} , w{n: 1 ; s-1}; 
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

        void exec();
        void _init(){
            reloadWindow relwin ;
            this->commands.push_back(relwin);
        };
        
        void init(std::vector<workload*>){
            this->_init();
        };

    };


#include <json.hpp>
#include <stratum/acqres/strata/ini.hpp>
#include <windows.h>
#include <winreg.h>
#include <backend/impl.hpp>
#include <backend/keycode.hpp>
class workloadMan : workload {
    enum wls{
        node_wl    =0b00000001,
        image_wl   =0b00000010,
        widgetux_wl=0b00000100,
        modelling  =0b00001000,
        terrain_wl =0b00010000,
        scene_wl   =0b00100000,
        video_wl   =0b01000000,
        audio_wl   =0b10000000
    };

    class editor : clss_refl {

        class m : clss_refl  {

        };

        REFL_DECL(m, mode) ;
        
    }
    struct editorInfo{
        std::string filePath ;
        uint8_t workload ;
        uint8_t tab ; //
        bool docked; 
        glm::vec4 pos ;
        glm::vec2 scroll ;
    };
    class session {
        
        std::string project ;
        uint8_t workLoads;
        uint16_t activeWorkLoadTab;
        std::vector<float> SideBarTabs ; float sideBarScroll ;
        std::vector<float> LeftSideBarTabs ; float sideBarScroll ;
        std::vector<glm::vec2> editorTabs ; 
        std::vector<editorInfo> openEditors;
        uint16_t activeEditor ;
        
        void read(std::string installLocation){

        }
        void save(std::string installLocation){

        };
    };
    class settings {
        

        typedef struct {
            enum values {
                String,
                Boolean,
                Number            
            };
            union {
                std::string String;
                double Number ;
                bool Boolean;
            } val;
            values v ;
        }Value;
        

        //[Application]
        struct {
            std::string ProjectsFolder = "C:\\src\\StrataProjects";
            std::string font = "LatoItalic.ttf";
            int fontsize= 12;
            
        }app; 
        // [window]
        struct {
            struct  {
                bool cmd = true
                bool scripts = true
            } statusbar;  
            struct {
                bool Save = true
                bool modeselect = true
                bool cinematic = true
                bool compile = true
                bool media = Control = true
                bool platforms = true

            }toolbar;
            bool content = true;
            struct {
                bool pallete = true ;
            } topbar ;
            bool gridView = true ;
        }window;
        struct {
            bool wp = false ;
            bool sp = false ;
            bool coordinates = false ;
            bool entity.StaticMesh = false ;
            bool entity.Actor.Accessory = false ;  
            bool entity.Actor.Material = false ;
            bool entity.Actor = false ;
            bool fps = true ; 
            bool Logging = true ;
        }stats;
        
        //[Stats]
        //[User]
        bool sync = true ;
        std::string name ; 
        std::string password ;   


        void read(std::string installLocation){
            ini i ;
            i.read(installLocation + "settings.cfg");
            for(const auto& it : i.data){
                switch(it.name){
                    case "Application" : {
                        for(const auto& [k,v] : it.entries){
                            switch(k){
                                case "app.ProjectsFolder" : { this->app.ProjectsFolder = resolveVal(v);continue;};
                                case "app.font" : { this->app.font = resolveVal(v);continue;};
                            };
                        };
                    };
                    case "window" : {
                        for(const auto& [k,v] : it.entries){
                            switch(k){
                                case "window.statusbar.cmd" : {this->window.statusbar.cmd = resolveVal(v) ; continue;   };
                                case "window.statusbar.scripts" : {this->window.statusbar.scripts = resolveVal(v) ; continue;   };
                                case "window.toolbar.Save" : {this->window.toolbar.Save = resolveVal(v) ; continue;   };
                                case "window.toolbar.modeselect" : {this->window.toolbar.modeselect = resolveVal(v) ; continue;   };
                                case "window.toolbar.cinematic" : {this->window.toolbar.cinematic = resolveVal(v) ; continue;   };
                                case "window.toolbar.compile" : {this->window.toolbar.compile = resolveVal(v) ; continue;   };
                                case "window.toolbar.media" : {this->window.toolbar.media = resolveVal(v) ; continue;   };
                                case "window.toolbar.platforms" : {this->window.toolbar.platforms = resolveVal(v) ; continue;   };
                                case "window.content"  : {this->window.content = resolveVal(v) ; continue;   };
                                case "window.topbar.pallete" : {this->window.topbar.pallete = resolveVal(v) ; continue;   };
                                case "window.preview.image" : {this->window.preview.image = resolveVal(v) ; continue;   };
                                case "window.preview.model" : {this->window.preview.model = resolveVal(v) ; continue;   };
                                case "Content.gridView"  : {this->Content.gridView = resolveVal(v) ; continue;   };
                            };
                        };
                    };
                    case "Stats" : {
                        for(const auto& [k,v] : it.entries){
                            switch(k){
                                case "stats.wp"                      : { this->stats.wp                      = resolveVal(v);continue ;};  
                                case "stats.sp"                      : { this->stats.sp                      = resolveVal(v);continue ;};  
                                case "stats.coordinates"             : { this->stats.coordinates             = resolveVal(v);continue ;};           
                                case "stats.entity.StaticMesh"       : { this->stats.entity.StaticMesh       = resolveVal(v);continue ;};                 
                                case "stats.entity.Actor.Accessory"  : { this->stats.entity.Actor.Accessory  = resolveVal(v);continue ;};                        
                                case "stats.entity.Actor.Material"   : { this->stats.entity.Actor.Material   = resolveVal(v);continue ;};                     
                                case "stats.entity.Actor"            : { this->stats.entity.Actor            = resolveVal(v);continue ;};            
                                case "stats.fps"                     : { this->stats.fps                     = resolveVal(v);continue ;};   
                                case "stats.Logging"                 : { this->stats.Logging                 = resolveVal(v);continue ;};
                            };
                        };
                    }
                    case "User" : {

                    };
                };
            };

        };
        void save(std::string installLocation){
            ini i ; 

        };
    };
    settings stng; 
    class shortcuts { 
        
        typedef struct {
            size_t si;
            uint8_t* keyc;
        }bind;
        typedef void(*fp)() ;
        std::map<bind, fp> bindings; 
        std::map<std::string , fp> setting;// Initiit
        std::vector<bind> processBindStr(std::string s){
            // Tokenize ;
          
            std::vector<std::string> s; 
            std::vector<uint8_t> op ;
            for(const auto& c : s){
                if(c=='+'){
                    op.push_back(0); 
                    continue ;
                }
                if(c=='|'){
                    s.push_back(new std::string) ;
                    op.push_back(1) ; 
                    continue ;
                }
                s.end() = s.end() + c ;
            };
            std::vector<std::vector<uint8_t>> t;
            for(int i = 0 ; i < s.length(); i++){
                if(s[i].size()==1){
                    t.end().push_back( (uint8_t)s[i][0])
                }
                else {
                    switch(s[i]){
                        case "CTRL" : {t.end().push_back(KC_CONTROL); break;};
                        case "ALT" : {t.end().push_back(KC_ALT); break;};
                        case "SHIFT" : {t.end().push_back(KC_SHIFT); break;};
                        case "MouseRight" : {t.end().push_back(KC_RBUTTON); break;};
                        case "MouseLeft" : {t.end().push_back(KC_LBUTTON); break;};                
                        case "Mouse1" : {t.end().push_back(KC_XBUTTON1); break;};
                        case "Mouse2" : {t.end().push_back(KC_XBUTTON2); break;};
                        case "MouseMiddle" : {t.end().push_back(KC_MBUTTON); break;};
                        case "MouseWheel" : {t.end().push_back(KC_MOUSEWHEEL); break;};                
                    }
                }
                if(op[i] == 1) { 
                    t.push_back(new std::vector<uint>);
                }
            };
            std::vector<bind> res ;
            for(const auto& i : t){
                bind m ;
                m.si = i.length();
                m.keyc= i.data() ;
                res.push_back(m);
            };
            return res;

        };
        void read(std::string installLocation){
            ini i ;
            i.read(installLocation + "shortcuts.cfg");
            for(const auto& it : i.data){
                for(const auto& [key,val] : it.entries) {
                    std::vector<bind> bs = porcessBindStr(val) ;
                    for(const auto& s : bs){
                        this->bindings[s] = this->setting[key]
                    };
                }
            };
        

        };
        void save(std::string installLocation){

        };
        shortcuts(std::map<std::string,fp> _setting) : setting(_setting) ;
    };
    shortcuts shor; 
    std::string installLocation ;
    std::vector<workload>  workloads;    std::vector<uint16_t> enables ; 
    std::vector<workload> plugins_wl ;
    settings stng; 
    
    std::string getInstallLocation(){
        //"StratumEngine"/ Location
        // HINSTANCE hinstLib = LoadLibrary("Advapi32.dll") ;
        // GetProcAddress(hinslib,"RegCreateKeyExA") ;
        PHKEY software ;
        RegOpenKeyExA(HKEY_CURRENT_USER, "Software", 0,KEY_ALL_ACCESS,software);
        PHKEY Stratum ;
        RegOpenKeyExA(software,"StratumEngine",KEY_ALL_ACCESS,Stratum);
        LPDWORD pdt ; PVOID data ; LPDWORD size;
        RegGetValueExA(Stratum,NULL,NULL,NULL,pdt,data,size) ;
        this->intallLocation = std::string((char*)data) ;
    };
    std::string getProjectsFolder(){
        
    };
    std::string setProjectsFolder(std::string path){

    };
    void parseSession(){
        std::string installLoc = getInstallLocation() ;
        std::ifstream f(installLoc + "session.cfg") ;
        session n ; 

    };
    void saveSession(){
        std::string installLoc = getInstallLocation() ;
        std::fstream f(installLoc + "session.cfg", ios::in | ios::out) ;
        std::string line ;
        line<<f ; 
    };
    void addWorkload(workload work_load) [this->plugins.push_back(work_load);];

    workloadMan(uint wl){
        if(wl && wls::node_wl){this->workload.push_back(new node_wl)};
        if(wl && wls::image_wl){this->workload.push_back(new image_wl)};
        if(wl && wls::widgetux_wl){this->workload.push_back(new widgetux_wl)};
        if(wl && wls::modelling){this->workload.push_back(new modelling)};
        if(wl && wls::terrain_wl){this->workload.push_back(new terrain_wl)};
        if(wl && wls::scene_wl){this->workload.push_back(new scene_wl)};
        if(wl && wls::video_wl){this->workload.push_back(new video_wl)};
        if(wl && wls::audio_wl){this->workload.push_back(new audio_wl)};
        this->parseSessionCfg()

    };
};


workloadMan wlm;

void addWorkload(plwl work_load){wlm.addWorkload(work_load);};



#endif