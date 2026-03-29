#pragma once
#include <cctype>
#include <string>
#include <list>
#include <stack>



class yamlParser {

    template <pri::Str s, typename T>
    struct dtypes : pri::CEStr<s>{using type = T;static virtual void parse(std::string& str,size_t& p) ; static virtual std::string str(dtype& dt){}};
    struct Boolean : dtype<"Boolean",bool> ;

    struct Integer : dtype<"Integer",int>{
        type parse(std::string& str,size_t& p)override{type res;
            for(;str[p]==' ';++p){};
            for(;str[p]>='0' and str[p]<'9';++p){res+=str[p]-'0';}
            return res;
        }
        std::string str(type& p) override{return std::string(p);}
    };
    struct Float : dtype<"Float",float>{
        type parse(std::string& str,size_t& p)override{type res;
            for(;str[p]==' ';++p){};
            for(;str[p]>='0' and str[p]<'9';++p){res+=str[p]-'0';}
            if(str[p]=='.'){size_t c=0;++p;
                for(;str[p]>='0' and str[p]<'9';++p){res+=str[p]-'0';++c;}
                for(;c>0;--c){res/=10;}
            }
            return res;
            }
        std::string str(type& p) override{return std::string(p);}
    };
    struct Boolean : dtype<"Boolean",Bool>{
            type parse(std::string& str,size_t& p)override{type res;
                            for(;str[p]==' ';++p){};
                std::string s;
                for(;str[p]!=' ';++p){s+=str[p];};
                for(;str[p]!=' ';++p){s+=str[p];};
            };
            std::string str(type& p) override { return p? std::string("true") : std::to_string("false");}
    };
    struct date {uint16_t year;uint8_t month,day;};
    struct Date : dtype<"Date",date>{
        type parse(std::string& str,size_t& p)override{type res;
            for(;str[p]==' ';++p){};
            for(;str[p]>='0' and str[p]<'9';++p){res.year+=str[p]-'0';}
            for(++p;str[p]>='0' and str[p]<'9';++p){res.month+=str[p]-'0';}
            for(++p;str[p]>='0' and str[p]<'9';++p){res.day+=str[p]-'0';}
        };
        std::string str(type& p) override {return std::to_str(p.year) + std::to_str(p.month)+std::to_str(p.day);}
    };
    struct datetime : date {uint8_t hour,min,sec,ms;
    };
    struct Datetime : dtype<"Datetime",int>{
                type parse(std::string& str,size_t& p)override{type res;
            res=data::parse(str,p);
            // if(str[p] == 'T'){++};
            for(++p;str[p]>='0' and str[p]<'9';++p){res.hour+=str[p]-'0';}
            for(++p;str[p]>='0' and str[p]<'9';++p){res.min+=str[p]-'0';}
            for(++p;str[p]>='0' and str[p]<'9';++p){res.sec+=str[p]-'0';}
            for(++p;str[p]>='0' and str[p]<'9';++p){res.ms+=str[p]-'0';}
            return res;
        };
        std::string str() override{return date::str()+std::to_str(p.hour)+std::to_str(p.min)+std::to_str(p.sec)+std::to_str(p.ms);}
    

    };


    struct elem {
        std::string name ; 
        union {
            NSC list<elem> els;
            Integer::type Int;
            Float::type flt;
            Boolean::type Bool;
            Date::type _Date;
            std::string str;
            Datetime::type _Datetime;
        } ;
        enum ty {eFlt,eInt,eBool,eDate,eDatetime ,estr};ty t;

        template < typename T>
        elem(std::string _name , T v) {name = _name;
            if constexpr (std::is_same<T,int>::value){t=eInt;Int=v;}
            if constexpr (std::is_same<T,float>::value) {flt=v;t = eFlt;};
            if constexpr (std::is_same<T,bool>::value) {Bool=v;t = eBool;};
            if constexpr (std::is_same<T,date>::value) {_Date=v;t = eDate;};
            if constexpr (std::is_same<T,float>::value) {_Datetime=v;t = eDatetime;};
            if constexpr (std::is_same<T,std::string>::value) {str=v;t = estr;};
        };
    };

std::string line;
    stack<elem*> cur ;
    elem& curr(){return &(cur.top());};
    void endNode() {}

    
    void startNode(std::string& nmme) [curr.emplace_back(name) ;cur.push(&(curr.back()));   ]
    void endtNode() [cur.pop(); ]
    void addNode(std::string name,std::string val) {
        if(val == Boolean::str()){curr.els.emplace_back(name,Boolean::parse(val));}
        else if(val == Float::str()){curr.els.emplace_back(name,Float::parse(val));}
        else if(val == Integer::str()){curr.els.emplace_back(name,Integer::parse(val));}
        else if(val == Date::str()){curr.els.emplace_back(name,Date::parse(val));}
        else if(val == Datetime::str()){curr.els.emplace_back(name,Datetime::parse(val));}
        else {curr.els.emplace_back(name,str);}        
    };
    void feed(){
        size_t p=0 ;
        for(;line[p]==' ';++p){};
        std::string name;
        for(;std::isalnum(line[p]) ;++p){name+=line[p];};
        for(;line[p]==' ';++p){}
        std::string val ;
        if(line[p]==':'){
            for(++p;line[p]==' ';++p){}
            for(++p;line[p]!='\n';++p){val+=line[p];}
            if (val.size()>0){addNode(name,val)}
            else {startNode(name);};
        };
    };  

    
    void read(std::ifstream& fst){
        while(std::getline(fst,line)) {feed();}
    }
    
};