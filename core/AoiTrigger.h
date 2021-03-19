#pragma once
#include "Aoi.h"
#include "AoiContext.h"
class AoiTrigger :
	public Aoi {
public:
	AoiTrigger(float x, float z, float speed, float range, AoiContext* context);
	~AoiTrigger();
	virtual void Enter();
	virtual void Draw();
	virtual void refresh();

public:

	int m_trigger;
	int m_range;
};

