// #define MACROSP
#include "xml.cpp"

typedef struct table {
    std::string name ; 
    struct field {
        std::string type ; 
        std::string name ;
        std::string index; 
    };

    std::vector<field> strct ;
} table;

std::ofstream ofs;
void writeFile(std::ostream& of, table it){
        size_t pos = it.name.find(" ");
        if(pos!= std::string::npos){
            it.name.insert(pos,"/*");
            it.name+="*/";
        };
        for(int i = 0 ; i < it.name.size();i++){
            if(it.name[i] =='\''){
                it.name.erase(it.name.begin());
            }
        };
        for(table::field& s :it.strct ){
            if(!s.name.empty()){
                size_t pos = s.name.find("[");
                if(pos != std::string::npos){
                    size_t pos2 = s.name.find("]",pos+1);
                    if(pos2 != std::string::npos){
                        s.index=s.name.substr(pos+1,pos2-(pos+1));
                        s.name=s.name.substr(0,pos);
                    }
                    else {
                    s.name = s.name.substr(0,pos);
                    s.index = "variable";
                }
                }
            };
        };
        std::string fbody ; bool use ;
   
        of<<"typedef struct {\n";
        fbody += "\nACQRES(" +it.name+"){\n";
        for(const auto& f : it.strct){
            if(!f.index.empty()){
                of<<f.type<<"*   "<<f.name<<";";
                use = true;
                fbody+="arr("+f.name+", "+ f.index+ ");\n ";
                of<<"//"<<"["<<f.index<<"]";
            }
            else {
                of<<f.type<<"   "<<f.name<<";";
                fbody+="one("+f.name+");\n";
            }
            of<<std::endl;

        };
        of<<"}"<<it.name<<";";
        if(use){
            fbody+= "};\nUSE_ACQRES("+it.name+")\n";
            of<<fbody ;
        };
        of<<std::endl;
        use =false ; fbody = std::string();
};

void execTable(table tb){
    writeFile(std::cout, tb );
    writeFile(ofs, tb );
}

void onep(int s , std::string str,  table* tb){
    switch(s){
        case  0 : {tb->name=str;return;};
        case  1 : {tb->strct.push_back(table::field());return;};
        case  2 : {tb->strct.back().type = str;return;};
        case  3 : {tb->strct.back().name = str;return;};
    };
};
void pattern(std::ifstream& ifs){
    std::string one= "<p><em $val=0></em></p>\
<table>\
<tbody>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
<tr $iter=1>\
<td $val=2></td>\
<td $val=3></td>\
</tr>\
</tbody>\
</table>" ;
    std::string two = "<p><em $val = 0></em></p>\
<table>\
<thead>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
</thead>\
<tbody>\
<tr $iter=1>\
<td $val=2></td>\
<td $val=3></td>\
</tr>\
</tbody>\
</table>" ;
        std::string three = "<p><em $val = 0></em></p>\
<table>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
<tr $iter=1>\
<td $val=2> </td>\
<td $val=3> </td>\
</tr>\
</table>";

std::string four = "<p><em $val=0></em></p>\
<p><a></a></p>>\
<table>\
<tbody>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
<tr $iter=1>\
<td $val=2></td>\
<td $val=3></td>\
</tr>\
</tbody>\
</table>" ;

std::string five = "<p><em $val=0></em></p>\
<p><a></a></p>>\
<table>\
<tbody>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
<tr $iter=1>\
<td $val=2></td>\
<td $val=3></td>\
</tr>\
</tbody>\
</table>" ;

std::string six = "<p><em $val = 0></em></p>\
<p><a></a></p>>\
<table>\
<tr>\
<th>Type</th>\
<th>Name</th>\
</tr>\
<tr $iter=1>\
<td $val=2> </td>\
<td $val=3> </td>\
</tr>\
</table>";

    xmlParser::pattern<table> patone(one, &onep);
    xmlParser::pattern<table> pattwo(two, &onep);
    xmlParser::pattern<table> patthree(three, &onep);
    xmlParser::pattern<table> patfour(four, &onep);
    xmlParser::pattern<table> patfive(five, &onep);
    xmlParser::pattern<table> patsix(six, &onep);
    std::vector<xmlParser::pattern<table>> patt = {patone,pattwo,patthree,patfour,patfive,patsix};
    xmlParser p ; p.feed<table>(patt,&execTable,ifs);  
};



int main(int argc, char* argv[]){
    std::string in = std::string(argv[1]);
    std::string out = std::string(in+".hpp");
    std::cout<<"Crawling file: "<<in<<" to file: "<<out<<std::endl;
    
    // p.parse(in);
    // p.print(&p.tree) ;
    ofs.open(out);
    std::ifstream ins(in);
    if(ins.is_open()){
        std::cout<<"Opened file: "<<in<<std::endl;
    }
    pattern(ins);
    
    // for( table& it : vec ){
    //     writeFile(ofs,it);        
    // };
   
};
/*
./fontget.exe avar; `
./fontget.exe base; `
./fontget.exe cbdt; `
./fontget.exe cblc; `
./fontget.exe cff; `
./fontget.exe cff2; `
./fontget.exe cmap; `
./fontget.exe colr; `
./fontget.exe cpal; `
./fontget.exe cvar; `
./fontget.exe cvt; `
./fontget.exe dsig; `
./fontget.exe ebdt; `
./fontget.exe eblc; `
./fontget.exe ebsc; `
./fontget.exe fpgm; `
./fontget.exe fvar; `
./fontget.exe gasp; `
./fontget.exe gdef; `
./fontget.exe glyf; `
./fontget.exe gpos; `
./fontget.exe gsub; `
./fontget.exe gvar; `
./fontget.exe hdmx; `
./fontget.exe head; `
./fontget.exe hhea; `
./fontget.exe hmtx; `
./fontget.exe hvar; `
./fontget.exe ibmfc; `
./fontget.exe jstf; `
./fontget.exe kern; `
./fontget.exe loca; `
./fontget.exe ltsh; `
./fontget.exe math; `
./fontget.exe maxp; `
./fontget.exe merg; `
./fontget.exe meta; `
./fontget.exe mvar; `
./fontget.exe name; `
./fontget.exe ompl; `
./fontget.exe os2; `
./fontget.exe otff; `
./fontget.exe pclt; `
./fontget.exe post; `
./fontget.exe prep; `
./fontget.exe sbix; `
./fontget.exe stat; `
./fontget.exe svg; `
./fontget.exe vdmx; `
./fontget.exe vhea; `
./fontget.exe vmtx; `
./fontget.exe vorg; `
./fontget.exe vvar; `
*/