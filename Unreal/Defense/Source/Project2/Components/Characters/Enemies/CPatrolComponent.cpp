#include "CPatrolComponent.h"
#include "Global.h"
#include "Objects/CPatrolPath.h"

UCPatrolComponent::UCPatrolComponent()
{
}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UCPatrolComponent::IsValidPath()
{
	if (PatrolPath)
		return true;

	return false;
}

FVector UCPatrolComponent::GetIndexLocation()
{
	if (!IsValidPath())
		return FVector();

	return PatrolPath->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
}

void UCPatrolComponent::UpdateNextIndex()
{
	CheckFalse(IsValidPath());

	if (bReverse)
	{
		if (Index <= 0)
		{
			if (PatrolPath->IsClosedLoop())
			{
				Index = GetSplineCount() - 1;
			}
			else
			{
				Index = 1;
				bReverse = false;
			}
		}
		else
		{
			Index--;
		}
	}
	else
	{
		if (Index >= GetSplineCount() - 1)
		{
			if (PatrolPath->IsClosedLoop())
			{
				Index = 0;
			}
			else
			{
				Index = GetSplineCount() - 2;
				bReverse = true;
			}
		}
		else
		{
			Index++;
		}
	}
}

int32 UCPatrolComponent::GetSplineCount()
{
	return PatrolPath->GetNumberOfSplinePoints();
}