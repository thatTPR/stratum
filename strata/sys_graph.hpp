#include "editor_sys.hpp"
#include "nodes\data_image.hpp"
#include "nodes\data_image.hpp"
#include <type_traits>
#include <string>
#include <iostream>

namespace graph
{
#define PINNED_ALPHA 200
#define TRIGGERED_ALPHA 255
#define UNPINNED_ALPHA 160

    enum pinType {
        Resource =0 // file (fs or net ) 
        Data = 1 ,  // Any sort of data vertex or texture   
        Exec = 2 ,  // lhs executes current ; rhs executes other pin 
        Event = 3 , // lhs or rhs triggers or can trigger 
    };
    class Snode  ;
    class execPin {
        public:
        const std::string name ;
        std::string data ;  // In case of expression ;
        const glm::lowp_uvec4 color_off = {255, 255, 255 , 240} ; 
        const glm::lowp_uvec4 color_on = {255, 255, 255 , 60 } ;
        Snode* parent ; 
        virtual void exec() ;
        eventPin(Snode* N ,const std::string& Name, const std::string& Data  ) : n(N),name(Name), data(Data) {};
        eventPin(Snode* N ,const std::string& Name, const std::string& Data ,  const glm::lowp_uvec4& Color_off,  const glm::lowp_uvec4& Color_on  ) : n(N),name(Name), data(Data),  color_off(Color_off),color_on(Color_on) {};
        eventPin() = default;
    };
    
    // EventPinStart
 
    template<typename T>
    class event { // TODO
        T val; 
        std::string name ;
        event(std::string Name ) name(Name) ; 
    };
    template <typename event> //
    class eventPin{
        if constexpr (!type_traits::is_base_of<event,T>){std::cerr<<"template parameter is not of event type "<<std::endl} ; 
        const std::string name ;
        std::string data ;  // In case of expression ;
        const glm::lowp_uvec4 color_off = {255, 255, 255 , 240} ; 
        const glm::lowp_uvec4 color_on = {255, 255, 255 , 60 } ;
        Snode* parent ; 
        event ev ; 
        eventPin(Snode* N ,const std::string& Name, const std::string& Data  ) : n(N),name(Name), data(Data) {};
        eventPin(Snode* N ,const std::string& Name, const std::string& Data ,  const glm::lowp_uvec4& Color_off,  const glm::lowp_uvec4& Color_on  ) : n(N),name(Name), data(Data),  color_off(Color_off),color_on(Color_on) {};
        eventPin() = default;
    } ;
    
 
    template <struct T>
    class dataPin 
    {
        glm::u8vec4 color;
        std::string name;
        T val;
        bool pinned;
       
        void setData(T d)
        {
            this->data = d;
        }
        dataPin(std::string name)
        {
            this->name = name;
        }
        dataPin(std::string name, color::rgba color)
        {
            this->name = name;
            this->color = color;
        };
        dataPin(std::string name, T val)
        {
            this->name = name;
            this->val = val;
        };
        dataPin(std::string name, T val, color::rgba col)
        {
            this->color = col;
            this->name;
            this->val = val;
        }
    };
/*
 * Base class from which all classes inherit
 */
#define EXEC_COLOR color::rgba(255, 255, 255, 100)
#define EXEC_COLOR_PINNED color::rgba(200, 200, 200, 255)
#define EXEC_COLOR_TRIGGERED color::rgba(240, 240, 200, 255)

    // TODO can inherit from dataPin
    class Snode // TODO async options 
    {

        public:
        std::string name; // Custom name
        execPin mainExec
        std::pair<bool, bool>, void> inExecState;
        std::pair<bool, bool>, void> outExecState;

        std::vector<std::pair<Snode *, bool>> outEx;

        std::vector<dataPin > dataIns;
        std::vector<std::pair<dataPin *, std::pair<Snode *, size_t>>, void> dataOuts;

        // Get executed accordingly, in
        std::vector<void (*actions)()> actions;
        virtual void run()
        {
        }
        template <typename U = T, typename std::enable_if<outExec, U>::type * = nullptr>
        void out()
        {
            this->out->in();
        };
        template <typename U = T, typename std::enable_if<inExec, U>::type * = nullptr>
        void in()
        { // Gets executed when the in execPin is triggered
            this->run();
            out();
        };
        void addDataIns(std::vector<dataPin> dps)
        {
            for (auto i : dps)
            {
                this->dataIns.push_back(i);
            }
        };
        void addDataOuts(std::vector<dataPin> dps)
        {
            for (auto i : dps)
            {
                this->dataOuts.push_back(i);
            }
        };

        Snode(std::string n)
        {
            this->name = n;
        }
        Snode(std::array<dataPin> dataIns , std::array<dataPin> dataOuts ){
            
        }
    };



   
