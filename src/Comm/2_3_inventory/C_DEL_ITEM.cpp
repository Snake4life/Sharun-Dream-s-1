#include "Sharun.hpp"

void* C_DEL_ITEM_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	packet_l->read_4(); // Player ID
	packet_l->read_4(); // Sub ID

	ushort slot = packet_l->read_2(); // Slot
	slot += 39;

	packet_l->read_2();
	ushort item_count = packet_l->read_2(); // Item Count

	player_l->Items.slot[slot].count -= item_count;
	Sharun->DB.Query_Slow("UPDATE `character_items` SET `item_count` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", player_l->Items.slot[slot].count, player_l->Id, player_l->Items.slot[slot].id);
	if (player_l->Items.slot[slot].count <= 0) {
		player_l->Items.slot[slot].Item = NULL;
		Sharun->DB.Query_Slow("DELETE FROM `character_items` WHERE `owner_id` = '%i' AND `object_id` = '%i';", player_l->Id, player_l->Items.slot[slot].id);
	}

	Sharun->OpCodes.Send[S_INVEN](args);


	return NULL;
}
