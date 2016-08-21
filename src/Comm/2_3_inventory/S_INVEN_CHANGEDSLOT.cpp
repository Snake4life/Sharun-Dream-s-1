#include "Sharun.hpp"

void* S_INVEN_CHANGEDSLOT_f(const void** argv)
{
	player*	player_l = (player*) argv[0];
//	short*	slot = (short*) argv[1];

	ushort slot_count = player_l->Items.slot_count*8;
	packet*	packet_l = new_packet(S_INVEN_CHANGEDSLOT, 4 + slot_count * 9);

	packet_l->write_2(slot_count);//);1); // Count
	packet_l->write_2(8);

	ushort next = 0;
	for (ushort inv_pos=0; inv_pos < slot_count; inv_pos++) {
		if (next) packet_l->write_Pos(next);
		packet_l->write_2(packet_l->pos); // Actual
		next = packet_l->pos;
		packet_l->write_2(0); // Next
		packet_l->write_1(0); // Next
		packet_l->write_4(inv_pos+1); // slot id
	}

	player_l->Send(packet_l);
	return NULL;
}
