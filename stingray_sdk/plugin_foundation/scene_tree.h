#pragma once

#include "matrix4x4.h"
#include "allocator.h"
#include "hash_function.h"
#include "hash_function_string.h"
#include "vector.h"
#include "hash_map.h"
#include "id_string.h"

namespace stingray_plugin_foundation {


enum ChannelType {
	CT_FLOAT1 = 0,
	CT_FLOAT2,
	CT_FLOAT3,
	CT_FLOAT4,
	CT_MATRIX4x4,
	CT_QUATERNION,
	CT_FLOAT3_CMP_11_11_10,
	CT_HALF1,
	CT_HALF2,
	CT_HALF3,
	CT_HALF4,
	CT_UBYTE4,
	CT_SHORT1,
	CT_SHORT2,
	CT_SHORT3,
	CT_SHORT4,
	CT_COUNT
};

uint32_t channel_size(ChannelType type);
const char *Parameter_LocalTransform();
const char *Channel_LocalTransform();
const char *Channel_BlendShapeWeight();

// General container for storing data
struct Stream {
	ALLOCATOR_AWARE;
	Stream(Allocator &a) : data(a), channels(a), size(0), stride(0) { }

	// Structure describing a single data channel in the stream
	struct Channel {
		ALLOCATOR_AWARE;
		Channel(Allocator &a) : name(a) { }

		// Semantic name of channel
		DynamicString name;

		// Semantic index of channel
		unsigned index;

		// Data contained within channel
		ChannelType type;
	};

	// List of channels describing the contents of this stream
	Vector<Channel> channels;

	// Number of elements in stream
	unsigned size;

	// Stride in bytes between two elements
	unsigned stride;

	// Stream data
	Array<char> data;
};

bool operator==(const Stream::Channel &lhs, const Stream::Channel &rhs);
bool operator!=(const Stream::Channel &lhs, const Stream::Channel &rhs);

typedef Vector<Stream> Streams;

// Structure that represents a scene node
struct Node {
	ALLOCATOR_AWARE;
	Node(Allocator &a) : parent(a), children(a), geometries(a), viewport_visible(true), has_local_mirroring(false) { }


	// Name of parent (can be empty)
	DynamicString parent;

	// List with names of this nodes children
	Vector<DynamicString> children;

	// Local transformation matrix
	Matrix4x4 local;

	// List with names of geometries attached to this node
	Vector<DynamicString> geometries;

	// Initial visibility preference (overridden by renderables section of .unit)
	bool viewport_visible;

	// We keep this information here to avoid computing the local transform determinant
	// every time we want to know whether the transform is mirrored or not.
	// NOTE: we neither serialize this information but compute it from local once read.
	bool has_local_mirroring;

	void swap(Node &o) {
		parent.swap(o.parent);
		children.swap(o.children);
		std::swap(local, o.local);
		geometries.swap(o.geometries);
		std::swap(viewport_visible, o.viewport_visible);
		std::swap(has_local_mirroring, o.has_local_mirroring);
	}
};

// Structure that represents mesh topology
struct Indices {
	ALLOCATOR_AWARE;
	Indices(Allocator &a) : streams(a), n_indices(0), type(TRIANGLE_LIST) { }

	// Number of indices
	unsigned n_indices;

	// Primitive type - currently we are only handling TRIANGLE_LIST
	enum PrimitiveType { TRIANGLE_LIST };
	PrimitiveType type;

	struct Stream {
		ALLOCATOR_AWARE;
		Stream(Allocator &a) : indices(a) { }

		Array<unsigned> indices;
	};
	// List of indices for each stream in a mesh
	Vector<Stream> streams;
};

// Structure describing a Skin modifier
struct Skin {
	ALLOCATOR_AWARE;
	Skin(Allocator &a) : joints(a), max_affecting_bones(0) { }

	// Describes a skin joint
	struct Joint {
		ALLOCATOR_AWARE;
		Joint(Allocator &a) : name(a) { }

		// Name of joint
		DynamicString name;
		// Inverse bind matrix for joint
		Matrix4x4 inv_bind_matrix;
	};

	// Formerly "Bind shape matrix for skin".
	// This information is actually stored by cluster in FBX and there is no such
	// global bind matrix anymore there. Nevertheless, it is used in BSI exporters
	// so we keep it for backward-compatibility there and remove it from anywhere
	// else, namely the engine.
#ifdef BSI_PLUGIN
	Matrix4x4 bind_matrix;
#endif

	// Maximum number of influences
	unsigned max_affecting_bones;

	// Skin joints
	Vector<Joint> joints;
};

// Structure describing a mesh instance
struct GeometryInstance {
	ALLOCATOR_AWARE;
	GeometryInstance(Allocator &a) : geometry(a), materials(a) { }

	DynamicString geometry;
	Vector<DynamicString> materials;
};

// Structure describing a mesh
struct Geometry {
	ALLOCATOR_AWARE;
	Geometry(Allocator &a) : name(a), streams(a), indices(a), materials(a), skin(a), primitive_smoothing(a), blend_shape_targets(a), shadow_caster(true), vertex_position_remapping(a), vertex_normal_remapping(a) { }

	DynamicString name;

	// List of vertex data streams
	Streams streams;

	// Indices of mesh
	Indices indices;

	// Name of skin if mesh is skinned
	DynamicString skin;

	// Structure describing a mesh material
	struct Material {
		ALLOCATOR_AWARE;
		Material(Allocator &a) : name(a), primitives(a) { }

		// Material name
		DynamicString name;

		// List of primitive indices that the material is assigned to
		Array<unsigned> primitives;
	};

	// List of materials assigned to this mesh
	Vector<Material> materials;

	// Per primitive smoothing group information
	Array<unsigned> primitive_smoothing;

	// Structure describing a blend shape target
	struct BlendShapeTarget {
		ALLOCATOR_AWARE;
		BlendShapeTarget(Allocator &a) : name(a), streams(a) { }

		// Name of blend_shape target
		DynamicString name;

		// Blend Shape Target vertex data streams
		Streams streams;
	};

	// BlendShape targets
	Vector<BlendShapeTarget> blend_shape_targets;

	// Initial shadow preference (overridden by renderables section of .unit)
	bool shadow_caster;

	Array<unsigned> vertex_position_remapping;
	Array<unsigned> vertex_normal_remapping;
};

// Structure describing a light
struct Light {

	enum DefinitionType { // same enum values as found in: source\engine\engine\scene\light.h
		OMNI = 0,
		SPOT = 1,
		BOX = 2,
		DIRECTIONAL = 3
	};
	DefinitionType type;

	float color[4];

	float falloff_start; // units are meters
	float falloff_end;   // units are meters

	float spot_angle_start; // radians
	float spot_angle_end;   // radians

	bool cast_shadow;
};

// Structure describing a camera
struct Camera {

	enum DefinitionType { // same enum values as found in source\engine\engine\scene\camera.h
		ORTHOGRAPHIC,
		PERSPECTIVE
	};
	DefinitionType type;

	float near_plane; // units are meters
	float far_plane;  // units are meters
	float vertical_fov; // units are radians
};

// Structure describing a animation.
// there are 4 types of animation curve :
// NODE_LOCAL_TRANSFORM   : in this case, parameter == "local_tm". The animation has 1 channel of CT_MATRIX4x4 of name "matrix".
// NODE_PROPERTY          : in this case, parameter is the name of the animated property. The animation has up to 4 channels of CT_FLOAT1 named "0","1","2","3"
// NODE_BLENDSHAPECHANNEL : in this case, parameter is the name of the blend shape channel. The animation has 1 channel of CT_FLOAT1 named "weight"
// MATERIAL_PROPERTY      : in this case, parameter is the name of the animated property. The animation has up to 4 channels of CT_FLOAT1 named "0","1","2","3"
struct Animation {
	ALLOCATOR_AWARE;

	Animation(Allocator &a) : node(a), parameter(a), times(a), data(a) { }

	bool is_local_transform_anim() const { return data.channels.size() == 1 && data.channels[0].type == CT_MATRIX4x4 && parameter == Parameter_LocalTransform() && data.channels[0].name == Channel_LocalTransform(); }

	// Name of node this animation affects, or name of the material
	DynamicString node;

	// Name of affected parameter
	DynamicString parameter;

	// List of time keys
	Array<float> times;

	// Data stream containing the animation data (1:1 mapping with 'times' indices)
	Stream data;
};

// Structure describing an animation take
struct AnimationTake {
	ALLOCATOR_AWARE;

	AnimationTake(Allocator &a) : animations(a), start_time(0), end_time(0), nb_samples(0) { }

	// infos
	float start_time;
	float end_time;
	unsigned nb_samples;

	// animations for each node
	Vector<Animation> animations;
};

// Structure describing a surface material
struct SurfaceMaterial {
	ALLOCATOR_AWARE;

	SurfaceMaterial(Allocator& a) : type(LAMBERT), properties(a), nb_influences(0) { }

	// Type of definition
	enum DefinitionType {
		LAMBERT = 0,
		PHONG   = 1,
		SHADER  = 2
	};
	DefinitionType type;

	// Next version, we should consider adding a Datatype attribute so we know what kind of data is stored
	// by the property. This will help representing shaders parameters since they can be: bool, ints, enums,
	// floats, etc...
	struct Property {
		ALLOCATOR_AWARE;

		Property(Allocator& a) : n_integers(0), n_floats(0), name(a), value_string(a), textures(a) { }

		unsigned n_integers;
		int integer;
		unsigned n_floats;
		float floats[4];

		DynamicString name;
		DynamicString value_string;

		// reference to textures attached to this property
		Vector<DynamicString> textures;
	};

	typedef Vector<Property> Properties;
	Properties properties;

	// number of bones influences [0..4]
	unsigned nb_influences;
};

// Structure describing a texture
struct Texture {
	ALLOCATOR_AWARE;

	Texture(Allocator& a) : file_path(a), relative_path(a), embedded(false), uv_rotation(0)
	{
		uv_offset.x = uv_offset.y = 0;
		uv_scale.x = uv_scale.y = 1;
	}

	DynamicString file_path;
	DynamicString relative_path;

	// was embedded in source .fbx file
	bool embedded;

	Vector2 uv_offset;
	Vector2 uv_scale;
	float uv_rotation;
};

// Structure describing a Level of Details
struct LevelOfDetail {
	ALLOCATOR_AWARE;

	LevelOfDetail(Allocator& a) : orientation_node(a), bounding_volume(a), requires_predefined_pct(0), steps(a) { }

	DynamicString orientation_node;
	DynamicString bounding_volume;
	bool          requires_predefined_pct;

	struct Step {
		ALLOCATOR_AWARE;

		Step(Allocator& a) : nodes(a), min_pct(0.0f), max_pct(1.0f) {}

		Vector<DynamicString> nodes;
		float min_pct;
		float max_pct;
	};

	Vector<Step> steps;
};


// Structure describing how a scene is interpreted when importing

struct SceneImportOptions {
	SceneImportOptions() :
		combine_meshes(false),
		combine_meshes_by_material(false),
		reverse_forward_axis(false),
		skip_create_extra_root(false),
		skip_textures(false),
		skip_lights(false),
		skip_cameras(false),
		create_missing_uvs(false),
		bake_scale(false),
		tangents(TANGENTS_IMPORT)
	{ }

	enum TangentsOption {TANGENTS_IMPORT, TANGENTS_MIKKTSPACE};

	bool combine_meshes;
	bool combine_meshes_by_material;
	bool reverse_forward_axis;
	bool skip_create_extra_root;
	bool skip_textures;
	bool skip_lights;
	bool skip_cameras;
	bool create_missing_uvs;
	bool bake_scale;
	TangentsOption tangents;
};

// Structure describing a scene
struct SceneDatabase {
	SceneDatabase(Allocator &a) : nodes(a), roots(a), geometry_instances(a), geometries(a), lights(a), cameras(a), skins(a), materials(a), textures(a), lods(a), anim_takes(a), source_path(a), properties(a), geometry_entries(a) {  }
	Allocator &allocator() const {return nodes.allocator();}

	typedef HashMap<DynamicString, Node, string_hash> Nodes;
	Nodes nodes;
	Vector<DynamicString> roots;

	typedef HashMap<DynamicString, GeometryInstance, string_hash> GeometryInstances;
	GeometryInstances geometry_instances;

	typedef Vector<Geometry> Geometries;
	Geometries geometries;

	typedef HashMap<DynamicString, Light, string_hash> Lights;
	Lights lights;

	typedef HashMap<DynamicString, Camera, string_hash> Cameras;
	Cameras cameras;

	typedef HashMap<DynamicString, Skin, string_hash> Skins;
	Skins skins;

	typedef HashMap<DynamicString, SurfaceMaterial, string_hash> Materials;
	Materials materials;

	typedef HashMap<DynamicString, Texture, string_hash> Textures;
	Textures textures;

	typedef HashMap<DynamicString, LevelOfDetail, string_hash> Lods;
	Lods lods;

	typedef HashMap<DynamicString, AnimationTake, string_hash> AnimTakes;
	AnimTakes anim_takes;

	DynamicString source_path;

	SceneImportOptions import_options;

	typedef HashMap<DynamicString, DynamicString, string_hash> Properties;
	Properties properties;

	//////////////////////////////////////////////////////////////////////////
	typedef HashMap<IdString32, unsigned, idstring_hash> GeometryEntries;
	GeometryEntries geometry_entries;

	Geometry *find_geometry(const char *name) {
		const IdString32 id(name);
		auto it = geometry_entries.find(id);
		return it != geometry_entries.end() ? &geometries[it->second] : nullptr;
	}

	Geometry &add_geometry(const char *name) {
		const IdString32 id(name);
		geometry_entries.insert(id, geometries.size());

		Geometry &geom = geometries.extend();
		geom.name = name;
		return geom;
	}
};


}

#include "scene_tree.inl"
