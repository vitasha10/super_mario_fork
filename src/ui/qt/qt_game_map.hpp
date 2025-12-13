#pragma once

#include <vector>

#include <QWidget>

#include "game_map.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
        class QtGameWidget;

        class QtGameMap : public GameMap {
        private:
                QtGameWidget* view = nullptr;
                std::vector<QtUIObject*> objs;
                const int scale;

        public:
                QtGameMap(const int height, const int width, QWidget* parent = nullptr);
                ~QtGameMap();

                static constexpr int DEFAULT_SCALE = 6;

                void add_obj(QtUIObject*);
                void clear() noexcept override;
                int get_scale() const noexcept;
                int get_view_height() const noexcept;
                int get_view_width() const noexcept;
                const std::vector<QtUIObject*>& get_objects() const noexcept;
                void refresh() noexcept override;
                void remove_obj(QtUIObject*);
                void remove_objs() override;
                void show() const noexcept override;
                QWidget* widget() const noexcept;
                void close_widget() const noexcept;

        private:
                void configure_widget(QWidget* parent);
        };
}
