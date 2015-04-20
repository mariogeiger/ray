bool refraction(in vec3 v, in vec3 n, in float cos, out vec3 t, in float eta);
const int maxrays = 10;
void main(void)
{
    vec3 color = vec3(0.0, 0.0, 0.0);

    ray r;
    r.power = 1.0;
    r.origin = vec3(view[3]);
    r.direction = normalize(first_ray);

    for (int ray_count = 0; true; ++ray_count) {
        float d = 0.0;

        // collision
        vec3 n;
        vec2 tx;
        material m;
        if (!next_intersection(r.origin, r.direction, n, m, tx)) {
            color += r.power * texture(cubemap, r.direction).rgb;
            //color += r.power * r.direction;
            break;
        }

        float cos = dot(r.direction, n);
        vec3 i = r.direction - 2.0 * cos * n;

        // phong
        if (m.phong_factor > 0.0) {
            float lfactor = 1.0; // light
            float dfactor = 0.0; // diffuse
            float sfactor = 0.0; // specular

            vec3 nn;
            material mm;
            if (light_intersection(r.origin + fuzzy * light, light, nn, mm)) {
                if (mm.eta > 0.0)
                    lfactor = (1.0 - abs(mm.phong_factor)) * abs(dot(light, nn));
                else
                    lfactor = 1.0 - abs(dot(light, nn));// * abs(mm.phong_factor);
            }

            if (lfactor > 0.0) { // if we are not in the shadow
                dfactor = max(cos > 0.0 ? -dot(light, n) : dot(light, n), 0.0);
                sfactor = pow(max(dot(light, i), 0.0), 4.0);
            }

            color += r.power * m.phong_factor * (m.ambiant + lfactor * (dfactor * m.diffuse + sfactor * vec3(1.0, 1.0, 1.0)));
        }

        // texture
        float pf = abs(m.phong_factor);
        /*if (m.phong_factor < 0.0) {
            //color += r.power * pf * texture(tex, tx).rgb;
            color += r.power * pf * vec3(0, 1, 0);
        }*/

        // reflexion & transmission
        if (pf < 1.0 && ray_count < maxrays) {
            vec3 t;

            if (m.eta > 0.0 && refraction(r.direction, n, cos, t, m.eta)) {
                r.power *= 1.0 - pf;
                r.origin += fuzzy * t;
                r.direction = t;
            } else {
                r.power *= 1.0 - pf;
                r.origin += fuzzy * i;
                r.direction = i;
            }
        } else {
            break;
        }
    }

    pixelColor = vec4(color, 1.0);
}

bool refraction(in vec3 v, in vec3 n, in float cos, out vec3 t, in float eta)
{
    // cos = dot(v,n)
    if (cos < 0.0) {
        //        t = refract(v, n, 1.0 / eta);
        float k = 1.0 - (1.0 - cos * cos) / eta / eta;
        if (k < 0.0)
            return false;
        t = v / eta - (cos / eta + sqrt(k)) * n;
    } else {
        //        t = refract(v, -n, eta);
        float k = 1.0 - eta * eta * (1.0 - cos * cos); // -a * -a = a * a
        if (k < 0.0)
            return false;
        t = eta * v + (-eta * cos + sqrt(k)) * n; // -n
    }
    return true;
}
