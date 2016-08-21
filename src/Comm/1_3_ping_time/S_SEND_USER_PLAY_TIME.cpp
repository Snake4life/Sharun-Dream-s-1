#include "Sharun.hpp"

void* S_SEND_USER_PLAY_TIME_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SEND_USER_PLAY_TIME, 12);

	const char *sql = "SELECT `online_time` FROM `characters` WHERE `object_id`='%i';";

	packet_l->write_4(Sharun->DB.Query_int(NULL, sql, player_l->Id));
	packet_l->write_8(time(NULL));

	player_l->Send(packet_l);
	return NULL;
}
