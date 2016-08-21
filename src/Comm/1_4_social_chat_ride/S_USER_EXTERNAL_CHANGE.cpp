#include "Sharun.hpp"

void* S_USER_EXTERNAL_CHANGE_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_USER_EXTERNAL_CHANGE, 120);

		packet_l->write_4(player_l->Id);// обджект ид объекта
		packet_l->write_4(player_l->SUBID);
		
		packet_l->write_4(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].Item->id : 0);// DB_getEquipment(rslt2, SLOT_WEAPON, player_l->Id)); // SLOT_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].Item->id : 0);// DB_getEquipment(rslt2, SLOT_ARMOR, player_l->Id)); // SLOT_ARMOR;
		packet_l->write_4(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].Item->id : 0);// DB_getEquipment(rslt2, SLOT_GLOVES, player_l->Id)); // SLOT_GLOVES;
		packet_l->write_4(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].Item->id : 0);// DB_getEquipment(rslt2, SLOT_BOOTS, player_l->Id)); // SLOT_BOOTS;
		packet_l->write_4(player_l->Items.slot[SLOT_SHIRT].Item ? player_l->Items.slot[SLOT_SHIRT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_SHIRT, player_l->Id)); // SLOT_SHIRT;
		packet_l->write_4(player_l->Items.slot[SLOT_HAT].Item ? player_l->Items.slot[SLOT_HAT].Item->id : 0);// DB_getEquipment(rslt2, SLOT_HAT, player_l->Id)); // SLOT_HAT;
		packet_l->write_4(player_l->Items.slot[SLOT_MASK].Item ? player_l->Items.slot[SLOT_MASK].Item->id : 0);// DB_getEquipment(rslt2, SLOT_MASK, player_l->Id)); // SLOT_MASK;

		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);
		packet_l->write_8(0);

		packet_l->write_1(player_l->Items.slot[SLOT_WEAPON].Item ? player_l->Items.slot[SLOT_WEAPON].enchant[0] : 0);// weapon.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_ARMOR].Item ? player_l->Items.slot[SLOT_ARMOR].enchant[0] : 0);// armor.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_GLOVES].Item ? player_l->Items.slot[SLOT_GLOVES].enchant[0] : 0);// glove.getEnchantLevel
		packet_l->write_1(player_l->Items.slot[SLOT_BOOTS].Item ? player_l->Items.slot[SLOT_BOOTS].enchant[0] : 0);// boot.getEnchantLevel

		packet_l->write_4(player_l->Items.slot[SLOT_APP_HAT].Item ? player_l->Items.slot[SLOT_APP_HAT].Item->id : 0);// new SLOT_APP_HAT
		packet_l->write_4(player_l->Items.slot[SLOT_APP_MASK].Item ? player_l->Items.slot[SLOT_APP_MASK].Item->id : 0);// new SLOT_APP_MASK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_BACK].Item ? player_l->Items.slot[SLOT_APP_BACK].Item->id : 0);// new SLOT_APP_BACK
		packet_l->write_4(player_l->Items.slot[SLOT_APP_WEAPON].Item ? player_l->Items.slot[SLOT_APP_WEAPON].Item->id : 0);// new SLOT_APP_WEAPON
		packet_l->write_4(player_l->Items.slot[SLOT_APP_ARMOR].Item ? player_l->Items.slot[SLOT_APP_ARMOR].Item->id : 0);// new SLOT_APP_ARMOR
		packet_l->write_4(0);

		packet_l->write_1(1);

	return packet_l;
}
