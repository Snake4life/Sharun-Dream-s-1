#include "Sharun.hpp"

void* C_STR_EVALUATE_LIST_f(player* player_l, packet* packet_l)
{
	packet_l->read_4();
	packet_l->read_4();
	packet_l->read_4();
	packet_l->read_2();

	uint type  = packet_l->read_4();
	const char16_t *name = packet_l->read_S(NULL);

	const void *args[] = {player_l, &type, name, NULL};

	Sharun->OpCodes.Send[S_STR_EVALUATE_LIST](args);

	delete name;
	return NULL;
}
