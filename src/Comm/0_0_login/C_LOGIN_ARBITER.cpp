#include "Sharun.hpp"

/***
 * 	TODO: IP BLOCK !
 **/
void* C_LOGIN_ARBITER_f(player* player_l, packet* packet_l)
{
	ushort Pos_User = packet_l->read_2();
	ushort Pos_Pass = packet_l->read_2();
	ushort Pass_Len = packet_l->read_2();

	packet_l->pos += 4;
	packet_l->pos += 1;
	ushort C_Lang = packet_l->read_2();

	char   User[100];
	packet_l->pos = Pos_User;
	packet_l->read_C(User);

	char Pass[Pass_Len+1];
	packet_l->pos = Pos_Pass ;
	packet_l->read(Pass, Pass_Len);
	Pass[Pass_Len] = 0;

	SQL_Format_Char(User);

	void *rslt = NULL;
	const char *sql = "SELECT `AccoundId`, `password`, `RightLevel`, `end_pay` FROM `accounts` WHERE `Name`='%s' AND `PasswordRecovery` IS NULL AND `end_block` < '%ld'";
	char **row;

	int run;
	do {
		run = 0;
		rslt = Sharun->DB.Query_Fast(1, sql, User, time(NULL));
		row = Sharun->DB.Next_Row(rslt);
		if ((!row || !row[0]) && Sharun->Settings.AutoAccount) {
			Sharun->DB.Result_Clear(rslt);
			rslt = NULL;
			Sharun->DB.Query_Fast(0, "INSERT INTO `accounts` (`Name`, `password`) VALUES ('%s', '%s');", User, Pass);
			run = 1;
		}
	} while (run);

	if (row[0] && !strncmp(row[1], Pass, strlen(row[1]))) {
		player_l->Account_Id = atoi(row[0]);
		player_l->Right = atoi(row[2]);
		player_l->end_pay = atol(row[3]);
		const char *sql = "UPDATE `accounts` SET `last_ip` = '%s', `lastOnlineUTC`='%i' WHERE `AccoundId`='%ld'";
		Sharun->DB.Query_Slow(sql, player_l->connex->IP, time(NULL), player_l->Account_Id);
		player_l->C_Lang = (CLIENT_LANG) C_Lang;
	} else {
		const void *args[] = {player_l, &var_NBR[0], NULL};
		Sharun->OpCodes.Send[S_LOGIN_ARBITER](args);
		free_player(player_l);
		player_l = NULL;
	}
	Sharun->DB.Result_Clear(rslt);
	return player_l;
}
