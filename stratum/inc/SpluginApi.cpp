// Allows wriing and contributing plugins to the engine
#include "pluginsys.cpp"
#include "../editor/editor.cpp"
#include "../editor/util/apparatus.hpp"
#include "pluginApi.hpp"
// TODO compile properly

void contributeDestruction(destruction::destruction contrib ){
    curr_plugin.destructions.push_back(contrib);
};
void contributeSculptingBrush(modelling::sculptingBrush sc_b){
    curr_plugin.sculpting_brushes.push_back(sc_b);
};
void contributePaintingBrush(modelling::paintingBrush p_b){
    curr_pugin.painting_brushes.push_back(p_b) ; 
};
void contributeAnimationAction(AnimationAction animAction){
    curr_plugin.animation_actions.push_back(animAction);
};

void contributeTerrainBrush(environment::terrainBrush t_b)[
    curr_plugin.terrain_brushes.push_back(t_b);
];
void contributeFoliageBrush(environment::foliageBrush f_b)[
    curr_plugin.foliage_brushes.push_back(f_b);
];
void contributeSurfaceTerrainBrush(environment::SurfaceTerrainBrush s_t_b){
    curr_plugin.surface_terrain_brushes.push_back(s_t_b);
};

void contributeNode(graph::Snode node){
    curr_plugin.nodes.push_back(node);
};
void contributeGraph(graph::Sgraph graph){
    curr_plugin.graphs.push_back(graph);
};
void contributeMode(editor::mode mode){
    curr_plugin.modes.push_back(mode);
};
void contributeSideBar(editor::sideBar sb){
        curr_plugin.sideBarses.push_back();
};
void contributeSidebarView(editor::sideBarView sbv  ){
    curr_plugin.sideBars.push_back(sbv);
};
void contributeActivityBarView(editor::activityBarView ac)[
        curr_plugin.activityBarViews.push_back(ac);
];
void contributeTopBarView(editor::topBarView topBarview){
        curr_plugin.topBarViews.push_back(topBarview);
};
void contributeStatusBarView(editor::statusBarView statusView){
        curr_plugin.statusBarViews.push_back(statusView);
};
void contributePanelView(editor::panel panel){
        curr_plugin.panels.push_back(panel);
};

void contributeCommand(apparatus::Scommand command){
        curr_plugin.commands.push_back(command);
}

void contributeFileIconThme(iconTheme i ){
        curr_plugin.iconThemes.push_back(i);
} ; 
void contributeWidgetTheme(widgetTheme w){
        curr_plugin.widgetThemes.push_back(i);

}
void contributePluginWidgetTheme(widgetTheme w){
        curr_plugin.pluginWidgetThemes.push_back(w);

};

void contributeMaterial(material mat){
        curr_plugin.push_back();
};
void contributeParticle(particle particle){
        curr_plugin.push_back();
};
void activate(){

};