#ifndef JSON_HPP
#define JSON_HPP
#include <string>
#include <vector>
#include <fstream>
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
    typedef std::vector<jsonvalue> jsonarr ;
    typedef std::map<std::string,jsonvalue> jsonobj;
     typedef union jsonvalu{
        int i;
        float flt;
        std::string str;
        void Null ;
        bool Bool;
        jsonobj* val ;
        jsonarr arr;
    } jsonvalu;
    std::string id ;
    jsonvalu val;
    jsonvalt valt = jsonvalue::obj ;

    void read(std::string& s){
        if(s[0] == '\"'){
            valt = jsonvalt::stri;
            val.str = s;
        }
        else (s.find(".")!=std::string::npos) {
                valt= jsonvalt::flt;
                val.flt = std::stof(s);
        }
        else (s.find("null")!=std::string::npos){
            valt = jsonvalt::Null;
        }
        else (s.find("true")!=std::string::npos){
            valt = jsonvalt::Bool;
            val.Bool = true;
        }
        else(s.find("false")!=std::string::npos){
            valt= jsonvalt::Bool;
            val.Bool = false;
        }
        else {
            valt = jsonvalt::intgr;
            val.i = std::stoi(s);
        };

    };
    auto get(){
        switch(valty){
            case jsonvalt::Bool: {return val.Bool}
            case jsonvalt::intgr: {return val.i;};
            case jsonvalt::flt: {return val.flt;};
            case jsonvalt::stri: {return val.str;};
            case jsonvalt::arr: {return val.arr;};
            case jsonvalt::obj: {return val.val;};
        }; 
        return "null";
    };
    void put(ofstream& fs){
        switch(this->valty){
            case jsonvalt::none : {fs<<"null";};
            case jsonvalt::Bool : {if(val.Bool){*fs<<"true";}else {fs<<"false";};};
            case jsonvalt::intgr : {fs<<val.i;};
            case jsonvalt::flt : {fs<<val.flt;};
            case jsonvalt::stri : {fs<<val.stri;};
            case jsonvalt::arr : {
                fs<<"[";
                val.arr[0].put(fs);
                for(int i = 1; i<val.arr.size();i++ ){
                    fs<<"," ;
                    if(val.arr[i-1].valty == jsonval::obj){fs<<std::endl;};
                    if(val.arr[i].valty == jsonval::obj){
                        fs<<std::endl;
                    }
                    val.arr[i].put(fs);
                };
                fs<<"]"<<std::endl;
            };
            case jsonvalt::obj : {
                val.val.put(fs);
            };
        };
        fs<<",";
        
    };
};


class json_parser {
    public:
    jsonvalue::jsonobj val; 

    pri::stack<jsonvalue*> cur ;
    ifstream f;
    size_t p ;
    std::string line ;
    std::ifstream* filein;

    std::string value ;
    bool startValue = true ;
    bool startStr(){return cur.top()->valt==jsonvalue::jsonvalt::stri;}
    bool startObj(){return cur.top()->valt==jsonvalue::jsonvalt::obj;} 
    bool startArr(){cur.top()->valt==jsonvalue::jsonvalt::arr;};
    std::string line;
    void pushArr(){
        cur.top()->val.arr.push_back(jsonvalue());
        cur.push(&cur.top()->val.arr.back());
    };
    void feed(){
        for(int i =0 ; i<line.size();i++){
            if(line[i] == ':') { cur.top().id=value;startValue = true;value = std::string();continue;};
            if(line[i] == '"')  { 
                    if(startStr() ) {if( line[i-1] == '\\')
                                    else {  
                        if(!startValue){cur.top()->val.arr.top().val.str = value;
                        }
                        else {
                            cur.top()->val.str = value;}
                    };}
                    else  { cur.top()->valt =jsonvalue::jsonvalt::str;};
                    
                };
            if(line[i] == '{')  { 
                cur.top()->valt=jsonvalue::jsonvalt::obj;
            }
            if(line[i] == '}')  { cur.pop();}
                    
                
            if(line[i] == '[') {
                cur.top()->valt=jsonvalue::jsonvalt::arr;
                pushArr();
                };
            if(line[i] == ']')  {startValue=false;
                cur.pop()};
            if(line[i] == ',')  {
                cur.pop();
                if(startArr()){
                    pushArr();
                    continue;
                };
                startValue = false;
            };
            if(isspace(line[i])){
                if(startStr()){value+=line[i];continue;};
                if(startValue  ){
                    if(value.size()>0){
                        cur.top()->read(value); 
                        cur.pop(); 
                    };
                };
                if(cur.top()->valty == jsonvalue::jsonvalt::stri){
                    cur->ptr->val.str+=line[i];
                };
            }
            else {
                if(startStr() || startValue ){value+=line[i];continue;}
                else if(startObj()){value+=line[i];}
                else if(startArr()){value+=line[i];}
            }
        };
    }
    bool feedLine(){
        if(std::getline(*filein,line)){
            feed(line);
            return true;};
        return false;
    };
    void parse(std::ifstream* file){
        filein = file;
        while(feedLine())
    };
}




#endif