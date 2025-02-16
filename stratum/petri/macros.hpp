

#define ONE(macro , first) macro(first)
#define ONE(macro , first, second) macro(first) macro(second)

#define ONE(macro , first, ...) macro(first) ONE(macro, __VA_ARGS__)
#define ONE(macro , ...) 


#define defm(FLAG) #define FLAG
#define undefm(FLAG) #undef FLAG
#define def_mult(...) ONE(defm,__VA_ARGS__)
#define undef_mult(...) ONE(undefm,__VA_ARGS__)

#define PAIR_LITERAL_ENUM(name,a) {##name::##a, ##name::##a }
#define MAP_LIST()
#define EN_MEMBER(a) a,
#define EN_MEMBER_STR() ; 
#define ENUM(name ,...) \
enum name {\
    ONE(EN_MEMBER, __VA_ARGS__) \
}; \
std::map<name,std::string> name_map = 
