#include "Sharun.hpp"

void* S_FRIEND_LIST_f(const void** argv)
{
	player*	player_l = (player*)argv[0];

	const char *sql = "SELECT `Friends_List`.*, `characters`.* FROM `Friends_List`, `characters` WHERE `Player_ID` = '%ld' AND `object_id` = `Friend_ID`;";
	void *rslt = Sharun->DB.Query_Fast(1, sql, player_l->Id);

	ushort count = Sharun->DB.Max_Row(rslt);

	packet* packet_l = new_packet(S_FRIEND_LIST, 6 + count * 63 + count * (50 * 2 + 40));

	packet_l->write_2(count);
	ushort nextPos = packet_l->write_NextPos();

	ushort MessPos = packet_l->write_NextPos();
	packet_l->write_Pos(MessPos);
	packet_l->write_S(u"[Say Test 1 !]");
//	packet_l->write_S(player_l->comment_S);

	char **row;
	for (int i=0; (row = Sharun->DB.Next_Row(rslt)); i++) {
		packet_l->write_Pos(nextPos);
		packet_l->write_Pos(0);
		nextPos = packet_l->write_NextPos();

		ushort NamePos = packet_l->write_NextPos();
		ushort CommPos = packet_l->write_NextPos();
		MessPos = packet_l->write_NextPos();

		packet_l->write_4(atoi(row[DB_Friends_List_Friend_ID]));	// Player ID

		short group_id = atoi(row[DB_Friends_List_Group]);
		// group ... 1 = Waiting agree
		if  (group_id < 0)
			packet_l->write_2(0);
		else
			packet_l->write_4(group_id);

		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_level]));	// level
		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_race_id]));	// race
		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_class_id]));	// class

		/* bonds lv1 = 0-49 ; lv2 = 50-99 ; lv3 = 100-299 ; lv4 = 300-499 ; lv5 = 500-999 ; lv6 = 1000-9999 */
		packet_l->write_4(atoi(row[DB_Friends_List_Bonds]));	// Friendship bonds

		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_country]));	// Zone Data 1
		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_lander]));	// Zone Data 2
		packet_l->write_4(atoi(row[DB_Friends_List_MAXI + DB_characters_aera]));	// Zone Data 3

		// GM Icon ?
		if (atoi(row[DB_Friends_List_MAXI + DB_characters_class_id]) > 4)
			packet_l->write_1(1);
		else
			packet_l->write_1(0);

		packet_l->write_8(atoi(row[DB_Friends_List_MAXI + DB_characters_last_online]));	// last loged time

		// 1 = Friend request ?
		switch (group_id) {
			case -2:
				packet_l->write_2(2);	// from him
				break;
			case -1:
				packet_l->write_2(1);	// from me
				break;
			default:
				packet_l->write_2(0);	// Accepted
		}
		packet_l->write_2(0);	// ???
		packet_l->write_4(0);	// ???

		packet_l->write_Pos(NamePos);
		packet_l->write_C(row[DB_Friends_List_MAXI + DB_characters_char_name]);

		packet_l->write_Pos(CommPos);
		if (group_id < 0)
			packet_l->write_S(u"");
		else
			packet_l->write_C(row[DB_Friends_List_Comment]);

		packet_l->write_Pos(MessPos);
		if (group_id < 0)
			packet_l->write_C(row[DB_Friends_List_MAXI + DB_characters_friend_note]);
		else
			packet_l->write_S(u"");
	}

	player_l->Send(packet_l);

	return packet_l;
}
