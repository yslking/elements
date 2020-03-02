/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_DYNAMIC_MARCH_2_2020)
#define ELEMENTS_DYNAMIC_MARCH_2_2020

#include <elements/element/element.hpp>
#include <memory>
#include <vector>
#include <utility>

namespace cycfi { namespace elements
{
   class dynamic : public element
   {
   public:

      class composer : public std::enable_shared_from_this<composer>
      {
      public:

         struct limits
         {
            double   min = 0;
            double   max = full_extent;
         };

         virtual std::size_t     size() const = 0;
         virtual element_ptr     compose(std::size_t index) = 0;
         virtual limits          width_limits() const = 0;
         virtual double          line_height(std::size_t index) const = 0;
      };

      using composer_ptr = std::shared_ptr<composer>;

                                 dynamic(composer_ptr composer)
                                  : _composer(composer)
                                 {}

      view_limits                limits(basic_context const& ctx) const override;
      void                       draw(context const& ctx) override;
      void                       layout(context const& ctx) override;

      void                       build();

   private:

      using row_info = std::pair<double, element_ptr>;

      composer_ptr               _composer;
      std::vector<row_info>      _rows;
      bool                       _needs_layout = true;
      rect                       _previous_bounds;
   };
}}

#endif
