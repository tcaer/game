$input v_color0, v_texcoord0

#include "./common.sh"

SAMPLER2D(texx, 0);

void main() {
	gl_FragColor = texture2D(texx, v_texcoord0);
}
