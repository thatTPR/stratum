#include <string>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#include "shad.hpp"
#define fs std::filesystem
using namespace std;

// static const char* workspace_folder = get_strata_workspace_folder();
// static const char* STRA_PATH = get_strata_path()
 // TODO  Shaderc for runtime shader compilation with vulkan 
std::vector<std::string> get_STRA_PATH(){
    return {};
};
// std::vector<std::string> get_STRA_PATH(){ // TODO make this file in projdir + instdir
    // const char* path = "STRA_PATH"; 
    // const char* paths std::getenv(path);
    // char c;
    // std::vector<std::string> path;
    // int i=0;
    // while(c<<paths){
    //     if(c==';'){i++; continue;}
    //     path[i]+=c;
    // };
    // return path;
// };
    std::string command;
std::string incl_file(fs::path file, std::vector<std::string>& paths){
    std::ifstream ifile(file);
    std::string line;
    int lineno=-1;
    std::string f;
    while(std::getline(ifile,line)){
        lineno++;
        f+="\n";
        if(line.find("#include")){
            int first = 0 ;
            int sec = 0 ;
            if(first=line.find("\"")){
                sec = line.find_last_of("\"");
                fs::path p = line.substr(first+1,sec-1-first );
                std::ifstream fi(p);
                if(fi.is_open()){
                    std::stringstream s ;s<< fi.rdbuf();
                    line = s.str(); f+=line;
                }
                else {std::cerr<<"File not found at line "<<lineno;}

            }
            if(first=line.find("<")){
                sec = line.find_last_of(">");
                fs::path p(line.substr(first+1,sec-1-first )) ;
                for(std::string it : paths){
                    fs::path p(it) ; bool found = false;
                    for(fs::directory_entry i : fs::directory_iterator(p)){
                        if(i.is_regular_file()){
                            fs::path pn = i.path();
                            if(pn.filename() == p){
                                ifstream fi(pn);
                                std::stringstream buf ;buf<< fi.rdbuf();
                                std::string line = buf.str();
                                f+=line; bool found = true;
                                break;
                            };
                        };
                    }
                    if(found){break;}
                    else std::cerr<<"File not found at line" << lineno;

                };
            };
            continue;
        };
        f+=line;
    };
    return f;
};

void file_comp(std::vector<std::string> files,std::vector<std::string>& incpath){
    for(std::string f : files){
        std::stringstream fi ;fi << "\"";
        fi << incl_file(f,incpath);
        fs::path p(f);
        fi << "\" | "+command; 
        std::string stem ;
        fi << "-o " + p.stem().string();
        bool b = false;
        
        if      (p.extension()== vert ){fi<<"_"<<vert<<".spv -fshader-stage="<<vert    ;b=true;  }
        else if (p.extension()== frag ){fi<<"_"<<frag<<".spv -fshader-stage="<<frag    ;b=true;  }
        else if (p.extension()== geom ){fi<<"_"<<geom<<".spv -fshader-stage="<<geom    ;b=true;  }
        else if (p.extension()== tesc ){fi<<"_"<<tesc<<".spv -fshader-stage="<<tesc    ;b=true;  }
        else if (p.extension()== tese ){fi<<"_"<<tese<<".spv -fshader-stage="<<tese    ;b=true;  }
        else if (p.extension()== comp ){fi<<"_"<<comp<<".spv -fshader-stage="<<comp    ;b=true;  }
        else if (p.extension()== task ){fi<<"_"<<task<<".spv -fshader-stage="<<task    ;b=true;  }
        else if (p.extension()== mesh ){fi<<"_"<<mesh<<".spv -fshader-stage="<<mesh    ;b=true;  }
        else if (p.extension()== rgen ){fi<<"_"<<rgen<<".spv -fshader-stage="<<rgen    ;b=true;  }
        else if (p.extension()== rint ){fi<<"_"<<rint<<".spv -fshader-stage="<<rint    ;b=true;  }
        else if (p.extension()== rahit){fi<<"_"<<rahit<<".spv -fshader-stage="<<rahit ;b=true;  }
        else if (p.extension()== rchit){fi<<"_"<<rchit<<".spv -fshader-stage="<<rchit ;b=true;  }
        else if (p.extension()== rmiss){fi<<"_"<<rmiss<<".spv -fshader-stage="<<rmiss ;b=true;  }
        else if (p.extension()== rcall){fi<<"_"<<rcall<<".spv -fshader-stage="<<rcall ;b=true;  }
        else if (p.extension()=="glsl"){fi<<"_"<<"glsl"<<".spv " ;  }
        else if(b==false)continue;
        fi<<" - ";
        std::cout<<"Executing"<<fi.str();
        std::system(fi.str().c_str());  
    };

};
void comp_dirs_files(std::vector<std::string> dirs,std::vector<std::string>& incpath){
        std::vector<std::string> files;
    for(std::string en : dirs){
        fs::path d(en);
        files.clear();
        for(fs::path entry : fs::directory_iterator(d)) {
            if(fs::is_regular_file(entry)){
                files.push_back(entry.string());
            };
        };
        file_comp(files,incpath);
    };
};

void write_dirs_spvs_to_file(std::vector<std::string> dirs ){
    for(std::string dir: dirs ){

    std::string files[1000] ;
    int j =0;
    fs::path s(dir);
    std::ofstream out(dir+"\\"+s.stem().string());
    
    for( fs::path entry : fs::directory_iterator(s)){
         if (fs::is_regular_file(entry)){
            std::string ext = entry.extension().string();
            if (ext.compare("spv")){
                std::string command;
                std::ifstream in(entry);
                out<<"char"<<" "<<entry.stem()<<"[]= \"";
                char i;
                while(in>>i){
                    out<<i;
                };
                out<<"\";\n";
            };
        };
    };
    }
   
};
#ifndef STRATA_NO_MAIN
int main( int argc, char* argv[]){
    if(argc==1){
    if(argc == 1){std::cout<<"shadbat -Iinc... -Ddir... file.. -ddir_file_incls -\"command\" :\n -I : include folders\n -D : compile shaders and include in dir fild\n -d include spv.s in source file.hpp";}
        return 1;
    };
    std::vector<std::string> incpath ; /*incpath=get_STRA_PATH()*/
    std::vector<std::string> directories ;
    std::vector<std::string> files;
    std::vector<std::string> incldir;
    command = "";
    for ( int i = 1 ; i < argc ; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'I'){
                
            std::string com;
            int j=2;
            while (char c = argv[i][j]){
                com =+c; j++;
            };
            com[j]=argv[i][j];

            std::string p(com);
            incpath.push_back(p);
            char c[com.length()] ;
            std::strcpy(c, com.c_str());
            
            std::cout<<c;
            }
            else if (argv[i][1]== 'D'){
                 std::string com;
                int j=2;
                while (char c = argv[i][j]){
                    com =+c; j++;
                };
                com[j]=argv[i][j];
                directories.push_back(com);
            }
            else if(argv[i][1] =='\"'){
                int j=2 ;
                while (char c = argv[i][j]){
                    if(c=='\"'){command+=c;break;}
                    command =+c; j++;
                };
            }
            else if(argv[i][1] == 'd'){
                std::string com;
                int j=2;
                while (char c = argv[i][j]){
                    com =+c; j++;
                };
                com[j]=argv[i][j];incldir.push_back(com);
            };
        }
        else {
            files.push_back( std::string(argv[i] ));
        };            
    
        };
            
        comp_dirs_files(directories,incpath);
        write_dirs_spvs_to_file(directories);
        file_comp(files,incpath);
        write_dirs_spvs_to_file(incldir);
        
    return 1;
    };
    
#endif