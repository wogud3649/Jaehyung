class SoundManager
{
private:
	SoundManager();
	~SoundManager();

public:
	static void CreateInstance();
	static void DeleteInstance();
	static SoundManager* GetInstance();

	void KnightAttackSound(shared_ptr<class Creature> attacker, shared_ptr<Creature> victim);
	void ArcherAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim);
	void MageAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim);
	void GoblinAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim);
	void GoblinKingAttackSound(shared_ptr<Creature> attacker, shared_ptr<Creature> victim);
	void TakeDamageSound(int aD, int aP, shared_ptr<Creature> victim);
	void DeadSound(shared_ptr<Creature> victim);

private:
	static SoundManager* instance;

};