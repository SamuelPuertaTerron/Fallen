#pragma once

namespace FEngine
{
	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(float x, float y, float z)
			: X(x), Y(y), Z(z) {}

		Vector3(float value)
			: X(value), Y(value), Z(value) {}

		static Vector3 Zero() { return { 0 }; }
		static Vector3 One() { return { 1 }; }

		bool operator==(const Vector3& other) const;
	};
}//namespace FEngine