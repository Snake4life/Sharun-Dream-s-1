#include "Sharun.hpp"

void* C_ADD_FRIEND_GROUP_f(player* player_l, packet* packet_l)
{
	packet_l->read_4();
	ushort	pos = packet_l->read_2();
	uint	id = packet_l->read_4();

	packet_l->swap(pos);
	char name[15];
	packet_l->read_C(name);
	SQL_Format_Char(name);

	const char *SQL = "INSERT INTO `Friends_Group` VALUES ('%ld', '%i', '%s');";
	Sharun->DB.Query_Fast(0, SQL, player_l->Players_ID, id, name);

	return NULL;
}
