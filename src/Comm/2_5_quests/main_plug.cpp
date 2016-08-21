#include "Sharun.hpp"


void* S_COMPLETED_MISSION_INFO_f(const void**);
void* S_DAILY_QUEST_COMPLETE_COUNT_f(const void**);
void* S_CLEAR_QUEST_INFO_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_COMPLETED_MISSION_INFO, "S_COMPLETED_MISSION_INFO", S_COMPLETED_MISSION_INFO_f },
		{ S_DAILY_QUEST_COMPLETE_COUNT, "S_DAILY_QUEST_COMPLETE_COUNT", S_DAILY_QUEST_COMPLETE_COUNT_f },
		{ S_CLEAR_QUEST_INFO, "S_CLEAR_QUEST_INFO", S_CLEAR_QUEST_INFO_f },

		{ OPC_MAX, NULL, NULL }
	},
};

