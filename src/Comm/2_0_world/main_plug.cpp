#include "Sharun.hpp"

void* C_PLAYER_LOCATION_f(player*, packet*);
void* C_LOAD_TOPO_FIN_f(player*, packet*);
void* C_VISIT_NEW_SECTION_f(player*, packet*);
void* C_SET_VISIBLE_RANGE_f(player*, packet*);

void* S_LOAD_HINT_f(const void**);
void* S_SPAWN_ME_f(const void**);
void* S_LOAD_TOPO_f(const void**);
void* S_SPAWN_USER_f(const void**);
void* S_SPAWN_NPC_f(const void**);
void* S_NPC_LOCATION_f(const void**);
void* S_DESPAWN_NPC_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_PLAYER_LOCATION, "C_PLAYER_LOCATION", (void*(*)(const void**)) C_PLAYER_LOCATION_f },
		{ C_LOAD_TOPO_FIN, "C_LOAD_TOPO_FIN", (void*(*)(const void**)) C_LOAD_TOPO_FIN_f },
		{ C_VISIT_NEW_SECTION, "C_VISIT_NEW_SECTION", (void*(*)(const void**)) C_VISIT_NEW_SECTION_f },
		{ C_SET_VISIBLE_RANGE, "C_SET_VISIBLE_RANGE", (void*(*)(const void**)) C_SET_VISIBLE_RANGE_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_LOAD_HINT, "S_LOAD_HINT", S_LOAD_HINT_f },
		{ S_SPAWN_ME, "S_SPAWN_ME", S_SPAWN_ME_f },
		{ S_LOAD_TOPO, "S_LOAD_TOPO", S_LOAD_TOPO_f },
		{ S_SPAWN_USER, "S_SPAWN_USER", S_SPAWN_USER_f },
		{ S_SPAWN_NPC, "S_SPAWN_NPC", S_SPAWN_NPC_f },
		{ S_NPC_LOCATION, "S_NPC_LOCATION", S_NPC_LOCATION_f },
		{ S_DESPAWN_NPC, "S_DESPAWN_NPC", S_DESPAWN_NPC_f },

		{ OPC_MAX, NULL, NULL }
	},
};

