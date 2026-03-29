#include <sgui/sgui.hpp>
#include <sgui/strata/nodes.hpp>
template <typename T>
struct treeEntry ;


struct treeEntry<texture::textureInfo> ;
struct treeEntry<texture::texture> ;
struct treeEntry<lod::atlas> ;
struct treeEntry<lod::file_atlas> ;
struct treeEntry<lod::> ;// TODO


class sideBarNodeInput {
    

    
    sideBar(node n ){

    };
};


struct timeLineTab : public widget {

};
template <class node>
struct timelineTabFromNode : public timeLineTab {

};