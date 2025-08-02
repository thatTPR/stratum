#include "acqres.hpp"
#include <vector>
#include <string>
#include <pair>
#include <glm/glm.hpp>
#include <stratum/modules.hpp>
#include <stratum/acqres/StmImage.hpp>
#include <functional>


struct command {
    std::string value;
    void (*func)(std::string&,size_t& );
    command(std::string s,void (*ptr)(std::string&,size_t& pos)) : value(s),func(ptr){}
};

namespace obj {
    #include <stratum/acqres/values.hpp>
template <typename vT>
vT vert(std::string& line , int indexStart){
            vT s;float pt;int num=-1;
            for(uint i=indexStart;i<line.size();i++){
                int32_t n ;
                if(isdigit(line[i]) ){
                    pt = val(line,i);
                    num++;
                   
                    else {
                        switch(num){
                            case 0 : {s.x=pt;break;}
                            case 1 : {s.y=pt;break;}
                            case 2 : {s.z=pt;break;}
                            if constexpr (std::is_same<glm::vec4,vT>::value){
                                case 3 : {s.w=pt;break;}
                            }
                        }
                    }
                }
                
            };
            return s;
}
    
struct mtl {
    const std::string newMtl = "newmtl"

    const std::string ambient="Ka";
    const std::string diffuse="Kd";
    const std::string specular="Ks";
    const std::string specularExp="Ns";
    const std::string dissolve="d";
    const std::string transparency="Tr";
    const std::string transparencyF="Tf";// rgb or ciexyz
    const std::string opticalDensity="Ni"; // From 0.0001 to 10

    const std::string illum = "illum";
const std::strign disp = "refl";
const std::strign disp = "disp";
const std::string bump = "bump";
const std::string decal = "decal"; // Matte channel
const std::string map = "map_";

const std::string blendu = "blendu";
const std::string blendv = "blendv";
const std::string boost = "boost";
const std::string mm = "mm";






/*
-blendu on | off                       # set horizontal texture blending (default on)
-blendv on | off                       # set vertical texture blending (default on)
-boost float_value                     # boost mip-map sharpness
-mm base_value gain_value              # modify texture map values (default 0 1)
                                       #     base_value = brightness, gain_value = contrast
-o u [v [w]]                           # Origin offset             (default 0 0 0)
-s u [v [w]]                           # Scale                     (default 1 1 1)
-t u [v [w]]                           # Turbulence                (default 0 0 0)
-texres resolution                     # texture resolution to create
-clamp on | off                        # only render texels in the clamped 0-1 range (default off)
                                       #   When unclamped, textures are repeated across a surface,
                                       #   when clamped, only texels which fall within the 0-1
                                       #   range are rendered.
-bm mult_value                         # bump multiplier (for bump maps only)

-imfchan r | g | b | m | l | z         # specifies which channel of the file is used to 
                                       # create a scalar or bump texture. r:red, g:green,
                                       # b:blue, m:matte, l:luminance, z:z-depth.. 
                                       # (the default for bump is 'l' and for decal is 'm')

For Reflection Maps
-type sphere                           # specifies a sphere for a "refl" reflection map    
-type cube_top    | cube_bottom |      # when using a cube map, the texture file for each
      cube_front  | cube_back   |      # side of the cube is specified separately
      cube_left   | cube_right

PBR extensions  
Clara.io:
Pr/map_Pr     # roughness
Pm/map_Pm     # metallic
Ps/map_Ps     # sheen
Pc            # clearcoat thickness
Pcr           # clearcoat roughness
Ke/map_Ke     # emissive
aniso         # anisotropy
anisor        # anisotropy rotation
norm          # normal map (RGB components represent XYZ components of the surface normal)

Ms :
map_RMA       # RMA material (roughness, metalness, ambient occlusion)
map_ORM       # alternate definition of map_RMA

*/
std::vector<named<image2D>> images; 
struct Tmap {
    
    modules::image2D image ;
struct tmapOps{
    bool blendu=true;bool blendv=true;
    float boost;
    float mm_base=0 ; float mm_gain=1;
    glm::vec3 o = glm::vec3(0,0,0);  // Origin offset
    glm::vec3 s = glm::vec3(1,1,1);  // Scale
    glm::vec3 t = glm::vec3(0,0,0);  // Turbulence
    uint32_t texres;
    bool clamp =false;
    float bm =1;
    char imfchan ;
    enum TYPE{
        sphere ,cube_top,  cube_bottom,  cube_front,  cube_back,    cube_left,  cube_right 
    }
    TYPE type;
    Tmap& operator=(modules::Tmap& s){
        std::memcpy(this ,&s,sizeof(s));
        return *this;
    };
    
};
modules::Tmap& operator=(Tmap& s){
        modules::Tmap t; 
        std::memcpy( &t,this,sizeof(*this));
        return t;
    };
tmapOps ops;
}
struct material {

    std::string name;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float specularExponent;
    float transparency ;
    enum {
        rgb=0,
        ciexyz=1
    }TfFlag;
    glm::vec3 Tf;
    float refraction ;

    enum illumin {
        ColorAmbientOff=0,//0. Color on and Ambient off
        ColorAmbientOn=1,//1. Color on and Ambient on
        Highlight=2,//2. Highlight on
        Reflection=3,//3. Reflection on and Ray trace on
        GlassRT=4, ////4. Transparency: Glass on, Reflection: Ray trace on
        FresnelRT=5,//5. Reflection: Fresnel on and Ray trace on
        RefractionRT=6, Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
        RefractionFresnelRT=7, Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
        Reflection=8,// Reflection on and Ray trace off
        Glass=9, //Transparency: Glass on, Reflection: Ray trace off
        ShadowOnGhost=10//. Casts shadows onto invisible surfaces
    };

    uint illum;

    Tmap map_bump ;
    Tmap map_disp ;
    Tmap map_decal ;
    Tmap map_refl ;
    Tmap map_Ka ;// ambient
    Tmap map_Kd ;// diffuse
    Tmap map_Ks ;// specularity

    template <modules::quality::QUALITY q>
    named<modules::material<q>> get(){
        named<modules::material<q>> res;
        res.name=name;
        if constexpr(Q>4){
                    res.data.map_bump =map_bump.image ;
        }
        if constexpr(Q>3){
                    res.data.map_disp =map_disp.image ;
        }
        if constexpr(Q>2){
                    res.data.map_matte =map_matte.image ;
                    res.data.map_refl =map_refl.image ;
                    res.data.map_ambient =map_Ka.image ;
                    res.data.map_diffuse =map_Kd.image ;
                    res.data.map_specular =map_Ks.image ;
        }
        if constexpr(Q>2){
            res.
        };
        
        res.map_ambient =map_Ka.image ;

    }

    material(std::string name);
}
std::vector<material> materials;
void ldKa(std::string& line){
    glm::vec3 r = vert<glm::vec3>(line,2);
    materials.back().ambient=r;
};
void ldKd(std::string& line){
    glm::vec3 r = vert<glm::vec3>(line,2);
    materials.back().diffuse=r;
}
void ldKs(std::string& line){
    glm::vec3 r = vert<glm::vec3>(line,2);
    materials.back().specular=r;
}


void ldF2(std::string& line, float* ptr ){
     for(int i=2;i<line.size();i++){
        if(isdigit(line[i])){
            float v = val(line,i);
            *ptr=v;
            return;
        };
};

}
void ldNs(std::string& line){ldF2(line,&materials.back().specularExponent);};
void ldNi(std::string& line){ldF2(line,&materials.back().refraction);}
void ldTr(std::string& line){ldF2(line,&materials.back().transparency);materials.back().transparency=1-materials.back().transparency;};
void ldd(std::string& line){ldF2(line,&materials.back().transparency);};


void ldrgbTf(std::string& line){
    glm::vec3 
    materials.back().Tf=r;
}

void ldTf(std::string& line){
    glm::vec3 r;
    if(line.find("xyz")== std::string::npos){vert<glm::vec3>(line,5);materials.back().TfFlag=1;}
    else  {r = vert<glm::vec3>(line,2);materials.back().TfFlag=0; }
    materials.back().Tf=r;
};

void uvwOpt(std::string& line ,size_t& pos,glm::vec3* ptr){
      ptr->x=val(line,pos);
     for(line[pos]==' ';pos++){};
     if(isdigit(line[pos])){
        ptr->y=val(line,pos);
    }
    for(line[pos]==' ';pos++){};
         if(isdigit(line[pos])){
        ptr->z=val(line,pos);
    }

};
void blend(std::string& line ,size_t& pos, bool& p){
    for(;line[pos]!=' ';pos++){};
        std::string subs = line.substr(pos,3);
        if(subs==std::string("on")){*p=true;}
        if(subs==std::string("off")){*p=false;}
        pos+=3;
};
std::string current;


image2D Tmap(std::string& line){

    size_t pos = line.find_first_of(" ");
    tmapOps opts; Tmap res;
    for(;pos<line.size();pos++){
        if(line[pos]==' '){continue;}
        if(line[pos]=='-'){pos++;
            if(line[pos]=='o'){
                uvwOpt(line,pos,&opts.o);
                continue;
            }
            if(line[pos]=='s'){
                uvwOpt(line,pos,&opts.s);                
                continue;
            }
            if(line[pos]=='o'){
                uvwOpt(line,pos,&opts.t);                                
                continue;
            }   
            if(line[pos]=='b' and line[pos+1]=="m"){
                pos++;opts.bm=val(line,pos);                     
                continue;
            }

            std::string subs =line.substr(pos,2);
            if(subs==mm){
                opts.mm_base=val(line,pos);
                opts.mm_gain=val(line,pos);
                continue;
            }
            subs=line.substr(pos,5);
            if(subs==std::string("blend")){
                pos+=5;
                if(line[pos]=='u'){pos++;blendu(line,pos,&opts.blendu);}
                if(line[pos]=='u'){pos++;blendv(line,pos,&opts.blendv);}
                continue;
            }
            if(subs==std::string("clamp")){
                blend(line,pos,&opts.clamp);
            }
            if(subs == std::string("texre")){
                pos+=5 ;
                if(line[pos]=='s'){
                    pos++;
                    opts.texres = val(line,pos);
                };
            };
            if(subs==std::string("boost")){
                pos++;opts.boost = val(line,pos);continue;
            };
            if(subs==std::string("imfch")){
                pos+=5;
                if(line[i]=='a' and line[i]=='n'){
                    pos+=2;
                    for(;line[pos]==' ';pos++){}
                    opts.imfchan=line[pos];
                }
            }
            if(subs==std::string("type ")){
                pos+=5;
                std::string p;
                for(;line[pos]==' ';pos++){};
                for(;line[pos]!=' ';pos++){
                    p+=std::string(line[i]);
                } 
                switch(p){
                    case std::string(sphere) :{opts.type=tmapOps::TYPE::sphere;}
                    case std::string(cube_top) :{opts.type=tmapOps::TYPE::cube_top;}
                    case std::string(cube_bottom) :{opts.type=tmapOps::TYPE::cube_bottom;}
                    case std::string(cube_front) :{opts.type=tmapOps::TYPE::cube_front;}
                    case std::string(cube_back) :{opts.type=tmapOps::TYPE::cube_back;}
                    case std::string(cube_left) :{opts.type=tmapOps::TYPE::cube_left;}
                    case std::string(cube_right) :{opts.type=tmapOps::TYPE::cube_right;}    
                }

            }

        }
        else {
            std::string fileName; 
            for(;line[pos]!=' ';pos++){fileName+=std::string(line[pos]);}
            std::string path= current+filename;
            bool found = false;
            for(named<image2D> i : images){
                if(i.name == path){
                    res.image=i.data;found=true;
                }
            }
            if(!found){
                res.image = StmLoadImage(path);
                images.push_back(named<image2d>(path,res.image));
            }
        }
    };
    switch (opts.imfchan){
        case 'r' :{res.image=res.image.loadChannel(0);} 
        case 'g' :{res.image=res.image.loadChannel(1);}
        case 'b' :{res.image=res.image.loadChannel(2);} 
        
    }
    res.ops = opts;
    return res;
};

void ld(std::string file){current=file;
    std::ifstream fi(file);
    std::string line;
    while(std::getline(fi,line)){
        if(line.substr(0,6) == newMtl){
            size_t pos  = line.find_first_not_of(" ",7);
            size_t pos2 = line.find_first_of(" ",pos);
            std::string name = line.substr(pos,pos2-pos);
            materials.push_back(material(name)); 
            continue;
        };
        switch(line[0]){
case 'K' : {
    switch(line[1]){
        case 'a' : { ldKa(line);}
        case 'd' : { ldKd(line);}
        case 's' : { ldKs(line);}
        };
    }
case 'N' : {
    switch(line[1]){
        case 's' : {ldNs(line);}
        case 'i' : {ldNi(line);}
    }
    }
case 'T' : {
    switch (line[1])
    {
    case 'r': {ldTr(line);}
    case 'f': {ldTf(line);}
    }
};
}
auto mapB =[&line](std::string& s){return line.substr(3,s.size()) ==s or (line.substr(0,s.size())==s) ;}
if(line.substr(0,2) == "d "){ldd(line);};
if(line.substr(0,5) == illum){materials.back().illum= num(line,6);}
if(mapB(std::string("Ka"))){materials.back().map_Ka=Tmap(line);}
if(mapB(std::string("Kd"))){materials.back().map_Kd=Tmap(line);}
if(mapB(std::string("Ks"))){materials.back().map_Ks=Tmap(line);}
if(mapB(bump)){materials.back().map_bump= Tmap(line);}
if(mapB(disp)){materials.back().map_disp=Tmap(line);} 
if(mapB(decal)){materials.back().map_decal=Tmap(line);} 
if(mapB(refl)){materials.back().map_refl=Tmap(line);} 
if(mapB(std::string("metallicity"))){materials}

};
};
};
    struct obj {
        const char vertex = 'v';
        const std::string Pvertex = "vp";
        const std::string Nvertext= "vn";
        const std::string Tvertex = "vt";
        const char face ='f';
        
        const std::string vertexTexture = "/";
        const std::string vertexNormal = "/";
        const char line = 'l';
        struct face {
            std::vector<uint32_t> vertices;

            std::vector<uint32_t> vertT;
            std::vector<uint32_t> vertN;
        }
        struct group {
            std::string s="###";
            // Ranges
            std::pair<uint32_t,uint32_t> vert;
            std::pair<uint32_t,uint32_t> Pvert;
            std::pair<uint32_t,uint32_t> Nvert;
            std::pair<uint32_t,uint32_t> Tvert;
            std::pair<uint32_t,uint32_t> lines;
            std::pair<uint32_t,uint32_t> faces;
            group(std::string _name,
uint32_t_ vert,uint32_t _Pvert,uint32_t _Nvert,uint32_t _Tvert,uint32_t _lines,uint32_t _faces){
    name=_name;Pvert.first=_Pvert;
                Nvert.first=_Nvert;
                Tvert.first=_Tvert;
                lines.first=_lines;
                faces.first=_faces;
}
        }
        struct mesh {
            std::vector<glm::vec4> vertices;
            std::vector<glm::vec3> Pvertices;
            std::vector<glm::vec3> Nvertices;
            std::vector<glm::vec3> Tvertices;

            glm::vec3 defVal()){return glm::vec3(1,1,1);}
            std::vector<std::vector<uint32_t>> lines;
            std::vector<face> faces;
            
            std::vector<mtl::material*> materials;
            std::vector<mtl> matlibs;
            std::vector<group> groups;
            void pushVert(glm::vec4& o){vertices.push_back(o);groups.back().vert.second=vertices.size();}
            void pushPVert(glm::vec3& o){Pvertices.push_back(o);groups.back().Pvert.second=Pvertices.size();}
            void pushNVert(glm::vec3& o){Nvertices.push_back(o);groups.back().Nvert.second=Nvertives.size();}
            void pushTVert(glm::vec3& o){Tvertices.push_back(o);groups.back().Tvert.second=Tvertices.size();}
            void pushLines(std::vector<uint32_t>& o){lines.push_back(o);groups.back().lines.second=line.size();}
            void pushFaces(face o){faces.push_back(o);groups.back().faces.second=faces.size();materials.back().faces.second=faces.size();}
        };
        mesh data;
        template <typename meshType>
        meshType get(mesh& s){
            meshType res;
            res.vert=vertices;
            res.tvert=Tvertices;
            res.nvert=Nvertices;
            res.pvert=Pvertices;
            for(std::vector<uint32_t>& line : s.lines){
                res.lines.push_back(std::vector<glm::vec4>());
                for(uint32_t& ind : line){
                    if(ind==0){res.lines.back().push_back(defVal());}
                    else {res.lines.back().push_back(s.vertices[ind]);}
                }
            };
            for(face& f : s.faces){
                for(uint32_t& ind : f.vertices){
                    if(ind==0){res.facevert.back().push_back(defVal());}
                    else {res.facevert.back().push_back(s.vertices[ind]);}
                }
                for(uint32_t& ind : f.vertT){
                    if(ind==0){res.facetvert.back().push_back(defVal());}
                    else {res.facetvert.back().push_back(s.Tvertices[ind]);}
                }
                for(uint32_t& ind : f.vertices){
                    if(ind==0){res.facenvert.back().push_back(defVal());}
                    else {res.facenvert.back().push_back(s.Nvertices[ind]);}
                }

            };
        };

        template <modules::quality::QUALIY Q>
        modules::mesh<3,Q> getMesh(mesh& s){
            get<mesh<3,Q>> res = get<modules::mesh<3>>(s);
        };
        template <modules::quality::QUALIY Q>
        modules::model<3,Q> getModel(mesh& s){
            std::string manifold=std::string("manifold");
            modules::model<3,Q> res= get<modules::model<3>>(s);
            for(group& g: s.groups){
                if(g.name.substr(0,manifold.size()) == manifold ){
                    res.manifolds.push_back(modules::model<3,Q>::manifold())

                };
            }
        };
        template <typename vT>
        void ldVert(std::string& line , int indexStart,std::vector<vT>* ptr){
            vT s=vert<vT>(line,indexStart);
            switch(ptr){
                case &f.vertices : {f.pushVert(s);}
                case &f.Pvertices : {f.pushPVert(s);}
                case &f.Nvertices : {f.pushNVert(s);}
                case &f.Tvertices : {f.pushTVert(s);}
            }
        };  
        void ldLine(std::string& line){
            std::vector<uint32_t> l;
            for(int i=1;i<line.size();i++){
                if(isdigit(line[i]) ){
                    int32_t n =num(line,i);
                    uint32_t s = n>=0?n:f.vertices.size()+n;
                    l.push_back(s);
                }
                if(line[i] == '#' ){break;}
            }
            f.pushLines(l);
        }
        void ldFace(std::string& line){
            face fa;
            for(int i=1;i<line.size();i++){
                if(isdigit(line[i]) ){

                    int32_t n =num(line,i);
                    int32_t vt,vn;bool tb,nb;tb=false;nb=false;
                    if(line[i]=='/'){
                        i++;
                        if(isdigit(line[i]) ){tb=true;
                            int32_t vt =num(line,i);
                        }
                        if(line[i]=='/'){nb=true;
                            vn=num(line,i);
                        }
                    }
                    uint32_t vertex = n>=0?n:f.vertices.size()+n;
                    fa.vertices.push_back(vertex);
                    vertex=0;
                    if(tb){
                        vertex=vt>=0?vt:f.vertices.size()+vt;
                    }
                    fa.vertT.push_back(vertex);;
                    vertex=0;
                    if(nb){
                        uint32_t vertex=vn>=0?vn:f.vertices.size()+vn;
                    }
                    fa.vertN.push_back(vertex);;
                }
                if(line[i] == '#' ){break;}
            }
            f.pushFaces(fa);

        };
        void ldGroup(std::string& line){std::string name;
            for(int i=1;i<line.size();i++){
                if(line[i]!=' '){name+=std::string(line[i]);}
                if(line[i]=='#'){break;}
            }
            group g(name,f.vertices.size()+1,f.Pvertices.size()+1,f.Nvertices.size()+1,f.Tvertices.size()+1,
f.lines.size()+1,
f.faces.size()+1);
            f.groups.push_back(g);
        };
        void ldMtl(std::string& line){std::string name;
            for(int i=6;i<line.size();i++){
                if(line[i]!=' '){
                    name+=std::string(line[i]);
                };
            };
            for(const mtl& m : matlibs){
                for(const mtl::material mat : m.materials){
                    if(mat.name==name){
                        f.materials.push_back(m);return; 
                    }
                }
            }
            
        };
        void ldMtllib(std::string& line){std::string name;
            for(int i=6;i<line.size();i++){
                if(line[i]!=' '){
                    name+=std::string(line[i]);
                };
            }
            mtl mtlli;
            mtlli.ld(name);
            f.matlibs.push_back(mtlli);
        };
        std::string current;
        void load(std::ifsteam& fi){
            std::string line; 
             while(std::getline(fi,line)){
                switch(line[0]){
                    case vertex : {
                        switch(line[1]){
                            case ' ' :{ldVert<glm::vec4>(line,1,&f.vertices);}
                            case 'p' :{ldVert<glm::vec3>(line,1,&f.Pvertices);}
                            case 'n' :{ldVert<glm::vec3>(line,1,&f.Nvertices);}
                            case 't' :{ldVert<glm::vec3>(line,1,&f.Tvertices);}
                            
                        }
                        }
                    case line : {ldLine(line);}
                    case vertex : {face f;f.ld(line);data.faces.push_back(f);}
                    case 'g' : {ldGroup(line);}
                }
                size_t pos =line.find("usemtl");
                if(pos!=std::string::npos){
                    ldMtl(line);
                };
                 pos =line.find("mtllib");
                if(pos!=std::string::npos){
                    ldMtllib(line);
                };
            }
        }
        Mesh<3> ld(std::string& name){
            current = name;
            std::ifstream fi(name);
            load(fi);
            
           
        };
        DynamicMesh<3> ldStratumExt(std::ifsream& fi){

        };
    };  
    
    
}