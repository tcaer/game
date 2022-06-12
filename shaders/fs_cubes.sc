$input v_color0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "./common.sh"

vec4 vec4_splat(float _x) { return vec4(_x, _x, _x, _x); }

void main()
{
	gl_FragColor = v_color0;
}
