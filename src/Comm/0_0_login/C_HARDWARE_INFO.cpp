#include "Sharun.hpp"

void* C_HARDWARE_INFO_f(player* player_l, packet* packet_l)
{
	if (Sharun->Settings.HardwareHistory) {
		ushort OS_Pos  = packet_l->read_2();
		ushort CPU_Pos = packet_l->read_2();
		ushort GPU_Pos = packet_l->read_2();


		uint CRAM = packet_l->read_4();
		uint GRAM = packet_l->read_4();
		uint G_W  = packet_l->read_4();
		uint G_H  = packet_l->read_4();

		packet_l->read_1();

		packet_l->swap(OS_Pos - 4);
		uint ScreenID  = packet_l->read_4();
		packet_l->swap();

		uint S_ID, S_W, S_H;
		do {
			S_W  = packet_l->read_4();
			S_H  = packet_l->read_4();
			S_ID = packet_l->read_4();
		} while (S_ID != ScreenID);

		char OS[101], CPU[101], GPU[101];

		packet_l->pos = OS_Pos;
		packet_l->read_C(OS);

		packet_l->pos = CPU_Pos;
		packet_l->read_C(CPU);

		packet_l->pos = GPU_Pos;
		packet_l->read_C(GPU);

		SQL_Format_Char(OS);
		SQL_Format_Char(CPU);
		SQL_Format_Char(GPU);

		const char *SQL = "INSERT INTO `hardware` VALUES ('%i', '%ld', '%i', '%s', '%s', '%s (%i MB)', '%s (%i MB)', '%ix%i', '[%i] %ix%i');";
		Sharun->DB.Query_Slow(SQL, player_l->Account_Id, time(NULL), Sharun->Settings.Server_ID, player_l->connex->IP, OS, CPU, CRAM, GPU, GRAM, G_W, G_H, S_ID, S_W, S_H);
	}
	return NULL;
}
