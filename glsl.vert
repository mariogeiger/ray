#version 130
in vec2 vertex;
uniform float aspect;
uniform float anglevalue; // angle / 2 == arctan(1 / anglevalue)
uniform mat3 nview;
uniform mat4 view;
out vec3 first_ray;

void main(void)
{
    first_ray = nview * vec3(vertex.x * aspect, vertex.y, -anglevalue);
    gl_Position = vec4(vertex, 0.0, 1.0);
}
