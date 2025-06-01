// #define MACROSP
#include "xml.cpp"

typedef struct table {
    std::string name ; 
    typedef struct {
        std::string type ; 
        std::string name ;
        std::string index; 
    }field ;

    std::vector<field> strct ;
} table;

std::ofstream ofs;
void writeFile(std::ostream& of, table it){
    std::cout<<"Writing to file";
 std::string fbody ; bool use ;
        std::cout<<"Doing struct"<<it.name;
        of<<"typedef struct {\n";
        fbody += "ACQRES(" +it.name+"){\n";
        for(const auto& f : it.strct){
            std::cout<<"   "<<f.type<<"   "<<f.name;
            of<<f.type<<"   "<<f.name;
            if(f.index.size()>0){
                use = true;
                fbody+="arr("+f.name+", "+ f.index+ ");\n ";
                of<<"//"<<f.index;
            }
            else {
                fbody+="one("+f.name+");\n";
            }
            of<<std::endl;

        };
        of<<"}"<<it.name<<";";
        if(use){
            fbody+= "};\nUSE_ACQRES("+it.name+")\n";
            of<<fbody ;
        };
        
        use =false ; fbody = std::string();
};
void getTb(xmlParser* parser){
        if(parser->cur->value.size()<=2){return;};
        if(parser->cur->value.back().t==1  ){
             if(parser->cur->value.back().d.child->name != "p"){return;}; 
            xmlParser::eltree el;if( parser->getChildByName(*parser->cur->value.back().d.child,"em",&el)){ 
                parser->printTree(parser->cur->value.back().d.child);
                bool foundTable = false;
                auto cursize =  [&](xmlParser::eltree* el){int size=0 ; for(const auto p: el->value ) {
                    if(p.t==1){size++;};};return size;
                };
                int currsize=  cursize(parser->cur);
                xmlParser::eltree* current=  parser->cur;
                while(currsize == cursize(current)){parser->feed();}
                if(parser->cur->value.back().d.child->name == "table"){
                    table n ;
                    if(el.value.size() >0){
                        if(el.value.front().t == 0){n.name= el.value.front().d.str;};
                    }
                    else{return;};

                        xmlParser::eltree head ; bool foundTable =  parser->getChildByName(*parser->cur->value.back().d.child,"thead", &head);
                        if(!foundTable){return;};
                        bool type=false ;bool name = false; bool description = false ;
                        for(auto it : head.value){
                            if(it.t == 1){
                                if(it.d.str == "Type"){type = true;} ;
                                if(it.d.str == "Name"){name = true;} ;
                                if(it.d.str == "Description"){description = true;} ;
                            };
                        };

                        if(! (type || name || description) ){return;} ;
                        xmlParser::eltree body ; foundTable = parser->getChildByName(*parser->cur->value.back().d.child,"tbody",&body);
                        if(!foundTable){return;}
                        std::vector<xmlParser::eltree> bodyCh = parser->getChildsByName(body,"tr");
                        for( xmlParser::eltree it : bodyCh ){
                            std::vector<xmlParser::eltree> td = parser->getChildsByName(it,"td");
                            if(td.size()<=3){
                                table::field s ;
                                if(td.size()>0 and td[0].value.size()>0){if(td[0].value.front().t == 0){s.type=it.value.front().d.str;};};
                                if(td.size()>1 and td[0].value.size()>0){if(td[1].value.front().t == 0){s.name=it.value.front().d.str;};};

                                if(s.name.size()>0){
                                    size_t pos = s.name.find("[");
                                        if(pos){
                                            size_t pos2 = s.name.find("]",pos+1);
                                            s.index=s.name.substr(pos,pos2-pos);
                                            s.name=s.name.substr(0,pos);
                                        };
                                };
                                n.strct.push_back(s);
                            };
                        };
                        writeFile(std::cout,n);
                        writeFile(ofs,n);
                    
                };
            
            };

        };
};

int main(int argc, char* argv[]){
    std::string in = std::string(argv[1]);
    std::string out = std::string(in+".hpp");
    std::cout<<"Crawling file: "<<in<<" to file: "<<out<<std::endl;
    std::ifstream inf(in);
    if(inf.is_open()){
        std::cout<<in<<"Is open"<<std::endl;
    }
    
    xmlParser p ;
    // p.parse(in);
    // p.print(&p.tree) ;
    ofs.open(out);
    p.funcFeed(getTb,inf);
    
    // for( table& it : vec ){
    //     writeFile(ofs,it);        
    // };
   
};