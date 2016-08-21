#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

class settings {
	public:
		settings();
		virtual ~settings();
		ushort	Server_ID;
		char*	Server_Name;
		char	Start_Time[20];
		char*	SERVER_SIGN;
		char*	SERVER_COPYRIGHT;
		ushort	Start_Count;
		ushort	PLAYER_COUNT;
		ushort	Player_Max;
		ushort	Charcters_Max_Per_Account;
		ushort	Confirm_Time;
		bool	Packets_Fill_Size;
		bool	AutoAccount;
		bool	HardwareHistory;
		bool	newHP;
		bool	Stamina4Speed;
		bool	main_run;
		struct Dirs {
			std::string Saves;
			std::string Logs;
			std::string WWW;
			std::string OpCodes;
			std::string Plugins;
			std::string Guild_Logo;
			struct Settings {
				std::string Account;
				std::string Chat;
				std::string User;
			} Settings;
		} Dirs;
		struct Thread {
			ushort	Broadcast;
			ushort	Httpd;
			struct DataBase {
				ushort Fast;
				ushort Slow;
			} DataBase;
		} Thread;
		struct Net {
			bool	localhost;
			char	IP[16];
			struct Ports {
				ushort	Game;
				ushort	Httpd;
				ushort	Bridge;
			} Ports;
		} Net;
		struct SubID {
			uint	PLayer;
			uint	NPC;
			uint	Monster;
			uint	Shot;
			uint	Collect;
			uint	Drop;
		} SubID;
		STUFF *class_mat;
};

#ifdef DLL_VERSION
extern ulong	(*get_Experience_LEVEL)(ushort);
#else
extern "C" {
ulong	get_Experience_LEVEL(ushort);
}
#endif // DLL_VERSION

#endif // _SETTINGS_HPP_
