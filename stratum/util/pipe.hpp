// Pipeline management 
// Plugin integration.

class shader {

};


template <class o , shader s>
class Stage {
    obj d ; 
    virtual init() ;
    virtual run() ; 
};
class stageStruct {

};
template<stageStruct obj>
class FixedFunctionStage { // Fixed Function Stage
    obj ;
    virtual void init();
    virtual void decouple() ;
};
template <class o , shader s >
class ShaderStage { // ShaderStage
    virtual void init();
    virtual void decouple();
};

template <>
class Resource {
    Resource(){

    };
};
class StageObject {
   
};
class PipeLine {

};
class NoPipeLine : PipeLine {

};
class RenderEngine {
    std::vector<PipeLine> pipelines; 
    std::vector<>
};