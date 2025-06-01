#ifndef JSON_HPP
#define JSON_HPP
#include <string>
#include <vector>
#include <map>
#include <petri/stack.hpp>
#include <stack>
class jsonvalue {
    public:
enum jsonvalt{
    none,
    intgr,
    Bool,
    flt,
    stri,
    arr,
    obj,
};
    typedef std::vector<jsonval> jsonarr ;
    typedef std::map<std::string,jsonvalue> jsonobj;
     typedef union jsonvalu{
        int i;
        float flt;
        std::string str;
        void Null ;
        bool Bool;
        jsonobj* val ;
        jsonarr* arr;
    } jsonvalu;
    std::string id ;
    jsonvalu val;
    jsonvalt valty ;

    void read(std::string& s){
        if(s[0] == '\"'){
            valty = jsonvalt::stri;
            val.str = s;
        }
        else (s.find(".")) {
                valty= jsonvalt::flt;
                val.flt = std::stof(s);
        }
        else (s.find("null")){
            valty = jsonvalt::Null;
        }
        else (s.find("true")){
            valty = jsonvalt::Bool;
            val.Bool = true;
        }
        else(s.find("false")){
            valty= jsonvalt::Bool;
            val.Bool = false;
        }
        else {
            valty = jsonvalt::intgr;
            val.i = std::stoi(s);
        };

    };
    auto get(jsonvalue vl){
        switch(valty){
            case jsonvalt::Bool: {return val.Bool}
            case jsonvalt::intgr: {return val.i;};
            case jsonvalt::flt: {return val.flt;};
            case jsonvalt::stri: {return val.str;};
            case jsonvalt::arr: {return val.val;};
            case jsonvalt::obj: {return val.val;};
            case jsonvalt::arr : {return val.arr;}
        }; 
        return "null";
    };
    void put(ofstream* fs){
        switch(this->valty){
            case jsonvalt::none : {*fs<<"null";};
            case jsonvalt::Bool : {if(val.Bool){*fs<<"true";}else {*fs<<"false";};};
            case jsonvalt::intgr : {*fs<<val.i;};
            case jsonvalt::flt : {*fs<<val.flt;};
            case jsonvalt::stri : {*fs<<val.stri;};
            case jsonvalt::arr : {
                *fs<<"[";
                val.arr[0].put(fs);
                for(int i = 1; i<val.arr.size();i++ ){
                    *fs<<"," ;
                    if(val.arr[i-1].valty == jsonval::obj){*fs<<std::endl;};
                    if(val.arr[i].valty == jsonval::obj){
                        *fs<<std::endl;
                    }
                    val.arr[i].put(fs);
                };
                *fs<<"]"<<std::endl;
            };
            case jsonvalt::obj : {
                val.val.put(fs);
            };
        };
        *fs<<",";
        
    };
};


class json_parser {
    public:
    jsonvalue::jsonobj val; 

    stack<jsonvalue*> cur ;
    ifstream f;
    size_t p ;
    std::string line ;
    std::ifstream* filein;

    void pushArr(){
        cur.back()->val.arr.push_back(jsonvalue());
        cur.push(&(cur.back()->val));
    };
    std::string value ;
    bool startValue = true ;
    bool startArr = false ;
    bool startStr = false;
    void feed(std::string line){
        for(int i =0 ; i<line.size();i++){
            
            if(line[i] == ':') { startValue = true;continue;};
            if(line[i] == '"')  { 
                    if(startStr and  line[i-1] == '\\') {value+='"';}
                    else (!startStr) {startStr = true; value=std::string()+'"';};
                    else {  startStr = false;
                        if(!startValue){cur.back()->val.val[value] = NULL;
                            cur.push(&(cur.back()->val));
                        }
                        else {
                            cur.back()->val.stri = value+'"';startStr=false;}
                    };
                    if(startValue && (startStr == false)){
                        cur.back()->valt =jsonvalue::jsonvalt::str;
                        cur.back()->val.str = value; startStr=true;
                    };
                };
            if(line[i] == '{')  { startValue = true;
                cur.back()->valt=jsonvalue::jsonvalt::obj;
            }
            if(line[i] == '}')  { startValue = false;cur.pop();}
                    
                };
            if(line[i] == '[') {
                cur.back()->valt=jsonvalue::jsonvalt::arr;
                pushArr();
                startArr = true;};
            if(line[i] == ']')  {
                startArr = false;cur.pop()};
            if(line[i] == ',')  {
                if(startArr){
                    cur.pop();
                    pushArr();
                    continue;
                };
                startValue = false;
            };

            if(isspace(line[i])){
                if(startStr){value+=line[i];continue;};
                if(startValue  ){
                    if(value.size()>0){
                        cur.back()->read(value); 
                        cur.pop(); 
                    };
                };
                if(cur->ptr->valty == jsonvalue::jsonvalt::stri and startStr){
                    cur->ptr->val.str+=line[i];
                };
            }
            else {
                if(startStr || startValue){value+=line[i];continue;}
                    value+=line[i];
            }
            

        };

    bool feed(){
        if(std::getline(*filein,line)){
            feed(line);
            return true;};
        return false;
    };
    void parse(std::ifstream* file){
        filein = file;
        while(feed())
    };


};


#endif