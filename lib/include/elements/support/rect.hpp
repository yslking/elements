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
      constexpr         rect(double left, double top, double right, double bottom);
      constexpr         rect(point const& origin, double right, double bottom)
                         : rect(origin.x, origin.y, right, bottom)
                        {}
      constexpr         rect(double left, double top, extent size)
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

      constexpr double  width() const;
      constexpr void    width(double width_);
      constexpr double  height() const;
      constexpr void    height(double height_);

      constexpr point   top_left() const;
      constexpr point   bottom_right() const;
      constexpr point   top_right() const;
      constexpr point   bottom_left() const;

      constexpr rect    move(double dx, double dy) const;
      constexpr rect    move_to(double x, double y) const;
      constexpr rect    inset(double x_inset = 1.0, double y_inset = 1.0) const;

      double            left;
      double            top;
      double            right;
      double            bottom;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Free Functions
   ////////////////////////////////////////////////////////////////////////////
   constexpr bool       is_valid(rect const& r);
   constexpr bool       is_same_size(rect const& a, rect const& b);
   bool                 intersects(rect const& a, rect const& b);

   constexpr point      center_point(rect const& r);
   constexpr double     area(rect const& r);
   rect                 max(rect const& a, rect const& b);
   rect                 min(rect const& a, rect const& b);

   constexpr void       clear(rect& r);
   rect                 center(rect const& r, rect const& encl);
   rect                 center_h(rect const& r, rect const& encl);
   rect                 center_v(rect const& r, rect const& encl);
   rect                 align(rect const& r, rect const& encl, double x_align, double y_align);
   rect                 align_h(rect const& r, rect const& encl, double x_align);
   rect                 align_v(rect const& r, rect const& encl, double y_align);
   rect                 clip(rect const& r, rect const& encl);

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   constexpr rect::rect()
    : left(0.0), top(0.0), right(0.0), bottom(0.0)
   {}

   constexpr rect::rect(double left, double top, double right, double bottom)
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

   constexpr double rect::width() const
   {
      return right - left;
   }

   constexpr void rect::width(double width_)
   {
      right = left + width_;
   }

   constexpr double rect::height() const
   {
      return (bottom - top);
   }

   constexpr void rect::height(double height_)
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

   constexpr rect rect::move(double dx, double dy) const
   {
      rect r = *this;
      r.top += dy;
      r.left += dx;
      r.bottom += dy;
      r.right += dx;
      return r;
   }

   constexpr rect rect::move_to(double x, double y) const
   {
      return move(x-left, y-top);
   }

   constexpr rect rect::inset(double x_inset, double y_inset) const
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

   constexpr double area(rect const& r)
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
