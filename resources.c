#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource."), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1489]; const double alignment; void * const ptr;}  _resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\034\001\000\000\000\000\000\050\011\000\000\000"
  "\000\000\000\000\001\000\000\000\001\000\000\000\002\000\000\000"
  "\004\000\000\000\005\000\000\000\006\000\000\000\010\000\000\000"
  "\011\000\000\000\225\076\165\373\002\000\000\000\034\001\000\000"
  "\012\000\114\000\050\001\000\000\054\001\000\000\033\150\101\235"
  "\006\000\000\000\054\001\000\000\021\000\166\000\100\001\000\000"
  "\165\005\000\000\223\033\303\071\010\000\000\000\165\005\000\000"
  "\014\000\114\000\204\005\000\000\210\005\000\000\124\340\246\014"
  "\000\000\000\000\210\005\000\000\010\000\114\000\220\005\000\000"
  "\224\005\000\000\254\051\032\175\005\000\000\000\224\005\000\000"
  "\005\000\114\000\234\005\000\000\240\005\000\000\324\265\002\000"
  "\377\377\377\377\240\005\000\000\001\000\114\000\244\005\000\000"
  "\250\005\000\000\326\067\257\036\007\000\000\000\250\005\000\000"
  "\006\000\114\000\260\005\000\000\264\005\000\000\227\323\376\062"
  "\003\000\000\000\264\005\000\000\005\000\114\000\274\005\000\000"
  "\300\005\000\000\006\340\175\003\004\000\000\000\300\005\000\000"
  "\011\000\114\000\314\005\000\000\320\005\000\000\163\153\164\163"
  "\145\156\144\145\162\057\000\000\003\000\000\000\146\151\154\145"
  "\055\164\162\141\156\163\146\145\162\056\160\156\147\000\000\000"
  "\045\004\000\000\000\000\000\000\211\120\116\107\015\012\032\012"
  "\000\000\000\015\111\110\104\122\000\000\000\060\000\000\000\060"
  "\010\004\000\000\000\375\013\061\014\000\000\000\040\143\110\122"
  "\115\000\000\172\046\000\000\200\204\000\000\372\000\000\000\200"
  "\350\000\000\165\060\000\000\352\140\000\000\072\230\000\000\027"
  "\160\234\272\121\074\000\000\000\002\142\113\107\104\000\377\207"
  "\217\314\277\000\000\000\011\160\110\131\163\000\000\013\023\000"
  "\000\013\023\001\000\232\234\030\000\000\000\007\164\111\115\105"
  "\007\352\011\031\002\041\022\047\250\130\345\000\000\002\364\111"
  "\104\101\124\130\303\265\230\115\110\024\141\034\306\177\263\233"
  "\146\232\371\121\250\025\121\012\012\301\322\241\016\101\105\224"
  "\335\072\165\051\072\010\041\225\026\342\105\222\072\004\175\211"
  "\025\025\004\101\012\035\054\373\070\025\164\014\051\241\242\103"
  "\202\132\104\007\065\350\240\024\056\232\242\121\256\306\076\035"
  "\034\266\231\232\235\171\147\327\236\271\314\276\363\177\237\347"
  "\375\177\274\377\175\147\340\077\303\012\062\120\226\204\001\002"
  "\066\175\011\065\154\240\300\307\060\301\127\206\371\152\270\352"
  "\077\364\102\071\072\244\027\372\246\204\346\175\256\204\146\325"
  "\257\026\225\010\231\171\275\150\250\002\235\327\264\114\361\113"
  "\017\124\156\044\220\242\277\254\071\143\372\105\334\120\116\240"
  "\104\212\376\152\150\172\151\134\333\003\004\154\372\102\135\123"
  "\042\064\275\044\235\361\025\110\321\337\320\174\106\364\122\227"
  "\042\177\004\042\236\145\271\212\013\064\223\143\132\155\177\141"
  "\245\363\307\062\017\372\042\056\162\062\143\172\260\234\033\301"
  "\041\220\242\277\304\111\267\160\066\370\053\104\024\322\146\104"
  "\077\303\007\342\241\224\204\220\245\323\106\251\235\126\275\112"
  "\265\133\175\236\117\037\053\252\064\002\061\175\066\252\223\367"
  "\052\026\102\133\075\045\134\002\356\020\325\262\311\310\335\012"
  "\266\000\060\100\043\175\346\071\260\354\151\351\061\307\030\243"
  "\214\062\117\063\033\001\030\244\221\267\176\123\234\351\264\050"
  "\362\245\237\340\034\257\122\266\263\366\335\073\232\270\113\314"
  "\114\300\277\221\277\344\016\013\036\343\375\074\111\057\020\301"
  "\034\153\050\111\263\310\162\263\020\005\141\007\035\274\140\001"
  "\013\213\004\317\031\263\227\170\224\303\006\263\205\242\172\154"
  "\330\316\222\352\264\377\273\242\152\320\244\171\231\232\342\023"
  "\355\114\001\021\216\161\205\122\077\323\314\004\104\022\210\160"
  "\234\366\064\171\011\231\203\137\374\240\320\121\143\125\264\361"
  "\224\155\064\005\321\233\011\304\271\316\000\007\150\040\067\065"
  "\353\010\207\310\063\071\237\004\013\304\151\245\033\370\310\076"
  "\066\073\306\127\230\105\063\110\040\316\051\036\000\220\237\132"
  "\177\050\370\047\171\221\136\300\152\316\122\111\370\223\244\257"
  "\007\023\264\332\364\220\107\017\275\200\210\122\313\141\226\207"
  "\166\305\143\243\335\122\104\170\134\305\352\361\335\206\306\033"
  "\155\206\244\347\370\117\276\057\115\210\016\362\214\327\366\175"
  "\051\125\166\006\242\354\141\357\322\010\124\163\233\023\274\261"
  "\163\320\102\055\002\042\224\206\151\221\376\125\024\243\223\235"
  "\000\174\341\046\111\052\250\240\054\334\221\046\250\027\305\350"
  "\144\027\000\043\114\204\041\066\025\200\030\035\354\147\075\165"
  "\124\146\042\140\342\156\214\107\114\122\101\176\266\002\351\117"
  "\335\105\001\307\001\067\134\074\356\020\205\250\157\037\270\130"
  "\234\002\111\206\226\104\140\310\271\101\335\036\364\062\236\065"
  "\175\234\336\164\036\300\000\335\341\373\245\013\242\233\301\264"
  "\317\204\312\164\117\013\031\276\072\111\013\272\257\062\167\255"
  "\130\116\001\000\212\251\247\216\032\162\315\137\330\001\061\317"
  "\060\017\351\142\312\115\153\271\255\154\254\245\232\165\241\172"
  "\176\202\057\214\170\175\112\370\147\225\331\245\040\304\167\212"
  "\245\302\157\306\122\060\037\310\216\273\322\000\000\000\045\164"
  "\105\130\164\144\141\164\145\072\143\162\145\141\164\145\000\062"
  "\060\062\066\055\060\071\055\062\065\124\060\062\072\063\063\072"
  "\060\067\053\060\060\072\060\060\331\145\272\271\000\000\000\045"
  "\164\105\130\164\144\141\164\145\072\155\157\144\151\146\171\000"
  "\062\060\062\066\055\060\071\055\062\065\124\060\062\072\063\063"
  "\072\060\067\053\060\060\072\060\060\250\070\002\005\000\000\000"
  "\050\164\105\130\164\144\141\164\145\072\164\151\155\145\163\164"
  "\141\155\160\000\062\060\062\066\055\060\071\055\062\065\124\060"
  "\062\072\063\063\072\061\070\053\060\060\072\060\060\305\317\123"
  "\255\000\000\000\000\111\105\116\104\256\102\140\202\000\000\050"
  "\165\165\141\171\051\155\171\137\160\162\157\171\145\143\164\163"
  "\057\000\000\000\000\000\000\000\150\151\143\157\154\157\162\057"
  "\007\000\000\000\150\157\155\145\057\000\000\000\010\000\000\000"
  "\057\000\000\000\004\000\000\000\064\070\170\064\070\057\000\000"
  "\001\000\000\000\141\160\160\163\057\000\000\000\006\000\000\000"
  "\141\156\141\143\150\165\162\151\057\000\000\000\002\000\000\000"
  "" };

static GStaticResource static_resource = { _resource_data.data, sizeof (_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *_get_resource (void);
GResource *_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
