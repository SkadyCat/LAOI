#pragma once


#include "Aoi.h"
#include "AoiEntity.h"
#include "AoiTrigger.h"
#include <unordered_map>
using namespace std;

class TriggerMarker 
	: public Aoi {
public:
		
	TriggerMarker(int id,float x, float z, float speed, float range, AoiContext* context);
	~TriggerMarker();
	AoiContext* context;
	virtual void SetTarget(float x, float z);
	virtual void Enter();
	virtual void Update(float interval);
	virtual void Draw();

public:
	
	int id;
	Aoi* entity;
	Aoi* trigger;
	
	map<int,int> maps;
};
