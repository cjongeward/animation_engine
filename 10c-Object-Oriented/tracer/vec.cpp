#include "vec.h"

float dist2(const vec& v1, const vec& v2)
{
  return (v1 - v2).mag2();
}
