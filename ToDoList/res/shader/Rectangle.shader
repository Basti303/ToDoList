#shader vertex
#version 450 core
layout(location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
};

#shader fragment
#version 450 core
out vec4 FragColor;

uniform vec4 color;

void main()
{
	FragColor = color;
};