#pragma once
#include "sys_graph.hpp"
#include "nodes/canvas.hpp"

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
    };

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

};