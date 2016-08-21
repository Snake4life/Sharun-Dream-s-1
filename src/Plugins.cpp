#include <Dream/Dream.hpp>

#include <dirent.h>
#include <dlfcn.h>

#ifndef WIN32
#define PluginEXT ".so"
#else
#define PluginEXT ".dll"
void *CallBack_Plugin_Link[] = {
	// sharun_t WIN32 Adaptator
	NULL,
	// DEBUG WIN32 Adaptator
	(void*) DEBUG,
	(void*) DEBUG2,
	// DB WIN32 Adaptator
	(void*) DB_Query_Add,
	(void*) DB_Max_Row,
	(void*) DB_Seek,
	(void*) DB_Next_Row,
	(void*) DB_Result_Clear,
	(void*) DB_Query_Fast,
	(void*) DB_Query_Slow,
	(void*) DB_Query_int,
	(void*) DB_Query_long,
	(void*) DB_Query_float,
	(void*) DB_Query_S,
	(void*) DB_Query_char,
	// NEW_* WIN32 Adaptator
	(void*) free_player,
	(void*) new_packet,
	(void*) packet_send_empty,
	(void*) Send_Packet,
	(void*) player_Load,
	(void*) player_Save,
	(void*) Stats_Update,
	// Equipment WIN32 Adaptator
	(void*) DB_getEquipment,
	(void*) DB_getEquipment_Ench,
	(void*) DB_getEquipment_Max,
	// Some needed tools WIN32 Adaptator
	(void*) get_Experience_LEVEL,
	(void*) World_Spam,
	(void*) World_Exit,
	(void*) World_Chat,
	(void*) World_PlayerMove,
	(void*) World_PlayerSocial,
	(void*) World_PlayerMount,
	(void*) World_PlayerSkill,
	// Broadcast WIN32 Adaptator
	(void*) BroadcastD_Add,
	(void*) BroadcastD_Greet,
	// SECURITY STOP
	NULL
};
#endif

void Plugin_Scan(std::string Path)
{
	DIR *pdir;
	struct dirent *dirp;
	if ((pdir = opendir(Path.c_str()))) {
		while ((dirp = readdir(pdir))) {
			if ((strcmp(dirp->d_name, ".")) && (strcmp(dirp->d_name, ".."))) {
				std::string filename = Path + DSlash + dirp->d_name;
				if (dir_exist(filename.c_str()))
					Plugin_Scan(filename);
				else {
					if (!strcmp(&dirp->d_name[strlen(dirp->d_name)-strlen(PluginEXT)], PluginEXT)) {
						void *handle = dlopen(filename.c_str(), RTLD_LAZY);
						if (handle) {
#ifdef WIN32
							void (*CallBack_Plugin)(void**) = (void(*)(void**))dlsym(handle, "CallBack_Plugin");
							if (CallBack_Plugin)
								CallBack_Plugin(CallBack_Plugin_Link);
#endif
							plugin_t* Plugin_l = (plugin_t*)dlsym(handle, "Plugin");
							Plugin_l->handle = handle;
							if (Plugin_l->init)
								Plugin_l->init();
DEBUG("--> %s: Ok !\n", dirp->d_name);
							for (int i=0; Plugin_l->recv && Plugin_l->recv[i].name; i++) {
								DEBUG("  %s\n", Plugin_l->recv[i].name);
								if (Plugin_l->recv[i].func)
									Sharun->OpCodes.Set_Recv(Plugin_l->recv[i].name, Plugin_l->recv[i].func);
							}
							for (int i=0; Plugin_l->send && Plugin_l->send[i].name; i++) {
								DEBUG("  %s\n", Plugin_l->send[i].name);
								if (Plugin_l->send[i].func)
									Sharun->OpCodes.Set_Send(Plugin_l->send[i].id, Plugin_l->send[i].func);
							}
/*							dlclose(handle);
							handle = NULL;*/
						}
					}
				}
			}
		}
		closedir(pdir);
	}

  
}


void Plugin_Init()
{
#ifdef WIN32
	CallBack_Plugin_Link[0] = (void*) Sharun;
#endif
	Plugin_Scan(Sharun->Settings.Dirs.Plugins);
}
