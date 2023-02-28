#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Brick.png");
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	_instanceDatas.resize(18);

	for (int i = 0; i < _instanceDatas.size(); i++)
	{
		Transform transform;
		Vector2 pos;

		if (i % 3 == 0)
			pos.x = CENTER_X - 90;
		else if (i % 3 == 1)
			pos.x = CENTER_X;
		else
			pos.x = CENTER_X + 90;

		if ((i % 9) / 3 == 0)
			pos.y = CENTER_Y + 90;
		else if ((i % 9) / 3 == 1)
			pos.y = CENTER_Y;
		else
			pos.y = CENTER_Y - 90;

		transform.SetPos(pos);
		transform.UpdateSRT();

		_instanceDatas[i].maxFrame = Vector2(3.0f, 3.0f);
		_instanceDatas[i].curFrame = Vector2(i % 3, i / 3);
		_instanceDatas[i].matrix = XMMatrixTranspose(transform.GetMatrix());
	}

	_transform = make_shared<Transform>();

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}

Brick::~Brick()
{
}

void Brick::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_transform->SetPos(MOUSE_POS);
		_transform->UpdateSRT();
		_instanceDatas[0].matrix = XMMatrixTranspose(_transform->GetMatrix());
		_instanceBuffer->Update();
	}
}

void Brick::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);
}