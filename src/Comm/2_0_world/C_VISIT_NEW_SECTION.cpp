#include "Sharun.hpp"

void* C_VISIT_NEW_SECTION_f(player* player_l, packet* packet_l)
{
	player_l->country = packet_l->read_4();
	player_l->lander = packet_l->read_4();
	player_l->aera = packet_l->read_4();

	const char* SQL = "UPDATE `characters` SET `country` = '%i', `lander` = '%i', `aera` = '%i' WHERE `object_id` = '%ld';";
	Sharun->DB.Query_Slow(SQL, player_l->country, player_l->lander, player_l->aera, player_l->Id);

	return NULL;
}
