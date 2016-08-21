#include <Dream/Dream.hpp>

#include <dirent.h>

extern const char *OpCode_Gen[];

opcodes::~opcodes()
{
	for (int i=0; i < Max_OpCode_List; i++) {
		while (list[i].Unknow) {
			opcode_unk_t *tmp_OPC_Unk = list[i].Unknow;
			list[i].Unknow = list[i].Unknow->next;
			delete tmp_OPC_Unk->name;
			delete tmp_OPC_Unk;
		}
	}
}

opcodes::opcodes()
{
	size = 0;
	for (int j=0; j < OPC_MAX; j++)
		Send[j] = NULL;
	for (int i=0; i < Max_OpCode_List; i++) {
		list[i].version = 0.0;
		list[i].Unknow = NULL;
		list[i].detect = -1;
		for (int j=0; j < OPC_MAX; j++)
			list[i].Send[j] = -1;
		for (int j=0; j < PACKET_MAX_SIZE; j++) {
			list[i].OpName[j] = NULL;
			list[i].Recv[j] = NULL;
		}
	}
}

void opcodes::Set_Recv(const char *opcode_n, void* (*opcode_f)(const void**))
{
	for (int i=0; i < Max_OpCode_List; i++) {
		if (list[i].version) {
			int j=0;
			bool loop_me = true;
			while (loop_me && j < PACKET_MAX_SIZE) {
				if (list[i].OpName[j] && !strcmp(list[i].OpName[j], opcode_n)) {
					loop_me = false;
				} else
					j++;
			}
			if (j < PACKET_MAX_SIZE) {
				if (!strcmp(opcode_n, "C_LOGIN_ARBITER"))
					list[i].detect = j;
					list[i].Recv[j] = (void*(*)(player*, packet*)) opcode_f;
			}
		}
	}
}

void opcodes::Set_Send(OpCode_Enum Op_ID, void* (*OpCode_f)(const void**))
{
	
	Send[Op_ID] = OpCode_f;
}

void* opcodes::Recv(player* player_l, packet* packet_l)
{
	if (player_l->Op_GID < 0 || !list[player_l->Op_GID].Recv[packet_l->id])
		return NULL;
	return list[player_l->Op_GID].Recv[packet_l->id](player_l, packet_l);
}

const char* opcodes::Recv_name(player* player_l, packet* packet_l)
{
	if (player_l->Op_GID < 0 || !list[player_l->Op_GID].OpName[packet_l->id]) {
		DEBUG("Unknow OpCode %i in \"%.04f\"\n", packet_l->id, list[player_l->Op_GID].version);
		return "???";
	}
	return list[player_l->Op_GID].OpName[packet_l->id];
}

const char* opcodes::Send_name(packet* packet_l)
{
	return OpCode_Gen[packet_l->Op_ID];
}

int opcodes::Get_GID(packet* packet_l)
{
	int GID = -1;
	for (int i=0; GID < 0 && i < Max_OpCode_List; i++) {
		if (list[i].version && list[i].detect >= 0 && list[i].detect == packet_l->id) 
			GID = i;
	}
	if (GID < 0)
		DEBUG("OpCode Version Detector :: Can't find OpCode for this client version ! (%i)\n", packet_l->id);
	return GID;
}

bool opcodes::load()
{
	FILE *fp;
	struct dirent *dirp;
	DIR *pdir;
	if ((pdir = opendir(Sharun->Settings.Dirs.OpCodes.c_str()))) {
		while ((dirp = readdir(pdir))) {
			if ((strcmp(dirp->d_name, ".")) && (strcmp(dirp->d_name, "..")) && (strcmp(dirp->d_name, ".")) && (!dir_exist(dirp->d_name)) && ((!strcmp(strrchr(dirp->d_name, '.'), ".txt")) || (!strcmp(strrchr(dirp->d_name, '.'), ".TXT")))) {
				std::string filename = Sharun->Settings.Dirs.OpCodes + DSlash + dirp->d_name;
				fopen_s(&fp, filename.c_str(), "r");
				if (fp) {
						char version[10];
//	list[size].version
					memset(version, 0, 10);
					strncpy_s(version, 10, dirp->d_name, strrchr(dirp->d_name, '.') - dirp->d_name);
					for (uint i=0; i < strlen(version); i++) {
						if ( version[i] == '_' )
							version[i] = '.';
						if ( version[i] != '.' && (version[i] < '0' || version[i] > '9') ) {
							char tmp[10];
							strcpy_s(tmp, 10, version);
							uint j = i+1;
							while (j < strlen(tmp) + 1 && tmp[j] && (tmp[j] < '0' || tmp[j] > '9'))
								j++;
							strcpy_s(version + i, 10 - i, tmp + j);
						}
					}
					list[size].version = atof(version) / 100;
					DEBUG("%s%.04f", size ? ", " : "Loading OpCode Files : ", list[size].version);
					char tmpS[100];
					uint tmpI;
					while (fp && !feof(fp)) {
						tmpS[0] = 0;
						tmpI = 0;
#ifdef _MSC_VER
						fscanf_s(fp, " %s = %i", tmpS, 100, &tmpI);
#else
						fscanf(fp, " %s = %i", tmpS, &tmpI);
#endif
						if (strlen(tmpS)) {
							int i=0;
							while (i < OPC_MAX && OpCode_Gen[i] && strcmp(OpCode_Gen[i], tmpS))
								i++;
							if (i < OPC_MAX) {
								list[size].OpName[tmpI] = OpCode_Gen[i];
								list[size].Send[i] = tmpI;
							} else {
								opcode_unk_t * tmp_OPC_Unk;
								tmp_OPC_Unk = list[size].Unknow;
								if (tmp_OPC_Unk) {
									while (tmp_OPC_Unk->next)
										tmp_OPC_Unk = tmp_OPC_Unk->next;
									tmp_OPC_Unk->next = new opcode_unk_t;
									tmp_OPC_Unk = tmp_OPC_Unk->next;
								} else
									tmp_OPC_Unk = list[size].Unknow = new opcode_unk_t;
								tmp_OPC_Unk->next = NULL;
								tmp_OPC_Unk->func = NULL;
								tmp_OPC_Unk->name = strdump(tmpS);
								tmp_OPC_Unk->code = tmpI;
							}
						}
					}
					size++;
				}
			}
		}
		closedir(pdir);
	}
	if (size)
		DEBUG(".\n");
	DEBUG("%s (%i) :: OpCodes loaded (%i files). ~\n", __FILE__, __LINE__, size);
	if (size)
		return true;
	return false;
}
