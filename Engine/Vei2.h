#pragma once
#include <math.h>

class Vei2
{
public:
	Vei2() = default;
	Vei2( int x_in,int y_in );
	Vei2 operator+( const Vei2& rhs ) const;
	Vei2& operator+=( const Vei2& rhs );
	Vei2 operator*( int rhs ) const;
	Vei2& operator*=( int rhs );
	Vei2 operator-( const Vei2& rhs ) const;
	Vei2& operator-=( const Vei2& rhs );
	Vei2 operator/( int rhs ) const;
	Vei2& operator/=( int rhs );
	float GetLength() const;
	int GetLengthSq() const;
	static int GetDistanceSq(const Vei2& pos1, const Vei2& pos2)
	{
		
	//	return ( pow(((long)pos1.x - (long)pos2.x),2)  + pow(((long)pos1.y - (long)pos2.y),2) );

	}
	
public:
	int x;
	int y;
};