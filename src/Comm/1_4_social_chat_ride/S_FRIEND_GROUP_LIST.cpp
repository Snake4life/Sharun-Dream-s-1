#include "Sharun.hpp"

void* S_FRIEND_GROUP_LIST_f(const void** argv)
{
	const char*	value[] = { "2", "Best Friends", NULL };

	ushort count = 0;
	ushort countSize = 0;
	for (ushort i=0; value[i]; i+=2) {
		count++;
		countSize += sizeof(value[i+1]);
	}

	player*	player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_FRIEND_GROUP_LIST, 4 + count * 10 + countSize);

	packet_l->write_2(count);
	ushort nextPos = packet_l->write_NextPos();

	for (ushort i=0; value[i]; i+=2) {
		packet_l->write_Pos(nextPos);
		packet_l->write_Pos(0);
		nextPos = packet_l->write_NextPos();

		ushort NamePos = packet_l->write_NextPos();
		packet_l->write_4(atoi(value[i]));	// ID Group ?
		packet_l->write_Pos(NamePos);
		packet_l->write_C(value[i+1]);
	}

	player_l->Send(packet_l);

	return packet_l;
}
