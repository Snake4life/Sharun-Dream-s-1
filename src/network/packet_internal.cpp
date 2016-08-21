#include <Dream/Dream.hpp>

packet* new_packet(OpCode_Enum Op_ID, int initial_size)
{
	packet* packet_l = new packet(initial_size);
	packet_l->Op_ID = Op_ID;
	return packet_l;
}

void* packet_send_empty(OpCode_Enum Op_ID, const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(Op_ID, 0);

	player_l->Send(packet_l);
	return NULL;
}
