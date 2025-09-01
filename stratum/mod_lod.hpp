#define MOD_LOD_HPP
#ifndef MOD_LOD_HPP

namespace mod {
namespace lod
{
    struct resource {

    };

    template <quality::QUALITY q>
    struct atlas{ // Can contain uv's and a bunch other stuff

        material<Q> image ; 
        
        uint32_t width;
        uint32_t height;

        uint64_t widthFull;
        uint64_t heightFull;
        size_t lod ; // How many downscalings are there 
        

        glm::uvec2 getLODuv(uint ind ){ // Order Down,right,

        };
        glm::uvec2 getSetuv(uint ind){

        };
        loadMaterial(){
            
        };
       
        void lod(material<Q> im){ // TODO in lod systems there is a a progrssively lower resolution. Everything is placed below the image
            
        };        
        atlas(std::path p , std::vector<std::pair<size_t , size_t> > sizes ) :  p(p) , sizes(sizes) {};
    };
    class file_atlas {
        std::vector<atlas> atlases;
    };
   
    struct lod {
        void 
    };
    
    enum LOD {
        Normal,
        Imposter, // Looks like 3d image but always gets rendered at same angle not size though
        Sprite, // Simmillar to imposter but is not 3d in any way 
    
    } LOD;
    void makeImposter();
    void makeSprite(){};
    void makeSprieFan(){};

    template <DIM d,quality::QUALITY q, template <template <DIM ,quality::QUALITY >> typename T>
    struct qdlod {
       
        T<d,q>& original;
        std::vector<T<d,q>> sub;
        template <DIM d,quality::QUALITY q>
        void LodSys(uint8_t s){
            T<d,q> original.Lod(s);
        };
    }
    template <DIM d, template <template <DIM ,>> typename T>
    struct dlod {
       
        T<d>& original;
        std::vector<T<d>> sub;
        template <DIM d>
        void LodSys(uint8_t s){
            T<d> original.Lod(s);
        };
    }
    template <quality::QUALITY q, template <template <quality::QUALITY >> typename T>
    struct dlod {
       
        T<q>& original;
        std::vector<T<q>> sub;
        template <quality::QUALITY q>
        void LodSys(uint8_t s){
             sub.push_back(original.Lod(s));
        };
    }

     

    struct lodSys {
        
    }
};
  
};