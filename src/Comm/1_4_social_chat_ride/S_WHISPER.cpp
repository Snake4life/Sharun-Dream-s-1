#include "Sharun.hpp"

void* S_WHISPER_f(const void** argv)
{
	const char16_t * txt1 = u"[system] Now, you can whispe with this player.";
	
	player* player_l = (player*) argv[0];
	player* TOplayer_l = (player*) argv[1];
	char*	name = (char*) argv[2];
	char*	text1 = (char*) argv[3];
	char16_t*	text2 = (char16_t*) argv[4];

	ushort Pck_size = 2*3 + 1 + (str8_strlen16(player_l->name) + 1) * 2 + ((name ? strlen(name) : str8_strlen16(TOplayer_l->name)) + 1) * 2 + ((text2 ? strlen16(text2) : (text1 ? strlen(text1) : strlen16(txt1)) + 1)) * 2;
	packet* packet_l = new_packet(S_WHISPER, Pck_size);

	ushort Name_Pos = packet_l->write_NextPos();
	ushort Name_Pos2 = packet_l->write_NextPos();
	ushort Text_Pos = packet_l->write_NextPos();

	if (player_l->Right > 4)
		packet_l->write_1(1);

	packet_l->write_Pos(Name_Pos);
	packet_l->write_S(player_l->name_S);//имя

	packet_l->write_Pos(Name_Pos2);
	if (!name)
		packet_l->write_S(TOplayer_l->name_S);//имя
	else
		packet_l->write_C(name);//имя

	packet_l->write_Pos(Text_Pos);
	if (text2)
		packet_l->write_S(text2);
	else {
		if (text1)
			packet_l->write_C(text1);
		else
			packet_l->write_S(txt1);
	}

	TOplayer_l->Send(packet_l);

	if (text1 || text2) {
		packet_l = new_packet(S_WHISPER, Pck_size);

//		ushort Name_Pos = packet_l->pos;
		packet_l->write_NextPos();
//		ushort Name_Pos2 = packet_l->pos;
		packet_l->write_NextPos();
//		ushort Text_Pos = packet_l->pos;
		packet_l->write_NextPos();

		if (TOplayer_l->Right > 4)
			packet_l->write_1(1);

		packet_l->write_Pos(Name_Pos);
		packet_l->write_S(player_l->name_S);//имя

		packet_l->write_Pos(Name_Pos2);
	if (!name)
		packet_l->write_S(TOplayer_l->name_S);//имя
	else
		packet_l->write_C(name);//имя

		packet_l->write_Pos(Text_Pos);
		if (text2)
			packet_l->write_S(text2);
		else {
			if (text1)
				packet_l->write_C(text1);
		}

		player_l->Send(packet_l);
	}
	return NULL;
}
