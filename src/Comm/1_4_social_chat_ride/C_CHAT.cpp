#include "Sharun.hpp"

void* C_CHAT_f(player* player_l, packet* packet_l)
{
	ushort text_pos = packet_l->read_2(); // Text Pos

	CHAT_TYPE type = (CHAT_TYPE) packet_l->read_2();

	const char16_t* text = (char16_t*) packet_l->read_D(text_pos);

	World_Chat(player_l, type, NULL, NULL, text);

	return NULL;
}
