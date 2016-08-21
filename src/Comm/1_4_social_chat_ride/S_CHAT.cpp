#include "Sharun.hpp"

void* S_CHAT_f(const void** argv)
{
	short i = 0;
	player*	player_l = (player*)argv[i++];
	CHAT_TYPE*	c_type = (CHAT_TYPE*)argv[i++];
	const char*	name = (const char*)argv[i++];
	const char*	text1 = (const char*)argv[i++];
	const char16_t*	text2 = (const char16_t*)argv[i++];
	packet* packet_l = new_packet(S_CHAT, -1);

	switch (*c_type) {
		case PARTY_CHAT:
			packet_l->BC_Type = BC_TYPE_PARTY;
			break;
		case GUILD_CHAT:
			packet_l->BC_Type = BC_TYPE_GUILD;
			break;
		case SHAUT_CHAT:
			packet_l->BC_Type = BC_TYPE_ZONE;
			break;
		case RAID_CHAT:
		case RAID_LEADER_CHAT:
			packet_l->BC_Type = BC_TYPE_RAID;
			break;
		case PRIVATE_CHAT:
		case WHISHPER_CHAT:
			packet_l->BC_Type = BC_TYPE_TARGET;
			break;
		case MAIN_CHAT:
			packet_l->BC_Type = BC_TYPE_ARROUND;
			break;
		default:
			packet_l->BC_Type = BC_TYPE_MAIN;
	}

//	packet_l->write_2(22);
	ushort Name_Pos = packet_l->write_NextPos();
	ushort Text_Pos = packet_l->write_NextPos();
	packet_l->write_4(*c_type);

	if (player_l) {
		packet_l->write_4(player_l->Id);
		packet_l->write_4(player_l->SUBID);
	} else {
		packet_l->write_4(0);
		packet_l->write_4(0);
	}

	packet_l->write_1(0);
/*	if (player_l && player_l->Right > 4)
		packet_l->write_1(1);// chat_icon
	else
*/		packet_l->write_1(0);// chat_icon
	packet_l->write_1(0);

	if(name || player_l)
		Name_Pos = packet_l->write_Pos(Name_Pos);
	if (name)
		packet_l->write_C(name);//имя
	else if (player_l)
		packet_l->write_S(player_l->name_S);
//	else
//		packet_l->write_S(u"");

//	packet_l->write_1(0);

	if(!name && !player_l)
		packet_l->write_2(0x0000);

//	packet_l->write_1(0);
	Text_Pos = packet_l->write_Pos(Text_Pos);
	if (text1) {
		if (!strstr(text1, "<FONT>")) {
			char text1_t[6+strlen(text1)+7+1];
			sprintf(text1_t, "<FONT>%s</FONT>", text1);
			packet_l->write_C(text1_t);//?????
		} else
			packet_l->write_C(text1);//?????
	} else if (text2) {
		if (!strstr16(text2, u"<FONT>")) {
			char16_t text2_t[6+strlen16(text2)+7+1];
			memset(text2_t, 0, sizeof(char16_t)*(6+strlen16(text2)+7+1));
			strcpy16(text2_t, u"<FONT>");
			strcpy16(&text2_t[6], text2);
			strcpy16(&text2_t[6+strlen16(text2)], u"</FONT>");
			packet_l->write_S(text2_t);//?????
		} else
			packet_l->write_S(text2);//?????
	}

//	packet_l->write_1(0);

	return packet_l;
}
