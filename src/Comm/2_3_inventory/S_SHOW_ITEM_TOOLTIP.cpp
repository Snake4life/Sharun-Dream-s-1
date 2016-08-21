#include "Sharun.hpp"

void* S_SHOW_ITEM_TOOLTIP_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	const char16_t*	name = (const char16_t*) argv[1];
	ulong*	itemID = (ulong*) argv[2];
	packet* packet_l = new_packet(S_SHOW_ITEM_TOOLTIP, -1);

	uint i=0;
	while ( name && name[0] && i<Sharun->Settings.Player_Max
	  && ( !Sharun->Players.Lists[i]
	    || ( Sharun->Players.Lists[i]
	      && strcmp16(name, Sharun->Players.Lists[i]->name_S ) ) ) ) i++;
	if (i>=Sharun->Settings.Player_Max) return NULL;
	if (name && !name[0])
		i = player_l->Players_ID;

	int index=0;
	while ( index < 39 + Sharun->Players.Lists[i]->Items.slot_count * 8
	  && ( !Sharun->Players.Lists[i]->Items.slot[index].Item
	    || (Sharun->Players.Lists[i]->Items.slot[index].Item
	    && Sharun->Players.Lists[i]->Items.slot[index].id != *itemID) ) ) index++;
	if (index>=39+player_l->Items.slot_count*8) return NULL;

/*
00 object_id
01 owner_id
02 item_id
03 item_count
04 enchant_level
05 enchant_max
06 autor
07 location
08 index
09 crystal1
10 crystal2
11 crystal3
12 crystal4
13 binded
14 binder name
*/
	ushort cristal_Pos = packet_l->pos;
	packet_l->write_4(0); //Cristal Count + Pos

	ushort UNK_Pos = packet_l->pos;
	packet_l->write_4(0); //UNK Count (15) + Pos

	ushort binded_Pos = packet_l->pos;
	packet_l->write_4(0); //Binded Pos + Binder Name Pos

	packet_l->write_4(20); // 14 00 00 00
	packet_l->write_8(Sharun->Players.Lists[i]->Items.slot[index].id); // BE B4 4F 01
	packet_l->write_4(Sharun->Players.Lists[i]->Items.slot[index].Item->id); // D8 33 00 00
	packet_l->write_8(Sharun->Players.Lists[i]->Items.slot[index].id); // BE B4 4F 01
	packet_l->write_4(player_l->Id); // 48 38 00 00
	packet_l->write_4(0); // 00 00 00 00	SUB ID ?
	packet_l->write_4(index); // 44 00 00 00
	packet_l->write_4(0); // 00 00 00 00
	packet_l->write_4(1); // 01 00 00 00
	packet_l->write_4(1); // 01 00 00 00
	packet_l->write_4(Sharun->Players.Lists[i]->Items.slot[index].enchant[0]); // 00 00 00 00 заточка

	packet_l->write_4(0);//1);

	packet_l->write_4(Sharun->Players.Lists[i]->Items.slot[index].Item->bind ? 1 : 0); // 00 00 00 00 00 00 00 00
	/* бонусы от заточки включаеться если заточить на +1 а так нули */
	packet_l->write_4(0); // 00 00 00 00 флота атаки бонус от заточки
	packet_l->write_4(0); // 00 00 00 00 флот овертёрна бонус от заточки
	packet_l->write_4(0); // 00 00 00 00 флот защиты бонус от заточки
	packet_l->write_4(0); // 00 00 00 00 флот защиты от овертёрна бонус от заточки

	/*
	  * writeIntS(0xACBD0400); //00 00 00 00 writeIntS(0x3CBF0400); //00 00 00 00 writeIntS(0x80BC0400); //00 00 00 00 writeIntS(0x30C10400); //00 00 00 00
	  */

	packet_l->write_1(0); // 00

	/* бонусы */
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	// нужно распиливать на флоты на каждый параметр бонус отдельно

	packet_l->write_8(0);// бонус к следующим заточкам
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);// бонус к следующим заточкам

	packet_l->write_8(0xFEFEFEFEFEFEFEFE);// видимо какието бафы
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);// какойто байтовый беспредел
	packet_l->write_8(0xFEFEFEFEFEFEFEFE);// ?? иногда 3

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
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_2(0);

	packet_l->write_8(0);//item.getItemLevel());// Итем лвл
	packet_l->write_8(0);

	packet_l->write_8(0xFFFFFFFFFFFFFFFF);// не понятно иногда биндиться суда
	packet_l->write_8(0xFFFFFFFFFFFFFFFE);
	packet_l->write_8(0xFFFFFFFFFFFFFFFF);

	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_4(0);

	packet_l->write_1(3);
	packet_l->write_1(0);
	packet_l->write_1(0);
	packet_l->write_1(0);
	packet_l->write_1(172);
	packet_l->write_8(0);
	packet_l->write_8(0);

	if(Sharun->Players.Lists[i]->Items.slot[index].Item->bind && Sharun->Players.Lists[i]->Items.slot[index].binded)
	{
		packet_l->write_Pos(binded_Pos);
		packet_l->write_2(0);
		packet_l->write_Pos(binded_Pos+2);
		packet_l->write_C(Sharun->Players.Lists[i]->Items.slot[index].binder);
	}

	// если в итем вставлены кристаллы
	short cristal_count = 0;
	ushort Cristal_Next = 0;
	for (int j=0; j<4; j++) {
		if (Sharun->Players.Lists[i]->Items.slot[index].crystal[j]) {
			if (!cristal_count)
				packet_l->write_Pos(cristal_Pos+2);
			if (Cristal_Next)
				packet_l->write_Pos(Cristal_Next);
			packet_l->write_2(packet_l->pos);
			Cristal_Next = packet_l->pos;
			packet_l->write_2(0);
			packet_l->write_4(Sharun->Players.Lists[i]->Items.slot[index].crystal[j]);
			cristal_count++;
		}
	}
	if (cristal_count) {
		packet_l->swap(cristal_Pos);
		packet_l->write_2(cristal_count);
		packet_l->swap();
	}

	/**
	 * UNKNOW
	 **/
	cristal_count = 0;
	for (int j=0; j<15; j++) {
		cristal_count++;
		if (!cristal_count)
			packet_l->write_Pos(UNK_Pos+2);
		if (j)
			packet_l->write_Pos(Cristal_Next);
		packet_l->write_2(packet_l->pos);
		Cristal_Next = packet_l->pos;
		packet_l->write_2(0);
		packet_l->write_4(0);
	}
	if (cristal_count) {
		packet_l->swap(UNK_Pos);
		packet_l->write_2(cristal_count);
	}

	player_l->Send(packet_l);
	return NULL;
}
