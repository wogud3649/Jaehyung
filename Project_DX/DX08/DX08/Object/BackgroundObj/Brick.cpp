#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	CreateBlocks();
}

Brick::~Brick()
{
}

void Brick::Update()
{
	for (const auto& col : _cols)
	{
		col->Update();
	}

	if (KEY_DOWN('4'))
	{
		_blockType++;
		_blockType %= _blockBasicNumber;
	}

	if (_player.expired() == false)
	{
		for (auto col : _cols)
		{
			HIT_RESULT result = col->Block(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
			if (result.dir == Direction::DOWN)
				_player.lock()->Beat();
		}
	}

}

void Brick::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);

	for (const auto& col : _cols)
	{
		col->Render();
	}
}

void Brick::PostRender()
{
	ImGui::SliderInt("BlockType", &_blockType, 0, _blockBasicNumber-1);
}

void Brick::Draw(Vector2 pos)
{
	for (const auto& transform : _transforms)
	{
		if (transform->GetPos() == pos)
			return;
	}

	int minBlockIndex = _blockType * _blockPairNumber;

	int tempIdx = -1;
	for (int i = minBlockIndex; i < minBlockIndex + _blockPairNumber; i++)
	{
		if (_activeBlocks[i] == false)
		{
			tempIdx = i;
			break;
		}
	}
	if (tempIdx == -1)
		return;

	_transforms[tempIdx]->SetPos(pos);
	_transforms[tempIdx]->UpdateSRT();
	_instanceDatas[tempIdx].matrix = XMMatrixTranspose(_transforms[tempIdx]->GetMatrix());
	_instanceBuffer->Update();

	_activeBlocks[tempIdx] = true;
}

void Brick::Erase(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_transforms[i]->GetPos() == pos)
		{
			_transforms[i]->SetPos(_outPos);
			_transforms[i]->UpdateSRT();
			_instanceDatas[i].matrix = XMMatrixTranspose(_transforms[i]->GetMatrix());
			_instanceBuffer->Update();

			_activeBlocks[i] = false;
		}
	}
}

void Brick::Drag(int index, Vector2 pos)
{
	for (const auto& transform : _transforms)
	{
		if (transform->GetPos() == pos)
			return;
	}

	_transforms[index]->SetPos(pos);
	_transforms[index]->UpdateSRT();
	_instanceDatas[index].matrix = XMMatrixTranspose(_transforms[index]->GetMatrix());
	_instanceBuffer->Update();

	_activeBlocks[index] = true;
}

int Brick::SelectBlock(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_transforms[i]->GetPos() == pos)
		{
			return i;
		}
	}
	return -1;
}

void Brick::CreateBlocks()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Brick.png", Vector2(2, 1));
	_size = _quad->GetSize();
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	for (int i = 0; i < _blockBasicNumber * _blockPairNumber; i++)
	{
		Brick::InstanceData instanceData;

		Vector2 colSize;
		Vector2 colPos;

		shared_ptr<Transform> transform = make_shared<Transform>();

		transform->SetPos(_outPos);
		transform->UpdateSRT();

		int block = i / (_blockPairNumber);
		switch (block)
		{
		case 0:
			colSize = Vector2(30, 60);
			colPos = Vector2(0, -15);
			break;
		case 1:
			colSize = Vector2(30, 40);
			colPos = Vector2(0, -5);
			break;
		default:
			break;
		}

		instanceData.maxFrame = Vector2(2.0f, 1.0f);
		instanceData.curFrame = Vector2(block % 2, block / 1);
		instanceData.matrix = XMMatrixTranspose(transform->GetMatrix());

		_instanceDatas.emplace_back(instanceData);

		_transforms.emplace_back(transform);

		shared_ptr<RectCollider> col = make_shared<RectCollider>(colSize);
		_cols.emplace_back(col);
		_cols[i]->GetTransform()->SetParent(_transforms[i]);
		_cols[i]->GetTransform()->Move(colPos);
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}
