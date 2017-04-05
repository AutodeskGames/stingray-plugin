
template<typename ValueType>
__forceinline ValueType *allocate_plugin_array(uint32_t size, Allocator &a)
{
	if (size == 0)
		return nullptr;
	Array<ValueType> *container = MAKE_NEW(a, Array<ValueType>, size, a);
	return &(*container)[0];
}

__forceinline void to_plugin(const char *&dest, const DynamicString &source)
{
	dest = !source.empty() ? source.c_str() : nullptr;
}
__forceinline void from_plugin(DynamicString &dest, const char *source)
{
	dest = source ? source : "";
}

__forceinline void to_plugin(SDB_StringList &dest, const Vector<DynamicString> &source, Allocator &a)
{
	dest.size = source.size();
	dest.data = dest.size > 0 ? allocate_plugin_array<const char *>(dest.size, a) : nullptr;
	for (uint32_t i=0; i < dest.size; ++i) {
		to_plugin(dest.data[i], source[i]);
	}
}
__forceinline void from_plugin(Vector<DynamicString> &dest, const SDB_StringList &source)
{
	dest.resize(source.size);
	for (uint32_t i=0; i < source.size; ++i) {
		from_plugin(dest[i], source.data[i]);
	}
}

template<typename DestContainerType, typename DestDataType, typename SourceContainerType>
__forceinline void vector_to_plugin_internal(uint32_t &dest_size, DestContainerType &dest_data, DestDataType *dummy_value, SourceContainerType &source, Allocator &a)
{
	dest_size = source.size();
	dest_data = dest_size > 0 ? allocate_plugin_array<DestDataType>(dest_size, a) : nullptr;
	for (uint32_t i=0; i < dest_size; ++i) {
		to_plugin(dest_data[i], source[i], a);
	}
}
template<typename DestContainerType, typename SourceContainerType>
__forceinline void vector_to_plugin(uint32_t &dest_size, DestContainerType &dest_data, SourceContainerType &source, Allocator &a)
{
	vector_to_plugin_internal(dest_size, dest_data, dest_data, source, a);
}
template<typename DestContainerType, typename SourceContainerType>
__forceinline void vector_from_plugin(uint32_t source_size, DestContainerType &dest, SourceContainerType &source_data)
{
	dest.resize(source_size);
	for (uint32_t i=0; i < source_size; ++i) {
		from_plugin(dest[i], source_data[i]);
	}
}

template<typename T>
__forceinline void array_to_plugin(uint32_t &dest_size, T *&dest_data, const Array<T> &source, Allocator &a)
{
	dest_size = source.size();
	if (dest_size > 0) {
		dest_data = allocate_plugin_array<T>(dest_size, a);
		memcpy(dest_data, &source[0], dest_size * sizeof(T));
	} else {
		dest_data = nullptr;
	}
}
template<typename T>
__forceinline void array_from_plugin(const uint32_t source_size, Array<T> &dest, const T *source_data)
{
	dest.resize(source_size);
	if (source_size > 0) {
		memcpy(&dest[0], source_data, source_size * sizeof(T));
	}
}

template<typename ExternalContainerType, typename InternalContainerType, typename ValueType>
__forceinline void hashmap_to_plugin_internal(ExternalContainerType &dest, InternalContainerType &source, ValueType *dummy_value, Allocator &a)
{
	dest.size = source.size();
	dest.data = dest.size > 0 ? allocate_plugin_array<ValueType>(dest.size, a) : nullptr;
	uint32_t i=0;
	for (const auto &it : source) {
		to_plugin(dest.data[i++], it.second, it.first.c_str(), a);
	}
}

template<typename ExternalContainerType, typename InternalContainerType>
__forceinline void hashmap_to_plugin(ExternalContainerType &dest, InternalContainerType &source, Allocator &a)
{
	hashmap_to_plugin_internal(dest, source, dest.data, a);
}

template<typename InternalContainerType, typename ExternalContainerType>
__forceinline void hashmap_from_plugin(InternalContainerType &dest, ExternalContainerType &source)
{
	dest.reserve(source.size);
	for (uint32_t i=0; i < source.size; ++i) {
		auto &dest_item = dest[source.data[i].name];
		from_plugin(dest_item, source.data[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

__forceinline void to_plugin(SDB_Channel &dest, const Stream::Channel &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	dest.index = source.index;
	dest.type = (SDB_ChannelType)source.type;
}
__forceinline void from_plugin(Stream::Channel &dest, const SDB_Channel &source)
{
	from_plugin(dest.name, source.name);
	dest.index = source.index;
	dest.type = (ChannelType)source.type;
}

__forceinline void to_plugin(SDB_Stream &dest, const Stream &source, Allocator &a)
{
	vector_to_plugin(dest.n_channels, dest.channels, source.channels, a);
	dest.size = source.size;
	dest.stride = source.stride;
	dest.n_data = source.data.size();
	dest.data = dest.n_data > 0 ? (uint8_t *)&source.data[0] : nullptr;
}
__forceinline void from_plugin(Stream &dest, const SDB_Stream &source)
{
	vector_from_plugin(source.n_channels, dest.channels, source.channels);
	dest.size = source.size;
	dest.stride = source.stride;
	dest.data.resize(source.n_data);
	if (source.n_data > 0) {
		memcpy(&dest.data[0], source.data, source.n_data);
	}
}

__forceinline void to_plugin(SDB_Node &dest, const Node &source, const char *name, Allocator &a)
{
	dest.name = name;
	to_plugin(dest.parent, source.parent);
	to_plugin(dest.children, source.children, a);
	memcpy(dest.local, &source.local, sizeof(Matrix4x4));
	to_plugin(dest.geometries, source.geometries, a);
	dest.viewport_visible = source.viewport_visible;
	dest.has_local_mirroring = source.has_local_mirroring;
}
__forceinline void from_plugin(Node &dest, const SDB_Node &source)
{
	from_plugin(dest.parent, source.parent);
	from_plugin(dest.children, source.children);
	memcpy(&dest.local, &source.local, sizeof(Matrix4x4));
	from_plugin(dest.geometries, source.geometries);
	dest.viewport_visible = source.viewport_visible == 1;
	dest.has_local_mirroring = source.has_local_mirroring == 1;
}

__forceinline void to_plugin(SDB_IndicesStream &dest, const Indices::Stream &source, Allocator &a)
{
	array_to_plugin(dest.n_indices, dest.indices, source.indices, a);
}
__forceinline void from_plugin(Indices::Stream &dest, const SDB_IndicesStream &source)
{
	array_from_plugin(source.n_indices, dest.indices, source.indices);
}

__forceinline void to_plugin(SDB_Indices &dest, const Indices &source, Allocator &a)
{
	dest.n_indices = source.n_indices;
	vector_to_plugin(dest.n_streams, dest.streams, source.streams, a);
}
__forceinline void from_plugin(Indices &dest, const SDB_Indices &source)
{
	dest.n_indices = source.n_indices;
	vector_from_plugin(source.n_streams, dest.streams, source.streams);
}

__forceinline void to_plugin(SDB_Joint &dest, const Skin::Joint &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	memcpy(dest.inv_bind_matrix, &source.inv_bind_matrix, sizeof(Matrix4x4));
}
__forceinline void from_plugin(Skin::Joint &dest, const SDB_Joint &source)
{
	from_plugin(dest.name, source.name);
	memcpy(&dest.inv_bind_matrix, source.inv_bind_matrix, sizeof(Matrix4x4));
}

__forceinline void to_plugin(SDB_Skin &dest, const Skin &source, const char *name, Allocator &a)
{
	dest.name = name;
	dest.max_affecting_bones = source.max_affecting_bones;
	vector_to_plugin(dest.n_joints, dest.joints, source.joints, a);
}
__forceinline void from_plugin(Skin &dest, const SDB_Skin &source)
{
	dest.max_affecting_bones = source.max_affecting_bones;
	vector_from_plugin(source.n_joints, dest.joints, source.joints);
}

__forceinline void to_plugin(SDB_GeometryInstance &dest, const GeometryInstance &source, const char *name, Allocator &a)
{
	dest.name = name;
	to_plugin(dest.geometry, source.geometry);
	to_plugin(dest.materials, source.materials, a);
}
__forceinline void from_plugin(GeometryInstance &dest, const SDB_GeometryInstance &source)
{
	from_plugin(dest.geometry, source.geometry);
	from_plugin(dest.materials, source.materials);
}

__forceinline void to_plugin(SDB_GeometryMaterial &dest, const Geometry::Material &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	array_to_plugin(dest.n_primitives, dest.primitives, source.primitives, a);
}
__forceinline void from_plugin(Geometry::Material &dest, const SDB_GeometryMaterial &source)
{
	from_plugin(dest.name, source.name);
	array_from_plugin(source.n_primitives, dest.primitives, source.primitives);
}

__forceinline void to_plugin(SDB_GeometryBlendShapeTarget &dest, const Geometry::BlendShapeTarget &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	vector_to_plugin(dest.n_streams, dest.streams, source.streams, a);
}
__forceinline void from_plugin(Geometry::BlendShapeTarget &dest, const SDB_GeometryBlendShapeTarget &source)
{
	from_plugin(dest.name, source.name);
	vector_from_plugin(source.n_streams, dest.streams, source.streams);
}

__forceinline void to_plugin(SDB_Geometry &dest, const Geometry &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	vector_to_plugin(dest.n_streams, dest.streams, source.streams, a);
	to_plugin(dest.indices, source.indices, a);
	to_plugin(dest.skin, source.skin);
	vector_to_plugin(dest.n_materials, dest.materials, source.materials, a);
	array_to_plugin(dest.n_primitive_smoothing, dest.primitive_smoothing, source.primitive_smoothing, a);
	vector_to_plugin(dest.n_blend_shape_targets, dest.blend_shape_targets, source.blend_shape_targets, a);
	dest.shadow_caster = source.shadow_caster;
	array_to_plugin(dest.n_vertex_position_remapping, dest.vertex_position_remapping, source.vertex_position_remapping, a);
	array_to_plugin(dest.n_vertex_normal_remapping, dest.vertex_normal_remapping, source.vertex_normal_remapping, a);
}
__forceinline void from_plugin(Geometry &dest, const SDB_Geometry &source)
{
	from_plugin(dest.name, source.name);
	vector_from_plugin(source.n_streams, dest.streams, source.streams);
	from_plugin(dest.indices, source.indices);
	from_plugin(dest.skin, source.skin);
	vector_from_plugin(source.n_materials, dest.materials, source.materials);
	array_from_plugin(source.n_primitive_smoothing, dest.primitive_smoothing, source.primitive_smoothing);
	vector_from_plugin(source.n_blend_shape_targets, dest.blend_shape_targets, source.blend_shape_targets);
	dest.shadow_caster = source.shadow_caster == 1;
	array_from_plugin(source.n_vertex_position_remapping, dest.vertex_position_remapping, source.vertex_position_remapping);
	array_from_plugin(source.n_vertex_normal_remapping, dest.vertex_normal_remapping, source.vertex_normal_remapping);
}

__forceinline void to_plugin(SDB_Light &dest, const Light &source, const char *name, Allocator &a)
{
	dest.name = name;
	dest.type = (SDB_LightDefinitionType)source.type;
	memcpy(dest.color, source.color, 4 * sizeof(float));
	dest.falloff_start = source.falloff_start;
	dest.falloff_end = source.falloff_end;
	dest.spot_angle_start = source.spot_angle_start;
	dest.spot_angle_end = source.spot_angle_end;
	dest.cast_shadow = source.cast_shadow;
}
__forceinline void from_plugin(Light &dest, const SDB_Light &source)
{
	dest.type = (Light::DefinitionType)source.type;
	memcpy(dest.color, source.color, 4 * sizeof(float));
	dest.falloff_start = source.falloff_start;
	dest.falloff_end = source.falloff_end;
	dest.spot_angle_start = source.spot_angle_start;
	dest.spot_angle_end = source.spot_angle_end;
	dest.cast_shadow = source.cast_shadow == 1;
}

__forceinline void to_plugin(SDB_Camera &dest, const Camera &source, const char *name, Allocator &a)
{
	dest.name = name;
	dest.type = (SDB_CameraDefinitionType)source.type;
	dest.near_plane = source.near_plane;
	dest.far_plane = source.far_plane;
	dest.vertical_fov = source.vertical_fov;
}
__forceinline void from_plugin(Camera &dest, const SDB_Camera &source)
{
	dest.type = (Camera::DefinitionType)source.type;
	dest.near_plane = source.near_plane;
	dest.far_plane = source.far_plane;
	dest.vertical_fov = source.vertical_fov;
}

__forceinline void to_plugin(SDB_Animation &dest, const Animation &source, Allocator &a)
{
	to_plugin(dest.node, source.node);
	to_plugin(dest.parameter, source.parameter);
	array_to_plugin(dest.n_times, dest.times, source.times, a);
	to_plugin(dest.data, source.data, a);
}
__forceinline void from_plugin(Animation &dest, const SDB_Animation &source)
{
	from_plugin(dest.node, source.node);
	from_plugin(dest.parameter, source.parameter);
	array_from_plugin(source.n_times, dest.times, source.times);
	from_plugin(dest.data, source.data);
}

__forceinline void to_plugin(SDB_AnimationTake &dest, const AnimationTake &source, const char *name, Allocator &a)
{
	dest.name = name;
	dest.start_time = source.start_time;
	dest.end_time = source.end_time;
	dest.nb_samples = source.nb_samples;
	vector_to_plugin(dest.n_animations, dest.animations, source.animations, a);
}
__forceinline void from_plugin(AnimationTake &dest, const SDB_AnimationTake &source)
{
	dest.start_time = source.start_time;
	dest.end_time = source.end_time;
	dest.nb_samples = source.nb_samples;
	vector_from_plugin(source.n_animations, dest.animations, source.animations);
}

__forceinline void to_plugin(SDB_SurfaceMaterialProperty &dest, const SurfaceMaterial::Property &source, Allocator &a)
{
	to_plugin(dest.name, source.name);
	dest.n_integers = source.n_integers;
	dest.integer = source.integer;
	dest.n_floats  = source.n_floats;
	memcpy(dest.floats, source.floats, 4 * sizeof(float));
	to_plugin(dest.value_string, source.value_string);
	to_plugin(dest.textures, source.textures, a);
}
__forceinline void from_plugin(SurfaceMaterial::Property &dest, const SDB_SurfaceMaterialProperty &source)
{
	from_plugin(dest.name, source.name);
	dest.n_integers = source.n_integers;
	dest.integer = source.integer;
	dest.n_floats  = source.n_floats;
	memcpy(dest.floats, source.floats, 4 * sizeof(float));
	from_plugin(dest.value_string, source.value_string);
	from_plugin(dest.textures, source.textures);
}

__forceinline void to_plugin(SDB_SurfaceMaterial &dest, const SurfaceMaterial &source, const char *name, Allocator &a)
{
	dest.name = name;
	dest.type = (SDB_SurfaceMaterialDefinitionType)source.type;
	vector_to_plugin(dest.properties.size, dest.properties.data, source.properties, a);
	dest.nb_influences = source.nb_influences;
}
__forceinline void from_plugin(SurfaceMaterial &dest, const SDB_SurfaceMaterial &source)
{
	dest.type = (SurfaceMaterial::DefinitionType)source.type;
	vector_from_plugin(source.properties.size, dest.properties, source.properties.data);
	dest.nb_influences = source.nb_influences;
}

__forceinline void to_plugin(SDB_Texture &dest, const Texture &source, const char *name, Allocator &a)
{
	dest.name = name;
	to_plugin(dest.file_path, source.file_path);
	to_plugin(dest.relative_path, source.relative_path);
	dest.embedded = source.embedded;
	dest.uv_offset[0] = source.uv_offset.x;
	dest.uv_offset[1] = source.uv_offset.y;
	dest.uv_scale[0] = source.uv_scale.x;
	dest.uv_scale[1] = source.uv_scale.y;
	dest.uv_rotation = source.uv_rotation;
}
__forceinline void from_plugin(Texture &dest, const SDB_Texture &source)
{
	from_plugin(dest.file_path, source.file_path);
	from_plugin(dest.relative_path, source.relative_path);
	dest.embedded = source.embedded == 1;
	dest.uv_offset.x = source.uv_offset[0];
	dest.uv_offset.y = source.uv_offset[1];
	dest.uv_scale.x = source.uv_scale[0];
	dest.uv_scale.y = source.uv_scale[1];
	dest.uv_rotation = source.uv_rotation;
}

__forceinline void to_plugin(SDB_LevelOfDetailStep &dest, const LevelOfDetail::Step &source, Allocator &a)
{
	to_plugin(dest.nodes, source.nodes, a);
	dest.min_pct = source.min_pct;
	dest.max_pct = source.max_pct;
}
__forceinline void from_plugin(LevelOfDetail::Step &dest, const SDB_LevelOfDetailStep &source)
{
	from_plugin(dest.nodes, source.nodes);
	dest.min_pct = source.min_pct;
	dest.max_pct = source.max_pct;
}

__forceinline void to_plugin(SDB_LevelOfDetail &dest, const LevelOfDetail &source, const char *name, Allocator &a)
{
	dest.name = name;
	to_plugin(dest.orientation_node, source.orientation_node);
	to_plugin(dest.bounding_volume, source.bounding_volume);
	dest.requires_predefined_pct = source.requires_predefined_pct;
	vector_to_plugin(dest.n_steps, dest.steps, source.steps, a);
}
__forceinline void from_plugin(LevelOfDetail &dest, const SDB_LevelOfDetail &source)
{
	from_plugin(dest.orientation_node, source.orientation_node);
	from_plugin(dest.bounding_volume, source.bounding_volume);
	dest.requires_predefined_pct = source.requires_predefined_pct == 1;
	vector_from_plugin(source.n_steps, dest.steps, source.steps);
}

__forceinline void to_plugin(SDB_SceneImportOptions &dest, const SceneImportOptions &source)
{
	dest.combine_meshes = source.combine_meshes;
	dest.combine_meshes_by_material = source.combine_meshes_by_material;
	dest.reverse_forward_axis = source.reverse_forward_axis;
	dest.skip_create_extra_root = source.skip_create_extra_root;
	dest.skip_textures = source.skip_textures;
	dest.skip_lights = source.skip_lights;
	dest.skip_cameras = source.skip_cameras;
	dest.create_missing_uvs = source.create_missing_uvs;
	dest.tangents = (SDB_SceneImportTangents)source.tangents;
}
__forceinline void from_plugin(SceneImportOptions &dest, const SDB_SceneImportOptions &source)
{
	dest.combine_meshes = source.combine_meshes == 1;
	dest.combine_meshes_by_material = source.combine_meshes_by_material == 1;
	dest.reverse_forward_axis = source.reverse_forward_axis == 1;
	dest.skip_create_extra_root = source.skip_create_extra_root == 1;
	dest.skip_textures = source.skip_textures == 1;
	dest.skip_lights = source.skip_lights == 1;
	dest.skip_cameras = source.skip_cameras == 1;
	dest.create_missing_uvs = source.create_missing_uvs == 1;
	dest.tangents = (SceneImportOptions::TangentsOption)source.tangents;
}

__forceinline void to_plugin(SDB_Properties &dest, const SceneDatabase::Properties &source, Allocator &a)
{
	dest.size = source.size();
	dest.data = dest.size > 0 ? allocate_plugin_array<SDB_Property>(dest.size, a) : nullptr;
	uint32_t i=0;
	for (const auto &it : source) {
		auto &dest_item = dest.data[i++];
		to_plugin(dest_item.first, it.first);
		to_plugin(dest_item.second, it.second);
	}
}
__forceinline void from_plugin(SceneDatabase::Properties &dest, const SDB_Properties &source)
{
	dest.reserve(source.size);
	for (uint32_t i=0; i < source.size; ++i) {
		from_plugin(dest[source.data[i].first], source.data[i].second);
	}
}

__forceinline void to_plugin(SDB_SceneDatabase &dest, const SceneDatabase &source, Allocator &a)
{
	hashmap_to_plugin(dest.nodes, source.nodes, a);
	to_plugin(dest.roots, source.roots, a);
	hashmap_to_plugin(dest.geometry_instances, source.geometry_instances, a);
	vector_to_plugin(dest.geometries.size, dest.geometries.data, source.geometries, a);
	hashmap_to_plugin(dest.lights, source.lights, a);
	hashmap_to_plugin(dest.cameras, source.cameras, a);
	hashmap_to_plugin(dest.skins, source.skins, a);
	hashmap_to_plugin(dest.materials, source.materials, a);
	hashmap_to_plugin(dest.textures, source.textures, a);
	hashmap_to_plugin(dest.lods, source.lods, a);
	hashmap_to_plugin(dest.anim_takes, source.anim_takes, a);
	to_plugin(dest.source_path, source.source_path);
	to_plugin(dest.import_options, source.import_options);
	to_plugin(dest.properties, source.properties, a);
}
__forceinline void from_plugin(SceneDatabase &dest, const SDB_SceneDatabase &source)
{
	hashmap_from_plugin(dest.nodes, source.nodes);
	from_plugin(dest.roots, source.roots);
	hashmap_from_plugin(dest.geometry_instances, source.geometry_instances);
	vector_from_plugin(source.geometries.size, dest.geometries, source.geometries.data);
	hashmap_from_plugin(dest.lights, source.lights);
	hashmap_from_plugin(dest.cameras, source.cameras);
	hashmap_from_plugin(dest.skins, source.skins);
	hashmap_from_plugin(dest.materials, source.materials);
	hashmap_from_plugin(dest.textures, source.textures);
	hashmap_from_plugin(dest.lods, source.lods);
	hashmap_from_plugin(dest.anim_takes, source.anim_takes);
	from_plugin(dest.source_path, source.source_path);
	from_plugin(dest.import_options, source.import_options);
	from_plugin(dest.properties, source.properties);
}
