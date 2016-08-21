#include "Sharun.hpp"

void* C_UPDATE_CONTENTS_PLAYTIME_f(player*, packet*);
void* C_REQUEST_PING_f(player*, packet*);
void* C_SIMPLE_TIP_REPEAT_CHECK_f(player*, packet*);
void* C_PONG_f(player*, packet*);
void* C_REQUEST_GAMESTAT_PING_f(player*, packet*);
void* C_PING_f(player*, packet*);
void* C_SERVER_TIME_f(player*, packet*);

void* S_VIRTUAL_LATENCY_f(const void**);
void* S_SEND_USER_PLAY_TIME_f(const void**);
void* S_SIMPLE_TIP_REPEAT_CHECK_f(const void**);
void* S_RESPONSE_GAMESTAT_PONG_f(const void**);
void* S_PING_f(const void**);
void* S_RESPONSE_PONG_f(const void**);
void* S_SERVER_TIME_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_UPDATE_CONTENTS_PLAYTIME, "C_UPDATE_CONTENTS_PLAYTIME", (void*(*)(const void**)) C_UPDATE_CONTENTS_PLAYTIME_f },
		{ C_REQUEST_PING, "C_REQUEST_PING", (void*(*)(const void**)) C_REQUEST_PING_f },
		{ C_SIMPLE_TIP_REPEAT_CHECK, "C_SIMPLE_TIP_REPEAT_CHECK", (void*(*)(const void**)) C_SIMPLE_TIP_REPEAT_CHECK_f },
		{ C_PONG, "C_PONG", (void*(*)(const void**)) C_PONG_f },
		{ C_REQUEST_GAMESTAT_PING, "C_REQUEST_GAMESTAT_PING", (void*(*)(const void**)) C_REQUEST_GAMESTAT_PING_f },
		{ C_PING, "C_PING", (void*(*)(const void**)) C_PING_f },
		{ C_SERVER_TIME, "C_SERVER_TIME", (void*(*)(const void**)) C_SERVER_TIME_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_VIRTUAL_LATENCY, "S_VIRTUAL_LATENCY", S_VIRTUAL_LATENCY_f },
		{ S_SEND_USER_PLAY_TIME, "S_SEND_USER_PLAY_TIME", S_SEND_USER_PLAY_TIME_f },
		{ S_SIMPLE_TIP_REPEAT_CHECK, "S_SIMPLE_TIP_REPEAT_CHECK", S_SIMPLE_TIP_REPEAT_CHECK_f },
		{ S_RESPONSE_GAMESTAT_PONG, "S_RESPONSE_GAMESTAT_PONG", S_RESPONSE_GAMESTAT_PONG_f },
		{ S_PING, "S_PING", S_PING_f },
		{ S_RESPONSE_PONG, "S_RESPONSE_PONG", S_RESPONSE_PONG_f },
		{ S_SERVER_TIME, "S_SERVER_TIME", S_SERVER_TIME_f },

		{ OPC_MAX, NULL, NULL }
	},
};

