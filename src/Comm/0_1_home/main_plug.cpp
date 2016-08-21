#include "Sharun.hpp"

void* C_DELETE_USER_f(player*, packet*);
void* C_GET_USER_LIST_f(player*, packet*);
void* C_CHECK_USERNAME_f(player*, packet*);
void* C_CAN_CREATE_USER_f(player*, packet*);
void* C_CREATE_USER_f(player*, packet*);
void* C_SELECT_USER_f(player*, packet*);

void* S_DELETE_USER_f(const void**);
void* S_SELECT_USER_f(const void**);
void* S_CAN_CREATE_USER_f(const void**);
void* S_GET_USER_LIST_f(const void**);
void* S_LOGIN_f(const void**);
void* S_CREATE_USER_f(const void**);
void* S_CHECK_USERNAME_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_DELETE_USER, "C_DELETE_USER", (void*(*)(const void**)) C_DELETE_USER_f },
		{ C_GET_USER_LIST, "C_GET_USER_LIST", (void*(*)(const void**)) C_GET_USER_LIST_f },
		{ C_CHECK_USERNAME, "C_CHECK_USERNAME", (void*(*)(const void**)) C_CHECK_USERNAME_f },
		{ C_CAN_CREATE_USER, "C_CAN_CREATE_USER", (void*(*)(const void**)) C_CAN_CREATE_USER_f },
		{ C_CREATE_USER, "C_CREATE_USER", (void*(*)(const void**)) C_CREATE_USER_f },
		{ C_SELECT_USER, "C_SELECT_USER", (void*(*)(const void**)) C_SELECT_USER_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_DELETE_USER, "S_DELETE_USER", S_DELETE_USER_f },
		{ S_SELECT_USER, "S_SELECT_USER", S_SELECT_USER_f },
		{ S_CAN_CREATE_USER, "S_CAN_CREATE_USER", S_CAN_CREATE_USER_f },
		{ S_GET_USER_LIST, "S_GET_USER_LIST", S_GET_USER_LIST_f },
		{ S_LOGIN, "S_LOGIN", S_LOGIN_f },
		{ S_CREATE_USER, "S_CREATE_USER", S_CREATE_USER_f },
		{ S_CHECK_USERNAME, "S_CHECK_USERNAME", S_CHECK_USERNAME_f },

		{ OPC_MAX, NULL, NULL }
	},
};

