namespace stingray_plugin_foundation {

__forceinline uint32_t channel_size(ChannelType type) {
	switch (type) {
		case CT_FLOAT1: return 1*sizeof(float);
		case CT_FLOAT2: return 2*sizeof(float);
		case CT_FLOAT3: return 3*sizeof(float);
		case CT_FLOAT4: return 4*sizeof(float);
		case CT_MATRIX4x4: return 16*sizeof(float);
		case CT_QUATERNION: return 4*sizeof(float);
		case CT_FLOAT3_CMP_11_11_10: return sizeof(unsigned);
		case CT_HALF1: return 1*sizeof(short);
		case CT_HALF2: return 2*sizeof(short);
		case CT_HALF3: return 3*sizeof(short);
		case CT_HALF4: return 4*sizeof(short);
		case CT_UBYTE4: return sizeof(unsigned);
		case CT_SHORT1: return 1*sizeof(short);
		case CT_SHORT2: return 2*sizeof(short);
		case CT_SHORT3: return 3*sizeof(short);
		case CT_SHORT4: return 4*sizeof(short);
		default: return 0;
	}

	return 0;
}

__forceinline const char *Parameter_LocalTransform()
{
	return "matrix";
}

__forceinline const char *Channel_LocalTransform()
{
	return "local_tm";
}

__forceinline const char *Channel_BlendShapeWeight()
{
	return "blend_shape_channel_weight";
}

}
