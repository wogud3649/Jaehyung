#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Brick.png");
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	_instanceDatas.resize(9);



	//for (auto& data : _instanceDatas)
	//{
	//	Transform transform;
	//	Vector2 pos = Vector2(0.0f, 0.0f);

	//	transform.SetPos(pos);
	//	transform.UpdateSRT();

	//	data.maxFrame = Vector2(4.0f, 4.0f);
	//	data.curFrame = Vector2(MathUtility::RandomInt(0, 4), MathUtility::RandomInt(0, 4));

	//	data.matrix = XMMatrixTranspose(transform.GetMatrix());
	//}
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

void Brick::Createblocks()
{
	string name;
	float speed;

	wstring srvPath = L"Resources/Texture/Brick.png";
	string xmlPath = "Resources/XML/Brick.xml";

	MyXML xml = MyXML(xmlPath, srvPath);

	name = "Brick";
	// TODO
}
