uniform sampler2D u_tex_ground;
uniform sampler2D u_tex_velocities;

uniform float u_distortion;
uniform float u_dt;
uniform float u_grid_res;
uniform float u_time;

in vec2 v_tex;

out float frag_col;

void main()
{
    vec2  vel   = texelFetch(u_tex_velocities, ivec2(gl_FragCoord.xy), 0).xy;
    float vel_v = length(vel);
    vec2  dir = normalize(vel);
    vec2  amp0 = dir * (2.0+vel_v);
    vec2  amp = amp0;
    // vec2 amp_max1 = vec2(1.0e-1);
    // vec2 amp_max2 = vec2(-1.0e-1);
    // amp.xy = min(amp_max1.xy, amp0.xy);
    // amp.xy = max(amp_max2.xy, amp0.xy);
    // vec2 arg = dir*(gl_FragCoord.xy-vec2(1024.0, -512.0)) - u_time*10;
    vec2 arg0 = 0.0 * vec2(u_time);
    vec2 arg  = 0.01*dir*gl_FragCoord.xy;
    vec2 pos  = gl_FragCoord.xy - u_grid_res * u_dt * u_distortion *
                (amp * sin(arg) - (vel+0.1)*sin(arg0));

    // Neighbour indices
    vec4 n;
    n.xy = floor(pos-0.5)+0.5;
    n.zw = n.xy+1.0;
        
    // Neighbour values
    float v_tl = texelFetch(u_tex_ground, ivec2(n.xy), 0).x; // top left
    float v_tr = texelFetch(u_tex_ground, ivec2(n.zy), 0).x; // top right
    float v_bl = texelFetch(u_tex_ground, ivec2(n.xw), 0).x; // bottom left
    float v_br = texelFetch(u_tex_ground, ivec2(n.zw), 0).x; // bottom right

    vec2 f = pos - n.xy;

    frag_col = mix(mix(v_tl, v_tr, f.x), mix(v_bl, v_br, f.x), f.y);
}
