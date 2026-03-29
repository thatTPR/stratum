#pragma once
#include <sys.cpp>
#include <apparatus.cpp>
#include <interface.cpp> 


namespace scene
{
    class preview
    {
    };

   
    class layout
    {
        int rowFirstNum ;
        int rowSecondNum ;
        int rowThirfNum ;
    };
    class gizmo
    {
        run
    };
    class editor:
    {
    }
};
namespace graph
{
#define PINNED_ALPHA 200
#define TRIGGERED_ALPHA 255
#define UNPINNED_ALPHA 160

    enum pinType {
        Event, // Gets triggered 
        Exec ,
        Data ,

    };
    class pin {
        color::rgba col ; 
    };
    class eventPin : pin {

    };
    class execPin : pin {

    } ;
    
    template <typename T>
    class dataPin
    {
        color::rgba color;
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
    class graph {

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
    };
    Snode compileSnode(Sgraph sg){

    } ;

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
            this->pluginView= pluginContrib;
        };
    };
};
namespace modeling {
    class ModellingAction {

    };
    class sculpting {
        std::vector<sculptingBrush> brushes ;

    };
    class paintingBrush {

    };
    class sculptingBrush {

    };
    class painting {
        std::vector<paintingBrush> brushes ;
    };
    class modelling : mode { // Main scene
        std::vector<>
    };
};
namespace animation {
    class AnimationAction {

    };
    class animation : mode {
        std::string name = "Animation ";
        std::string description = "Allows edition of animations for object "
    };
};
namespace environment {
    class terrainBrush : brush {

    };
    class foliageBrush : brush  {

    };
    class SurfaceTerrainBrush : brush {

    };
    class environment : mode {

    };
};

class mode { // Modes are consumed and contributed to the topbar as a tab 
    std::string description ; 
    std::string name ;
};
class destruction : mode {

};
class modelling : mode {

};
class scene : mode {

};
class environment {

};