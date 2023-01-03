#include "framework.h"
#include "ArkBall.h"

ArkBall::ArkBall()
{
    _circle = make_shared<CircleCollider>(Vector2(0.0f, WIN_HEIGHT-(_radius * 2)), _radius);
}

ArkBall::~ArkBall()
{
}

void ArkBall::Update()
{
    if (_circle->_isActive == false)
        return;
    if (_fired == false)
        return;

    _circle->GetCenter() += _dir * _speed;
    Reflection();

    _circle->Update();
}

void ArkBall::Render(HDC hdc)
{
    _circle->Render(hdc);
}

void ArkBall::Reflection()
{
    if (_circle->GetCenter().x < 0 || _circle->GetCenter().x > WIN_WIDTH)
        _dir.x *= -1;
    if (_circle->GetCenter().y < 0)
        _dir.y *= -1;
}