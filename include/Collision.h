#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {
public:
  static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
    Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                 Vec2( a.x + a.w, a.y + a.h ),
                 Vec2( a.x + a.w, a.y ),
                 Vec2( a.x, a.y ) };

    Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                 Vec2( b.x + b.w, b.y + b.h ),
                 Vec2( b.x + b.w, b.y ),
                 Vec2( b.x, b.y ) };

    for (auto& v : A) {
      v = (v - a.GetCenter()).Rotate(angleOfA) + a.GetCenter();
    }

    for (auto& v : B) {
      v = (v - b.GetCenter()).Rotate(angleOfB) + b.GetCenter();
    }

    Vec2 axes[] = { (A[0] - A[1]).GetNormalized(),
                    (A[1] - A[2]).GetNormalized(),
                    (B[0] - B[1]).GetNormalized(),
                    (B[1] - B[2]).GetNormalized() };

    for (auto& axis : axes) {
      float P[4];

      for (int i = 0; i < 4; ++i) P[i] = (A[i] * axis);

      float minA = *std::min_element(P, P + 4);
      float maxA = *std::max_element(P, P + 4);

      for (int i = 0; i < 4; ++i) P[i] = (B[i] * axis);

      float minB = *std::min_element(P, P + 4);
      float maxB = *std::max_element(P, P + 4);

      if (maxA < minB || minA > maxB)
        return false;
    }

    return true;
  }
};
