#include "Sharun.hpp"

void* S_INVEN_f(const void** argv)
{
	bool show = 0;
	player* player_l = (player*) argv[0];
	if (argv[1])
		show = 1;
	packet* packet_l = new_packet(S_INVEN, -1);
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
14 binder
*/
	int total = 0;
	ushort nextPos = 0, UnkPos, totalPos;

	// определяем кол-во всех ячеяк
	totalPos = packet_l->write_NextPos();
	nextPos = packet_l->write_NextPos();

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	packet_l->write_8(player_l->money);

	packet_l->write_1(show);// 01
	packet_l->write_2(1);
	packet_l->write_4(player_l->Items.slot_count*8);

	if (player_l->Client_Version < 39) {
		packet_l->write_4(1);
		packet_l->write_4(1);
	} else {
		packet_l->write_4(209);
		packet_l->write_4(209);
	}
	packet_l->write_4(0); // new
	packet_l->write_4(0); // new
	packet_l->write_4(0); // new

	if (player_l->Client_Version >= 39) {
		packet_l->write_4(0); // new
		packet_l->write_4(0); // new
	}

	for (short index=0; index<39+player_l->Items.slot_count*8; index++) {
		if (player_l->Items.slot[index].Item) {
			total++;

			packet_l->write_Pos(nextPos);

			packet_l->write_Pos(0);

			nextPos = packet_l->write_NextPos();

			packet_l->write_4(0);
			// Count ? Item Stat
			// Pos of Item Stat

			UnkPos = packet_l->write_NextPos();;

			packet_l->write_4(player_l->Items.slot[index].Item->id);
			packet_l->write_8(player_l->Items.slot[index].id);
			packet_l->write_4(player_l->Id);
			packet_l->write_4(player_l->SUBID);
			packet_l->write_4(index+1);//i + 1);
			packet_l->write_4(0);
			packet_l->write_8(player_l->Items.slot[index].count);
			packet_l->write_4(0);

			packet_l->write_1(player_l->Items.slot[index].Item->bind ? 1 : 0);

			// если кристалов нет
			for (int j=0; j<4; j++)
				packet_l->write_4(player_l->Items.slot[index].crystal[j]);

			packet_l->write_8(0);
			packet_l->write_8(0);
			packet_l->write_8(0);//-1);
			packet_l->write_8(0);//-1);
			packet_l->write_8(0);
			packet_l->write_1(0);
			packet_l->write_4(0); // need to have Combat item type added like 3 etc...(349, ...)
			packet_l->write_8(0);
			packet_l->write_8(0);
			packet_l->write_8(0);
			packet_l->write_4(player_l->Items.slot[index].binded); // ??? = atoi(row[1]) linked owner ?
			packet_l->write_4(0);
			packet_l->write_4(0);
			packet_l->write_1(0);
//			packet_l->write_4(0xFFFFFFFF); 0xFFFFFFFF // rollable bonus
			packet_l->write_1(-1);//36);
			packet_l->write_1(-1);//0);
			packet_l->write_1(-1);//0);
			packet_l->write_1(-1);//0);
			packet_l->write_4(0);

			packet_l->write_Pos(UnkPos);
			packet_l->write_2(0);

			/** // Special Stat?
			  * ushort This Pos
			  * ushort Next Stat Pos ; if = 0 : no next
			  * uint Stat Code	320200 ; 325300 ; 325200
			  **/
			packet_l->write_4(0);
		}
	}

	packet_l->swap(totalPos);
	packet_l->write_2(total);

	player_l->Send(packet_l);
	return NULL;
}
