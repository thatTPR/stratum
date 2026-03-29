#pragma once

#include "../editor/editor.hpp"
#include "../editor/util/sys.hpp"
#include "../editor/theming.hpp"


void contributeDestruction(destruction::destruction contrib);

void contributeSculptingBrush(modelling::sculptingBrush sc_b);
void contributePaintingBrush(modelling::paintingBrush p_b);
void contributeTerrainBrush(terrainBrush t_b);

void contributeAnimationAction(AnimationAction animAction);

void contributeModelingAction(ModelingAction modeling);

void contributeMaterial(material mat);
void contributeFluid(fluid fluid);
void contributeParticle(particle particle);

void contributeNode(Snode node);

void contributeMode(editor::mode mode);

void contributeSideBar(editor::sideBar sideBar)
void contributePanelView(panel::view pv);

void contributeActivityBarView(editor::activityBarView abv);
void contributeSidebarView(editor::sideBarView );
void contributeTopBarView(editor::topBarView tbv);
void contributeStatusBar(editor::statusBarView sbv );

void contributeCommand(command c);
void contributeShortcut(shortcut s);


void contributeTheme(theme t ) ;
void contributeFileIcon(icon i ) ; 


