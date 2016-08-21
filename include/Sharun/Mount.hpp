
class mount {
	public:
	uint	Skill_Id;
	ushort	Mount_Id;
	ushort	Speed;
	uchar	R_Stamina;
	uchar	R_HP;
	uchar	R_MP;
};

class row_mount
{
	public:
		row_mount();
		mount*		Mount;
		row_mount*	Next;
		row_mount*	Prev;
};

bool is_Mount(uint);
