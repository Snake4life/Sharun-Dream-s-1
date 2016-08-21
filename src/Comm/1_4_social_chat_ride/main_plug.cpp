#include "Sharun.hpp"

void* C_ADD_FRIEND_GROUP_f(player*, packet*);
void* C_WHISPER_f(player*, packet*);
void* C_CHAT_f(player*, packet*);
void* C_UPDATE_FRIEND_INFO_f(player*, packet*);
void* C_DELETE_FRIEND_f(player*, packet*);
void* C_UNMOUNT_VEHICLE_f(player*, packet*);
void* C_ADD_FRIEND_f(player*, packet*);
void* C_SOCIAL_f(player*, packet*);

void* S_USER_BLOCK_LIST_f(const void**);
void* S_AVAILABLE_SOCIAL_LIST_f(const void**);
void* S_FRIEND_LIST_f(const void**);
void* S_CHAT_f(const void**);
void* S_UPDATE_FRIEND_INFO_f(const void**);
void* S_FRIEND_GROUP_LIST_f(const void**);
void* S_MOUNT_VEHICLE_f(const void**);
void* S_SOCIAL_f(const void**);
void* S_WHISPER_f(const void**);
void* S_USER_EXTERNAL_CHANGE_f(const void**);
void* S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA_f(const void**);
void* S_UNMOUNT_VEHICLE_f(const void**);
void* S_CURRENT_CHANNEL_f(const void**);
void* S_SYSTEM_MESSAGE_f(const void**);
void* S_ANNOUNCE_MESSAGE_f(const void**);
void* S_SOCIAL_CANCEL_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_ADD_FRIEND_GROUP, "C_ADD_FRIEND_GROUP", (void*(*)(const void**)) C_ADD_FRIEND_GROUP_f },
		{ C_WHISPER, "C_WHISPER", (void*(*)(const void**)) C_WHISPER_f },
		{ C_CHAT, "C_CHAT", (void*(*)(const void**)) C_CHAT_f },
		{ C_UPDATE_FRIEND_INFO, "C_UPDATE_FRIEND_INFO", (void*(*)(const void**)) C_UPDATE_FRIEND_INFO_f },
		{ C_DELETE_FRIEND, "C_DELETE_FRIEND", (void*(*)(const void**)) C_DELETE_FRIEND_f },
		{ C_UNMOUNT_VEHICLE, "C_UNMOUNT_VEHICLE", (void*(*)(const void**)) C_UNMOUNT_VEHICLE_f },
		{ C_ADD_FRIEND, "C_ADD_FRIEND", (void*(*)(const void**)) C_ADD_FRIEND_f },
		{ C_SOCIAL, "C_SOCIAL", (void*(*)(const void**)) C_SOCIAL_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_USER_BLOCK_LIST, "S_USER_BLOCK_LIST", S_USER_BLOCK_LIST_f },
		{ S_AVAILABLE_SOCIAL_LIST, "S_AVAILABLE_SOCIAL_LIST", S_AVAILABLE_SOCIAL_LIST_f },
		{ S_FRIEND_LIST, "S_FRIEND_LIST", S_FRIEND_LIST_f },
		{ S_CHAT, "S_CHAT", S_CHAT_f },
		{ S_UPDATE_FRIEND_INFO, "S_UPDATE_FRIEND_INFO", S_UPDATE_FRIEND_INFO_f },
		{ S_FRIEND_GROUP_LIST, "S_FRIEND_GROUP_LIST", S_FRIEND_GROUP_LIST_f },
		{ S_MOUNT_VEHICLE, "S_MOUNT_VEHICLE", S_MOUNT_VEHICLE_f },
		{ S_SOCIAL, "S_SOCIAL", S_SOCIAL_f },
		{ S_WHISPER, "S_WHISPER", S_WHISPER_f },
		{ S_USER_EXTERNAL_CHANGE, "S_USER_EXTERNAL_CHANGE", S_USER_EXTERNAL_CHANGE_f },
		{ S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA, "S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA", S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA_f },
		{ S_UNMOUNT_VEHICLE, "S_UNMOUNT_VEHICLE", S_UNMOUNT_VEHICLE_f },
		{ S_CURRENT_CHANNEL, "S_CURRENT_CHANNEL", S_CURRENT_CHANNEL_f },
		{ S_SYSTEM_MESSAGE, "S_SYSTEM_MESSAGE", S_SYSTEM_MESSAGE_f },
		{ S_ANNOUNCE_MESSAGE, "S_ANNOUNCE_MESSAGE", S_ANNOUNCE_MESSAGE_f },
		{ S_SOCIAL_CANCEL, "S_SOCIAL_CANCEL", S_SOCIAL_CANCEL_f },

		{ OPC_MAX, NULL, NULL }
	},
};

