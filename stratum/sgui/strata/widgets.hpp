#include <sgui/sgui.hpp>
#include <sgui/strata/nodes.hpp>
template <typename T>
struct treeEntry ;


struct treeEntry<texture::textureInfo> ;
struct treeEntry<texture::texture> ;
struct treeEntry<lod::atlas> ;
struct treeEntry<lod::file_atlas> ;
struct treeEntry<lod::> ;// TODO


template <class node>
struct sideBarFromNode : public widget{
    node::inevtup in_event_pins;
    node::inrestup in_res_pins;
    node::inmodtup in_mod_pins;

    node::outevtup ot_event_pins;
    node::outrestup out_mod_pins;
    node::outmodtup out_mod_pins;


};


struct timeLineTab : public widget {

};
template <class node>
struct timelineTabFromNode : public timeLineTab {

};