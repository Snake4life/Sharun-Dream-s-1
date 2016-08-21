#include "Sharun.hpp"

void* S_MOUNT_VEHICLE_f(const void** argv)
{
	player*	player_l = (player*)argv[0];

	if (!player_l->Mount)
		return NULL;

	packet* packet_l = new_packet(S_MOUNT_VEHICLE, 17);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	packet_l->write_4(player_l->Mount->Mount_Id); // mountId
	packet_l->write_4(player_l->Mount->Skill_Id); // skillId

	packet_l->write_1(0);

	return packet_l;
}
