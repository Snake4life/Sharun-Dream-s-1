#include "Sharun.hpp"


void* S_CREATURE_CHANGE_HP_f(const void**);
void* S_USER_STATUS_f(const void**);
void* S_PLAYER_CHANGE_MP_f(const void**);
void* S_PLAYER_STAT_UPDATE_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_CREATURE_CHANGE_HP, "S_CREATURE_CHANGE_HP", S_CREATURE_CHANGE_HP_f },
		{ S_USER_STATUS, "S_USER_STATUS", S_USER_STATUS_f },
		{ S_PLAYER_CHANGE_MP, "S_PLAYER_CHANGE_MP", S_PLAYER_CHANGE_MP_f },
		{ S_PLAYER_STAT_UPDATE, "S_PLAYER_STAT_UPDATE", S_PLAYER_STAT_UPDATE_f },

		{ OPC_MAX, NULL, NULL }
	},
};

