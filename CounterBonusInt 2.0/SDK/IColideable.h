#pragma once

#include "..\sdk.h"

class ICollideable
{
public:
	virtual void pad0 ();
	virtual const Vector& OBBMins () const;
	virtual const Vector& OBBMaxs () const;
};