#include "Sharun.hpp"

void* S_PLAYER_STAT_UPDATE_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_PLAYER_STAT_UPDATE, 200);

	packet_l->write_4(player_l->Stats.HP); // Actuel HP
	packet_l->write_4(player_l->Stats.MP); // Actuel MP

	packet_l->write_4(0);

	packet_l->write_4(player_l->Stats.maxHP[1]); // Max HP
	packet_l->write_4(player_l->Stats.maxMP[1]); // Max MP

	packet_l->write_4(player_l->Stats.stat_detail[Unbuffed][powerFactor]);
	packet_l->write_4(player_l->Stats.stat_detail[Unbuffed][defenceFactor]);
	packet_l->write_4(player_l->Stats.stat_detail[Unbuffed][impactFactor]);
	packet_l->write_4(player_l->Stats.stat_detail[Unbuffed][balanceFactor]);
	
	packet_l->write_2(player_l->Stats.runSpeed[0]); // базовая скорость бега
	packet_l->write_2(walk_speed);//2800 Walk speed
	packet_l->write_2(player_l->Stats.atkSpeed[0]);

	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][critRate]); // шанс крита
	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][critRcpt]); // защита от крита (пока не ясно кд или шанс режет)
	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][critDmg]); // крит дамаг

	packet_l->write_4(player_l->Stats.attack[0]); // базовая атака мин
	packet_l->write_4(player_l->Stats.attack[0]); // базовая атака макс
	packet_l->write_4(player_l->Stats.defense[0]);
	packet_l->write_4(player_l->Stats.impact[0]);
	packet_l->write_4(player_l->Stats.balance[0]);

	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][weakRcpt]);// (Hex)Сопротивление к Ядам 38
	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][dmgRcpt]);// (Hex)Сопротивление к повреждениям 38
	packet_l->write_F(player_l->Stats.stat_detail[Unbuffed][stunRcpt]);// (Hex)Сопротивление к обиздвиживанию 38

	packet_l->write_4(player_l->Stats.stat_detail[Buffed][powerFactor] - player_l->Stats.stat_detail[Unbuffed][powerFactor]); // бонус к повер фактору
	packet_l->write_4(player_l->Stats.stat_detail[Buffed][defenceFactor] - player_l->Stats.stat_detail[Unbuffed][defenceFactor]); // бонус к дефенс фактору
	packet_l->write_4(player_l->Stats.stat_detail[Buffed][impactFactor] - player_l->Stats.stat_detail[Unbuffed][impactFactor]); // бонус к импакт фактору
	packet_l->write_4(player_l->Stats.stat_detail[Buffed][balanceFactor] - player_l->Stats.stat_detail[Unbuffed][balanceFactor]); // бонус к баланс фактору

	packet_l->write_4((player_l->Mount ? player_l->Mount->Speed : player_l->Stats.runSpeed[1]) - player_l->Stats.runSpeed[0]); // Бонус к скорости бега...

	packet_l->write_2(player_l->Stats.atkSpeed[1] - player_l->Stats.atkSpeed[0]); // бонус к атак спиду

	packet_l->write_F(player_l->Stats.stat_detail[Buffed][critRate] - player_l->Stats.stat_detail[Unbuffed][critRate]); // крит рейт бонус
	packet_l->write_F(player_l->Stats.stat_detail[Buffed][critRcpt] - player_l->Stats.stat_detail[Unbuffed][critRcpt]); // крит ресист бонус
	packet_l->write_F(player_l->Stats.stat_detail[Buffed][critDmg] - player_l->Stats.stat_detail[Unbuffed][critDmg]); // крит мощность бонус

	packet_l->write_4(player_l->Stats.attack[1] - player_l->Stats.attack[0]); // бонус к атаке мин
	packet_l->write_4(player_l->Stats.attack[1] - player_l->Stats.attack[0]); // бонус к атаке макс
	packet_l->write_4(player_l->Stats.defense[1] - player_l->Stats.defense[0]); // бонус к защите
	packet_l->write_2(player_l->Stats.impact[1] - player_l->Stats.impact[0]); // бонус к импакту
	packet_l->write_2(player_l->Stats.balance[1] - player_l->Stats.balance[0]); // бонус к балансу

	packet_l->write_F(player_l->Stats.stat_detail[Buffed][weakRcpt] - player_l->Stats.stat_detail[Unbuffed][weakRcpt]);
	packet_l->write_F(player_l->Stats.stat_detail[Buffed][dmgRcpt] - player_l->Stats.stat_detail[Unbuffed][dmgRcpt]);
	packet_l->write_F(player_l->Stats.stat_detail[Buffed][stunRcpt] - player_l->Stats.stat_detail[Unbuffed][stunRcpt]);

	packet_l->write_2(0);//0000 // new
	packet_l->write_2(0);//0000 // new

	packet_l->write_2(player_l->Level);
	packet_l->write_2(/*player_l.isBattleStanced() ? 1 : */0);

	packet_l->write_2(4);
	packet_l->write_1(1);

	packet_l->write_4(player_l->Stats.maxHP[1] - player_l->Stats.maxHP[0]);
	packet_l->write_4(player_l->Stats.maxMP[1] - player_l->Stats.maxMP[0]);
	packet_l->write_4(player_l->Stats.Stamina[1]);
	packet_l->write_4(player_l->Stats.maxStamina);

	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);// карма


	if (player_l->Client_Version < 39) {
		packet_l->write_4(0);// Уровень брони
		packet_l->write_4(0);// Уровень брони
	} else {
		packet_l->write_4(209);
		packet_l->write_4(209);
	}

	packet_l->write_8(0);

	packet_l->write_4(8000);
	packet_l->write_4(3);

	if (player_l->Client_Version < 39)
		packet_l->write_4(1);
	else {
		packet_l->write_4(53);
		packet_l->write_F(1000);
		packet_l->write_4(0);
		packet_l->write_F(1);
	  
	}

	player_l->Send(packet_l);
	return NULL;
}
