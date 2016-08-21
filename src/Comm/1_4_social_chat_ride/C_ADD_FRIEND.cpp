#include "Sharun.hpp"

void* C_ADD_FRIEND_f(player* player_l, packet* packet_l)
{
	ushort	posN = packet_l->read_2();
	ushort	posC = packet_l->read_2();

	packet_l->swap(posN);
	char *nameS = (char*) packet_l->read_D(0);
	char name[45];
	packet_l->read_C(name);
	SQL_Format_Char(name);

	packet_l->swap(posC);
	char desc[105];
	packet_l->read_C(desc);
	SQL_Format_Char(desc);

	if (strcmp(player_l->name, name)) {
		const char *SQL;
		SQL = "SELECT `object_id` FROM `characters` WHERE `char_name` = '%s' AND `Server_ID` IN (0, %i);";
		uint id = Sharun->DB.Query_int(NULL, SQL, name, Sharun->Settings.Server_ID);
		if (id) {
			SQL = "INSERT INTO `Friends_Request` VALUES ( '%ld' , '%ld' , '%s' );";
			Sharun->DB.Query_Fast(0, SQL, player_l->Id, id, desc);

			const void* args[] = {player_l, NULL, NULL};

/*			char16_t Mess[16+40] = u"@3442UserName";
			strcpy8_16(Mess + strlen16(Mess), name);
			Sharun->OpCodes.Send[S_SYSTEM_MESSAGE](args);*/

			char16_t Mess[14+40] = u"@433UserName";
			args[1] = Mess;
			args[2] = nameS;
			Sharun->OpCodes.Send[S_SYSTEM_MESSAGE](args);
			args[1] = args[2] = NULL;
			
			Sharun->OpCodes.Send[S_FRIEND_LIST](args);
			Sharun->OpCodes.Send[S_UPDATE_FRIEND_INFO](args);
		}
	}

	return NULL;
}
