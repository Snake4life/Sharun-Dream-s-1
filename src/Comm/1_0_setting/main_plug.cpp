#include "Sharun.hpp"

void* C_SAVE_CHAT_SETTING_f(player*, packet*);
void* C_SAVE_CLIENT_ACCOUNT_SETTING_f(player*, packet*);
void* C_SAVE_CLIENT_USER_SETTING_f(player*, packet*);

void* S_LOAD_CHAT_SETTING_f(const void**);
void* S_LOAD_CLIENT_ACCOUNT_SETTING_f(const void**);
void* S_LOAD_CLIENT_USER_SETTING_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_SAVE_CHAT_SETTING, "C_SAVE_CHAT_SETTING", (void*(*)(const void**)) C_SAVE_CHAT_SETTING_f },
		{ C_SAVE_CLIENT_ACCOUNT_SETTING, "C_SAVE_CLIENT_ACCOUNT_SETTING", (void*(*)(const void**)) C_SAVE_CLIENT_ACCOUNT_SETTING_f },
		{ C_SAVE_CLIENT_USER_SETTING, "C_SAVE_CLIENT_USER_SETTING", (void*(*)(const void**)) C_SAVE_CLIENT_USER_SETTING_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_LOAD_CHAT_SETTING, "S_LOAD_CHAT_SETTING", S_LOAD_CHAT_SETTING_f },
		{ S_LOAD_CLIENT_ACCOUNT_SETTING, "S_LOAD_CLIENT_ACCOUNT_SETTING", S_LOAD_CLIENT_ACCOUNT_SETTING_f },
		{ S_LOAD_CLIENT_USER_SETTING, "S_LOAD_CLIENT_USER_SETTING", S_LOAD_CLIENT_USER_SETTING_f },

		{ OPC_MAX, NULL, NULL }
	},
};

