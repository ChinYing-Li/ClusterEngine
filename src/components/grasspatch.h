#pragma once
#include "src/components/drawable.h"

class GrassPatch: public Drawable
{
public:
    GrassPatch();
    ~GrassPatch() = default;
    
protected:
    void set_instanced_models() override;
};
