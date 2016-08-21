#include "Sharun.hpp"

void* C_DELETE_USER_f(player* player_l, packet* packet_l)
{
	uint object_id = packet_l->read_4();
	uchar result = 0;
	const void *args[] = {player_l, &result, NULL};

	short DB_Res = Sharun->DB.Query_int(NULL, "SELECT COUNT(`object_id`) FROM `characters` WHERE `object_id`='%i' AND `end_ban`<UNIX_TIMESTAMP();", object_id);

	const char *SQL[] = {
		"UPDATE `characters` AS C1, `characters` AS C2 SET `C1`.`Order`=`C1`.`Order`-1 WHERE `C2`.`object_id`='%i' AND `C1`.`Order` > `C2`.`Order`;",
		"DELETE FROM `characters` WHERE `object_id`='%i';",
		"DELETE FROM `character_appearances` WHERE `object_id`='%i';",
		"DELETE FROM `character_detail_2` WHERE `object_id`='%i';",
		"DELETE FROM `character_items` WHERE `owner_id`='%i';",
		NULL
	};

	if (DB_Res) {
		for (int i=0; SQL[i]; i++) {
			if (i>1)
				Sharun->DB.Query_Slow(SQL[i], object_id);
			else
				Sharun->DB.Query_Fast(0, SQL[i], object_id);
		}

		if (!Sharun->DB.Query_int(NULL, "SELECT COUNT(`object_id`) FROM `characters` WHERE `object_id`='%i';", object_id));
			result = 1;
	}
	Sharun->OpCodes.Send[S_DELETE_USER](args);

	return NULL;
}
