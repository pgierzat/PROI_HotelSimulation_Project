#include <vector>
#include <algorithm>

template<typename T>
std::vector<const T*> const_ptr_vec(const std::vector<T*>& vec)
{
    std::vector<const T*> ret;
    std::ranges::for_each(vec, [&](T* elem){ ret.push_back(elem); });
    return ret;
}
