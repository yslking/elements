/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_PORT_APRIL_24_2016)
#define ELEMENTS_PORT_APRIL_24_2016

#include <elements/element/proxy.hpp>
#include <elements/view.hpp>
#include <memory>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Port elements
   ////////////////////////////////////////////////////////////////////////////
   class port_base : public proxy_base
   {
   public:

      virtual double          halign() const = 0;
      virtual void            halign(double val) = 0;
      virtual double          valign() const = 0;
      virtual void            valign(double val) = 0;
   };

   template <typename Base>
   class port_element : public Base
   {
   public:

      using Base::Base;

      view_limits             limits(basic_context const& ctx) const override;
      void                    prepare_subject(context& ctx) override;
      void                    draw(context const& ctx) override;

      double                  halign() const override       { return _halign; }
      void                    halign(double val) override   { _halign = val; }
      double                  valign() const override       { return _valign; }
      void                    valign(double val) override   { _valign = val; }

   private:

      double                  _halign = 0.0;
      double                  _valign = 0.0;
   };

   template <typename Subject>
   inline proxy<Subject, port_element<port_base>>
   port(Subject&& subject)
   {
      return { std::forward<Subject>(subject) };
   }

   template <typename Base>
   class vport_element : public Base
   {
   public:

      using Base::Base;

      view_limits             limits(basic_context const& ctx) const override;
      void                    prepare_subject(context& ctx) override;
      void                    draw(context const& ctx) override;

      double                  halign() const override       { return 0; }
      void                    halign(double val) override   {}
      double                  valign() const override       { return _valign; }
      void                    valign(double val) override   { _valign = val; }

   private:

      double                  _valign = 0.0;
   };

   template <typename Subject>
   inline proxy<Subject, vport_element<port_base>>
   vport(Subject&& subject)
   {
      return { std::forward<Subject>(subject) };
   }

   ////////////////////////////////////////////////////////////////////////////
   // Scrollers
   ////////////////////////////////////////////////////////////////////////////

   // scrollable: Mixin class for a element that is scrollable
   // scroll the rectangle, r into view
   class scrollable
   {
   public:
      virtual ~scrollable() = default;

      struct scrollable_context
      {
         context const* context_ptr;
         scrollable*    scrollable_ptr;

         // scroll the rectangle, r into view
         bool scroll_into_view(rect r_)
         {
            if (scrollable_ptr && context_ptr)
            {
               rect r = r_;
               return scrollable_ptr->scroll_into_view(*context_ptr, r);
            }
            return false;
         }
      };

      virtual bool               scroll_into_view(context const& ctx, rect const& r) = 0;
      static scrollable_context  find(context const& ctx);
   };

   enum
   {
      no_scrollbars  = 1,
      no_hscroll     = 1 << 1,
      no_vscroll     = 1 << 2
   };

   // Base proxy class for views that are scrollable
   class scroller_base : public port_base, public scrollable
   {
   public:

      static float            width;

      scroller_base(int traits = 0)
       : _tracking(none)
       , _traits(traits)
      {}

      ~scroller_base() {}

      view_limits             limits(basic_context const& ctx) const override;
      element*                hit_test(context const& ctx, point const& p) override;
      void                    draw(context const& ctx) override;

      bool                    wants_control() const override;
      element*                click(context const& ctx, mouse_button btn) override;
      void                    drag(context const& ctx, mouse_button btn) override;
      bool                    scroll(context const& ctx, point const& dir, point const& p) override;
      bool                    scroll_into_view(context const& ctx, rect const& r) override;
      bool                    cursor(context const& ctx, point const& p, cursor_tracking status) override;
      bool                    key(context const& ctx, key_info k) override;

      struct scrollbar_info
      {
         double   pos;
         float    extent;
         rect     bounds;
      };

      virtual void            draw_scroll_bar(context const& ctx, scrollbar_info const& info, point const& mp);
      virtual rect            scroll_bar_position(context const& ctx, scrollbar_info const& info);

   private:

      struct scrollbar_bounds
      {
         rect vscroll_bounds;
         rect hscroll_bounds;
         bool has_v = false;
         bool has_h = false;
      };

      enum tracking_status
      {
         none,
         start,
         tracking_v,
         tracking_h
      };

      scrollbar_bounds  get_scrollbar_bounds(context const& ctx);
      bool              reposition(context const& ctx, point const& p);

      bool              has_scrollbars() const { return !(_traits & no_scrollbars); }
      bool              allow_hscroll() const { return !(_traits & no_hscroll); }
      bool              allow_vscroll() const { return !(_traits & no_vscroll); }

      point             _offset;
      tracking_status   _tracking;
      int               _traits;
   };

   template <typename Subject>
   inline proxy<Subject, port_element<scroller_base>>
   scroller(Subject&& subject, int traits = 0)
   {
      return { std::forward<Subject>(subject), traits };
   }

   template <typename Subject>
   inline proxy<Subject, port_element<scroller_base>>
   vscroller(Subject&& subject, int traits = 0)
   {
      return { std::forward<Subject>(subject), traits | no_hscroll };
   }

   template <typename Subject>
   inline proxy<Subject, port_element<scroller_base>>
   hscroller(Subject&& subject, int traits = 0)
   {
      return { std::forward<Subject>(subject), traits | no_vscroll };
   }

   ////////////////////////////////////////////////////////////////////////////
   // port_base class implementation
   ////////////////////////////////////////////////////////////////////////////
   constexpr auto min_port_size = 32;

   template <typename Base>
   inline view_limits port_element<Base>::limits(basic_context const& ctx) const
   {
      view_limits e_limits = this->subject().limits(ctx);
      return {{ min_port_size, min_port_size }, e_limits.max };
   }

   template <typename Base>
   inline void port_element<Base>::prepare_subject(context& ctx)
   {
      view_limits    e_limits          = this->subject().limits(ctx);
      double         elem_width        = e_limits.min.x;
      double         elem_height       = e_limits.min.y;
      double         available_width   = ctx.parent->bounds.width();
      double         available_height  = ctx.parent->bounds.height();

      ctx.bounds.left -= (elem_width - available_width) * _halign;
      ctx.bounds.width(elem_width);
      ctx.bounds.top -= (elem_height - available_height) * _valign;
      ctx.bounds.height(elem_height);

      this->subject().layout(ctx);
   }

   template <typename Base>
   inline void port_element<Base>::draw(context const& ctx)
   {
      auto state = ctx.canvas.new_state();
      ctx.canvas.rect(ctx.bounds);
      ctx.canvas.clip();
      Base::draw(ctx);
   }

   ////////////////////////////////////////////////////////////////////////////
   // vport_base class implementation
   ////////////////////////////////////////////////////////////////////////////
   template <typename Base>
   inline view_limits vport_element<Base>::limits(basic_context const& ctx) const
   {
      view_limits e_limits = this->subject().limits(ctx);
      return {{ e_limits.min.x, min_port_size }, e_limits.max };
   }

   template <typename Base>
   inline void vport_element<Base>::prepare_subject(context& ctx)
   {
      view_limits    e_limits          = this->subject().limits(ctx);
      double         elem_height       = e_limits.min.y;
      double         available_height  = ctx.parent->bounds.height();

      ctx.bounds.top -= (elem_height - available_height) * _valign;
      ctx.bounds.height(elem_height);

      this->subject().layout(ctx);
   }

   template <typename Base>
   inline void vport_element<Base>::draw(context const& ctx)
   {
      auto state = ctx.canvas.new_state();
      ctx.canvas.rect(ctx.bounds);
      ctx.canvas.clip();
      Base::draw(ctx);
   }
}}

#endif
