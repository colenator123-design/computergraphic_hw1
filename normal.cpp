#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

using namespace std;
float hit_sphere(const vec3 &center, float radius, const ray& r) {
	
	float A=dot(r.D,r.D);
	float B=2*dot(r.D,r.O-center);
	float C=dot(center-r.O,center-r.O)-radius*radius;
	if(B*B-4*A*C>=0)
	{
		return ((-B-sqrt(B*B-4.0*A*C))/2.0*A);
	}
	else
	{
		return -1;
	}
}

vec3 color(const ray& r)
{
    float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	cout<<t;
    vec3 center(0,0,-1);
	if (t > 0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t) -center);
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t= 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)* vec3(1, 1, 1) + t* vec3(1, 0.5, 0);

}


int main()
{
	int width = 200;
	int height = 100;

	fstream file;
	file.open("ray.ppm", ios::out);

	vec3 lower_left_corner(-2, -1, -1);
	vec3 origin(0, 0, 0);
	vec3 horizontal(4, 0, 0);
	vec3 vertical(0, 2, 0);
	file << "P3\n"
		 << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float u = float(i) / float(width);
			float v = float(j) / float(height);
			vec3 uvcenter = lower_left_corner + u * horizontal + v * vertical;
			ray r(origin, uvcenter - origin);
			vec3 c = color(r);

			file << int(c[0] * 255) << " " << int(c[1] * 255) << " " << int(c[2] * 255) << "\n";
		}
	}

	return 0;
}
