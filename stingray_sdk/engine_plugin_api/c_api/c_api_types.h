#pragma once

/*
	* These types mainly exist to simplify the otherwise ambiguous abstracted void pointers used by the ScriptApi.
	* They should be able to be casted to and treated the same way their respective plugin_foundation type is.
*/

/*
*	All functions declared as "unsigned find_x(name)" will return UINT_MAX when no index was found.
*/

#include "../plugin_api_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	typedef CApiStoryTeller* StoryTellerPtr;
	typedef CApiWorld* WorldPtr;
	typedef CApiLevel* LevelPtr;
	typedef CApiScatterSystem* ScatterSystemPtr;
	typedef CApiVectorField* VectorFieldPtr;
	typedef CApiCamera* CameraPtr;
	typedef CApiViewport* ViewportPtr;
	typedef CApiShadingEnvironment* ShadingEnvironmentPtr;
	typedef CApiActor* ActorPtr;
	typedef void* TerrainPtr;
	typedef CApiMover* MoverPtr;
	typedef CApiMaterial* MaterialPtr;
	typedef void* LanLobbyPtr;
	typedef void* LanLobbyBrowserPtr;
	typedef void* GameSessionPtr;
	typedef CApiUnitSynchronizer* UnitSynchronizerPtr;
	typedef CApiMesh* MeshPtr;
	typedef void* JointPtr;
	typedef void* LodObjectPtr;
	typedef CApiLight* LightPtr;
	typedef void* VehiclePtr;
	typedef void* ClothPtr;
	typedef CApiLineObject* LineObjectPtr;
	typedef CApiGui* GuiPtr;
	typedef CApiQuaternion* QuaternionPtr;
	typedef CApiWindow* WindowPtr;
	typedef CApiNavigationMesh* NavigationMeshPtr;
	typedef CApiVideoPlayer* VideoPlayerPtr;
	typedef CApiReplay* ReplayPtr;
	typedef CApiCallbackData32* CallbackData32Ptr;
	typedef CApiStreamSource* StreamSourcePtr;
	typedef CApiTimpaniWorldInterface* TimpaniWorldInterfacePtr;
	typedef CApiGuiThumbnail* GuiThumbnailPtr;
	typedef CApiCaptureBuffer* CApiCaptureBufferPtr;
	typedef CApiInputController* CApiInputControllerPtr;

	typedef CApiTransformComponent* TransformComponentPtr;
	typedef CApiMeshComponent* MeshComponentPtr;
	typedef CApiActorComponent* ActorComponentPtr;
	typedef CApiSceneGraphComponent* SceneGraphComponentPtr;
	typedef CApiAnimationBlenderComponent* AnimationBlenderComponentPtr;
	typedef CApiAnimationStateMachineComponent* AnimationStateMachineComponentPtr;
	typedef CApiDebugNameComponent* DebugNameComponentPtr;
	typedef CApiDataComponentPtr* DataComponentPtr;
	typedef CApiRenderDataComponent* RenderDataComponentPtr;
	typedef CApiTagComponent* TagComponentPtr;
	typedef CApiComponent* ComponentPtr;
	typedef CApiFlowComponent* FlowComponentPtr;
	typedef CApiUnitComponent* UnitComponentPtr;
	typedef CApiPhysicsWorld* PhysicsWorldPtr;

	typedef const CApiWorldConfig* ConstWorldConfigPtr;
	typedef const void* ConstConfigRootPtr;
	typedef const CApiMatrix4x4* ConstMatrix4x4Ptr;
	typedef const CApiVector2* ConstVector2Ptr;
	typedef const CApiVector3* ConstVector3Ptr;
	typedef const CApiVector4* ConstVector4Ptr;
	typedef const CApiLocalTransform* ConstLocalTransformPtr;
	typedef const CApiViewport* ConstViewportPtr;

	typedef const CApiShadingEnvironment* ConstShadingEnvironmentPtr;
	typedef const CApiWindow* ConstWindowPtr;
	typedef const CApiCamera* ConstCameraPtr;
	typedef const CApiWorld* ConstWorldPtr;
	typedef const CApiMaterial* ConstMaterialPtr;
	typedef const void* ConstRenderResourcePtr;
	typedef const void* ConstLanLobbyPtr;
	typedef const void* ConstLanLobbyBrowserPtr;
	typedef const CApiQuaternion* ConstQuaternionPtr;
	typedef const CApiLevel* ConstLevelPtr;
	typedef const CApiMesh* ConstMeshPtr;
	typedef const CApiNavigationMesh* ConstNavigationMeshPtr;
	typedef CApiMaterialData* MaterialDataPtr;

	typedef CApiUnitRef UnitRef;
	typedef unsigned ParticleRef;
	typedef unsigned GameObjectId;
	typedef uint64_t PeerId;
	typedef unsigned EntityRef;
	typedef CApiInstance Instance;
	typedef CApiInstanceId InstanceId;
	typedef CApiInstanceWithId InstanceWithId;
	typedef unsigned RaycastId;
	typedef unsigned SaveToken;
	typedef unsigned ScatterBrushId;
	typedef unsigned ScatterUnitId;
	typedef unsigned ScatterObserverId;

	struct WindowRectWrapper {
		int pos[4];
	};

	struct OOBBWrapper {
		float tm[16];
		float half_ext[3];
	};

	struct BoundingVolumeWrapper {
		CApiVector3 min;
		CApiVector3 max;
		float radius;
	};

	struct MoverFitsAtResult {
		int fits;
		CApiVector3 pos;
	};

	struct MoverSeparateResult {
		int is_colliding;
		int can_be_resolved;
		CApiVector3 position_after_resolving;
		ActorPtr collides_with; /* Can be nullptr even if is_colliding is true, not all collidables are actors. */
	};

	/*
		UINT_MAX represents a nil AnimationState value.
		Currently up to 32 states can be returned, use num_states to find out how many are.
	*/

	enum {MAX_ANIMATION_STATES = 32};
	struct AnimationStates {
		unsigned states[MAX_ANIMATION_STATES];
		unsigned num_states;
	};

	enum { MAX_ANIMATION_LAYER_SEEDS = 32 };
	struct AnimationLayerSeeds {
		unsigned seeds[MAX_ANIMATION_LAYER_SEEDS];
		unsigned num_seeds;
	};

	struct AnimationLayerInfo {
		float length;
		double t;
	};

	enum { MAX_ANIMATION_EVENT_PARAMETERS = 1 };
	enum { ANIMATION_EVENT_PERCENT_SYNC = 0 };

	struct AnimationEventParameters
	{
		unsigned n;
		unsigned keys[MAX_ANIMATION_EVENT_PARAMETERS];
		float values[MAX_ANIMATION_EVENT_PARAMETERS];
	};

	/*
	*	Specifies how units will be faded in/out when un-/spawned by the ScatterSystem
	*	POP - pop in place
	*	SLIDE_Z - slide in along object's z-axis
	*	SCALE - scale to full size
	*/
	enum ScatterFadeMethod {SCATTER_FADE_POP, SCATTER_FADE_SLIDE_Z, SCATTER_FADE_SCALE};

	/*
	*	Specifies how an animation should be blended with other animations.
	*	With BT_NORMAL the pose is lerped based on the blend strength.
	*	With BT_OFFSET the pose is applied as an offset.
	*/
	enum AnimationBlendType { ANIM_BT_NORMAL, ANIM_BT_OFFSET };

	enum WindowKeystrokes
	{
		WINDOW_KEYSTROKE_WINDOWS,
		WINDOW_KEYSTROKE_ALT_TAB,
		WINDOW_KEYSTROKE_ALT_ENTER,
		WINDOW_KEYSTROKE_ALT_F4,
	};

	/* Represents both the animation_root_mode and animation_bone_mode types since they are equal. */
	enum AnimationBoneRootMode
	{
		BRM_IGNORE					= 0,
		BRM_POSITION				= 1 << 0,
		BRM_ROTATION				= 1 << 1,
		BRM_SCALE					= 1 << 2,
		BRM_TRANSFORM				= BRM_POSITION | BRM_ROTATION | BRM_SCALE,
		BRM_POSITION_AND_ROTATION	= BRM_POSITION | BRM_ROTATION,
		BRM_POSITION_AND_SCALE		= BRM_POSITION | BRM_SCALE,
		BRM_ROTATION_AND_SCALE		= BRM_ROTATION | BRM_SCALE
	};

	/* Take note of the escape characters when reading. Example bone_names_list: "bone_hand_1\0bone_hand_2\0etc\0" */
	struct BoneNamesWrapper {
		const char* bone_names_list;
		unsigned num_bones;
	};

	enum RawInputEventType
	{
		BUTTON_PRESSED,
		BUTTON_RELEASED,

		AXIS_CHANGED,

		TOUCH_DOWN,
		TOUCH_UP,
		TOUCH_MOVE,
	};

	enum RawInputEventController
	{
		KEYBOARD,
		MOUSE,
		TOUCH_PANEL,
		GAMEPAD,
		PS4PAD
	};

	struct RawInputEventWrapper {
		CApiVector3 delta_value;
		unsigned char id;
		unsigned char controller_index;
		unsigned char type; /* RawInputEventType */
		unsigned char controller; /* RawInputEventController */
	};

	enum RemoteEventType {
		REMOTE_EVENT_TYPE_KEY_DOWN = 0,
		REMOTE_EVENT_TYPE_KEY_UP = 1,
		REMOTE_EVENT_TYPE_KEY_PRESS = 2,
		REMOTE_EVENT_TYPE_MOUSE_DOWN = 3,
		REMOTE_EVENT_TYPE_MOUSE_UP = 4,
		REMOTE_EVENT_TYPE_MOUSE_MOVE = 5,
		REMOTE_EVENT_TYPE_MOUSE_WHEEL = 6
	};

	struct RemoteEventWrapper {
		unsigned input_type;
		int button_id;
		int x;
		int y;
		float dx;
		float dy;
		float dz;
		int key_code;
	};

	enum InputCategory
	{
		INPUT_CATEGORY_GAMEPAD = 0,
		INPUT_CATEGORY_TOUCH_PANEL = 1,
		INPUT_CATEGORY_MOUSE = 2,
		INPUT_CATEGORY_KEYBOARD = 3,
		INPUT_CATEGORY_POINTER = 4
	};

	enum Keystroke
	{
		KS_CHAR_ARROW_LEFT = 1,
		KS_CHAR_ARROW_RIGHT = 2,
		KS_CHAR_ARROW_UP = 3,
		KS_CHAR_ARROW_DOWN = 4,
		KS_CHAR_INSERT = 5,
		KS_CHAR_HOME = 6,
		KS_CHAR_END = 7,
		KS_CHAR_BACKSPACE = 8,
		KS_CHAR_TAB = 9,
		KS_CHAR_PG_UP = 11,
		KS_CHAR_PG_DOWN = 12,
		KS_CHAR_ENTER = 13,
		KS_CHAR_F1 = 14,
		KS_CHAR_F2 = 15,
		KS_CHAR_F3 = 16,
		KS_CHAR_F4 = 17,
		KS_CHAR_F5 = 18,
		KS_CHAR_F6 = 19,
		KS_CHAR_F7 = 20,
		KS_CHAR_F8 = 21,
		KS_CHAR_F9 = 22,
		KS_CHAR_F10 = 23, // magical, does not work
		KS_CHAR_F11 = 24,
		KS_CHAR_F12 = 25,
		KS_CHAR_DELETE = 26,
		KS_CHAR_ESCAPE = 27
	};

	struct TouchPinchGesture
	{
		unsigned began_last_frame;
		unsigned ended_last_frame;
		struct CApiVector2 location;
		float scale;
		float scale_per_second;
	};

	struct TouchRotationGesture
	{
		unsigned began_last_frame;
		unsigned ended_last_frame;
		struct CApiVector2 location;
		float accumulated_rotation_rad;
		float rotation_per_second_rad;
	};

	enum SwipeDirection { SWIPE_DIRECTION_NONE = -1, SWIPE_DIRECTION_RIGHT = 1, SWIPE_DIRECTION_LEFT = 2, SWIPE_DIRECTION_UP = 4, SWIPE_DIRECTION_DOWN = 8};

	enum TouchEdge { TOUCH_EDGE_NONE = 0, TOUCH_EDGE_TOP = 0x01, TOUCH_EDGE_BOTTOM = 0x02, TOUCH_EDGE_LEFT = 0x04, TOUCH_EDGE_RIGHT = 0x08 };

	enum { MAX_TOUCH_CONTACTS = 64 };

	enum DeadZoneMode { DEADZONE_MODE_CIRCULAR, DEADZONE_MODE_INDEPENDENT, DEADZONE_MODE_RAW };

	struct DeadZoneSetting {
		enum DeadZoneMode mode;
		float size;
	};

	struct RumbleParameters
	{
		float frequency;		// Default 0.0f	(frequency = 1.0f / period)
		float offset;			// Default 0.0f
		float attack_level;		// Default 1.0f
		float sustain_level;	// Default 1.0f
		float attack;			// Default 0.0f
		float release;			// Default 0.0f
		float sustain;			// Default 0.0f
		float decay;			// Default 0.0f
	};

	struct SocketAddressWrapper {
		char address_and_port[22];
	};

	enum RPCParameterType
	{
		RPC_PARAM_BOOL_TYPE,
		RPC_PARAM_INT_TYPE,
		RPC_PARAM_FLOAT_TYPE,
		RPC_PARAM_VECTOR3_TYPE,
		RPC_PARAM_QUATERNION_TYPE,
		RPC_PARAM_STRING_TYPE,
		RPC_PARAM_IDSTRING32_TYPE,
		RPC_PARAM_IDSTRING64_TYPE,
		RPC_PARAM_RESOURCE_ID_TYPE,
		RPC_PARAM_UINT_64_TYPE,
		RPC_PARAM_ARRAY_BEGINS,
		RPC_PARAM_ARRAY_ENDS
	};

	struct RPCMessageParameter
	{
		enum RPCParameterType type;
		void* data_pointer;
	};

	struct GameObjectField
	{
		unsigned field_name_id32;
		enum RPCParameterType type;
		void* data_pointer;
	};

	typedef void (*game_object_callback_function) (int id, uint64_t sending_peer);

	/*	These member functions will receive callbacks from the engine during NetworkCApi's update_receive.
		You're expected to assign all the function pointers before passing the struct. */
	struct RPCCallback {
		game_object_callback_function	game_object_created;
		game_object_callback_function	game_object_destroyed;
		game_object_callback_function	game_object_migrated_to_me;
		game_object_callback_function	game_object_migrated_away;
		void (*game_object_sync_done)	(uint64_t sending_peer);
		void (*game_session_disconnect)	(uint64_t sending_peer);
		/* Note: all data passed in the RPCMessageParameter array are temporary allocated and will get destroyed after the callback. */
		void (*custom_callback)			(uint64_t sending_peer, unsigned message_id32, struct RPCMessageParameter* parameter_array, unsigned num_parameters);
	};

	struct EntityInstanceId
	{
		EntityRef entity;
		InstanceId instance_id;
	};

	/* Entity property type. */
	enum EntityPropertyType
	{
		ENTITY_PROPERTY_TYPE_NIL,
		ENTITY_PROPERTY_TYPE_BOOL,
		ENTITY_PROPERTY_TYPE_FLOAT,
		ENTITY_PROPERTY_TYPE_STRING,
		ENTITY_PROPERTY_TYPE_FLOAT_ARRAY
	};

	/* The combined hash of the individual hashes of the separate key strings. */
	typedef unsigned EntityPropertyKey;

	struct EntityPropertyValueFloatArray
	{
		float *a;
		unsigned n;
	};

	struct EntityPropertyValue
	{
		enum EntityPropertyType type;
		union {
			unsigned b;
			float f;
			const char *s;
			struct EntityPropertyValueFloatArray a;
		};
	};

	enum RaycastType	{ RAY_TYPE_ANY, RAY_TYPE_CLOSEST, RAY_TYPE_ALL };
	enum ActorTemplate	{ ACTOR_T_STATIC = 1, ACTOR_T_DYNAMIC, ACTOR_T_BOTH };
	enum OverlapShape	{ OVERLAP_SPHERE, OVERLAP_AABB, OVERLAP_OOBB, OVERLAP_CAPSULE };

	struct CollisionHit
	{
		CApiVector3 position;
		CApiVector3 normal;
		float		distance;
		ActorPtr	actor;
	};

	enum SaveSystemError
	{
		SAVEDATA_ERROR_ERROR_MISSING,		/* The specified file does not exist. */
		SAVEDATA_ERROR_INVALID_FILENAME,	/* The specified filename is invalid. */
		SAVEDATA_ERROR_IO_ERROR,			/* A disk error occurred. */
		SAVEDATA_ERROR_BROKEN,				/* The saved data is corrupted. */
		SAVEDATA_ERROR_UNSUPPORTED_VERSION,	/* The data was saved using an old version, and cannot be loaded by this version. */
		SAVEDATA_ERROR_INVALID_TOKEN,		/* The specified token could not be found. */
		SAVEDATA_ERROR_NOT_DONE,			/* The specified token has not finished loading yet. */
		SAVEDATA_ERROR_NONE					/* No error occured. */
	};

	struct SaveSystemProgress
	{
		int is_done;
		float progress;
		enum SaveSystemError error_code;
	};

	enum SaveParameterType
	{
		SAVE_PARAM_TABLE_BEGIN,
		SAVE_PARAM_TABLE_END,
		SAVE_PARAM_NUMBER_FLOAT,
		SAVE_PARAM_STRING,
		SAVE_PARAM_BOOL,
		SAVE_PARAM_VECTOR3,
		SAVE_PARAM_VECTOR3_BOX,
		SAVE_PARAM_MATRIX4X4,
		SAVE_PARAM_MATRIX4X4_BOX,
		SAVE_PARAM_NUMBER_DOUBLE
	};

	struct SaveParameter
	{
		enum SaveParameterType type;
		void* data_pointer;
	};

	/* Note: You still have to close the token to free the data. */
	typedef void (*save_system_data_callback) (struct SaveParameter* parameter_array, unsigned num_parameters);

	/* Access the different null-terminated strings via s[i], i must be less than num_strings. The s must be pre-allocated by the user. */
	struct MultipleStringsBuffer
	{
		unsigned	num_strings;
		char**		s;
	};

	enum TimeStepPolicyType
	{
		TSP_FRAME_RATE,
		TSP_THROTTLE_FRAME_RATE,
		TSP_SMOOTHING,
		TSP_DEBT_PAYBACK,
		TSP_EXTERNAL_STEP_RANGE,
		TSP_EXTERNAL_MULTIPLIER,
		TSP_SYSTEM_STEP_RANGE,
		TSP_CLEAR_HISTORY,
		TSP_JUMP
	};

	struct TimeStepPolicyWrapper
	{
		enum TimeStepPolicyType type;

		union {
			int frames;
			int fps;
			float multiplier;
			float time;
			float min;
		};
		union {
			int outliers;
			float max;
		};
		union {
			float lerp;
		};
	};

	struct WindowOpenParameter
	{
		int x;
		int y;
		int width;
		int height;
		const char* optional_title;
		WindowPtr optional_parent;
		int explicit_resize;
		int main_window;
		int visible;
		int pass_key_events_to_parent;
		int layered;
		int frameless;
	};

	struct Vector3ArrayWrapper
	{
		int count;
		CApiVector3* v;
	};

	enum ReplayRecordMode
	{
		REPLAY_RECORD_MODE_DISABLED,
		REPLAY_RECORD_MODE_TRANSFORM,
		REPLAY_RECORD_MODE_SCENE_GRAPH
	};

	struct MaterialDecalDrawer {
		unsigned material_id32;
		unsigned drawer_id32;
	};

	struct TextExtentsResult
	{
		struct CApiVector2 min;
		struct CApiVector2 max;
		struct CApiVector2 caret;
	};

	enum VideoCApi_TextureLayout { VIDEO_TEXTURE_LAYOUT_UNKNOWN = 0, VIDEO_TEXTURE_LAYOUT_YUV2, VIDEO_TEXTURE_LAYOUT_RGBA };

	enum WorldCApi_OrphanedParticlePolicy
	{
		WA_OPP_DESTROY_ORPHAN,
		WA_OPP_STOP_SPAWNING_ORPHAN,
		WA_OPP_UNLINK_ORPHAN
	};

	enum UnitCApi_VisibilityContext
	{
		UVC_DEFAULT = 1,
		UVC_SHADOW_CASTER = 2,
		UVC_OCCLUDER = 4,
		UVC_ALL = 255
	};

	enum DynamicScriptDataType
	{
		D_DATA_NIL_TYPE,
		D_DATA_BOOLEAN_TYPE,
		D_DATA_NUMBER_TYPE,
		D_DATA_STRING_TYPE,
		D_DATA_CUSTOM_TVECTOR2 = 100,
		D_DATA_CUSTOM_TVECTOR3,
		D_DATA_CUSTOM_TVECTOR4,
		D_DATA_CUSTOM_TMATRIX4X4,
		D_DATA_CUSTOM_TUNITREFERENCE,
		D_DATA_CUSTOM_TPOINTER,
		D_DATA_CUSTOM_TLUAREF, /* Custom Lua reference is currently not supported via the C Api's DynamicScriptData. */
		D_DATA_CUSTOM_ID64
	};

	typedef struct DynamicScriptDataItem {
		const void *pointer;
		enum DynamicScriptDataType type;
		unsigned size;
	} DynamicScriptDataItem;

	enum CameraProjectionType {
		CAMERA_PROJ_ORTHOGRAPHIC,
		CAMERA_PROJ_PERSPECTIVE
	};

	enum ApplicationImageFormats {
		APPLICATION_RAW,
		APPLICATION_PNG,
		APPLICATION_DDS
	};
	enum CameraMode {
		CAMERA_MODE_MONO,
		CAMERA_MODE_STEREO
	};

	enum FlowType {
		FLOW_NIL_TYPE = 0,
		FLOW_UNIT_TYPE = 1,
		FLOW_ACTOR_TYPE = 2,
		FLOW_MOVER_TYPE = 3,
		FLOW_VECTOR3_TYPE = 4,
		FLOW_FLOAT_TYPE = 5,
		FLOW_BOOL_TYPE = 6,
		FLOW_STRING_TYPE = 7,
		FLOW_ID64_TYPE = 8,
		FLOW_QUATERNION_TYPE = 9,
		FLOW_UNSIGNED_TYPE = 10,
		FLOW_CAMERA_TYPE = 11,
		FLOW_LIGHT_TYPE = 12,
		FLOW_MESH_TYPE = 13,
		FLOW_MATERIAL_TYPE = 14,
		FLOW_ID32_TYPE = 15,
		FLOW_ENTITY_TYPE = 16
	};

#ifdef __cplusplus
};
#endif
