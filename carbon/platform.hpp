// file      : carbon/platform.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

//   _____  _       _    __
//  |  __ \| |     | |  / _|
//  | |__) | | __ _| |_| |_ ___  _ __ _ __ ___
//  |  ___/| |/ _` | __|  _/ _ \| '__| '_ ` _ \.
//  | |    | | (_| | |_| || (_) | |  | | | | | |
//  |_|    |_|\__,_|\__|_| \___/|_|  |_| |_| |_|
//

#define CARBON_PLATFORM_UNKNOWN  0x00000000

#define CARBON_PLATFORM_WINDOWS  0x00010000
#define CARBON_PLATFORM_LINUX    0x00020000
#define CARBON_PLATFORM_APPLE    0x00040000
#define CARBON_PLATFORM_ANDROID  0x00100000
#define CARBON_PLATFORM_NATIVE   0x00200000
#define CARBON_PLATFORM_UNIX     0x00400000
#define CARBON_PLATFORM_WINCE    0x01000000
#define CARBON_PLATFORM_CYGWIN   0x02000000

#if defined(_WIN32)
#	define CARBON_PLATFORM CARBON_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#	define CARBON_PLATFORM CARBON_PLATFORM_APPLE
#elif defined(__ANDROID__)
#	define CARBON_PLATFORM CARBON_PLATFORM_ANDROID
#elif defined(__linux)
#	define CARBON_PLATFORM CARBON_PLATFORM_LINUX
#elif defined(__native_client__)
#	define CARBON_PLATFORM CARBON_PLATFORM_NATIVE
#elif defined(WINCE)
#	define CARBON_PLATFORM CARBON_PLATFORM_WINCE
#elif defined(__CYGWIN__)
#	define CARBON_PLATFORM CARBON_PLATFORM_CYGWIN
#elif defined(__unix)
#	define CARBON_PLATFORM CARBON_PLATFORM_UNIX
#else
#	define CARBON_PLATFORM CARBON_PLATFORM_UNKNOWN
#endif

//    _____                      _ _
//   / ____|                    (_) |
//  | |     ___  _ __ ___  _ __  _| | ___ _ __
//  | |    / _ \| '_ ` _ \| '_ \| | |/ _ \ '__|
//  | |___| (_) | | | | | | |_) | | |  __/ |
//   \_____\___/|_| |_| |_| .__/|_|_|\___|_|
//                        | |
//                        |_|

#define CARBON_COMPILER_UNKNOWN  0x00000000

// --------------
// - Visual C++ -
// --------------

#define CARBON_COMPILER_VC      0x01000000
#define CARBON_COMPILER_VC14    0x01000001
#define CARBON_COMPILER_VC15    0x01000002
#define CARBON_COMPILER_VC15_3  0x01000003
#define CARBON_COMPILER_VC15_5  0x01000004
#define CARBON_COMPILER_VC15_6  0x01000005
#define CARBON_COMPILER_VC15_7  0x01000006
#define CARBON_COMPILER_VC15_8  0x01000007
#define CARBON_COMPILER_VC15_9  0x01000008
#define CARBON_COMPILER_VC16    0x01000009

// -------
// - GCC -
// -------

#define CARBON_COMPILER_GCC    0x02000000
#define CARBON_COMPILER_GCC46  0x020000D0
#define CARBON_COMPILER_GCC47  0x020000E0
#define CARBON_COMPILER_GCC48  0x020000F0
#define CARBON_COMPILER_GCC49  0x02000100
#define CARBON_COMPILER_GCC5   0x02000200
#define CARBON_COMPILER_GCC6   0x02000300
#define CARBON_COMPILER_GCC7   0x02000400
#define CARBON_COMPILER_GCC8   0x02000500

// ---------
// - Clang -
// ---------

#define CARBON_COMPILER_CLANG    0x20000000
#define CARBON_COMPILER_CLANG34  0x20000050
#define CARBON_COMPILER_CLANG35  0x20000060
#define CARBON_COMPILER_CLANG36  0x20000070
#define CARBON_COMPILER_CLANG37  0x20000080
#define CARBON_COMPILER_CLANG38  0x20000090
#define CARBON_COMPILER_CLANG39  0x200000A0
#define CARBON_COMPILER_CLANG40  0x200000B0
#define CARBON_COMPILER_CLANG41  0x200000C0
#define CARBON_COMPILER_CLANG42  0x200000D0

// Visual C++
// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=vs-2019
#if defined(_MSC_VER)
#	if _MSC_VER >= 1920
#		define CARBON_COMPILER CARBON_COMPILER_VC16
#	elif _MSC_VER >= 1916
#		define CARBON_COMPILER CARBON_COMPILER_VC15_9
#	elif _MSC_VER >= 1915
#		define CARBON_COMPILER CARBON_COMPILER_VC15_8
#	elif _MSC_VER >= 1914
#		define CARBON_COMPILER CARBON_COMPILER_VC15_7
#	elif _MSC_VER >= 1913
#		define CARBON_COMPILER CARBON_COMPILER_VC15_6
#	elif _MSC_VER >= 1912
#		define CARBON_COMPILER CARBON_COMPILER_VC15_5
#	elif _MSC_VER >= 1911
#		define CARBON_COMPILER CARBON_COMPILER_VC15_3
#	elif _MSC_VER >= 1910
#		define CARBON_COMPILER CARBON_COMPILER_VC15
#	elif _MSC_VER >= 1900
#		define CARBON_COMPILER CARBON_COMPILER_VC14
#	elif _MSC_VER < 1900
#		error "Carbon Engine requires Visual C++ 14 (2015) or higher"
#	endif

// GNU C Compiler (GCC or G++)
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros
#elif defined(__GNUC__) || defined(__MINGW32__)
#	if __GNUC__ >= 8
#		define CARBON_COMPILER CARBON_COMPILER_GCC8
#	elif __GNUC__ >= 7
#		define CARBON_COMPILER CARBON_COMPILER_GCC7
#	elif __GNUC__ >= 6
#		define CARBON_COMPILER CARBON_COMPILER_GCC6
#	elif __GNUC__ >= 5
#		define CARBON_COMPILER CARBON_COMPILER_GCC5
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 9
#		define CARBON_COMPILER CARBON_COMPILER_GCC49
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 8
#		define CARBON_COMPILER CARBON_COMPILER_GCC48
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 7
#		define CARBON_COMPILER CARBON_COMPILER_GCC47
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 6
#		define CARBON_COMPILER CARBON_COMPILER_GCC46
#	elif ((__GNUC__ == 4) && (__GNUC_MINOR__ < 6)) || (__GNUC__ < 4)
#		error "Carbon Engine requires GCC v4.6 or higher"
#	endif

// Clang
// https://sourceforge.net/p/predef/wiki/Compilers/
#elif defined(__clang__)
#	if defined(__apple_build_version__)
#		if (__clang_major__ < 6)
#			error "Carbon Engine requires Clang v3.4 / Apple Clang v6.0 or higher"
#		elif __clang_major__ == 6 && __clang_minor__ == 0
#			define CARBON_COMPILER CARBON_COMPILER_CLANG35
#		elif __clang_major__ == 6 && __clang_minor__ >= 1
#			define CARBON_COMPILER CARBON_COMPILER_CLANG36
#		elif __clang_major__ >= 7
#			define CARBON_COMPILER CARBON_COMPILER_CLANG37
#		endif
#	else
#		if ((__clang_major__ == 3) && (__clang_minor__ < 4)) || (__clang_major__ < 3)
#			error "Carbon Engine requires Clang v3.4 or higher"
#		elif __clang_major__ == 3 && __clang_minor__ == 4
#			define CARBON_COMPILER CARBON_COMPILER_CLANG34
#		elif __clang_major__ == 3 && __clang_minor__ == 5
#			define CARBON_COMPILER CARBON_COMPILER_CLANG35
#		elif __clang_major__ == 3 && __clang_minor__ == 6
#			define CARBON_COMPILER CARBON_COMPILER_CLANG36
#		elif __clang_major__ == 3 && __clang_minor__ == 7
#			define CARBON_COMPILER CARBON_COMPILER_CLANG37
#		elif __clang_major__ == 3 && __clang_minor__ == 8
#			define CARBON_COMPILER CARBON_COMPILER_CLANG38
#		elif __clang_major__ == 3 && __clang_minor__ >= 9
#			define CARBON_COMPILER CARBON_COMPILER_CLANG39
#		elif __clang_major__ == 4 && __clang_minor__ == 0
#			define CARBON_COMPILER CARBON_COMPILER_CLANG40
#		elif __clang_major__ == 4 && __clang_minor__ == 1
#			define CARBON_COMPILER CARBON_COMPILER_CLANG41
#		elif __clang_major__ == 4 && __clang_minor__ >= 2
#			define CARBON_COMPILER CARBON_COMPILER_CLANG42
#		elif __clang_major__ >= 4
#			define CARBON_COMPILER CARBON_COMPILER_CLANG42
#		endif
#	endif

// unknown compiler
#else
#	define CARBON_COMPILER CARBON_COMPILER_UNKNOWN
#	error "Carbon Engine could not detect your compiler, aborting ..."
#endif

#endif // PLATFORM_HPP