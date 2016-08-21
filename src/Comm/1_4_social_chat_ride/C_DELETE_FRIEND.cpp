#include "Sharun.hpp"

void* C_DELETE_FRIEND_f(player* player_l, packet* packet_l)
{
	ushort	posN = packet_l->read_2();

	packet_l->swap(posN);
	char name[45];
	packet_l->read_C(name);
	SQL_Format_Char(name);

	if (strcmp(player_l->name, name)) {
		const char *SQL;
		SQL = "SELECT `object_id` FROM `characters` WHERE `char_name` = '%s' AND `Server_ID` IN (0, %i);";
		uint id = Sharun->DB.Query_int(NULL, SQL, name, Sharun->Settings.Server_ID);
		if (id) {
			SQL = "DELETE FROM `Friends_Request` WHERE `Player_ID` = '%ld' AND `Player_RQ` = '%s';";
			Sharun->DB.Query_Fast(0, SQL, id, player_l->name);
			Sharun->DB.Query_Fast(0, SQL, player_l->Id, name);

			SQL = "DELETE FROM `Friends_List` WHERE `Player_1` = '%ld' AND `Player_2` = '%ld';";
			Sharun->DB.Query_Fast(0, SQL, id, player_l->Id);
			Sharun->DB.Query_Fast(0, SQL, player_l->Id, id);

			const void* args[] = {player_l, NULL};

			Sharun->OpCodes.Send[S_FRIEND_LIST](args);
			Sharun->OpCodes.Send[S_UPDATE_FRIEND_INFO](args);

	/*		char16_t Mess[16+40] = u"@3442UserName";
			strcpy8_16(Mess + strlen16(Mess), name);
			Sharun->OpCodes.Send[S_SYSTEM_MESSAGE](args);*/
		}
	}

	return NULL;
}
