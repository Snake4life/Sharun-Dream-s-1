#include "Sharun.hpp"

void* C_PLAYER_LOCATION_f(player* player_l, packet* packet_l)
{
	for (int i=0; i<3; i++)
		player_l->DjW->XYZ[i] = packet_l->read_F();

	player_l->DjW->heading = packet_l->read_2();

	packet_l->read_2();

	//целевая точка
	for (int i=0; i<3; i++)
		player_l->DjW->toXYZ[i] = packet_l->read_F();

	//тип перемещения
	player_l->moveType[1] = packet_l->read_2();
/*
	packet_l->read_1();
	packet_l->read_4();
	packet_l->read_4();
*/

	World_PlayerMove(player_l, player_l->moveType[1]);

	player_l->moveType[0] = player_l->moveType[1];
	return NULL;
}
