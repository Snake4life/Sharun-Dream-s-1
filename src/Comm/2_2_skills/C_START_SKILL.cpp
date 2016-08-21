#include "Sharun.hpp"

void* C_START_SKILL_f(player* player_l, packet* packet_l)
{
	uint Skill_ID = packet_l->read_4();
	Skill_ID -= 67108864;

	ushort Heading = packet_l->read_2(); //Heading
	float pos[3];
	float target_pos[3];

	pos[0] = packet_l->read_F(); // X
	pos[1] = packet_l->read_F(); // Y
	pos[2] = packet_l->read_F(); // Z

	target_pos[0] = packet_l->read_F(); // target X
	target_pos[1] = packet_l->read_F(); // target Y
	target_pos[2] = packet_l->read_F(); // target Z
/*
	packet_l->pos += 2;
	packet_l->pos += 1;

	uint Tar_ID = packet_l->read_4(); // target ID
	uint Sub_ID = packet_l->read_4(); // target SubID
*/
	World_PlayerSkill(player_l, NULL, Skill_ID, Heading, pos, target_pos);

	return NULL;
}
/*
	@Override
	public void runImpl()
	{
		Player player = getPlayer();

		if(player == null)
			return;

		Skill skill = player.getSkill(skillId);

		if(skill == null)
		{
			player.sendMessage("Этого скила у вас нету.");
			return;
		}

		float startX = getStartX();
		float startY = getStartY();
		float startZ = getStartZ();

		Character target = null;

		if(player.getSquareDistance(startX, startY) > Config.WORLD_MAX_SKILL_DESYNC)
		{
			startX = player.getX();
			startY = player.getY();
		}

		int targetId = getTargetId();
		int targetSubId = getTargetSubId();

		if(targetId > 0)
			target = World.getAroundById(Character.class, player, targetId, targetSubId);

		player.setTarget(target);

		float targetX = getTargetX();
		float targetY = getTargetY();
		float targetZ = getTargetZ();

		int heading = getHeading();

		if(target != null && skill.isCorrectableTarget() && targetSubId == Config.SERVER_PLAYER_SUB_ID)
		{
			targetX = target.getX();
			targetY = target.getY();
			targetZ = target.getZ() + target.getGeomHeight() * 0.5F;

			heading = Angles.calcHeading(startX, startY, targetX, targetY);
		}

		player.getAI().startCast(startX, startY, startZ, skill, 0, heading, targetX, targetY, targetZ);
	}

*/