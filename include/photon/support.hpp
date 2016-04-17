/*=================================================================================================   Copyright (c) 2016 Joel de Guzman   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.   http://creativecommons.org/licenses/by-sa/4.0/=================================================================================================*/#if !defined(PHOTON_GUI_LIB_SUPPORT_APRIL_10_2016)#define PHOTON_GUI_LIB_SUPPORT_APRIL_10_2016#include <photon/point.hpp>#include <photon/rect.hpp>#include <cfloat>namespace photon{   ////////////////////////////////////////////////////////////////////////////////////////////////   // Limits   ////////////////////////////////////////////////////////////////////////////////////////////////   constexpr float   full_extent    = 10E6;   constexpr rect    full_limits    = { 0.0, 0.0, full_extent, full_extent };   constexpr rect    empty_limits   = { 0.0, 0.0, 0.0, 0.0 };   constexpr rect    empty_rect     = { 0.0, 0.0, 0.0, 0.0 };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Mouse Button   ////////////////////////////////////////////////////////////////////////////////////////////////   enum class mouse_button   {      left,      middle,      right   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Key info   ////////////////////////////////////////////////////////////////////////////////////////////////   struct key_info   {      int   key;      int   scancode;      int   action;      int   modifiers;   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Focus request   ////////////////////////////////////////////////////////////////////////////////////////////////   enum class focus_request   {      wants_focus,      begin_focus,      end_focus   };   ////////////////////////////////////////////////////////////////////////////////////////////////   // Utilities   ////////////////////////////////////////////////////////////////////////////////////////////////   template <typename T, typename U>   inline void max_limit(T& val, U const& max)   {      if (val > max)         val = max;   }   template <typename T, typename U>   inline void min_limit(T& val, U const& min)   {      if (val < min)         val = min;   }   template <typename T, typename U, typename V>   inline void limit(T& val, U const& min, V const& max)   {      min_limit(val, min);      max_limit(val, max);   }   template <typename T, typename U, typename V>   inline bool within(T const& val, U const& min, V const& max)   {      return (val >= min) && (val <= max);   }}#endif