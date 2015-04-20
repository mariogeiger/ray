float refraction(in vec3 v, in vec3 n, in float cosi, out vec3 t, in float eta);
const int maxrays = 25;
const int qmax = 16;
ray queue[qmax];
const float minpower = 1.0 / 256.0;

void main(void)
{
    vec3 color = vec3(0.0, 0.0, 0.0);

    int qread = 0;
    int qwrite = 1;

    queue[0].power = 1.0;
    queue[0].origin = vec3(view[3]);
    queue[0].direction = normalize(first_ray);

    for (int ray_count = 0; ray_count < maxrays; ++ray_count) {
        // nothing to read
        if (qread == qwrite) {
			break;
		}
        ray r = queue[qread++]; qread = qread % qmax;

        // collision
        vec3 n;
        material m;
        if (!next_intersection(r.origin, r.direction, n, m)) {
            color += r.power * texture(cubemap, r.direction).rgb;
            continue;
        }

        float cos = -dot(r.direction, n); // cos(theta_incident)
        vec3 i = r.direction + 2.0 * cos * n; // reflexion

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
                dfactor = max(cos < 0.0 ? -dot(light, n) : dot(light, n), 0.0);
                sfactor = pow(max(dot(light, i), 0.0), 4.0);
            }

            color += r.power * m.phong_factor * (m.ambiant + lfactor * (dfactor * m.diffuse + sfactor * vec3(1.0, 1.0, 1.0)));
        }

        float pf = abs(m.phong_factor);

        // reflexion & transmission
        if (pf < 1.0) {
            vec3 t;
            float R = 1.0;
            ray s;

			if ((qwrite+1)%qmax == qread)
				continue;
			
            if (m.eta > 0.0) {
                R = refraction(r.direction, n, cos, t, m.eta);
			}
			
			if (R < 1.0) {
				s = r;
				s.power *= (1.0 - pf) * (1.0 - R);
				if (s.power > minpower) {
					s.origin += fuzzy * t;
					s.direction = t;
					queue[qwrite++] = s;
					qwrite = qwrite % qmax;
				}
			}

			if ((qwrite+1)%qmax == qread)
				continue;

			s = r;
			s.power *= (1.0 - pf) * R;
			if (s.power > minpower) {
				s.origin += fuzzy * i;
				s.direction = i;
				queue[qwrite++] = s; 
				qwrite = qwrite % qmax;
			}
        }
    }

    pixelColor = vec4(color, 1.0);
}

float refraction(in vec3 v, in vec3 n, in float cosi, out vec3 t, in float eta)
{
    if (cosi < 0.0) {
        //return refraction(v, -n, -cosi, t, 1./eta);
        n = -n;
        cosi = -cosi;
        eta = 1.0/eta;
    }
    // dot(v,n)<0 and eta=n2/n1 where v goes from n1 to n2

    // return the power of reflection

    // sin(ti) = eta sin(tt)
    float cost2 = 1. - (1. - cosi*cosi) / (eta*eta);
    if (cost2 <= 0.0) {
        // T.I.R.
        return 1.;
    }
    float cost = sqrt(cost2);

    float rs = (cosi - eta*cost) / (cosi + eta*cost);
    float rp = (eta*cosi - cost) / (eta*cosi + cost);

    t = v / eta - (cost - cosi/eta) * n;

    return (rs*rs + rp*rp) / 2.0;
}
