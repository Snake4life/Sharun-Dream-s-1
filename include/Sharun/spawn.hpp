#ifndef _SPAWN_HPP_
#define _SPAWN_HPP_

class spawn
{
	protected:
		pthread_mutex_t	mtx;

	public:
		spawn();
		virtual ~spawn();
		virtual void clean();
		uchar	is; // 0 = not ; 2 = hided
		row_player*	Players[2];
		row_npc*	Friendly[2];
		row_monster*	Monsters[2];

		virtual bool	in(player*);
		virtual bool	in(npc*);
		virtual bool	in(monster*);

		virtual void	add(player*);
		virtual void	add(npc*);
		virtual void	add(monster*);

		virtual void	del(player*);
		virtual void	del(npc*);
		virtual void	del(monster*);
};

#endif // _SPAWN_HPP_
