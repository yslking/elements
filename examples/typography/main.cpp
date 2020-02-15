#include <elements.hpp>
#include <pango/pangocairo.h>

using namespace cycfi::elements;

// Main window background color
auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

auto samples = basic(
   [](context const& ctx)
   {
      auto& cnv = ctx.canvas;
      font_descr font_{"Open Sans" };
      font_.size(24);

      text_layout layout_{ cnv };
      layout_.font(font_);

      cnv.fill_style(get_theme().label_font_color);

      layout_.text("Regular");
      cnv.fill({ 20, 20 }, layout_);

      layout_.text("Bold");
      font_.weight(font_descr::bold);
      layout_.font(font_);
      cnv.fill({ 150, 20 }, layout_);

      layout_.text("Outline");
      font_.weight(font_descr::normal);
      layout_.font(font_);
      cnv.stroke_style(get_theme().label_font_color);
      cnv.line_width(0.5);
      cnv.stroke({ 20, 60 }, layout_);

      layout_.text("AV Kerning");
      cnv.fill({ 20, 100 }, layout_);
   }
);

int main(int argc, const char* argv[])
{
   app _app(argc, argv);
   window _win(_app.name());
   _win.on_close = [&_app]() { _app.stop(); };

   view view_(_win);

   view_.content(
      {
         share(samples),
         share(background)    // Replace background with your main element,
                              // or keep it and add another layer on top of it.
      }
   );

   _app.run();
   return 0;
}