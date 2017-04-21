#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif
enum NetworkCApi_LogLevel
{
	NET_LOG_SILENT, NET_LOG_WARNINGS, NET_LOG_MESSAGES, NET_LOG_SPEW
};

struct NetworkCApi
{
	GameSessionPtr	(*create_game_session) ();
	GameSessionPtr	(*game_session) ();
	void			(*shutdown_game_session) ();
	PeerId			(*peer_self) ();

	void	(*update_receive) (float dt, struct RPCCallback* callback_functions);
	void	(*update_transmit) ();
	void	(*send_rpc) (unsigned message_name_id32, PeerId peer, struct RPCMessageParameter* parameter_array, unsigned num_parameters);

	int		(*fatal_error_occured) ();
	void	(*write_dump_tag) (const char* msg);
	void	(*set_log_level) (enum NetworkCApi_LogLevel);
};

#ifdef __cplusplus
}
#endif

