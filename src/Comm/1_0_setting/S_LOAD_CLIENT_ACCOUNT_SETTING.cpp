#include "Sharun.hpp"

void S_LOAD_SETTING_failled(OpCode_Enum, const void**);

void* S_LOAD_CLIENT_ACCOUNT_SETTING_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	char FName[Sharun->Settings.Dirs.Settings.Account.length() + 2 + 10];
	sprintf(FName, "%s/%i", Sharun->Settings.Dirs.Settings.Account.c_str(), player_l->Account_Id);
	FILE *fp = fopen(FName, "rb");
	if (fp) {
		packet* packet_l = new_packet(S_LOAD_CLIENT_ACCOUNT_SETTING, -1);
		int size = fread(packet_l->raw + packet_l->pos, 1, PACKET_MAX_SIZE - packet_l->pos, fp);
		fclose(fp);
		if (size > 0) {
			packet_l->pos += size;
			packet_l->size += size;
		}
		player_l->Send(packet_l);
	} else
		S_LOAD_SETTING_failled(S_LOAD_CLIENT_ACCOUNT_SETTING, argv);
	return NULL;
}

void S_LOAD_SETTING_failled(OpCode_Enum Op_ID, const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(Op_ID, 4);

	packet_l->write_4(8);

	player_l->Send(packet_l);
}
