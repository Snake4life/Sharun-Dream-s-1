#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

typedef struct skill_2_t {
	uint	id;
	uchar	type;
	skill_2_t*	next;
} skill_2_t;

class player {
	public:
		player(connexion_list*);
		virtual ~player();
		virtual void	start(void*);
		virtual void	regen(void*);
		virtual int	Send(packet*);
		virtual int	Send_Direct(char*);
		virtual void	Load(uint);
		virtual void	Save();
		virtual void	Chat(CHAT_TYPE, const char*, const char16_t*);

		connexion_list*	connex;
		short	Op_GID;
		float	Client_Version;
		CLIENT_LANG	C_Lang;
		uint	Players_ID;
		ushort	Characters_Count;
		ushort	Characters_Max;

		uint	Account_Id;
		uint	Id;
		uint	SUBID;
		uint	Class_Id;
		uint	Race_Id;
		uint	Sex;
		uint	Level;
		ulong	exp;
		ulong	money;

		uint	country;
		uint	lander;
		uint	aera;

		CHAR_LOC_t	World;
		CHAR_LOC_t	DJ;
		CHAR_LOC_t*	DjW;

		struct skill {
			uchar	id;
			uchar	type;
			uchar	level;
		} skill[50];
		skill_2_t*	skill2;

		uchar	collect[3];
		char	name[51];
		char	title[51];
		char	friend_note[151];
		char	guild_note[106];
		char16_t	name_S[41];
		char16_t	title_S[41];
		char16_t	friend_note_S[51];
		char16_t	guild_note_S[36];
		uchar	appearance[6+32+64];

		ushort	moveType[2];

		struct Items {
			item_slot	slot[39+20*8];
			uchar	slot_count;
		} Items;

		spawn*	Spawn;
		stat_t	Stats;
		mount*	Mount;

		ulong	Last_Move;
		ulong	loged;
		ulong	Saved_Time;
		uchar	exit_type;
		ulong	exit_time;
		ushort	Right;
		ulong	end_pay;
};

class row_player
{
	public:
		row_player();
		player*		Player;
		row_player*	Next;
		row_player*	Prev;
};

#ifdef DLL_VERSION
extern void	(*free_player)(player*);
extern int	(*Send_Packet)(player*, packet*);
extern void	(*player_Load)(player*, uint);
extern void	(*player_Save)(player*);
extern void	(*Stats_Update)(player*);
//extern void	(*RegenD_ReWait(player*));
//extern void	(*RegenD_DontWait(player*));
#else
extern "C" {
void	free_player(player*);
int	Send_Packet(player*, packet*);
void	player_Load(player*, uint);
void	player_Save(player*);
void	Stats_Update(player*);
void	RegenD_ReWait(player*);
void	RegenD_DontWait(player*);
}
#endif // DLL_VERSION

#endif // _PLAYER_HPP_
