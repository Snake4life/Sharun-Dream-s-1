
class item {
	public:
	uint	id;
	char	category[30];
	uchar	level;
	char	type[30];
	short	cooldown;
	short	rank;
	char	rareGrade[10];
	uchar	slotLimit;
	short	maxStack;
	uchar	ability;
	uint	buyPrice;
	uint	sellPrice;
	uint	skill_id;
	uchar	c_slots;
	ushort	atk;
	ushort	def;
	ushort	bal;
	ushort	ipt;
	uchar	bind;
};

typedef struct item_slot {
	uint	id;
	item*	Item;
	ushort	count;
	uchar	enchant[2];
	uint	crystal[4];
	uint	binded;
	char	binder[141];
	char16_t	binder_S[41];
} item_slot;

enum ITEM_CAN {
	ITEM_CAN_TRADE	 = 1,
	ITEM_CAN_DESTROY = 2,
	ITEM_CAN_BANK	 = 4,
	ITEM_CAN_GUILD	 = 8
};

class row_item
{
	public:
		row_item();
		item*		Item;
		row_item*	Next;
		row_item*	Prev;
};
