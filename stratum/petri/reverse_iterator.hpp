#ifndef PRI_REVERSE_ITERATOR
#define PRI_REVERSE_ITERATOR
namespace pri {

    template <typename T, template <typename > class C>
    struct reverse {
        C<T>& r;
        struct iterator  {
            friend C<T>::iter;
            C<T>::iter it ;
            T* operator->(){return it.operator->();};
            T& operator*(){return *it;};
            decltype(*this) operator++(){--it;return *this;}
            decltype(*this) operator--(){++it;return *this;}
            decltype(*this) operator++(int){it--;return *this;}
            decltype(*this) operator--(int){it++;return *this;}
        };
        C<T>::iter begin(){return r.rbegin();}
        C<T>::iter end(){return r.rend()}
        reverse_iterator(C<T>& ref) : r(ref){};
    };


};
#endif