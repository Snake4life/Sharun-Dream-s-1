#include <Dream/Dream.hpp>

#include <queue>
//#include <unistd.h>

waiting_thd	BroadcastD_thd;
std::queue<packet*> BroadcastD_queue;
Fixed_thread_W_t	BroadcastD_thread;

void BroadcastD_Add(packet* packet_l)
{
	pthread_mutex_lock(&BroadcastD_thread.mtx);
	BroadcastD_queue.push(packet_l);
	BroadcastD_thd.resume();
	pthread_mutex_unlock(&BroadcastD_thread.mtx);
}

void BroadcastD_Cleanup()
{
	packet *packet_l;
	Fixed_thread_Cleanup(&BroadcastD_thread);
	while (!BroadcastD_queue.empty()) {
		packet_l = BroadcastD_queue.front();
		BroadcastD_queue.pop();
		delete packet_l;
	}
}

void BroadcastD_Thread(thread_list* my_thread)
{
	packet* packet_l;
	Fixed_thread_t *BroadcastD_thread_l;
	BroadcastD_thread_l = Fixed_thread_Add(BroadcastD_Cleanup, &BroadcastD_thread, my_thread);
	while (my_thread->run) {
		pthread_mutex_lock(&BroadcastD_thread.mtx);
		if (BroadcastD_queue.empty()) {
			BroadcastD_thd.push(my_thread);
			pthread_mutex_unlock(&BroadcastD_thread.mtx);
			my_thread->wait();
		} else {
			packet_l = BroadcastD_queue.front();
			BroadcastD_queue.pop();
			pthread_mutex_unlock(&BroadcastD_thread.mtx);

			pthread_mutex_lock(&Sharun->Players.mtx);
			for (uint i=0; i<Sharun->Settings.Player_Max; i++) {
				bool is_spawP_b = false;
				if (Sharun->Players.Lists[i] && packet_l->sender) is_spawP_b = Sharun->Players.Lists[i]->Spawn->in(packet_l->sender);
				if (   packet_l
				    && (!(packet_l->BC_Type & BC_TYPE_NOT_ME) || ((packet_l->BC_Type & BC_TYPE_NOT_ME) && packet_l->sender->Players_ID != i))
				    && Sharun->Players.Lists[i]
				    && Sharun->Players.Lists[i]->loged
				    && Sharun->Players.Lists[i]->DjW
				    && Sharun->Players.Lists[i]->DjW->Zone
				    && (  (packet_l->BC_Type & BC_TYPE_MAIN)
				      || ((packet_l->BC_Type & BC_TYPE_ZONE) && packet_l->sender && packet_l->sender->DjW->Zone == Sharun->Players.Lists[i]->DjW->Zone)
				      || ((packet_l->BC_Type & BC_TYPE_ARROUND) && packet_l->sender && packet_l->sender->DjW->Zone == Sharun->Players.Lists[i]->DjW->Zone
						&& ( (packet_l->Op_ID == S_DESPAWN_NPC && ((packet_l->BC_Type & BC_TYPE_FORCE) || getDistance_2D(packet_l->sender->DjW->XYZ, Sharun->Players.Lists[i]->DjW->XYZ) > 100) && is_spawP_b)
						  || (packet_l->Op_ID == S_SPAWN_USER  && getDistance_2D(packet_l->sender->DjW->XYZ, Sharun->Players.Lists[i]->DjW->XYZ) <= 100 && !is_spawP_b)
	/*					  || ((packet_l->Op_ID == S_USER_EXTERNAL_CHANGE || packet_l->Op_ID == S_MOUNT_VEHICLE || packet_l->Op_ID == S_UNMOUNT_VEHICLE) && getDistance_2D(packet_l->sender->DjW->XYZ, Sharun->Players.Lists[i]->DjW->XYZ) <= 100
						    && (Sharun->Players.Lists[i] == packet_l->sender || (Sharun->Players.Lists[i] != packet_l->sender && is_spawP_b)))
	*/					  || (packet_l->Op_ID == S_CHAT && getDistance_2D(packet_l->sender->DjW->XYZ, Sharun->Players.Lists[i]->DjW->XYZ) < 200)
						  || ((packet_l->Op_ID != S_DESPAWN_NPC && packet_l->Op_ID != S_SPAWN_USER && packet_l->Op_ID != S_CHAT) && getDistance_2D(packet_l->sender->DjW->XYZ, Sharun->Players.Lists[i]->DjW->XYZ) <= 100
						    && (Sharun->Players.Lists[i] == packet_l->sender || (Sharun->Players.Lists[i] != packet_l->sender && is_spawP_b)))
						  )
					)
				    )
				) {
					if (packet_l->Op_ID == S_DESPAWN_NPC)
						Sharun->Players.Lists[i]->Spawn->del(packet_l->sender);
					else if (packet_l->Op_ID == S_SPAWN_USER)
						Sharun->Players.Lists[i]->Spawn->add(packet_l->sender);
					Sharun->Players.Lists[i]->Send_Direct(packet_l->clone());
				}
			}
			pthread_mutex_unlock(&Sharun->Players.mtx);

			delete packet_l;
		}
	}
	Fixed_thread_Del(&BroadcastD_thread, BroadcastD_thread_l);
	DEBUG("%s (%i) :: BroadcastD thread Stopped.\n", __FILE__, __LINE__);
	pthread_exit(NULL);
}

void BroadcastD_Greet(player* player_l, OpCode_Enum Op_ID, BROADCAST_TYPE BC_Type)
{
	pthread_mutex_lock(&Sharun->Players.mtx);
	for (uint i=0; i<Sharun->Settings.Player_Max; i++) {
		bool is_spawP_b = false;
		if (Sharun->Players.Lists[i] && player_l) is_spawP_b = player_l->Spawn->in(Sharun->Players.Lists[i]);
		if (   player_l
		    && (!(BC_Type & BC_TYPE_NOT_ME) || ((BC_Type & BC_TYPE_NOT_ME) && player_l->Players_ID != i))
		    && Sharun->Players.Lists[i]
		    && Sharun->Players.Lists[i]->loged
		    && Sharun->Players.Lists[i]->DjW
		    && Sharun->Players.Lists[i]->DjW->Zone
		    && (  (BC_Type & BC_TYPE_MAIN)
		      || ((BC_Type & BC_TYPE_ZONE) && player_l->DjW->Zone == Sharun->Players.Lists[i]->DjW->Zone)
		      || ((BC_Type & BC_TYPE_ARROUND) && player_l->DjW->Zone == Sharun->Players.Lists[i]->DjW->Zone
				&& ((getDistance_2D(player_l->DjW->toXYZ, Sharun->Players.Lists[i]->DjW->toXYZ) <= 100  && !is_spawP_b)
				 || (getDistance_2D(player_l->DjW->toXYZ, Sharun->Players.Lists[i]->DjW->toXYZ) > 100  &&  is_spawP_b)
				   )
			 )
		    )
		) {
			const void *args[] = {Sharun->Players.Lists[i], NULL};
			packet* packet_buf = (packet*) Sharun->OpCodes.Send[Op_ID](args);
			if (packet_buf)
				player_l->Send(packet_buf);
			if (Op_ID == S_DESPAWN_NPC)
				player_l->Spawn->del(Sharun->Players.Lists[i]);
			else if (Op_ID == S_SPAWN_USER)
				player_l->Spawn->add(Sharun->Players.Lists[i]);
		}
	}
	pthread_mutex_unlock(&Sharun->Players.mtx);
}
