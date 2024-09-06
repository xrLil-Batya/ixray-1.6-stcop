#include "common.hlsli"
#include "sload.hlsli"

void main(p_shadow _I, out IXrayGbufferPack O)
{
    IXrayGbuffer G;
    p_bumped_new I;

    GbufferUnpack(_I.tc0.xy, _I.hpos.xy, G);
	
	clip(G.SnowMask - 0.00001f);
	clip(0.9999f - G.Depth);
	
    I.position = float4(G.Point.xyz, 1.0f);
	I.snow_mask = G.SnowMask;

    float3 P = mul(m_invV, I.position);
    float3 N = normalize(mul(m_invV, G.Normal.xyz));

    float3 T = float3(-1.0f, 0.0f, 0.0f);
    T = normalize(T - dot(T, N) * N);
    float3 B = cross(N, T);

    float3x3 xform = mul((float3x3)m_V, float3x3(
        T.x, B.x, N.x,
        T.y, B.y, N.y,
        T.z, B.z, N.z
		)
    );

    I.tcdh.xy = P.xz * 0.2f;
    I.tcdh.zw = 0.5f;

    I.M1 = xform[0];
    I.M2 = xform[1];
    I.M3 = xform[2];

    I.hpos_curr = I.hpos_old = I.hpos = _I.hpos;
    IXrayMaterial M;

    M.Sun = I.tcdh.w;
    M.Hemi = I.tcdh.z;

    M.Depth = G.Point.z;
    M.Point = G.Point.xyz;

    SloadNew(I, M);

	M.Normal = mul(xform, M.Normal);
	M.Normal = normalize(M.Normal);

    O.Velocity = 0.0f;
    GbufferPack(O, M);
	
	O.Color.w = I.snow_mask;
	O.Normal.w = I.snow_mask;
	O.Material.w = I.snow_mask;
}

