#include "Sharun.hpp"

void* S_UNMOUNT_VEHICLE_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_UNMOUNT_VEHICLE, 12);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);
	packet_l->write_4(player_l->Mount->Skill_Id);

	return packet_l;
}
