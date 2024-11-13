#include <string>
#include <vector>
#include <pair>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;
namespace xml {
    class xmln{
    public:
    string name ;
    string val
    std::vector<xmln> els;
    std::map<string,string> atrs;
    xmln par ; 

    xmln(xmln element){
        // this->element = element
        
        // Initialize the member variables
        this->name = element.name  // Tag name (e.g., 'div', 'p')
        this->val = element.get_text(strip=true)  // Text content (without leading/trailing whitespace)
        // print(this->val)
        this->ats = element.attrs  // Attributes (as a dictionary)
        
        // Initialize the parent and children attributes
        this->par = element.parent if element.parent else None  // Parent element
        this->els = [](){ for (const auto child : element.children) this->els+= xmln(child)}  // Recursively parse children
        return this
    };
    xmln(std::string _name , std::map<std::string> _ats ,std::string _val): name(_name) , ats(_ats) , val(_val){};
    xmln(std::string _name, std::map<std::string> _ats) : name(_name),ats(_ats);
    xmln(std::string& s_){
        return xml_parse(s_);
    };
    bool operator==(xmln& ob_, xmln& ob ){
        if ((ob_.name == ob.name) and (ob_.val == ob.val )and (ob_.ats == ob.ats)) return true;
        return false 
    };
    void soft_neq_name_ats(xmln _ob, xmln ob){
        b_name = true
        b_ats = true
        try:
            b_name =ob.name == _ob.name
            for (const auto std::pair<std::string,std::string >& t : ob.ats  ){
                    b_ats = _ob.ats[k] == t.
        }
        catch (std::excpetion& e)  :
            std::cout<<"softneq excpetion:"<<e<<std::endl;
        return ((not b_name) and (not b_ats))
    };
    void soft_neq_name_ats_dict(_ob, name, at_dict){
        bool b_name = true
        bool b_ats = true
        try{
            b_name = _ob.name == name
            for (const auto k,v : at_dict  )
                b_ats= _ob.ats[k] == v
        }
        catch(const std::exception& e)
        {
            std::cerr << softneqif<<e.what() << '\n';
        }
        return b_name and b_ats
    };
    void get_val_rec_ex(xmln element , bool(excl*)(xmln)){
        for (c : element.els){
            std::string t = xmln.get_val_rec_ex(c,excl)
            bool sneq  = false
            for (const auto s : excl ){
                print(f"{type(s)}")
                if ( xmln.soft_neq_name_ats(c, s)) {
                    sneq = true
                    continue
                };
            };
            if (sneq){
                if (t){
                    std::cout<<t ;
                    return c.val?c.val:'' + t ;
                };
                else return c.val?c.val:''

            };
        };

    };
    void get_val_rec_ex_dict(xmln& element , std::string& name , std::map<std::string, std::string>& dict){
        for (const auto c : element->els ){
            std::string t = c.get_val_rec_ex_dict(c,name, dict)
            bool sneq  = false
            for (const auto s : dict ){
                if  xmln.soft_neq_name_ats_dict(c, name , dict ):
                    sneq = true
                    continue
            };
            if (sneq){
                if (t){
                    std::cout<<t;
                    return c.val?c.val:'' + t;
                };
                else return c.val?c.val:'' + t;
             };
        };
    };
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
    std::string get_val_rec( xmln& element){
        std::vector<std::string> vec ;  
        // values.append(s)
        for (const auto c : element.els ){
            t = c.get_val_rec(c)
            if (t) {values+=return c.val?c.val:'' + t;}
            else values+=return c.val?c.val:'' + t;};
        return values 
    };
    std::string get_values_rec_incl(xmln& element, std::function<bool(xmln&)> should_incl){
        
        if ((should_incl(element) )   and (element.ats["visited"] != "visited")){
            element.ats["visited"] = "visited"
            std::string values="";
            if(element.val){
                values+=element.val;
            };
            std::string v  = element.get_val_rec(element)
            if (v){
                values+=" " +v;
                std::cout<<"values appended";
            };
            // Recurse through child elements and collect their values
            for (const auto child : element.els ){
                std::string child_value = child.get_values_rec_incl(&child,should_incl);
                if (child_value){values+=child_value;}
            };
            return values
        };
        return ''
    };
    void get_values_rec_tree_incl(xmln& element,std::function<bool(xmln&)> should_incl){
        std::string values ="";
        element.ats["visited"] = "v";
        if (should_incl(element)){
            values+= " "+ this->get_values_rec_incl(element, should_incl);
        }
        else{
            for (const xmln& i : element.els  )
                values+=i.get_values_rec_tree_incl(i,should_incl);
            };
        return values
    };
    // void get_values_recursively(exclusions):
    //     // //Recursively collect values (text) from element and its children, excluding certain elements.//
    //     // Skip this element if it matches any exclusion criteria
    //     if (this->should_exclude(exclusions))
    //         return ''  // Skip this element

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
    
    xmln from_str(std::string& str){
        try{
            xmln xl = XMLParse(str)
        }
        catch(const std::exception& e) {
            std::err<< xmln parsing error: << e << std::endl;
        };
        return xmln(x1)
    };
    xmln& operator++(int){
        result = this->els[this->pos]
        this->pos += 1
        return result
        
    };
    xmln& find(std::string& name){
        for (xmln& el : this->els){
            if (el.name==name) return el;
        };
    };
    friend std::ostream& operator<<(std::ostream& os, const xmln& n){
        os<< std::string( "name"+ this->name + "val="+this->val, "ats="+[this->ats](std::map<std::string,std::string> &n){std::string sum = "" ; for (const auto& s : n) sum+= s; return s}, ",els="+ [this->els](xmln[]& n){ std::string sum="" ;for (const auto& s : n) sum+=s.repr(s); return sum}   ;;;
        return os ;
    };
};
    
    
    // using parse_rule =  int; 
    // static const parse_rule xml =  0x1 ;
    // static const parse_rule xhtml = 0x1;
    // static const parse_rule lax =  0x2; // Tags must not necesarrily have end tags
    // static const parse_rule html = 0x2; // same as lax 
    
    

class xml_parse {
    private:
      const string quot="&quot"; //"
      const string apos="&apos"; //'
      const string lt="&lt"; //<
      const string gt="&gt"; //>
      const string amp="&amp"; //&
    using pos_vec = std::vector<int>
    using pos_pair_vec = std::vector<std::pair<int,int>>
    
    string get_escape(std::string& c , size_t& pos){
        size_t p = pos
        string str = c[pos] ;
        bool t=true;
        while(t){
            pos++;
            str+=c[pos];
            switch(str){
                case quot :{return '\"';};
                case apos :{return '\'';};
                case lt :{return '<';};
                case gt :{return '>';};
                case amp :{return '&';};
            };
            if (str.length()==6){
                return string;
            };
        };
    };
    public:
    parse_rule prl ;
    xml_n node ;

    xml_parse(std::ifstream s,  parse_rule prl)
    xml_parse(std::string& str, parse_rule prl){
        return xml_parse::from_str(str) ;
    };
    xml_parse(std::string& str) :  xml_parse(str, xml) {} // Default to parse_rule xml

    void lex(std::string& str, std::vector<std::pair<int,int>& dbq,std::vector<std::pair<int,int>& sq,std::vector<std::pair<int,int>& tags,std::vector<int>& eq){
        for (int i=0;i<str.size();i++){ 
            int dbq_start=-1;
            int sq_start=-1;
            int tag_start=-1;
            switch (str[i]) {
                case '\"': {
                    if (sq_start!=-1){continue;}
                    if(dbq_start!=-1){dbq.push_back({dbq_start,i});dbq_start=-1;}
                    else {dbq_start=i};
                      ;continue ;}
                case '\'': {
                    if(dbq_start!=-1){continue;};
                    if(sq!=-1){sq.push_back({sq_start,i});sq_start=-1 ;};
                    else {sq_start=i;}; 
                    continue;
                 }
                case '<': {if((dbq_start!=-1) or (sq_start!=-1) ){continue;}; tag_start = i;} 
                case '>': {if((dbq_start!=-1) or (sq_start!=-1) ){continue;}; 
                 if(-1!=tag_start){tags.push_back({tag_start,i});tag_start =- };
                 else {tag_start=i} ;
                 continue;
                }
                case '=': {if((dbq_start!=-1) or (sq_start!=-1) ){continue;};
                eq.push_back(i);continue;}
                case '&': {
                    string s = str.substr(i+1,4);
                    if(quot==s){str=str.replace(i+1,4,'"');};
                    if(apos==s){str=str.replace(i+1,4,"'");};
                    s = s.substr(0,3);
                    if(amp==s){str=str.replace(i+1,3,"&");};
                    s = substr(0,2);
                    if(gt==s){str=str.replace(i+1,2,">");};
                    if(lt==s){str=str.replace(i+1,2,"<");};
                    i+=1;
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
    inline void pop_cur_el_vec(std::vector<xmln&> _cur){
        _cur[_cur[_cur.length()-2]].els+=_cur[_cur.length()-1];
        _cur.pop_back();
    };
    void escape_amps()
    xmln from_str(std::string& str){
        
        std::vector<std::pair<int,int>> dbq = {} ;
        std::vector<std::pair<int,int>> sq = {} ; 
        std::vector<std::pair<int,int>> tags ={} ;
        std::vector<int> eq = {} ;
        size_t& pos=0; 
        inline xml_parse::lex(str, dbq,sq,tags,eq,amps);
       
        xmln n ; // Root node
        std::vector<xmln&> curn_vec = {n}; xmln curn;// Currently opened tags 
         int next_eq_ind = 0; std::pair<int,int> prev;
        for(std::pair<int,int>& thans : tags  ){ //"012345"
            std::string value; 
            
            if (str[thans.first+1] == '/'){
                if(thans.first+2 == thans.second){
                    value = str.substr(prev.second+1,thans.first-1-(prev.second))
                    curn_vec[curn_vec.length()-1].val = value ; 
                    pop_cur_el_vec(curn_vec);
                    goto set_prev;    
                };
            
                std::string close_name = (str.substr(thans.first+2,thans.second-(thans.first+2)) ;
                int it; cur_pos = curn_vec.length() -1;
                for(it = cur_pos ; it >0 ;it-- ){
                    if(curn_vec[it].name==close_name){
                        if(it == cur_pos -1){
                            value = str.substr(prev.second+1,thans.first-1-(prev.second));
                            curn_vec[curn_vec.length()-1].val = value ; 
                        };
                        else value = "";
                            pop_cur_el_vec(curn_vec);
                        break;
                    };
                    pop_cur_el_vec(curn_vec);
                };
                goto set_prev
            };
            // Find equals
            std::vector<int> eq_tag ={}; int i;
            for( i = next_eq_ind ;eq[i] < thans.second;i++ ){
                if(eq[i]>thans.first)
                    eq_tag+=eq[i];                
            };
            next_eq_ind = i ;
          
            
            string name =""; int passed_space=0; int i ;
            for(  i = thans.first+1  ; ; i++  ) {
                if(isspace(str[i]){
                    if(i -thans.first+1 - passed_space ==0){
                        passed_space++;
                    };
                    else break;
                }
            };
            name=str.substr(thans.first+1+passed_space, thans.first+i - (thans.first+1 +passed_space) );

            std::map<std::string,std::string> atrs ;
            for(int eqs : eq_tag){
                std::string atr_name ; int i ; int passed_first_space = 0
                for(i  = eqs ;; i--){
                    if(isspace(str[i])){
                        if(passed_first_space == (eqs - i - 1)){
                            passed_first_space++;
                        };
                        else break;
                    };
                    else passed_first_space +=1 ;
                } ;
                atr_name = str.substr(i+1,eqs-i-1 - (passed_first_space - 1);
                std::string atr_val;
                bool sq_start = 0 ; int dbq_start = 0; passed_first_space = 0;
                for(i = eqs ;;i++){
                    if((str[i] == "'") ){
                        if(dbq_start>0){continue;}
                        if(sq_start>0){break;}
                            else {sq_start = i; passed_first_space = -1;}
                    };
                    if((str[i] == '"') ){
                        if(sq_start>0){continue;}
                        if(dbq_start>0){break;}
                        else {dbq_start = i; passed_first_space = -1;}
                    };
                    if(isspace(str[i])){
                        if(dbq_start or sq_start ){continue;}
                        if(passed_first_space == (i -eqs - 1){
                            passed_first_space++ ;
                        };
                        else break;
                    };
                } ;
                if(passed_first_space>0){atr_val = str.substr(eqs+passed_first_space+1,(i-eqs)-(passed_first_space+1);};
                else if(dbq_start>0){atr_val = str.substr(eqs+dbq_start, (i-eqs)-dbq_start);};
                else if(sq_start>0){atr_val = str.substr(eqs+sq_start, (i-eqs)-sq_start));};
                atrs+={atr_name,atr_val};
            };
            if(curn_vec.length() > 1){
                xmln n(name,atrs);
                curn_vec.push_back(n)
            };
            set_prev:
            prev=thans
        };
        
    };
    
 
        
};
};
