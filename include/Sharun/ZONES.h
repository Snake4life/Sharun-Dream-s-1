
typedef struct ZONE_t {
	uint	Id;
	row_npc*	Friendly;
	row_monster*	Monsters;
	ZONE_t*	next;
} ZONE_t;
