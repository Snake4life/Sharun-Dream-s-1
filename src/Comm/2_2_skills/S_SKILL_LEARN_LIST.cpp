#include "Sharun.hpp"

void* S_SKILL_LEARN_LIST_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SKILL_LEARN_LIST, -1);

	const char *sql = "SELECT * FROM `skill_learn` WHERE `class` IN (-1, %i) AND `race` IN (-1, %i) AND `id`*10000+`lv`*100+`type` NOT IN (SELECT `skill_id`*10000+`lv`*100+`type` FROM `character_skill` WHERE `owner_id`='%i' AND `skill_id`=`id`) ORDER BY `id`, `lv`, `type`;";
	void *rslt = Sharun->DB.Query_Fast(1, sql, player_l->Class_Id, player_l->Race_Id, player_l->Id);
	char **row;

/*
00 id
01 type
02 lv
03 class
04 race
05 active
06 plv
07 price
*/
	ushort count=0, countPos, replPos, nextPos = 0;
	countPos = packet_l->write_NextPos();
	nextPos = packet_l->write_NextPos();
	
	while ((row = Sharun->DB.Next_Row(rslt))) {
		packet_l->write_Pos(nextPos);

		packet_l->write_Pos(0);
		nextPos = packet_l->write_NextPos();

		if(atoi(row[2]) <= 1)
			packet_l->write_4(0);
		else {
			packet_l->write_2(1);
			replPos = packet_l->write_NextPos();
		}

		packet_l->write_4(0);

		uint id = atoi(row[0])*10000 + atoi(row[2])*100 + atoi(row[1]);
		packet_l->write_4(id);// ид скила

		packet_l->write_1(atoi(row[5]));// ативный 01, пассивный 00

		packet_l->write_4(atoi(row[7]));// цена за изучение скила
		packet_l->write_4(atoi(row[6]));// минимальный лвл на изучение
		packet_l->write_1(1);//SkillShopDialog.isLearneableSkill(player, currentSkills, skill, false)? 1 : 0); //может изучать 1 или неможет 0

		if(atoi(row[2]) > 1)
		{
			packet_l->write_Pos(replPos);
			packet_l->write_Pos(0);
			packet_l->write_2(0);
			uint replid = atoi(row[0])*10000 + atoi(row[2])*100 + atoi(row[1])-1;
			packet_l->write_4(replid);// ид заменяемого скила
			packet_l->write_1(atoi(row[5]));// ативный 01, пассивный 00 заменяемый скилл
		}
		count++;
	}

	packet_l->swap(countPos);
	packet_l->write_2(count);
	packet_l->swap(0);

	Sharun->DB.Result_Clear(rslt);

	player_l->Send(packet_l);
	return NULL;
}
