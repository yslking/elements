/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_POINT_APRIL_10_2016)
#define ELEMENTS_POINT_APRIL_10_2016

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Points
   ////////////////////////////////////////////////////////////////////////////
   struct point
   {
      constexpr         point();
      constexpr         point(double x, double y);
      constexpr         point(point const&) = default;
      constexpr point&  operator=(point const &) = default;

      constexpr bool    operator==(point const& other) const;
      constexpr bool    operator!=(point const& other) const;

      constexpr point   move(double dx, double dy) const;
      constexpr point   move_to(double x, double y) const;

      double            x;
      double            y;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Sizes
   ////////////////////////////////////////////////////////////////////////////
   struct extent : point
   {
      using point::point;

                  extent(point const& p)
                   : point(p)
                  {}

      point       move(double dx, double dy) const = delete;
      point       move_to(double x, double y) const = delete;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   inline constexpr point::point()
    : x(0.0), y(0.0)
   {}

   inline constexpr point::point(double x, double y)
    : x(x), y(y)
   {}

   inline constexpr bool point::operator==(point const& other) const
   {
      return (other.x == x) && (other.y == y);
   }

   inline constexpr bool point::operator!=(point const& other) const
   {
      return !(*this == other);
   }

   inline constexpr point point::move(double dx, double dy) const
   {
      point r = *this;
      r.x += dx;
      r.y += dy;
      return r;
   }

   inline constexpr point point::move_to(double x_, double y_) const
   {
      point r = *this;
      r.x = x_;
      r.y = y_;
      return r;
   }
}}

#endif
