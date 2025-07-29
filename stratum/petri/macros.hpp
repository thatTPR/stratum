





#define REPEAT(macro , first) macro(first)
#define REPEAT(macro , first, second) macro(first) macro(second)

#define REPEAT(macro , first, ...) macro(first) REPEAT(macro, __VA_ARGS__)
#define REPEAT(macro , ...) 


#define defm(FLAG) #define FLAG
#define undefm(FLAG) #undef FLAG
#define def_mult(...) REPEAT(defm,__VA_ARGS__)
#define undef_mult(...) REPEAT(undefm,__VA_ARGS__)

#define PAIR_LITERAL_ENUM(name,a) {##name::##a, ##name::##a }
#define MAP_LIST()
#define EN_MEMBER(a) a,
#define EN_MEMBER_STR() ; 
#define ENUM(name ,...) \
enum name {\
    REPEAT(EN_MEMBER, __VA_ARGS__) \
}; \
std::map<name,std::string> name_map = 
