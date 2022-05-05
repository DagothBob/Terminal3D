#include "./include/Terminal3D"

#ifndef TERM3D_SPHERE_H
#define TERM3D_SPHERE_H

/* Sphere which is coloured based on the normal of the surface hit. */
class Sphere : public Drawables::Drawable {
    public:

    V3D centre; // Point where the sphere exists.
    double radius;

    Sphere(V3D _centre, double _radius);

    virtual bool hit(Renderer::Ray& ray, double int_min, double int_max, hit_record& rec) override;
};

#endif
