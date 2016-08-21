#include "Sharun.hpp"

void* C_MOVE_INVEN_POS_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	packet_l->read_4(); // Player ID
	packet_l->read_4(); // Sub ID

	ushort slot1 = packet_l->read_4(); // Slot1
	slot1--;
	ushort slot2 = packet_l->read_4(); // Slot2
	slot2--;

			if (player_l->Items.slot[slot2].Item) Sharun->DB.Query_Slow("UPDATE `character_items` SET `index` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", slot1, player_l->Id, player_l->Items.slot[slot2].id);
			if (player_l->Items.slot[slot1].Item) Sharun->DB.Query_Slow("UPDATE `character_items` SET `index` = '%i' WHERE `owner_id` = '%i' AND `object_id` = '%i';", slot2, player_l->Id, player_l->Items.slot[slot1].id);

	item_slot Item_slot_tmp;
	memcpy(&Item_slot_tmp, &player_l->Items.slot[slot1], sizeof(item_slot));
	memcpy(&player_l->Items.slot[slot1], &player_l->Items.slot[slot2], sizeof(item_slot));
	memcpy(&player_l->Items.slot[slot2], &Item_slot_tmp, sizeof(item_slot));

	Sharun->OpCodes.Send[S_INVEN](args);

	return NULL;
}
