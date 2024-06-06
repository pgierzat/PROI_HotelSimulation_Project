#ifndef EQUAL_OPERATORS_HPP
#define EQUAL_OPERATORS_HPP

#include <vector>
#include <algorithm>

template<typename T>
bool operator==(const std::vector<const T*>& pvec, const std::vector<T>& vec)
{
    return std::ranges::equal(pvec, vec, [](auto p, const auto& elem){ return *p == elem; });
}


#endif
