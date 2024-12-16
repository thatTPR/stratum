#include "vects.hpp"



typedef struct strct {
    int size; // In bytes
    int num_members;

    int* members_sizes;
    int* member_orders;
   int** member_orders_sizes; 
    int* member_types_sizes;
    int* member_types; 
    int* member_names_sizes;
    char* all_names;
    int* members;
    
}strct;

template <size_t member_max>
typedef struct strct_ {
    int size;
    int num_members;
    int members_sizes[member_max];
    int member_orders[member_max];
    int member_orders_sizes[member_max][member_max]; 
    int member_types_sizes[member_max*16];
    int member_types[member_max]; 
    uint member_names_sizes[member_max*16];
    char all_names[member_max*16];
    int members[member_max];
    
}strct_;
using strct_16 = strct_<16>;
using strct_32 = strct_<32>;
using strct_64 = strct_<64>;
using strct_128 = strct_<128>;
using strct_256 = strct_<256>;
using strct_512 = strct_<512>;

class refl_variant {
    private:
    vect<strct> data;
    public:
    template <size_t sizer>
    bool get_sttc(strct s , strct_sttc* ret){
        stctc->size = s.size; 
        stctc->num_members = s.num_members;
        uint names_size=0
        for(int i =0 ; i<ret->num_members;i++ ){
        ret->members_sizes[i]     =s.members_sizes[i];
        ret->members_names_size[i]=s.members_names_size[i];
        ret->members[i]           =s.members[i];
            for(int j=names_size;j < s.members_names_size[i];j++ ){
                ret->all_names[j] = (int)s.all_names[j];
            };
            names_size+=s.member_names_sizes[i];
        };
    };
bool get_sttc(size_t pos,strct_sttc* ret){return this->get_sttc(this->data[pos],ret);};
char* get_name_size( var_spec* var_sp,uint index){return var_sp->members_names_sizes[index];};
char* get_name(var_spec* var_sp,uint index){
        size_t names = get_name_size(var_sp,index);
        char name[names] ; int j =0;
        for(int i =0 ; i<index ; i++){
            j+=get_name_size(i);
        };
        for(int i =j ; i<index ; i++){
            name[i-j] = var_sp->all_names[j];
        };
        return name;
}  ;
    void add(variant_spec s)
    dyn_variant() {

    };
};

