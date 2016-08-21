#include "Sharun.hpp"

void* S_UPDATE_FRIEND_INFO_f(const void** argv)
{/*
	short i = 0;
	player*	player_l = (player*)argv[i++];
	packet* packet_l = new_packet(S_UPDATE_FRIEND_INFO, 4);

	packet_l->write_4(0);
*/

	const char*	value[] = { "456789", "WistiShite", "Bad Monkey", "Gni ha ha ha", NULL };

	ushort count = 0;
	ushort countSize = 0;
	for (ushort i=0; value[i]; i+=4) {
		count++;
		for (ushort j=1; j<3; j++)
			countSize += sizeof(value[j]);
	}

	player*	player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_UPDATE_FRIEND_INFO, 2 + count * 63 + countSize);

	packet_l->write_2(count);
	ushort nextPos = packet_l->write_NextPos();

	for (ushort i=0; value[i]; i+=4) {
		packet_l->write_Pos(nextPos);
		packet_l->write_Pos(0);
		nextPos = packet_l->write_NextPos();

		ushort NamePos = packet_l->write_NextPos();
		ushort CommPos = packet_l->write_NextPos();
		ushort MessPos = packet_l->write_NextPos();

		packet_l->write_4(atoi(value[i]));	// Player ID

		packet_l->write_4(2);	// group ... 1 = Waiting agree

		packet_l->write_4(0);	// ???

		packet_l->write_4(26);	// level
		packet_l->write_4(4);	// race
		packet_l->write_4(6);	// class

		/* bonds lv1 = 0-49 ; lv2 = 50-99 ; lv3 = 100-299 ; lv4 = 300-499 ; lv5 = 500-999 ; lv6 = 1000-9999 */
		packet_l->write_4(1);	// Friendship bonds

		packet_l->write_4(1);	// Zone Data 1
		packet_l->write_4(1);	// Zone Data 2
		packet_l->write_4(1);	// Zone Data 3

		packet_l->write_1(1);	// ? Logged ?

		packet_l->write_1(0);	// GM Icon ?

		packet_l->write_8(15081850);	// last loged time

		packet_l->write_Pos(NamePos);
		packet_l->write_C(value[i+1]);

		packet_l->write_Pos(CommPos);
		packet_l->write_C(value[i+2]);

		packet_l->write_Pos(MessPos);
		packet_l->write_C(value[i+3]);
	}

	player_l->Send(packet_l);

	return packet_l;
}
