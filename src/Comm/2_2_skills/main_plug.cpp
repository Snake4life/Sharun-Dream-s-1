#include "Sharun.hpp"

void* C_SKILL_LEARN_LIST_f(player*, packet*);
void* C_START_SKILL_f(player*, packet*);

void* S_START_COOLTIME_SKILL_f(const void**);
void* S_SKILL_LEARN_LIST_f(const void**);
void* S_SKILL_LIST_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_SKILL_LEARN_LIST, "C_SKILL_LEARN_LIST", (void*(*)(const void**)) C_SKILL_LEARN_LIST_f },
		{ C_START_SKILL, "C_START_SKILL", (void*(*)(const void**)) C_START_SKILL_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_START_COOLTIME_SKILL, "S_START_COOLTIME_SKILL", S_START_COOLTIME_SKILL_f },
		{ S_SKILL_LEARN_LIST, "S_SKILL_LEARN_LIST", S_SKILL_LEARN_LIST_f },
		{ S_SKILL_LIST, "S_SKILL_LIST", S_SKILL_LIST_f },

		{ OPC_MAX, NULL, NULL }
	},
};

