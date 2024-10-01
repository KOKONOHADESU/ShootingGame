#include "Collision2D.h"


// lŠpŒ`‚Ì”»’è
bool Collision2D::CheckRect(const Rect& data, const Rect& data2)
{
    if (data.right.x < data2.left.x)  return false;
    if (data.left.x  > data2.right.x) return false;
    if (data.right.y < data2.left.y)   return false;
    if (data.left.y  > data2.right.y)  return false;

    return true;
}
