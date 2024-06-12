#ifndef TO_INTERVAL_HPP
#define TO_INTERVAL_HPP


template<typename T>
struct ToInterval
{
    public:
        ToInterval(T left, T right);
        T operator()(T x);
        T left;
        T right;
};


template<typename T>
ToInterval<T>::ToInterval(T left, T right) : left{left}, right{right} {}


template<typename T>
T ToInterval<T>::operator()(T x)
{
    return 0.5 * (abs(x - left) - abs(x - right) + left + right); 
}


#endif
