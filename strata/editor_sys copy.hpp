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
namespace graph
{
#define PINNED_ALPHA 200
#define TRIGGERED_ALPHA 255
#define UNPINNED_ALPHA 160

    enum pinType {
        Data = 0 ,
        Exec = 1 // Rendered on topBar and is triggered by event nodes.
        Event = 2 , // Gets triggered 
    };
    class Snode  ;
    class execPin {
        public:
        const std::string name ;
        std::string data ;  // In case of expression ;
        const glm::lowp_uvec4 color_off = {255, 255, 255 , 240} ; 
        const glm::lowp_uvec4 color_on = {255, 255, 255 , 60 } ;
        Snode* n ; 
        eventPin(Snode* N ,const std::string& Name, const std::string& Data  ) : n(N),name(Name), data(Data) {};
        eventPin(Snode* N ,const std::string& Name, const std::string& Data ,  const glm::lowp_uvec4& Color_off,  const glm::lowp_uvec4& Color_on  ) : n(N),name(Name), data(Data),  color_off(Color_off),color_on(Color_on) {};
        eventPin() = default;
    };
    class execPin {

    };
    // EventPinStart
    template <glm::length_t C, glm::length_t R, typename T , glm::qualifier Q>
    class eventPinbase {
        private:
        const std::string name ; 
        bool c_bool = C==1 ;
        bool r = R==1 ;
        public: 
        std::string data = NULL; // In case of logical expression()
        using type = typename std::conditional<C==1 , glm::vec<R,T,Q>,  glm::mat<C,R,T,Q>   >  ;
        execPin* exec ;
        vector< type> vec ;
        eventPin(const std::string& Name) : name(Name) {};
        eventPin(const std::string& Name, const std::string& Data ) : name(Name), data(Data) {};
        eventPin(const std::string& Name, const std::string& Data , vector<type>& Vec  ) : name(Name), data(Data), vec(Vec) {};
        eventPin() = default;
    };
    
    // Derived class that uses the common base implementation
    template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
    class eventPin : public eventPinBase<C, R, T, Q> {
    public:
        using eventPinBase<C, R, T, Q>::eventPinBase;  
    };

    // Partial specialization for `C = 1`, reuses the base class
    template <glm::length_t S, typename T, glm::qualifier Q>
    class eventPin<1, S, T, Q> : public eventPinBase<1, S, T, Q> {
    public:
        using eventPinBase<1, S, T, Q>::eventPinBase; 
    };
/// Eventpin end
    template <struct T>
    class dataPin 
    {
        glm::u8vec4 color;
        std::string name;
        T val;
        bool pinned;
       
        void setData(T d)
        {
            this->data = d;
        }
        dataPin(std::string name)
        {
            this->name = name;
        }
        dataPin(std::string name, color::rgba color)
        {
            this->name = name;
            this->color = color;
        };
        dataPin(std::string name, T val)
        {
            this->name = name;
            this->val = val;
        };
        dataPin(std::string name, T val, color::rgba col)
        {
            this->color = col;
            this->name;
            this->val = val;
        }
    };
/*
 * Base class from which all classes inherit
 */
#define EXEC_COLOR color::rgba(255, 255, 255, 100)
#define EXEC_COLOR_PINNED color::rgba(200, 200, 200, 255)
#define EXEC_COLOR_TRIGGERED color::rgba(240, 240, 200, 255)

    class Snode // TODO async options
    {

        public:
        std::string name; // Custom name
        execPin mainExec
        std::pair<bool, bool>, void> inExecState;
        std::pair<bool, bool>, void> outExecState;

        std::vector<std::pair<Snode *, bool>> outEx;

        std::vector<dataPin > dataIns;
        std::vector<std::pair<dataPin *, std::pair<Snode *, size_t>>, void> dataOuts;

        // Get executed accordingly, in
        std::vector<void (*actions)()> actions;
        virtual void run()
        {
        }
        template <typename U = T, typename std::enable_if<outExec, U>::type * = nullptr>
        void out()
        {
            this->out->in();
        };
        template <typename U = T, typename std::enable_if<inExec, U>::type * = nullptr>
        void in()
        { // Gets executed when the in execPin is triggered
            this->run();
            out();
        };
        void addDataIns(std::vector<dataPin> dps)
        {
            for (auto i : dps)
            {
                this->dataIns.push_back(i);
            }
        };
        void addDataOuts(std::vector<dataPin> dps)
        {
            for (auto i : dps)
            {
                this->dataOuts.push_back(i);
            }
        };

        Snode(std::string n)
        {
            this->name = n;
        }
        Snode(std::array<dataPin> dataIns , std::array<dataPin> dataOuts ){
            
        }
    };



    
    class Sgraph
    { // Sgraph is the editor abstraction for a node collection
        std::string name;
        std::string category;
        uint size;
        snodeElem start;
        std::vector<std::pair<Snode>> nodes; // x , y, pixelWidth , pixelHeight

        // TODO so it takes into account value previews ( in the case of textures ) and multiLine pin sizez ;
        // Not forget
        void getPinPos(Snode node, uint indDataPinIn){

        };
        void calculateNodeSize(sNode *node, uint FontSize, )
        {
            this->size = 0;
            uint w = 0;
            uint h = 0;
            if (typeof(node->inExecState) == typeof(void))
            {
            }
        };
        void autoOrganise()
        {
            // sort vector based on connections
            for (const auto &i : nodes)
            {
                calci->first
            }
            // Make sure they are clean
        }
        void optimize(){

        };
        void render(){

        };
        void preview(){

        };
        void setSize(uint fontSize)
        {
            this->size;
        };
        void update(uint fontSize){

        };
        compile()
        Sgraph(std::vector<Snode> graph, uint fontSize)
        {
            setSize(fontSize)
        }
    }

/*
    @canvas is the canvas used to UX it is rendered internally in the graph. Any canvas 
*/

namespace canvas
{

    enum responsive
    {
        adapitve = 0b01,
        fluid = 0b10,
        mask = 0b11
    };
  
    class widget : graph::Snode
    {
        uint x;
        uint y;
        uint h;
        uint w;

        // Responsiveness all can both by oring
        responsive mode ;
        
        // if adaptive normalised to screen size
        // if fluid normalised to screen percentages
        // if both
        uint left;
        uint right;
        uint up;
        uint down;

        virtual void calculatePosition();
        virtual void behaviour(); // Rendering and interactivity logic

        std::string textsize
    };
    class canvas : Sgraph 
    {
        bool inSpace;
        // Both can be active
        uint w;
        uint h;

        std::vector<std::widget> widgets;
        responsive responsive_mode;
        void responsiveResize(){

        }
        void behaviour(){
            SfwGui::BeginChild();
        };
    }


}

    class canvasGraph {

    };

    #define SNODE
    
    // Snode buildSnode(class classdef)
    // {
    //     Snode n = Snode(typeid(classname).name()) ;
    //     classdef.
        
    // };

        Snode buildSnode(std::string codeBlock ){
            
        }
    Snode codeParse(std::string filename)
    {
        std::ifstream n;
        n.open(nodeName);
    };

    // Compiles all nodes
    void codeGen(Snode node, std::string path){

    };

    Sgraph jsonRead(std::string path){
        std::m};
    void jsonWrite(Sgraph graph, std::string path){

    };


    class graphEditor : editor {

    };

}
// Allows the definition of graphable objects
// The engine searches for these in nodes folder

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
#include "project.cpp"        
            void reload(){
                // Reloads window and settings

            };
          
           
            void FirstWindowMenu(std::string projectsFolder){
                Spreset preset_select = Spreset.Last ; 
                std::vector<std::string> projects =  getProjects(projectsFolder);
                bool grid_view = true ;

#include "../lib/stb/stb_image.h"
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

