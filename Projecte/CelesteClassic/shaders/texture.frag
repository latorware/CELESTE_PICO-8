#version 330

uniform int gris; 
uniform vec4 color;
uniform sampler2D tex;


in vec2 texCoordFrag;
out vec4 outColor;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	vec4 texColor = texture(tex, texCoordFrag);
	if(texColor.a < 0.5f)
		discard;

	outColor = color * texColor;
	if (gris == 1)
	{
		float lineal = (outColor.x*0.299)+(outColor.y*0.587)+(outColor.z*0.114); 
		outColor = vec4(lineal, lineal, lineal, outColor.w); 
	}
}

