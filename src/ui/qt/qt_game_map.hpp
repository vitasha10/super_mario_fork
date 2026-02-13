#pragma once

#include <vector>
#include <QPainter>

#include "game_map.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
    class QtGameMap : public GameMap {
    private:
        std::vector<QtUIObject*> objs;

    public:
        QtGameMap(const int height, const int width);

        void add_obj(QtUIObject*);
        void clear() noexcept override;
        void refresh() noexcept override;
        void remove_obj(QtUIObject*);
        void remove_objs() override;
        void show() const noexcept override;

        void paint(QPainter& painter, int cell_size) const;
        int get_width() const noexcept;
        int get_height_val() const noexcept;
        const std::vector<QtUIObject*>& get_objs() const;
    };
}
