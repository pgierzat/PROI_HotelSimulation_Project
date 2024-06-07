#ifndef VEC_TO_PVEC_HPP
#define VEC_TO_PVEC_HPP

#include <vector>
#include <ranges>
#include <memory>

template<typename T>
std::vector<const T*> vec_to_pvec(const std::vector<T>& vec)
{
    std::vector<const T*> pvec{};
    std::ranges::for_each(vec, [&](const T& elem){ pvec.push_back(&elem); });
    return pvec;
}

template<typename T>
std::vector<T*> vec_to_pvec(std::vector<T>& vec)
{
    std::vector<T*> pvec{};
    std::ranges::for_each(vec, [&](const T& elem){ pvec.push_back(&elem); });
    return pvec;
}

template<typename T>
std::vector<const T*> vec_to_pvec(const std::vector<std::unique_ptr<T>>& vec)
{
    auto pvec = std::vector<const T*>{};
    std::ranges::for_each(vec, [&](const auto& elem){ pvec. push_back(elem.get()); });
    return pvec;
}


template<typename T, typename U>
std::vector<const U*> vec_to_pvec(const std::vector<std::unique_ptr<T>>& vec)
{
    std::vector<const U*> pvec{};
    for (const auto& elem : vec)
    {
        pvec.push_back(elem.get());
    }
    return pvec;
}

#endif
