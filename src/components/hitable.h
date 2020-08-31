#pragma once

#include "includes/gl_headers.h"
#include "src/foundation/convexhull.h"
#include "src/components/drawable.h"

typedef float radian;

class Hitable: public Drawable
{
public:
    Hitable();
    Hitable(const float x, const float y, const float z);
    ~Hitable() = default;
    ConvexHull collision_shape;
    
    void virtual update_convexhull() = 0;
    void virtual resolve_collision() = 0;
protected:
    void virtual set_up_collision_shape() = 0;
};
