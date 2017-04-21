#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum LanCApi_LanLobbyState { LAN_LB_CREATING, LAN_LB_JOINING, LAN_LB_JOINED, LAN_LB_FAILED };

struct LanCApi
{
	void		(*init_client) (uint64_t network_config_id64, unsigned port, uint64_t peer_id);
	void		(*shutdown_client) ();

	LanLobbyPtr (*create_lobby) (unsigned port, unsigned max_members);
	LanLobbyPtr (*join_lobby) (const char* server_address, unsigned port);
	void		(*leave_lobby) (LanLobbyPtr);
	enum LanCApi_LanLobbyState (*state) (LanLobbyPtr);
	void		(*set_data) (LanLobbyPtr, const char* key, const char* value);
	const char* (*data) (ConstLanLobbyPtr, const char* key);

	void	(*set_game_session_host) (LanLobbyPtr, uint64_t peer_id64);
	void	(*set_game_session_host_to_none) (LanLobbyPtr);
	uint64_t	(*game_session_host) (ConstLanLobbyPtr);
	uint64_t	(*lobby_host) (ConstLanLobbyPtr);

	unsigned	(*num_members) (ConstLanLobbyPtr);
	uint64_t		(*member) (ConstLanLobbyPtr, unsigned index);
	void		(*kick) (LanLobbyPtr, uint64_t peer_id64);

	void		(*set_member_data) (LanLobbyPtr, const char* key, const char* value);
	const char* (*own_data) (LanLobbyPtr, const char* key);
	const char* (*member_data) (LanLobbyPtr, uint64_t peer_id64, const char* key);

	LanLobbyBrowserPtr	(*lobby_browser) ();
	struct SocketAddressWrapper	(*lobby_address) (ConstLanLobbyBrowserPtr, unsigned index);
	unsigned	(*num_lobbies) (ConstLanLobbyBrowserPtr);
	const char*	(*lobby_data) (LanLobbyBrowserPtr, unsigned index, const char* key);
	void		(*refresh) (LanLobbyBrowserPtr, unsigned port);
	int			(*is_refreshing) (ConstLanLobbyBrowserPtr);
};

#ifdef __cplusplus
}
#endif

