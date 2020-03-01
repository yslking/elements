/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_CIRCLE_APRIL_17_2016)
#define ELEMENTS_CIRCLE_APRIL_17_2016

#include <elements/support/rect.hpp>
#include <algorithm>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Circles
   ////////////////////////////////////////////////////////////////////////////
   struct circle
   {
      constexpr   circle();
      constexpr   circle(double cx, double cy, double radius);
      constexpr   circle(point const& c, double radius);
      constexpr   circle(rect const& r);
                  circle(circle const&) = default;
      circle&     operator=(circle const&) = default;

      rect        bounds() const { return { cx-radius, cy-radius, cx+radius, cy+radius }; }
      bool        operator==(circle const& other) const;
      bool        operator!=(circle const& other) const;

      point       center() const;
      circle      inset(double x) const;
      circle      move(double dx, double dy) const;
      circle      move_to(double x, double y) const;

      double      cx;
      double      cy;
      double      radius;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   inline constexpr circle::circle()
    : cx(0.0), cy(0.0), radius(0.0)
   {}

   inline constexpr circle::circle(double cx, double cy, double radius)
    : cx(cx), cy(cy), radius(radius)
   {}

   inline constexpr circle::circle(point const& c, double radius)
    : cx(c.x), cy(c.y), radius(radius)
   {}

   inline constexpr circle::circle(rect const& r)
    : circle(center_point(r), std::min(r.width(), r.height()))
   {}

   inline bool circle::operator==(circle const& other) const
   {
      return (other.cx == cx) && (other.cy == cy) && (other.radius == radius);
   }

   inline bool circle::operator!=(circle const& other) const
   {
      return !(*this == other);
   }

   inline point circle::center() const
   {
      return { cx, cy };
   }

   inline circle circle::inset(double x) const
   {
      return { cx, cy, radius-x };
   }

   inline circle circle::move(double dx, double dy) const
   {
      return { cx+dx, cy+dy, radius };
   }

   inline circle circle::move_to(double x, double y) const
   {
      return { x, y, radius };
   }
}}

#endif
