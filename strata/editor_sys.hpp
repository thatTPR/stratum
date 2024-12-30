#pragma once

#include "../lib/glm/glm.hpp"
#include <type_traits>
#include <string>
#include <vector>
using namespace std ;
namespace panel
{
    class gizmo 
    {
        
        virtual void behaviour();
    };
    
    class tool { // TOOD
        gizmo mouseGizmo ; 
        
    };
    class view {

    };
      
};

namespace destruction
{ // Destruction view
    class destruction
    {
        std::string name;
        std::string iconPath;
    };
    class fracture : destruction
    {
        std::string name;
    };
    class cut : destruction 
    {
    };
    class gore : destruction
    {
    };
    class compression : destruction {

    };
    class tearing : destruction {

    };
    class editor
    {
        std::array<destruction> builtin, std::vector<destruction> pluginContrib;
        editor(std::array<destruction> builtin, std::vector<destruction> pluginContrib)
        {
            this->builtin = builtin;
            this->pluginContrib = pluginContrib;
        };
    };
};
namespace modelling {
    class ModellingAction {

    };
    class sculptingBrush {
        std::vector<sculptingBrush> brushes ;

    };
    class paintingBrush {

    };
    class painting {
        std::vector<paintingBrush> brushes ;
    };
    class modelingEditor{ // Main scene
        std::vector<>
    };
};
namespace animation {
    class AnimationAction {

    };
}

namespace editor
{
    
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

     enum SideBarSide {
        left = 0,
        right = 1;
    };
    // A dockable view 
    class view
    { // TODO make so that it
        // Since theses views are rendered in a scroll view there must be a system in place to ensure their correct behaviour

        uint x, y, w, h;
        virtual std::string menuName;
        virtual std::string menuTypeName;
        virtual void calculateBounds();
        
        
        virtual void behaviour()
        {
            // Test with
            SfwGui::BeginChild(menuName);
            this->barRender();
            SfwGui::EndChild(menuName);
            // SfwGui::BeginMenu("")
        };
    };
    class panelView 
    {

    };
    
    

    class sideBarContrib : view
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
    class activityBarContrib : view
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
    class outline : sideBarContrib
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
    class layers : sideBarContrib
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
    class detailsContrib
    {
        T val;
        virtual behaviour()
    };
    class details : sideBarContrib
    {
        side sd = side.right;
        uint priority = 2;
        bool primary;

        std::vector<>
    };

    class explorer : sideBarContrib
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
        std::vector<sideBarContrib> left;
        std::vector<sideBarContrib> right;


        void changeSideBarLeft(){

        };
        void 
        void calculatePositions(){

        };

            void
            update(){

            };
    };
    class topBarContrib
    {
    };
    class topBar
    {
    };
    class statusBar
    {
        uint relx;
        uint rely;

    };
    class statusBarContrib {
        std::string imagePath ;

    };
    
    // TODO allows executing commands from a command pallette instead Like Quick Select
    bool pallette = false ;
    void commandPalletteBehaviour(){

    }; 
    void quickSelect();// CTRL+P     

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
#define SEI_SETTINGS_ALL
#include "../lib/sei_settings.hpp"
stng_condition cond;
            class SeiSet : sei_settings
            {   
                SeiSet(std::string filename , )
            };
#include <project.cpp>   
            void reload(){
                // Reloads window and settings

            };
          
           
            void FirstWindowMenu(std::string projectsFolder){
                Spreset preset_select = Spreset.Last ; 
                std::vector<std::string> projects =  getProjects(projectsFolder);
                bool grid_view = true ;

#include <lib/stb_image.h>
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
                 while () 
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
            };
        };
    strata::SeiProjSet sei_project_set ;
    strata::SeiProject sei_project;

    
    SeiSet sei_set ;
    #define SEI_SETTINGS
    #include "../lib/sei_defs.hpp"
#include "../lib/sei.hpp"
    sei sei;

    
    void run(){
        this->FirstWindowMenu()};
    editor()
    {
        this->sei = SeiInt();
        this->sei_set = SeiSet();
    };
    
    
};

