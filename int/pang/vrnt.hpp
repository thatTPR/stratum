 template<typename A, typename B>
    struct vrnt {
      public:
      union str_int {
        A first;
        B second ; 
      } data;
      enum kind{
        str=0,
        int=1
      } type;
      operator[](typename a){

      };
      vrnt operator=(A i)
        {
          return vrnt(i).type=0 ;
      };
      vrnt operator=(B s){
          return vrnt(i).type=1 ;

      };
      template<typename t>
      T get(vrnt v){
        return this->data.i
      };
      ~vrnt();
      vrnt();
    };