/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/dynamic.hpp>
#include <elements/view.hpp>

namespace cycfi { namespace elements
{
   view_limits dynamic::limits(basic_context const& ctx) const
   {
      if (_composer)
      {
         auto w_limits = _composer->width_limits();
         if (auto size = _composer->size())
         {
            view_limits l = {{ w_limits.min, 0 }, { w_limits.max, full_extent }};
            for (std::size_t i = 0; i != size; ++i)
               l.min.y += _composer->line_height(i);
            l.max.y = l.min.y;
            return l;
         }
      }
      return {{ 0, 0 }, { 0, 0 }};
   }

   void dynamic::draw(context const& ctx)
   {
      auto& cnv = ctx.canvas;
      auto  state = cnv.new_state();
      auto  clip_extent = cnv.clip_extent();
      auto  y = ctx.bounds.top;

      cnv.rect(ctx.bounds);
      cnv.clip();
      for (auto const& row : _rows)
      {
         context rctx { ctx, row.second.get(), ctx.bounds };
         rctx.bounds.top = y;
         rctx.bounds.bottom = (y += row.first);
         if (intersects(clip_extent, rctx.bounds))
         {
            if (_needs_layout)
               row.second->layout(rctx);
            row.second->draw(rctx);
         }
      }
      _needs_layout = false;
      _previous_bounds = ctx.bounds;
   }

   void dynamic::layout(context const& ctx)
   {
      if (_previous_bounds != ctx.bounds)
         _needs_layout = true;
   }

   void dynamic::build()
   {
      if (_composer)
      {
         if (auto size = _composer->size())
         {
            _rows.reserve(_composer->size());
            for (std::size_t i = 0; i != size; ++i)
               _rows.push_back(
                  std::pair{
                     _composer->line_height(i)
                   , _composer->compose(i)
                  }
               );
         }
      }
      _needs_layout = true;
   }
}}

