/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_RECT_APRIL_10_2016)
#define ELEMENTS_RECT_APRIL_10_2016

#include <elements/support/point.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // rect
   ////////////////////////////////////////////////////////////////////////////
   struct rect
   {
      constexpr         rect();
      constexpr         rect(float left, float top, float right, float bottom);
      constexpr         rect(point const& origin, float right, float bottom)
                         : rect(origin.x, origin.y, right, bottom)
                        {}
      constexpr         rect(float left, float top, extent size)
                         : rect(left, top, left + size.x, top + size.y)
                        {}
      constexpr         rect(point const& origin, extent size)
                         : rect(origin.x, origin.y, origin.x + size.x, origin.y + size.y)
                        {}

                        rect(rect const &) = default;
      constexpr rect&   operator=(rect const&) = default;

      constexpr bool    operator==(rect const& other) const;
      constexpr bool    operator!=(rect const& other) const;

      constexpr bool    is_empty() const;
      constexpr bool    includes(point const& p) const;
      constexpr bool    includes(rect const& other) const;

      constexpr float   width() const;
      constexpr void    width(float width_);
      constexpr float   height() const;
      constexpr void    height(float height_);

      constexpr point   top_left() const;
      constexpr point   bottom_right() const;
      constexpr point   top_right() const;
      constexpr point   bottom_left() const;

      constexpr rect    move(float dx, float dy) const;
      constexpr rect    move_to(float x, float y) const;
      constexpr rect    inset(float x_inset = 1.0, float y_inset = 1.0) const;

      float             left;
      float             top;
      float             right;
      float             bottom;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Free Functions
   ////////////////////////////////////////////////////////////////////////////
   constexpr bool       is_valid(rect const& r);
   constexpr bool       is_same_size(rect const& a, rect const& b);
   bool                 intersects(rect const& a, rect const& b);

   constexpr point      center_point(rect const& r);
   constexpr float      area(rect const& r);
   rect                 max(rect const& a, rect const& b);
   rect                 min(rect const& a, rect const& b);

   constexpr void       clear(rect& r);
   rect                 center(rect const& r, rect const& encl);
   rect                 center_h(rect const& r, rect const& encl);
   rect                 center_v(rect const& r, rect const& encl);
   rect                 align(rect const& r, rect const& encl, float x_align, float y_align);
   rect                 align_h(rect const& r, rect const& encl, float x_align);
   rect                 align_v(rect const& r, rect const& encl, float y_align);
   rect                 clip(rect const& r, rect const& encl);

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   constexpr rect::rect()
    : left(0.0), top(0.0), right(0.0), bottom(0.0)
   {}

   constexpr rect::rect(float left, float top, float right, float bottom)
    : left(left), top(top), right(right), bottom(bottom)
   {}

   constexpr bool rect::operator==(rect const& other) const
   {
      return
         (top == other.top) && (bottom == other.bottom) &&
         (left == other.left) && (right == other.right)
         ;
   }

   constexpr bool rect::operator!=(rect const& other) const
   {
      return !(*this == other);
   }

   constexpr bool rect::is_empty() const
   {
      return (left == right) || (top == bottom);
   }

   constexpr bool rect::includes(point const& p) const
   {
      return
         (p.x >= left) && (p.x <= right) &&
         (p.y >= top) && (p.y <= bottom)
         ;
   }

   constexpr bool rect::includes(rect const& other) const
   {
      return
         (other.left >= left) && (other.left <= right) &&
         (other.top >= top) && (other.top <= bottom) &&
         (other.right >= left) && (other.right <= right) &&
         (other.bottom >= top) && (other.bottom <= bottom)
         ;
   }

   constexpr float rect::width() const
   {
      return right - left;
   }

   constexpr void rect::width(float width_)
   {
      right = left + width_;
   }

   constexpr float rect::height() const
   {
      return (bottom - top);
   }

   constexpr void rect::height(float height_)
   {
      bottom = top + height_;
   }

   constexpr point rect::top_left() const
   {
      return { left, top };
   }

   constexpr point rect::bottom_right() const
   {
      return { right, bottom };
   }

   constexpr point rect::top_right() const
   {
      return { right, top };
   }

   constexpr point rect::bottom_left() const
   {
      return { left, bottom };
   }

   constexpr rect rect::move(float dx, float dy) const
   {
      rect r = *this;
      r.top += dy;
      r.left += dx;
      r.bottom += dy;
      r.right += dx;
      return r;
   }

   constexpr rect rect::move_to(float x, float y) const
   {
      return move(x-left, y-top);
   }

   constexpr rect rect::inset(float x_inset, float y_inset) const
   {
      rect r = *this;
      r.top += y_inset;
      r.left += x_inset;
      r.bottom -= y_inset;
      r.right -= x_inset;

      if (!is_valid(r))
         clear(r);

      return r;
   }

   constexpr bool is_valid(rect const& r)
   {
      return (r.left <= r.right) && (r.top <= r.bottom);
   }

   constexpr bool is_same_size(rect const& a, rect const& b)
   {
      return (a.width() == b.width()) && (a.height() == b.height());
   }

   constexpr point center_point(rect const& r)
   {
      return { r.left + (r.width() / 2.0f), r.top + (r.height() / 2.0f) };
   }

   constexpr float area(rect const& r)
   {
      return r.width() * r.height();
   }

   constexpr void clear(rect& r)
   {
      r.left = 0.0;
      r.top  = 0.0;
      r.right = 0.0;
      r.bottom = 0.0;
   }
}}

#endif
