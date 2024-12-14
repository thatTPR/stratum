enum types {
    
};

typedef struct layout {
    int uniform_count;
    int* uniform;
    uniform_option* uniform;
    int*  ubo_size; // Ubos and SSBO
    int* ssbo_size;
    buffer_options* s ; 
    int* ins;
    int* out;
    
}layout;



struct layout {
    
};
template <typename T>
 get_layout_data(size_t ars, T* data ){
    
};