#include "Sharun.hpp"

void* S_ARTISAN_RECIPE_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];
/*
	uint value[] = { 23001, 1022, 2, 1002, 2, 1631, 2, 0, 0};
	ushort Artisan_Count = 0, Artisan_Mat_Count = 0;
	for (int i=0; value[i]; i++) {
		i+=3;
		while (value[i]) {
			i+=2;
			Artisan_Mat_Count++;
		}
		Artisan_Count++;
	}
*/
	packet* packet_l /*= new_packet(S_ARTISAN_RECIPE_LIST, 6 + Artisan_Count * 50 + Artisan_Mat_Count * 17);

	packet_l->write_2(Artisan_Count);
	ushort Next = packet_l->write_NextPos();

	packet_l->write_2(0);

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		ushort Mat_count_pos	= packet_l->write_NextPos();
		ushort Mat_pos		= packet_l->write_NextPos();
		packet_l->write_4(value[i]);	// Design
		packet_l->write_8(21);	// ???
		packet_l->write_4(value[i+1]);	// reward
		packet_l->write_4(value[i+2]);	//	reward count

		packet_l->write_4(-1);
		packet_l->write_2(0);
		packet_l->write_1(0);
		packet_l->write_1(128);
		packet_l->write_1(63);
		packet_l->write_1(59);
		packet_l->write_1(222);
		packet_l->write_1(156);
		packet_l->write_1(87);
		packet_l->write_1(0);
		packet_l->write_4(0);
		packet_l->write_4(2);

		ushort Mat_count = 0;
		for (i+=3; value[i]; i+=2) {
			packet_l->write_Pos(Mat_pos);
			packet_l->write_Pos(0);	// this Materials pos
			Mat_pos = packet_l->write_NextPos();	// this Materials next

			packet_l->write_4(value[i]);	// Materials ID
			packet_l->write_4(value[i+1]);	// Materials cound need

			packet_l->write_4(-1);
			packet_l->write_1(0);
			Mat_count++;
		}
		packet_l->swap(Mat_count_pos);
		packet_l->write_2(Mat_count);
		packet_l->swap();
	}

	player_l->Send(packet_l);



	packet_l*/ = new_packet(S_ARTISAN_RECIPE_LIST, 6);

	packet_l->write_4(0);
//	packet_l->write_2(257);
	packet_l->write_1(0);
	packet_l->write_1(1);

	player_l->Send(packet_l);

	return NULL;
}
