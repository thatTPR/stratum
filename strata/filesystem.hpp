#include <sfwgui/sfwgui.h>
#include <sfwgui-extra/sfwgui_file_dialog.cpp>
#include <project.cpp>
#include <fstream>

getDirectories(std::filesystem::path path)
            
for (const auto& entry : fs::directory_iterator(path)
if (fs::is_directory(entry.status()
push_back( entry.path()
filename() 
 gridAndFileView()
 dirView(std::filesystem::path* dir  , std::filesystem::path* selected , bool* grid_view )
if(*grid_view )
for(const auto  &i : projects) 
                        
ImageButton("", Plus , FolderImageSize, uv0, uv1 ,SfwVec4(0 , 0 , 0 , 255) 
SfwVec4(0 , 0 , 0 , 255) 
SfwVec4(70 , 140, 224 , 225)
if(SfwGui::IsItemHovered()
SetItemTooltip();
for(const auto &i : projects) 
                        
 render()
 treeDirView(std::filesystem::path folderPath , std::filesystem::path* selected)