#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject
{
public:
    virtual ~DynamicObject() {}

    // We return a boolean to say if the object is to be deleted
    virtual bool update() = 0;
};

inline std::unordered_set<DynamicObject*> move_queue;

} // namespace GL
