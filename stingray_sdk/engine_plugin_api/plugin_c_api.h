#pragma once

#include "c_api/c_api_input.h"
#include "c_api/c_api_world.h"
#include "c_api/c_api_application.h"
#include "c_api/c_api_unit.h"
#include "c_api/c_api_camera.h"
#include "c_api/c_api_material.h"
#include "c_api/c_api_lan.h"
#include "c_api/c_api_network.h"
#include "c_api/c_api_game_session.h"
#include "c_api/c_api_unit_synchronizer.h"
#include "c_api/c_api_level.h"
#include "c_api/c_api_utilities.h"
#include "c_api/c_api_psn.h"
#include "c_api/c_api_dynamic_script_data.h"
#include "c_api/c_api_entity.h"
#include "c_api/c_api_line_object.h"
#include "c_api/c_api_gui.h"
#include "c_api/c_api_physics_world.h"
#include "c_api/c_api_actor.h"
#include "c_api/c_api_mover.h"
#include "c_api/c_api_save_system.h"
#include "c_api/c_api_viewport.h"
#include "c_api/c_api_mesh.h"
#include "c_api/c_api_ps4.h"
#include "c_api/c_api_ps4_ime_dialog.h"
#include "c_api/c_api_ps4_msg_dialog.h"
#include "c_api/c_api_ps4_error_dialog.h"
#include "c_api/c_api_ps4_np_commerce_dialog.h"
#include "c_api/c_api_window.h"


#ifdef __cplusplus
extern "C" {
#endif

struct ScriptApi
{
	struct InputCApi *Input;
	struct WorldCApi* World;
	struct ApplicationCApi* Application;
	struct UnitCApi* Unit;
	struct CameraCApi* Camera;
	struct MaterialCApi* Material;
	struct LanCApi* Lan;
	struct NetworkCApi* Network;
	struct GameSessionCApi* GameSession;
	struct UnitSynchronizerCApi* UnitSynchronizer;
	struct LevelCApi* Level;
	struct UtilitiesCApi* Utilities;
	struct PsnCApi* Psn;
	struct DynamicScriptDataCApi* DynamicScriptData;
	struct EntityCApi* Entity;
	struct LineObjectCApi* LineObject;
	struct GuiCApi* Gui;
	struct PhysicsWorldCApi* PhysicsWorld;
	struct ActorCApi* Actor;
	struct MoverCApi* Mover;
	struct SaveSystemCApi* SaveSystem;
	struct ViewportCApi* Viewport;
	struct MeshCApi* Mesh;
	struct Ps4CApi* Ps4;
	struct Ps4ImeDialogCApi* Ps4ImeDialog;
	struct Ps4MsgDialogCApi* Ps4MsgDialog;
	struct Ps4ErrorDialogCApi* Ps4ErrorDialog;
	struct Ps4NpCommerceDialogCApi* Ps4NpCommerceDialog;
	struct WindowCApi* Window;
};

#ifdef __cplusplus
}
#endif
