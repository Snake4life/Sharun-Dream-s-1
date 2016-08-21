#include "Sharun.hpp"

void* S_SPAWN_USER_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SPAWN_USER, -1);

		packet_l->write_8(0);

		ushort Name_Pos = packet_l->write_NextPos();	// Write Later
		ushort GName_Pos = packet_l->write_NextPos();	// Write Later
		ushort Title_Pos = packet_l->write_NextPos();	// Write Later

		// remeber Detail1_Pos pos
		ushort Detail1_Pos = packet_l->write_NextPos();	// Write Later
		packet_l->write_2(32);// кол-во байт описания внешности

		ushort GTitle_Pos = packet_l->write_NextPos();	// Write Later
		ushort GIcon_Pos = packet_l->write_NextPos();	// Write Later

		// remeber Detail2_Pos pos
		ushort Detail2_Pos = packet_l->write_NextPos();	// Write Later
		packet_l->write_2(64);	// Detail2 Len

		ushort Class_Race = 10000;
		Class_Race += (player_l->Race_Id * 2 + 1 + player_l->Sex) * 100;
		Class_Race += player_l->Class_Id + 1;

		packet_l->write_4(0);// айди сервера
		packet_l->write_4(player_l->Account_Id);
		packet_l->write_4(player_l->Id);// обджект ид объекта
		packet_l->write_4(player_l->SUBID);
		for (int i=0; i<3; i++)
			packet_l->write_F(player_l->DjW->XYZ[i]);
		packet_l->write_2(player_l->DjW->heading);

		packet_l->write_4(0);//player.getColor(newPlayer)); // цвет ника
		packet_l->write_4(Class_Race);// индетификатор класса и расы объекта
		packet_l->write_2(0);
		packet_l->write_2(70);	// > 39 = 50
		packet_l->write_2(170);	// > 39 = 233
		packet_l->write_2(0); // поза перса
		packet_l->write_2(0);
		packet_l->write_1(1);
		packet_l->write_1(player_l->Stats.HP ? 1 : 0); // смерть

		// внешность
		packet_l->write_1(101); // temp[9]
		for (int j = 0; j < 6; j++)
			packet_l->write_1(player_l->appearance[j]);
		packet_l->write_1(0); // temp[14]

		packet_l->write_4(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].Item->id : 0);// DB_getEquipment(rslt2, SLOT_WEAPON, player_l->Id)); // SLOT_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].Item->id : 0);// DB_getEquipment(rslt2, SLOT_ARMOR, player_l->Id)); // SLOT_ARMOR;
		packet_l->write_4(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].Item->id : 0);// DB_getEquipment(rslt2, SLOT_GLOVES, player_l->Id)); // SLOT_GLOVES;
		packet_l->write_4(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].Item->id : 0);// DB_getEquipment(rslt2, SLOT_BOOTS, player_l->Id)); // SLOT_BOOTS;
		packet_l->write_4(player_l->Items.slot[SLOT_SHIRT].Item ? player_l->Items.slot[SLOT_SHIRT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_SHIRT, player_l->Id)); // SLOT_SHIRT;
		packet_l->write_4(player_l->Items.slot[SLOT_HAT].Item ? player_l->Items.slot[SLOT_HAT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_HAT, player_l->Id)); // SLOT_HAT;
		packet_l->write_4(player_l->Items.slot[SLOT_MASK].Item ? player_l->Items.slot[SLOT_MASK].Item->id : 0);// DB_getEquipment(rslt2, SLOT_MASK, player_l->Id)); // SLOT_MASK;

		packet_l->write_4(player_l->Spawn->is ? 1 : 0); // вспышка
		packet_l->write_4(player_l->Mount ? player_l->Mount->Mount_Id : 0);//newPlayer.getMountId()); // животное

		packet_l->write_4(7); // 7 ???
		packet_l->write_4(0); // 326 ??? // Title_id

		packet_l->write_8(0);
		packet_l->write_8(0);

		packet_l->write_8(0);
		packet_l->write_8(0);

		packet_l->write_8(0);
		packet_l->write_8(0);

		packet_l->write_8(0);

		packet_l->write_4(0);
		packet_l->write_2(0);
		packet_l->write_1(0);

		packet_l->write_1(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].enchant[0] : 0);// weapon.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].enchant[0] : 0);// armor.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].enchant[0] : 0);// glove.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].enchant[0] : 0);// boot.getEnchantLevel

		packet_l->write_1(0);
		packet_l->write_1(0);//newPlayer.isPvPMode() ? 1 : 0); // включен ли пвп режим

		packet_l->write_2(player_l->Level);
		packet_l->write_2(0);
		packet_l->write_4(0);

		packet_l->write_4(0);// что-то тоже нательное

		packet_l->write_1(1);

		packet_l->write_4(player_l->Items.slot[SLOT_APP_HAT].Item ? player_l->Items.slot[SLOT_APP_HAT].Item->id : 0);// new SLOT_APP_HAT
		packet_l->write_4(player_l->Items.slot[SLOT_APP_MASK].Item ? player_l->Items.slot[SLOT_APP_MASK].Item->id : 0);// new SLOT_APP_MASK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_BACK].Item ? player_l->Items.slot[SLOT_APP_BACK].Item->id : 0);// new SLOT_APP_BACK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_WEAPON].Item ? player_l->Items.slot[SLOT_APP_WEAPON].Item->id : 0);// new SLOT_APP_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_APP_ARMOR].Item ? player_l->Items.slot[SLOT_APP_ARMOR].Item->id : 0);// new SLOT_APP_ARMOR
		packet_l->write_4(0);

		packet_l->write_4(0);
		packet_l->write_4(0);
		packet_l->write_1(0);

		packet_l->write_4(0);// Allience
		// 1 = Velika ; 2 = Allemantheia ; 3 = Kaiator
		packet_l->write_4(100);// 64 00 00 00 = 100 // > 39 = 0
		packet_l->write_4(0);// 0
		packet_l->write_4(256001);// 01 E8 03 00 = 256001 // > 39 = 1
		packet_l->write_4(0);// 0
		packet_l->write_1(0);// 0
		packet_l->write_4(100);// 64 00 00 00 = 100
		packet_l->write_F(1);// 80 3F = 16256

		packet_l->write_Pos(Name_Pos);
		packet_l->write_S(player_l->name_S); //name);// имя

		packet_l->write_Pos(GName_Pos);
		packet_l->write_S(u"");//player_l->Guild->name);// название клана

		packet_l->write_Pos(Title_Pos);
		packet_l->write_S(player_l->title_S);// title); // титул

		packet_l->write_Pos(Detail1_Pos);
		for (int j = 0; j<32; j++)
			packet_l->write_1(player_l->appearance[6+j]);

		packet_l->write_Pos(GTitle_Pos);
		packet_l->write_S(u"");//player_l->Guild->title);

		packet_l->write_Pos(GIcon_Pos);
		packet_l->write_S(u"");//player_l->Guild->icon);

		packet_l->write_Pos(Detail2_Pos);
		for (int j = 0; j < 64; j++)
			packet_l->write_1(player_l->appearance[6+32+j]);

	return packet_l;
}
