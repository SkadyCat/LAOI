
#include "AoiContext.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "AoiEntity.h"
#include "AoiTrigger.h"
#include "TriggerMarker.h"
#include <sstream>
#include <iostream>
AoiContext::AoiContext(float width, float height, float range) {
	m_width = width;
	m_height = height;
	m_range = range;
	m_countor = 1;
	m_context = NULL;
	m_context = create_aoi(5000, width, height, 5);
}


AoiContext::~AoiContext() {
}

Aoi* AoiContext::CreateTrigger() {
	Aoi* aoi = new AoiTrigger(rand() % (int)m_width, rand() % (int)m_height, rand() % 10 + 5, rand() % (int)m_range + 2, this);
	aoi->RandomTarget();
	m_trigger_list[aoi->m_id] = aoi;
	aoi->Enter();

	return aoi;
}

Aoi* AoiContext::CreateEntity() {
	Aoi* aoi = new AoiEntity(rand() % (int)m_width, rand() % (int)m_height, rand() % 10 + 5, this);
	aoi->RandomTarget();
	m_entity_list[aoi->m_id] = aoi;
	aoi->Enter();
	return aoi;
}

Aoi* AoiContext::CreateTriggerMarker(int id) {
	Aoi* aoi = new TriggerMarker(id, rand() % (int)m_width, rand() % (int)m_height, rand() % 10 + 5, 10, this);
	aoi->RandomTarget();

	wm_list[aoi->m_id] = aoi;

	return aoi;
}


void AoiContext::OnEntityEnter(int self, int other, void* ud) {
	AoiContext* inst = (AoiContext*)ud;

	if (inst->idMaps[self] != inst->idMaps[other]) {
		inst->RefEntity(self,other);

		int _self = inst->idMaps[self];
		int _other = inst->idMaps[other];

		inst->links[_self][_other] = 2;

	}
	

	//TriggerMarker* tmSelf = (TriggerMarker*)inst->wm_list[inst->idMaps[self]];

	//tmSelf->maps[inst->idMaps[other]] = 2;
}

void AoiContext::OnEntityLeave(int self, int other, void* ud) {

	AoiContext* inst = (AoiContext*)ud;
	if (inst->idMaps[self] != inst->idMaps[other]) {
		inst->DeRefEntity(self, other);

		int _self = inst->idMaps[self];
		int _other = inst->idMaps[other];
		inst->links[_self].erase(_other);
	}
	
	

	//TriggerMarker* tmSelf = (TriggerMarker*)inst->wm_list[inst->idMaps[self]];
	//	
	//tmSelf->maps[inst->idMaps[other]] = 0;

	
}

void AoiContext::OnTriggerEnter(int self, int other, void* ud) {
	AoiContext* inst = (AoiContext*)ud;
	if (inst->idMaps[self] != inst->idMaps[other]) {
		
		inst->RefEntity(other, self);
	}

}

void AoiContext::OnTriggerLeave(int self, int other, void* ud) {
	AoiContext* inst = (AoiContext*)ud;
	if (inst->idMaps[self] != inst->idMaps[other]) {
	
		inst->DeRefEntity(other, self);
	}
	
}

void AoiContext::RefEntity(int uid,int aim) {
	std::map<int, Aoi*>::iterator iter = m_entity_list.find(uid);
	if (iter != m_entity_list.end()) {
		Aoi* aoi = iter->second;
		//printf("links -> %d---%d\n", aoi->m_ref, aoi->keys.size());
		aoi->Ref(aim);
		
	} else {
		std::map<int, Aoi*>::iterator iter = m_trigger_list.find(uid);
		Aoi* aoi = iter->second;
		if (idMaps[aoi->m_id] != idMaps[uid])
		{
			
		}
		aoi->Ref(aim);
	}

}

void AoiContext::DeRefEntity(int uid,int aim) {
	std::map<int, Aoi*>::iterator iter = m_entity_list.find(uid);
	if (iter != m_entity_list.end()) {
		Aoi* aoi = iter->second;
		aoi->DeRef(aim);
	} else {
		std::map<int, Aoi*>::iterator iter = m_trigger_list.find(uid);
		Aoi* aoi = iter->second;
		aoi->DeRef(aim);
	}
}


void AoiContext::Update(float interval) {
	std::map<int, Aoi*>::iterator iter = wm_list.begin();
	for (; iter != wm_list.end(); iter++) {
		Aoi* aoi = iter->second;
		aoi->Update(interval);
		aoi->refresh();
	}

}

void AoiContext::Draw() {
	/*std::map<int, Aoi*>::iterator iter = m_entity_list.begin();
	for (; iter != m_entity_list.end(); iter++) {
		Aoi* aoi = iter->second;
		aoi->Draw();
	}

	iter = m_trigger_list.begin();
	for (; iter != m_trigger_list.end(); iter++) {
		Aoi* aoi = iter->second;
		aoi->Draw();
	}*/

	std::map<int, Aoi*>::iterator iter = wm_list.begin();
	for (; iter != wm_list.end(); iter++) {
		Aoi* aoi = iter->second;
		aoi->Draw();
	}
}