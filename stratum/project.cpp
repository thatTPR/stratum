#pragma once
#include <system>
#include "util/sys.cpp"

namespace strata {

    class shared {
        std::string name ;
    };
    class module {
        std::string name ;
    };       

#define USER_SETTINGS
#include "../lib/sei_settings.hpp"
             
            SeiProjSetCondition : stng_condition {
            
                // plugins, // List link of plugins <plugins="lnk1", "lnk2".. >
                // name,

           

             };
            class SeiProjSet : sei_settings
            {

                bool _3d;
                bool _2d;
                bool _app;

                std::string file;
                Spreset pres;
                XR xr;

                std::string name;
                std::string authorName;
                std::array<std::string> plugins;

                std::vector<std::string> modelsPaths ;
                std::vector<std::string> imagesPaths ;
                std::vector<std::string> gltfs ;

                std::vector<std::string> externalImports ;

                std::vector<std::string> nodes;

                

                setDefaults()
                {
                }
                void parseSettings()
                {
                    std::map<std::string, boost::json::value::kind> tags = {
                    "name", boost::json::value::kind::string};
                    std::ifstream f(this->file);
                    if (!f.is_open())
                    {
                        std::string jsonString(this->setDefaults());
                    }
                    else
                    {
                        std::string jsonString((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
                    }
                    f.close();
                    try
                    {

                        json::value jv = json::parse(jsonString);
                        delete jsonString;
                    }
                    catch (const std::exception &e)
                    {
                        strata::Logging("ProjectSettings.json Parsing error: " + e.what());
                        return 1;
                    }
                }
                projectSettings() override{

                };
            };

            class SeiProject
            {
                std::string path;

                SeiProjSet settings;

                bool reloading;
                bool compiling;
                std::vector<std::pair<shared, bool>>  compiledShared;
                std::vector<std::pair<modules, bool>> compiledModules ; 
                
                
                typedef bool changed;
                std::vector<std::string, bool> content;

                
                bool resourcesChanged(){

                };
                  enum Mode {
            DebugAll   // Build both engine and user code in debug mode
            DebugGame, // In this mode debugging engine is built in optimised mode and  game code is built in debug 
            Develop,  // Medium optimisation nothing built in debug mode
            Testing   // Built with enabled stats , profiling , and console command enabled 
            Release, // For release mode 
            } ;

                #include <../inc/codesys.hpp>
                std::string getCxxDebugAll(){
                    
                };    
                std::string getCxxDebugGame();
                std::string getCxxDevelop();
                std::string getCxxTesting();
                std::string getCxxRel();

                void cxxCompile(){

                }
                enum compileTargets
                {
                    Editor,
                    Client,
                    Server,
                };
                void run()
                {
                }
                void save()
                { // Saves project settings and references to ProjectName.Sproject (json file format)
                }
                void saveSettings(){

                };
                void hotReload()
                { // hot reload detected
                    this->reloading = true;
                };
                void hotReloadEnded()
                {
                    this->reloading = false ;
                }

                void projectParse(std::string name){

                };
                void searchProject()
                {
                }

                project(std::string ProjectPath, std::string name)
                {

                    this->Log = StrataLog();

                    std::ifstream in;
                    in.open(projectPath++ name);
                    if (!in.is_open())
                    {
                    }
                };
            }
}
