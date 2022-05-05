#include "./include/Terminal3D"
#include "sphere.hpp"

Sphere::Sphere(V3D _centre, double _radius):
centre(_centre),
radius(_radius) {}

bool Sphere::hit(Renderer::Ray& ray, double int_min, double int_max, hit_record& rec) {
    V3D oc = ray.origin - centre;
    double a = ray.direction.dot(ray.direction);
    double b = oc.dot(ray.direction);
    double c = oc.dot(oc) - (radius * radius);

    double discriminant = (b * b) - (a * c);

    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (-b - sqrtd) / a;

    if (root < int_min || root > int_max) {
        root = (-b + sqrtd) / a;
        if (root < int_min || root > int_max) return false;
    }

    rec.interval = root;
    rec.point = ray.get_at(rec.interval);

    V3D outward_normal = (rec.point - centre) / radius;
    rec.set_face_normal(ray, outward_normal);

    ray.colour = Colour::Pixel_Colour(127 * (rec.normal + V3D(1, 1, 1)));

    return true;
}
