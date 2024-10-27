template <typename ...args>
class parser {  
    args ; 
};

template <parser p >
class ResourceReference  {
    p parser; 
};