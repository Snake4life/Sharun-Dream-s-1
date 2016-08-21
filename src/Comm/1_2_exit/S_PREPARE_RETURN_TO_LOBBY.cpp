#include "Sharun.hpp"

void* S_PREPARE_RETURN_TO_LOBBY_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_PREPARE_RETURN_TO_LOBBY, 4);

	packet_l->write_4(Sharun->Settings.Confirm_Time);

	player_l->Send(packet_l);

	player_l->exit_type = 2;
	player_l->exit_time = time(NULL) + Sharun->Settings.Confirm_Time;
	return NULL;
}
