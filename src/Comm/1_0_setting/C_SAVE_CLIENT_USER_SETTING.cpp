#include "Sharun.hpp"

void* C_SAVE_CLIENT_USER_SETTING_f(player* player_l, packet* packet_l)
{
	char FName[Sharun->Settings.Dirs.Settings.User.length() + 2 + 10];
	sprintf(FName, "%s/%i", Sharun->Settings.Dirs.Settings.User.c_str(), player_l->Id);
	FILE *fp = fopen(FName, "wb");
	if (fp) {
		fwrite(packet_l->raw + 4, 1, packet_l->size - 4, fp);
		fclose(fp);
	}
	return NULL;
}
