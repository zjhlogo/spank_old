/*!
 * \file BaseType.h
 * \date 7-20-2011 9:33:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BASETYPE_H__
#define __BASETYPE_H__

#ifndef WIN32
	#include <stdint.h>
#endif

//typedef bool						bool;

//typedef char						char;
typedef unsigned char				uchar;

//typedef short						short;
typedef unsigned short				ushort;

//typedef int						int;
typedef unsigned int				uint;

#ifndef WIN32
	typedef int64_t					int64;
	typedef uint64_t				uint64;
#else
	typedef __int64					int64;
	typedef unsigned __int64		uint64;
#endif

//typedef float						float;

//typedef NULL						NULL;

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}
#define SAFE_DELETE_ARRAY(x) if (x) {delete[] (x); (x) = NULL;}
#define SAFE_RELEASE(x) if (x) {(x)->Release(); (x) = NULL;}

#endif // __BASETYPE_H__
