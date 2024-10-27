#pragma once


#include <coroutine>



#include "editor.hpp"

#include <type_traits>
#include <typeinfo>
#include <theming.hpp>
#include <../lib/sfwgui/sfwgui.h>

#include "editor/editor.hpp"

#include "lib/vk/vulkan.hpp"
#include "lib/SDL2/SDL2.h"
#include "lib/sei_defs.hpp"
#include "lib/sei.hpp"
#include <vulkan.h>

#include "util/sys.hpp"

#include <type_traits>
#include <typeinfo>
#include <theming.hpp>

#define SEI_SETTINGS_ALL
#include "../lib/sei_settings.hpp"

#include "project.cpp"        

#include "../lib/stb/stb_image.h"

#define SEI_SETTINGS
    #include "../lib/sei_defs.hpp"
#include "../lib/sei.hpp"


 // In this folder only manages settings and own filesystem and trivial code operations
 // TOD
namespace editor
{

    // A dockable view 
    class view 
    { // TODO make so that it
        // Since theses views are rendered in a scroll view there must be a system in place to ensure their correct behaviour

        uint x, y, w, h;y
        virtual std::string menuName;
       
        virtual bool begin();
        virtual bool end();
        virtual bool push(std::vector<view>){

        };
        
        void view_behaviour()
        {
            // Test with
            SfwGui::BeginChild(menuName);
            this->barRender();
            SfwGui::EndChild(menuName);
            // SfwGui::BeginMenu("")
        };
    };
    class panelView : view 
    {
        
        panelView(std::string _menuName) :  menuName(_menuName) ,  {};
    };
    class sideBarView : view
    {
        SideBarSide side;
        bool uint priorirty;
        bool primary;
        auto icon; // Can be pg image and other
        side sb;
        virtual behaviour(){

        };
        void changeSideBehaviour() virtual bool barRender(uint x, uint y, uint w, uint h, window window)
        {
            if (SfwGui::ImageButton(, size))
            {
                this->changeSide();
            }; // TODO
            if (SfwGui::IsItemHovered())
                SfwGui::SetTooltip("Change Side");
            SfwGui::SameLine();
            if (SfwGui::ImageButton("", size))
            {
            };
            if (SfwGui::IsItemHovered())
                SfwGui::SetTooltip("Priority Down");
            SfwGui::SameLIne();
            if (SfwGui::ImageButton("", size))
            {
            };
            if (SfwGui::IsItemHovered())
                SfwGui::SetTooltip("Priority Up");
        };
        virtual calculateBounds(uint x, uint y, uint w, uint h) override
        {
            this->x
        }
    };
    class activityBarView: view
    {
        image::rgba_static_image iconPath;
        behaviour();
        activityBarContrib(std::string iconPath)
        {
        }
    };
    class activityBar
    {
        std::vector<activityBarContrib> contribs;
        std::vector<activityBarContrib> pluginContribs;
        void render()
        {
        }
    };

    // Owns all entities withing the scene within a hierarachical structure
    // and allows the user to select and edit their attributes
    class outline : sideBarView
    {

        SideBarSide side = SideBarSide.right;
        uint priorirty = 1;
        bool primary;
        bool x, y, w, h;
        std::string menuName = outline;
        std::string menuTypeName = ;
        void render() override
        {
            view::render();
        }
        outline(){

        };
    };
    class layers : sideBarView
    {
        std::vector<std::vector<model *>> lyrs;
        side renderSide = side.right;
        uint priorirty = 1;
        bool primary;
        bool x, y, w, h;
        std::string menuName;
        std::string menuTypeName;

        std::string void render() override{
            view::barRender()} outline(){

        };
    };
    template <class T>
    class details
    {
        T val;
        virtual behaviour()
    };
    class details : sideBarView
    {
        side sd = side.right;
        uint priority = 2;
        bool primary;

        std::vector<>
    };

    class explorer : sideBarView
    {
    };
    
    class sideBar: view  {
        uint w ;
        bool active ;
    };
   
    class sideBars
    {
        sideBar left ; 
        sideBar right ; 
        
        // bool leftActive;
        // bool rightActive;
        std::vector<sideBarView> left;
        std::vector<sideBarView> right;


        void changeSideBarLeft(){

        };
        void 
        void calculatePositions(){

        };

            void
            update(){

            };
    };
    
    class topBar
    {
    };
    class topBarView {

    };
    class statusBar
    {
        uint relx;
        uint rely;

    };
    class statusBarView {
        std::string imagePath ;

    };
     class mode
    {
        virtual std::string mode_name;
        virtual std::string trigger;
        virtual std::vector<> views; // Views which are relevant to the mode
        virtual void trigger()
        {
        }
        mode(std::string Trigger)
        {
            this->trigger = Trigger;
        }
    };
    class animation : mode
    {
    };
    class selection : mode
    {
        std::vector<>
    };
    class environment : mode
    {
    };
    class destruction : mode
    {

    };


    // TODO allows executing commands from a command pallette instead Like Quick Select
    bool pallette = false ;
    void commandPalletteBehaviour(){

    }; 
    void quickSelect();// CTRL+P     


// Begin editor
    class editor
    {

        Slog logging;
        Scommand commands
        std::vector<mode> modes;
        std::vector<mode> plugin_modes;

        std::vector<StrataCommand> commands;
        std::vector<StrataCommand> plugin_commands;

        std::vector<view> views;
        std::vector<>

            // TODO
         editor::editor appEditor;
        platform::platforms appPlatform;
        destruction::editor destructionEditor;
        scene::editor sceneEditor;
        preview::preview ;

        std::filesystem::path projectsDir ;
        std::filesystem::path pluginsDir ;

   // [Section] Project and application
stng_condition cond;
            class SeiSet : sei_settings
            {   
                SeiSet(std::string filename , )
            };
            void reload();
          
           
            void FirstWindowMenu(std::string projectsFolder){
                Spreset preset_select = Spreset.Last ; 
                std::vector<std::string> projects =  getProjects(projectsFolder);
                bool grid_view = true ;

                SfwVec2 PresetButtonSize = SfwVec2(600, 200);
                    SfwVec2 PresetImageSize = SfwVec2(500 , 180);
                auto AppImage = stbi_load("assets/ui/PresetAppImage.png",PresetImageSize.x,PresetImageSize.y);
                    auto GameImage = stbi_load("assets/ui/PresetGameImage.png",PresetImageSize.x,PresetImageSize.y);
                    auto FilmLiveImage = stbi_load("assets/ui/PresetFilm&LiveImage.png",PresetImageSize.x,PresetImageSize.y);
                    auto ArchitectureImage = stbi_load("assets/ui/PresetArchitectureImage.png",PresetImageSize.x,PresetImageSize.y);
                    auto SimulationImage = stbi_load("assets/ui/PresetSimulationImage.png",PresetImageSize.x,PresetImageSize.y);
                    auto EngineeringImage = stbi_load("assets/ui/PresetEngineeringImage.png", PresetImageSize.x,PresetImageSize.y);

                      SfwTextureID  App = (SfwTextureID)AppImage ;
                    SfwTextureID  Game = (SfwTextureID)GameImage ;
                    SfwTextureID  FilmAndLive = (SfwTextureID)FilmImage ;
                    SfwTextureID  Architecture = (SfwTextureID)ArchitectureImage ;
                    SfwTextureID  Simulation = (SfwTextureID)SimulationImage ;
                    SfwTextureID  Engineering = (SfwTextureID)EngineeringImage ;

                    SfwGui::SfwVec2 FolderImageSize = SfwVec2(690, 690 );
                    auto plusImage = stbi_load("assets/ui/plus.png" , FolderImageSize.x, FolderImageSize.y);
                    SfwTextureId Plus = (SfwTextureId)plusImage;

                    const float padding = 0.01 ;
                    constexpr const float uv0 = SfwVec2(0 + padding , 0+ padding);
                    constexpr const float uv1 = SfwVec2(1 - padding , 1 - padding) ;
                // Start window to select or create project as well as review settings
                 while (SDL_PollEvent(&event) != 0) 
                {
                    SfwGui::Begin("StartWindow");
                    SfwGui::Columns(2, "FirstWIndowCols" , true );
                    SfwGui::SetColumnWidth(300);
                    
                    if(SfwGui::ImageButton("App" ,        App ,            PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,  (preset_select==strata::Spreset.App)?S_BUTTON_TINT:S_BUTTON_TINT_ON)){
                        preset_select = (preset_select!=strata::Spreset.App)? strata::Spreset.App :  strat::Spreset.App.First;
                    };
                    if(SfwGui::ImageButton("Game",        Game ,           PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,  (preset_select==strata::Spreset.Game)?S_BUTTON_TINT:S_BUTTON_TINT_ON )){
                        preset_select = (preset_select!=strata::Spreset.Game)?strata::Spreset.Game:strat::Spreset.App.First ;
                    };     
                    if(SfwGui::ImageButton("Film&Live",   Film ,           PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,   (preset_select==strata::Spreset.FilmAndLive)?S_BUTTON_TINT:S_BUTTON_TINT_ON )){
                        preset_select = (preset_select!=strata::Spreset.FilmAndLive)?strata::Spreset.FilmAndLive:strat::Spreset.App.First ;
                    };  
                    if(SfwGui::ImageButton("Architecture",Architecture ,   PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,   (preset_select==strata::Spreset.Architecture)?S_BUTTON_TINT:S_BUTTON_TINT_ON )){
                        preset_select = (preset_select!=strata::Spreset.Architecture)?strata::Spreset.Architecture:strat::Spreset.App.First;

                    };
                    if(SfwGui::ImageButton("Simulation",  Simulation ,     PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,   (preset_select==strata::Spreset.Simulation)?S_BUTTON_TINT:S_BUTTON_TINT_ON )){
                        preset_select = (preset_select!=strata::Spreset.Simulation)?strata::Spreset.Simulation:strat::Spreset.App.First ;

                    };
                    if(SfwGui::ImageButton("Engineering", Engineering ,    PresetImageSize ,uv0 , uv1, S_BUTTON_BG ,   (preset_select==strata::Spreset.Engineering)?S_BUTTON_TINT:S_BUTTON_TINT_ON )){
                        preset_select = (preset_select!=strata::Spreset.Engineering)?strata::Spreset.Engineering:strat::Spreset.App.First ;

                    };   
                    SfwGui::NextColumn();
                    SfwGui::Text("Projects") ;
                    // DirView of the projects directory
                    SfwGui::Separator();                                      
                    #include "filesystem.cpp"
                    
                    dirView(this->projectsDir)
                    SfwGui::End()
                }
            };
            void run(){

            };
            void editor()
            {
                this->editorInst = editor(&this->sei_project, &this->sei, &this->sei_set, &this->sei_project);
            }
        
    strata::SeiProjSet sei_project_set ;
    strata::SeiProject sei_project;

    
    SeiSet sei_set ;
   
    sei sei;

    void undo(){

    };
    void run(){
        this->FirstWindowMenu()};
    editor()
    {
        this->sei = SeiInt();
        this->sei_set = SeiSet();
    };
    
    
};

namespace editor {
class editor_global {
    private:

    protected:

    public:
    editor_global();
};

editor_global ed_global ;
};


namespace workload {


enum editor_workload {
    // Default
    Node=0 ,
    Canvas=1,
    Model=2,
    Terrain=3,
    Image=4,
    Video=5,
    Scene=6, 

    Max = 10 
};

class workload {
    uint8_t editor_workload ;
    workload* deps ;
    workload()  :{}; 

};

class node_wl : workload {

};
class canvas_wl : workload {

};
class model_wl : workload {

};
class terrain_wl : workload {

};
class image_wl : workload {

};
class video_wl : workload {

};
class scene_wl : workload {

};


class workload_global {
    private :
   std::vector<workload editor_workload> workloads ;
    public:
    void addPluginWorkload(struct workload wl);
    
    workload_global();

};

workload_global work_global ; 

};
