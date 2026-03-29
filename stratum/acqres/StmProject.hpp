// xml file format representing strata project strucutre
// Defines plugin dependencies ( and the specific modules )
// Defines local module dependencies
// Assets and atlases
// Scene Files
// Canvases
// 
#ifndef STM_PROJECT_HPP
#define STM_PROJECT_HPP
#include <string>
#include "xml.cpp"
#include "../util/syscanvas.cpp"


namespace StmProject {
    




struct StmProj  : xmlLib{

    typedef std::string capabilty ;
       
    struct plugin {// Has config.json and main.
        std::string name ;
        std::string path;
          enum type {
            shared ,
            script
        };
        type t ;
        
        std::vector<capability> caps; 
    };

    template <>
    struct tag<plugin> {
        plugin data;
        const std::string name = "plugin" ;
        void parse(xmlParser::eltree& tree){
            for(const xmlParser::attribute& at : tree.attributes) {
                switch (at.first){
                    case std::string("path") : {data.path = at.second;}
                    case std::string("name") : {data.name = at.second;}
                    case std::string("cap") : {data.caps.push_back(at.second);}
                    case std::string("type") : {switch(at.second){
                        case std::string("shared") : {t = type::shared;}
                        case std::string("script") : {t = type::script;}
                    }}
                }
            };
        };
    }
    struct asset {
        std::string path;
        enum type {
            image,
            audio,
            video,
            model,
            scene,
            world
        };
        type t;
    };
    
    template <>
    struct tag<asset> {
        plugin data;
        const std::string name = "plugin" ;
        void parse(xmlParser::eltree& tree){
            for(const xmlParser::attribute& at : tree.attributes) {
                switch (at.first){
                    case std::string("name") : {data.name = at.second;}
                    case std::string("type") : {
                        switch(at.second){
                            case std::string("image"):{data.t=asset::type::image;};
                            case std::string("audio"):{data.t=asset::type::audio;};
                            case std::string("video"):{data.t=asset::type::video;};
                            case std::string("model"):{data.t=asset::type::model;};
                            case std::string("scene"):{data.t=asset::type::scene;};
                            case std::string("world"):{data.t=asset::type::world;};
                        }
                    }
                    case std::string("path") : {data.path=at.second;}
                }
            };
        };
    }

    struct lib {
        std::vector<capabilty> caps;
        std::string name ;
        std::string path;
    }
    template <> struct tag<lib> {
        lib data;
        const std::string name = "lib";
        void parse(xmlParser::eltree& tree){
            for(const xmlParser::attribute& at : tree.attributes) {
                switch (at.first){
                    case std::string("name") : {data.name = at.second;}
                    case std::string("cap") : {data.caps.push_back(at.second);}
                    case std::string("path") : {data.path=at.second;}
                }
            };
        };
    }

    struct session {
        struct editorState {
            std::string editorid;
            std::string asset;
        };
        std::vector<>  
    };
    smlLib::elems<plugin,asset,lib> tags;




    std::vector<plugin> plugins;  
    std::vector<asset> assets ; 
    std::vector<lib> libs ;
    std::string name ;

    const std::string 

    

    
    StmProj(std::string path){
        
    };
};



};

#endif