#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

enum ClassType
{
	PLAYER,
	KNIGHT,
	ARCHER,
	MAGE
};

#include "SoundManager.h"

#include "GameObject/Creature.h"
#include "GameObject/Player.h"
#include "GameObject/Knight.h"
#include "GameObject/Archer.h"
#include "GameObject/Mage.h"
#include "GameObject/Monster.h"
#include "GameObject/Boss.h"
#include "GameObject/GoblinKing.h"
#include "GameObject/Goblin.h"

#include "World/World.h"