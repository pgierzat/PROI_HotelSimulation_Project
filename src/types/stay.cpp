#include "stay.hpp"

Stay::Stay(const Guest& guest, const Room& room, const jed_utils::datetime& start,
    const jed_utils::datetime& end) : guest{guest}, room{room}, start{start}, end{end}
{
    (this -> start).trunkate();
    (this -> end).trunkate();
    if (start > end)
        throw std::invalid_argument("Stay must start before it ends.");
}
