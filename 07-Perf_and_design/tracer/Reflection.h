#ifndef REFLECTION_H_
#define REFLECTION_H_

template <class VEC>
VEC reflect(const VEC& orig, const VEC& norm) {
  return orig - norm * 2.f * orig.dot(norm);
}

#endif

