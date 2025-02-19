#include "common.hlsli"

float4 main(p_bumped_new I, out float depth : SV_Depth) : SV_Target
{
    depth = 1.0f;
    return 0.0f;
}

