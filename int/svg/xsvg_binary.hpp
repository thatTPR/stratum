
// Binary types
template <typename T>
class _d_bin : _d {
    struct _d_prim_bin {
        using struct _d_prim_pt<T>:: ;

    };
    
    _d_bin match_parse(std::vector<char> , size_t& pos){

    }
};