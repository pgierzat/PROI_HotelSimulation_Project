#ifndef HAS_ELEM_HPP
#define HAS_ELEM_HPP

#include <ranges>
#include <type_traits>

template<typename C>
using ValueType = typename C::value_type;

template<typename R>
bool has_elem(const R& vec, const ValueType<R>& elem)
{
    auto p = std::ranges::find(vec, elem);
    if (p == vec.end())
        return false;
    return true;
}

template<typename C, typename T>
bool has_elem_ptr(const C& vec, const T& elem)
{
    auto p = std::ranges::find_if(vec, [&](auto p){ return *p == elem; });
    if (p == vec.end())
        return false;
    return true;
}

#endif
