#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <queue>
namespace xml {
using namespace std;
class xml_parse;
    class xmln{
    public:
    size_t depth ;

    string name ;
    string val ;
    std::vector<xmln> els;
    std::map<string,string> ats;
    xmln* par ; 
    
    // xmln(xmln* element){
    //     this->name = element->name;  // Tag name (e.g., "div", "p")
    //     this->val = element->val;  // Text content (without leading/trailing whitespace)
    //     // print(this->val)
    //     this->ats = element->ats ; // Attributes (as a dictionary)
        
    //     // Initialize the parent and children attributes
    //     this->par = element->par;  // Parent element
    //     for (int i= 0 ; i < element->els.size() ; i++ ){
    //         xmln* pt = &(element->els[i]);
    //      this->els.emplace_back(pt);
    //     };
    //     delete element;
    // };
    // xmln(xmln& element){
    //     // this->element = element
        
    //     // Initialize the member variables
    //     this->name = element.name;  // Tag name (e.g., "div", "p")
    //     this->val = element.val;  // Text content (without leading/trailing whitespace)
    //     // print(this->val)
    //     this->ats = element.ats ; // Attributes (as a dictionary)
        
    //     // Initialize the parent and children attributes
    //     this->par = element.par;  // Parent element
    //     for (xmln& child : element.els){
    //      this->els.emplace_back(&child);
    //     };    
    // };
    xmln(){};
    xmln(std::string _name , std::map<std::string,std::string> _ats ,std::string _val){
  this->name = _name ;
        this->ats= _ats ; 
    this->val = _val ;
    };
    xmln(std::string _name, std::map<std::string,std::string> _ats) {
        this->name = _name ;
        this->ats= _ats ; 
    };
    xmln(std::string _name) :name(_name){};
    // xmln(std::string& s_){
    //     xml_parse prs = new xml_parse(0x1);
    //     xmln x = new xmln();
    //     x = prs.from_str(s_);
    //     return x;
    // };
    //  xmln& operator=(const xmln& other) {
    //     return *this;  // Return the current object to allow chaining
    // };
    void set_parents(){
        for(xmln& s : this->els ){
            s.par = this ;
            s.set_parents();
        };
    };
    xmln* operator[](int in){
        return &(this->els[in]);
    };

    bool operator==( xmln& ob ){
        if (this->name == ob.name) {return true;};
        return false ;
    };
    // void soft_neq_name_ats(xmln& _ob, xmln& ob){
    //     bool b_name = true;
    //     bool b_ats = true;
    //     try{
    //         b_name =ob.name == _ob.name;
    //         for (const auto std::pair<std::string,std::string >& t : ob.ats  ){
    //                 b_ats = _ob.ats[k] == t. }
    //     }
    //     catch (std::excpetion& e)  {
    //         std::cout<<"softneq excpetion:"<<e<<std::endl;
    //     }
    //     return ((not b_name) and (not b_ats))
    // };
    
    // void should_exclude(xmln element,std::map<std::string,std::string> exclusions){
    //     //Check if an element should be excluded based on name and attributes.//
    //     if (exclusions.size == 0)
    //         return false
    //     for (auto const exclusion : exclusions){
    //         name_b = true
    //         attributes_b = true
    //         try:
    //             if isinstance(exclusion, dict):  // Ensure exclusions are dicts
    //                 name_b = exclusion.get("name") == element.name
    //                 attributes_b = all(element.ats.get(attr) == value for attr, value in exclusion.get("attributes", {}).items())
    //             if name_b and attributes_b:
    //                 return true
    //         except Exception as e : 
    //             print(f"Keynot found:{e}");};
    //     return false
    // }
    // std::string get_val_rec( xmln& element){
    //     std::vector<std::string> vec ;  
    //     // values.append(s)
    //     for (const auto c : element.els ){
    //         t = c.get_val_rec(c)
    //         if (t) {values+=return c.val?c.val:"" + t;}
    //         else values+=return c.val?c.val:"" + t;};
    //     return values 
    // };
    // std::string get_values_rec_incl(xmln& element, bool(*should_incl)(xmln&) ){
        
    //     if ((should_incl(element) )   and (element.ats["visited"] != "visited")){
    //         element.ats["visited"] = "visited"
    //         std::string values="";
    //         if(element.val){
    //             values+=element.val;
    //         };
    //         std::string v  = element.get_val_rec(element)
    //         if (v){
    //             values+=" " +v;
    //             std::cout<<"values appended";
    //         };
    //         // Recurse through child elements and collect their values
    //         for (const auto child : element.els ){
    //             std::string child_value = child.get_values_rec_incl(&child,should_incl);
    //             if (child_value){values+=child_value;}
    //         };
    //         return values
    //     };
    //     return ""
    // };
    // void get_values_rec_tree_incl(xmln& element,bool(*should_incl)(xmln&)){
    //     std::string values ="";
    //     element.ats["visited"] = "v";
    //     if (should_incl(element)){
    //         values+= " "+ this->get_values_rec_incl(element, should_incl);
    //     }
    //     else{
    //         for (const xmln& i : element.els  )
    //             values+=i.get_values_rec_tree_incl(i,should_incl);
    //         };
    //     return values
    // };
    // void get_values_recursively(exclusions):
    //     // //Recursively collect values (text) from element and its children, excluding certain elements.//
    //     // Skip this element if it matches any exclusion criteria
    //     if (this->should_exclude(exclusions))
    //         return ""  // Skip this element

    //     // Collect the element's text if it has any
    //     std::string values;
    //     if (this->val) 
    //         values.append(this->val)

    //     // Recurse through child elements and collect their values
    //     for (const auto child : this->els ){
    //         child_value = child.get_values_recursively(exclusions)
    //         if child_value:
    //             values.append(child_value)
    //     };
    //     return values
    // };
    bool lt_eq(std::map<std::string,std::string>& mlhs, std::map<std::string,std::string>& mrhs){
        bool t = true ;
        for(std::pair<std::string,std::string> p : mlhs){
            if(mrhs[p.first] == p.second){t= true;}
            else {t=false ; return t;}
        };
        return t;
    };
    xmln* dfs_first(std::string name, std::map<std::string,std::string> atrs);
    std::vector<xmln*> dfs_all(){
        std::vector<xmln*> vec ;
        for( int i=0 ;  i< this->els.size() ; i++ ){
            xmln* s =&(this->els[i]); vec.push_back(s);
            for(int i=0 ; i <s->els.size();i++ )  {
                vec.push_back(s);
                while(!s->els.empty()){
                    s = &(s->els.front());
                    vec.push_back(s); }
            };
        };
        return vec ;
    };   
    std::vector<xmln*> bfs_all(){
        std::vector<xmln*> vec ;
            std::queue<xmln*> elq = {};
            for(int i = 0 ; i<this->els.size();i++ ){xmln* n=&(this->els[i]);elq.push(n);};
            for(;  !elq.empty() ;  elq.pop() ){
                
                for(int i=0;i<elq.front()->els.size();i++){ xmln* s= &(elq.front()->els[i]);elq.push(s);};
                vec.push_back(elq.front());
            };        
            return vec ;
    };
    std::vector<xmln*> bfs_all( bool(*condition)(xml::xmln*)){
        std::vector<xmln*> vec ;
        std::queue<xmln*> elq = {};
        
        for(int i = 0 ; i<this->els.size();i++ ){xmln* n=&(this->els[i]);elq.push(n);};
        for(;  !elq.empty() ;  elq.pop() ){
            
            for(int i=0;i<elq.front()->els.size();i++){ xmln* s= &(elq.front()->els[i]);elq.push(s);};
            if( condition(elq.front()) ){vec.push_back(elq.front());};
        };        
        return vec ;
    
    };
    std::vector<xmln*> bfs_all(std::string name, std::map<std::string,std::string> atrs){
        std::vector<xmln*> vec ;
        std::queue<xmln*> elq = {};
       
        for(int i = 0 ; i<this->els.size();i++  ){ xmln* n=&(this->els[i]);elq.push(n);};
        for(;  !elq.empty() ;  elq.pop() ){
            
            for(int i=0;i<elq.front()->els.size();i++){ xmln* s= &(elq.front()->els[i]);elq.push(s);};
            if( (name.length()>0?elq.front()->name==name:true) and (elq.front()->lt_eq(atrs ,elq.front()->ats ) )){
                vec.push_back(elq.front());};
        };
        return vec ;
    };
    

    // xmln from_str(std::string& str){
    //     try{
    //         xmln xl = xml_parse(str)
    //     }
    //     catch(const std::exception& e) {
    //         std::err<< xmln parsing error: << e << std::endl;
    //     };
    //     return xmln(x1)
    // };
    // xmln& operator++(int){
    //     xmln result = this->els[this->pos]
    //     this->pos += 1
    //     return result
    // };
    xmln* find(std::string& name){
        for (xmln& el : this->els){
            if (el.name==name) {return &el;}
        };
    };
    friend std::ostream& operator<<(std::ostream& os,const xmln& n){
        std::string ats = "" ;
        for (const std::pair<std::string,std::string>& s : n.ats){ats+= s.first +":"+ s.second+",";};
        os<<  "name:" << n.name << ";val=" <<n.val << ";ats={" << ats <<"},els={"<<"\n " ;
          for (const auto& s : n.els) {os<<s<<"} ";};
        return os ;
    };
};
    
    
    using parse_rule =  int; 
    static const parse_rule xml =  0x1 ;
    static const parse_rule xhtml = 0x1;
    static const parse_rule lax =  0x2; 
    static const parse_rule html = 0x2; // same as lax 

class xml_parse : xmln{
    public:
    std::string  prlg;
      const string quot="&quot;"; //"
      const string apos="&apos;"; //'
      const string lt="&lt;"; //<
      const string gt="&gt;"; //>
      const string amp="&amp;"; //&
    using pos_vec = std::vector<int>;
    using pos_pair_vec = std::vector<std::pair<int,int>>;
    parse_rule prl ;
    // xml_parse(std::ifstream s,  parse_rule prl){};
    void lex(std::string& str, std::vector<std::pair<int,int>>& dbq,std::vector<std::pair<int,int>>& sq,std::vector<std::pair<int,int>>& tags,std::vector<int>& eq){
        for (size_t i=0;i<str.size();i++){ 
            int dbq_start=-1;
            int sq_start=-1;
            int tag_start=-1;
            // char dbq = '\"';
            // char sq = '\'';
            // char lt = '<';
            // char gt = '>';
            // char eq = '=';
            // char amp= 'amp';
            switch (str.at(i)) {
                case '\"': {
                    if (sq_start!=-1){continue;}
                    if(dbq_start!=-1){dbq.push_back({dbq_start,i});dbq_start=-1;}
                    else {dbq_start=i;};
                    continue ;}
                case '\'': {
                    if(dbq_start!=-1){continue;};
                    if(sq_start!=-1){sq.push_back({sq_start,i});sq_start=-1 ;}
                    else {sq_start=i;}; 
                    continue;
                 }
                case '<': {if((dbq_start!=-1) or (sq_start!=-1) ){continue;}; tag_start = i;} 
                case '>': {if((dbq_start!=-1) or (sq_start!=-1) or (tag_start!=-1) ){continue;}; 
                 if(-1!=tag_start){tags.push_back({tag_start,i});tag_start =-1 ;}
                 continue;
                }
                case '=': {if((dbq_start!=-1) or (sq_start!=-1) ){continue;};
                eq.push_back(i);continue;}
                case '&': {
                    // size_t s=static_cast<size_t>(1) ; 
                    // for(int it = i+1; it< static_cast<size_t>(10) ; i++){
                    //     s++;
                    // };/*if(s!=sizeof(quot) ;std::cerr<<"xml escape not terminated ")*/
                    
                    string s = str.substr(i+1,4);
                    if(quot==s){str.replace(i,sizeof(quot)+1,1,'\"');};
                    if(apos==s){str.replace(i,sizeof(apos)+1,1,'\'');};
                    s = s.substr(0,sizeof(amp));
                    if(amp==s){str.replace(i,sizeof(amp)+1,1,'&');};
                    s = s.substr(0,sizeof(gt));
                    if(gt==s){str.replace(i,sizeof(gt)+1,1,'>');};
                    if(lt==s){str.replace(i,sizeof(lt)+1,1,'<');};
                    i+=3;
                };
                
            };
        };
    };
    
    int find_index_front(int ind, std::vector<int>& t){// negative ind means find back
        for(int i = 0; i<t.size();i++){
            if(t[i] > ind) return t[i];
        };
    };
    int find_index_back(int ind, std::vector<int>& t){// negative ind means find back
        for(int i = 0; i<t.size();i++){
            if(t[i] > ind) return t[i-1];
        };
    };
    //TODO feed
    //TODO pull(feed)
    
    //  value_parse() TODO
   
    // xmln lax_from_str()// same as from str but tags need be closed only for valued tags or root  
    inline void pop_cur_el_vec(std::vector<xmln>* _cur ,xmln& n){
        if(_cur->size()==1){n.els.emplace_back(_cur->front() ); return;}
        (*_cur)[_cur->size()-2].els.emplace_back(_cur->back());
        _cur->pop_back();
    };
#ifdef XML_NO_POP_MACRO    
#define pop_el_vec pop_cur_el_vec(&curn_vec, n);
#endif
#ifndef XML_NO_POP_MACRO
#define pop_el_vec \
if(curn_vec.size()==1){n.els.emplace_back(curn_vec.front() ); } \
else {curn_vec[curn_vec.size()-2].els.emplace_back(curn_vec.back()); \
curn_vec.pop_back();} \

#endif

    // inline void pop_cur_el_vec(std::vector<xmln> _cur ,xmln& n){
    //     if(_cur->size()==1){n.els.push_back((*_cur)[0] ); return;}
    //     (*_cur)[_cur->size()-2].els.push_back((*_cur)[_cur->size()-1]);
    //     _cur->pop_back();
    // };
    std::string get_str_with_escape();
    std::string get_str(){
        return get_str_with_escape();
    };
    xmln from_str(std::string& str){
        
        std::vector<std::pair<int,int>> dbq = {} ;
        std::vector<std::pair<int,int>> sq = {} ; 
        std::vector<std::pair<int,int>> tags ={} ;
        std::vector<int> eq = {} ;
        this->lex(str, dbq,sq,tags,eq);
       
        xmln n("root",{{"atribute","basenode"}}) ; // Root node
        std::vector<xmln> curn_vec ; // Currently opened tags 
        int next_eq_ind = 0; std::pair<int,int> prev;

         std::vector<int> eq_tag ={}; 
        for(int it=0;it<tags.size(); it++  ){ //"012345"
            std::pair<int,int> thans = tags[it];
            std::string value; 
            if (str.at(thans.first+1) == '/'){
                if(thans.first+2 == thans.second){
                    value = str.substr(prev.second+1,thans.first-1-(prev.second));
                    curn_vec[curn_vec.size()-1].val = value ; 
                    pop_el_vec
                    prev=thans;
                    continue;   
                };
            
                std::string close_name = str.substr(thans.first+2,thans.second-(thans.first+2)) ;
                int it; int cur_pos = curn_vec.size() -1;
                for(it = cur_pos ; it >0 ;it-- ){
                    if(curn_vec[it].name==close_name){
                        if(it == cur_pos -1){
                            value = str.substr(prev.second+1,thans.first-1-(prev.second));
                            curn_vec[curn_vec.size()-1].val = value ; 
                        }
                        else value = "";
                            pop_el_vec
                        break;
                    };
                    pop_el_vec
                };
                prev=thans;
                continue;
            };
            // Find equals
            eq_tag ={};  int i; // Defined ::for 
            for( i = next_eq_ind ;eq[i] < thans.second;i++ ){
                if(eq[i]>thans.first)
                    eq_tag.push_back(eq[i]);                
            };
            next_eq_ind = i ;
          
            
             string name ;   int passed_space=0; 
            for(  i = thans.first+1  ; ; i++  ) {
                if(isspace(str.at(i))){
                    if(i -thans.first+1 - passed_space ==0){
                        passed_space++;
                    }
                    else break;
                }
            };
            name=str.substr(thans.first+1+passed_space, thans.first+i - (thans.first+1 +passed_space) );

            std::map<std::string,std::string> attributes  ;
            int eqs; 
            for(i=0 ; i<eq_tag.size();i++){
                eqs = eq_tag[i];
                std::string atr_name ;  int passed_first_space = 0;
                for(i  = eqs ;; i--){
                    if(isspace(str.at(i))){
                        if(passed_first_space == (eqs - i - 1)){
                            passed_first_space++;
                        }
                        else break;
                    }
                } ;
                atr_name = str.substr(i+1,eqs-i-1 - (passed_first_space - 1));
                std::string atr_val;
                bool sq_start = 0 ; int dbq_start = 0; passed_first_space = 0;
                for(i = eqs ;i<thans.second;i++){
                    if((str.at(i) == '\'') ){
                        if(dbq_start>0){continue;}
                        if(sq_start>0){break;}
                        else {sq_start = i; passed_first_space = -1;}
                    };
                    if((str.at(i) == '\"') ){
                        if(sq_start>0){continue;}
                        if(dbq_start>0){break;}
                        else {dbq_start = i; passed_first_space = -1;}
                    };
                    if(isspace(str.at(i))){
                        if(dbq_start or sq_start ){continue;}
                        if(passed_first_space == (i -eqs - 1)){passed_first_space++ ;}
                        else break;
                    };
                } ;
                if(passed_first_space>0){atr_val = str.substr(eqs+passed_first_space+1,(i-eqs)-(passed_first_space+1));}
                else if(dbq_start>0){atr_val = str.substr(eqs+dbq_start, (i-eqs)-dbq_start);}
                else if(sq_start>0){atr_val = str.substr(eqs+sq_start, (i-eqs)-sq_start);};
                attributes[atr_name]=atr_val;
            };
            if(curn_vec.size() > 1){
                xmln node(name,attributes);
                curn_vec.emplace_back(node);
            };
            if(str.at(thans.second-1)=='/'){pop_el_vec};
            prev=thans;
        };
        while (curn_vec.size()>1){
            pop_el_vec
        };
      
        return n;
        
    };
    void from_str_prolog(string s,std::string& prlg){
        size_t p= (s.find_first_of("\n"));
        this->prlg = s.substr(0,p);
    };
    xml_parse(){        this->prl = xml::xml; };
    xml_parse(xml::parse_rule _prl){this->prl = _prl;};

 
        
};
};




