#include "Sharun.hpp"


void* S_ARTISAN_SKILL_LIST_f(const void**);
void* S_ARTISAN_RECIPE_LIST_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_ARTISAN_SKILL_LIST, "S_ARTISAN_SKILL_LIST", S_ARTISAN_SKILL_LIST_f },
		{ S_ARTISAN_RECIPE_LIST, "S_ARTISAN_RECIPE_LIST", S_ARTISAN_RECIPE_LIST_f },

		{ OPC_MAX, NULL, NULL }
	},
};

