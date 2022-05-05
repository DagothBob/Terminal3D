/*
 * Drawable geometries
 * 
 * Made by DagothBob (https://github.com/DagothBob)
 */

#include <memory>
#include <vector>
#include "render.hpp"
#include "types.hpp"

#ifndef TERM3D_DRAWABLES_H
#define TERM3D_DRAWABLES_H

namespace Drawables {
    /* Abstract class for building drawable geometries. */
    class Drawable {
        public:

        /* Holds various data about a ray hit. */
        struct hit_record {
            V3D point; // Point where ray collided.
            V3D normal; // Normal vector from collision.
            double interval; // Multiple of pointing vector hit occurred at.
            bool front_face; // Did ray collide from the front?

            inline void set_face_normal(Renderer::Ray& ray, V3D& outward_normal) {
                front_face = ray.direction.dot(outward_normal) < 0;
                normal = front_face ? outward_normal : -outward_normal;
            }
        };

        Drawable() = default;

        Drawable(const Drawable&) = default;

        virtual ~Drawable() = default;

        /* ray: Ray to perform the collision check.
           int_min: Minimal interval "t" to check from.
           int_max: Maximal interval "t" to check until.
           rec: Hit record to store data about the ray collision. */
        virtual bool hit(Renderer::Ray& ray, double int_min, double int_max, hit_record& rec) = 0;
    };

    /* List of drawable objects. Good for representing a "world", "level", or
       a compound object made from other drawables. */
    class Draw_List : public Drawable{
        public:

        std::vector<std::shared_ptr<Drawable>> list; // Object list
        
        /* Initialises an empty list of drawables. */
        Draw_List();

        /* Initialises the draw list with the given drawable object. */
        Draw_List(std::shared_ptr<Drawable> drawable);

        /* Empty the object list. */
        void clear();

        /* Add a drawable to the draw list. */
        void add(std::shared_ptr<Drawable> drawable);

        /* If any objects in the draw list are hit, returns true. "ray"
           contains the colour of the object hit. */
        virtual bool hit(Renderer::Ray& ray, double int_min, double int_max, hit_record& rec) override;
    };
}

#endif
