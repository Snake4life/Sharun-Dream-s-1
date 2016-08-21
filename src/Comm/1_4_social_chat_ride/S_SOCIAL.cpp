#include "Sharun.hpp"

void* S_SOCIAL_f(const void** argv)
{
	uint*	Cha_ID = (uint*)argv[0];
	uint*	Sub_ID = (uint*)argv[1];
	int*	id = (int*)argv[2];

	if (!id && (*id) < 0)
		return NULL;

	packet* packet_l = new_packet(S_SOCIAL, 17);

	packet_l->write_4(*Cha_ID);
	packet_l->write_4(*Sub_ID);
	packet_l->write_4(*id);
	packet_l->write_4(0);
	packet_l->write_1(0);

	return packet_l;
}
