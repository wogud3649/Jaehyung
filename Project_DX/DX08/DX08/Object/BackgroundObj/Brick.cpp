#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Brick.png", Vector2(3,3));
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	_instanceDatas.resize(180);
	_blockDatas.resize(_instanceDatas.size());

	for (int i = 0; i < _instanceDatas.size(); i++)
	{
		Vector2 colSize;
		Transform transform;
		Vector2 pos = Vector2(-30, -30);

		transform.SetPos(pos);
		transform.UpdateSRT();

		_blockDatas[i].pos = pos;

		if (i % 3 == 0)
			_blockDatas[i].sortx = Direction::RIGHT;
		else if (i % 3 == 1)
			_blockDatas[i].sortx = Direction::MID;
		else
			_blockDatas[i].sortx = Direction::LEFT;

		if ((i % 9) / 3 == 0)
			_blockDatas[i].sorty = Direction::BOTTOM;
		else if ((i % 9) / 3 == 1)
			_blockDatas[i].sorty = Direction::MID;
		else
			_blockDatas[i].sorty = Direction::TOP;

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
		Vector2 tempPos = Vector2((int)(MOUSE_POS.x / 30) * 30, (int)(MOUSE_POS.y / 30) * 30);
		
		for (const auto& block : _blockDatas)
		{
			if (block.pos == tempPos)
				return;
		}
		_blockDatas[_blockIndex].pos = tempPos;

		_transform->SetPos(tempPos);
		_transform->UpdateSRT();
		_instanceDatas[_blockIndex].matrix = XMMatrixTranspose(_transform->GetMatrix());
		_instanceBuffer->Update();
	}
	if (KEY_DOWN('1'))
	{
		_blockIndex--;
		if (_blockIndex < 0)
			_blockIndex = _blockDatas.size() - 1;
	}
	if (KEY_DOWN('3'))
	{
		_blockIndex++;
		if (_blockIndex >= _blockDatas.size())
			_blockIndex = 0;
	}

	for (const auto& col : _cols)
	{
		col->Update();
	}
}

void Brick::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);
}

void Brick::PostRender()
{
	ImGui::SliderInt("Selected Block", &_blockIndex, 0, _blockDatas.size() - 1);
}
