#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#ifdef DLL_VERSION
extern void	(*World_Spam)(player*);
extern void	(*World_Exit)(player*);
extern void	(*World_Chat)(player*, CHAT_TYPE, const char*, const char*, const char16_t*);
extern void	(*World_PlayerMove)(player*, ushort);
extern void	(*World_PlayerSocial)(player*, bool, int);
extern void	(*World_PlayerMount)(player*, bool, uint);
extern void	(*World_PlayerSkill)(player*, player*, uint, ushort, float*, float*);
#else
extern "C" {
void	World_Spam(player*);
void	World_Exit(player*);
void	World_Chat(player*, CHAT_TYPE, const char*, const char*, const char16_t*);
void	World_PlayerMove(player*, ushort);
void	World_PlayerSocial(player*, bool, int);
void	World_PlayerMount(player*, bool, uint);
void	World_PlayerSkill(player*, player*, uint, ushort, float*, float*);
}
#endif // DLL_VERSION

#endif // _WORLD_HPP_
