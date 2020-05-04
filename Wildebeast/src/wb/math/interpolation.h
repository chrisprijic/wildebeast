#pragma once

namespace wb {
	template<typename T>
	inline T cubicInterp(T n0, T n1, T n2, T n3, T a) {
		double p = (n3 - n2) - (n0 - n1);
		double q = (n0 - n1) - p;
		double r = n2 - n0;
		double s = n1;
		return static_cast<T>(p * a * a * a + q * a * a + r * a + s);
	}

	template<typename T>
	inline T lerp(T n0, T n1, T a) {
		return static_cast<T>(((1.0 - a) * n0) + (a * n1));
	}

	template<typename T>
	inline T scurve3(T a) {
		return static_cast<T>(a * a * (3.0 - 2.0 * a));
	}

	template<typename T>
	inline double scurve5(double a) {
		double a3 = a * a * a;
		double a4 = a3 * a;
		double a5 = a4 * a;
		return static_cast<T>((6.0 * a5) - (15.0 * a4) + (10.0 * a3));
	}

	template<typename T>
	inline T clamp(T value, T lowerBound, T upperBound) {
		if (value < lowerBound) {
			return lowerBound;
		}
		else if (value > upperBound) {
			return upperBound;
		}
		else {
			return value;
		}
	}

	template <class T>
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}

}