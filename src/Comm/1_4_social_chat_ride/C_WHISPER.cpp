#include "Sharun.hpp"

void* C_WHISPER_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL, NULL, NULL, NULL};

	ushort name_pos = packet_l->read_2();
	ushort text_pos = packet_l->read_2();


	const char16_t* name = (char16_t*) packet_l->read_D(name_pos);
	const char16_t* text = (char16_t*) packet_l->read_D(text_pos);


	if (!strcmp16(player_l->name_S, name)) {
		player_l->Chat(SYSTEM_CHAT, NULL, u"Your can't whisper to yourself !");
		return NULL;
	}

	for (int i=0; i<Sharun->Settings.Player_Max; i++) {
		if ( Sharun->Players.Lists[i]
		  && Sharun->Players.Lists[i]->loged
		  && !strcmp16(Sharun->Players.Lists[i]->name_S, name) ) {
			args[1] = Sharun->Players.Lists[i];
			args[4] = text;
			Sharun->OpCodes.Send[S_WHISPER](args);
			return NULL;
		}
	}

	char tmp[51+21] = {'"'};
	strcpy16_8(&tmp[1], name);
	sprintf(&tmp[strlen(tmp)], "\" was not online.");
	player_l->Chat(SYSTEM_CHAT, tmp, NULL);

	return NULL;
}
