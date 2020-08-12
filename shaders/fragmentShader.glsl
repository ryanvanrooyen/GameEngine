
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
   // color = vec4(0.0, 1.0, 0.0, 1.0);
   color = u_Color;
}
