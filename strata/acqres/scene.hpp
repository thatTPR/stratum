#include <acqres/source.hpp>

#include <acqres/vg2.hpp>
struct scene {

};

class scene_prop : public aqres_prop{
    public:
    std::vector<std::string> extensions;
    std::vector<aq_resprop> image_props;
    std::vector<aq_resprop> model_props;
    std::vector<aq_resprop> node;
    std::vector<std::string> get_used_ext(){
        for(aq_resprop s: this->model_props  )
    };
    void loadfile(std::string path) {

    };
};