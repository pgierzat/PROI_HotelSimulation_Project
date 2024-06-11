#ifndef INNER_TASK_HPP
#define INNER_TASK_HPP

#include "../tasks/task.hpp"

class InnerTask : public virtual Task
{
    public:
        InnerTask(const Task&);
        WeakOwnSystemObserver<Worker>& get_wosow();
        WeakMultipleOwnSystemObserver<Worker>& get_wmosow();
        WeakOwnSystemObserver<Room>& get_wosor();
        WeakOwnSystemObserver<Guest>& get_wosog();
        const WeakOwnSystemObserver<Worker>& get_wosow() const noexcept;
        const WeakMultipleOwnSystemObserver<Worker>& get_wmosow() const noexcept;
        const WeakOwnSystemObserver<Room>& get_wosor() const noexcept;
        const WeakOwnSystemObserver<Guest>& get_wosog() const noexcept;
    private:
        using WOSOw = WeakOwnSystemObserver<Worker>;
        using WMOSOw = WeakMultipleOwnSystemObserver<Worker>;
        using WOSOr = WeakOwnSystemObserver<Room>;
        using WOSOg = WeakOwnSystemObserver<Guest>;
};


#endif
