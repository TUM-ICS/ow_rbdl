/*
 * RBDL - Rigid Body Dynamics Library
 * Copyright (c) 2011-2012 Martin Felis <martin.felis@iwr.uni-heidelberg.de>
 *
 * Licensed under the zlib license. See LICENSE for more details.
 */

#ifndef OW_RBDL_CONFIG_H
#define OW_RBDL_CONFIG_H

namespace ow_rbdl{

#define OW_RBDL_API_VERSION (2 << 16) + (4 << 8) + 0

/* #undef OW_RBDL_USE_SIMPLE_MATH */
/* #undef OW_RBDL_ENABLE_LOGGING */
#define OW_RBDL_BUILD_REVISION "unknown"
#define OW_RBDL_BUILD_TYPE "unknown"
#define OW_RBDL_BUILD_BRANCH "unknown"
/* #undef OW_RBDL_BUILD_ADDON_LUAMODEL */
#define OW_RBDL_BUILD_ADDON_URDFREADER
/* #undef OW_RBDL_BUILD_STATIC */
#define OW_RBDL_USE_ROS_URDF_LIBRARY

/* compatibility defines */
#ifdef _WIN32
	#define __func__ __FUNCTION__
	#define M_PI 3.1415926535897932384
#endif

// Handle portable symbol export.
// Defining manually which symbol should be exported is required
// under Windows whether MinGW or MSVC is used.
//
// The headers then have to be able to work in two different modes:
// - dllexport when one is building the library,
// - dllimport for clients using the library.
//
// On Linux, set the visibility accordingly. If C++ symbol visibility
// is handled by the compiler, see: http://gcc.gnu.org/wiki/Visibility
# if defined _WIN32 || defined __CYGWIN__
// On Microsoft Windows, use dllimport and dllexport to tag symbols.
#  define OW_RBDL_DLLIMPORT __declspec(dllimport)
#  define OW_RBDL_DLLEXPORT __declspec(dllexport)
#  define OW_RBDL_DLLLOCAL
# else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#   define OW_RBDL_DLLIMPORT __attribute__ ((visibility("default")))
#   define OW_RBDL_DLLEXPORT __attribute__ ((visibility("default")))
#   define OW_RBDL_DLLLOCAL  __attribute__ ((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#   define OW_RBDL_DLLIMPORT
#   define OW_RBDL_DLLEXPORT
#   define OW_RBDL_DLLLOCAL
#  endif // __GNUC__ >= 4
# endif // defined _WIN32 || defined __CYGWIN__

# ifdef OW_RBDL_BUILD_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define OW_RBDL_DLLAPI
#  define OW_RBDL_LOCAL
# else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef rbdl_EXPORTS
#   define OW_RBDL_DLLAPI OW_RBDL_DLLEXPORT
#  else
#   define OW_RBDL_DLLAPI OW_RBDL_DLLIMPORT
#  endif // OW_RBDL_EXPORTS
#  define OW_RBDL_LOCAL OW_RBDL_DLLLOCAL
# endif // OW_RBDL_BUILD_STATIC

}
#endif
