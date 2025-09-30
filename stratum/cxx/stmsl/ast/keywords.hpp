#ifndef STMSL_KW
#define STMSL_KW
#include "ast.hpp"

namespace stmsl{
enum pcntxt {
    global,
    funcblock,
    funcargs,
    parameterlist,
    declType,
    
}


template <pcntxt pc,pcntxt... pcs >
struct context_tuple {
    static constexpr pcntxt pcs[] = {pc,pcs...};

    struct iter {
        size_t s;
        pcntxt operator*(){return s<=sizeof...(pcs)?pcs[s]:pcs[0];}
        decltype(*this) operator++(){s++;return *this;}
        iter(size_t _s): s(_s){}
    };
    constexpr iter begin(){return iter(0);}
    constexpr iter end(){return iter(sizeof...(pcs)+1);}
    constexpr pcntxt operator[](size_t i){return pcs[i];}
};
template <pcntxt pc,pcntxt... pcs>
struct kw : context_tuple<pc,pcs...> {
    const std::string name;
    bool check(stmsl_parser& p){
        for(pcntxt it : *this){
            if(it==p.cntxt){return true;}
        };
        return false;
    }
    void proc(stmsl_parser& p){

    }
};

#define KW_LIST 
#define KW_N(name,sname, cntxt,...) struct name : kw<cntxt,__VA_ARGS__> {const std::string name = sname;void proc(smtsl_parser& p) ;}; \
#define KW_LIST KW_LIST, name

KW_N(kw_Incl,"#include",global)
#define KW_LIST kw_Incl 
void kw_Incl::proc(stmsl_parser& p){
    std::string s=p.untilEOL();
    std::string name;
    for(i=0;i<s.length() and s[i]==' ';i++){}
    for(i=0;i<s.length() and s[i]!=' ';i++){name+=line[i];}
    std::string str = name.substr(1,name.length()-2);
    if(name[0]=='<'){if(name[name.length()-1]=='>'){
        std::filesystem::path pth;
            if(p.pushRel(str,&pth)){
                ast<meta> Ast;
                ast<meta>& curTU = ast_stack.back();
                if(CPHU && cph(pth,&Ast)){curTU.include(Ast);}
                else {cphAst = p.include(pth);curTU.include(Ast);}
        }
        else {std::err<<"error on line "<<p.line<<"Expected closing \'>\' in include statement:\n"<<p.line<<std::endl}}
    else{ if(name[name.length()-1]=='\"'){
            p.pushRelcwd(str);}
        else {std::err<<"error on line "<<p.line<<"Expected closing \'\"\' in include statement:\n"<<p.line<<std::endl}}

    }
};

KW_N(kw_Define,"#define",global) 
void kw_Define::proc(stmsl_parser& p){
    std::string s=p.untilEOL();
    std::string name ;std::string value;size_t i;
    for(i=0;i<s.length() and s[i]==' ';i++){}
    for(i=0;i<s.length() and s[i]!=' ';i++){name+=line[i];}
    for(i=0;i<s.length() ;i++){value+=line[i];}
    macros.push(macro(name,value));
};
KW_N(kw_if,"#if",global)
void kw_if::proc(stmsl_parser& p){
    expr<meta> Ex = p.parse(p.untilEOL());
    p.cast.push_back(tu<meta>(Ex));
};
KW_N(kw_else,"#else",global)
KW_N(kw_elif,"#elif",global)
KW_N(kw_elifdef,"#elifdef",global)
KW_N(kw_endif,"#endif",global)

KW_N(kw_ifndef,"#ifndef",global)
void kw_ifndef::proc(stmsl_parser& p){
    std::string str=p.untilEOL();
    std::string s;for(size_t i=0;i<str.length();i++){
        if(str[i]!=' '){size_t p=str.find_first_of(" ");
            if(p!=std::string::npos){s=str.substr(i,p-i+1);break;};
            else {s.str.substr(i);}
        }
    } ;
    bool found=false;
    for(macro mit : macros.mlist){
        if(mit.name==s){found=true;break;}
    };
    if(found){
        p.cast.push_back(tu<meta>(expr<meta>(true)))
    }
    else {p.untilKWs<kw_else,kw_elif,kw_elifdef,kw_endif>();}
}

KW_N(kw_ifdef,"#ifdef",global)
void kw_ifdef::proc(stmsl_parser& p){
    
};


KW_N(kw_Layout,"layout")
void kw_Layout::proc(stmsl_parser& p){
    
};
KW_N(kw_Location,"location")
KW_N(kw_Binding,"binding")
KW_N(kw_uniform,"uniform")
KW_N(kw_in,"in")
KW_N(kw_out,"out")
KW_N(kw_inout,"inout")
void kw_inout::proc(stmsl_parser& p){
    
};

KW_N(kw_Buffer,"buffer")
KW_N(kw_Image2D,"image2D")
KW_N(kw_Image3D,"image3D")
KW_N(kw_Sampler,"sampler")
KW_N(kw_Void,"void")
KW_N(kw_Float,"float")
KW_N(kw_Int,"int")
KW_N(kw_Uint,"uint")
KW_N(kw_Bool,"bool")
KW_N(kw_Vec,"vec")
KW_N(kw_Mat,"mat")
KW_N(kw_Ivec,"ivec")
KW_N(kw_Imat,"imat")
KW_N(kw_Uvec,"uvec")
KW_N(kw_Umat,"umat")
KW_N(kw_Bvec,"bvec")
KW_N(kw_Bmat,"bmat")
KW_N(kw_Flat,"flat")
KW_N(kw_Const,"const")
KW_N(kw_Template,"template") 
KW_N(kw_Typename,"typename")
KW_N(kw_Constexpr,"constexpr") 
KW_N(kw_While,"while") 
KW_N(kw_For,"for") 
KW_N(kw_If,"if")  
KW_N(kw_Else,"else")  
KW_N(kw_Switch,"switch")
KW_N(kw_Case,"switch")

}
#endif