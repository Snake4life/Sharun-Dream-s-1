#include "Sharun.hpp"

#ifdef DLL_VERSION

sharun_t *Sharun;
ushort var_NBR[0xffff];

void (*DEBUG)(const char*, ...);
void (*DEBUG2)(const char*, ...);

uint	(*SQL_Num_Rows_PLG)(void*);
void	(*SQL_Data_Seek_PLG)(void*, ulong);
char**	(*SQL_Fetch_Row_PLG)(void*);
void	(*SQL_Free_Result_PLG)(void*);
void	(*SQL_Add_PLG)(SQL_QUEUE*);

void	(*free_player)(player*);
packet*	(*new_packet)(OpCode_Enum, int);
void*	(*packet_send_empty)(OpCode_Enum, const void**);
int	(*Send_Packet)(player*, packet*);
void	(*player_Load)(player*, uint);
void	(*player_Save)(player*);
void	(*Stats_Update)(player*);

int	(*DB_getEquipment)(void*, enum SlotType, long);
char	(*DB_getEquipment_Ench)(void*, enum SlotType, long);
char	(*DB_getEquipment_Max)(void*, enum SlotType, long);

ulong	(*get_Experience_LEVEL)(ushort);
void	(*World_Spam)(player*);
void	(*World_Exit)(player*);
void	(*World_Chat)(player*, CHAT_TYPE, const char*, const char*, const char16_t*);
void	(*World_PlayerMove)(player*, ushort);
void	(*World_PlayerSocial)(player*, bool, int);
void	(*World_PlayerMount)(player*, bool, uint);
void	(*World_PlayerSkill)(player*, player*, uint, ushort, float*, float*);

void	(*BroadcastD_Add)(packet*);
void	(*BroadcastD_Greet)(player*, OpCode_Enum, BROADCAST_TYPE);

extern "C" {

void CallBack_Plugin(void** Link)
{
	for (ushort j=0; j < 0xffff; j++)
		var_NBR[j] = j;
	uint i = 0;
	Sharun = (sharun_t*) Link[i++];

	DEBUG = (void (*)(const char*, ...)) Link[i++];
	DEBUG2 = (void (*)(const char*, ...)) Link[i++];

	SQL_Num_Rows_PLG = (uint (*)(void*)) Link[i++];
	SQL_Data_Seek_PLG = (void (*)(void*, ulong)) Link[i++];
	SQL_Fetch_Row_PLG = (char** (*)(void*)) Link[i++];
	SQL_Free_Result_PLG = (void (*)(void*)) Link[i++];
	SQL_Add_PLG = (void (*)(SQL_QUEUE*)) Link[i++];

	free_player = (void (*)(player*)) Link[i++];
	new_packet = (packet* (*)(OpCode_Enum, int)) Link[i++];
	packet_send_empty = (void* (*)(OpCode_Enum, const void**)) Link[i++];
	Send_Packet = (int (*)(player*, packet*)) Link[i++];
	player_Load = (void (*)(player*, uint)) Link[i++];
	player_Save = (void (*)(player*)) Link[i++];
	Stats_Update = (void (*)(player*)) Link[i++];

	DB_getEquipment = (int (*)(void*, enum SlotType, long)) Link[i++];
	DB_getEquipment_Ench = (char (*)(void*, enum SlotType, long)) Link[i++];
	DB_getEquipment_Max = (char (*)(void*, enum SlotType, long)) Link[i++];

	get_Experience_LEVEL = (ulong (*)(ushort)) Link[i++];
	World_Spam = (void (*)(player*)) Link[i++];
	World_Exit = (void (*)(player*)) Link[i++];
	World_Chat = (void (*)(player*, CHAT_TYPE, const char*, const char*, const char16_t*)) Link[i++];
	World_PlayerMove = (void (*)(player*, ushort)) Link[i++];
	World_PlayerSocial = (void (*)(player*, bool, int)) Link[i++];
	World_PlayerMount = (void (*)(player*, bool, uint)) Link[i++];
	World_PlayerSkill = (void (*)(player*, player*, uint, ushort, float*, float*)) Link[i++];

	BroadcastD_Add = (void (*)(packet*)) Link[i++];
	BroadcastD_Greet = (void (*)(player*, OpCode_Enum, BROADCAST_TYPE)) Link[i++];

}

}

#endif // DLL_VERSION
