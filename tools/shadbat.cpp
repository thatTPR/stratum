#define __cpp_lib_filesystem
#include <string>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
using namespace std;
using fs = std::filesystem;

void write_dir_file(std::filesystem::path dir, char* com ){
    std::string files[1000] ;
    int j =0;
    std::ofstream out(dir.string()+"\\"+dir.stem().string());
    
    for( std::filesystem::path entry : std::filesystem::directory_iterator(dir)){
         if (std::filesystem::is_regular_file(entry)){
            std::string ext = entry.extension().string();
            if (ext.compare("glsl") or ext.compare("hlsl")){
                std::string command;
                command+=com;command+=" ";command+=entry.string();
                system(command.c_str());
                files[j] = entry.stem().string() ; j++;     
                std::ifstream in(entry);
                out<<"char"<<" "<<entry.stem()<<"[]= \"";
                char i;
                while(in>>i){
                    out<<i;
                };
                out<<"\";\n";
            };
        }
    };
   
};
void write_dirs_files(std::filesystem::path* dir , size_t dir_size , char* com){
    for(int i = 0 ; i < dir_size ;i++){
        write_dir_file(dir[i],com);
    };
};
#ifndef STRATA_NO_MAIN
int main( int argc, char* argv[]){
    std::filesystem::path* directories = new std::filesystem::path[argc]; size_t dirs_it = 0;
    if(argc == 1){std::cout<<"shadbat dirs ... -\"glslc|dxc args \"";}
    for ( int i = 1 ; i < argc ; i++){
        if(argv[i][0] == '-'){
            int j=1;
            std::string com;
            
            while (char c = argv[i][j]){
                com =+c; j++;
            };
            com[j]=argv[i][j]; 
            char c[com.length()] ;
            std::strcpy(c, com.c_str());
            
            std::cout<<c;
            write_dirs_files(directories,dirs_it+1,c);
            delete[] directories;
            directories= new std::filesystem::path[argc];
            continue ;
        };
            std::filesystem::path p(argv[i]);
            directories[dirs_it] = p ;dirs_it++ ;
            
        
    };
    return 1;
    
};
#endif