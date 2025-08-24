#ifndef VECT_HPP
#define VECT_HPP
namespace ptr {

template <typename T,typename sizeT>
void resizeVect(T* d,sizeT* si, sizeT s){
    
    T* temp = new T[s];
    for(int i=0;i<*si;i++){
        temp[i]=d[i];
    };
    *si=s;
    d=temp;
};
template <typename T,typename sizeT>
void insertVect(T* d,sizeT* si,T data, sizeT s){
    *si++;
    resizeVect(d,si,*si);
    for(int i=*si-1;i>s;i--){
        d[i]=d[i-1];
    }
    d[s]=data;
};
template <typename T,typename sizeT>
void popVect(T* d,sizeT* si,sizeT s){
    for(int i=s;i<*si-1;i++){
        d[i]=d[i+1];
    };
    *si=*si-1;    
};
template <typename T,typename sizeT>
void push_backVect(T* d,sizeT* si,T data){
    *si++;
    resizeVect(d,si,*si);
    d[*si-1]=data;
};
template <typename T,typename sizeT>
void pop_backVect(T* d,sizeT* si){
    *si--;
    resizeVect(d,si,*si);
};


#define ALIAS_VECT(T,sizeT,dataMember,sizeMember) \
void resize##dataMember(sizeT s){ resizeVect<T,sizeT>(dataMember,&sizeMember,s) ;} \
void insert##dataMember(T data, sizeT s){ insertVect<T,sizeT>(dataMember,&sizeMember,data ,s); ;} \
void pop##dataMember( sizeT s){ popVect<T,sizeT>(dataMember,&sizeMember,s); ;} \
void push_back##dataMember(T data){ push_backVect<T,sizeT>(dataMember,&sizeMember,data); ;} \
void pop_back##dataMember(T data){ pop_backVect<T,sizeT>(dataMember,&sizeMember); ;} 
}


#endif