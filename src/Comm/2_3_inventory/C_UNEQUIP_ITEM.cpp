#include "Sharun.hpp"

void* C_UNEQUIP_ITEM_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	packet_l->read_4(); // Player ID
	packet_l->read_4(); // Sub ID

	ushort slot = packet_l->read_2(); // Slot
	slot--;

	packet_l->read_2();
	packet_l->read_4();

	uint item_id = packet_l->read_4(); // Item ID

	short inv_pos = 39;
	ulong obj_id = 0;
	bool changed = false;
	if (!player_l->Items.slot[slot].Item) return NULL;
	if (player_l->Items.slot[slot].Item->id == item_id) {
		while (player_l->Items.slot[inv_pos].Item && inv_pos < 39+player_l->Items.slot_count*8) inv_pos++;
		if (inv_pos >= 39+player_l->Items.slot_count*8) {
			player_l->Chat(SYSTEM_CHAT, NULL, u"Inventory is full !");
			return NULL;
		} else {
			memcpy(&player_l->Items.slot[inv_pos], &player_l->Items.slot[slot], sizeof(item_slot));
			player_l->Items.slot[slot].Item = NULL;
			Sharun->DB.Query_Slow("UPDATE `character_items` SET `index` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", inv_pos, player_l->Id, player_l->Items.slot[slot].id);
			obj_id = player_l->Items.slot[inv_pos].id;
			changed = true;
		}
	}

	if (changed) {
//		packet * packet_buf = Sharun->OpCodes.Send[S_USER_EXTERNAL_CHANGE](args);
//		packet_buf->BC_Type = BC_TYPE_ARROUND;
//		packet_buf->Sender = player;
////		S_USER_STATUS_f(player);
		if ( inv_pos < SLOT_HAT
		  || inv_pos == SLOT_BELT
		  || inv_pos == SLOT_BROOCH )
			Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
		Sharun->OpCodes.Send[S_INVEN](args);
		args[1] = &obj_id;
		Sharun->OpCodes.Send[S_UNEQUIP_ITEM](args);
////		inv_pos -= 39+1;
////		args[1] = &inv_pos;
////		Sharun->OpCodes.Send[S_INVEN_CHANGEDSLOT](args);(player_l, inv_pos-39+1);
//		BroadcastD_Add(packet_buf);
	}


	return NULL;
}
