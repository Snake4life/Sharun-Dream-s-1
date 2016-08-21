#include "Sharun.hpp"

void* S_GET_USER_LIST_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_GET_USER_LIST, -1);

	char **row;
	const char *sql = "SELECT * FROM `characters`, `character_appearances`, `character_detail_2` WHERE `character_appearances`.`object_id`=`characters`.`object_id` AND `character_detail_2`.`object_id`=`characters`.`object_id` AND `end_ban`<NOW()+0 AND `AccoundId`='%i' AND `Server_ID` IN (0, %i) ORDER BY `Order`";
	void *rslt = Sharun->DB.Query_Fast(1, sql, player_l->Account_Id, Sharun->Settings.Server_ID);

	const char *sql2 = "SELECT `owner_id`, `item_id`, `index`, `enchant_level`, `enchant_max` FROM `character_items`, `characters` WHERE `index` < '39' AND `owner_id` = `characters`.`object_id` AND `AccoundId`='%i' AND `Server_ID` IN (0, %i)  ORDER BY `owner_id`, `index`";
	void *rslt2 = Sharun->DB.Query_Fast(1, sql2, player_l->Account_Id, Sharun->Settings.Server_ID);

	ushort nextPos = 0;
	player_l->Characters_Count = Sharun->DB.Max_Row(rslt);
	packet_l->write_2(player_l->Characters_Count);

	// remeber where is next head in this  head
	nextPos = packet_l->write_NextPos();
	if(!player_l->Characters_Count) {
		packet_l->write_4(0);
	} else {
		packet_l->write_4(1);
	}

	if (player_l->Client_Version < 39)
		packet_l->write_4(0);

	packet_l->write_1(0);
	packet_l->write_4(player_l->Characters_Max);
	packet_l->write_4(1);
	packet_l->write_2(0);
	packet_l->write_4(40);
	packet_l->write_4(0);
	packet_l->write_4(24);

	for (int i=0; (row = Sharun->DB.Next_Row(rslt)); i++) {

		uint owner_id = atoi(row[DB_characters_object_id]);
		// Write Pos of this Head into previous Head
		packet_l->write_Pos(nextPos);

		// Write this Pos
		packet_l->write_Pos(0);

		// remeber where is next head in this  head
		// Write Next Head Pos 0 by def, updated by next next loop 
		nextPos = packet_l->write_NextPos();
		// ZERO (Character Data begin !
		packet_l->write_4(0);

		// remeber Name_Pos pos
		ushort Name_Pos = packet_l->write_NextPos();

		// remeber Detail1_Pos pos
		ushort Detail1_Pos = packet_l->write_NextPos();
		packet_l->write_2(32);	// Detail1 Len

		// remeber Detail2_Pos pos
		ushort Detail2_Pos = packet_l->write_NextPos();
		packet_l->write_2(64);	// Detail2 Len

		// remeber Unknow_Pos pos ... New!
		ushort Unknow_Pos = packet_l->write_NextPos();

		packet_l->write_4(owner_id); // object_id
		packet_l->write_4(atoi(row[DB_characters_sex])); // sex
		packet_l->write_4(atoi(row[DB_characters_race_id])); // race_id
		packet_l->write_4(atoi(row[DB_characters_class_id])); // class_id
		packet_l->write_4(atoi(row[DB_characters_level])); // level

		packet_l->write_4(100000); // AD040000
		packet_l->write_4(100000); // AD040000

		packet_l->write_4(atoi(row[DB_characters_country]));
		packet_l->write_4(atoi(row[DB_characters_lander]));
		packet_l->write_4(atoi(row[DB_characters_aera]));

		packet_l->write_8(atoi(row[DB_characters_last_online])); // Last Online Time
		packet_l->write_1(0); // 
		packet_l->write_8(0); // Deletion Time ?

		packet_l->write_4(0xA9C1BD41); // HEAD STUFF
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_WEAPON, owner_id)); // SLOT_WEAPON
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_EARRING_L, owner_id)); // SLOT_EAR;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_EARRING_R, owner_id)); // SLOT_EAR;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_ARMOR, owner_id)); // SLOT_ARMOR;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_GLOVES, owner_id)); // SLOT_GLOVES;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_BOOTS, owner_id)); // SLOT_BOOTS;
		packet_l->write_4(0);
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_RING_L, owner_id)); // SLOT_RING_L;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_RING_R, owner_id)); // SLOT_RING_R;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_SHIRT, owner_id)); // SLOT_SHIRT;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_HAT, owner_id)); // SLOT_HAT;
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_MASK, owner_id)); // SLOT_MASK;
//		packet_l->write_4(DB_getEquipment(rslt2, SLOT_NECKLACE, owner_id)); // SLOT_NECKLACE

		packet_l->write_1(101); // HEAD APPEARANCE
		for (int j = DB_character_appearances_face_color; j < DB_character_appearances_bone_structure_brow; j++)
			packet_l->write_1(atoi(row[DB_characters_MAXI + j]));
		packet_l->write_1(0); // temp[14]

		packet_l->write_8(0); //8
		packet_l->write_4(0); // 4
		packet_l->write_2(0); // 2

		packet_l->write_4(0xA9C06BC1); // BF1857B0
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);

		packet_l->write_4(DB_getEquipment(rslt2, SLOT_APP_HAT, owner_id)); // new SLOT_APP_HAT
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_APP_MASK, owner_id)); // new SLOT_APP_MASK
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_APP_BACK, owner_id)); // new SLOT_APP_BACK
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_APP_WEAPON, owner_id)); // new SLOT_APP_WEAPON
		packet_l->write_4(DB_getEquipment(rslt2, SLOT_APP_ARMOR, owner_id)); // new SLOT_APP_ARMOR
		packet_l->write_4(0); // new 

		packet_l->write_1(DB_getEquipment_Ench(rslt2, SLOT_WEAPON, owner_id)); // weapon.getEnchantLevel
		packet_l->write_1(DB_getEquipment_Ench(rslt2, SLOT_ARMOR, owner_id)); // armor.getEnchantLevel
		packet_l->write_1(DB_getEquipment_Ench(rslt2, SLOT_GLOVES, owner_id)); // glove.getEnchantLevel
		packet_l->write_1(DB_getEquipment_Ench(rslt2, SLOT_BOOTS, owner_id)); // boot.getEnchantLevel

		packet_l->write_4(416294); //218506); // Rested
		packet_l->write_4(2430063); //1815139); // Rest Max
		packet_l->write_1(1);

		if (atoi(row[DB_characters_level]) > 1 || atoi(row[DB_characters_online_time]) > 60)
			packet_l->write_1(0);
		else
			packet_l->write_1(1);

		packet_l->write_4(0);

		packet_l->write_1(1); // new

		packet_l->write_4(100);

		packet_l->write_4(820); // Achievements
		packet_l->write_4(0);
		packet_l->write_4(0); // new
		packet_l->write_4(0); // new

		packet_l->write_Pos(Name_Pos);
		packet_l->write_C(row[DB_characters_char_name]);

		packet_l->write_Pos(Detail1_Pos);
		for (int j = DB_character_appearances_bone_structure_brow; j<DB_character_appearances_MAXI; j++)
			packet_l->write_1(atoi(row[DB_characters_MAXI + j]));

		packet_l->write_Pos(Detail2_Pos);
		for (int j = DB_character_detail_2_temp1; j < DB_character_detail_2_MAXI; j++)
			packet_l->write_1(atoi(row[DB_characters_MAXI + DB_character_appearances_MAXI + j]));

		// Unknow... New!
		packet_l->write_Pos(Unknow_Pos);
		packet_l->write_2(0);
	}

	player_l->Send(packet_l);

	Sharun->DB.Result_Clear(rslt2);
	Sharun->DB.Result_Clear(rslt);

	return NULL;
}
