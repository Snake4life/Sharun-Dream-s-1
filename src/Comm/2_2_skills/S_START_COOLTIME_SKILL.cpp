#include "Sharun.hpp"

void* S_START_COOLTIME_SKILL_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
	uint*	Skill_Id = (uint*)argv[1];
	uint*	Delay = (uint*)argv[2];
	packet* packet_l = new_packet(S_START_COOLTIME_SKILL, 8);

	packet_l->write_4(*Skill_Id);
	packet_l->write_4(*Delay);

	player_l->Send(packet_l);
	return NULL;
}
