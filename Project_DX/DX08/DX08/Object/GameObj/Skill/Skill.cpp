#include "framework.h"
#include "Skill.h"

Skill::Skill()
{
	_transform = make_shared<Transform>();
	_reverseBuffer = make_shared<ReverseBuffer>();
}

Skill::~Skill()
{
}

void Skill::Update()
{
}

void Skill::Render()
{
	_reverseBuffer->SetPSBuffer(2);
}

void Skill::SetRight(bool isRight)
{
	_isRight = isRight;
	_reverseBuffer->_data.reverse = !_isRight;
}

void Skill::SetActive()
{
	_isActive = true;
}
