#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct GameSessionCApi_BoolPeerWrapper {
	int bool_value;
	PeerId peer;
};

struct GameSessionCApi
{
	int		(*in_session_self) (GameSessionPtr);
	int		(*in_session) (GameSessionPtr, PeerId);

	PeerId	(*host) (GameSessionPtr);
	void	(*make_host) (GameSessionPtr);
	void	(*shutdown_host) (GameSessionPtr);
	int		(*host_error_occured) (GameSessionPtr);
	void	(*migrate_host) (GameSessionPtr);
	void	(*disconnect_from_host) (GameSessionPtr);

	void	 (*add_peer) (GameSessionPtr, uint64_t);
	PeerId	 (*peer) (GameSessionPtr, unsigned index);
	unsigned (*num_peers) (GameSessionPtr);
	int		 (*peer_is_synchronizing) (GameSessionPtr, unsigned index);

	UnitSynchronizerPtr (*unit_synchronizer) (GameSessionPtr);

	GameObjectId (*create_game_object_with_default_values) (GameSessionPtr, unsigned unit_type_id32);
	GameObjectId (*create_game_object) (GameSessionPtr, unsigned unit_type_id32, struct GameObjectField* field_array, unsigned num_elements);
	void		 (*destroy_game_object) (GameSessionPtr, GameObjectId);
	int			 (*game_object_exists) (GameSessionPtr, GameObjectId);

	void	(*remove_peer) (GameSessionPtr, PeerId, game_object_callback_function game_object_destroyed);
	void	(*leave) (GameSessionPtr);

	struct GameSessionCApi_BoolPeerWrapper (*broken_connection) (GameSessionPtr);
	struct GameSessionCApi_BoolPeerWrapper (*wants_to_leave) (GameSessionPtr);

	void			(*migrate_game_object) (GameSessionPtr, GameObjectId, PeerId new_owner, struct RPCCallback*);
	unsigned		(*num_game_objects) (GameSessionPtr);
	GameObjectId	(*game_object_id_from_index) (GameSessionPtr, unsigned);
	PeerId			(*game_object_owner) (GameSessionPtr, GameObjectId);
	int				(*game_object_owner_is_self) (GameSessionPtr, GameObjectId);

	void					(*set_game_object_fields) (GameSessionPtr, GameObjectId, struct GameObjectField* field_array, unsigned num_elements);
	struct GameObjectField	(*game_object_field) (GameSessionPtr, GameObjectId, unsigned field_name_id32);
};

#ifdef __cplusplus
}
#endif
