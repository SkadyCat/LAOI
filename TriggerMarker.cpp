#include "TriggerMarker.h"
#include <math.h>
#include "glut.h"
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
	//printf("aim pos %f,%f\n", m_target.m_x, m_target.m_z);
	Aoi::Update(0.5);
	//this->m_pos.m_x += ((rand() % (int)m_context->m_width) / (int)m_context->m_width) - 0.5;
	//this->m_pos.m_z += ((rand() % (int)m_context->m_height) / (int)m_context->m_width) - 0.5;
	//= Vector2(, rand() % (int)m_context->m_height));
	entity->m_pos = m_pos;
	trigger->m_pos = m_pos;
	entity->Update(interval);
	trigger->Update(interval);

	//move_trigger(m_context->m_context,trigger->m_id, 
	//	m_pos.m_x,m_pos.m_z, AoiContext::OnTriggerEnter, m_context, AoiContext::OnTriggerLeave, m_context);
	
	//move_entity(m_context->m_context, entity->m_id,
	//	m_pos.m_x, m_pos.m_z, AoiContext::OnEntityEnter, m_context, AoiContext::OnEntityLeave, m_context);


}

void TriggerMarker::Draw()
{
	printf("status : %d", keys.size());
	trigger->Draw();
	entity->Draw();
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineStipple(2, 0x5555);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);

	map<int, int>::iterator it = entity->keys.begin();

	while (it!= entity->keys.end())
	{
		
		glVertex3f(m_pos.m_x, m_pos.m_z, 0);
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		glVertex3f(tt->m_pos.m_x, tt->m_pos.m_z, 0);
		it++;
	}

	it = trigger->keys.begin();

	while (it != trigger->keys.end())
	{

		glVertex3f(m_pos.m_x, m_pos.m_z, 0);
		Aoi* tt = context->wm_list[context->idMaps[it->first]];
		glVertex3f(tt->m_pos.m_x, tt->m_pos.m_z, 0);
		it++;
	}

	//glVertex3f(m_pos.m_x - range, m_pos.m_z - range, 0);
	//glVertex3f(m_pos.m_x + range, m_pos.m_z - range, 0);
	//
	//glVertex3f(m_pos.m_x - range, m_pos.m_z + range, 0);
	//glVertex3f(m_pos.m_x + range, m_pos.m_z + range, 0);
	//
	//glVertex3f(m_pos.m_x + range, m_pos.m_z - range, 0);
	//glVertex3f(m_pos.m_x + range, m_pos.m_z + range, 0);

	glEnd();
	glDisable(GL_LINE_STIPPLE);
	
}