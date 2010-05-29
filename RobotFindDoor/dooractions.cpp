#include "door.h"
#include "manager.h"

Door *getDoor(int index)
{
    return Manager::instance()->getDoor(index);
}
