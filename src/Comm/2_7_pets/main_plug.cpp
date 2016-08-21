#include "Sharun.hpp"



plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){

		{ OPC_MAX, NULL, NULL }
	},
};

