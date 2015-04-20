#version 130

struct material {
    float phong_factor; // between 0 and 1
    vec3 ambiant;
    vec3 diffuse;

    // eta == 0 -> no refraction, only relfection
    float eta; // index inside the material, behind the normal direction
};

struct sphere {
    vec3 center;
    float radius;
    material mat;
};

struct plane {
    vec3 point;
    vec3 normal;
    vec3 width;
    vec3 height;
    material mat;
};

struct ray {
    float power;
    vec3 origin;
    vec3 direction;
};

in vec3 first_ray; // direction du rayon qui part de camera
uniform vec3 light; // position de la lumire
uniform sphere spheres[4];
uniform plane planes[6];
uniform samplerCube cubemap;
uniform sampler2D tex;
uniform mat4 view;
out vec4 pixelColor;

bool next_intersection(inout vec3 origin, in vec3 direction, out vec3 normal, out material mat, out vec2 texture);
bool light_intersection(in vec3 origin, in vec3 direction, out vec3 normal, out material mat);

void fresnel();

const float fuzzy = 5e-4;

#include MAIN

// retourne la distance minimale strictement positive
bool line_sphere_intersection(in vec3 origin, in vec3 direction, in sphere s, out float dist)
{
    vec3 x = origin - s.center;
    float a = dot(direction, direction);
    float b = 2.0 * dot(direction, x);
    float c = dot(x, x) - s.radius * s.radius;
    float delta = b * b - 4.0 * a * c;

    if (delta < 0.0)
        return false;
    if (c < 0.0) {
        // in the sphere
        dist = (-b + sqrt(delta)) / (2.0 * a);
    } else {
        // out of the sphere
        dist = (-b - sqrt(delta)) / (2.0 * a);
    }
    return dist > 0.0;
}

// retourne la distance minimale strictement positive
bool line_plane_intersection(in vec3 origin, in vec3 direction, in plane p, out float dist, out vec2 tx)
{
    vec3 h = cross(direction, p.height);
    float a = dot(p.width, h);
    if (a == 0.0) return false;
    float f = 1.0 / a;
    vec3 s = origin - p.point;
    tx.x = f * dot(s, h);
    if (tx.x < 0.0 || tx.x > 1.0) return false;
    vec3 q = cross(s, p.width);
    tx.y = f * dot(direction, q);
    if (tx.y < 0.0 || tx.y > 1.0) return false;
    dist = f * dot(p.height, q);
    if (dist <= 0.0) return false;
    return true;
}

bool next_intersection(inout vec3 origin, in vec3 direction, out vec3 normal, out material mat, out vec2 texture)
{
    float d;
    float dmin = 1e38;

    int ii = -1;
    for (int i = 0; i < 4; ++i) {
        //if (spheres[i].radius == 0.0)
        //break;

        if (line_sphere_intersection(origin, direction, spheres[i], d)) {
            if (d < dmin) {
                dmin = d;
                ii = i;
            }
        }
    }

    int jj = -1;
    for (int j = 0; j < 6; ++j) {
        //if (planes[j].mat.eta < 0.0)
        //break;

        vec2 tx;
        if (line_plane_intersection(origin, direction, planes[j], d, tx)) {
            if (d < dmin) {
                dmin = d;
                jj = j;
                texture = tx;
            }
        }
    }

    if (jj != -1) {
        origin += direction * dmin;
        normal = planes[jj].normal;
        mat = planes[jj].mat;
        return true;
    } else if (ii != -1) {
        origin += direction * dmin;
        normal = (origin - spheres[ii].center) / spheres[ii].radius;
        mat = spheres[ii].mat;
        return true;
    } else {
        return false;
    }
}

bool light_intersection(in vec3 origin, in vec3 direction, out vec3 normal, out material mat)
{
    vec3 tmp = origin; vec2 tx;
    return next_intersection(tmp, direction, normal, mat, tx);
}
