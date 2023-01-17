#include "framework.h"
#include "Arrow.h"

Arrow::Arrow(wstring path)
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	count = 0;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if (_isActive == false)
		return;
	if (count >= 5000)
	{
		_isActive = false;
		count = 0;
	}

	_quad->GetTransform()->GetPos().x += 0.2 * Timer::GetInstance()->GetDeltaTime() * 5000.0f;
	count++;

	_quad->Update();
}

void Arrow::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
}
