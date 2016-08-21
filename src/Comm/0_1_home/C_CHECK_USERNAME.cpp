#include "Sharun.hpp"

void* C_CHECK_USERNAME_f(player* player_l, packet* packet_l)
{
	packet_l->read_2();
	char Name[100];
	packet_l->read_C(Name);
	uchar result = 0;

	const void *args[] = {player_l, &result, NULL};
	if ( !strchr(Name, ' ') &&
	     !strchr(Name, '[') && !strchr(Name, ']') &&
	     !strchr(Name, '(') && !strchr(Name, ')') ) {
		SQL_Format_Char(Name);

		const char *SQL = "SELECT COUNT(`object_id`) FROM `characters` WHERE `char_name` = '%s'";
		if(!Sharun->DB.Query_int(NULL, SQL, Name))
			result = 1;
	}

	Sharun->OpCodes.Send[S_CHECK_USERNAME](args);
	return NULL;
}
