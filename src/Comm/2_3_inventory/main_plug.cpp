#include "Sharun.hpp"

void* C_EQUIP_ITEM_f(player*, packet*);
void* C_SHOW_INVEN_f(player*, packet*);
void* C_MOVE_INVEN_POS_f(player*, packet*);
void* C_UNEQUIP_ITEM_f(player*, packet*);
void* C_DEL_ITEM_f(player*, packet*);
void* C_SHOW_ITEM_TOOLTIP_EX_f(player*, packet*);

void* S_INVEN_f(const void**);
void* S_UNEQUIP_ITEM_f(const void**);
void* S_INVEN_CHANGEDSLOT_f(const void**);
void* S_ITEM_CUSTOM_STRING_f(const void**);
void* S_SHOW_ITEM_TOOLTIP_f(const void**);
void* S_EQUIP_ITEM_f(const void**);
void* S_USER_ITEM_EQUIP_CHANGER_f(const void**);

plugin_t Plugin = {
	.handle = NULL,
	.init = NULL,
	.uninit = NULL,
	.recv = (plugin_opcode_t[]){
		{ C_EQUIP_ITEM, "C_EQUIP_ITEM", (void*(*)(const void**)) C_EQUIP_ITEM_f },
		{ C_SHOW_INVEN, "C_SHOW_INVEN", (void*(*)(const void**)) C_SHOW_INVEN_f },
		{ C_MOVE_INVEN_POS, "C_MOVE_INVEN_POS", (void*(*)(const void**)) C_MOVE_INVEN_POS_f },
		{ C_UNEQUIP_ITEM, "C_UNEQUIP_ITEM", (void*(*)(const void**)) C_UNEQUIP_ITEM_f },
		{ C_DEL_ITEM, "C_DEL_ITEM", (void*(*)(const void**)) C_DEL_ITEM_f },
		{ C_SHOW_ITEM_TOOLTIP_EX, "C_SHOW_ITEM_TOOLTIP_EX", (void*(*)(const void**)) C_SHOW_ITEM_TOOLTIP_EX_f },

		{ OPC_MAX, NULL, NULL }
	},
	.send = (plugin_opcode_t[]){
		{ S_INVEN, "S_INVEN", S_INVEN_f },
		{ S_UNEQUIP_ITEM, "S_UNEQUIP_ITEM", S_UNEQUIP_ITEM_f },
		{ S_INVEN_CHANGEDSLOT, "S_INVEN_CHANGEDSLOT", S_INVEN_CHANGEDSLOT_f },
		{ S_ITEM_CUSTOM_STRING, "S_ITEM_CUSTOM_STRING", S_ITEM_CUSTOM_STRING_f },
		{ S_SHOW_ITEM_TOOLTIP, "S_SHOW_ITEM_TOOLTIP", S_SHOW_ITEM_TOOLTIP_f },
		{ S_EQUIP_ITEM, "S_EQUIP_ITEM", S_EQUIP_ITEM_f },
		{ S_USER_ITEM_EQUIP_CHANGER, "S_USER_ITEM_EQUIP_CHANGER", S_USER_ITEM_EQUIP_CHANGER_f },

		{ OPC_MAX, NULL, NULL }
	},
};

