#include "Sharun.hpp"

void* C_EQUIP_ITEM_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	packet_l->read_4(); // Player ID
	packet_l->read_4(); // Sub ID

	ushort slot = packet_l->read_2(); // Slot
	slot--;

//	packet_l->read_2();
//	packet_l->read_4();

//	uint item_id = packet_l->read_4(); // Item ID

	short dest_pos = -1;
	bool changed = false;
	if (!player_l->Items.slot[slot].Item) return NULL;
	if (player_l->Items.slot[slot].binded && player_l->Items.slot[slot].binded != player_l->Id) {
		player_l->Chat(SYSTEM_CHAT, NULL, u"You can't equip this item (not linked to your) !");
		return NULL;
	}

	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_WEAPON")) {
		dest_pos = SLOT_WEAPON;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ARMOR_BODY")) {
		dest_pos = SLOT_ARMOR;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ARMOR_ARM")) {
		dest_pos = SLOT_GLOVES;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ARMOR_LEG")) {
		dest_pos = SLOT_BOOTS;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "necklace")) {
		dest_pos = SLOT_NECKLACE;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_UNDERWEAR")) {
		dest_pos = SLOT_SHIRT;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "accessoryHair")) {
		memcpy(&player_l->Items.slot[SLOT_HAT], &player_l->Items.slot[slot], sizeof(item_slot));
		dest_pos = SLOT_HAT;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "accessoryFace")) {
		dest_pos = SLOT_MASK;
		changed = true;
	} else 
	if ((!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") || !strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_STYLE_ACCESSORY")) && !strcmp(player_l->Items.slot[slot].Item->category, "style_hair")) {
		dest_pos = SLOT_APP_HAT;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_STYLE_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "style_face")) {
		dest_pos = SLOT_APP_MASK;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_STYLE_WEAPON")) {
		dest_pos = SLOT_APP_WEAPON;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_STYLE_BODY")) {
		dest_pos = SLOT_APP_ARMOR;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_STYLE_BACK")) {
		dest_pos = SLOT_APP_BACK;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "belt")) {
		dest_pos = SLOT_BELT;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "brooch")) {
		dest_pos = SLOT_BROOCH;
		changed = true;
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "earring")) {
		if (!player_l->Items.slot[SLOT_EARRING_L].Item) {
			dest_pos = SLOT_EARRING_L;
			changed = true;
		} else
		if (!player_l->Items.slot[SLOT_EARRING_R].Item) {
			dest_pos = SLOT_EARRING_R;
			changed = true;
		}
	} else 
	if (!strcmp(player_l->Items.slot[slot].Item->type, "EQUIP_ACCESSORY") && !strcmp(player_l->Items.slot[slot].Item->category, "ring")) {
		if (!player_l->Items.slot[SLOT_RING_L].Item) {
			dest_pos = SLOT_RING_L;
			changed = true;
		} else
		if (!player_l->Items.slot[SLOT_RING_R].Item) {
			dest_pos = SLOT_RING_R;
			changed = true;
		}
	}


	if (changed) {
		ulong obj_id = 0;
		if (dest_pos > -1) {
			if (player_l->Items.slot[dest_pos].Item) Sharun->DB.Query_Slow("UPDATE `character_items` SET `index` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", slot, player_l->Id, player_l->Items.slot[dest_pos].id);
			if (player_l->Items.slot[slot].Item) Sharun->DB.Query_Slow("UPDATE `character_items` SET `index` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", dest_pos, player_l->Id, player_l->Items.slot[slot].id);
			obj_id = player_l->Items.slot[slot].id;
			item_slot Item_slot_tmp;
			memcpy(&Item_slot_tmp, &player_l->Items.slot[dest_pos], sizeof(item_slot));
			memcpy(&player_l->Items.slot[dest_pos], &player_l->Items.slot[slot], sizeof(item_slot));
			memcpy(&player_l->Items.slot[slot], &Item_slot_tmp, sizeof(item_slot));
		}

		packet* packet_buf = (packet*) Sharun->OpCodes.Send[S_USER_EXTERNAL_CHANGE](args);
		packet_buf->BC_Type = BC_TYPE_ARROUND;
		packet_buf->sender = player_l;
		Sharun->OpCodes.Send[S_USER_STATUS](args);
		BroadcastD_Add(packet_buf);
		if ( dest_pos < SLOT_HAT
		  || dest_pos == SLOT_BELT
		  || dest_pos == SLOT_BROOCH )
			Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
		Sharun->OpCodes.Send[S_INVEN](args);
		if (dest_pos > -1) {
			args[1] = &obj_id;
			Sharun->OpCodes.Send[S_EQUIP_ITEM](args);
		}
////		dest_pos -=39+1
////		args[1] = &dest_pos;
////		Sharun->OpCodes.Send[S_INVEN_CHANGEDSLOT](args);
	}

	return NULL;
}
