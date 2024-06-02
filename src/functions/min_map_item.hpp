#ifndef MIN_MAP_ITEM_HPP
#define MIN_MAP_ITEM_HPP

#include <algorithm>

template<typename M>
class MapValueComp
{
    public:
        MapValueComp() = default;
        bool operator()(const M::value_type&, const M::value_type&);
};

template<typename M>
bool MapValueComp<M>::operator()(const M::value_type& p1, const M::value_type& p2) {
    return p1.second < p2.second;
}

template<typename M>
M::iterator min_map_item(const M& map)
{
    return std::min_element(map.begin(), map.end(), MapValueComp<M>());
}

template<typename M>
void nth_map_item(M& map, typename M::iterator pos)
{
    std::nth_element(map.begin(), map.end(), pos, MapValueComp<M>());
}


#endif
