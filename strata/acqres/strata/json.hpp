
#include <string>

enum jsonval{
    none,
    stri,
    intgr,
    dble,
    stri,
    arr,
    obj,
};
template <jsonval v> 
struct jsonval_t {
    using type = std::conditional<v==jsonval::intgr, int ,
                 std::conditional<v==jsonval::dble, dble ,
                 std::conditional<v==jsonval::uri, std::string ,
                 std::conditional<v==jsonval::stri, std::string , void>::type>,void>::type>,void>::type>
                 
};
    typedef union jsonvalu{
        int i;
        double dbl;
        std::string str;
    } jsonvalu;


class jsonvalue {
    public:
    jsonval valty;
    jsonvalu val;
    
    jsonvalue get(size_t pos,std::string s){
        std::string v;
        size_t pos = s.find_first_of(":");
        size_t pos1=s.find_first_of("\"",pos+1);
        size_t pos2=s.find_first_of("\"",pos1+1);
        if(s[pos] == '\"'){
            for(size_t i = pos;(s[i]!="\"") and (s[i-1]!="\\");i++){v+=s[i];};
            this->valty = jsonval::stri;};
            this->val->str = v; return *this;
            for(size_t i = pos;(v[i]!=" ");i++){v+=s[i];};
            size_t p = v.find_first_of(".");
            if(!p){p=v.end();}
            double dbl;
                int pow=1;
                for(size_t i = p ; i<v.begin();i--){ dbl+=pow*(v[i] - "0");pow=pow*10; };
            if(p){
                pow=1;
                for(size_t i = p ; i<v.end();i++){ pow=pow/10;dbl+=pow*(v[i] - "0"); };
            };
            return dbl;
            return *this;
        };
        
    
    
    template <jsonval v> 
    jsonval_t<v>::type get(bool names, size_t pos,std::string s){
        jsonval_t<v>::type res;
        jsonvalue t = get(pos,s);
        if(t.valty==valty::v){
            switch(t.valty){
                case valt::intgr : { res = t.val.in};
                case valt::dble : { res = t.val.dbl};
                case valt::stri : { res = t.val.str};
            };
        };
        return res;
    }; 
    void put(ostream fs){
        switch(this->valty){
            case jsonval::intgr : {fs<<this->val.i;};
            case jsonval::dble : {fs<<this->val.dbl;};
            case jsonval::uri : {fs<<"\""<<this->val.str<<"\"";};
            case jsonval::stri : {fs<<"\""<<this->val.str<<"\"";};
        };
    };
};


class json_parser {
    public:
    ifstream f;
    size_t p ;
    std::string cur;
    void pos_reset(this->p=0;);
    bool nline(){(this->f)>>(this->cur);this->pos_reset();};
    bool operator bool(){return this->nline();};
    bool operator>>(std::string& s){(this->f)>>cur;s=this->cur;};
    bool pos_first_of(std::string n){
        size_t po = this->cur.find_first_of(n,this->p);
        if(po!=this->cur.npos){this->p=p;return true};
        else return false;
    };
    bool brace_start(){return ((this->cur.npos) != this->cur.find_first_of("["));};
      bool brace_end(){return ((this->cur.npos) != this->cur.find_first_of("]"));};
    bool brack_start(){return ((this->cur.npos) != this->cur.find_first_of("{"));};
      bool brack_end(){return ((this->cur.npos) != this->cur.find_first_of("}"));};
          bool comma(){return ((this->cur.npos) != this->cur.find_first_of(","));};

    bool pos_brace_start(){return this->pos_first_of("[")};
      bool pos_brace_end(){return this->pos_first_of("]")};
    bool pos_brack_start(){return this->pos_first_of("{");};
      bool pos_brack_end(){return this->pos_first_of("}");};
          bool pos_comma(){return this->pos_first_of(",");};

    void pos_name(std::string s){
        size_t po= this->cur.find_first_of()
    };
    void name_s_in_line(std::string s){

    };
    void feed_obj(){

    };
    void feed_arr(){

    };
    void feed(){

    };
};


#include <regex>
void regex(){

};