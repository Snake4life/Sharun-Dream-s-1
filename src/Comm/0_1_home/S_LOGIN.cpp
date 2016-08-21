#include "Sharun.hpp"

void* S_LOGIN_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_LOGIN, -1);

		// remeber Name_Pos pos
		ushort Name_Pos = packet_l->write_NextPos();	// Write Later

		// remeber Detail1_Pos pos
		ushort Detail1_Pos = packet_l->write_NextPos();	// Write Later
		packet_l->write_2(32);	// Detail1 Len

		// remeber Detail2_Pos pos
		ushort Detail2_Pos = packet_l->write_NextPos();	// Write Later
		packet_l->write_2(64);	// Detail2 Len

		ushort Class_Race = 10000;
		Class_Race += (player_l->Race_Id * 2 + 1 + player_l->Sex) * 100;
		Class_Race += player_l->Class_Id + 1;
		packet_l->write_4(Class_Race); // Sex + Race + Class

		packet_l->write_4(player_l->Account_Id);//player_l->Id); // Account_id
		packet_l->write_4(player_l->SUBID); // sub_object_id

		packet_l->write_4(20 + Sharun->Settings.Server_ID); // SERVER ID
		packet_l->write_4(player_l->Id); // Character ID


		packet_l->write_4(0);
		packet_l->write_1(player_l->Stats.HP ? 1 : 0);// player.isDead
		packet_l->write_4(0);
		packet_l->write_4(50);
		packet_l->write_4(110);

		packet_l->write_1(101); // HEAD APPEARANCE
		for (int j = 0; j < 6; j++)
			packet_l->write_1(player_l->appearance[j]);
		packet_l->write_1(0); // temp[14]

		packet_l->write_2(1);
		packet_l->write_2(player_l->Level);// уровень игрока

		packet_l->write_2(player_l->collect[0]);// Collect Mining
		packet_l->write_2(0);// Collect 0
		packet_l->write_2(player_l->collect[1]);// Collect Plant
		packet_l->write_2(player_l->collect[2]);// Collect Energy

		packet_l->write_4(1);
		packet_l->write_2(0);

		packet_l->write_4(0);

		packet_l->write_8(player_l->exp); // not really exp !
		packet_l->write_8(player_l->exp);
		packet_l->write_8(get_Experience_LEVEL(player_l->Level));

		packet_l->write_4(0);// ?
		packet_l->write_4(0);// ?
		if (player_l->Client_Version < 39)
			packet_l->write_4(419);// ?
		packet_l->write_8(0);// ?

		if (player_l->Client_Version >= 39) {
			packet_l->write_4(0x04BD0768);// ?
			packet_l->write_4(0x04BD0768);// ?
			packet_l->write_F(1);
			packet_l->write_4(0);
		}

		packet_l->write_4(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].Item->id : 0);// DB_getEquipment(rslt2, SLOT_WEAPON, player_l->Id)); // SLOT_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].Item->id : 0);// DB_getEquipment(rslt2, SLOT_ARMOR, player_l->Id)); // SLOT_ARMOR;
		packet_l->write_4(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].Item->id : 0);// DB_getEquipment(rslt2, SLOT_GLOVES, player_l->Id)); // SLOT_GLOVES;
		packet_l->write_4(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].Item->id : 0);// DB_getEquipment(rslt2, SLOT_BOOTS, player_l->Id)); // SLOT_BOOTS;
		packet_l->write_4(player_l->Items.slot[SLOT_SHIRT].Item ? player_l->Items.slot[SLOT_SHIRT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_SHIRT, player_l->Id)); // SLOT_SHIRT;
		packet_l->write_4(player_l->Items.slot[SLOT_HAT].Item ? player_l->Items.slot[SLOT_HAT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_HAT, player_l->Id)); // SLOT_HAT;
		packet_l->write_4(player_l->Items.slot[SLOT_MASK].Item ? player_l->Items.slot[SLOT_MASK].Item->id : 0);// DB_getEquipment(rslt2, SLOT_MASK, player_l->Id)); // SLOT_MASK;

		if (player_l->Client_Version < 39)
			packet_l->write_4(0x1291E64A); // new
		else
			packet_l->write_4(0x0B59F357); // new
		packet_l->write_4(0);// new
			
		packet_l->write_8(1);
		packet_l->write_1(0);
		packet_l->write_4(0);// 03 00 00 00 если 3, то надпись "Ангел смерти"
		packet_l->write_4(0);// 00 00 00 00

		packet_l->write_4(0);// 00 00 00 00 // new
		packet_l->write_4(0);// 00 00 00 00 // new
		packet_l->write_4(0);// 00 00 00 00 // new
		packet_l->write_4(0);// 00 00 00 00 // new

		packet_l->write_4(0);// 00 00 00 00
		packet_l->write_4(0);// 00 00 00 00
		packet_l->write_4(0);// 00 00 00 00
		packet_l->write_4(0);// 00 00 00 00

		packet_l->write_4(0);// 00 00 00 00
		packet_l->write_4(0);// 00 00 00 00
/*48*/		packet_l->write_4(0);// 00 00 00 00

		packet_l->write_1(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].enchant[0] : 0);// weapon.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].enchant[0] : 0);// armor.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].enchant[0] : 0);// glove.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].enchant[0] : 0);// boot.getEnchantLevel

		packet_l->write_1(0);// 00

		packet_l->write_4(0);// 78 00 00 00 .//карма player.getKarma()
		packet_l->write_1(1);// 01 00 00 00

		packet_l->write_4(player_l->Items.slot[SLOT_APP_HAT].Item ? player_l->Items.slot[SLOT_APP_HAT].Item->id : 0);// new SLOT_APP_HAT
		packet_l->write_4(player_l->Items.slot[SLOT_APP_MASK].Item ? player_l->Items.slot[SLOT_APP_MASK].Item->id : 0);// new SLOT_APP_MASK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_BACK].Item ? player_l->Items.slot[SLOT_APP_BACK].Item->id : 0);// new SLOT_APP_BACK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_WEAPON].Item ? player_l->Items.slot[SLOT_APP_WEAPON].Item->id : 0);// new SLOT_APP_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_APP_ARMOR].Item ? player_l->Items.slot[SLOT_APP_ARMOR].Item->id : 0);// new SLOT_APP_ARMOR
		packet_l->write_4(0); // new

		packet_l->write_4(0);// 00 00 00 00 // new 02 00 00 00
		packet_l->write_4(0);// 00 00 00 00 // new 64 00 00 00
		packet_l->write_4(0);// 00 00 00 00 // new

		packet_l->write_4(1);// 01 00 00 00
		packet_l->write_4(0);// 00 00 00 00
		packet_l->write_1(0);// 00
		packet_l->write_4(100);// 64 00 00 00
		packet_l->write_F(1);

		if (player_l->Client_Version < 39) {
			packet_l->write_1(1);
			packet_l->write_4(1);
		} else {
			packet_l->write_1(0);
			packet_l->write_4(0);
		}
		packet_l->write_4(0);

		packet_l->write_Pos(Name_Pos);
		packet_l->write_S(player_l->name_S);

		packet_l->write_Pos(Detail1_Pos);
		for (int j = 0; j<32; j++)
			packet_l->write_1(player_l->appearance[6+j]);

		packet_l->write_Pos(Detail2_Pos);
		for (int j = 0; j < 64; j++)
			packet_l->write_1(player_l->appearance[6+32+j]);

	player_l->Send(packet_l);
	return NULL;
}
