#include <Dream/Dream.hpp>

void regen_hp(player* player_l)
{
	const void* args[] = {player_l, NULL, NULL, &var_NBR[0], &var_NBR[0]};
	float stamina_factor = Stamina(player_l);
	if (!player_l->Stats.HP && player_l->Spawn->is<2) {
		player_l->Spawn->is = 2;
		player_l->Stats.HP = 0;
		player_l->Stats.MP = 0;
		player_l->Stats.Stamina[0] = player_l->Stats.Stamina[1];
		player_l->Stats.Stamina[1] = 0;
		player_l->Stats.maxHP[1] = player_l->Stats.stat_detail[2][maxHP] * HP_MOD[player_l->Class_Id][player_l->Level] * stamina_factor;
		player_l->Stats.maxMP[1] = player_l->Stats.stat_detail[2][maxMP] * stamina_factor;
		Sharun->OpCodes.Send[S_CREATURE_CHANGE_HP](args);
		Sharun->OpCodes.Send[S_PLAYER_CHANGE_MP](args);
		if (Sharun->Settings.Stamina4Speed) {
			player_l->Stats.atkSpeed[0] = player_l->Stats.stat_detail[2][atkSpd] * stamina_factor;
			player_l->Stats.runSpeed[0] = player_l->Stats.stat_detail[2][runSpd] * stamina_factor;
			Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
		}
		return;
	}
	if ((player_l->Stats.HP > 0 && player_l->Stats.HP < player_l->Stats.maxHP[1]) || player_l->Stats.HP > player_l->Stats.maxHP[1]) {
	int hp = player_l->Stats.stat_detail[2][regHp] * HP_MOD[player_l->Class_Id][player_l->Level];
	if (player_l->Mount && player_l->Mount->R_HP) hp += player_l->Stats.maxHP[0] * 1.005;
		if (player_l->Stats.HP + hp > player_l->Stats.maxHP[1] || player_l->Stats.HP > player_l->Stats.maxHP[1])
			player_l->Stats.HP = player_l->Stats.maxHP[1];
		else player_l->Stats.HP += hp;
		player_l->Stats.maxHP[1] = player_l->Stats.stat_detail[2][maxHP] * HP_MOD[player_l->Class_Id][player_l->Level] * stamina_factor;
		Sharun->OpCodes.Send[S_CREATURE_CHANGE_HP](args);
	}
}

void regen_mp(player* player_l)
{
	const void* args[] = {player_l, NULL, NULL, &var_NBR[0], &var_NBR[0]};
	if (!player_l->Stats.HP) return;
	int mp = player_l->Stats.stat_detail[2][regMp];
	if (player_l->Mount && player_l->Mount->R_MP) mp += player_l->Stats.maxMP[0] * 1.005;
	if ((mp>0 && player_l->Stats.MP < player_l->Stats.maxMP[1]) || (mp<0 && player_l->Stats.MP >0 ) || player_l->Stats.MP > player_l->Stats.maxMP[1]) {
		if (mp<0 && ((long)player_l->Stats.MP) < (mp<0?-(mp):mp))
			player_l->Stats.MP = 0;
		else if ((mp>0 && player_l->Stats.MP + mp > player_l->Stats.maxMP[1]) || player_l->Stats.MP > player_l->Stats.maxMP[1])
			player_l->Stats.MP = player_l->Stats.maxMP[1];
		else player_l->Stats.MP += mp;
		float stamina_factor = Stamina(player_l);
		player_l->Stats.maxMP[1] = player_l->Stats.stat_detail[2][maxMP] * stamina_factor;
		Sharun->OpCodes.Send[S_PLAYER_CHANGE_MP](args);
	}
}

void regen_sp(player* player_l)
{
	const void* args[] = {player_l, NULL, NULL, &var_NBR[0], &var_NBR[0]};
	if (!player_l->Stats.HP) return;
	int sp = 0;
	if ((player_l->Stats.Stamina[1] < 120 || (0 && player_l->Stats.Stamina[1] < 130)) && player_l->Mount && player_l->Mount->R_Stamina) sp = 1;
	player_l->Stats.Stamina[1] += sp;
	if (player_l->Stats.Stamina[0] != player_l->Stats.Stamina[1]) {
		float stamina_factor = Stamina(player_l);
		if (Sharun->Settings.Stamina4Speed) {
			player_l->Stats.atkSpeed[0] = player_l->Stats.stat_detail[2][atkSpd] * stamina_factor;
			player_l->Stats.runSpeed[0] = player_l->Stats.stat_detail[2][runSpd] * stamina_factor;
			Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
		}
		player_l->Stats.Stamina[0] = player_l->Stats.Stamina[1];
	}
}
