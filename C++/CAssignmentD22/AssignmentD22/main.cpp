#include "Framework.h"

int main()
{
	SoundManager::CreateInstance();
	srand(static_cast<unsigned int>(time(nullptr)));

	World* world = new World();

	delete world;
	SoundManager::DeleteInstance();
	return 0;
}