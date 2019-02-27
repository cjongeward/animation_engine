#include "vec.hpp"

unsigned int toColor(const vec& v) {
	return (static_cast<unsigned>(255. * v.z) << 8) + (static_cast<unsigned>(255. * v.y) << 16) + (static_cast<unsigned>(255. * v.x) << 24);
}
