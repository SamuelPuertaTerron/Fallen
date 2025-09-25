#pragma once

namespace FEngine
{
	struct Colour
	{
		float R;
		float G;
		float B;
		float A;

		// Primary colors
		static Colour Red() { return { 1.f, 0.f, 0.f, 1.f }; }
		static Colour Green() { return { 0.f, 1.f, 0.f, 1.f }; }
		static Colour Blue() { return { 0.f, 0.f, 1.f, 1.f }; }

		// Dark variants
		static Colour DarkRed() { return { 0.55f, 0.f, 0.f, 1.f }; }
		static Colour DarkGreen() { return { 0.f, 0.55f, 0.f, 1.f }; }
		static Colour DarkBlue() { return { 0.f, 0.f, 0.55f, 1.f }; }

		// Light variants
		static Colour LightRed() { return { 1.f, 0.5f, 0.5f, 1.f }; }
		static Colour LightGreen() { return { 0.5f, 1.f, 0.5f, 1.f }; }
		static Colour LightBlue() { return { 0.5f, 0.5f, 1.f, 1.f }; }

		// Common grayscale
		static Colour White() { return { 1.f, 1.f, 1.f, 1.f }; }
		static Colour Black() { return { 0.f, 0.f, 0.f, 1.f }; }
		static Colour Gray() { return { 0.5f, 0.5f, 0.5f, 1.f }; }
		static Colour LightGray() { return { 0.75f, 0.75f, 0.75f, 1.f }; }
		static Colour DarkGray() { return { 0.25f, 0.25f, 0.25f, 1.f }; }

		// Extended basics
		static Colour Yellow() { return { 1.f, 1.f, 0.f, 1.f }; }
		static Colour Cyan() { return { 0.f, 1.f, 1.f, 1.f }; }
		static Colour Magenta() { return { 1.f, 0.f, 1.f, 1.f }; }
		static Colour Orange() { return { 1.f, 0.65f, 0.f, 1.f }; }
		static Colour Purple() { return { 0.5f, 0.f, 0.5f, 1.f }; }
		static Colour Pink() { return { 1.f, 0.75f, 0.8f, 1.f }; }
		static Colour Brown() { return { 0.6f, 0.3f, 0.1f, 1.f }; }

		// Dark extended
		static Colour DarkYellow() { return { 0.7f, 0.7f, 0.f, 1.f }; }
		static Colour DarkCyan() { return { 0.f, 0.55f, 0.55f, 1.f }; }
		static Colour DarkMagenta() { return { 0.55f, 0.f, 0.55f, 1.f }; }
		static Colour DarkOrange() { return { 0.8f, 0.35f, 0.f, 1.f }; }
		static Colour DarkPurple() { return { 0.35f, 0.f, 0.35f, 1.f }; }
		static Colour DarkPink() { return { 0.8f, 0.5f, 0.55f, 1.f }; }
		static Colour DarkBrown() { return { 0.4f, 0.2f, 0.07f, 1.f }; }

		// Extra hues
		static Colour Teal() { return { 0.f, 0.5f, 0.5f, 1.f }; }
		static Colour Lime() { return { 0.75f, 1.f, 0.f, 1.f }; }
		static Colour Navy() { return { 0.f, 0.f, 0.5f, 1.f }; }
		static Colour Maroon() { return { 0.5f, 0.f, 0.f, 1.f }; }
		static Colour Olive() { return { 0.5f, 0.5f, 0.f, 1.f }; }
		static Colour Gold() { return { 1.f, 0.84f, 0.f, 1.f }; }
		static Colour Silver() { return { 0.75f, 0.75f, 0.75f, 1.f }; }

		// Transparency helpers
		static Colour Transparent() { return { 0.f, 0.f, 0.f, 0.f }; }
	};
} // namespace FEngine

