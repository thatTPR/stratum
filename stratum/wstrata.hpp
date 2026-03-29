
namespace contribute { // All func return -1 if failed and index of workload if succesfull.

int getWorkload(char* name);
int getTaskbar(char* name);
int getSideBarView(char* name);
int getWidget(char* name);
int getWidgetPen(char* name);
int getModelPen(char* name) 
int getModelBrush(char* name);
int getSceneryPen(char* name);
int getSceneryBrush(char* name);

int get_vertModule(char* name);
int get_fragModule(char* name);
int get_geomModule(char* name);
int get_tescModule(char* name);
int get_teseModule(char* name);
int get_compModule(char* name);
int get_taskModule(char* name);
int get_meshModule(char* name);
int get_rgenModule(char* name);
int get_rintModule(char* name);
int get_rahitModule(char* name);
int get_rchitModule(char* name);
int get_rmissModule(char* name);
int get_rcallModule(char* name);
int get_entityModule(char* name);
int get_sceneryModule(char* name);

int WorkLoad(workload_contrib wc);
int Taskbar_contrib(char* workload_name ,taskbar_contrib tc);
int SidebarView_contrib(char* workload_name, sidebar_contrib tc); // Has a workload contribution point, model,scenery

enum widget_contrib_point {
    Sidebar,
    SideBarAssets,
    CustomView,
} ;
int Widget_contrib(char* workload_name, widget_contrib wc ,widget_contrib_point wcpt );
int WidgetPen_contrib( widget_contrib wc ,widget_contrib_point wcpt);
int ModelPen_contrib();
int ModelBrush_contrib();
int ModelKern_contrib();
int SceneryPen_contrib();
int SceneryBrush_contrib();
int SceneryKern_contrib();


int vertModule(vertModule mod);
int fragModule(fragModule mod);
int geomModule(geomModule mod);
int tescModule(tescModule mod);
int teseModule(teseModule mod);
int compModule(compModule mod);
int taskModule(taskModule mod);
int meshModule(meshModule mod);
int rgenModule(rgenModule mod);
int rintModule(rintModule mod);
int rahitModule(rahitModule mod);
int rchitModule(rchitModule mod);
int rmissModule(rmissModule mod);
int rcallModule(rcallModule mod);


void entityModule();

void sceneryModule();

};


