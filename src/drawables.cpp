/* 
 * Made by DagothBob (https://github.com/DagothBob) 
 */

#include "drawables.hpp"
#include "types.hpp"

using namespace Drawables;

Draw_List::Draw_List():
list(std::vector<std::shared_ptr<Drawable>>()) {}

Draw_List::Draw_List(std::shared_ptr<Drawable> drawable):
list(std::vector<std::shared_ptr<Drawable>>()) {
    add(drawable);
}

void Draw_List::clear() {
    list.clear();
}

void Draw_List::add(std::shared_ptr<Drawable> drawable) {
    list.push_back(drawable);
}

bool Draw_List::hit(Renderer::Ray& ray, double int_min, double int_max, hit_record& rec) {
    hit_record temp_record;
    bool hit_anything = false;
    double closest = int_max;

    for (std::shared_ptr<Drawable> obj : list) {
        if (obj->hit(ray, int_min, closest, temp_record)) {
            hit_anything = true;
            closest = temp_record.interval;
            rec = temp_record;
        }
    }

    return hit_anything;
}
