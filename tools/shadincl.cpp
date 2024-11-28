#include <string>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <vector>
#include <cstdlib>
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
int main(int argc , char* argv[]){
    if(argc==1){
        std::cout<<"shadincl -Isearchdir files...  -\"command\"";
        return 1;
    };
    std::vector<std::string> incpath = get_STRA_PATH();
    
    std::vector<std::string> files;
    std::string command;
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
            if(argv[i][1] =='\"'){
            int j=2 ;
            while (char c = argv[i][j]){
                if(c=='\"')break;
                command =+c; j++;
            };
            };
        }
        else {
            files.push_back( std::string(argv[i] ));
        };            
        
    };
    for(std::string f : files){
        std::string fi ;fi += "\"";
        fi += incl_file(f,incpath);
        fs::path p(f);
        fi+="\" | "+command; 
        std::string stem ;
        fi+="-o " + p.stem().string();
        if(p.extension() == "frag"){
            fi+="_frag.spv";
            fi+="-fshader-stage=fragment";
        };
        if(p.extension() == "vert"){
            fi+="_vert.spv ";
            fi+="-fshader-stage=vertex ";
        };
        fi+=" -";
        std::cout<<"Executing"<<fi;
        std::system(fi.c_str());  
    };
};