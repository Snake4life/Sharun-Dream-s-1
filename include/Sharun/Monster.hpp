
class monster : public npc
{
	public:
};

class row_monster
{
	public:
		row_monster();
		monster*	Monster;
		row_monster*	Next;
		row_monster*	Prev;
};
