#include <sfwgui/sfwgui.h>
#include <sfwgui-extra/sfwgui_file_dialog.cpp>

#include <project.cpp>

// TODD Get ProjectInfo

inline std::vector<<std::filesystem::path> getDirectories(std::filesystem::path path)
            {
                std::vector<std::filesystem::path> dirs ;
                for (const auto& entry : fs::directory_iterator(path)) {
                    if (fs::is_directory(entry.status())) 
                    {
                        dirs.push_back( entry.path().filename() );
                    }
                }
            };


void gridAndFileView(){

};
void dirView(std::filesystem::path* dir  , std::filesystem::path* selected , bool* grid_view ){
    
                if(*grid_view ){
                        for(const auto  &i : projects) 
                        {

                        };
                        SfwGui::ImageButton("", Plus , FolderImageSize, uv0, uv1 ,SfwVec4(0 , 0 , 0 , 255) , SfwVec4(0 , 0 , 0 , 255) , SfwVec4(70 , 140, 224 , 225));
                        if(SfwGui::IsItemHovered()){
                            SfwGui::SetItemTooltip();
                        };
                    };
                    else {
                        for(const auto &i : projects) 
                        {
                            Butt
                        }

                    };
            };
class DirView {
    #include <fstream>
    bool grid_view ; 
    std::filesystem::path dir ; 
    std::vector<std::filesystem>
    std::filesystem::path selected ;
    void render(){

    };

};
 // Renders a tree view of a directory
void treeDirView(std::filesystem::path folderPath , std::filesystem::path* selected){

};

