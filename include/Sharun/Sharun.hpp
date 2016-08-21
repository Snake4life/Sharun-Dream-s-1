#ifndef _SHARUN_HPP_
#define _SHARUN_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

#ifdef _MSC_VER
	#define __func__ __FUNCTION__
	#define DSlash "\\"
#else
	#include <unistd.h>
	#define fopen_s(a, b, c)	*a = fopen(b, c)
	#define strcpy_s(a, b, c)	strcpy(a, c)
	#define strncpy_s(a, b, c, d)	strncpy(a, c, d)
	#define sprintf_s(a, b, c, ...)	sprintf((a), (c), ##__VA_ARGS__)
	#define vsprintf_s(a, b, c, ...)	vsprintf((a), (c), ##__VA_ARGS__)
	#define DSlash "/"
#endif

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <winsock2.h>
	#include <windows.h>
#else
	#define Sleep(x) usleep(x*1000)
#endif

#include "data_type.hpp"
#include "OpCode_Gen.hpp"

class player;
class npc;
class monster;

class row_player;
class row_monster;
class row_npc;

class packet;
class spawn;

#include "Chat_Type.h"
#include "Class.h"
#include "Client_Lang.h"
#include "Emote_Type.h"
#include "Move_Type.h"
#include "Name_Color.h"
#include "Race.h"
#include "Slot_Type.h"
#include "Stuff.h"
#include "CheckType.h"
#include "Stat.h"
#include "ZONES.h"
#include "CHAR_LOC.h"

#include "Items.hpp"
#include "Mount.hpp"
#include "settings.hpp"
#include "DB.hpp"
#include "Broadcast.hpp"
#include "packet.hpp"
#include "connexion.hpp"
#include "player.hpp"
#include "NPC.hpp"
#include "Monster.hpp"
#include "spawn.hpp"
#include "OpCodes.hpp"
#include "utils.hpp"
#include "plugins.hpp"
#include "World.hpp"


#define MAX_BYTE	3
#define MAX_USHORT	5
#define MAX_UINT	10
#define MAX_ULONG	20
#define MAX_FLOAT	20

#define LV_Max 120
#define walk_speed 40

/*********************************************************************
 * WARNING :
 *	If something have changed inside "sharun_t" structure or
 *	sub-part, please incrase "sharun_t.version" of 1 more.
 * 		(A plugin without same "sharun_t.version" will be not
 * 		loaded by Sharun Plugin Manager).
 *********************************************************************/
typedef struct sharun_t {
	static const uint version = 1;
	struct Players {
		player**	Lists;
		pthread_mutex_t	mtx;
	} Players;
	settings	Settings;
	opcodes 	OpCodes;
} sharun_t;

extern sharun_t *Sharun;

extern ushort var_NBR[0xffff];

#ifdef DLL_VERSION
extern int	(*DB_getEquipment)(void*, enum SlotType, long);
extern char	(*DB_getEquipment_Ench)(void*, enum SlotType, long);
extern char	(*DB_getEquipment_Max)(void*, enum SlotType, long);
#else
extern "C" {
int	DB_getEquipment(void*, enum SlotType, long);
char	DB_getEquipment_Ench(void*, enum SlotType, long);
char	DB_getEquipment_Max(void*, enum SlotType, long);
}
#endif // DLL_VERSION

#endif // _SHARUN_HPP_
