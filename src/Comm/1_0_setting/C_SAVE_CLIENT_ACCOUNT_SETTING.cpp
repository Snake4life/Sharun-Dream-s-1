#include "Sharun.hpp"

void* C_SAVE_CLIENT_ACCOUNT_SETTING_f(player* player_l, packet* packet_l)
{
	char FName[Sharun->Settings.Dirs.Settings.Account.length() + 2 + 10];
	sprintf(FName, "%s/%i", Sharun->Settings.Dirs.Settings.Account.c_str(), player_l->Account_Id);
	FILE *fp = fopen(FName, "wb");
	if (fp) {
		fwrite(packet_l->raw + 4, 1, packet_l->size - 4, fp);
		fclose(fp);
	}
	return NULL;
}
