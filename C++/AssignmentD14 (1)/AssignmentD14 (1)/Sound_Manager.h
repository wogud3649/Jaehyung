class Sound_Manager
{
private:
	Sound_Manager();
	~Sound_Manager();

public:
	static void CreateInstance();
	static void DeleteInstance();
	static Sound_Manager* GetInstance();

	void KnightAttack(class Creature* creature);
	void ArcherAttack(class Creature* creature);
	void MageAttack(class Creature* creature);
	void GoblinAttack(class Creature* creature);
	void Damaged(Creature* creature, Creature* other);
	void Dead(Creature* creature);
	void AlreadyDead(Creature* creature);
	void PlayerWin();
	void PlayerLose();


private:
	static Sound_Manager* instance; // -> SoundManager::instance는 전체 프로그램에서 단 하나

	string _knightAttackSound;
	string _archerAttackSound;
	string _mageAttackSound;
	string _goblinAttackSound;
	string _deadSound;
	string _damagedSound;
	string _alreadyDeadSound;
	string _playerWinSound;
	string _playerLoseSound;
};