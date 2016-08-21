#include <Dream/Dream.hpp>

spawn::spawn()
{
		pthread_mutex_init(&mtx, NULL);
		is = 0;
		Players[0] = NULL;
		Players[1] = NULL;
		Friendly[0] = NULL;
		Friendly[1] = NULL;
		Monsters[0] = NULL;
		Monsters[1] = NULL;
}

spawn::~spawn()
{
	clean();
	pthread_mutex_destroy(&mtx);
}

void spawn::clean()
{
	while(Players[0]) {
		row_player* t_dat = Players[0];
		Players[0] = t_dat->Next;
		delete t_dat;
	}
	while(Friendly[0]) {
		row_npc* t_dat = Friendly[0];
		Friendly[0] = t_dat->Next;
		delete t_dat;
	}
	while(Monsters[0]) {
		row_monster* t_dat = Monsters[0];
		Monsters[0] = t_dat->Next;
		delete t_dat;
	}
}
//=========================================================================================
bool spawn::in(player* t_val)
{
	row_player* t_dat = Players[0];
	while (t_dat) {
		if (t_dat->Player == t_val)
			return true;
		t_dat = t_dat->Next;
	}
	return false;
}

bool spawn::in(npc* t_val)
{
	row_npc* t_dat = Friendly[0];
	while (t_dat) {
		if (t_dat->NPC == t_val)
			return true;
		t_dat = t_dat->Next;
	}
	return false;
}

bool spawn::in(monster* t_val)
{
	row_monster* t_dat = Monsters[0];
	while (t_dat) {
		if (t_dat->Monster == t_val)
			return true;
		t_dat = t_dat->Next;
	}
	return false;
}
//=========================================================================================
void spawn::add(player* t_val)
{
	if (!Players[0])
		Players[0] = Players[1] = new row_player();
	else {
		Players[1]->Next = new row_player();
		Players[1] = Players[1]->Next;
	}
	Players[1]->Player = t_val;
}

void spawn::add(npc* t_val)
{
	if (!Friendly[0])
		Friendly[0] = Friendly[1] = new row_npc();
	else {
		Friendly[1]->Next = new row_npc();
		Friendly[1] = Friendly[1]->Next;
	}
	Friendly[1]->NPC = t_val;
}

void spawn::add(monster* t_val)
{
	if (!Monsters[0])
		Monsters[0] = Monsters[1] = new row_monster();
	else {
		Monsters[1]->Next = new row_monster();
		Monsters[1] = Monsters[1]->Next;
	}
	Monsters[1]->Monster = t_val;
}
//=========================================================================================
void spawn::del(player* t_val)
{
	row_player* t_dat = Players[0];
	while (t_dat && t_dat->Player != t_val)
		t_dat = t_dat->Next;
	if (t_dat->Player != t_val)
		delete t_dat;
}

void spawn::del(npc* t_val)
{
	row_npc* t_dat = Friendly[0];
	while (t_dat && t_dat->NPC != t_val)
		t_dat = t_dat->Next;
	if (t_dat->NPC != t_val)
		delete t_dat;
}

void spawn::del(monster* t_val)
{
	row_monster* t_dat = Monsters[0];
	while (t_dat && t_dat->Monster != t_val)
		t_dat = t_dat->Next;
	if (t_dat->Monster != t_val)
		delete t_dat;
}
