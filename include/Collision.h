#ifndef COLLISION_H_
#define COLLISION_H_

#include "Common.h"

namespace collision {

class Collision {
  public:
    Collision() {}
    ~Collision() {}
    inline bool isCollision(struct vec position_curr, struct vec position_next);
}

} // namespace collision

#endif // COLLISION_H_