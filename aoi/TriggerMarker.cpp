#include "TriggerMarker.h"
#include <math.h>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;
TriggerMarker::TriggerMarker(int id,float x, float z, float speed,float range, AoiContext* context)
	:Aoi(x,z,speed,context)
{


	m_id = id;
	this->context = context;
	
	trigger = context->CreateEntity();
	entity = context->CreateTrigger();
	
	context->idMaps[trigger->m_id] = id;
	context->idMaps[entity->m_id] = id;
	m_target.setData((rand() % (int)m_context->m_width), (rand() % (int)m_context->m_height));
}

TriggerMarker::~TriggerMarker()
{
	
}

void TriggerMarker::SetTarget(float x, float z) {
	entity->SetTarget(x,z);
	trigger->SetTarget(x, z);
}
void TriggerMarker::Enter()
{
}
int times = 0;
void TriggerMarker::Update(float interval)
{

	
	maps.clear();
	if (times > 100) {
		m_target.setData((rand() % (int)m_context->m_width), (rand() % (int)m_context->m_height));
		times = 0;
	}
	times++;
	Aoi::Update(0.5);
	entity->m_pos = m_pos;
	trigger->m_pos = m_pos;
	entity->Update(interval);
	trigger->Update(interval);
	
	




	

}

void TriggerMarker::Draw()
{
	trigger->Draw();
	entity->Draw();
	map<int, int>::iterator it = entity->keys.begin();

	while (it!= entity->keys.end())
	{
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		keys[it->first] = 2;
		it++;
	}
	it = trigger->keys.begin();
	while (it != trigger->keys.end())
	{
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		keys[it->first] = 2;
		it++;
	}
	
}

void TriggerMarker::refresh()
{
	keys.clear();
	entity->refresh();
	trigger->refresh();
	map<int, int>::iterator it = entity->keys.begin();
	while (it != entity->keys.end())
	{
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		keys[it->first] = 2;
		it++;
	}
	it = trigger->keys.begin();
	while (it != trigger->keys.end())
	{
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		keys[it->first] = 2;
		it++;
	}
}
