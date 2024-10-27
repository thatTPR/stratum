#pragma once

#include <filesystem>
#include <ifstream>
#include <typeinfo>
#include <string>
#include <>
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#define USER_SETTINGS
#define SEI_SETTINGS_NESTED
#include <../lib/sei_settings.hpp>
typedef HINSTANCE shared
#endif
#else
#ifdef PLATFORM_LINUX
typedef 
#ifdef 

using namespace std ;


class pluginSettings : sei_settings {

};

class plugin {
    std::string name ; 
    bool enable ;
    bool enable_theme ; 

    std::vector<plugin> pluginDeps  ;
    
    std::vector<destruction::destruction> destructions ;
    std::vector<modelling::sculptingBrush> sculpting_brushes ;
    std::vector<modelling::paintingBrush> painting_brushes ;
    std::vector<animation::AnimationAction> animation_actions;

    std::vector<environment::terrainBrush> terrain_brushes; 
    std::vector<environment::foliageBrush> foliage_brushes; 
    std::vector<environment::SurfaceTerrainBrush> surface_terrain_brushes ; 
    
    std::vector<graph::Sgraph> graphs ;
    std::vector<graph::Snode> nodes ;


    std::vector<editor::mode> modes ;
    std::vector<editor::panel> panels ;
    std::vector<editor::activityBarView> activityBarViews ;
    std::vector<editor::topBarView> topBarViews ; 
    std::vector<editor::sideBarView> sideBarViews;
    std::vector<editor::statusBarView> statusBarViews;
    std::vector<editor::sideBar> sideBars;
    std::vector<editor::sideBars> sideBarses ; // Contains controls two sidebars

    std::vector<apparatus::Scommand> commands; 

    std::vector<theme::iconTheme> iconThemes ;
    std::vector<theme::widgetTheme> widgetThemes ;
    std::vector<theme::widgetTheme> pluginWidgetThemes ; 
};
plugin curr_plugin = NULL ; 

void requirePlugin(plugin plugin){
    curr_plugin.plugins.pushBack(name);
};
void requirePluginDeps(std::vector<std::string> pluginNames){

};
// TODO




class pluginsys {
    std::vector<plugin> plugins;

    std::vector< std::pair<std::string, std::vector<plugin*> > > contributions ;
};
void pluginActivation(){

};
    void pluginParse(){

    };
    void searchPlugins(){

    };
    void pluginsProcess(std::string pluginFolder){

    };
    