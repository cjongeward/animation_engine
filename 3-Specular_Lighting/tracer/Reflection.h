#ifndef REFLECTION_H_
#define REFLECTION_H_

template <class VEC>
VEC reflect(const VEC& orig, const VEC& norm) {
  auto orig_dot_norm = orig.dot(norm);
  auto real_norm = norm;
  // negate the norm if it is pointing in the wrong direction
  if (orig_dot_norm > 0) {
    real_norm = real_norm * -1.f;
  }
  return orig - real_norm * 2.f * orig.dot(real_norm);
}

#endif

