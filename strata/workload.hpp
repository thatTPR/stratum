#pragma once
#include "inc/strata_types"
// From this file plugins can add app contribution;
// Each of these classes have their own scope
class taskbar_contrib{
    
};
class topbar_contrib{

};
class sidebar_contrib{
    left ;
    right ;
};
class widget_contrib{
    
};
class editor_contrib{

};


class workload {
    sidebar_contrib;
    topbar_contrib;
    taskbar_contrib;
    widget_contrib;
    

    workload(); 

};