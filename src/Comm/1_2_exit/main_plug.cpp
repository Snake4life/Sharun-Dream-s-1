#include "Sharun.hpp"

void* C_CANCEL_EXIT_f(player*, packet*);
void* C_CANCEL_RETURN_TO_LOBBY_f(player*, packet*);
void* C_RETURN_TO_LOBBY_f(player*, packet*);
void* C_EXIT_f(player*, packet*);

void* S_CANCEL_EXIT_f(const void**);
void* S_PREPARE_RETURN_TO_LOBBY_f(const void**);
void* S_RETURN_TO_LOBBY_f(const void**);
void* S_EXIT_f(const void**);
void* S_PREPARE_EXIT_f(const void**);
void* S_CANCEL_RETURN_TO_LOBBY_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_CANCEL_EXIT, "C_CANCEL_EXIT", (void*(*)(const void**)) C_CANCEL_EXIT_f },
		{ C_CANCEL_RETURN_TO_LOBBY, "C_CANCEL_RETURN_TO_LOBBY", (void*(*)(const void**)) C_CANCEL_RETURN_TO_LOBBY_f },
		{ C_RETURN_TO_LOBBY, "C_RETURN_TO_LOBBY", (void*(*)(const void**)) C_RETURN_TO_LOBBY_f },
		{ C_EXIT, "C_EXIT", (void*(*)(const void**)) C_EXIT_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_CANCEL_EXIT, "S_CANCEL_EXIT", S_CANCEL_EXIT_f },
		{ S_PREPARE_RETURN_TO_LOBBY, "S_PREPARE_RETURN_TO_LOBBY", S_PREPARE_RETURN_TO_LOBBY_f },
		{ S_RETURN_TO_LOBBY, "S_RETURN_TO_LOBBY", S_RETURN_TO_LOBBY_f },
		{ S_EXIT, "S_EXIT", S_EXIT_f },
		{ S_PREPARE_EXIT, "S_PREPARE_EXIT", S_PREPARE_EXIT_f },
		{ S_CANCEL_RETURN_TO_LOBBY, "S_CANCEL_RETURN_TO_LOBBY", S_CANCEL_RETURN_TO_LOBBY_f },

		{ OPC_MAX, NULL, NULL }
	},
};

