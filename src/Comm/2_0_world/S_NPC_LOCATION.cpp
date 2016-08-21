#include "Sharun.hpp"

void *S_NPC_LOCATION_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
	npc*	npc_l = (npc*)argv[1];
	ushort*	type = (ushort*)argv[2];
	packet* packet_l = new_packet(S_NPC_LOCATION, 40);

	if (npc_l) {
		packet_l->write_4(npc_l->Id);
		packet_l->write_4(npc_l->SUBID);
	} else {
		packet_l->write_4(player_l->Id);
		packet_l->write_4(player_l->SUBID);
	}

	//начальная точка
	for (int i=0; i<3; i++) {
		if (npc_l)
			packet_l->write_F(npc_l->World.XYZ[i]);
		else
			packet_l->write_F(player_l->DjW->XYZ[i]);
	}

	//поворот
	if (npc_l)
		packet_l->write_2(npc_l->World.heading);
	else
		packet_l->write_2(player_l->DjW->heading);

	//скорость
	if ( ( npc_l &&   npc_l->World.XYZ[0] == npc_l->World.toXYZ[0]   &&   npc_l->World.XYZ[1] == npc_l->World.toXYZ[1])
	  || (!npc_l && player_l->DjW->XYZ[0] == player_l->DjW->toXYZ[0] && player_l->DjW->XYZ[1] == player_l->DjW->toXYZ[1]) )
		packet_l->write_2(0);
	else {
		if ( *type == MOVE_WALK)
			packet_l->write_2(walk_speed);
		else {
			if (npc_l) {
				/*switch (player_l->moveType[1] != MOVE_JUMP ? player_l->moveType[1] : player_l->moveType[0])
				{
					case MOVE_WALK:
					{
						packet_l->write_2(walk_speed);
					}
					default:
					{*/
						packet_l->write_2(walk_speed);
					/*}
				}*/
			} else {
				/*switch (player_l->moveType[1] != MOVE_JUMP ? player_l->moveType[1] : player_l->moveType[0])
				{
					case MOVE_WALK:
					{
						packet_l->write_2(walk_speed);
					}
					default:
					{*/
						packet_l->write_2(player_l->Mount ? player_l->Mount->Speed : player_l->Stats.runSpeed[1]);
					/*}
				}*/
			}
		}
	}

	//конечная точка
	for (int i=0; i<3; i++) {
		if (npc_l)
			packet_l->write_F(npc_l->World.toXYZ[i]);
		else
			packet_l->write_F(player_l->DjW->toXYZ[i]);
	}

	//тип движения
	packet_l->write_2(*type);

	packet_l->write_2(0);

	return packet_l;
}
