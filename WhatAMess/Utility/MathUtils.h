#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

class MathUtils
{
public:
	static float Clamp(float min, float max, float value)
	{
		if(value < min)
			return min;
		if(value > max)
			return max;

		return value;
	}

	static float Lerp(float min, float max, float value)
	{
		return min + (max - min) * value;
	}

	static float LerpClamp(float min, float max, float value)
	{
		return Clamp(min, max, Lerp(min, max, value));
	}

	static float Normalize(float min, float max, float value)
	{
        return (value - min) / (max - min);
	}

	static float NormalizeClamp(float min, float max, float value)
	{
		return Clamp(0.0f, 1.0f, Normalize(min, max, value));
	}
};

#endif