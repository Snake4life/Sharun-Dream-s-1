#include "Sharun.hpp"

void* C_CREATE_USER_f(player* player_l, packet* packet_l)
{
	uchar result = 0;
	const void *args[] = {player_l, &result, NULL};

	const char *SQL[] = {
		"INSERT INTO `characters` (`create_time`, `AccoundId`, `sex`, `race_id`, `class_id`, `char_name`, `Order`, `Server_ID`) VALUE (UNIX_TIMESTAMP(), '%i', '%i', '%i', '%i', '%s', '%i', '%i');",
		"SELECT `object_id` FROM `characters` WHERE `AccoundId`='%i' AND `char_name`='%s' AND `Server_ID` IN (0, %i);",
		"INSERT INTO `character_appearances` VALUE ('%ld', '%i', '%i', '%i', '%i', '%i', '%i'",
		"INSERT INTO `character_detail_2` VALUE ('%ld'",
		"INSERT INTO `character_items` (`owner_id`, `item_id`, `item_count`, `autor`, `location`, `index`) SELECT %ld, `Item_ID`, `Count`, 'CreatePlayer', `location`, `index` FROM `Noobs` WHERE `location`=0 OR (`Class_ID`=%i AND `Material_ID`=-1) OR (`Class_ID`=-1 AND `Material_ID`=%i)",
		"UPDATE `characters` SET `x`='-48077', `y`='-52002', `z`='642', `heading`='45330', `zone_id`='7087', `level`='50' WHERE `object_id`='%i';"
	};

	ushort Name_Pos = packet_l->read_2();
	ushort Detail1_Pos = packet_l->read_2();
	/*ushort Detail1_Len = */packet_l->read_2();
	ushort Detail2_Pos = packet_l->read_2();
	/*ushort Detail2_Len = */packet_l->read_2();

	uint sex = packet_l->read_4();
	uint race = packet_l->read_4();
	uint class_l = packet_l->read_4();

	packet_l->read_1();

	ushort FaceColor = packet_l->read_1();
	ushort FaceSkin = packet_l->read_1();
	ushort AdormentsSkin = packet_l->read_1();
	ushort FeaturesSkin = packet_l->read_1();
	ushort FeaturesColor = packet_l->read_1();
	ushort Voice = packet_l->read_1();

	/*packet_l->read_1();

	packet_l->read_2();
	packet_l->read_2();
	packet_l->read_2();*/

	char Name[100];
	packet_l->swap(Name_Pos);
	packet_l->read_C(Name);

	if ( !strchr(Name, ' ') &&
	     !strchr(Name, '[') && !strchr(Name, ']') &&
	     !strchr(Name, '(') && !strchr(Name, ')') ) {
		char Query[2000];
		SQL_Format_Char(Name);

		Sharun->DB.Query_Fast(0, SQL[0], player_l->Account_Id, sex, race, class_l, Name, player_l->Characters_Count, Sharun->Settings.Server_ID);

		uint object_id = Sharun->DB.Query_int(NULL, SQL[1], player_l->Account_Id, Name, Sharun->Settings.Server_ID);

		packet_l->swap(Detail1_Pos);
		sprintf(Query, SQL[2], object_id, FaceColor, FaceSkin, AdormentsSkin, FeaturesSkin, FeaturesColor, Voice);
		for (int i=0; i<32; i++)
			sprintf(&Query[strlen(Query)], ", '%i'", (ushort)packet_l->read_1());
		sprintf(&Query[strlen(Query)], ");");
		Sharun->DB.Query_Fast(0, Query);

		packet_l->swap(Detail2_Pos);
		sprintf(Query, SQL[3], object_id);
		for (int i=0; i<64; i++)
			sprintf(&Query[strlen(Query)], ", '%i'", (ushort)packet_l->read_1());
		sprintf(&Query[strlen(Query)], ");");
		Sharun->DB.Query_Fast(0, Query);

		// Add item to character
		sprintf(Query, SQL[4], object_id, class_l, class_l == REAPER ? -1 : Sharun->Settings.class_mat[class_l]);
		Sharun->DB.Query_Fast(0, Query);

		if (class_l == REAPER) {
			sprintf(Query, SQL[5], object_id);
			Sharun->DB.Query_Fast(0, Query);
		}
		result = 1;
	}
	Sharun->OpCodes.Send[S_CREATE_USER](args);
	return NULL;
}
