
namespace graph {
 // This class cannot be extended since it is part of the node editor subsystem, no extensions can be done on this class
    class Sgraph 
    { 
        std::string name;
        std::string category;
       
        vector<Snode> nodes; // All the nodes in the
        // TODO so it takes into account value previews ( in the case of textures ) and multiLine pin sizes ;

        // Not forget
        void getPinPos(Snode node, uint indDataPinIn){

        };
        void calculateNodeSize(sNode *node, uint FontSize, )
        {
            this->size = 0;
            uint w = 0;
            uint h = 0;
            if (typeof(node->inExecState) == typeof(void))
            {
            }
        };
        void autoOrganise()
        {
            // sort vector based on connections
            for (const auto &i : nodes)
            {
                calci->first
            }
            // Make sure they are clean
        };
        void optimize(){

        };
        void render(){

        };
        void preview(){

        };
        void setSize(uint fontSize)
        {
            this->size;
        };
        void update(uint fontSize){

        };
        void bake(){

        };
        void compiler(){

        };
        Sgraph(std::vector<Snode> graph, uint fontSize)
        {
            setSize(fontSize)
        }
    }
}