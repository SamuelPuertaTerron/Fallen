#include "Globals.h"
#include "Vector3.h"

namespace FEngine
{
    bool Vector3::operator==(const Vector3& other) const
	{
        constexpr float epsilon = 1e-5f; // Tolerance for floating-point comparisons
        return std::abs(X - other.X) < epsilon &&
            std::abs(Y - other.Y) < epsilon &&
            std::abs(Z - other.Z) < epsilon;
    }
}//namespace FEngine