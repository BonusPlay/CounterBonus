#pragma once

struct VMatrix
{
	float m[ 4 ][ 4 ];

	inline float* operator[](int i)
	{
		return m[ i ];
	}

	inline const float* operator[](int i) const
	{
		return m[ i ];
	}
};

struct matrix3x3_t
{
	float m_flMatVal[ 3 ][ 3 ];
};

struct matrix3x4_t
{
	float m_flMatVal[ 3 ][ 4 ];
};