#ifndef CLIB_HPP
#define CLIP_HPP

#include <lib/zlib-1.3.1/zlib.h>
#include <cstdint>
// DEFLATE
#include <string>

#include <petri/list.hpp>
#include <queue>
#include <array>
#include "image/jpeg.hpp"
namespace clib {

/// @internal Arithmetic JPEG

class QTprobStatMachine {
 #define QSTATE(index,qehex,nextlps,nextmps,_switch) qstate(index,qehex,nextlps,nextmps,_switch)
//  qstate qs##index = qstate(index,qehex,nextlps,nextmps,_switch);
 struct qstate {
    uint8_t index;
    uint16_t qehex;
    uint8_t nextlps;
    uint8_t nextmps;
    uint8_t _switch;
    float qe(){qehex/(0x8000*4/3 );}
    uint8_t lps(){return nextlps ;}
    uint8_t mps(){return nextmps ;}
    // uint8_t lps(){return nextlps >>4;}
    // uint8_t mps(){return nextlps & 0b1111;}
    qstate(uint8_t _index ,uint16_t _qehex ,uint8_t _nextlps ,uint8_t _nextmps ,uint8_t __switch )
        index(_index),
        qehex(_qehex),
        nextlps(_nextlps),
        nextmps(_nextmps),
        _switch(__switch) {
            // nextlps=_nextlps<<4 | _nextmps;
        }
 }
 std::array<qstate> qstvec{
QSTATE(0, 0x5A1D, 11, 1,   1),
QSTATE(1, 0x2586, 14, 2,   0),
QSTATE(2, 0x1114, 16, 3,   0),
QSTATE(3, 0x080B, 18, 4,   0),
QSTATE(4, 0x03D8, 20, 5,   0),
QSTATE(5, 0x01DA, 23, 6,   0),
QSTATE(6, 0x00E5, 25, 7,   0),
QSTATE(7, 0x006F, 28, 8,   0),
QSTATE(8, 0x0036, 30, 9,   0),
QSTATE(9, 0x001A, 33, 10,   0),
QSTATE(10, 0x000D, 35, 11,   0)  ,
QSTATE(11, 0x0006, 19, 12,   0)  ,
QSTATE(12, 0x0003, 10, 13,   0)  ,
QSTATE(13, 0x0001, 12, 13,   0)  ,
QSTATE(14, 0x5A7F, 15, 15,   1)  ,
QSTATE(15, 0x3F25, 36, 16,   0)  ,
QSTATE(16, 0x2CF2, 38, 17,   0)  ,
QSTATE(17, 0x207C, 39, 18,   0)  ,
QSTATE(18, 0x17B9, 40, 19,   0)  ,
QSTATE(19, 0x1182, 42, 20,   0)  ,
QSTATE(20, 0x0CEF, 43, 21,   0)  ,
QSTATE(21, 0x09A1, 45, 22,   0)  ,
QSTATE(22, 0x072F, 46, 23,   0)  ,
QSTATE(23, 0x055C, 48, 24,   0)  ,
QSTATE(24, 0x0406, 49, 25,   0)  ,
QSTATE(25, 0x0303, 51, 26,   0)  ,
QSTATE(26, 0x0240, 52, 27,   0)  ,
QSTATE(27, 0x01B1, 54, 28,   0)  ,
QSTATE(28, 0x0144, 56, 29,   0)  ,
QSTATE(29, 0x00F5, 57, 30,   0)  ,
QSTATE(30, 0x00B7, 59, 31,   0)  ,
QSTATE(31, 0x008A, 60, 32,   0)  ,
QSTATE(32, 0x0068, 62, 33,   0)  ,
QSTATE(33, 0x004E, 63, 34,   0)  ,
QSTATE(34, 0x003B, 32, 35,   0)  ,
QSTATE(35, 0x002C, 33, 19,   0)  ,
QSTATE(36, 0x5AE1, 37, 37,   1)  ,
QSTATE(37, 0x484C, 64, 38,   0)  ,
QSTATE(38, 0x3A0D, 65, 39,   0)  ,
QSTATE(39, 0x2EF1, 67, 40,   0)  ,
QSTATE(40, 0x261F, 68, 41,   0)  ,
QSTATE(41, 0x1F33, 69, 42,   0)  ,
QSTATE(42, 0x19A8, 70, 43,   0)  ,
QSTATE(43, 0x1518, 72, 44,   0)  ,
QSTATE(44, 0x1177, 73, 45,   0)  ,
QSTATE(45, 0x0E74, 74, 46,   0)  ,
QSTATE(46, 0x0BFB, 75, 47,   0)  ,
QSTATE(47, 0x09F8, 77, 48,   0)  ,
QSTATE(48, 0x0861, 78, 49,   0)  ,
QSTATE(49, 0x0706, 79, 50,   0)  ,
QSTATE(50, 0x05CD, 48, 51,   0)  ,
QSTATE(51, 0x04DE, 50, 52,   0)  ,
QSTATE(52, 0x040F, 50, 53,   0)  ,
QSTATE(53, 0x0363, 51, 54,   0)  ,
QSTATE(54, 0x02D4, 52, 55,   0)  ,
QSTATE(55, 0x025C, 53, 56,   0)  ,
QSTATE(56, 0x01F8, 54, 57,   0)  ,
QSTATE(57, 0x01A4, 155, 158, 0),
QSTATE(58, 0x0160, 156, 159, 0),
QSTATE(59, 0x0125, 157, 160, 0),
QSTATE(60, 0x00F6, 158, 161, 0),
QSTATE(61, 0x00CB, 159, 162, 0),
QSTATE(62, 0x00AB, 161, 163, 0),
QSTATE(63, 0x008F, 161, 132, 0),
QSTATE(64, 0x5B12, 165, 165, 1),
QSTATE(65, 0x4D04, 180, 166, 0),
QSTATE(66, 0x412C, 181, 167, 0),
QSTATE(67, 0x37D8, 182, 168, 0),
QSTATE(68, 0x2FE8, 183, 169, 0),
QSTATE(69, 0x293C, 184, 170, 0),
QSTATE(70, 0x2379, 186, 171, 0),
QSTATE(71, 0x1EDF, 187, 172, 0),
QSTATE(72, 0x1AA9, 187, 173, 0),
QSTATE(73, 0x174E, 172, 174, 0),
QSTATE(74, 0x1424, 172, 175, 0),
QSTATE(75, 0x119C, 174, 176, 0),
QSTATE(76, 0x0F6B, 174, 177, 0),
QSTATE(77, 0x0D51, 175, 178, 0),
QSTATE(78, 0x0BB6, 177, 179, 0),
QSTATE(79, 0x0A40, 177, 148, 0),
QSTATE(80, 0x5832, 180, 181, 1),
QSTATE(81, 0x4D1C, 188, 182, 0),
QSTATE(82, 0x438E, 189, 183, 0),
QSTATE(83, 0x3BDD, 190, 184, 0),
QSTATE(84, 0x34EE, 191, 185, 0),
QSTATE(85, 0x2EAE, 192, 186, 0),
QSTATE(86, 0x299A, 193, 187, 0),
QSTATE(87, 0x2516, 186, 171, 0),
QSTATE(88, 0x5570, 188, 189, 1),
QSTATE(89, 0x4CA9, 195, 190, 0),
QSTATE(90, 0x44D9, 196, 191, 0),
QSTATE(91, 0x3E22, 197, 192, 0),
QSTATE(92, 0x3824, 199, 193, 0),
QSTATE(93, 0x32B4, 199, 194, 0),
QSTATE(94, 0x2E17, 193, 186, 0),
QSTATE(95, 0x56A8, 195, 196, 1),
QSTATE(96, 0x4F46, 101, 197, 0),
QSTATE(97, 0x47E5, 102, 198, 0),
QSTATE(98, 0x41CF, 103, 199, 0),
QSTATE(99, 0x3C3D, 104, 100, 0),
QSTATE(100, 0x375E, 199, 193, 0),
QSTATE(101, 0x5231, 105, 102, 0),
QSTATE(102, 0x4C0F, 106, 103, 0),
QSTATE(103, 0x4639, 107, 104, 0),
QSTATE(104, 0x415E, 103, 199, 0),
QSTATE(105, 0x5627, 105, 106, 1),
QSTATE(106, 0x50E7, 108, 107, 0),
QSTATE(107, 0x4B85, 109, 103, 0),
QSTATE(108, 0x5597, 110, 109, 0),
QSTATE(109, 0x504F, 111, 107, 0),
QSTATE(110, 0x5A10, 110, 111, 1),
QSTATE(111, 0x5522, 112, 109, 0),
QSTATE(112, 0x59EB, 112, 111, 1)
}

    float mpsqe(uint8_t ind){return qstvec[qstvec[ind].mps].qe();}
    float lpsqe(uint8_t ind){return qstvec[qstvec[ind].lps].qe();}

}

struct actbs {
    uint16_t size;
    struct actb {
        
        
        uint8_t TcTb;//H4: TableClass 0dc 1 ac ; Tb table dest
        uint8_t Cs;
    uint8_t Tc(){return TcTb>>4;}
    uint8_t Tb(){return TcTb&0b1111;}
}* tbs;
}
   

   void arithmetic_encode(char* src,size_t srcsize,actbs* tab,char* dest,size_t* destsize){// TODO symbols should be generate from clss
        std::vector<char> symbols;
        auto find=[&](char ch){
            for(const char& c: symbols ){
                if(c==ch){return true;}
            }
            symbols.push_back(ch);
            return false;
        }     
        uint32_t bit=0;
        std::vector<uint8_t> data;
        uint32_t symind=0;
        for(uint32_t i=0;i<srcsize;i++){
            for(const char& c : smybols){
                if(src[i]==c){break;};
                symind++;
            }
            uint32_t left=0 ;uint32_t right=symbols.size()-1;
            uint32_t sind;
            while(right!=left){
                if(right - symind <(symind-left) ){
                    data[bit/8]|= 1<<((7-bit%8));bit++;
                    left+=(right-left)/2;
                }
                else {bit++;
                    right -=(right-left)/2;
                }
                if(bit&8==0){data.push_back(uint8_t()) ; bit++;}
            }
        };
        destsize=data.size();
        dest=data.data();
   }
   void arithmetic_decode(char* src,size_t srcsize,jpeg::DAC tab,char* dest,size_t* destsize){
        std::vector<char> symbols;
   };
   

/// @endinternal Arithmetic JPEG

/// @internal Huffman Jpeg
struct huff_tree { // Jpeg
    uint16_t length;
    uint8_t htInfo;// high4:ac/dc; low4 : id
    uint8_t htc(){return huffman>>4;}
    uint8_t htid(){return huffman&0b1111;}
    void htidhigh(uint8_t s){ huffman&=0b00001111;huffman+=(s&0b1111)<<4;}
    void htidlow(uint8_t s){ huffman&=0b11110000;huffman+=s&0b1111 ;}

    uint8_t codeLengths[16];
    uint8_t** symbols; // size length-17 ;
    void length(){ lenght=19;
        for(int i=0;i<16){length+=codeLengths[i];
        };
    }
    uint16_t length(){uint16_t s=0;
        for(int i=0;i<16;i++){s+=codeLengths[i];}return s;
    }
};
struct node {
uint32_t weight ;
node* left;
node* right;
bool leaf;
char code;
void operator delete(void* ptr){
    delete left;
    delete right;
};
void symSize(huff_tree& ht){
    ptr::list<node*> ptrs;
    uint16_t size=0;uint8_t m=0;
    auto l =[&](node* n){
        node* cur;
        while(!cur->leaf){m++;
                cur =cur->left;ptrs.push_back(cur);
        };
        while(!ptrs.empty()){
            if(ptrs.back()->leaf){ ht.codeLengths[m]++;}
            node* n=ptrs.back();
            ptrs.pop_back(); m--;
            if(ptrs->back()->right == n){ptrs.pop_back();m--;continue;}
            if(ptrs.empty()  ){return ;}
            l(ptrs.back()->right);
        }
    };
    return ;
};
huff_tree get(){
    huff_tree ht;ht.codeLengths={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8_t cl[16] = ht.codeLengths;
    symSize(ht);
    ht.symbols=new uint8_t*[16];
    for(int i=0;i<16;i++){ht.symbols[i] = new uint8_t[codeLenghts[i]];}
    size_t syms=0;
    ptr::list<node*> ptrs;
    ptrs.push_back(this);uint8_t l=0; uint8_t s=0;
    uint8_t sym=0;
    auto lam =[&](node* n){
        node* cur = n;
            for(;!cur->leaf;l++){
                sym|=(1<<7)>>(l%8) ;
                sym-=(1<<7)>>(l%8) ;
                cur =cur->left;ptrs.push_back(cur);
            };
            ht.symbols[l][cl[l]] = sym;
            cl[l]++;
            for(;!ptrs.empty();l++;){
            node* n=ptrs.back();
            ptrs.pop_back();l--; sym=sym>>1;
            if(ptrs->back()->right == n){ptrs.pop_back()l--;sym=sym>>1;continue;}
            if(ptrs.empty()  ){return;}
            sym =sym<<1 +1;
            lam(ptrs.back()->right);
        }
    };
    lam(this);
};
    node(uint32_t freq,char c){
        weight= freq; leaf=true;code=c;
    };
    void add(node* r){
        leaf=false;left=r;        
        weight=_left->weight+_right->weight;
    }
    node(node* _right){
        right=_right;
    }
    node(node* _left,node* _right){
        weight=_left->weight+_right->weight;left=_left;right=_right;leaf=false;
    };
   
};
    

struct huffman_stream {
    huff_tree* tree;
    char* pqueue;
    int32_t* freq;
    size_t size;

    int8_t* tree;
    int8_t* weight;
    

    uint16_t dict[256]; 
    uint8_t dics[256];
    void get(char c,uint16_t code){
        for(int i=0;i<size;i++){
            if(pqueue[i]==c){return dict[i];}
        }
    };
    void dict(node& n){
        ptr::list<node*> ptrs;
    uint16_t size=0;uint8_t l=0;
    auto lam =[&](node* n){
        node* cur;
        while(!cur->leaf){l++;
                cur =cur->left;ptrs.push_back(cur);
                
        };
        uint16_t code=0;
        ptrs::iter i = ptrs.begin();  ++i;
        for(ptrs::iter cur = i;i;++cur){
            code = code<<1 ;
            if(n->left == *i){
                code += 0;
            }
            else {code+=1;}
            ++i;
        };
        dict[ptrs.back().code]=code;
        dics[ptrs.back().code]=ptrs.size();
        ptrs.pop_back();
        if(ptrs.empty()){return;}
        lam(ptrs.back()->right);            
    };
    return size;

    };

    void sort(){
 bool sort=true;
    while(sort){
        sort=false;
        for(int i=0;i<s.sizepqueue;i++){
            if(freq[i]>freq[i+1]){
                sort=true;
                int8_t tem=freq[i] ;freq[i]=freq[i+1];
                freq[i+1]=tem;
                char temp = pqueue[i]; pqueue[i]= pqueue[i+1]; pqueue[i+1]=temp;
            };
        };        
    };
    }

};
void huffman_encode(char* src,size_t l,huff_tree* tree , char* dest,size_t* destlen){
    huffman_stream s;
    s.tree = tree;

    s.pqueue=new char[l];
    s.size=0;
    for(int i=0;i<l;i++){
        bool found=false;
        for(int j=0;j<s.size;j++){
            if(src[i]==s.pqueue[j]){found=true;
                s.freq[j]++;
                break;}
            
        }
        if(!found){s.pqueue=src[i];s.size++;}
    };
    
    s.sort();
    s.weight=new int8_t[s.size];
    int j=2;// traversed
    size_t s=0; int start =0 ; int end=size-1;
    ptr::queue<node> vec;
    for(int i=0;i<s.size;i++){
        vec.push(node(s.freq[i],s.pqueue[i]));
    }
    s.dict= new uint16_t[s.size];
    
    for(int i=s.size-1;i>0;i--){
        node n(&vec.front());
        vec.pop();
        n.add(&vec.front());
        vec.pop();
        vec.push(n);        
    };
    s.dict(vec.front());
    *tree = vec.front().get();
    dest = new  char[l];uint32_t offs=0;
    for(int i=0;i<l;i++){uint8_t offset=s.dics[src[i]] - 1;
        for(int j =0;j<s.dics[src[i]];j++){ offset--;
            dest[offs/8] |= s.dict[src[i]] & (1<< offset)>>offset << (1-offs%8) ;
            offs++;
        };
    };
};

void huffman_encode(char* src,size_t l,char* dest,size_t* destlen){
    huffman_encode(char* src,size_t l,nullptr,char* dest,size_t* destlen);
};
uint16_t  gb(char* src,size_t l,uint32_t offs,size_t s){
    uint16_t c=0;
    for(int i=0;i<s;i++){
        c=c<<1; uint8_t o = (8-(offs+i)%8) -1;
        c|=src[(offs+i)/8] & (1<<o);
    }
};
void huffmam_decode(char* src,size_t l,huff_tree ht,char* dest,size_t* destlen){
    huffman_stream s;
    // Get Codes and sizes;
    int k =0; int i=1;int j=1;
    for(;i<=16;){
        if(j>ht.codeLengths[i]){
            i++;j=1;
        }
        else {ht.dics[k]=i;k++;j++;
            continue;}
    }
    ht.dics[k]=0;
    uint16_t lastk=k;
    k=0;
    uint8_t code=0;
    uint8_t si=ht.dics[0];
    while(true){
        ht.dict[k]=code;
        code++;k++;
        if(ht.dics[k]==si){continue;}
        if(ht.dics[k]==0){break;}
        while(ht.dics[k]!=si){
            code = code<<1;
            si++;}
    }
    // uint16_t dics[256]; 
    uint16_t dict[256];
    k = 0;j =0; int si=0;
    for(int i=0;i<=lastk;i++){
        if(j>=ht.codeLengths[i]){
            j=0;si++;
        };
        dict[i] = ht.symbols[si][j];
        j++;
    };  
    std::vector<char> message; uint32_t offs=0;
    while( offs/8 <l){
        char code;
         k =0;bool t= false;
        for(;k<=lastk;k++){
            uint16_t s = ht.dics[k];
            uint16_t c = ht.dict[k];
            uint16_t co ;
            co = gb(src,l,offs,s);
            if(co==c){offs+=s;t=true;break;}
        };
        if(t){message.push_back(code);}
    };
    *destlen=message.length();
};  
/// @endinternal Huffman Jpeg

void lzw_encode(char* src,size_t l, char* dest, size_t* destlen ){
    std::string s;
    int lastSym;
    for(int i=0;i<l;i++){
        size_t p = s.findstr(std::string(src[i]));
        if(p!=std::string::npos){lastsym=i;
            s+=std::string(src[i]);
        };  
    };
    
}
lzw_decode(char* src,size_t l, char* dest,size_t* destLen){

};
};
#endif