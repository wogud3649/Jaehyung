#include "framework.h"
#include "Skill.h"

Skill::Skill()
{
}

Skill::~Skill()
{
}

void Skill::Update()
{
}

void Skill::Render()
{
}

void Skill::SetActive()
{
	_isActive = true;
}

void Skill::Hit()
{
	DeActivate();
}

void Skill::DeActivate()
{
	_isActive = false;
}