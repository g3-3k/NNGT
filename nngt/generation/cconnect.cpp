
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03020000)
    #error Cython requires Python 2.6+ or Python 3.2+.
#else
#define CYTHON_ABI "0_25_2"
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef HAVE_LONG_LONG
  #if PY_VERSION_HEX >= 0x03030000 || (PY_MAJOR_VERSION == 2 && PY_VERSION_HEX >= 0x02070000)
    #define HAVE_LONG_LONG
  #endif
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #undef CYTHON_USE_TYPE_SLOTS
  #define CYTHON_USE_TYPE_SLOTS 0
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #undef CYTHON_USE_UNICODE_INTERNALS
  #define CYTHON_USE_UNICODE_INTERNALS 0
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #undef CYTHON_AVOID_BORROWED_REFS
  #define CYTHON_AVOID_BORROWED_REFS 1
  #undef CYTHON_ASSUME_SAFE_MACROS
  #define CYTHON_ASSUME_SAFE_MACROS 0
  #undef CYTHON_UNPACK_METHODS
  #define CYTHON_UNPACK_METHODS 0
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
#elif defined(PYSTON_VERSION)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #if PY_MAJOR_VERSION < 3
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYLONG_INTERNALS
    #define CYTHON_USE_PYLONG_INTERNALS 0
  #elif !defined(CYTHON_USE_PYLONG_INTERNALS)
    #define CYTHON_USE_PYLONG_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_PYLIST_INTERNALS
    #define CYTHON_USE_PYLIST_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #if PY_VERSION_HEX < 0x030300F0
    #undef CYTHON_USE_UNICODE_WRITER
    #define CYTHON_USE_UNICODE_WRITER 0
  #elif !defined(CYTHON_USE_UNICODE_WRITER)
    #define CYTHON_USE_UNICODE_WRITER 1
  #endif
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #ifndef CYTHON_FAST_THREAD_STATE
    #define CYTHON_FAST_THREAD_STATE 1
  #endif
  #ifndef CYTHON_FAST_PYCALL
    #define CYTHON_FAST_PYCALL 1
  #endif
#endif
#if !defined(CYTHON_FAST_PYCCALL)
#define CYTHON_FAST_PYCCALL  (CYTHON_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
  #undef SHIFT
  #undef BASE
  #undef MASK
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
  #define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#ifndef METH_FASTCALL
  #define METH_FASTCALL 0x80
  typedef PyObject *(*__Pyx_PyCFunctionFast) (PyObject *self, PyObject **args,
                                              Py_ssize_t nargs, PyObject *kwnames);
#else
  #define __Pyx_PyCFunctionFast _PyCFunctionFast
#endif
#if CYTHON_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func)\
    ((PyCFunction_Check(func) && (METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   PyUnicode_MAX_CHAR_VALUE(u)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  PyUnicode_WRITE(k, d, i, ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
#else
  #define CYTHON_PEP393_ENABLED 0
  #define PyUnicode_1BYTE_KIND  1
  #define PyUnicode_2BYTE_KIND  2
  #define PyUnicode_4BYTE_KIND  4
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  (((void)(k)), ((Py_UNICODE*)d)[i] = ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#if CYTHON_COMPILING_IN_PYSTON
  #define __Pyx_PyCode_HasFreeVars(co)  PyCode_HasFreeVars(co)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno) PyFrame_SetLineNumber(frame, lineno)
#else
  #define __Pyx_PyCode_HasFreeVars(co)  (PyCode_GetNumFree(co) > 0)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno)  (frame)->f_lineno = (lineno)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if CYTHON_USE_ASYNC_SLOTS
  #if PY_VERSION_HEX >= 0x030500B1
    #define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
    #define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
  #else
    typedef struct {
        unaryfunc am_await;
        unaryfunc am_aiter;
        unaryfunc am_anext;
    } __Pyx_PyAsyncMethodsStruct;
    #define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
  #endif
#else
  #define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_MAYBE_UNUSED_VAR
#  if defined(__cplusplus)
     template<class T> void CYTHON_MAYBE_UNUSED_VAR( const T& ) { }
#  else
#    define CYTHON_MAYBE_UNUSED_VAR(x) (void)(x)
#  endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)

#ifndef __cplusplus
  #error "Cython files generated with the C++ option must be compiled with a C++ compiler."
#endif
#ifndef CYTHON_INLINE
  #if defined(__clang__)
    #define CYTHON_INLINE __inline__ __attribute__ ((__unused__))
  #else
    #define CYTHON_INLINE inline
  #endif
#endif
template<typename T>
void __Pyx_call_destructor(T& x) {
    x.~T();
}
template<typename T>
class __Pyx_FakeReference {
  public:
    __Pyx_FakeReference() : ptr(NULL) { }
    __Pyx_FakeReference(const T& ref) : ptr(const_cast<T*>(&ref)) { }
    T *operator->() { return ptr; }
    T *operator&() { return ptr; }
    operator T&() { return *ptr; }
    template<typename U> bool operator ==(U other) { return *ptr == other; }
    template<typename U> bool operator !=(U other) { return *ptr != other; }
  private:
    T *ptr;
};

#if defined(WIN32) || defined(MS_WINDOWS)
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif


#define __PYX_ERR(f_index, lineno, Ln_error) \
{ \
  __pyx_filename = __pyx_f[f_index]; __pyx_lineno = lineno; __pyx_clineno = __LINE__; goto Ln_error; \
}

#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__nngt__generation__cconnect
#define __PYX_HAVE_API__nngt__generation__cconnect
#include <vector>
#include "ios"
#include "new"
#include "stdexcept"
#include "typeinfo"
#include <string.h>
#include <string>
#include "func_connect.h"
#include <stdio.h>
#include <stdlib.h>
#include "numpy/arrayobject.h"
#include "numpy/ufuncobject.h"
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER) && defined (_M_X64)
    #define __Pyx_sst_abs(value) _abs64(value)
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;

/* Header.proto */
#if !defined(CYTHON_CCOMPLEX)
  #if defined(__cplusplus)
    #define CYTHON_CCOMPLEX 1
  #elif defined(_Complex_I)
    #define CYTHON_CCOMPLEX 1
  #else
    #define CYTHON_CCOMPLEX 0
  #endif
#endif
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #include <complex>
  #else
    #include <complex.h>
  #endif
#endif
#if CYTHON_CCOMPLEX && !defined(__cplusplus) && defined(__sun__) && defined(__GNUC__)
  #undef _Complex_I
  #define _Complex_I 1.0fj
#endif


static const char *__pyx_f[] = {
  "nngt/generation/cconnect.pyx",
  "__init__.pxd",
  "stringsource",
  "type.pxd",
};
/* BufferFormatStructs.proto */
#define IS_UNSIGNED(type) (((type) -1) > 0)
struct __Pyx_StructField_;
#define __PYX_BUF_FLAGS_PACKED_STRUCT (1 << 0)
typedef struct {
  const char* name;
  struct __Pyx_StructField_* fields;
  size_t size;
  size_t arraysize[8];
  int ndim;
  char typegroup;
  char is_unsigned;
  int flags;
} __Pyx_TypeInfo;
typedef struct __Pyx_StructField_ {
  __Pyx_TypeInfo* type;
  const char* name;
  size_t offset;
} __Pyx_StructField;
typedef struct {
  __Pyx_StructField* field;
  size_t parent_offset;
} __Pyx_BufFmt_StackElem;
typedef struct {
  __Pyx_StructField root;
  __Pyx_BufFmt_StackElem* head;
  size_t fmt_offset;
  size_t new_count, enc_count;
  size_t struct_alignment;
  int is_complex;
  char enc_type;
  char new_packmode;
  char enc_packmode;
  char is_valid_array;
} __Pyx_BufFmt_Context;


/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":725
 * # in Cython to enable them only on the right systems.
 * 
 * ctypedef npy_int8       int8_t             # <<<<<<<<<<<<<<
 * ctypedef npy_int16      int16_t
 * ctypedef npy_int32      int32_t
 */
typedef npy_int8 __pyx_t_5numpy_int8_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":726
 * 
 * ctypedef npy_int8       int8_t
 * ctypedef npy_int16      int16_t             # <<<<<<<<<<<<<<
 * ctypedef npy_int32      int32_t
 * ctypedef npy_int64      int64_t
 */
typedef npy_int16 __pyx_t_5numpy_int16_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":727
 * ctypedef npy_int8       int8_t
 * ctypedef npy_int16      int16_t
 * ctypedef npy_int32      int32_t             # <<<<<<<<<<<<<<
 * ctypedef npy_int64      int64_t
 * #ctypedef npy_int96      int96_t
 */
typedef npy_int32 __pyx_t_5numpy_int32_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":728
 * ctypedef npy_int16      int16_t
 * ctypedef npy_int32      int32_t
 * ctypedef npy_int64      int64_t             # <<<<<<<<<<<<<<
 * #ctypedef npy_int96      int96_t
 * #ctypedef npy_int128     int128_t
 */
typedef npy_int64 __pyx_t_5numpy_int64_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":732
 * #ctypedef npy_int128     int128_t
 * 
 * ctypedef npy_uint8      uint8_t             # <<<<<<<<<<<<<<
 * ctypedef npy_uint16     uint16_t
 * ctypedef npy_uint32     uint32_t
 */
typedef npy_uint8 __pyx_t_5numpy_uint8_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":733
 * 
 * ctypedef npy_uint8      uint8_t
 * ctypedef npy_uint16     uint16_t             # <<<<<<<<<<<<<<
 * ctypedef npy_uint32     uint32_t
 * ctypedef npy_uint64     uint64_t
 */
typedef npy_uint16 __pyx_t_5numpy_uint16_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":734
 * ctypedef npy_uint8      uint8_t
 * ctypedef npy_uint16     uint16_t
 * ctypedef npy_uint32     uint32_t             # <<<<<<<<<<<<<<
 * ctypedef npy_uint64     uint64_t
 * #ctypedef npy_uint96     uint96_t
 */
typedef npy_uint32 __pyx_t_5numpy_uint32_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":735
 * ctypedef npy_uint16     uint16_t
 * ctypedef npy_uint32     uint32_t
 * ctypedef npy_uint64     uint64_t             # <<<<<<<<<<<<<<
 * #ctypedef npy_uint96     uint96_t
 * #ctypedef npy_uint128    uint128_t
 */
typedef npy_uint64 __pyx_t_5numpy_uint64_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":739
 * #ctypedef npy_uint128    uint128_t
 * 
 * ctypedef npy_float32    float32_t             # <<<<<<<<<<<<<<
 * ctypedef npy_float64    float64_t
 * #ctypedef npy_float80    float80_t
 */
typedef npy_float32 __pyx_t_5numpy_float32_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":740
 * 
 * ctypedef npy_float32    float32_t
 * ctypedef npy_float64    float64_t             # <<<<<<<<<<<<<<
 * #ctypedef npy_float80    float80_t
 * #ctypedef npy_float128   float128_t
 */
typedef npy_float64 __pyx_t_5numpy_float64_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":749
 * # The int types are mapped a bit surprising --
 * # numpy.int corresponds to 'l' and numpy.long to 'q'
 * ctypedef npy_long       int_t             # <<<<<<<<<<<<<<
 * ctypedef npy_longlong   long_t
 * ctypedef npy_longlong   longlong_t
 */
typedef npy_long __pyx_t_5numpy_int_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":750
 * # numpy.int corresponds to 'l' and numpy.long to 'q'
 * ctypedef npy_long       int_t
 * ctypedef npy_longlong   long_t             # <<<<<<<<<<<<<<
 * ctypedef npy_longlong   longlong_t
 * 
 */
typedef npy_longlong __pyx_t_5numpy_long_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":751
 * ctypedef npy_long       int_t
 * ctypedef npy_longlong   long_t
 * ctypedef npy_longlong   longlong_t             # <<<<<<<<<<<<<<
 * 
 * ctypedef npy_ulong      uint_t
 */
typedef npy_longlong __pyx_t_5numpy_longlong_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":753
 * ctypedef npy_longlong   longlong_t
 * 
 * ctypedef npy_ulong      uint_t             # <<<<<<<<<<<<<<
 * ctypedef npy_ulonglong  ulong_t
 * ctypedef npy_ulonglong  ulonglong_t
 */
typedef npy_ulong __pyx_t_5numpy_uint_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":754
 * 
 * ctypedef npy_ulong      uint_t
 * ctypedef npy_ulonglong  ulong_t             # <<<<<<<<<<<<<<
 * ctypedef npy_ulonglong  ulonglong_t
 * 
 */
typedef npy_ulonglong __pyx_t_5numpy_ulong_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":755
 * ctypedef npy_ulong      uint_t
 * ctypedef npy_ulonglong  ulong_t
 * ctypedef npy_ulonglong  ulonglong_t             # <<<<<<<<<<<<<<
 * 
 * ctypedef npy_intp       intp_t
 */
typedef npy_ulonglong __pyx_t_5numpy_ulonglong_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":757
 * ctypedef npy_ulonglong  ulonglong_t
 * 
 * ctypedef npy_intp       intp_t             # <<<<<<<<<<<<<<
 * ctypedef npy_uintp      uintp_t
 * 
 */
typedef npy_intp __pyx_t_5numpy_intp_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":758
 * 
 * ctypedef npy_intp       intp_t
 * ctypedef npy_uintp      uintp_t             # <<<<<<<<<<<<<<
 * 
 * ctypedef npy_double     float_t
 */
typedef npy_uintp __pyx_t_5numpy_uintp_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":760
 * ctypedef npy_uintp      uintp_t
 * 
 * ctypedef npy_double     float_t             # <<<<<<<<<<<<<<
 * ctypedef npy_double     double_t
 * ctypedef npy_longdouble longdouble_t
 */
typedef npy_double __pyx_t_5numpy_float_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":761
 * 
 * ctypedef npy_double     float_t
 * ctypedef npy_double     double_t             # <<<<<<<<<<<<<<
 * ctypedef npy_longdouble longdouble_t
 * 
 */
typedef npy_double __pyx_t_5numpy_double_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":762
 * ctypedef npy_double     float_t
 * ctypedef npy_double     double_t
 * ctypedef npy_longdouble longdouble_t             # <<<<<<<<<<<<<<
 * 
 * ctypedef npy_cfloat      cfloat_t
 */
typedef npy_longdouble __pyx_t_5numpy_longdouble_t;
/* Declarations.proto */
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< float > __pyx_t_float_complex;
  #else
    typedef float _Complex __pyx_t_float_complex;
  #endif
#else
    typedef struct { float real, imag; } __pyx_t_float_complex;
#endif
static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float, float);

/* Declarations.proto */
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    typedef ::std::complex< double > __pyx_t_double_complex;
  #else
    typedef double _Complex __pyx_t_double_complex;
  #endif
#else
    typedef struct { double real, imag; } __pyx_t_double_complex;
#endif
static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double, double);


/*--- Type declarations ---*/

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":764
 * ctypedef npy_longdouble longdouble_t
 * 
 * ctypedef npy_cfloat      cfloat_t             # <<<<<<<<<<<<<<
 * ctypedef npy_cdouble     cdouble_t
 * ctypedef npy_clongdouble clongdouble_t
 */
typedef npy_cfloat __pyx_t_5numpy_cfloat_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":765
 * 
 * ctypedef npy_cfloat      cfloat_t
 * ctypedef npy_cdouble     cdouble_t             # <<<<<<<<<<<<<<
 * ctypedef npy_clongdouble clongdouble_t
 * 
 */
typedef npy_cdouble __pyx_t_5numpy_cdouble_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":766
 * ctypedef npy_cfloat      cfloat_t
 * ctypedef npy_cdouble     cdouble_t
 * ctypedef npy_clongdouble clongdouble_t             # <<<<<<<<<<<<<<
 * 
 * ctypedef npy_cdouble     complex_t
 */
typedef npy_clongdouble __pyx_t_5numpy_clongdouble_t;

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":768
 * ctypedef npy_clongdouble clongdouble_t
 * 
 * ctypedef npy_cdouble     complex_t             # <<<<<<<<<<<<<<
 * 
 * cdef inline object PyArray_MultiIterNew1(a):
 */
typedef npy_cdouble __pyx_t_5numpy_complex_t;

/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyObjectGetAttrStr.proto */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* GetModuleGlobalName.proto */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

/* PyCFunctionFastCall.proto */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func, PyObject **args, Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs)  (assert(0), NULL)
#endif

/* PyFunctionFastCall.proto */
#if CYTHON_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs)\
    __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, int nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#endif

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

/* RaiseArgTupleInvalid.proto */
static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found);

/* RaiseDoubleKeywords.proto */
static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name);

/* ParseKeywords.proto */
static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[],\
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args,\
    const char* function_name);

/* ArgTypeTest.proto */
static CYTHON_INLINE int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact);

/* BufferFormatCheck.proto */
static CYTHON_INLINE int  __Pyx_GetBufferAndValidate(Py_buffer* buf, PyObject* obj,
    __Pyx_TypeInfo* dtype, int flags, int nd, int cast, __Pyx_BufFmt_StackElem* stack);
static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info);
static const char* __Pyx_BufFmt_CheckString(__Pyx_BufFmt_Context* ctx, const char* ts);
static void __Pyx_BufFmt_Init(__Pyx_BufFmt_Context* ctx,
                              __Pyx_BufFmt_StackElem* stack,
                              __Pyx_TypeInfo* type); // PROTO

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* IncludeStringH.proto */
#include <string.h>

/* BytesEquals.proto */
static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals);

/* UnicodeEquals.proto */
static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals);

/* StrEquals.proto */
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Equals __Pyx_PyUnicode_Equals
#else
#define __Pyx_PyString_Equals __Pyx_PyBytes_Equals
#endif

/* ExtTypeTest.proto */
static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type);

#define __Pyx_BufPtrCContig2d(type, buf, i0, s0, i1, s1) ((type)((char*)buf + i0 * s0) + i1)
/* BufferFallbackError.proto */
static void __Pyx_RaiseBufferFallbackError(void);

/* PyThreadStateGet.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = PyThreadState_GET();
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#endif

/* PyErrFetchRestore.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ErrRestoreWithState(type, value, tb)  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)    __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)    __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
#define __Pyx_ErrRestoreWithState(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)  PyErr_Fetch(type, value, tb)
#endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* RaiseTooManyValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

/* RaiseNeedMoreValuesToUnpack.proto */
static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

/* IterFinish.proto */
static CYTHON_INLINE int __Pyx_IterFinish(void);

/* UnpackItemEndCheck.proto */
static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected);

/* PyFloatBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_DivideObjC(PyObject *op1, PyObject *op2, double floatval, int inplace);
#else
#define __Pyx_PyFloat_DivideObjC(op1, op2, floatval, inplace)\
    ((inplace ? __Pyx_PyNumber_InPlaceDivide(op1, op2) : __Pyx_PyNumber_Divide(op1, op2)))
    #endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_SubtractCObj(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_SubtractCObj(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceSubtract(op1, op2) : PyNumber_Subtract(op1, op2))
#endif

/* PyFloatBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_SubtractObjC(PyObject *op1, PyObject *op2, double floatval, int inplace);
#else
#define __Pyx_PyFloat_SubtractObjC(op1, op2, floatval, inplace)\
    (inplace ? PyNumber_InPlaceSubtract(op1, op2) : PyNumber_Subtract(op1, op2))
#endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddCObj(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_AddCObj(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* RaiseException.proto */
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause);

/* DictGetItem.proto */
#if PY_MAJOR_VERSION >= 3 && !CYTHON_COMPILING_IN_PYPY
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key) {
    PyObject *value;
    value = PyDict_GetItemWithError(d, key);
    if (unlikely(!value)) {
        if (!PyErr_Occurred()) {
            PyObject* args = PyTuple_Pack(1, key);
            if (likely(args))
                PyErr_SetObject(PyExc_KeyError, args);
            Py_XDECREF(args);
        }
        return NULL;
    }
    Py_INCREF(value);
    return value;
}
#else
    #define __Pyx_PyDict_GetItem(d, key) PyObject_GetItem(d, key)
#endif

/* RaiseNoneIterError.proto */
static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void);

/* SaveResetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

/* PyErrExceptionMatches.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyErr_ExceptionMatches(err) __Pyx_PyErr_ExceptionMatchesInState(__pyx_tstate, err)
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err);
#else
#define __Pyx_PyErr_ExceptionMatches(err)  PyErr_ExceptionMatches(err)
#endif

/* GetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* ListCompAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_ListComp_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len)) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L,x) PyList_Append(L,x)
#endif

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* CodeObjectCache.proto */
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

/* BufferStructDeclare.proto */
typedef struct {
  Py_ssize_t shape, strides, suboffsets;
} __Pyx_Buf_DimInfo;
typedef struct {
  size_t refcount;
  Py_buffer pybuffer;
} __Pyx_Buffer;
typedef struct {
  __Pyx_Buffer *rcbuffer;
  char *data;
  __Pyx_Buf_DimInfo diminfo[8];
} __Pyx_LocalBuf_ND;

#if PY_MAJOR_VERSION < 3
    static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags);
    static void __Pyx_ReleaseBuffer(Py_buffer *view);
#else
    #define __Pyx_GetBuffer PyObject_GetBuffer
    #define __Pyx_ReleaseBuffer PyBuffer_Release
#endif


/* None.proto */
static Py_ssize_t __Pyx_zeros[] = {0, 0, 0, 0, 0, 0, 0, 0};
static Py_ssize_t __Pyx_minusones[] = {-1, -1, -1, -1, -1, -1, -1, -1};

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_unsigned_int(unsigned int value);

/* CppExceptionConversion.proto */
#ifndef __Pyx_CppExn2PyErr
#include <new>
#include <typeinfo>
#include <stdexcept>
#include <ios>
static void __Pyx_CppExn2PyErr() {
  try {
    if (PyErr_Occurred())
      ; // let the latest Python exn pass through and ignore the current one
    else
      throw;
  } catch (const std::bad_alloc& exn) {
    PyErr_SetString(PyExc_MemoryError, exn.what());
  } catch (const std::bad_cast& exn) {
    PyErr_SetString(PyExc_TypeError, exn.what());
  } catch (const std::bad_typeid& exn) {
    PyErr_SetString(PyExc_TypeError, exn.what());
  } catch (const std::domain_error& exn) {
    PyErr_SetString(PyExc_ValueError, exn.what());
  } catch (const std::invalid_argument& exn) {
    PyErr_SetString(PyExc_ValueError, exn.what());
  } catch (const std::ios_base::failure& exn) {
    PyErr_SetString(PyExc_IOError, exn.what());
  } catch (const std::out_of_range& exn) {
    PyErr_SetString(PyExc_IndexError, exn.what());
  } catch (const std::overflow_error& exn) {
    PyErr_SetString(PyExc_OverflowError, exn.what());
  } catch (const std::range_error& exn) {
    PyErr_SetString(PyExc_ArithmeticError, exn.what());
  } catch (const std::underflow_error& exn) {
    PyErr_SetString(PyExc_ArithmeticError, exn.what());
  } catch (const std::exception& exn) {
    PyErr_SetString(PyExc_RuntimeError, exn.what());
  }
  catch (...)
  {
    PyErr_SetString(PyExc_RuntimeError, "Unknown exception");
  }
}
#endif

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value);

/* RealImag.proto */
#if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    #define __Pyx_CREAL(z) ((z).real())
    #define __Pyx_CIMAG(z) ((z).imag())
  #else
    #define __Pyx_CREAL(z) (__real__(z))
    #define __Pyx_CIMAG(z) (__imag__(z))
  #endif
#else
    #define __Pyx_CREAL(z) ((z).real)
    #define __Pyx_CIMAG(z) ((z).imag)
#endif
#if defined(__cplusplus) && CYTHON_CCOMPLEX\
        && (defined(_WIN32) || defined(__clang__) || (defined(__GNUC__) && (__GNUC__ >= 5 || __GNUC__ == 4 && __GNUC_MINOR__ >= 4 )) || __cplusplus >= 201103)
    #define __Pyx_SET_CREAL(z,x) ((z).real(x))
    #define __Pyx_SET_CIMAG(z,y) ((z).imag(y))
#else
    #define __Pyx_SET_CREAL(z,x) __Pyx_CREAL(z) = (x)
    #define __Pyx_SET_CIMAG(z,y) __Pyx_CIMAG(z) = (y)
#endif

/* Arithmetic.proto */
#if CYTHON_CCOMPLEX
    #define __Pyx_c_eq_float(a, b)   ((a)==(b))
    #define __Pyx_c_sum_float(a, b)  ((a)+(b))
    #define __Pyx_c_diff_float(a, b) ((a)-(b))
    #define __Pyx_c_prod_float(a, b) ((a)*(b))
    #define __Pyx_c_quot_float(a, b) ((a)/(b))
    #define __Pyx_c_neg_float(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zero_float(z) ((z)==(float)0)
    #define __Pyx_c_conj_float(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_abs_float(z)     (::std::abs(z))
        #define __Pyx_c_pow_float(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zero_float(z) ((z)==0)
    #define __Pyx_c_conj_float(z)    (conjf(z))
    #if 1
        #define __Pyx_c_abs_float(z)     (cabsf(z))
        #define __Pyx_c_pow_float(a, b)  (cpowf(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eq_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sum_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_diff_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prod_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex, __pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_neg_float(__pyx_t_float_complex);
    static CYTHON_INLINE int __Pyx_c_is_zero_float(__pyx_t_float_complex);
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conj_float(__pyx_t_float_complex);
    #if 1
        static CYTHON_INLINE float __Pyx_c_abs_float(__pyx_t_float_complex);
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_pow_float(__pyx_t_float_complex, __pyx_t_float_complex);
    #endif
#endif

/* Arithmetic.proto */
#if CYTHON_CCOMPLEX
    #define __Pyx_c_eq_double(a, b)   ((a)==(b))
    #define __Pyx_c_sum_double(a, b)  ((a)+(b))
    #define __Pyx_c_diff_double(a, b) ((a)-(b))
    #define __Pyx_c_prod_double(a, b) ((a)*(b))
    #define __Pyx_c_quot_double(a, b) ((a)/(b))
    #define __Pyx_c_neg_double(a)     (-(a))
  #ifdef __cplusplus
    #define __Pyx_c_is_zero_double(z) ((z)==(double)0)
    #define __Pyx_c_conj_double(z)    (::std::conj(z))
    #if 1
        #define __Pyx_c_abs_double(z)     (::std::abs(z))
        #define __Pyx_c_pow_double(a, b)  (::std::pow(a, b))
    #endif
  #else
    #define __Pyx_c_is_zero_double(z) ((z)==0)
    #define __Pyx_c_conj_double(z)    (conj(z))
    #if 1
        #define __Pyx_c_abs_double(z)     (cabs(z))
        #define __Pyx_c_pow_double(a, b)  (cpow(a, b))
    #endif
 #endif
#else
    static CYTHON_INLINE int __Pyx_c_eq_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex, __pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg_double(__pyx_t_double_complex);
    static CYTHON_INLINE int __Pyx_c_is_zero_double(__pyx_t_double_complex);
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj_double(__pyx_t_double_complex);
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs_double(__pyx_t_double_complex);
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow_double(__pyx_t_double_complex, __pyx_t_double_complex);
    #endif
#endif

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_enum__NPY_TYPES(enum NPY_TYPES value);

/* CIntFromPy.proto */
static CYTHON_INLINE size_t __Pyx_PyInt_As_size_t(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE unsigned int __Pyx_PyInt_As_unsigned_int(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* CStringEquals.proto */
static CYTHON_INLINE int __Pyx_StrEq(const char *, const char *);

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* PyIdentifierFromString.proto */
#if !defined(__Pyx_PyIdentifier_FromString)
#if PY_MAJOR_VERSION < 3
  #define __Pyx_PyIdentifier_FromString(s) PyString_FromString(s)
#else
  #define __Pyx_PyIdentifier_FromString(s) PyUnicode_FromString(s)
#endif
#endif

/* ModuleImport.proto */
static PyObject *__Pyx_ImportModule(const char *name);

/* TypeImport.proto */
static PyTypeObject *__Pyx_ImportType(const char *module_name, const char *class_name, size_t size, int strict);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'libcpp.vector' */

/* Module declarations from 'libc.string' */

/* Module declarations from 'libcpp.string' */

/* Module declarations from 'libcpp' */

/* Module declarations from 'cpython.buffer' */

/* Module declarations from 'libc.stdio' */

/* Module declarations from '__builtin__' */

/* Module declarations from 'cpython.type' */
static PyTypeObject *__pyx_ptype_7cpython_4type_type = 0;

/* Module declarations from 'cpython' */

/* Module declarations from 'cpython.object' */

/* Module declarations from 'cpython.ref' */

/* Module declarations from 'libc.stdlib' */

/* Module declarations from 'numpy' */

/* Module declarations from 'numpy' */
static PyTypeObject *__pyx_ptype_5numpy_dtype = 0;
static PyTypeObject *__pyx_ptype_5numpy_flatiter = 0;
static PyTypeObject *__pyx_ptype_5numpy_broadcast = 0;
static PyTypeObject *__pyx_ptype_5numpy_ndarray = 0;
static PyTypeObject *__pyx_ptype_5numpy_ufunc = 0;
static CYTHON_INLINE char *__pyx_f_5numpy__util_dtypestring(PyArray_Descr *, char *, char *, int *); /*proto*/

/* Module declarations from 'nngt.generation.cconnect' */
static int __pyx_v_4nngt_10generation_8cconnect_MAXTESTS;
static float __pyx_v_4nngt_10generation_8cconnect_EPS;
static PyObject *__pyx_f_4nngt_10generation_8cconnect__to_bytes(PyObject *); /*proto*/
static std::vector<size_t>  __pyx_convert_vector_from_py_size_t(PyObject *); /*proto*/
static PyObject *__pyx_convert_vector_to_py_size_t(const std::vector<size_t>  &); /*proto*/
static std::string __pyx_convert_string_from_py_std__in_string(PyObject *); /*proto*/
static std::vector<double>  __pyx_convert_vector_from_py_double(PyObject *); /*proto*/
static __Pyx_TypeInfo __Pyx_TypeInfo_size_t = { "size_t", NULL, sizeof(size_t), { 0 }, 0, IS_UNSIGNED(size_t) ? 'U' : 'I', IS_UNSIGNED(size_t), 0 };
static __Pyx_TypeInfo __Pyx_TypeInfo_double = { "double", NULL, sizeof(double), { 0 }, 0, 'R', 0, 0 };
#define __Pyx_MODULE_NAME "nngt.generation.cconnect"
int __pyx_module_is_main_nngt__generation__cconnect = 0;

/* Implementation of 'nngt.generation.cconnect' */
static PyObject *__pyx_builtin_ValueError;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_RuntimeError;
static PyObject *__pyx_builtin_ImportError;
static const char __pyx_k_T[] = "T";
static const char __pyx_k_b[] = "b";
static const char __pyx_k_x[] = "x";
static const char __pyx_k_y[] = "y";
static const char __pyx_k_np[] = "np";
static const char __pyx_k__46[] = "*";
static const char __pyx_k__66[] = "_";
static const char __pyx_k_abs[] = "abs";
static const char __pyx_k_all[] = "__all__";
static const char __pyx_k_arr[] = "arr";
static const char __pyx_k_avg[] = "avg";
static const char __pyx_k_idx[] = "idx";
static const char __pyx_k_msd[] = "msd";
static const char __pyx_k_omp[] = "omp";
static const char __pyx_k_out[] = "out";
static const char __pyx_k_ssp[] = "ssp";
static const char __pyx_k_std[] = "std";
static const char __pyx_k_sum[] = "sum";
static const char __pyx_k_area[] = "area";
static const char __pyx_k_dist[] = "dist";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_nngt[] = "nngt";
static const char __pyx_k_rule[] = "rule";
static const char __pyx_k_seed[] = "seed";
static const char __pyx_k_sign[] = "sign";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_tile[] = "tile";
static const char __pyx_k_uint[] = "uint";
static const char __pyx_k_view[] = "view";
static const char __pyx_k_void[] = "void";
static const char __pyx_k_DTYPE[] = "DTYPE";
static const char __pyx_k_UTF_8[] = "UTF-8";
static const char __pyx_k_array[] = "array";
static const char __pyx_k_b_out[] = "b_out";
static const char __pyx_k_crule[] = "crule";
static const char __pyx_k_dtype[] = "dtype";
static const char __pyx_k_edges[] = "edges";
static const char __pyx_k_floor[] = "floor";
static const char __pyx_k_nodes[] = "nodes";
static const char __pyx_k_numpy[] = "numpy";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_scale[] = "scale";
static const char __pyx_k_shape[] = "shape";
static const char __pyx_k_total[] = "total";
static const char __pyx_k_zeros[] = "zeros";
static const char __pyx_k_arange[] = "arange";
static const char __pyx_k_around[] = "around";
static const char __pyx_k_astype[] = "astype";
static const char __pyx_k_cedges[] = "cedges";
static const char __pyx_k_config[] = "config";
static const char __pyx_k_degree[] = "degree";
static const char __pyx_k_filter[] = "_filter";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_in_exp[] = "in_exp";
static const char __pyx_k_kwargs[] = "kwargs";
static const char __pyx_k_normal[] = "normal";
static const char __pyx_k_pareto[] = "pareto";
static const char __pyx_k_random[] = "random";
static const char __pyx_k_repeat[] = "repeat";
static const char __pyx_k_sum_in[] = "sum_in";
static const char __pyx_k_unique[] = "unique";
static const char __pyx_k_avg_deg[] = "avg_deg";
static const char __pyx_k_b_total[] = "b_total";
static const char __pyx_k_degrees[] = "degrees";
static const char __pyx_k_density[] = "density";
static const char __pyx_k_diff_in[] = "diff_in";
static const char __pyx_k_ia_base[] = "ia_base";
static const char __pyx_k_maximum[] = "maximum";
static const char __pyx_k_out_exp[] = "out_exp";
static const char __pyx_k_randint[] = "randint";
static const char __pyx_k_reshape[] = "reshape";
static const char __pyx_k_shuffle[] = "shuffle";
static const char __pyx_k_sum_out[] = "sum_out";
static const char __pyx_k_coord_nb[] = "coord_nb";
static const char __pyx_k_diff_out[] = "diff_out";
static const char __pyx_k_directed[] = "directed";
static const char __pyx_k_edge_num[] = "edge_num";
static const char __pyx_k_existing[] = "existing";
static const char __pyx_k_ia_edges[] = "ia_edges";
static const char __pyx_k_itemsize[] = "itemsize";
static const char __pyx_k_multiply[] = "multiply";
static const char __pyx_k_neg_dist[] = "neg_dist";
static const char __pyx_k_nngt_lib[] = "nngt.lib";
static const char __pyx_k_node_ids[] = "node_ids";
static const char __pyx_k_num_node[] = "num_node";
static const char __pyx_k_num_test[] = "num_test";
static const char __pyx_k_pos_dist[] = "pos_dist";
static const char __pyx_k_warnings[] = "warnings";
static const char __pyx_k_b_one_pop[] = "b_one_pop";
static const char __pyx_k_ia_in_deg[] = "ia_in_deg";
static const char __pyx_k_num_added[] = "num_added";
static const char __pyx_k_num_edges[] = "num_edges";
static const char __pyx_k_old_edges[] = "old_edges";
static const char __pyx_k_positions[] = "positions";
static const char __pyx_k_ValueError[] = "ValueError";
static const char __pyx_k_ia_indices[] = "ia_indices";
static const char __pyx_k_ia_out_deg[] = "ia_out_deg";
static const char __pyx_k_ia_sources[] = "ia_sources";
static const char __pyx_k_ia_targets[] = "ia_targets";
static const char __pyx_k_multigraph[] = "multigraph";
static const char __pyx_k_num_source[] = "num_source";
static const char __pyx_k_num_target[] = "num_target";
static const char __pyx_k_source_ids[] = "source_ids";
static const char __pyx_k_target_ids[] = "target_ids";
static const char __pyx_k_ImportError[] = "ImportError";
static const char __pyx_k_concatenate[] = "concatenate";
static const char __pyx_k_degree_type[] = "degree_type";
static const char __pyx_k_erdos_renyi[] = "_erdos_renyi";
static const char __pyx_k_num_desired[] = "num_desired";
static const char __pyx_k_num_neurons[] = "num_neurons";
static const char __pyx_k_reciprocity[] = "reciprocity";
static const char __pyx_k_unique_rows[] = "_unique_rows";
static const char __pyx_k_RuntimeError[] = "RuntimeError";
static const char __pyx_k_cnum_neurons[] = "cnum_neurons";
static const char __pyx_k_fixed_degree[] = "_fixed_degree";
static const char __pyx_k_ia_edges_tmp[] = "ia_edges_tmp";
static const char __pyx_k_newman_watts[] = "_newman_watts";
static const char __pyx_k_num_ecurrent[] = "num_ecurrent";
static const char __pyx_k_numpy_random[] = "numpy.random";
static const char __pyx_k_scipy_sparse[] = "scipy.sparse";
static const char __pyx_k_connect_tools[] = "connect_tools";
static const char __pyx_k_distance_rule[] = "_distance_rule";
static const char __pyx_k_no_self_loops[] = "_no_self_loops";
static const char __pyx_k_price_network[] = "price_network";
static const char __pyx_k_circular_edges[] = "circular_edges";
static const char __pyx_k_circular_graph[] = "_circular_graph";
static const char __pyx_k_existing_edges[] = "existing_edges";
static const char __pyx_k_ia_sources_tmp[] = "ia_sources_tmp";
static const char __pyx_k_ia_targets_tmp[] = "ia_targets_tmp";
static const char __pyx_k_idx_correct_in[] = "idx_correct_in";
static const char __pyx_k_proba_shortcut[] = "proba_shortcut";
static const char __pyx_k_InvalidArgument[] = "InvalidArgument";
static const char __pyx_k_check_num_edges[] = "_check_num_edges";
static const char __pyx_k_gaussian_degree[] = "_gaussian_degree";
static const char __pyx_k_idx_correct_out[] = "idx_correct_out";
static const char __pyx_k_pre_recip_edges[] = "pre_recip_edges";
static const char __pyx_k_price_scale_free[] = "_price_scale_free";
static const char __pyx_k_ascontiguousarray[] = "ascontiguousarray";
static const char __pyx_k_random_scale_free[] = "_random_scale_free";
static const char __pyx_k_compute_connections[] = "_compute_connections";
static const char __pyx_k_nngt_generation_cconnect[] = "nngt.generation.cconnect";
static const char __pyx_k_Generation_tools_for_NNGT[] = " Generation tools for NNGT ";
static const char __pyx_k_ndarray_is_not_C_contiguous[] = "ndarray is not C contiguous";
static const char __pyx_k_home_tfardet_Documents_NNGT_nng[] = "/home/tfardet/Documents/NNGT/nngt/generation/cconnect.pyx";
static const char __pyx_k_numpy_core_multiarray_failed_to[] = "numpy.core.multiarray failed to import";
static const char __pyx_k_unknown_dtype_code_in_numpy_pxd[] = "unknown dtype code in numpy.pxd (%d)";
static const char __pyx_k_Format_string_allocated_too_shor[] = "Format string allocated too short, see comment in numpy.pxd";
static const char __pyx_k_Non_native_byte_order_not_suppor[] = "Non-native byte order not supported";
static const char __pyx_k_This_graph_model_can_only_be_use[] = "This graph model can only be used if source                               and target populations are the same";
static const char __pyx_k_ndarray_is_not_Fortran_contiguou[] = "ndarray is not Fortran contiguous";
static const char __pyx_k_numpy_core_umath_failed_to_impor[] = "numpy.core.umath failed to import";
static const char __pyx_k_Format_string_allocated_too_shor_2[] = "Format string allocated too short.";
static PyObject *__pyx_n_s_DTYPE;
static PyObject *__pyx_kp_u_Format_string_allocated_too_shor;
static PyObject *__pyx_kp_u_Format_string_allocated_too_shor_2;
static PyObject *__pyx_n_s_ImportError;
static PyObject *__pyx_n_s_InvalidArgument;
static PyObject *__pyx_kp_u_Non_native_byte_order_not_suppor;
static PyObject *__pyx_n_s_RuntimeError;
static PyObject *__pyx_n_s_T;
static PyObject *__pyx_kp_s_This_graph_model_can_only_be_use;
static PyObject *__pyx_kp_s_UTF_8;
static PyObject *__pyx_n_s_ValueError;
static PyObject *__pyx_n_s__46;
static PyObject *__pyx_n_s__66;
static PyObject *__pyx_n_s_abs;
static PyObject *__pyx_n_s_all;
static PyObject *__pyx_n_s_arange;
static PyObject *__pyx_n_s_area;
static PyObject *__pyx_n_s_around;
static PyObject *__pyx_n_s_arr;
static PyObject *__pyx_n_s_array;
static PyObject *__pyx_n_s_ascontiguousarray;
static PyObject *__pyx_n_s_astype;
static PyObject *__pyx_n_s_avg;
static PyObject *__pyx_n_s_avg_deg;
static PyObject *__pyx_n_s_b;
static PyObject *__pyx_n_s_b_one_pop;
static PyObject *__pyx_n_s_b_out;
static PyObject *__pyx_n_s_b_total;
static PyObject *__pyx_n_s_cedges;
static PyObject *__pyx_n_s_check_num_edges;
static PyObject *__pyx_n_s_circular_edges;
static PyObject *__pyx_n_s_circular_graph;
static PyObject *__pyx_n_s_cnum_neurons;
static PyObject *__pyx_n_s_compute_connections;
static PyObject *__pyx_n_s_concatenate;
static PyObject *__pyx_n_s_config;
static PyObject *__pyx_n_s_connect_tools;
static PyObject *__pyx_n_s_coord_nb;
static PyObject *__pyx_n_s_crule;
static PyObject *__pyx_n_s_degree;
static PyObject *__pyx_n_s_degree_type;
static PyObject *__pyx_n_s_degrees;
static PyObject *__pyx_n_s_density;
static PyObject *__pyx_n_s_diff_in;
static PyObject *__pyx_n_s_diff_out;
static PyObject *__pyx_n_s_directed;
static PyObject *__pyx_n_s_dist;
static PyObject *__pyx_n_s_distance_rule;
static PyObject *__pyx_n_s_dtype;
static PyObject *__pyx_n_s_edge_num;
static PyObject *__pyx_n_s_edges;
static PyObject *__pyx_n_s_erdos_renyi;
static PyObject *__pyx_n_s_existing;
static PyObject *__pyx_n_s_existing_edges;
static PyObject *__pyx_n_s_filter;
static PyObject *__pyx_n_s_fixed_degree;
static PyObject *__pyx_n_s_floor;
static PyObject *__pyx_n_s_gaussian_degree;
static PyObject *__pyx_kp_s_home_tfardet_Documents_NNGT_nng;
static PyObject *__pyx_n_s_ia_base;
static PyObject *__pyx_n_s_ia_edges;
static PyObject *__pyx_n_s_ia_edges_tmp;
static PyObject *__pyx_n_s_ia_in_deg;
static PyObject *__pyx_n_s_ia_indices;
static PyObject *__pyx_n_s_ia_out_deg;
static PyObject *__pyx_n_s_ia_sources;
static PyObject *__pyx_n_s_ia_sources_tmp;
static PyObject *__pyx_n_s_ia_targets;
static PyObject *__pyx_n_s_ia_targets_tmp;
static PyObject *__pyx_n_s_idx;
static PyObject *__pyx_n_s_idx_correct_in;
static PyObject *__pyx_n_s_idx_correct_out;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_in_exp;
static PyObject *__pyx_n_s_itemsize;
static PyObject *__pyx_n_s_kwargs;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_maximum;
static PyObject *__pyx_n_s_msd;
static PyObject *__pyx_n_s_multigraph;
static PyObject *__pyx_n_s_multiply;
static PyObject *__pyx_kp_u_ndarray_is_not_C_contiguous;
static PyObject *__pyx_kp_u_ndarray_is_not_Fortran_contiguou;
static PyObject *__pyx_n_s_neg_dist;
static PyObject *__pyx_n_s_newman_watts;
static PyObject *__pyx_n_s_nngt;
static PyObject *__pyx_n_s_nngt_generation_cconnect;
static PyObject *__pyx_n_s_nngt_lib;
static PyObject *__pyx_n_s_no_self_loops;
static PyObject *__pyx_n_s_node_ids;
static PyObject *__pyx_n_s_nodes;
static PyObject *__pyx_n_s_normal;
static PyObject *__pyx_n_s_np;
static PyObject *__pyx_n_s_num_added;
static PyObject *__pyx_n_s_num_desired;
static PyObject *__pyx_n_s_num_ecurrent;
static PyObject *__pyx_n_s_num_edges;
static PyObject *__pyx_n_s_num_neurons;
static PyObject *__pyx_n_s_num_node;
static PyObject *__pyx_n_s_num_source;
static PyObject *__pyx_n_s_num_target;
static PyObject *__pyx_n_s_num_test;
static PyObject *__pyx_n_s_numpy;
static PyObject *__pyx_kp_s_numpy_core_multiarray_failed_to;
static PyObject *__pyx_kp_s_numpy_core_umath_failed_to_impor;
static PyObject *__pyx_n_s_numpy_random;
static PyObject *__pyx_n_s_old_edges;
static PyObject *__pyx_n_s_omp;
static PyObject *__pyx_n_s_out;
static PyObject *__pyx_n_s_out_exp;
static PyObject *__pyx_n_s_pareto;
static PyObject *__pyx_n_s_pos_dist;
static PyObject *__pyx_n_s_positions;
static PyObject *__pyx_n_s_pre_recip_edges;
static PyObject *__pyx_n_s_price_network;
static PyObject *__pyx_n_s_price_scale_free;
static PyObject *__pyx_n_s_proba_shortcut;
static PyObject *__pyx_n_s_randint;
static PyObject *__pyx_n_s_random;
static PyObject *__pyx_n_s_random_scale_free;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_reciprocity;
static PyObject *__pyx_n_s_repeat;
static PyObject *__pyx_n_s_reshape;
static PyObject *__pyx_n_s_rule;
static PyObject *__pyx_n_s_scale;
static PyObject *__pyx_n_s_scipy_sparse;
static PyObject *__pyx_n_s_seed;
static PyObject *__pyx_n_s_shape;
static PyObject *__pyx_n_s_shuffle;
static PyObject *__pyx_n_s_sign;
static PyObject *__pyx_n_s_source_ids;
static PyObject *__pyx_n_s_ssp;
static PyObject *__pyx_n_s_std;
static PyObject *__pyx_n_s_sum;
static PyObject *__pyx_n_s_sum_in;
static PyObject *__pyx_n_s_sum_out;
static PyObject *__pyx_n_s_target_ids;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_tile;
static PyObject *__pyx_n_s_total;
static PyObject *__pyx_n_s_uint;
static PyObject *__pyx_n_s_unique;
static PyObject *__pyx_n_s_unique_rows;
static PyObject *__pyx_kp_u_unknown_dtype_code_in_numpy_pxd;
static PyObject *__pyx_n_s_view;
static PyObject *__pyx_n_s_void;
static PyObject *__pyx_n_s_warnings;
static PyObject *__pyx_n_s_x;
static PyObject *__pyx_n_s_y;
static PyObject *__pyx_n_s_zeros;
static PyObject *__pyx_pf_4nngt_10generation_8cconnect__unique_rows(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_arr); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_2_no_self_loops(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_array); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_4_filter(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_ia_edges, PyObject *__pyx_v_ia_edges_tmp, PyObject *__pyx_v_num_ecurrent, PyObject *__pyx_v_b_one_pop, PyObject *__pyx_v_multigraph); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_6_fixed_degree(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, size_t __pyx_v_degree, PyObject *__pyx_v_degree_type, CYTHON_UNUSED float __pyx_v_reciprocity, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_existing_edges); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_8_gaussian_degree(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, unsigned int __pyx_v_avg, unsigned int __pyx_v_std, PyObject *__pyx_v_degree_type, CYTHON_UNUSED float __pyx_v_reciprocity, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_existing_edges); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_10_random_scale_free(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_in_exp, PyObject *__pyx_v_out_exp, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, PyObject *__pyx_v_reciprocity, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_12_erdos_renyi(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, PyObject *__pyx_v_reciprocity, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_14_price_scale_free(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_16_circular_graph(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_node_ids, PyObject *__pyx_v_coord_nb); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_18_newman_watts(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_coord_nb, PyObject *__pyx_v_proba_shortcut, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_20_distance_rule(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, double __pyx_v_scale, PyObject *__pyx_v_rule, PyObject *__pyx_v_shape, PyArrayObject *__pyx_v_positions, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_num_neurons, CYTHON_UNUSED PyObject *__pyx_v_kwargs); /* proto */
static PyObject *__pyx_pf_4nngt_10generation_8cconnect_22price_network(CYTHON_UNUSED PyObject *__pyx_self); /* proto */
static int __pyx_pf_5numpy_7ndarray___getbuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); /* proto */
static void __pyx_pf_5numpy_7ndarray_2__releasebuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info); /* proto */
static PyObject *__pyx_float_0_;
static PyObject *__pyx_float_2_;
static PyObject *__pyx_float_0_5;
static PyObject *__pyx_float_neg_0_5;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_neg_1;
static PyObject *__pyx_slice_;
static PyObject *__pyx_slice__3;
static PyObject *__pyx_slice__5;
static PyObject *__pyx_slice__6;
static PyObject *__pyx_slice__7;
static PyObject *__pyx_slice__8;
static PyObject *__pyx_slice__9;
static PyObject *__pyx_tuple__2;
static PyObject *__pyx_tuple__4;
static PyObject *__pyx_slice__10;
static PyObject *__pyx_slice__11;
static PyObject *__pyx_slice__13;
static PyObject *__pyx_slice__14;
static PyObject *__pyx_slice__15;
static PyObject *__pyx_slice__17;
static PyObject *__pyx_slice__18;
static PyObject *__pyx_slice__19;
static PyObject *__pyx_slice__20;
static PyObject *__pyx_slice__21;
static PyObject *__pyx_slice__23;
static PyObject *__pyx_slice__24;
static PyObject *__pyx_slice__25;
static PyObject *__pyx_slice__26;
static PyObject *__pyx_slice__27;
static PyObject *__pyx_slice__30;
static PyObject *__pyx_slice__31;
static PyObject *__pyx_slice__32;
static PyObject *__pyx_slice__34;
static PyObject *__pyx_slice__35;
static PyObject *__pyx_tuple__12;
static PyObject *__pyx_tuple__16;
static PyObject *__pyx_tuple__22;
static PyObject *__pyx_tuple__28;
static PyObject *__pyx_tuple__29;
static PyObject *__pyx_tuple__33;
static PyObject *__pyx_tuple__36;
static PyObject *__pyx_tuple__37;
static PyObject *__pyx_tuple__38;
static PyObject *__pyx_tuple__39;
static PyObject *__pyx_tuple__40;
static PyObject *__pyx_tuple__41;
static PyObject *__pyx_tuple__42;
static PyObject *__pyx_tuple__43;
static PyObject *__pyx_tuple__44;
static PyObject *__pyx_tuple__45;
static PyObject *__pyx_tuple__47;
static PyObject *__pyx_tuple__49;
static PyObject *__pyx_tuple__51;
static PyObject *__pyx_tuple__53;
static PyObject *__pyx_tuple__55;
static PyObject *__pyx_tuple__57;
static PyObject *__pyx_tuple__59;
static PyObject *__pyx_tuple__62;
static PyObject *__pyx_tuple__64;
static PyObject *__pyx_tuple__67;
static PyObject *__pyx_codeobj__48;
static PyObject *__pyx_codeobj__50;
static PyObject *__pyx_codeobj__52;
static PyObject *__pyx_codeobj__54;
static PyObject *__pyx_codeobj__56;
static PyObject *__pyx_codeobj__58;
static PyObject *__pyx_codeobj__60;
static PyObject *__pyx_codeobj__61;
static PyObject *__pyx_codeobj__63;
static PyObject *__pyx_codeobj__65;
static PyObject *__pyx_codeobj__68;
static PyObject *__pyx_codeobj__69;

/* "nngt/generation/cconnect.pyx":50
 * #
 * 
 * cdef bytes _to_bytes(string):             # <<<<<<<<<<<<<<
 *     ''' Convert string to bytes '''
 *     if not isinstance(string, bytes):
 */

static PyObject *__pyx_f_4nngt_10generation_8cconnect__to_bytes(PyObject *__pyx_v_string) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  __Pyx_RefNannySetupContext("_to_bytes", 0);

  /* "nngt/generation/cconnect.pyx":52
 * cdef bytes _to_bytes(string):
 *     ''' Convert string to bytes '''
 *     if not isinstance(string, bytes):             # <<<<<<<<<<<<<<
 *         return bytes(string, "UTF-8")
 *     return string
 */
  __pyx_t_1 = PyBytes_Check(__pyx_v_string); 
  __pyx_t_2 = ((!(__pyx_t_1 != 0)) != 0);
  if (__pyx_t_2) {

    /* "nngt/generation/cconnect.pyx":53
 *     ''' Convert string to bytes '''
 *     if not isinstance(string, bytes):
 *         return bytes(string, "UTF-8")             # <<<<<<<<<<<<<<
 *     return string
 * 
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 53, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_v_string);
    __Pyx_GIVEREF(__pyx_v_string);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_string);
    __Pyx_INCREF(__pyx_kp_s_UTF_8);
    __Pyx_GIVEREF(__pyx_kp_s_UTF_8);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_kp_s_UTF_8);
    __pyx_t_4 = __Pyx_PyObject_Call(((PyObject *)(&PyBytes_Type)), __pyx_t_3, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 53, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_r = ((PyObject*)__pyx_t_4);
    __pyx_t_4 = 0;
    goto __pyx_L0;

    /* "nngt/generation/cconnect.pyx":52
 * cdef bytes _to_bytes(string):
 *     ''' Convert string to bytes '''
 *     if not isinstance(string, bytes):             # <<<<<<<<<<<<<<
 *         return bytes(string, "UTF-8")
 *     return string
 */
  }

  /* "nngt/generation/cconnect.pyx":54
 *     if not isinstance(string, bytes):
 *         return bytes(string, "UTF-8")
 *     return string             # <<<<<<<<<<<<<<
 * 
 * def _unique_rows(arr):
 */
  __Pyx_XDECREF(__pyx_r);
  if (!(likely(PyBytes_CheckExact(__pyx_v_string))||((__pyx_v_string) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "bytes", Py_TYPE(__pyx_v_string)->tp_name), 0))) __PYX_ERR(0, 54, __pyx_L1_error)
  __Pyx_INCREF(__pyx_v_string);
  __pyx_r = ((PyObject*)__pyx_v_string);
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":50
 * #
 * 
 * cdef bytes _to_bytes(string):             # <<<<<<<<<<<<<<
 *     ''' Convert string to bytes '''
 *     if not isinstance(string, bytes):
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("nngt.generation.cconnect._to_bytes", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":56
 *     return string
 * 
 * def _unique_rows(arr):             # <<<<<<<<<<<<<<
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_1_unique_rows(PyObject *__pyx_self, PyObject *__pyx_v_arr); /*proto*/
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_1_unique_rows = {"_unique_rows", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_1_unique_rows, METH_O, 0};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_1_unique_rows(PyObject *__pyx_self, PyObject *__pyx_v_arr) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_unique_rows (wrapper)", 0);
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect__unique_rows(__pyx_self, ((PyObject *)__pyx_v_arr));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect__unique_rows(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_arr) {
  PyObject *__pyx_v_b = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  __Pyx_RefNannySetupContext("_unique_rows", 0);

  /* "nngt/generation/cconnect.pyx":57
 * 
 * def _unique_rows(arr):
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,             # <<<<<<<<<<<<<<
 *         arr.dtype.itemsize * arr.shape[1])))
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_ascontiguousarray); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_arr); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_arr};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_arr};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_arr);
      __Pyx_GIVEREF(__pyx_v_arr);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_arr);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_view); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_void); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":58
 * def _unique_rows(arr):
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))             # <<<<<<<<<<<<<<
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_arr, __pyx_n_s_dtype); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_itemsize); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_arr, __pyx_n_s_shape); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_2, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyNumber_Multiply(__pyx_t_3, __pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 58, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

  /* "nngt/generation/cconnect.pyx":57
 * 
 * def _unique_rows(arr):
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,             # <<<<<<<<<<<<<<
 *         arr.dtype.itemsize * arr.shape[1])))
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 */
  __pyx_t_6 = PyTuple_New(2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_2);
  __pyx_t_5 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_6);
  __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_Call(((PyObject *)__pyx_ptype_5numpy_dtype), __pyx_t_2, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 57, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 57, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_v_b = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":59
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])             # <<<<<<<<<<<<<<
 * 
 * def _no_self_loops(array):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_unique); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_6)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_6) {
    __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_b); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_v_b};
      __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_v_b};
      __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_6); __pyx_t_6 = NULL;
      __Pyx_INCREF(__pyx_v_b);
      __Pyx_GIVEREF(__pyx_v_b);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_b);
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_view); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_arr, __pyx_n_s_dtype); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_5};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_5};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    } else
    #endif
    {
      __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_6, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 59, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_reshape); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_arr, __pyx_n_s_shape); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_4, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 59, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  __pyx_t_7 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_7 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_4, __pyx_int_neg_1, __pyx_t_6};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_7, 2+__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_4, __pyx_int_neg_1, __pyx_t_6};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_7, 2+__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  } else
  #endif
  {
    __pyx_t_5 = PyTuple_New(2+__pyx_t_7); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    if (__pyx_t_4) {
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
    }
    __Pyx_INCREF(__pyx_int_neg_1);
    __Pyx_GIVEREF(__pyx_int_neg_1);
    PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_7, __pyx_int_neg_1);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_7, __pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 59, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":56
 *     return string
 * 
 * def _unique_rows(arr):             # <<<<<<<<<<<<<<
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("nngt.generation.cconnect._unique_rows", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_b);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":61
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 * 
 * def _no_self_loops(array):             # <<<<<<<<<<<<<<
 *     return array[array[:,0] != array[:,1],:]
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_3_no_self_loops(PyObject *__pyx_self, PyObject *__pyx_v_array); /*proto*/
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_3_no_self_loops = {"_no_self_loops", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_3_no_self_loops, METH_O, 0};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_3_no_self_loops(PyObject *__pyx_self, PyObject *__pyx_v_array) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_no_self_loops (wrapper)", 0);
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_2_no_self_loops(__pyx_self, ((PyObject *)__pyx_v_array));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_2_no_self_loops(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_array) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  __Pyx_RefNannySetupContext("_no_self_loops", 0);

  /* "nngt/generation/cconnect.pyx":62
 * 
 * def _no_self_loops(array):
 *     return array[array[:,0] != array[:,1],:]             # <<<<<<<<<<<<<<
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyObject_GetItem(__pyx_v_array, __pyx_tuple__2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyObject_GetItem(__pyx_v_array, __pyx_tuple__4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyObject_RichCompare(__pyx_t_1, __pyx_t_2, Py_NE); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_INCREF(__pyx_slice__5);
  __Pyx_GIVEREF(__pyx_slice__5);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_slice__5);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetItem(__pyx_v_array, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":61
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 * 
 * def _no_self_loops(array):             # <<<<<<<<<<<<<<
 *     return array[array[:,0] != array[:,1],:]
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("nngt.generation.cconnect._no_self_loops", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":64
 *     return array[array[:,0] != array[:,1],:]
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,             # <<<<<<<<<<<<<<
 *                             multigraph):
 *     '''
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_5_filter(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_4_filter[] = "\n    Filter the edges: remove self loops and multiple connections if the graph\n    is not a multigraph.\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_5_filter = {"_filter", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_5_filter, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_4_filter};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_5_filter(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_ia_edges = 0;
  PyObject *__pyx_v_ia_edges_tmp = 0;
  PyObject *__pyx_v_num_ecurrent = 0;
  PyObject *__pyx_v_b_one_pop = 0;
  PyObject *__pyx_v_multigraph = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_filter (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_ia_edges,&__pyx_n_s_ia_edges_tmp,&__pyx_n_s_num_ecurrent,&__pyx_n_s_b_one_pop,&__pyx_n_s_multigraph,0};
    PyObject* values[5] = {0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_ia_edges)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_ia_edges_tmp)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_filter", 1, 5, 5, 1); __PYX_ERR(0, 64, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_num_ecurrent)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_filter", 1, 5, 5, 2); __PYX_ERR(0, 64, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_b_one_pop)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_filter", 1, 5, 5, 3); __PYX_ERR(0, 64, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_filter", 1, 5, 5, 4); __PYX_ERR(0, 64, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_filter") < 0)) __PYX_ERR(0, 64, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 5) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
    }
    __pyx_v_ia_edges = values[0];
    __pyx_v_ia_edges_tmp = values[1];
    __pyx_v_num_ecurrent = values[2];
    __pyx_v_b_one_pop = values[3];
    __pyx_v_multigraph = values[4];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_filter", 1, 5, 5, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 64, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("nngt.generation.cconnect._filter", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_4_filter(__pyx_self, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_4_filter(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_ia_edges, PyObject *__pyx_v_ia_edges_tmp, PyObject *__pyx_v_num_ecurrent, PyObject *__pyx_v_b_one_pop, PyObject *__pyx_v_multigraph) {
  PyObject *__pyx_v_num_added = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  __Pyx_RefNannySetupContext("_filter", 0);
  __Pyx_INCREF(__pyx_v_ia_edges_tmp);
  __Pyx_INCREF(__pyx_v_num_ecurrent);

  /* "nngt/generation/cconnect.pyx":70
 *     is not a multigraph.
 *     '''
 *     if b_one_pop:             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)
 *     num_added = ia_edges_tmp.shape[0]
 */
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_b_one_pop); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(0, 70, __pyx_L1_error)
  if (__pyx_t_1) {

    /* "nngt/generation/cconnect.pyx":71
 *     '''
 *     if b_one_pop:
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)             # <<<<<<<<<<<<<<
 *     num_added = ia_edges_tmp.shape[0]
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_no_self_loops); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 71, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_ia_edges_tmp); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 71, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_edges_tmp};
        __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 71, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_2);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_edges_tmp};
        __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 71, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_2);
      } else
      #endif
      {
        __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 71, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_INCREF(__pyx_v_ia_edges_tmp);
        __Pyx_GIVEREF(__pyx_v_ia_edges_tmp);
        PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_ia_edges_tmp);
        __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 71, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":70
 *     is not a multigraph.
 *     '''
 *     if b_one_pop:             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)
 *     num_added = ia_edges_tmp.shape[0]
 */
  }

  /* "nngt/generation/cconnect.pyx":72
 *     if b_one_pop:
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)
 *     num_added = ia_edges_tmp.shape[0]             # <<<<<<<<<<<<<<
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
 *     num_ecurrent += num_added
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_ia_edges_tmp, __pyx_n_s_shape); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 72, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_2, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 72, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_num_added = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":73
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)
 *     num_added = ia_edges_tmp.shape[0]
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *     num_ecurrent += num_added
 *     if not multigraph:
 */
  __pyx_t_3 = PyNumber_Add(__pyx_v_num_ecurrent, __pyx_v_num_added); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PySlice_New(__pyx_v_num_ecurrent, __pyx_t_3, Py_None); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __Pyx_INCREF(__pyx_slice__6);
  __Pyx_GIVEREF(__pyx_slice__6);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_slice__6);
  __pyx_t_2 = 0;
  if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_3, __pyx_v_ia_edges_tmp) < 0)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":74
 *     num_added = ia_edges_tmp.shape[0]
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
 *     num_ecurrent += num_added             # <<<<<<<<<<<<<<
 *     if not multigraph:
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 */
  __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_v_num_ecurrent, __pyx_v_num_added); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 74, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_3);
  __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":75
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
 *     num_ecurrent += num_added
 *     if not multigraph:             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 *         num_ecurrent = ia_edges_tmp.shape[0]
 */
  __pyx_t_1 = __Pyx_PyObject_IsTrue(__pyx_v_multigraph); if (unlikely(__pyx_t_1 < 0)) __PYX_ERR(0, 75, __pyx_L1_error)
  __pyx_t_6 = ((!__pyx_t_1) != 0);
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":76
 *     num_ecurrent += num_added
 *     if not multigraph:
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])             # <<<<<<<<<<<<<<
 *         num_ecurrent = ia_edges_tmp.shape[0]
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 76, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = PySlice_New(Py_None, __pyx_v_num_ecurrent, Py_None); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 76, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 76, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_5);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5);
    __Pyx_INCREF(__pyx_slice__7);
    __Pyx_GIVEREF(__pyx_slice__7);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_slice__7);
    __pyx_t_5 = 0;
    __pyx_t_5 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_t_4); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 76, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_5); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 76, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_5};
        __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 76, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_5};
        __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 76, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      } else
      #endif
      {
        __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 76, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_GIVEREF(__pyx_t_5);
        PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_5);
        __pyx_t_5 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_7, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 76, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":77
 *     if not multigraph:
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 *         num_ecurrent = ia_edges_tmp.shape[0]             # <<<<<<<<<<<<<<
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *     return ia_edges, num_ecurrent
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_ia_edges_tmp, __pyx_n_s_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 77, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":78
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 *         num_ecurrent = ia_edges_tmp.shape[0]
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *     return ia_edges, num_ecurrent
 * 
 */
    __pyx_t_2 = PySlice_New(Py_None, __pyx_v_num_ecurrent, Py_None); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
    __Pyx_INCREF(__pyx_slice__8);
    __Pyx_GIVEREF(__pyx_slice__8);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_slice__8);
    __pyx_t_2 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_3, __pyx_v_ia_edges_tmp) < 0)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":75
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp
 *     num_ecurrent += num_added
 *     if not multigraph:             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 *         num_ecurrent = ia_edges_tmp.shape[0]
 */
  }

  /* "nngt/generation/cconnect.pyx":79
 *         num_ecurrent = ia_edges_tmp.shape[0]
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *     return ia_edges, num_ecurrent             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 79, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(__pyx_v_ia_edges);
  __Pyx_GIVEREF(__pyx_v_ia_edges);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_v_ia_edges);
  __Pyx_INCREF(__pyx_v_num_ecurrent);
  __Pyx_GIVEREF(__pyx_v_num_ecurrent);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_v_num_ecurrent);
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":64
 *     return array[array[:,0] != array[:,1],:]
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,             # <<<<<<<<<<<<<<
 *                             multigraph):
 *     '''
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("nngt.generation.cconnect._filter", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_num_added);
  __Pyx_XDECREF(__pyx_v_ia_edges_tmp);
  __Pyx_XDECREF(__pyx_v_num_ecurrent);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":87
 * #
 * 
 * def _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_7_fixed_degree(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_6_fixed_degree[] = " Generation of the edges through the C++ function ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_7_fixed_degree = {"_fixed_degree", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_7_fixed_degree, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_6_fixed_degree};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_7_fixed_degree(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyArrayObject *__pyx_v_source_ids = 0;
  PyArrayObject *__pyx_v_target_ids = 0;
  size_t __pyx_v_degree;
  PyObject *__pyx_v_degree_type = 0;
  CYTHON_UNUSED float __pyx_v_reciprocity;
  bool __pyx_v_directed;
  bool __pyx_v_multigraph;
  PyObject *__pyx_v_existing_edges = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_fixed_degree (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_degree,&__pyx_n_s_degree_type,&__pyx_n_s_reciprocity,&__pyx_n_s_directed,&__pyx_n_s_multigraph,&__pyx_n_s_existing_edges,0};
    PyObject* values[8] = {0,0,0,0,0,0,0,0};

    /* "nngt/generation/cconnect.pyx":90
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 *                   bool multigraph, existing_edges=None):             # <<<<<<<<<<<<<<
 *     ''' Generation of the edges through the C++ function '''
 *     np.random.seed()
 */
    values[7] = ((PyObject *)Py_None);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 1); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_degree)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 2); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_degree_type)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 3); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_reciprocity)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 4); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 5); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, 6); __PYX_ERR(0, 87, __pyx_L3_error)
        }
        case  7:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_existing_edges);
          if (value) { values[7] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_fixed_degree") < 0)) __PYX_ERR(0, 87, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_source_ids = ((PyArrayObject *)values[0]);
    __pyx_v_target_ids = ((PyArrayObject *)values[1]);
    __pyx_v_degree = __Pyx_PyInt_As_size_t(values[2]); if (unlikely((__pyx_v_degree == (size_t)-1) && PyErr_Occurred())) __PYX_ERR(0, 88, __pyx_L3_error)
    __pyx_v_degree_type = values[3];
    __pyx_v_reciprocity = __pyx_PyFloat_AsFloat(values[4]); if (unlikely((__pyx_v_reciprocity == (float)-1) && PyErr_Occurred())) __PYX_ERR(0, 89, __pyx_L3_error)
    __pyx_v_directed = __Pyx_PyObject_IsTrue(values[5]); if (unlikely((__pyx_v_directed == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 89, __pyx_L3_error)
    __pyx_v_multigraph = __Pyx_PyObject_IsTrue(values[6]); if (unlikely((__pyx_v_multigraph == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 90, __pyx_L3_error)
    __pyx_v_existing_edges = values[7];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_fixed_degree", 0, 7, 8, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 87, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("nngt.generation.cconnect._fixed_degree", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_source_ids), __pyx_ptype_5numpy_ndarray, 1, "source_ids", 0))) __PYX_ERR(0, 87, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_target_ids), __pyx_ptype_5numpy_ndarray, 1, "target_ids", 0))) __PYX_ERR(0, 88, __pyx_L1_error)
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_6_fixed_degree(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_degree, __pyx_v_degree_type, __pyx_v_reciprocity, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_existing_edges);

  /* "nngt/generation/cconnect.pyx":87
 * #
 * 
 * def _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_6_fixed_degree(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, size_t __pyx_v_degree, PyObject *__pyx_v_degree_type, CYTHON_UNUSED float __pyx_v_reciprocity, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_existing_edges) {
  bool __pyx_v_b_out;
  CYTHON_UNUSED bool __pyx_v_b_total;
  size_t __pyx_v_num_source;
  size_t __pyx_v_num_target;
  size_t __pyx_v_edges;
  CYTHON_UNUSED bool __pyx_v_b_one_pop;
  unsigned int __pyx_v_existing;
  PyArrayObject *__pyx_v_ia_edges = 0;
  unsigned int __pyx_v_idx;
  unsigned int __pyx_v_omp;
  unsigned int __pyx_v_num_node;
  long __pyx_v_msd;
  std::vector<size_t>  __pyx_v_degrees;
  std::vector<std::vector<size_t> >  __pyx_v_old_edges;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_ia_edges;
  __Pyx_Buffer __pyx_pybuffer_ia_edges;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_source_ids;
  __Pyx_Buffer __pyx_pybuffer_source_ids;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_target_ids;
  __Pyx_Buffer __pyx_pybuffer_target_ids;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  bool __pyx_t_4;
  size_t __pyx_t_5;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  PyObject *__pyx_t_11 = NULL;
  unsigned int __pyx_t_12;
  unsigned int __pyx_t_13;
  PyArrayObject *__pyx_t_14 = NULL;
  long __pyx_t_15;
  std::vector<size_t>  __pyx_t_16;
  std::vector<std::vector<size_t> >  __pyx_t_17;
  Py_ssize_t __pyx_t_18;
  Py_ssize_t __pyx_t_19;
  std::vector<size_t>  __pyx_t_20;
  Py_ssize_t __pyx_t_21;
  Py_ssize_t __pyx_t_22;
  PyObject *__pyx_t_23 = NULL;
  PyObject *__pyx_t_24 = NULL;
  PyObject *__pyx_t_25 = NULL;
  __Pyx_RefNannySetupContext("_fixed_degree", 0);
  __pyx_pybuffer_ia_edges.pybuffer.buf = NULL;
  __pyx_pybuffer_ia_edges.refcount = 0;
  __pyx_pybuffernd_ia_edges.data = NULL;
  __pyx_pybuffernd_ia_edges.rcbuffer = &__pyx_pybuffer_ia_edges;
  __pyx_pybuffer_source_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_source_ids.refcount = 0;
  __pyx_pybuffernd_source_ids.data = NULL;
  __pyx_pybuffernd_source_ids.rcbuffer = &__pyx_pybuffer_source_ids;
  __pyx_pybuffer_target_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_target_ids.refcount = 0;
  __pyx_pybuffernd_target_ids.data = NULL;
  __pyx_pybuffernd_target_ids.rcbuffer = &__pyx_pybuffer_target_ids;
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_source_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 87, __pyx_L1_error)
  }
  __pyx_pybuffernd_source_ids.diminfo[0].strides = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_source_ids.diminfo[0].shape = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.shape[0];
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_target_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 87, __pyx_L1_error)
  }
  __pyx_pybuffernd_target_ids.diminfo[0].strides = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_target_ids.diminfo[0].shape = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.shape[0];

  /* "nngt/generation/cconnect.pyx":92
 *                   bool multigraph, existing_edges=None):
 *     ''' Generation of the edges through the C++ function '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     cdef:
 *         # type of degree
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":95
 *     cdef:
 *         # type of degree
 *         bool b_out = (degree_type == "out")             # <<<<<<<<<<<<<<
 *         bool b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]
 */
  __pyx_t_1 = PyObject_RichCompare(__pyx_v_degree_type, __pyx_n_s_out, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 95, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely((__pyx_t_4 == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 95, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_b_out = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":96
 *         # type of degree
 *         bool b_out = (degree_type == "out")
 *         bool b_total = (degree_type == "total")             # <<<<<<<<<<<<<<
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 */
  __pyx_t_1 = PyObject_RichCompare(__pyx_v_degree_type, __pyx_n_s_total, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 96, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely((__pyx_t_4 == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 96, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_b_total = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":97
 *         bool b_out = (degree_type == "out")
 *         bool b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]             # <<<<<<<<<<<<<<
 *         size_t num_target = target_ids.shape[0]
 *         size_t edges = (num_target * degree
 */
  __pyx_v_num_source = (__pyx_v_source_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":98
 *         bool b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]             # <<<<<<<<<<<<<<
 *         size_t edges = (num_target * degree
 *                         if degree_type == "out" else num_source * degree)
 */
  __pyx_v_num_target = (__pyx_v_target_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":100
 *         size_t num_target = target_ids.shape[0]
 *         size_t edges = (num_target * degree
 *                         if degree_type == "out" else num_source * degree)             # <<<<<<<<<<<<<<
 *         bool b_one_pop = _check_num_edges(
 *             source_ids, target_ids, edges, directed, multigraph)
 */
  __pyx_t_6 = (__Pyx_PyString_Equals(__pyx_v_degree_type, __pyx_n_s_out, Py_EQ)); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 100, __pyx_L1_error)
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":99
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 *         size_t edges = (num_target * degree             # <<<<<<<<<<<<<<
 *                         if degree_type == "out" else num_source * degree)
 *         bool b_one_pop = _check_num_edges(
 */
    __pyx_t_5 = (__pyx_v_num_target * __pyx_v_degree);
  } else {

    /* "nngt/generation/cconnect.pyx":100
 *         size_t num_target = target_ids.shape[0]
 *         size_t edges = (num_target * degree
 *                         if degree_type == "out" else num_source * degree)             # <<<<<<<<<<<<<<
 *         bool b_one_pop = _check_num_edges(
 *             source_ids, target_ids, edges, directed, multigraph)
 */
    __pyx_t_5 = (__pyx_v_num_source * __pyx_v_degree);
  }
  __pyx_v_edges = __pyx_t_5;

  /* "nngt/generation/cconnect.pyx":101
 *         size_t edges = (num_target * degree
 *                         if degree_type == "out" else num_source * degree)
 *         bool b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *             source_ids, target_ids, edges, directed, multigraph)
 *         unsigned int existing = \
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_check_num_edges); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 101, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);

  /* "nngt/generation/cconnect.pyx":102
 *                         if degree_type == "out" else num_source * degree)
 *         bool b_one_pop = _check_num_edges(
 *             source_ids, target_ids, edges, directed, multigraph)             # <<<<<<<<<<<<<<
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 */
  __pyx_t_3 = __Pyx_PyInt_FromSize_t(__pyx_v_edges); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 102, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_7 = __Pyx_PyBool_FromLong(__pyx_v_directed); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 102, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_8 = __Pyx_PyBool_FromLong(__pyx_v_multigraph); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 102, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_9 = NULL;
  __pyx_t_10 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_9)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_9);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_10 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[6] = {__pyx_t_9, ((PyObject *)__pyx_v_source_ids), ((PyObject *)__pyx_v_target_ids), __pyx_t_3, __pyx_t_7, __pyx_t_8};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_10, 5+__pyx_t_10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 101, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[6] = {__pyx_t_9, ((PyObject *)__pyx_v_source_ids), ((PyObject *)__pyx_v_target_ids), __pyx_t_3, __pyx_t_7, __pyx_t_8};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_10, 5+__pyx_t_10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 101, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  } else
  #endif
  {
    __pyx_t_11 = PyTuple_New(5+__pyx_t_10); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 101, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    if (__pyx_t_9) {
      __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_9); __pyx_t_9 = NULL;
    }
    __Pyx_INCREF(((PyObject *)__pyx_v_source_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_source_ids));
    PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_10, ((PyObject *)__pyx_v_source_ids));
    __Pyx_INCREF(((PyObject *)__pyx_v_target_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_target_ids));
    PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_10, ((PyObject *)__pyx_v_target_ids));
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_11, 2+__pyx_t_10, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_11, 3+__pyx_t_10, __pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_11, 4+__pyx_t_10, __pyx_t_8);
    __pyx_t_3 = 0;
    __pyx_t_7 = 0;
    __pyx_t_8 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_11, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 101, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":101
 *         size_t edges = (num_target * degree
 *                         if degree_type == "out" else num_source * degree)
 *         bool b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *             source_ids, target_ids, edges, directed, multigraph)
 *         unsigned int existing = \
 */
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely((__pyx_t_4 == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 101, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_b_one_pop = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":104
 *             source_ids, target_ids, edges, directed, multigraph)
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]             # <<<<<<<<<<<<<<
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing+edges, 2), dtype=DTYPE)
 */
  __pyx_t_6 = (__pyx_v_existing_edges == Py_None);
  if ((__pyx_t_6 != 0)) {
    __pyx_t_12 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_existing_edges, __pyx_n_s_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 104, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 104, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_13 = __Pyx_PyInt_As_unsigned_int(__pyx_t_2); if (unlikely((__pyx_t_13 == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 104, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_12 = __pyx_t_13;
  }
  __pyx_v_existing = __pyx_t_12;

  /* "nngt/generation/cconnect.pyx":105
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_zeros); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":106
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing+edges, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges
 */
  __pyx_t_2 = __Pyx_PyInt_FromSize_t((__pyx_v_existing + __pyx_v_edges)); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_11 = PyTuple_New(2); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_2);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_11, 1, __pyx_int_2);
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":105
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_11);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_11);
  __pyx_t_11 = 0;

  /* "nngt/generation/cconnect.pyx":106
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing+edges, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges
 */
  __pyx_t_11 = PyDict_New(); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_DTYPE); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  if (PyDict_SetItem(__pyx_t_11, __pyx_n_s_dtype, __pyx_t_8) < 0) __PYX_ERR(0, 106, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "nngt/generation/cconnect.pyx":105
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_2, __pyx_t_11); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 105, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  if (!(likely(((__pyx_t_8) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_8, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 105, __pyx_L1_error)
  __pyx_t_14 = ((PyArrayObject *)__pyx_t_8);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_14, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_ia_edges = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf = NULL;
      __PYX_ERR(0, 105, __pyx_L1_error)
    } else {__pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_14 = 0;
  __pyx_v_ia_edges = ((PyArrayObject *)__pyx_t_8);
  __pyx_t_8 = 0;

  /* "nngt/generation/cconnect.pyx":107
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:             # <<<<<<<<<<<<<<
 *         ia_edges[:existing,:] = existing_edges
 *     cdef:
 */
  __pyx_t_6 = (__pyx_v_existing != 0);
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":108
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges             # <<<<<<<<<<<<<<
 *     cdef:
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 */
    __pyx_t_8 = __Pyx_PyInt_From_unsigned_int(__pyx_v_existing); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __pyx_t_11 = PySlice_New(Py_None, __pyx_t_8, Py_None); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    __pyx_t_8 = PyTuple_New(2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_GIVEREF(__pyx_t_11);
    PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_11);
    __Pyx_INCREF(__pyx_slice__9);
    __Pyx_GIVEREF(__pyx_slice__9);
    PyTuple_SET_ITEM(__pyx_t_8, 1, __pyx_slice__9);
    __pyx_t_11 = 0;
    if (unlikely(PyObject_SetItem(((PyObject *)__pyx_v_ia_edges), __pyx_t_8, __pyx_v_existing_edges) < 0)) __PYX_ERR(0, 108, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

    /* "nngt/generation/cconnect.pyx":107
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:             # <<<<<<<<<<<<<<
 *         ia_edges[:existing,:] = existing_edges
 *     cdef:
 */
  }

  /* "nngt/generation/cconnect.pyx":110
 *         ia_edges[:existing,:] = existing_edges
 *     cdef:
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target             # <<<<<<<<<<<<<<
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source
 */
  if ((__pyx_v_b_out != 0)) {
    __pyx_t_12 = 0;
  } else {
    __pyx_t_12 = 1;
  }
  __pyx_v_idx = __pyx_t_12;

  /* "nngt/generation/cconnect.pyx":111
 *     cdef:
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 *         unsigned int omp = nngt.config["omp"]             # <<<<<<<<<<<<<<
 *         unsigned int num_node = num_target if b_out else num_source
 *         long msd = np.random.randint(0, edges + 1)
 */
  __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_nngt); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_11 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_config); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_t_8 = PyObject_GetItem(__pyx_t_11, __pyx_n_s_omp); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_12 = __Pyx_PyInt_As_unsigned_int(__pyx_t_8); if (unlikely((__pyx_t_12 == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 111, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_v_omp = __pyx_t_12;

  /* "nngt/generation/cconnect.pyx":112
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source             # <<<<<<<<<<<<<<
 *         long msd = np.random.randint(0, edges + 1)
 *         vector[size_t] degrees = np.repeat(degree, num_node)
 */
  if ((__pyx_v_b_out != 0)) {
    __pyx_t_5 = __pyx_v_num_target;
  } else {
    __pyx_t_5 = __pyx_v_num_source;
  }
  __pyx_v_num_node = __pyx_t_5;

  /* "nngt/generation/cconnect.pyx":113
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source
 *         long msd = np.random.randint(0, edges + 1)             # <<<<<<<<<<<<<<
 *         vector[size_t] degrees = np.repeat(degree, num_node)
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 */
  __pyx_t_11 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_11, __pyx_n_s_random); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_randint); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyInt_FromSize_t((__pyx_v_edges + 1)); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = NULL;
  __pyx_t_10 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_11))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_11);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_11);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_11, function);
      __pyx_t_10 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_11)) {
    PyObject *__pyx_temp[3] = {__pyx_t_1, __pyx_int_0, __pyx_t_2};
    __pyx_t_8 = __Pyx_PyFunction_FastCall(__pyx_t_11, __pyx_temp+1-__pyx_t_10, 2+__pyx_t_10); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_11)) {
    PyObject *__pyx_temp[3] = {__pyx_t_1, __pyx_int_0, __pyx_t_2};
    __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_11, __pyx_temp+1-__pyx_t_10, 2+__pyx_t_10); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  {
    __pyx_t_7 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (__pyx_t_1) {
      __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_1); __pyx_t_1 = NULL;
    }
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_GIVEREF(__pyx_int_0);
    PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_10, __pyx_int_0);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_10, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_11, __pyx_t_7, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 113, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_15 = __Pyx_PyInt_As_long(__pyx_t_8); if (unlikely((__pyx_t_15 == (long)-1) && PyErr_Occurred())) __PYX_ERR(0, 113, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_v_msd = __pyx_t_15;

  /* "nngt/generation/cconnect.pyx":114
 *         unsigned int num_node = num_target if b_out else num_source
 *         long msd = np.random.randint(0, edges + 1)
 *         vector[size_t] degrees = np.repeat(degree, num_node)             # <<<<<<<<<<<<<<
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 * 
 */
  __pyx_t_11 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 114, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_11, __pyx_n_s_repeat); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 114, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = __Pyx_PyInt_FromSize_t(__pyx_v_degree); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 114, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_2 = __Pyx_PyInt_From_unsigned_int(__pyx_v_num_node); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 114, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = NULL;
  __pyx_t_10 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_7);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_7, function);
      __pyx_t_10 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_7)) {
    PyObject *__pyx_temp[3] = {__pyx_t_1, __pyx_t_11, __pyx_t_2};
    __pyx_t_8 = __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp+1-__pyx_t_10, 2+__pyx_t_10); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
    PyObject *__pyx_temp[3] = {__pyx_t_1, __pyx_t_11, __pyx_t_2};
    __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp+1-__pyx_t_10, 2+__pyx_t_10); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  {
    __pyx_t_3 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (__pyx_t_1) {
      __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1); __pyx_t_1 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_11);
    PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_10, __pyx_t_11);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_10, __pyx_t_2);
    __pyx_t_11 = 0;
    __pyx_t_2 = 0;
    __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_3, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 114, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_16 = __pyx_convert_vector_from_py_size_t(__pyx_t_8); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 114, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_v_degrees = __pyx_t_16;

  /* "nngt/generation/cconnect.pyx":115
 *         long msd = np.random.randint(0, edges + 1)
 *         vector[size_t] degrees = np.repeat(degree, num_node)
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()             # <<<<<<<<<<<<<<
 * 
 *     if b_out:
 */
  try {
    __pyx_t_17 = std::vector<std::vector<size_t> > ();
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 115, __pyx_L1_error)
  }
  __pyx_v_old_edges = __pyx_t_17;

  /* "nngt/generation/cconnect.pyx":117
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 * 
 *     if b_out:             # <<<<<<<<<<<<<<
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 */
  __pyx_t_6 = (__pyx_v_b_out != 0);
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":118
 * 
 *     if b_out:
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,             # <<<<<<<<<<<<<<
 *             idx, multigraph, directed, msd, omp)
 *     else:
 */
    __pyx_t_18 = 0;
    __pyx_t_19 = 0;
    __pyx_t_16 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_source_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 118, __pyx_L1_error)
    __pyx_t_20 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_target_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 118, __pyx_L1_error)

    /* "nngt/generation/cconnect.pyx":119
 *     if b_out:
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)             # <<<<<<<<<<<<<<
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 */
    try {
      generation::_gen_edges((&(*__Pyx_BufPtrCContig2d(size_t *, __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf, __pyx_t_18, __pyx_pybuffernd_ia_edges.diminfo[0].strides, __pyx_t_19, __pyx_pybuffernd_ia_edges.diminfo[1].strides))), __pyx_t_16, __pyx_v_degrees, __pyx_t_20, __pyx_v_old_edges, __pyx_v_idx, __pyx_v_multigraph, __pyx_v_directed, __pyx_v_msd, __pyx_v_omp);
    } catch(...) {
      __Pyx_CppExn2PyErr();
      __PYX_ERR(0, 118, __pyx_L1_error)
    }

    /* "nngt/generation/cconnect.pyx":117
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 * 
 *     if b_out:             # <<<<<<<<<<<<<<
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 */
    goto __pyx_L4;
  }

  /* "nngt/generation/cconnect.pyx":121
 *             idx, multigraph, directed, msd, omp)
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,             # <<<<<<<<<<<<<<
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 */
  /*else*/ {
    __pyx_t_21 = 0;
    __pyx_t_22 = 0;
    __pyx_t_20 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_target_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 121, __pyx_L1_error)
    __pyx_t_16 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_source_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 121, __pyx_L1_error)

    /* "nngt/generation/cconnect.pyx":122
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)             # <<<<<<<<<<<<<<
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 */
    try {
      generation::_gen_edges((&(*__Pyx_BufPtrCContig2d(size_t *, __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf, __pyx_t_21, __pyx_pybuffernd_ia_edges.diminfo[0].strides, __pyx_t_22, __pyx_pybuffernd_ia_edges.diminfo[1].strides))), __pyx_t_20, __pyx_v_degrees, __pyx_t_16, __pyx_v_old_edges, __pyx_v_idx, __pyx_v_multigraph, __pyx_v_directed, __pyx_v_msd, __pyx_v_omp);
    } catch(...) {
      __Pyx_CppExn2PyErr();
      __PYX_ERR(0, 121, __pyx_L1_error)
    }
  }
  __pyx_L4:;

  /* "nngt/generation/cconnect.pyx":123
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_6 = ((!(__pyx_v_directed != 0)) != 0);
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":124
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = PyObject_GetItem(((PyObject *)__pyx_v_ia_edges), __pyx_tuple__12); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 124, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
    PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_7);
    __pyx_t_7 = 0;
    __pyx_t_7 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_7) {
      __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 124, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_8);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_7, __pyx_t_2};
        __pyx_t_8 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 124, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_7, __pyx_t_2};
        __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 124, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      {
        __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 124, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_7); __pyx_t_7 = NULL;
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_11, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 124, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!(likely(((__pyx_t_8) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_8, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 124, __pyx_L1_error)
    __pyx_t_14 = ((PyArrayObject *)__pyx_t_8);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_10 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_14, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_10 < 0)) {
        PyErr_Fetch(&__pyx_t_23, &__pyx_t_24, &__pyx_t_25);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_23); Py_XDECREF(__pyx_t_24); Py_XDECREF(__pyx_t_25);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_23, __pyx_t_24, __pyx_t_25);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 124, __pyx_L1_error)
    }
    __pyx_t_14 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_8));
    __pyx_t_8 = 0;

    /* "nngt/generation/cconnect.pyx":125
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 125, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_11 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_11)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_11);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_11) {
      __pyx_t_8 = __Pyx_PyObject_CallOneArg(__pyx_t_3, ((PyObject *)__pyx_v_ia_edges)); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_8);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_11, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_8 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_8);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_11, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_8);
      } else
      #endif
      {
        __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_11); __pyx_t_11 = NULL;
        __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
        __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
        PyTuple_SET_ITEM(__pyx_t_2, 0+1, ((PyObject *)__pyx_v_ia_edges));
        __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_2, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_8);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!(likely(((__pyx_t_8) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_8, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 125, __pyx_L1_error)
    __pyx_t_14 = ((PyArrayObject *)__pyx_t_8);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_10 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_14, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_10 < 0)) {
        PyErr_Fetch(&__pyx_t_25, &__pyx_t_24, &__pyx_t_23);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_25); Py_XDECREF(__pyx_t_24); Py_XDECREF(__pyx_t_23);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_25, __pyx_t_24, __pyx_t_23);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 125, __pyx_L1_error)
    }
    __pyx_t_14 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_8));
    __pyx_t_8 = 0;

    /* "nngt/generation/cconnect.pyx":123
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":126
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
  __pyx_r = ((PyObject *)__pyx_v_ia_edges);
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":87
 * #
 * 
 * def _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_11);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("nngt.generation.cconnect._fixed_degree", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_ia_edges);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":129
 * 
 * 
 * def _gaussian_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_9_gaussian_degree(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_8_gaussian_degree[] = "\n    Connect nodes with a Gaussian distribution (generation through C++\n    function.\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_9_gaussian_degree = {"_gaussian_degree", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_9_gaussian_degree, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_8_gaussian_degree};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_9_gaussian_degree(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyArrayObject *__pyx_v_source_ids = 0;
  PyArrayObject *__pyx_v_target_ids = 0;
  unsigned int __pyx_v_avg;
  unsigned int __pyx_v_std;
  PyObject *__pyx_v_degree_type = 0;
  CYTHON_UNUSED float __pyx_v_reciprocity;
  bool __pyx_v_directed;
  bool __pyx_v_multigraph;
  PyObject *__pyx_v_existing_edges = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_gaussian_degree (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_avg,&__pyx_n_s_std,&__pyx_n_s_degree_type,&__pyx_n_s_reciprocity,&__pyx_n_s_directed,&__pyx_n_s_multigraph,&__pyx_n_s_existing_edges,0};
    PyObject* values[9] = {0,0,0,0,0,0,0,0,0};

    /* "nngt/generation/cconnect.pyx":132
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 *                      bool directed, bool multigraph, existing_edges=None):             # <<<<<<<<<<<<<<
 *     '''
 *     Connect nodes with a Gaussian distribution (generation through C++
 */
    values[8] = ((PyObject *)Py_None);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 1); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_avg)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 2); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_std)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 3); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_degree_type)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 4); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_reciprocity)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 5); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 6); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  7:
        if (likely((values[7] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, 7); __PYX_ERR(0, 129, __pyx_L3_error)
        }
        case  8:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_existing_edges);
          if (value) { values[8] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_gaussian_degree") < 0)) __PYX_ERR(0, 129, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_source_ids = ((PyArrayObject *)values[0]);
    __pyx_v_target_ids = ((PyArrayObject *)values[1]);
    __pyx_v_avg = __Pyx_PyInt_As_unsigned_int(values[2]); if (unlikely((__pyx_v_avg == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 130, __pyx_L3_error)
    __pyx_v_std = __Pyx_PyInt_As_unsigned_int(values[3]); if (unlikely((__pyx_v_std == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 131, __pyx_L3_error)
    __pyx_v_degree_type = values[4];
    __pyx_v_reciprocity = __pyx_PyFloat_AsFloat(values[5]); if (unlikely((__pyx_v_reciprocity == (float)-1) && PyErr_Occurred())) __PYX_ERR(0, 131, __pyx_L3_error)
    __pyx_v_directed = __Pyx_PyObject_IsTrue(values[6]); if (unlikely((__pyx_v_directed == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 132, __pyx_L3_error)
    __pyx_v_multigraph = __Pyx_PyObject_IsTrue(values[7]); if (unlikely((__pyx_v_multigraph == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 132, __pyx_L3_error)
    __pyx_v_existing_edges = values[8];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_gaussian_degree", 0, 8, 9, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 129, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("nngt.generation.cconnect._gaussian_degree", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_source_ids), __pyx_ptype_5numpy_ndarray, 1, "source_ids", 0))) __PYX_ERR(0, 129, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_target_ids), __pyx_ptype_5numpy_ndarray, 1, "target_ids", 0))) __PYX_ERR(0, 130, __pyx_L1_error)
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_8_gaussian_degree(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_avg, __pyx_v_std, __pyx_v_degree_type, __pyx_v_reciprocity, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_existing_edges);

  /* "nngt/generation/cconnect.pyx":129
 * 
 * 
 * def _gaussian_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_8_gaussian_degree(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, unsigned int __pyx_v_avg, unsigned int __pyx_v_std, PyObject *__pyx_v_degree_type, CYTHON_UNUSED float __pyx_v_reciprocity, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_existing_edges) {
  PyObject *__pyx_v_b_out = 0;
  CYTHON_UNUSED PyObject *__pyx_v_b_total = 0;
  size_t __pyx_v_num_source;
  size_t __pyx_v_num_target;
  unsigned int __pyx_v_idx;
  unsigned int __pyx_v_omp;
  unsigned int __pyx_v_num_node;
  std::vector<size_t>  __pyx_v_degrees;
  std::vector<std::vector<size_t> >  __pyx_v_old_edges;
  PyObject *__pyx_v_edges = NULL;
  CYTHON_UNUSED PyObject *__pyx_v_b_one_pop = NULL;
  long __pyx_v_msd;
  unsigned int __pyx_v_existing;
  PyArrayObject *__pyx_v_ia_edges = 0;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_ia_edges;
  __Pyx_Buffer __pyx_pybuffer_ia_edges;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_source_ids;
  __Pyx_Buffer __pyx_pybuffer_source_ids;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_target_ids;
  __Pyx_Buffer __pyx_pybuffer_target_ids;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  unsigned int __pyx_t_4;
  int __pyx_t_5;
  size_t __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  int __pyx_t_15;
  PyObject *__pyx_t_16 = NULL;
  std::vector<size_t>  __pyx_t_17;
  std::vector<std::vector<size_t> >  __pyx_t_18;
  long __pyx_t_19;
  unsigned int __pyx_t_20;
  PyArrayObject *__pyx_t_21 = NULL;
  Py_ssize_t __pyx_t_22;
  Py_ssize_t __pyx_t_23;
  std::vector<size_t>  __pyx_t_24;
  Py_ssize_t __pyx_t_25;
  Py_ssize_t __pyx_t_26;
  PyObject *__pyx_t_27 = NULL;
  PyObject *__pyx_t_28 = NULL;
  PyObject *__pyx_t_29 = NULL;
  __Pyx_RefNannySetupContext("_gaussian_degree", 0);
  __pyx_pybuffer_ia_edges.pybuffer.buf = NULL;
  __pyx_pybuffer_ia_edges.refcount = 0;
  __pyx_pybuffernd_ia_edges.data = NULL;
  __pyx_pybuffernd_ia_edges.rcbuffer = &__pyx_pybuffer_ia_edges;
  __pyx_pybuffer_source_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_source_ids.refcount = 0;
  __pyx_pybuffernd_source_ids.data = NULL;
  __pyx_pybuffernd_source_ids.rcbuffer = &__pyx_pybuffer_source_ids;
  __pyx_pybuffer_target_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_target_ids.refcount = 0;
  __pyx_pybuffernd_target_ids.data = NULL;
  __pyx_pybuffernd_target_ids.rcbuffer = &__pyx_pybuffer_target_ids;
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_source_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 129, __pyx_L1_error)
  }
  __pyx_pybuffernd_source_ids.diminfo[0].strides = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_source_ids.diminfo[0].shape = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.shape[0];
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_target_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 129, __pyx_L1_error)
  }
  __pyx_pybuffernd_target_ids.diminfo[0].strides = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_target_ids.diminfo[0].shape = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.shape[0];

  /* "nngt/generation/cconnect.pyx":137
 *     function.
 *     '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     cdef:
 *         # type of degree
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 137, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 137, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 137, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":140
 *     cdef:
 *         # type of degree
 *         b_out = (degree_type == "out")             # <<<<<<<<<<<<<<
 *         b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]
 */
  __pyx_t_1 = PyObject_RichCompare(__pyx_v_degree_type, __pyx_n_s_out, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 140, __pyx_L1_error)
  __pyx_v_b_out = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":141
 *         # type of degree
 *         b_out = (degree_type == "out")
 *         b_total = (degree_type == "total")             # <<<<<<<<<<<<<<
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 */
  __pyx_t_1 = PyObject_RichCompare(__pyx_v_degree_type, __pyx_n_s_total, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 141, __pyx_L1_error)
  __pyx_v_b_total = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":142
 *         b_out = (degree_type == "out")
 *         b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]             # <<<<<<<<<<<<<<
 *         size_t num_target = target_ids.shape[0]
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 */
  __pyx_v_num_source = (__pyx_v_source_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":143
 *         b_total = (degree_type == "total")
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]             # <<<<<<<<<<<<<<
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 *         unsigned int omp = nngt.config["omp"]
 */
  __pyx_v_num_target = (__pyx_v_target_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":144
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target             # <<<<<<<<<<<<<<
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source
 */
  __pyx_t_5 = __Pyx_PyObject_IsTrue(__pyx_v_b_out); if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 144, __pyx_L1_error)
  if (__pyx_t_5) {
    __pyx_t_4 = 0;
  } else {
    __pyx_t_4 = 1;
  }
  __pyx_v_idx = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":145
 *         size_t num_target = target_ids.shape[0]
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 *         unsigned int omp = nngt.config["omp"]             # <<<<<<<<<<<<<<
 *         unsigned int num_node = num_target if b_out else num_source
 *         vector[size_t] degrees = np.around(np.maximum(
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_nngt); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_config); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetItem(__pyx_t_2, __pyx_n_s_omp); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_4 = __Pyx_PyInt_As_unsigned_int(__pyx_t_1); if (unlikely((__pyx_t_4 == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 145, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_omp = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":146
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source             # <<<<<<<<<<<<<<
 *         vector[size_t] degrees = np.around(np.maximum(
 *             np.random.normal(avg, std, num_node), 0.)).astype(DTYPE)
 */
  __pyx_t_5 = __Pyx_PyObject_IsTrue(__pyx_v_b_out); if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 146, __pyx_L1_error)
  if (__pyx_t_5) {
    __pyx_t_6 = __pyx_v_num_target;
  } else {
    __pyx_t_6 = __pyx_v_num_source;
  }
  __pyx_v_num_node = __pyx_t_6;

  /* "nngt/generation/cconnect.pyx":147
 *         unsigned int omp = nngt.config["omp"]
 *         unsigned int num_node = num_target if b_out else num_source
 *         vector[size_t] degrees = np.around(np.maximum(             # <<<<<<<<<<<<<<
 *             np.random.normal(avg, std, num_node), 0.)).astype(DTYPE)
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_around); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_8 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_8, __pyx_n_s_maximum); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 147, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;

  /* "nngt/generation/cconnect.pyx":148
 *         unsigned int num_node = num_target if b_out else num_source
 *         vector[size_t] degrees = np.around(np.maximum(
 *             np.random.normal(avg, std, num_node), 0.)).astype(DTYPE)             # <<<<<<<<<<<<<<
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 * 
 */
  __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_10);
  __pyx_t_11 = __Pyx_PyObject_GetAttrStr(__pyx_t_10, __pyx_n_s_random); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_11, __pyx_n_s_normal); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_10);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = __Pyx_PyInt_From_unsigned_int(__pyx_v_avg); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_12 = __Pyx_PyInt_From_unsigned_int(__pyx_v_std); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __pyx_t_13 = __Pyx_PyInt_From_unsigned_int(__pyx_v_num_node); if (unlikely(!__pyx_t_13)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_13);
  __pyx_t_14 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_10))) {
    __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_10);
    if (likely(__pyx_t_14)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
      __Pyx_INCREF(__pyx_t_14);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_10, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_10)) {
    PyObject *__pyx_temp[4] = {__pyx_t_14, __pyx_t_11, __pyx_t_12, __pyx_t_13};
    __pyx_t_8 = __Pyx_PyFunction_FastCall(__pyx_t_10, __pyx_temp+1-__pyx_t_15, 3+__pyx_t_15); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_10)) {
    PyObject *__pyx_temp[4] = {__pyx_t_14, __pyx_t_11, __pyx_t_12, __pyx_t_13};
    __pyx_t_8 = __Pyx_PyCFunction_FastCall(__pyx_t_10, __pyx_temp+1-__pyx_t_15, 3+__pyx_t_15); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
  } else
  #endif
  {
    __pyx_t_16 = PyTuple_New(3+__pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    if (__pyx_t_14) {
      __Pyx_GIVEREF(__pyx_t_14); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_14); __pyx_t_14 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_11);
    PyTuple_SET_ITEM(__pyx_t_16, 0+__pyx_t_15, __pyx_t_11);
    __Pyx_GIVEREF(__pyx_t_12);
    PyTuple_SET_ITEM(__pyx_t_16, 1+__pyx_t_15, __pyx_t_12);
    __Pyx_GIVEREF(__pyx_t_13);
    PyTuple_SET_ITEM(__pyx_t_16, 2+__pyx_t_15, __pyx_t_13);
    __pyx_t_11 = 0;
    __pyx_t_12 = 0;
    __pyx_t_13 = 0;
    __pyx_t_8 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_t_16, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_8);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  }
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_t_10 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_10)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_10);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[3] = {__pyx_t_10, __pyx_t_8, __pyx_float_0_};
    __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[3] = {__pyx_t_10, __pyx_t_8, __pyx_float_0_};
    __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  } else
  #endif
  {
    __pyx_t_16 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    if (__pyx_t_10) {
      __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_10); __pyx_t_10 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_8);
    PyTuple_SET_ITEM(__pyx_t_16, 0+__pyx_t_15, __pyx_t_8);
    __Pyx_INCREF(__pyx_float_0_);
    __Pyx_GIVEREF(__pyx_float_0_);
    PyTuple_SET_ITEM(__pyx_t_16, 1+__pyx_t_15, __pyx_float_0_);
    __pyx_t_8 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_16, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
    __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_7);
    if (likely(__pyx_t_9)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
      __Pyx_INCREF(__pyx_t_9);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_7, function);
    }
  }
  if (!__pyx_t_9) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_7)) {
      PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_3};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
      PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_3};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    {
      __pyx_t_16 = PyTuple_New(1+1); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 147, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_9); __pyx_t_9 = NULL;
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_16, 0+1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_16, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 147, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_astype); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_DTYPE); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_16 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_7))) {
    __pyx_t_16 = PyMethod_GET_SELF(__pyx_t_7);
    if (likely(__pyx_t_16)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
      __Pyx_INCREF(__pyx_t_16);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_7, function);
    }
  }
  if (!__pyx_t_16) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 148, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_7)) {
      PyObject *__pyx_temp[2] = {__pyx_t_16, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
      PyObject *__pyx_temp[2] = {__pyx_t_16, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_16); __pyx_t_16 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_16); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_16); __pyx_t_16 = NULL;
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 148, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_17 = __pyx_convert_vector_from_py_size_t(__pyx_t_1); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 148, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_degrees = __pyx_t_17;

  /* "nngt/generation/cconnect.pyx":149
 *         vector[size_t] degrees = np.around(np.maximum(
 *             np.random.normal(avg, std, num_node), 0.)).astype(DTYPE)
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()             # <<<<<<<<<<<<<<
 * 
 *     # edges
 */
  try {
    __pyx_t_18 = std::vector<std::vector<size_t> > ();
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 149, __pyx_L1_error)
  }
  __pyx_v_old_edges = __pyx_t_18;

  /* "nngt/generation/cconnect.pyx":152
 * 
 *     # edges
 *     edges = np.sum(degrees)             # <<<<<<<<<<<<<<
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, edges, directed, multigraph)
 */
  __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_sum); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_7 = __pyx_convert_vector_to_py_size_t(__pyx_v_degrees); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 152, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 152, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_7};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_7};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    } else
    #endif
    {
      __pyx_t_16 = PyTuple_New(1+1); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_16);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_7);
      PyTuple_SET_ITEM(__pyx_t_16, 0+1, __pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_16, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 152, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_edges = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":153
 *     # edges
 *     edges = np.sum(degrees)
 *     b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *         source_ids, target_ids, edges, directed, multigraph)
 * 
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_check_num_edges); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 153, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "nngt/generation/cconnect.pyx":154
 *     edges = np.sum(degrees)
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, edges, directed, multigraph)             # <<<<<<<<<<<<<<
 * 
 *     cdef:
 */
  __pyx_t_16 = __Pyx_PyBool_FromLong(__pyx_v_directed); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __pyx_t_7 = __Pyx_PyBool_FromLong(__pyx_v_multigraph); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 154, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_2 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, ((PyObject *)__pyx_v_source_ids), ((PyObject *)__pyx_v_target_ids), __pyx_v_edges, __pyx_t_16, __pyx_t_7};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_15, 5+__pyx_t_15); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 153, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, ((PyObject *)__pyx_v_source_ids), ((PyObject *)__pyx_v_target_ids), __pyx_v_edges, __pyx_t_16, __pyx_t_7};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_15, 5+__pyx_t_15); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 153, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(5+__pyx_t_15); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 153, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_2) {
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_2); __pyx_t_2 = NULL;
    }
    __Pyx_INCREF(((PyObject *)__pyx_v_source_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_source_ids));
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_15, ((PyObject *)__pyx_v_source_ids));
    __Pyx_INCREF(((PyObject *)__pyx_v_target_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_target_ids));
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_15, ((PyObject *)__pyx_v_target_ids));
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_9, 2+__pyx_t_15, __pyx_v_edges);
    __Pyx_GIVEREF(__pyx_t_16);
    PyTuple_SET_ITEM(__pyx_t_9, 3+__pyx_t_15, __pyx_t_16);
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_9, 4+__pyx_t_15, __pyx_t_7);
    __pyx_t_16 = 0;
    __pyx_t_7 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 153, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_b_one_pop = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":157
 * 
 *     cdef:
 *         long msd = np.random.randint(0, edges + 1)             # <<<<<<<<<<<<<<
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_random); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_9, __pyx_n_s_randint); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = __Pyx_PyInt_AddObjC(__pyx_v_edges, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_7 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_int_0, __pyx_t_9};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 157, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_int_0, __pyx_t_9};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 157, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  } else
  #endif
  {
    __pyx_t_16 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 157, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_GIVEREF(__pyx_int_0);
    PyTuple_SET_ITEM(__pyx_t_16, 0+__pyx_t_15, __pyx_int_0);
    __Pyx_GIVEREF(__pyx_t_9);
    PyTuple_SET_ITEM(__pyx_t_16, 1+__pyx_t_15, __pyx_t_9);
    __pyx_t_9 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_16, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 157, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_19 = __Pyx_PyInt_As_long(__pyx_t_1); if (unlikely((__pyx_t_19 == (long)-1) && PyErr_Occurred())) __PYX_ERR(0, 157, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_msd = __pyx_t_19;

  /* "nngt/generation/cconnect.pyx":159
 *         long msd = np.random.randint(0, edges + 1)
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]             # <<<<<<<<<<<<<<
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edges, 2), dtype=DTYPE)
 */
  __pyx_t_5 = (__pyx_v_existing_edges == Py_None);
  if ((__pyx_t_5 != 0)) {
    __pyx_t_4 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_existing_edges, __pyx_n_s_shape); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_20 = __Pyx_PyInt_As_unsigned_int(__pyx_t_3); if (unlikely((__pyx_t_20 == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 159, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_4 = __pyx_t_20;
  }
  __pyx_v_existing = __pyx_t_4;

  /* "nngt/generation/cconnect.pyx":160
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_zeros); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":161
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edges, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges
 */
  __pyx_t_3 = __Pyx_PyInt_From_unsigned_int(__pyx_v_existing); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_16 = PyNumber_Add(__pyx_t_3, __pyx_v_edges); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_16);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_16);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_int_2);
  __pyx_t_16 = 0;

  /* "nngt/generation/cconnect.pyx":160
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_16 = PyTuple_New(1); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_3);
  __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":161
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edges, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges
 */
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_DTYPE); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_dtype, __pyx_t_9) < 0) __PYX_ERR(0, 161, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":160
 *         unsigned int existing = \
 *             0 if existing_edges is None else existing_edges.shape[0]
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:
 */
  __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_16, __pyx_t_3); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 160, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (!(likely(((__pyx_t_9) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_9, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 160, __pyx_L1_error)
  __pyx_t_21 = ((PyArrayObject *)__pyx_t_9);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_21, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_ia_edges = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf = NULL;
      __PYX_ERR(0, 160, __pyx_L1_error)
    } else {__pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_21 = 0;
  __pyx_v_ia_edges = ((PyArrayObject *)__pyx_t_9);
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":162
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:             # <<<<<<<<<<<<<<
 *         ia_edges[:existing,:] = existing_edges
 * 
 */
  __pyx_t_5 = (__pyx_v_existing != 0);
  if (__pyx_t_5) {

    /* "nngt/generation/cconnect.pyx":163
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges             # <<<<<<<<<<<<<<
 * 
 *     if b_out:
 */
    __pyx_t_9 = __Pyx_PyInt_From_unsigned_int(__pyx_v_existing); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 163, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_3 = PySlice_New(Py_None, __pyx_t_9, Py_None); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 163, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __pyx_t_9 = PyTuple_New(2); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 163, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_3);
    __Pyx_INCREF(__pyx_slice__13);
    __Pyx_GIVEREF(__pyx_slice__13);
    PyTuple_SET_ITEM(__pyx_t_9, 1, __pyx_slice__13);
    __pyx_t_3 = 0;
    if (unlikely(PyObject_SetItem(((PyObject *)__pyx_v_ia_edges), __pyx_t_9, __pyx_v_existing_edges) < 0)) __PYX_ERR(0, 163, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

    /* "nngt/generation/cconnect.pyx":162
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:             # <<<<<<<<<<<<<<
 *         ia_edges[:existing,:] = existing_edges
 * 
 */
  }

  /* "nngt/generation/cconnect.pyx":165
 *         ia_edges[:existing,:] = existing_edges
 * 
 *     if b_out:             # <<<<<<<<<<<<<<
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 */
  __pyx_t_5 = __Pyx_PyObject_IsTrue(__pyx_v_b_out); if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 165, __pyx_L1_error)
  if (__pyx_t_5) {

    /* "nngt/generation/cconnect.pyx":166
 * 
 *     if b_out:
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,             # <<<<<<<<<<<<<<
 *             idx, multigraph, directed, msd, omp)
 *     else:
 */
    __pyx_t_22 = 0;
    __pyx_t_23 = 0;
    __pyx_t_17 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_source_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 166, __pyx_L1_error)
    __pyx_t_24 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_target_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 166, __pyx_L1_error)

    /* "nngt/generation/cconnect.pyx":167
 *     if b_out:
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)             # <<<<<<<<<<<<<<
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 */
    try {
      generation::_gen_edges((&(*__Pyx_BufPtrCContig2d(size_t *, __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf, __pyx_t_22, __pyx_pybuffernd_ia_edges.diminfo[0].strides, __pyx_t_23, __pyx_pybuffernd_ia_edges.diminfo[1].strides))), __pyx_t_17, __pyx_v_degrees, __pyx_t_24, __pyx_v_old_edges, __pyx_v_idx, __pyx_v_multigraph, __pyx_v_directed, __pyx_v_msd, __pyx_v_omp);
    } catch(...) {
      __Pyx_CppExn2PyErr();
      __PYX_ERR(0, 166, __pyx_L1_error)
    }

    /* "nngt/generation/cconnect.pyx":165
 *         ia_edges[:existing,:] = existing_edges
 * 
 *     if b_out:             # <<<<<<<<<<<<<<
 *         _gen_edges(&ia_edges[0,0], source_ids, degrees, target_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 */
    goto __pyx_L4;
  }

  /* "nngt/generation/cconnect.pyx":169
 *             idx, multigraph, directed, msd, omp)
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,             # <<<<<<<<<<<<<<
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 */
  /*else*/ {
    __pyx_t_25 = 0;
    __pyx_t_26 = 0;
    __pyx_t_24 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_target_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 169, __pyx_L1_error)
    __pyx_t_17 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_source_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 169, __pyx_L1_error)

    /* "nngt/generation/cconnect.pyx":170
 *     else:
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)             # <<<<<<<<<<<<<<
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 */
    try {
      generation::_gen_edges((&(*__Pyx_BufPtrCContig2d(size_t *, __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf, __pyx_t_25, __pyx_pybuffernd_ia_edges.diminfo[0].strides, __pyx_t_26, __pyx_pybuffernd_ia_edges.diminfo[1].strides))), __pyx_t_24, __pyx_v_degrees, __pyx_t_17, __pyx_v_old_edges, __pyx_v_idx, __pyx_v_multigraph, __pyx_v_directed, __pyx_v_msd, __pyx_v_omp);
    } catch(...) {
      __Pyx_CppExn2PyErr();
      __PYX_ERR(0, 169, __pyx_L1_error)
    }
  }
  __pyx_L4:;

  /* "nngt/generation/cconnect.pyx":171
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_5 = ((!(__pyx_v_directed != 0)) != 0);
  if (__pyx_t_5) {

    /* "nngt/generation/cconnect.pyx":172
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyObject_GetItem(((PyObject *)__pyx_v_ia_edges), __pyx_tuple__16); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 172, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_16))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_16);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_16, function);
      }
    }
    if (!__pyx_t_3) {
      __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_16, __pyx_t_1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 172, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_16)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_1};
        __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_16, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 172, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_16)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_1};
        __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_16, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 172, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      {
        __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 172, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_t_7, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 172, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    if (!(likely(((__pyx_t_9) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_9, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 172, __pyx_L1_error)
    __pyx_t_21 = ((PyArrayObject *)__pyx_t_9);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_15 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_21, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_15 < 0)) {
        PyErr_Fetch(&__pyx_t_27, &__pyx_t_28, &__pyx_t_29);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_27); Py_XDECREF(__pyx_t_28); Py_XDECREF(__pyx_t_29);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_27, __pyx_t_28, __pyx_t_29);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_15 < 0)) __PYX_ERR(0, 172, __pyx_L1_error)
    }
    __pyx_t_21 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_9));
    __pyx_t_9 = 0;

    /* "nngt/generation/cconnect.pyx":173
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_16 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 173, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __pyx_t_7 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_16))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_16);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_16, function);
      }
    }
    if (!__pyx_t_7) {
      __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_16, ((PyObject *)__pyx_v_ia_edges)); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 173, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_16)) {
        PyObject *__pyx_temp[2] = {__pyx_t_7, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_16, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 173, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_9);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_16)) {
        PyObject *__pyx_temp[2] = {__pyx_t_7, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_16, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 173, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        __Pyx_GOTREF(__pyx_t_9);
      } else
      #endif
      {
        __pyx_t_1 = PyTuple_New(1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 173, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_7); __pyx_t_7 = NULL;
        __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
        __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
        PyTuple_SET_ITEM(__pyx_t_1, 0+1, ((PyObject *)__pyx_v_ia_edges));
        __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_t_1, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 173, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
    if (!(likely(((__pyx_t_9) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_9, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 173, __pyx_L1_error)
    __pyx_t_21 = ((PyArrayObject *)__pyx_t_9);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_15 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_21, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_15 < 0)) {
        PyErr_Fetch(&__pyx_t_29, &__pyx_t_28, &__pyx_t_27);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_29); Py_XDECREF(__pyx_t_28); Py_XDECREF(__pyx_t_27);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_29, __pyx_t_28, __pyx_t_27);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_15 < 0)) __PYX_ERR(0, 173, __pyx_L1_error)
    }
    __pyx_t_21 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_9));
    __pyx_t_9 = 0;

    /* "nngt/generation/cconnect.pyx":171
 *         _gen_edges(&ia_edges[0,0], target_ids, degrees, source_ids, old_edges,
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":174
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
  __pyx_r = ((PyObject *)__pyx_v_ia_edges);
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":129
 * 
 * 
 * def _gaussian_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_12);
  __Pyx_XDECREF(__pyx_t_13);
  __Pyx_XDECREF(__pyx_t_14);
  __Pyx_XDECREF(__pyx_t_16);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("nngt.generation.cconnect._gaussian_degree", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF(__pyx_v_b_out);
  __Pyx_XDECREF(__pyx_v_b_total);
  __Pyx_XDECREF(__pyx_v_edges);
  __Pyx_XDECREF(__pyx_v_b_one_pop);
  __Pyx_XDECREF((PyObject *)__pyx_v_ia_edges);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":177
 * 
 * 
 * def _random_scale_free(source_ids, target_ids, in_exp, out_exp, density,             # <<<<<<<<<<<<<<
 *                        edges, avg_deg, reciprocity, directed, multigraph,
 *                        **kwargs):
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_11_random_scale_free(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_10_random_scale_free[] = " Connect the nodes with power law distributions ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_11_random_scale_free = {"_random_scale_free", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_11_random_scale_free, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_10_random_scale_free};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_11_random_scale_free(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_source_ids = 0;
  PyObject *__pyx_v_target_ids = 0;
  PyObject *__pyx_v_in_exp = 0;
  PyObject *__pyx_v_out_exp = 0;
  PyObject *__pyx_v_density = 0;
  PyObject *__pyx_v_edges = 0;
  PyObject *__pyx_v_avg_deg = 0;
  PyObject *__pyx_v_reciprocity = 0;
  PyObject *__pyx_v_directed = 0;
  PyObject *__pyx_v_multigraph = 0;
  CYTHON_UNUSED PyObject *__pyx_v_kwargs = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_random_scale_free (wrapper)", 0);
  __pyx_v_kwargs = PyDict_New(); if (unlikely(!__pyx_v_kwargs)) return NULL;
  __Pyx_GOTREF(__pyx_v_kwargs);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_in_exp,&__pyx_n_s_out_exp,&__pyx_n_s_density,&__pyx_n_s_edges,&__pyx_n_s_avg_deg,&__pyx_n_s_reciprocity,&__pyx_n_s_directed,&__pyx_n_s_multigraph,0};
    PyObject* values[10] = {0,0,0,0,0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 10: values[9] = PyTuple_GET_ITEM(__pyx_args, 9);
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 1); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_in_exp)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 2); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_out_exp)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 3); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_density)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 4); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_edges)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 5); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_avg_deg)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 6); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  7:
        if (likely((values[7] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_reciprocity)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 7); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  8:
        if (likely((values[8] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 8); __PYX_ERR(0, 177, __pyx_L3_error)
        }
        case  9:
        if (likely((values[9] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, 9); __PYX_ERR(0, 177, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, __pyx_v_kwargs, values, pos_args, "_random_scale_free") < 0)) __PYX_ERR(0, 177, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 10) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
      values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
      values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
      values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
      values[9] = PyTuple_GET_ITEM(__pyx_args, 9);
    }
    __pyx_v_source_ids = values[0];
    __pyx_v_target_ids = values[1];
    __pyx_v_in_exp = values[2];
    __pyx_v_out_exp = values[3];
    __pyx_v_density = values[4];
    __pyx_v_edges = values[5];
    __pyx_v_avg_deg = values[6];
    __pyx_v_reciprocity = values[7];
    __pyx_v_directed = values[8];
    __pyx_v_multigraph = values[9];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_random_scale_free", 1, 10, 10, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 177, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
  __Pyx_AddTraceback("nngt.generation.cconnect._random_scale_free", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_10_random_scale_free(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_in_exp, __pyx_v_out_exp, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_reciprocity, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_kwargs);

  /* function exit code */
  __Pyx_XDECREF(__pyx_v_kwargs);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_10_random_scale_free(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_in_exp, PyObject *__pyx_v_out_exp, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, PyObject *__pyx_v_reciprocity, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs) {
  Py_ssize_t __pyx_v_num_source;
  Py_ssize_t __pyx_v_num_target;
  PyObject *__pyx_v_pre_recip_edges = NULL;
  PyObject *__pyx_v_b_one_pop = NULL;
  PyObject *__pyx_v_ia_edges = NULL;
  PyObject *__pyx_v_num_ecurrent = NULL;
  PyObject *__pyx_v_num_test = NULL;
  PyObject *__pyx_v_ia_in_deg = NULL;
  PyObject *__pyx_v_ia_out_deg = NULL;
  PyObject *__pyx_v_sum_in = NULL;
  PyObject *__pyx_v_sum_out = NULL;
  PyObject *__pyx_v_diff_in = NULL;
  PyObject *__pyx_v_diff_out = NULL;
  PyObject *__pyx_v_idx_correct_in = NULL;
  PyObject *__pyx_v_idx_correct_out = NULL;
  PyObject *__pyx_v_ia_sources = NULL;
  PyObject *__pyx_v_ia_targets = NULL;
  PyObject *__pyx_v_ia_edges_tmp = NULL;
  PyObject *__pyx_v_num_desired = NULL;
  PyObject *__pyx_v_ia_sources_tmp = NULL;
  PyObject *__pyx_v_ia_targets_tmp = NULL;
  PyObject *__pyx_v_ia_indices = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *(*__pyx_t_10)(PyObject *);
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  int __pyx_t_13;
  int __pyx_t_14;
  __Pyx_RefNannySetupContext("_random_scale_free", 0);
  __Pyx_INCREF(__pyx_v_source_ids);
  __Pyx_INCREF(__pyx_v_target_ids);
  __Pyx_INCREF(__pyx_v_edges);

  /* "nngt/generation/cconnect.pyx":181
 *                        **kwargs):
 *     ''' Connect the nodes with power law distributions '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 181, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 181, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 181, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 181, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 181, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":182
 *     ''' Connect the nodes with power law distributions '''
 *     np.random.seed()
 *     source_ids = np.array(source_ids).astype(int)             # <<<<<<<<<<<<<<
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_array); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_source_ids); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 182, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_source_ids};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_source_ids};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_source_ids);
      __Pyx_GIVEREF(__pyx_v_source_ids);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_source_ids);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_astype); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 182, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 182, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 182, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF_SET(__pyx_v_source_ids, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":183
 *     np.random.seed()
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)             # <<<<<<<<<<<<<<
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_target_ids); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_target_ids};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_target_ids};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_INCREF(__pyx_v_target_ids);
      __Pyx_GIVEREF(__pyx_v_target_ids);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_target_ids);
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_astype); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 183, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 183, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF_SET(__pyx_v_target_ids, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":184
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)             # <<<<<<<<<<<<<<
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 *                                 density, edges, avg_deg, directed, reciprocity)
 */
  __pyx_t_6 = PyObject_Length(__pyx_v_source_ids); if (unlikely(__pyx_t_6 == -1)) __PYX_ERR(0, 184, __pyx_L1_error)
  __pyx_t_7 = PyObject_Length(__pyx_v_target_ids); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 184, __pyx_L1_error)
  __pyx_v_num_source = __pyx_t_6;
  __pyx_v_num_target = __pyx_t_7;

  /* "nngt/generation/cconnect.pyx":185
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,             # <<<<<<<<<<<<<<
 *                                 density, edges, avg_deg, directed, reciprocity)
 *     b_one_pop = _check_num_edges(
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_compute_connections); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 185, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

  /* "nngt/generation/cconnect.pyx":186
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 *                                 density, edges, avg_deg, directed, reciprocity)             # <<<<<<<<<<<<<<
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, edges, directed, multigraph)
 */
  __pyx_t_5 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[8] = {__pyx_t_5, __pyx_t_3, __pyx_t_4, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_directed, __pyx_v_reciprocity};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 7+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[8] = {__pyx_t_5, __pyx_t_3, __pyx_t_4, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_directed, __pyx_v_reciprocity};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 7+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(7+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_5) {
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_5); __pyx_t_5 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_t_4);
    __Pyx_INCREF(__pyx_v_density);
    __Pyx_GIVEREF(__pyx_v_density);
    PyTuple_SET_ITEM(__pyx_t_9, 2+__pyx_t_8, __pyx_v_density);
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_9, 3+__pyx_t_8, __pyx_v_edges);
    __Pyx_INCREF(__pyx_v_avg_deg);
    __Pyx_GIVEREF(__pyx_v_avg_deg);
    PyTuple_SET_ITEM(__pyx_t_9, 4+__pyx_t_8, __pyx_v_avg_deg);
    __Pyx_INCREF(__pyx_v_directed);
    __Pyx_GIVEREF(__pyx_v_directed);
    PyTuple_SET_ITEM(__pyx_t_9, 5+__pyx_t_8, __pyx_v_directed);
    __Pyx_INCREF(__pyx_v_reciprocity);
    __Pyx_GIVEREF(__pyx_v_reciprocity);
    PyTuple_SET_ITEM(__pyx_t_9, 6+__pyx_t_8, __pyx_v_reciprocity);
    __pyx_t_3 = 0;
    __pyx_t_4 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if ((likely(PyTuple_CheckExact(__pyx_t_1))) || (PyList_CheckExact(__pyx_t_1))) {
    PyObject* sequence = __pyx_t_1;
    #if !CYTHON_COMPILING_IN_PYPY
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(0, 185, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (likely(PyTuple_CheckExact(sequence))) {
      __pyx_t_2 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_9 = PyTuple_GET_ITEM(sequence, 1); 
    } else {
      __pyx_t_2 = PyList_GET_ITEM(sequence, 0); 
      __pyx_t_9 = PyList_GET_ITEM(sequence, 1); 
    }
    __Pyx_INCREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_9);
    #else
    __pyx_t_2 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_9 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    #endif
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else {
    Py_ssize_t index = -1;
    __pyx_t_4 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 185, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_10 = Py_TYPE(__pyx_t_4)->tp_iternext;
    index = 0; __pyx_t_2 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_2)) goto __pyx_L3_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_2);
    index = 1; __pyx_t_9 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_9)) goto __pyx_L3_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_9);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_4), 2) < 0) __PYX_ERR(0, 185, __pyx_L1_error)
    __pyx_t_10 = NULL;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    goto __pyx_L4_unpacking_done;
    __pyx_L3_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_10 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    __PYX_ERR(0, 185, __pyx_L1_error)
    __pyx_L4_unpacking_done:;
  }

  /* "nngt/generation/cconnect.pyx":185
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,             # <<<<<<<<<<<<<<
 *                                 density, edges, avg_deg, directed, reciprocity)
 *     b_one_pop = _check_num_edges(
 */
  __Pyx_DECREF_SET(__pyx_v_edges, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_v_pre_recip_edges = __pyx_t_9;
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":187
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 *                                 density, edges, avg_deg, directed, reciprocity)
 *     b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *         source_ids, target_ids, edges, directed, multigraph)
 * 
 */
  __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_check_num_edges); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 187, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);

  /* "nngt/generation/cconnect.pyx":188
 *                                 density, edges, avg_deg, directed, reciprocity)
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, edges, directed, multigraph)             # <<<<<<<<<<<<<<
 * 
 *     ia_edges = np.zeros((edges,2),dtype=int)
 */
  __pyx_t_2 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  {
    __pyx_t_4 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (__pyx_t_2) {
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2); __pyx_t_2 = NULL;
    }
    __Pyx_INCREF(__pyx_v_source_ids);
    __Pyx_GIVEREF(__pyx_v_source_ids);
    PyTuple_SET_ITEM(__pyx_t_4, 0+__pyx_t_8, __pyx_v_source_ids);
    __Pyx_INCREF(__pyx_v_target_ids);
    __Pyx_GIVEREF(__pyx_v_target_ids);
    PyTuple_SET_ITEM(__pyx_t_4, 1+__pyx_t_8, __pyx_v_target_ids);
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_4, 2+__pyx_t_8, __pyx_v_edges);
    __Pyx_INCREF(__pyx_v_directed);
    __Pyx_GIVEREF(__pyx_v_directed);
    PyTuple_SET_ITEM(__pyx_t_4, 3+__pyx_t_8, __pyx_v_directed);
    __Pyx_INCREF(__pyx_v_multigraph);
    __Pyx_GIVEREF(__pyx_v_multigraph);
    PyTuple_SET_ITEM(__pyx_t_4, 4+__pyx_t_8, __pyx_v_multigraph);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 187, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_v_b_one_pop = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":190
 *         source_ids, target_ids, edges, directed, multigraph)
 * 
 *     ia_edges = np.zeros((edges,2),dtype=int)             # <<<<<<<<<<<<<<
 *     num_ecurrent, num_test = 0, 0
 * 
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_zeros); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_edges);
  __Pyx_GIVEREF(__pyx_v_edges);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_edges);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_int_2);
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_dtype, ((PyObject *)(&PyInt_Type))) < 0) __PYX_ERR(0, 190, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_4, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 190, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_ia_edges = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":191
 * 
 *     ia_edges = np.zeros((edges,2),dtype=int)
 *     num_ecurrent, num_test = 0, 0             # <<<<<<<<<<<<<<
 * 
 *     # lists containing the in/out-degrees for all nodes
 */
  __pyx_t_2 = __pyx_int_0;
  __Pyx_INCREF(__pyx_t_2);
  __pyx_t_1 = __pyx_int_0;
  __Pyx_INCREF(__pyx_t_1);
  __pyx_v_num_ecurrent = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_v_num_test = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":194
 * 
 *     # lists containing the in/out-degrees for all nodes
 *     ia_in_deg = np.random.pareto(in_exp,num_target)+1             # <<<<<<<<<<<<<<
 *     ia_out_deg = np.random.pareto(out_exp,num_source)+1
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_pareto); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_9 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_9)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_9);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_9, __pyx_v_in_exp, __pyx_t_4};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_9, __pyx_v_in_exp, __pyx_t_4};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  {
    __pyx_t_3 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (__pyx_t_9) {
      __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_9); __pyx_t_9 = NULL;
    }
    __Pyx_INCREF(__pyx_v_in_exp);
    __Pyx_GIVEREF(__pyx_v_in_exp);
    PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_8, __pyx_v_in_exp);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_8, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyInt_AddObjC(__pyx_t_1, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 194, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_ia_in_deg = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":195
 *     # lists containing the in/out-degrees for all nodes
 *     ia_in_deg = np.random.pareto(in_exp,num_target)+1
 *     ia_out_deg = np.random.pareto(out_exp,num_source)+1             # <<<<<<<<<<<<<<
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_pareto); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_4, __pyx_v_out_exp, __pyx_t_3};
    __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[3] = {__pyx_t_4, __pyx_v_out_exp, __pyx_t_3};
    __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_4) {
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_4); __pyx_t_4 = NULL;
    }
    __Pyx_INCREF(__pyx_v_out_exp);
    __Pyx_GIVEREF(__pyx_v_out_exp);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_v_out_exp);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_9, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_t_2, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 195, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_ia_out_deg = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":196
 *     ia_in_deg = np.random.pareto(in_exp,num_target)+1
 *     ia_out_deg = np.random.pareto(out_exp,num_source)+1
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)             # <<<<<<<<<<<<<<
 *     ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,
 *                                       ia_in_deg)).astype(int)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 196, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_sum); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 196, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_v_ia_in_deg); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 196, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_in_deg};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_in_deg};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_INCREF(__pyx_v_ia_in_deg);
      __Pyx_GIVEREF(__pyx_v_ia_in_deg);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_ia_in_deg);
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 196, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_sum); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 196, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_ia_out_deg); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 196, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_ia_out_deg};
      __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_ia_out_deg};
      __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    {
      __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_ia_out_deg);
      __Pyx_GIVEREF(__pyx_v_ia_out_deg);
      PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_ia_out_deg);
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_4, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 196, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_sum_in = __pyx_t_1;
  __pyx_t_1 = 0;
  __pyx_v_sum_out = __pyx_t_9;
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":197
 *     ia_out_deg = np.random.pareto(out_exp,num_source)+1
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,             # <<<<<<<<<<<<<<
 *                                       ia_in_deg)).astype(int)
 *     ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_around); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_multiply); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyNumber_Divide(__pyx_v_pre_recip_edges, __pyx_v_sum_in); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 197, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);

  /* "nngt/generation/cconnect.pyx":198
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,
 *                                       ia_in_deg)).astype(int)             # <<<<<<<<<<<<<<
 *     ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,
 *                                        ia_out_deg)).astype(int)
 */
  __pyx_t_11 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_11)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_11);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_11, __pyx_t_3, __pyx_v_ia_in_deg};
    __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_11, __pyx_t_3, __pyx_v_ia_in_deg};
    __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else
  #endif
  {
    __pyx_t_12 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    if (__pyx_t_11) {
      __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_11); __pyx_t_11 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_12, 0+__pyx_t_8, __pyx_t_3);
    __Pyx_INCREF(__pyx_v_ia_in_deg);
    __Pyx_GIVEREF(__pyx_v_ia_in_deg);
    PyTuple_SET_ITEM(__pyx_t_12, 1+__pyx_t_8, __pyx_v_ia_in_deg);
    __pyx_t_3 = 0;
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_12, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 197, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 197, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 197, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    {
      __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 197, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_12, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 197, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_astype); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 198, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_1) {
    __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_4, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 198, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_1, ((PyObject *)(&PyInt_Type))};
      __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 198, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_1, ((PyObject *)(&PyInt_Type))};
      __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 198, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    {
      __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 198, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_1); __pyx_t_1 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_12, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_12, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 198, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF_SET(__pyx_v_ia_in_deg, __pyx_t_9);
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":199
 *     ia_in_deg = np.around(np.multiply(pre_recip_edges/sum_in,
 *                                       ia_in_deg)).astype(int)
 *     ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,             # <<<<<<<<<<<<<<
 *                                        ia_out_deg)).astype(int)
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 */
  __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_around); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_multiply); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyNumber_Divide(__pyx_v_pre_recip_edges, __pyx_v_sum_out); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 199, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);

  /* "nngt/generation/cconnect.pyx":200
 *                                       ia_in_deg)).astype(int)
 *     ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,
 *                                        ia_out_deg)).astype(int)             # <<<<<<<<<<<<<<
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     while sum_in != pre_recip_edges or sum_out != pre_recip_edges:
 */
  __pyx_t_3 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_t_2, __pyx_v_ia_out_deg};
    __pyx_t_12 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 199, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_t_2, __pyx_v_ia_out_deg};
    __pyx_t_12 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 199, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  {
    __pyx_t_11 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 199, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    if (__pyx_t_3) {
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_3); __pyx_t_3 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_8, __pyx_t_2);
    __Pyx_INCREF(__pyx_v_ia_out_deg);
    __Pyx_GIVEREF(__pyx_v_ia_out_deg);
    PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_8, __pyx_v_ia_out_deg);
    __pyx_t_2 = 0;
    __pyx_t_12 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_11, NULL); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 199, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_12); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 199, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_12};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 199, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_12};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 199, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    {
      __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 199, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_12);
      PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_t_12);
      __pyx_t_12 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_11, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 199, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_astype); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 200, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_1, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 200, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 200, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 200, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    {
      __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 200, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_11, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_11, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 200, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF_SET(__pyx_v_ia_out_deg, __pyx_t_9);
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":201
 *     ia_out_deg = np.around(np.multiply(pre_recip_edges/sum_out,
 *                                        ia_out_deg)).astype(int)
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)             # <<<<<<<<<<<<<<
 *     while sum_in != pre_recip_edges or sum_out != pre_recip_edges:
 *         diff_in = sum_in-pre_recip_edges
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_11 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_sum); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_11))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_11);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_11);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_11, function);
    }
  }
  if (!__pyx_t_1) {
    __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_11, __pyx_v_ia_in_deg); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_11)) {
      PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_ia_in_deg};
      __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_11, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_11)) {
      PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_ia_in_deg};
      __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_11, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    {
      __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1); __pyx_t_1 = NULL;
      __Pyx_INCREF(__pyx_v_ia_in_deg);
      __Pyx_GIVEREF(__pyx_v_ia_in_deg);
      PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_ia_in_deg);
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_11, __pyx_t_4, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_sum); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 201, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_11 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_ia_out_deg); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 201, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_out_deg};
      __pyx_t_11 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_11);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_out_deg};
      __pyx_t_11 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_11);
    } else
    #endif
    {
      __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(__pyx_v_ia_out_deg);
      __Pyx_GIVEREF(__pyx_v_ia_out_deg);
      PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_v_ia_out_deg);
      __pyx_t_11 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_12, NULL); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 201, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF_SET(__pyx_v_sum_in, __pyx_t_9);
  __pyx_t_9 = 0;
  __Pyx_DECREF_SET(__pyx_v_sum_out, __pyx_t_11);
  __pyx_t_11 = 0;

  /* "nngt/generation/cconnect.pyx":202
 *                                        ia_out_deg)).astype(int)
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     while sum_in != pre_recip_edges or sum_out != pre_recip_edges:             # <<<<<<<<<<<<<<
 *         diff_in = sum_in-pre_recip_edges
 *         diff_out = sum_out-pre_recip_edges
 */
  while (1) {
    __pyx_t_11 = PyObject_RichCompare(__pyx_v_sum_in, __pyx_v_pre_recip_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_11); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 202, __pyx_L1_error)
    __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_11); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    if (!__pyx_t_14) {
    } else {
      __pyx_t_13 = __pyx_t_14;
      goto __pyx_L7_bool_binop_done;
    }
    __pyx_t_11 = PyObject_RichCompare(__pyx_v_sum_out, __pyx_v_pre_recip_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_11); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 202, __pyx_L1_error)
    __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_11); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __pyx_t_13 = __pyx_t_14;
    __pyx_L7_bool_binop_done:;
    if (!__pyx_t_13) break;

    /* "nngt/generation/cconnect.pyx":203
 *     sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *     while sum_in != pre_recip_edges or sum_out != pre_recip_edges:
 *         diff_in = sum_in-pre_recip_edges             # <<<<<<<<<<<<<<
 *         diff_out = sum_out-pre_recip_edges
 *         idx_correct_in = randint(0,num_target,np.abs(diff_in))
 */
    __pyx_t_11 = PyNumber_Subtract(__pyx_v_sum_in, __pyx_v_pre_recip_edges); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    __Pyx_XDECREF_SET(__pyx_v_diff_in, __pyx_t_11);
    __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":204
 *     while sum_in != pre_recip_edges or sum_out != pre_recip_edges:
 *         diff_in = sum_in-pre_recip_edges
 *         diff_out = sum_out-pre_recip_edges             # <<<<<<<<<<<<<<
 *         idx_correct_in = randint(0,num_target,np.abs(diff_in))
 *         idx_correct_out = randint(0,num_source,np.abs(diff_out))
 */
    __pyx_t_11 = PyNumber_Subtract(__pyx_v_sum_out, __pyx_v_pre_recip_edges); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 204, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    __Pyx_XDECREF_SET(__pyx_v_diff_out, __pyx_t_11);
    __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":205
 *         diff_in = sum_in-pre_recip_edges
 *         diff_out = sum_out-pre_recip_edges
 *         idx_correct_in = randint(0,num_target,np.abs(diff_in))             # <<<<<<<<<<<<<<
 *         idx_correct_out = randint(0,num_source,np.abs(diff_out))
 *         ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)
 */
    __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 205, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_1 = PyInt_FromSsize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 205, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 205, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_abs); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 205, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_12 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_v_diff_in); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_diff_in};
        __pyx_t_12 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 205, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_12);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_diff_in};
        __pyx_t_12 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 205, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_12);
      } else
      #endif
      {
        __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 205, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_INCREF(__pyx_v_diff_in);
        __Pyx_GIVEREF(__pyx_v_diff_in);
        PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_diff_in);
        __pyx_t_12 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_2, NULL); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 205, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_9);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_9, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_t_1, __pyx_t_12};
      __pyx_t_11 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_t_1, __pyx_t_12};
      __pyx_t_11 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    {
      __pyx_t_2 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      if (__pyx_t_5) {
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_5); __pyx_t_5 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_2, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_2, 1+__pyx_t_8, __pyx_t_1);
      __Pyx_GIVEREF(__pyx_t_12);
      PyTuple_SET_ITEM(__pyx_t_2, 2+__pyx_t_8, __pyx_t_12);
      __pyx_t_1 = 0;
      __pyx_t_12 = 0;
      __pyx_t_11 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_2, NULL); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_XDECREF_SET(__pyx_v_idx_correct_in, __pyx_t_11);
    __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":206
 *         diff_out = sum_out-pre_recip_edges
 *         idx_correct_in = randint(0,num_target,np.abs(diff_in))
 *         idx_correct_out = randint(0,num_source,np.abs(diff_out))             # <<<<<<<<<<<<<<
 *         ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)
 *         ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)
 */
    __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 206, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_2 = PyInt_FromSsize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 206, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 206, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_abs); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 206, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_1) {
      __pyx_t_12 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_v_diff_out); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 206, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_diff_out};
        __pyx_t_12 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 206, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_12);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_diff_out};
        __pyx_t_12 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 206, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_12);
      } else
      #endif
      {
        __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 206, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1); __pyx_t_1 = NULL;
        __Pyx_INCREF(__pyx_v_diff_out);
        __Pyx_GIVEREF(__pyx_v_diff_out);
        PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_diff_out);
        __pyx_t_12 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_4, NULL); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 206, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_9);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_9, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_t_2, __pyx_t_12};
      __pyx_t_11 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 206, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_t_2, __pyx_t_12};
      __pyx_t_11 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 206, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    {
      __pyx_t_4 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 206, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (__pyx_t_5) {
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5); __pyx_t_5 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_4, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_4, 1+__pyx_t_8, __pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_12);
      PyTuple_SET_ITEM(__pyx_t_4, 2+__pyx_t_8, __pyx_t_12);
      __pyx_t_2 = 0;
      __pyx_t_12 = 0;
      __pyx_t_11 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_4, NULL); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 206, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    }
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_XDECREF_SET(__pyx_v_idx_correct_out, __pyx_t_11);
    __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":207
 *         idx_correct_in = randint(0,num_target,np.abs(diff_in))
 *         idx_correct_out = randint(0,num_source,np.abs(diff_out))
 *         ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)             # <<<<<<<<<<<<<<
 *         ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)
 *         sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 */
    __Pyx_INCREF(__pyx_v_idx_correct_in);
    __pyx_t_11 = __pyx_v_idx_correct_in;
    __pyx_t_9 = PyObject_GetItem(__pyx_v_ia_in_deg, __pyx_t_11); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_sign); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __pyx_t_12 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_12 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_12)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_12);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_12) {
      __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_diff_in); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 207, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_12, __pyx_v_diff_in};
        __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 207, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
        __Pyx_GOTREF(__pyx_t_4);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_12, __pyx_v_diff_in};
        __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 207, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
        __Pyx_GOTREF(__pyx_t_4);
      } else
      #endif
      {
        __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 207, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_12); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_12); __pyx_t_12 = NULL;
        __Pyx_INCREF(__pyx_v_diff_in);
        __Pyx_GIVEREF(__pyx_v_diff_in);
        PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_diff_in);
        __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 207, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyNumber_Multiply(__pyx_int_1, __pyx_t_4); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyNumber_InPlaceSubtract(__pyx_t_9, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_ia_in_deg, __pyx_t_11, __pyx_t_4) < 0)) __PYX_ERR(0, 207, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":208
 *         idx_correct_out = randint(0,num_source,np.abs(diff_out))
 *         ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)
 *         ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)             # <<<<<<<<<<<<<<
 *         sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *         ia_in_deg[ia_in_deg<0] = 0
 */
    __Pyx_INCREF(__pyx_v_idx_correct_out);
    __pyx_t_11 = __pyx_v_idx_correct_out;
    __pyx_t_4 = PyObject_GetItem(__pyx_v_ia_out_deg, __pyx_t_11); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_9, __pyx_n_s_sign); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_9) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_v_diff_out); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_v_diff_out};
        __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_2);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_v_diff_out};
        __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_2);
      } else
      #endif
      {
        __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 208, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_9); __pyx_t_9 = NULL;
        __Pyx_INCREF(__pyx_v_diff_out);
        __Pyx_GIVEREF(__pyx_v_diff_out);
        PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_v_diff_out);
        __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_12, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = PyNumber_Multiply(__pyx_int_1, __pyx_t_2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyNumber_InPlaceSubtract(__pyx_t_4, __pyx_t_5); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    if (unlikely(PyObject_SetItem(__pyx_v_ia_out_deg, __pyx_t_11, __pyx_t_2) < 0)) __PYX_ERR(0, 208, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;

    /* "nngt/generation/cconnect.pyx":209
 *         ia_in_deg[idx_correct_in] -= 1*np.sign(diff_in)
 *         ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)
 *         sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)             # <<<<<<<<<<<<<<
 *         ia_in_deg[ia_in_deg<0] = 0
 *         ia_out_deg[ia_out_deg<0] = 0
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 209, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_sum); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 209, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_11 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_v_ia_in_deg); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 209, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_in_deg};
        __pyx_t_11 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_11);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_in_deg};
        __pyx_t_11 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_11);
      } else
      #endif
      {
        __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2); __pyx_t_2 = NULL;
        __Pyx_INCREF(__pyx_v_ia_in_deg);
        __Pyx_GIVEREF(__pyx_v_ia_in_deg);
        PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_ia_in_deg);
        __pyx_t_11 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_4, NULL); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 209, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_sum); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 209, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_ia_out_deg); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 209, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_out_deg};
        __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_5);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_out_deg};
        __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_5);
      } else
      #endif
      {
        __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_INCREF(__pyx_v_ia_out_deg);
        __Pyx_GIVEREF(__pyx_v_ia_out_deg);
        PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_v_ia_out_deg);
        __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_12, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 209, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_sum_in, __pyx_t_11);
    __pyx_t_11 = 0;
    __Pyx_DECREF_SET(__pyx_v_sum_out, __pyx_t_5);
    __pyx_t_5 = 0;

    /* "nngt/generation/cconnect.pyx":210
 *         ia_out_deg[idx_correct_out] -= 1*np.sign(diff_out)
 *         sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *         ia_in_deg[ia_in_deg<0] = 0             # <<<<<<<<<<<<<<
 *         ia_out_deg[ia_out_deg<0] = 0
 *     # make the edges
 */
    __pyx_t_5 = PyObject_RichCompare(__pyx_v_ia_in_deg, __pyx_int_0, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 210, __pyx_L1_error)
    if (unlikely(PyObject_SetItem(__pyx_v_ia_in_deg, __pyx_t_5, __pyx_int_0) < 0)) __PYX_ERR(0, 210, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

    /* "nngt/generation/cconnect.pyx":211
 *         sum_in, sum_out = np.sum(ia_in_deg), np.sum(ia_out_deg)
 *         ia_in_deg[ia_in_deg<0] = 0
 *         ia_out_deg[ia_out_deg<0] = 0             # <<<<<<<<<<<<<<
 *     # make the edges
 *     ia_sources = np.repeat(source_ids,ia_out_deg)
 */
    __pyx_t_5 = PyObject_RichCompare(__pyx_v_ia_out_deg, __pyx_int_0, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 211, __pyx_L1_error)
    if (unlikely(PyObject_SetItem(__pyx_v_ia_out_deg, __pyx_t_5, __pyx_int_0) < 0)) __PYX_ERR(0, 211, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  }

  /* "nngt/generation/cconnect.pyx":213
 *         ia_out_deg[ia_out_deg<0] = 0
 *     # make the edges
 *     ia_sources = np.repeat(source_ids,ia_out_deg)             # <<<<<<<<<<<<<<
 *     ia_targets = np.repeat(target_ids,ia_in_deg)
 *     np.random.shuffle(ia_targets)
 */
  __pyx_t_11 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 213, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_11, __pyx_n_s_repeat); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 213, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_11)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_11);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_11, __pyx_v_source_ids, __pyx_v_ia_out_deg};
    __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 213, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_11, __pyx_v_source_ids, __pyx_v_ia_out_deg};
    __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 213, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  {
    __pyx_t_12 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 213, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    if (__pyx_t_11) {
      __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_11); __pyx_t_11 = NULL;
    }
    __Pyx_INCREF(__pyx_v_source_ids);
    __Pyx_GIVEREF(__pyx_v_source_ids);
    PyTuple_SET_ITEM(__pyx_t_12, 0+__pyx_t_8, __pyx_v_source_ids);
    __Pyx_INCREF(__pyx_v_ia_out_deg);
    __Pyx_GIVEREF(__pyx_v_ia_out_deg);
    PyTuple_SET_ITEM(__pyx_t_12, 1+__pyx_t_8, __pyx_v_ia_out_deg);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_12, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 213, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_ia_sources = __pyx_t_5;
  __pyx_t_5 = 0;

  /* "nngt/generation/cconnect.pyx":214
 *     # make the edges
 *     ia_sources = np.repeat(source_ids,ia_out_deg)
 *     ia_targets = np.repeat(target_ids,ia_in_deg)             # <<<<<<<<<<<<<<
 *     np.random.shuffle(ia_targets)
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_repeat); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 214, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_12))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_12);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_12, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_12)) {
    PyObject *__pyx_temp[3] = {__pyx_t_2, __pyx_v_target_ids, __pyx_v_ia_in_deg};
    __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 214, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
    PyObject *__pyx_temp[3] = {__pyx_t_2, __pyx_v_target_ids, __pyx_v_ia_in_deg};
    __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 214, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  {
    __pyx_t_11 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 214, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_11);
    if (__pyx_t_2) {
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_2); __pyx_t_2 = NULL;
    }
    __Pyx_INCREF(__pyx_v_target_ids);
    __Pyx_GIVEREF(__pyx_v_target_ids);
    PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_8, __pyx_v_target_ids);
    __Pyx_INCREF(__pyx_v_ia_in_deg);
    __Pyx_GIVEREF(__pyx_v_ia_in_deg);
    PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_8, __pyx_v_ia_in_deg);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_11, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 214, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  }
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __pyx_v_ia_targets = __pyx_t_5;
  __pyx_t_5 = 0;

  /* "nngt/generation/cconnect.pyx":215
 *     ia_sources = np.repeat(source_ids,ia_out_deg)
 *     ia_targets = np.repeat(target_ids,ia_in_deg)
 *     np.random.shuffle(ia_targets)             # <<<<<<<<<<<<<<
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *     ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 */
  __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __pyx_t_11 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_random); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_11);
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_t_11, __pyx_n_s_shuffle); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 215, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  __pyx_t_11 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_12))) {
    __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_12);
    if (likely(__pyx_t_11)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
      __Pyx_INCREF(__pyx_t_11);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_12, function);
    }
  }
  if (!__pyx_t_11) {
    __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_12, __pyx_v_ia_targets); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 215, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_v_ia_targets};
      __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 215, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_v_ia_targets};
      __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 215, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    {
      __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 215, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_11); __pyx_t_11 = NULL;
      __Pyx_INCREF(__pyx_v_ia_targets);
      __Pyx_GIVEREF(__pyx_v_ia_targets);
      PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_ia_targets);
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_2, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 215, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "nngt/generation/cconnect.pyx":216
 *     ia_targets = np.repeat(target_ids,ia_in_deg)
 *     np.random.shuffle(ia_targets)
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T             # <<<<<<<<<<<<<<
 *     ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                      b_one_pop, multigraph)
 */
  __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  __pyx_t_12 = PyList_New(2); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_12);
  __Pyx_INCREF(__pyx_v_ia_sources);
  __Pyx_GIVEREF(__pyx_v_ia_sources);
  PyList_SET_ITEM(__pyx_t_12, 0, __pyx_v_ia_sources);
  __Pyx_INCREF(__pyx_v_ia_targets);
  __Pyx_GIVEREF(__pyx_v_ia_targets);
  PyList_SET_ITEM(__pyx_t_12, 1, __pyx_v_ia_targets);
  __pyx_t_11 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_11)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_11);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_11) {
    __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_12); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 216, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_t_12};
      __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_t_12};
      __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    } else
    #endif
    {
      __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_11); __pyx_t_11 = NULL;
      __Pyx_GIVEREF(__pyx_t_12);
      PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_t_12);
      __pyx_t_12 = 0;
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_4, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 216, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_T); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 216, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_v_ia_edges_tmp = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":217
 *     np.random.shuffle(ia_targets)
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *     ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                      b_one_pop, multigraph)
 * 
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_filter); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 217, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);

  /* "nngt/generation/cconnect.pyx":218
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *     ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                      b_one_pop, multigraph)             # <<<<<<<<<<<<<<
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 */
  __pyx_t_4 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[6] = {__pyx_t_4, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
    __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[6] = {__pyx_t_4, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
    __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
  #endif
  {
    __pyx_t_12 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    if (__pyx_t_4) {
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_4); __pyx_t_4 = NULL;
    }
    __Pyx_INCREF(__pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_v_ia_edges);
    PyTuple_SET_ITEM(__pyx_t_12, 0+__pyx_t_8, __pyx_v_ia_edges);
    __Pyx_INCREF(__pyx_v_ia_edges_tmp);
    __Pyx_GIVEREF(__pyx_v_ia_edges_tmp);
    PyTuple_SET_ITEM(__pyx_t_12, 1+__pyx_t_8, __pyx_v_ia_edges_tmp);
    __Pyx_INCREF(__pyx_v_num_ecurrent);
    __Pyx_GIVEREF(__pyx_v_num_ecurrent);
    PyTuple_SET_ITEM(__pyx_t_12, 2+__pyx_t_8, __pyx_v_num_ecurrent);
    __Pyx_INCREF(__pyx_v_b_one_pop);
    __Pyx_GIVEREF(__pyx_v_b_one_pop);
    PyTuple_SET_ITEM(__pyx_t_12, 3+__pyx_t_8, __pyx_v_b_one_pop);
    __Pyx_INCREF(__pyx_v_multigraph);
    __Pyx_GIVEREF(__pyx_v_multigraph);
    PyTuple_SET_ITEM(__pyx_t_12, 4+__pyx_t_8, __pyx_v_multigraph);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_12, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if ((likely(PyTuple_CheckExact(__pyx_t_2))) || (PyList_CheckExact(__pyx_t_2))) {
    PyObject* sequence = __pyx_t_2;
    #if !CYTHON_COMPILING_IN_PYPY
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(0, 217, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (likely(PyTuple_CheckExact(sequence))) {
      __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_12 = PyTuple_GET_ITEM(sequence, 1); 
    } else {
      __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
      __pyx_t_12 = PyList_GET_ITEM(sequence, 1); 
    }
    __Pyx_INCREF(__pyx_t_5);
    __Pyx_INCREF(__pyx_t_12);
    #else
    __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_12 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    #endif
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    Py_ssize_t index = -1;
    __pyx_t_4 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 217, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_10 = Py_TYPE(__pyx_t_4)->tp_iternext;
    index = 0; __pyx_t_5 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_5)) goto __pyx_L9_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_5);
    index = 1; __pyx_t_12 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_12)) goto __pyx_L9_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_12);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_4), 2) < 0) __PYX_ERR(0, 217, __pyx_L1_error)
    __pyx_t_10 = NULL;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    goto __pyx_L10_unpacking_done;
    __pyx_L9_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_10 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    __PYX_ERR(0, 217, __pyx_L1_error)
    __pyx_L10_unpacking_done:;
  }

  /* "nngt/generation/cconnect.pyx":217
 *     np.random.shuffle(ia_targets)
 *     ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *     ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                      b_one_pop, multigraph)
 * 
 */
  __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_5);
  __pyx_t_5 = 0;
  __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_12);
  __pyx_t_12 = 0;

  /* "nngt/generation/cconnect.pyx":220
 *                                      b_one_pop, multigraph)
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:             # <<<<<<<<<<<<<<
 *         num_desired = pre_recip_edges-num_ecurrent
 *         ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]
 */
  while (1) {
    __pyx_t_2 = PyObject_RichCompare(__pyx_v_num_ecurrent, __pyx_v_pre_recip_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 220, __pyx_L1_error)
    __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__pyx_t_14) {
    } else {
      __pyx_t_13 = __pyx_t_14;
      goto __pyx_L13_bool_binop_done;
    }
    __pyx_t_2 = __Pyx_PyInt_From_int(__pyx_v_4nngt_10generation_8cconnect_MAXTESTS); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_12 = PyObject_RichCompare(__pyx_v_num_test, __pyx_t_2, Py_LT); __Pyx_XGOTREF(__pyx_t_12); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_12); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 220, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __pyx_t_13 = __pyx_t_14;
    __pyx_L13_bool_binop_done:;
    if (!__pyx_t_13) break;

    /* "nngt/generation/cconnect.pyx":221
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 *         num_desired = pre_recip_edges-num_ecurrent             # <<<<<<<<<<<<<<
 *         ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
 */
    __pyx_t_12 = PyNumber_Subtract(__pyx_v_pre_recip_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 221, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_XDECREF_SET(__pyx_v_num_desired, __pyx_t_12);
    __pyx_t_12 = 0;

    /* "nngt/generation/cconnect.pyx":222
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 *         num_desired = pre_recip_edges-num_ecurrent
 *         ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]             # <<<<<<<<<<<<<<
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 222, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_v_num_desired};
      __pyx_t_12 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 222, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_12);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_v_num_desired};
      __pyx_t_12 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 222, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_12);
    } else
    #endif
    {
      __pyx_t_4 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 222, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      if (__pyx_t_5) {
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_5); __pyx_t_5 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_4, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_INCREF(__pyx_v_pre_recip_edges);
      __Pyx_GIVEREF(__pyx_v_pre_recip_edges);
      PyTuple_SET_ITEM(__pyx_t_4, 1+__pyx_t_8, __pyx_v_pre_recip_edges);
      __Pyx_INCREF(__pyx_v_num_desired);
      __Pyx_GIVEREF(__pyx_v_num_desired);
      PyTuple_SET_ITEM(__pyx_t_4, 2+__pyx_t_8, __pyx_v_num_desired);
      __pyx_t_12 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_4, NULL); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 222, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_GetItem(__pyx_v_ia_sources, __pyx_t_12); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 222, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_sources_tmp, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":223
 *         num_desired = pre_recip_edges-num_ecurrent
 *         ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 */
    __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __pyx_t_4 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_12))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_12);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_12, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[4] = {__pyx_t_4, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_v_num_desired};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[4] = {__pyx_t_4, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_v_num_desired};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 223, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      if (__pyx_t_4) {
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_INCREF(__pyx_v_pre_recip_edges);
      __Pyx_GIVEREF(__pyx_v_pre_recip_edges);
      PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_8, __pyx_v_pre_recip_edges);
      __Pyx_INCREF(__pyx_v_num_desired);
      __Pyx_GIVEREF(__pyx_v_num_desired);
      PyTuple_SET_ITEM(__pyx_t_5, 2+__pyx_t_8, __pyx_v_num_desired);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 223, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __pyx_t_12 = PyObject_GetItem(__pyx_v_ia_targets, __pyx_t_2); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 223, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_targets_tmp, __pyx_t_12);
    __pyx_t_12 = 0;

    /* "nngt/generation/cconnect.pyx":224
 *         ia_sources_tmp = ia_sources[randint(0,pre_recip_edges,num_desired)]
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T             # <<<<<<<<<<<<<<
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 224, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_array); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 224, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyList_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 224, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_v_ia_sources_tmp);
    __Pyx_GIVEREF(__pyx_v_ia_sources_tmp);
    PyList_SET_ITEM(__pyx_t_2, 0, __pyx_v_ia_sources_tmp);
    __Pyx_INCREF(__pyx_v_ia_targets_tmp);
    __Pyx_GIVEREF(__pyx_v_ia_targets_tmp);
    PyList_SET_ITEM(__pyx_t_2, 1, __pyx_v_ia_targets_tmp);
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_5);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_5, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_12 = __Pyx_PyObject_CallOneArg(__pyx_t_5, __pyx_t_2); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 224, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_12);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
        __pyx_t_12 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
        __pyx_t_12 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      {
        __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_12 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_11, NULL); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 224, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_12);
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_12, __pyx_n_s_T); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 224, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_5);
    __pyx_t_5 = 0;

    /* "nngt/generation/cconnect.pyx":225
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_filter); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 225, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);

    /* "nngt/generation/cconnect.pyx":226
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)             # <<<<<<<<<<<<<<
 *         num_test += 1
 * 
 */
    __pyx_t_11 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_12))) {
      __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_12);
      if (likely(__pyx_t_11)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
        __Pyx_INCREF(__pyx_t_11);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_12, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[6] = {__pyx_t_11, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
      PyObject *__pyx_temp[6] = {__pyx_t_11, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else
    #endif
    {
      __pyx_t_2 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      if (__pyx_t_11) {
        __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_11); __pyx_t_11 = NULL;
      }
      __Pyx_INCREF(__pyx_v_ia_edges);
      __Pyx_GIVEREF(__pyx_v_ia_edges);
      PyTuple_SET_ITEM(__pyx_t_2, 0+__pyx_t_8, __pyx_v_ia_edges);
      __Pyx_INCREF(__pyx_v_ia_edges_tmp);
      __Pyx_GIVEREF(__pyx_v_ia_edges_tmp);
      PyTuple_SET_ITEM(__pyx_t_2, 1+__pyx_t_8, __pyx_v_ia_edges_tmp);
      __Pyx_INCREF(__pyx_v_num_ecurrent);
      __Pyx_GIVEREF(__pyx_v_num_ecurrent);
      PyTuple_SET_ITEM(__pyx_t_2, 2+__pyx_t_8, __pyx_v_num_ecurrent);
      __Pyx_INCREF(__pyx_v_b_one_pop);
      __Pyx_GIVEREF(__pyx_v_b_one_pop);
      PyTuple_SET_ITEM(__pyx_t_2, 3+__pyx_t_8, __pyx_v_b_one_pop);
      __Pyx_INCREF(__pyx_v_multigraph);
      __Pyx_GIVEREF(__pyx_v_multigraph);
      PyTuple_SET_ITEM(__pyx_t_2, 4+__pyx_t_8, __pyx_v_multigraph);
      __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_2, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    if ((likely(PyTuple_CheckExact(__pyx_t_5))) || (PyList_CheckExact(__pyx_t_5))) {
      PyObject* sequence = __pyx_t_5;
      #if !CYTHON_COMPILING_IN_PYPY
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 225, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_12 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_2 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_12 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_2 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_12);
      __Pyx_INCREF(__pyx_t_2);
      #else
      __pyx_t_12 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __pyx_t_2 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      #endif
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_11 = PyObject_GetIter(__pyx_t_5); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 225, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_11)->tp_iternext;
      index = 0; __pyx_t_12 = __pyx_t_10(__pyx_t_11); if (unlikely(!__pyx_t_12)) goto __pyx_L15_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_12);
      index = 1; __pyx_t_2 = __pyx_t_10(__pyx_t_11); if (unlikely(!__pyx_t_2)) goto __pyx_L15_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_2);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_11), 2) < 0) __PYX_ERR(0, 225, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      goto __pyx_L16_unpacking_done;
      __pyx_L15_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 225, __pyx_L1_error)
      __pyx_L16_unpacking_done:;
    }

    /* "nngt/generation/cconnect.pyx":225
 *         ia_targets_tmp = ia_targets[randint(0,pre_recip_edges,num_desired)]
 *         ia_edges_tmp = np.array([ia_sources_tmp,ia_targets_tmp]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_12);
    __pyx_t_12 = 0;
    __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":227
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 *         num_test += 1             # <<<<<<<<<<<<<<
 * 
 *     if directed and reciprocity > 0:
 */
    __pyx_t_5 = __Pyx_PyInt_AddObjC(__pyx_v_num_test, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 227, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF_SET(__pyx_v_num_test, __pyx_t_5);
    __pyx_t_5 = 0;
  }

  /* "nngt/generation/cconnect.pyx":229
 *         num_test += 1
 * 
 *     if directed and reciprocity > 0:             # <<<<<<<<<<<<<<
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 */
  __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 229, __pyx_L1_error)
  if (__pyx_t_14) {
  } else {
    __pyx_t_13 = __pyx_t_14;
    goto __pyx_L18_bool_binop_done;
  }
  __pyx_t_5 = PyObject_RichCompare(__pyx_v_reciprocity, __pyx_int_0, Py_GT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 229, __pyx_L1_error)
  __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 229, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_13 = __pyx_t_14;
  __pyx_L18_bool_binop_done:;
  if (__pyx_t_13) {

    /* "nngt/generation/cconnect.pyx":230
 * 
 *     if directed and reciprocity > 0:
 *         while num_ecurrent != edges and num_test < MAXTESTS:             # <<<<<<<<<<<<<<
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 */
    while (1) {
      __pyx_t_5 = PyObject_RichCompare(__pyx_v_num_ecurrent, __pyx_v_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 230, __pyx_L1_error)
      __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 230, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      if (__pyx_t_14) {
      } else {
        __pyx_t_13 = __pyx_t_14;
        goto __pyx_L22_bool_binop_done;
      }
      __pyx_t_5 = __Pyx_PyInt_From_int(__pyx_v_4nngt_10generation_8cconnect_MAXTESTS); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 230, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_2 = PyObject_RichCompare(__pyx_v_num_test, __pyx_t_5, Py_LT); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 230, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 230, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_13 = __pyx_t_14;
      __pyx_L22_bool_binop_done:;
      if (!__pyx_t_13) break;

      /* "nngt/generation/cconnect.pyx":231
 *     if directed and reciprocity > 0:
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,             # <<<<<<<<<<<<<<
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 */
      __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 231, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);

      /* "nngt/generation/cconnect.pyx":232
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)             # <<<<<<<<<<<<<<
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 */
      __pyx_t_12 = PyNumber_Subtract(__pyx_v_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 232, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_12);
      __pyx_t_11 = NULL;
      __pyx_t_8 = 0;
      if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
        __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_5);
        if (likely(__pyx_t_11)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_11);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_5, function);
          __pyx_t_8 = 1;
        }
      }
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[4] = {__pyx_t_11, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_t_12};
        __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 231, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
        PyObject *__pyx_temp[4] = {__pyx_t_11, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_t_12};
        __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 231, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
      } else
      #endif
      {
        __pyx_t_4 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 231, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        if (__pyx_t_11) {
          __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_11); __pyx_t_11 = NULL;
        }
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_GIVEREF(__pyx_int_0);
        PyTuple_SET_ITEM(__pyx_t_4, 0+__pyx_t_8, __pyx_int_0);
        __Pyx_INCREF(__pyx_v_pre_recip_edges);
        __Pyx_GIVEREF(__pyx_v_pre_recip_edges);
        PyTuple_SET_ITEM(__pyx_t_4, 1+__pyx_t_8, __pyx_v_pre_recip_edges);
        __Pyx_GIVEREF(__pyx_t_12);
        PyTuple_SET_ITEM(__pyx_t_4, 2+__pyx_t_8, __pyx_t_12);
        __pyx_t_12 = 0;
        __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_4, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 231, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      }
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_XDECREF_SET(__pyx_v_ia_indices, __pyx_t_2);
      __pyx_t_2 = 0;

      /* "nngt/generation/cconnect.pyx":233
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]             # <<<<<<<<<<<<<<
 *             num_ecurrent = edges
 *             if not multigraph:
 */
      __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 233, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_v_ia_indices);
      __Pyx_GIVEREF(__pyx_v_ia_indices);
      PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_ia_indices);
      __Pyx_INCREF(__pyx_slice__17);
      __Pyx_GIVEREF(__pyx_slice__17);
      PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_slice__17);
      __pyx_t_5 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_t_2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 233, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_2 = PySlice_New(__pyx_v_num_ecurrent, Py_None, Py_None); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 233, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 233, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2);
      __Pyx_INCREF(__pyx_slice__18);
      __Pyx_GIVEREF(__pyx_slice__18);
      PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_slice__18);
      __pyx_t_2 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_4, __pyx_t_5) < 0)) __PYX_ERR(0, 233, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

      /* "nngt/generation/cconnect.pyx":234
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges             # <<<<<<<<<<<<<<
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 */
      __Pyx_INCREF(__pyx_v_edges);
      __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_v_edges);

      /* "nngt/generation/cconnect.pyx":235
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 *             if not multigraph:             # <<<<<<<<<<<<<<
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 */
      __pyx_t_13 = __Pyx_PyObject_IsTrue(__pyx_v_multigraph); if (unlikely(__pyx_t_13 < 0)) __PYX_ERR(0, 235, __pyx_L1_error)
      __pyx_t_14 = ((!__pyx_t_13) != 0);
      if (__pyx_t_14) {

        /* "nngt/generation/cconnect.pyx":236
 *             num_ecurrent = edges
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 */
        __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 236, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __pyx_t_2 = NULL;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
          __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
          if (likely(__pyx_t_2)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
            __Pyx_INCREF(__pyx_t_2);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_4, function);
          }
        }
        if (!__pyx_t_2) {
          __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_ia_edges); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 236, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_5);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_4)) {
            PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_edges};
            __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 236, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
            __Pyx_GOTREF(__pyx_t_5);
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
            PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_ia_edges};
            __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 236, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
            __Pyx_GOTREF(__pyx_t_5);
          } else
          #endif
          {
            __pyx_t_12 = PyTuple_New(1+1); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 236, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_12);
            __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_12, 0, __pyx_t_2); __pyx_t_2 = NULL;
            __Pyx_INCREF(__pyx_v_ia_edges);
            __Pyx_GIVEREF(__pyx_v_ia_edges);
            PyTuple_SET_ITEM(__pyx_t_12, 0+1, __pyx_v_ia_edges);
            __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_12, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 236, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_5);
            __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_DECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_5);
        __pyx_t_5 = 0;

        /* "nngt/generation/cconnect.pyx":237
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]             # <<<<<<<<<<<<<<
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 */
        __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_ia_edges_tmp, __pyx_n_s_shape); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 237, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __pyx_t_4 = __Pyx_GetItemInt(__pyx_t_5, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 237, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_4);
        __pyx_t_4 = 0;

        /* "nngt/generation/cconnect.pyx":238
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *             num_test += 1
 *     if not directed:
 */
        __pyx_t_4 = PySlice_New(Py_None, __pyx_v_num_ecurrent, Py_None); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 238, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __pyx_t_5 = PyTuple_New(2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 238, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_4);
        PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4);
        __Pyx_INCREF(__pyx_slice__19);
        __Pyx_GIVEREF(__pyx_slice__19);
        PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_slice__19);
        __pyx_t_4 = 0;
        if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_5, __pyx_v_ia_edges_tmp) < 0)) __PYX_ERR(0, 238, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

        /* "nngt/generation/cconnect.pyx":235
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 *             if not multigraph:             # <<<<<<<<<<<<<<
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 */
      }

      /* "nngt/generation/cconnect.pyx":239
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1             # <<<<<<<<<<<<<<
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 */
      __pyx_t_5 = __Pyx_PyInt_AddObjC(__pyx_v_num_test, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 239, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF_SET(__pyx_v_num_test, __pyx_t_5);
      __pyx_t_5 = 0;
    }

    /* "nngt/generation/cconnect.pyx":229
 *         num_test += 1
 * 
 *     if directed and reciprocity > 0:             # <<<<<<<<<<<<<<
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 */
  }

  /* "nngt/generation/cconnect.pyx":240
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_14 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_14 < 0)) __PYX_ERR(0, 240, __pyx_L1_error)
  __pyx_t_13 = ((!__pyx_t_14) != 0);
  if (__pyx_t_13) {

    /* "nngt/generation/cconnect.pyx":241
 *             num_test += 1
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_12 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_tuple__22); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 241, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_v_ia_edges);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_t_4);
    __pyx_t_4 = 0;
    __pyx_t_4 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_12))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_12);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_12, function);
      }
    }
    if (!__pyx_t_4) {
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_12, __pyx_t_2); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_12)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
        __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
        PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_t_2};
        __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      {
        __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 241, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_11);
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_4); __pyx_t_4 = NULL;
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_11, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 241, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_5);
    __pyx_t_5 = 0;

    /* "nngt/generation/cconnect.pyx":242
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_12 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_12)) __PYX_ERR(0, 242, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_12);
    __pyx_t_11 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_12))) {
      __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_12);
      if (likely(__pyx_t_11)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_12);
        __Pyx_INCREF(__pyx_t_11);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_12, function);
      }
    }
    if (!__pyx_t_11) {
      __pyx_t_5 = __Pyx_PyObject_CallOneArg(__pyx_t_12, __pyx_v_ia_edges); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 242, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_12)) {
        PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_v_ia_edges};
        __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 242, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_5);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_12)) {
        PyObject *__pyx_temp[2] = {__pyx_t_11, __pyx_v_ia_edges};
        __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_12, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 242, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_11); __pyx_t_11 = 0;
        __Pyx_GOTREF(__pyx_t_5);
      } else
      #endif
      {
        __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 242, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_11); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_11); __pyx_t_11 = NULL;
        __Pyx_INCREF(__pyx_v_ia_edges);
        __Pyx_GIVEREF(__pyx_v_ia_edges);
        PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_ia_edges);
        __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_12, __pyx_t_2, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 242, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_12); __pyx_t_12 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_5);
    __pyx_t_5 = 0;

    /* "nngt/generation/cconnect.pyx":240
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":243
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_ia_edges);
  __pyx_r = __pyx_v_ia_edges;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":177
 * 
 * 
 * def _random_scale_free(source_ids, target_ids, in_exp, out_exp, density,             # <<<<<<<<<<<<<<
 *                        edges, avg_deg, reciprocity, directed, multigraph,
 *                        **kwargs):
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_XDECREF(__pyx_t_12);
  __Pyx_AddTraceback("nngt.generation.cconnect._random_scale_free", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_pre_recip_edges);
  __Pyx_XDECREF(__pyx_v_b_one_pop);
  __Pyx_XDECREF(__pyx_v_ia_edges);
  __Pyx_XDECREF(__pyx_v_num_ecurrent);
  __Pyx_XDECREF(__pyx_v_num_test);
  __Pyx_XDECREF(__pyx_v_ia_in_deg);
  __Pyx_XDECREF(__pyx_v_ia_out_deg);
  __Pyx_XDECREF(__pyx_v_sum_in);
  __Pyx_XDECREF(__pyx_v_sum_out);
  __Pyx_XDECREF(__pyx_v_diff_in);
  __Pyx_XDECREF(__pyx_v_diff_out);
  __Pyx_XDECREF(__pyx_v_idx_correct_in);
  __Pyx_XDECREF(__pyx_v_idx_correct_out);
  __Pyx_XDECREF(__pyx_v_ia_sources);
  __Pyx_XDECREF(__pyx_v_ia_targets);
  __Pyx_XDECREF(__pyx_v_ia_edges_tmp);
  __Pyx_XDECREF(__pyx_v_num_desired);
  __Pyx_XDECREF(__pyx_v_ia_sources_tmp);
  __Pyx_XDECREF(__pyx_v_ia_targets_tmp);
  __Pyx_XDECREF(__pyx_v_ia_indices);
  __Pyx_XDECREF(__pyx_v_source_ids);
  __Pyx_XDECREF(__pyx_v_target_ids);
  __Pyx_XDECREF(__pyx_v_edges);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":246
 * 
 * 
 * def _erdos_renyi(source_ids, target_ids, density, edges, avg_deg, reciprocity,             # <<<<<<<<<<<<<<
 *                  directed, multigraph, **kwargs):
 *     '''
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_13_erdos_renyi(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_12_erdos_renyi[] = "\n    Returns a numpy array of dimension (2,edges) that describes the edge list\n    of an Erdos-Renyi graph.\n    @todo: perform all the calculations here\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_13_erdos_renyi = {"_erdos_renyi", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_13_erdos_renyi, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_12_erdos_renyi};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_13_erdos_renyi(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_source_ids = 0;
  PyObject *__pyx_v_target_ids = 0;
  PyObject *__pyx_v_density = 0;
  PyObject *__pyx_v_edges = 0;
  PyObject *__pyx_v_avg_deg = 0;
  PyObject *__pyx_v_reciprocity = 0;
  PyObject *__pyx_v_directed = 0;
  PyObject *__pyx_v_multigraph = 0;
  CYTHON_UNUSED PyObject *__pyx_v_kwargs = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_erdos_renyi (wrapper)", 0);
  __pyx_v_kwargs = PyDict_New(); if (unlikely(!__pyx_v_kwargs)) return NULL;
  __Pyx_GOTREF(__pyx_v_kwargs);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_density,&__pyx_n_s_edges,&__pyx_n_s_avg_deg,&__pyx_n_s_reciprocity,&__pyx_n_s_directed,&__pyx_n_s_multigraph,0};
    PyObject* values[8] = {0,0,0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 1); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_density)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 2); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_edges)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 3); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_avg_deg)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 4); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_reciprocity)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 5); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 6); __PYX_ERR(0, 246, __pyx_L3_error)
        }
        case  7:
        if (likely((values[7] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, 7); __PYX_ERR(0, 246, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, __pyx_v_kwargs, values, pos_args, "_erdos_renyi") < 0)) __PYX_ERR(0, 246, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 8) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
      values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
      values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
    }
    __pyx_v_source_ids = values[0];
    __pyx_v_target_ids = values[1];
    __pyx_v_density = values[2];
    __pyx_v_edges = values[3];
    __pyx_v_avg_deg = values[4];
    __pyx_v_reciprocity = values[5];
    __pyx_v_directed = values[6];
    __pyx_v_multigraph = values[7];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_erdos_renyi", 1, 8, 8, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 246, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
  __Pyx_AddTraceback("nngt.generation.cconnect._erdos_renyi", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_12_erdos_renyi(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_reciprocity, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_kwargs);

  /* function exit code */
  __Pyx_XDECREF(__pyx_v_kwargs);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_12_erdos_renyi(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, PyObject *__pyx_v_reciprocity, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs) {
  Py_ssize_t __pyx_v_num_source;
  Py_ssize_t __pyx_v_num_target;
  PyObject *__pyx_v_pre_recip_edges = NULL;
  PyObject *__pyx_v_b_one_pop = NULL;
  PyObject *__pyx_v_ia_edges = NULL;
  PyObject *__pyx_v_num_test = NULL;
  PyObject *__pyx_v_num_ecurrent = NULL;
  PyObject *__pyx_v_ia_sources = NULL;
  PyObject *__pyx_v_ia_targets = NULL;
  PyObject *__pyx_v_ia_edges_tmp = NULL;
  PyObject *__pyx_v_ia_indices = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  Py_ssize_t __pyx_t_6;
  Py_ssize_t __pyx_t_7;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *(*__pyx_t_10)(PyObject *);
  int __pyx_t_11;
  int __pyx_t_12;
  __Pyx_RefNannySetupContext("_erdos_renyi", 0);
  __Pyx_INCREF(__pyx_v_source_ids);
  __Pyx_INCREF(__pyx_v_target_ids);
  __Pyx_INCREF(__pyx_v_edges);

  /* "nngt/generation/cconnect.pyx":253
 *     @todo: perform all the calculations here
 *     '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 253, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 253, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 253, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":254
 *     '''
 *     np.random.seed()
 *     source_ids = np.array(source_ids).astype(int)             # <<<<<<<<<<<<<<
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 254, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_array); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 254, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_source_ids); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 254, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_source_ids};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_source_ids};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_source_ids);
      __Pyx_GIVEREF(__pyx_v_source_ids);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_source_ids);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_astype); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 254, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 254, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_5, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 254, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF_SET(__pyx_v_source_ids, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":255
 *     np.random.seed()
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)             # <<<<<<<<<<<<<<
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 255, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 255, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_target_ids); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 255, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_target_ids};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_target_ids};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_INCREF(__pyx_v_target_ids);
      __Pyx_GIVEREF(__pyx_v_target_ids);
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_target_ids);
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_astype); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 255, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 255, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_3, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 255, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF_SET(__pyx_v_target_ids, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":256
 *     source_ids = np.array(source_ids).astype(int)
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)             # <<<<<<<<<<<<<<
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 *                                 density, edges, avg_deg, directed, reciprocity)
 */
  __pyx_t_6 = PyObject_Length(__pyx_v_source_ids); if (unlikely(__pyx_t_6 == -1)) __PYX_ERR(0, 256, __pyx_L1_error)
  __pyx_t_7 = PyObject_Length(__pyx_v_target_ids); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 256, __pyx_L1_error)
  __pyx_v_num_source = __pyx_t_6;
  __pyx_v_num_target = __pyx_t_7;

  /* "nngt/generation/cconnect.pyx":257
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,             # <<<<<<<<<<<<<<
 *                                 density, edges, avg_deg, directed, reciprocity)
 * 
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_compute_connections); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 257, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyInt_FromSsize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 257, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 257, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);

  /* "nngt/generation/cconnect.pyx":258
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,
 *                                 density, edges, avg_deg, directed, reciprocity)             # <<<<<<<<<<<<<<
 * 
 *     b_one_pop = _check_num_edges(
 */
  __pyx_t_5 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[8] = {__pyx_t_5, __pyx_t_3, __pyx_t_4, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_directed, __pyx_v_reciprocity};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 7+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[8] = {__pyx_t_5, __pyx_t_3, __pyx_t_4, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_directed, __pyx_v_reciprocity};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 7+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(7+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_5) {
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_5); __pyx_t_5 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_4);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_t_4);
    __Pyx_INCREF(__pyx_v_density);
    __Pyx_GIVEREF(__pyx_v_density);
    PyTuple_SET_ITEM(__pyx_t_9, 2+__pyx_t_8, __pyx_v_density);
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_9, 3+__pyx_t_8, __pyx_v_edges);
    __Pyx_INCREF(__pyx_v_avg_deg);
    __Pyx_GIVEREF(__pyx_v_avg_deg);
    PyTuple_SET_ITEM(__pyx_t_9, 4+__pyx_t_8, __pyx_v_avg_deg);
    __Pyx_INCREF(__pyx_v_directed);
    __Pyx_GIVEREF(__pyx_v_directed);
    PyTuple_SET_ITEM(__pyx_t_9, 5+__pyx_t_8, __pyx_v_directed);
    __Pyx_INCREF(__pyx_v_reciprocity);
    __Pyx_GIVEREF(__pyx_v_reciprocity);
    PyTuple_SET_ITEM(__pyx_t_9, 6+__pyx_t_8, __pyx_v_reciprocity);
    __pyx_t_3 = 0;
    __pyx_t_4 = 0;
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if ((likely(PyTuple_CheckExact(__pyx_t_1))) || (PyList_CheckExact(__pyx_t_1))) {
    PyObject* sequence = __pyx_t_1;
    #if !CYTHON_COMPILING_IN_PYPY
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(0, 257, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (likely(PyTuple_CheckExact(sequence))) {
      __pyx_t_2 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_9 = PyTuple_GET_ITEM(sequence, 1); 
    } else {
      __pyx_t_2 = PyList_GET_ITEM(sequence, 0); 
      __pyx_t_9 = PyList_GET_ITEM(sequence, 1); 
    }
    __Pyx_INCREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_9);
    #else
    __pyx_t_2 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_9 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    #endif
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else {
    Py_ssize_t index = -1;
    __pyx_t_4 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 257, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_10 = Py_TYPE(__pyx_t_4)->tp_iternext;
    index = 0; __pyx_t_2 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_2)) goto __pyx_L3_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_2);
    index = 1; __pyx_t_9 = __pyx_t_10(__pyx_t_4); if (unlikely(!__pyx_t_9)) goto __pyx_L3_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_9);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_4), 2) < 0) __PYX_ERR(0, 257, __pyx_L1_error)
    __pyx_t_10 = NULL;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    goto __pyx_L4_unpacking_done;
    __pyx_L3_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_10 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    __PYX_ERR(0, 257, __pyx_L1_error)
    __pyx_L4_unpacking_done:;
  }

  /* "nngt/generation/cconnect.pyx":257
 *     target_ids = np.array(target_ids).astype(int)
 *     num_source, num_target = len(source_ids), len(target_ids)
 *     edges, pre_recip_edges = _compute_connections(num_source, num_target,             # <<<<<<<<<<<<<<
 *                                 density, edges, avg_deg, directed, reciprocity)
 * 
 */
  __Pyx_DECREF_SET(__pyx_v_edges, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_v_pre_recip_edges = __pyx_t_9;
  __pyx_t_9 = 0;

  /* "nngt/generation/cconnect.pyx":260
 *                                 density, edges, avg_deg, directed, reciprocity)
 * 
 *     b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *         source_ids, target_ids, edges, directed, multigraph)
 * 
 */
  __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_check_num_edges); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 260, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);

  /* "nngt/generation/cconnect.pyx":261
 * 
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, edges, directed, multigraph)             # <<<<<<<<<<<<<<
 * 
 *     ia_edges = np.zeros((edges,2), dtype=int)
 */
  __pyx_t_2 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 260, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
    PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 260, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  {
    __pyx_t_4 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (__pyx_t_2) {
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_2); __pyx_t_2 = NULL;
    }
    __Pyx_INCREF(__pyx_v_source_ids);
    __Pyx_GIVEREF(__pyx_v_source_ids);
    PyTuple_SET_ITEM(__pyx_t_4, 0+__pyx_t_8, __pyx_v_source_ids);
    __Pyx_INCREF(__pyx_v_target_ids);
    __Pyx_GIVEREF(__pyx_v_target_ids);
    PyTuple_SET_ITEM(__pyx_t_4, 1+__pyx_t_8, __pyx_v_target_ids);
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_4, 2+__pyx_t_8, __pyx_v_edges);
    __Pyx_INCREF(__pyx_v_directed);
    __Pyx_GIVEREF(__pyx_v_directed);
    PyTuple_SET_ITEM(__pyx_t_4, 3+__pyx_t_8, __pyx_v_directed);
    __Pyx_INCREF(__pyx_v_multigraph);
    __Pyx_GIVEREF(__pyx_v_multigraph);
    PyTuple_SET_ITEM(__pyx_t_4, 4+__pyx_t_8, __pyx_v_multigraph);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_4, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 260, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_v_b_one_pop = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":263
 *         source_ids, target_ids, edges, directed, multigraph)
 * 
 *     ia_edges = np.zeros((edges,2), dtype=int)             # <<<<<<<<<<<<<<
 *     num_test, num_ecurrent = 0, 0 # number of tests and current number of edges
 * 
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_zeros); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_edges);
  __Pyx_GIVEREF(__pyx_v_edges);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_edges);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_int_2);
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_dtype, ((PyObject *)(&PyInt_Type))) < 0) __PYX_ERR(0, 263, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_4, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 263, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_ia_edges = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":264
 * 
 *     ia_edges = np.zeros((edges,2), dtype=int)
 *     num_test, num_ecurrent = 0, 0 # number of tests and current number of edges             # <<<<<<<<<<<<<<
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 */
  __pyx_t_2 = __pyx_int_0;
  __Pyx_INCREF(__pyx_t_2);
  __pyx_t_1 = __pyx_int_0;
  __Pyx_INCREF(__pyx_t_1);
  __pyx_v_num_test = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_v_num_ecurrent = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":266
 *     num_test, num_ecurrent = 0, 0 # number of tests and current number of edges
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:             # <<<<<<<<<<<<<<
 *         ia_sources = source_ids[randint(0, num_source,
 *                                         pre_recip_edges-num_ecurrent)]
 */
  while (1) {
    __pyx_t_1 = PyObject_RichCompare(__pyx_v_num_ecurrent, __pyx_v_pre_recip_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 266, __pyx_L1_error)
    __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 266, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (__pyx_t_12) {
    } else {
      __pyx_t_11 = __pyx_t_12;
      goto __pyx_L7_bool_binop_done;
    }
    __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_4nngt_10generation_8cconnect_MAXTESTS); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 266, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyObject_RichCompare(__pyx_v_num_test, __pyx_t_1, Py_LT); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 266, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 266, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_11 = __pyx_t_12;
    __pyx_L7_bool_binop_done:;
    if (!__pyx_t_11) break;

    /* "nngt/generation/cconnect.pyx":267
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 *         ia_sources = source_ids[randint(0, num_source,             # <<<<<<<<<<<<<<
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_targets = target_ids[randint(0, num_target,
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 267, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyInt_FromSsize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 267, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);

    /* "nngt/generation/cconnect.pyx":268
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 *         ia_sources = source_ids[randint(0, num_source,
 *                                         pre_recip_edges-num_ecurrent)]             # <<<<<<<<<<<<<<
 *         ia_targets = target_ids[randint(0, num_target,
 *                                         pre_recip_edges-num_ecurrent)]
 */
    __pyx_t_9 = PyNumber_Subtract(__pyx_v_pre_recip_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 268, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_3 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[4] = {__pyx_t_3, __pyx_int_0, __pyx_t_4, __pyx_t_9};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 267, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[4] = {__pyx_t_3, __pyx_int_0, __pyx_t_4, __pyx_t_9};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 267, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 267, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      if (__pyx_t_3) {
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_3); __pyx_t_3 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_5, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_GIVEREF(__pyx_t_4);
      PyTuple_SET_ITEM(__pyx_t_5, 1+__pyx_t_8, __pyx_t_4);
      __Pyx_GIVEREF(__pyx_t_9);
      PyTuple_SET_ITEM(__pyx_t_5, 2+__pyx_t_8, __pyx_t_9);
      __pyx_t_4 = 0;
      __pyx_t_9 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 267, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":267
 * 
 *     while num_ecurrent != pre_recip_edges and num_test < MAXTESTS:
 *         ia_sources = source_ids[randint(0, num_source,             # <<<<<<<<<<<<<<
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_targets = target_ids[randint(0, num_target,
 */
    __pyx_t_1 = PyObject_GetItem(__pyx_v_source_ids, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 267, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_sources, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":269
 *         ia_sources = source_ids[randint(0, num_source,
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_targets = target_ids[randint(0, num_target,             # <<<<<<<<<<<<<<
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 269, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = PyInt_FromSsize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 269, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);

    /* "nngt/generation/cconnect.pyx":270
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_targets = target_ids[randint(0, num_target,
 *                                         pre_recip_edges-num_ecurrent)]             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 */
    __pyx_t_9 = PyNumber_Subtract(__pyx_v_pre_recip_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 270, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_4 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_4)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_4);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[4] = {__pyx_t_4, __pyx_int_0, __pyx_t_5, __pyx_t_9};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[4] = {__pyx_t_4, __pyx_int_0, __pyx_t_5, __pyx_t_9};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 269, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      if (__pyx_t_4) {
        __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_4); __pyx_t_4 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_GIVEREF(__pyx_t_5);
      PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_8, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_9);
      PyTuple_SET_ITEM(__pyx_t_3, 2+__pyx_t_8, __pyx_t_9);
      __pyx_t_5 = 0;
      __pyx_t_9 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":269
 *         ia_sources = source_ids[randint(0, num_source,
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_targets = target_ids[randint(0, num_target,             # <<<<<<<<<<<<<<
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 */
    __pyx_t_2 = PyObject_GetItem(__pyx_v_target_ids, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 269, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_targets, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "nngt/generation/cconnect.pyx":271
 *         ia_targets = target_ids[randint(0, num_target,
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T             # <<<<<<<<<<<<<<
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 271, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_array); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 271, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 271, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_ia_sources);
    __Pyx_GIVEREF(__pyx_v_ia_sources);
    PyList_SET_ITEM(__pyx_t_1, 0, __pyx_v_ia_sources);
    __Pyx_INCREF(__pyx_v_ia_targets);
    __Pyx_GIVEREF(__pyx_v_ia_targets);
    PyList_SET_ITEM(__pyx_t_1, 1, __pyx_v_ia_targets);
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_9) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 271, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_1};
        __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 271, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_1};
        __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 271, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      {
        __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 271, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_9); __pyx_t_9 = NULL;
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 271, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_T); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 271, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":272
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_filter); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 272, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);

    /* "nngt/generation/cconnect.pyx":273
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)             # <<<<<<<<<<<<<<
 *         num_test += 1
 * 
 */
    __pyx_t_5 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[6] = {__pyx_t_5, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
      PyObject *__pyx_temp[6] = {__pyx_t_5, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else
    #endif
    {
      __pyx_t_1 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (__pyx_t_5) {
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5); __pyx_t_5 = NULL;
      }
      __Pyx_INCREF(__pyx_v_ia_edges);
      __Pyx_GIVEREF(__pyx_v_ia_edges);
      PyTuple_SET_ITEM(__pyx_t_1, 0+__pyx_t_8, __pyx_v_ia_edges);
      __Pyx_INCREF(__pyx_v_ia_edges_tmp);
      __Pyx_GIVEREF(__pyx_v_ia_edges_tmp);
      PyTuple_SET_ITEM(__pyx_t_1, 1+__pyx_t_8, __pyx_v_ia_edges_tmp);
      __Pyx_INCREF(__pyx_v_num_ecurrent);
      __Pyx_GIVEREF(__pyx_v_num_ecurrent);
      PyTuple_SET_ITEM(__pyx_t_1, 2+__pyx_t_8, __pyx_v_num_ecurrent);
      __Pyx_INCREF(__pyx_v_b_one_pop);
      __Pyx_GIVEREF(__pyx_v_b_one_pop);
      PyTuple_SET_ITEM(__pyx_t_1, 3+__pyx_t_8, __pyx_v_b_one_pop);
      __Pyx_INCREF(__pyx_v_multigraph);
      __Pyx_GIVEREF(__pyx_v_multigraph);
      PyTuple_SET_ITEM(__pyx_t_1, 4+__pyx_t_8, __pyx_v_multigraph);
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if ((likely(PyTuple_CheckExact(__pyx_t_3))) || (PyList_CheckExact(__pyx_t_3))) {
      PyObject* sequence = __pyx_t_3;
      #if !CYTHON_COMPILING_IN_PYPY
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 272, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_2 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_1 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_2 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_1 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_1);
      #else
      __pyx_t_2 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_1 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      #endif
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_5 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 272, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_5)->tp_iternext;
      index = 0; __pyx_t_2 = __pyx_t_10(__pyx_t_5); if (unlikely(!__pyx_t_2)) goto __pyx_L9_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_2);
      index = 1; __pyx_t_1 = __pyx_t_10(__pyx_t_5); if (unlikely(!__pyx_t_1)) goto __pyx_L9_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_1);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_5), 2) < 0) __PYX_ERR(0, 272, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      goto __pyx_L10_unpacking_done;
      __pyx_L9_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 272, __pyx_L1_error)
      __pyx_L10_unpacking_done:;
    }

    /* "nngt/generation/cconnect.pyx":272
 *                                         pre_recip_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_2);
    __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":274
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 *         num_test += 1             # <<<<<<<<<<<<<<
 * 
 *     if directed and reciprocity > 0:
 */
    __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_num_test, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 274, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF_SET(__pyx_v_num_test, __pyx_t_3);
    __pyx_t_3 = 0;
  }

  /* "nngt/generation/cconnect.pyx":276
 *         num_test += 1
 * 
 *     if directed and reciprocity > 0:             # <<<<<<<<<<<<<<
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 */
  __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 276, __pyx_L1_error)
  if (__pyx_t_12) {
  } else {
    __pyx_t_11 = __pyx_t_12;
    goto __pyx_L12_bool_binop_done;
  }
  __pyx_t_3 = PyObject_RichCompare(__pyx_v_reciprocity, __pyx_int_0, Py_GT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 276, __pyx_L1_error)
  __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 276, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_11 = __pyx_t_12;
  __pyx_L12_bool_binop_done:;
  if (__pyx_t_11) {

    /* "nngt/generation/cconnect.pyx":277
 * 
 *     if directed and reciprocity > 0:
 *         while num_ecurrent != edges and num_test < MAXTESTS:             # <<<<<<<<<<<<<<
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 */
    while (1) {
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_num_ecurrent, __pyx_v_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 277, __pyx_L1_error)
      __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 277, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_12) {
      } else {
        __pyx_t_11 = __pyx_t_12;
        goto __pyx_L16_bool_binop_done;
      }
      __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_4nngt_10generation_8cconnect_MAXTESTS); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 277, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_1 = PyObject_RichCompare(__pyx_v_num_test, __pyx_t_3, Py_LT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 277, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 277, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_11 = __pyx_t_12;
      __pyx_L16_bool_binop_done:;
      if (!__pyx_t_11) break;

      /* "nngt/generation/cconnect.pyx":278
 *     if directed and reciprocity > 0:
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,             # <<<<<<<<<<<<<<
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 */
      __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 278, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);

      /* "nngt/generation/cconnect.pyx":279
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)             # <<<<<<<<<<<<<<
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 */
      __pyx_t_2 = PyNumber_Subtract(__pyx_v_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 279, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_5 = NULL;
      __pyx_t_8 = 0;
      if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
        __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
        if (likely(__pyx_t_5)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
          __Pyx_INCREF(__pyx_t_5);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_3, function);
          __pyx_t_8 = 1;
        }
      }
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_t_2};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 278, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[4] = {__pyx_t_5, __pyx_int_0, __pyx_v_pre_recip_edges, __pyx_t_2};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 278, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      {
        __pyx_t_9 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 278, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        if (__pyx_t_5) {
          __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_5); __pyx_t_5 = NULL;
        }
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_GIVEREF(__pyx_int_0);
        PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_int_0);
        __Pyx_INCREF(__pyx_v_pre_recip_edges);
        __Pyx_GIVEREF(__pyx_v_pre_recip_edges);
        PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_v_pre_recip_edges);
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_9, 2+__pyx_t_8, __pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 278, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      }
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_XDECREF_SET(__pyx_v_ia_indices, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "nngt/generation/cconnect.pyx":280
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]             # <<<<<<<<<<<<<<
 *             num_ecurrent = edges
 *             if not multigraph:
 */
      __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 280, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_INCREF(__pyx_v_ia_indices);
      __Pyx_GIVEREF(__pyx_v_ia_indices);
      PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_ia_indices);
      __Pyx_INCREF(__pyx_slice__23);
      __Pyx_GIVEREF(__pyx_slice__23);
      PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_slice__23);
      __pyx_t_3 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 280, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = PySlice_New(__pyx_v_num_ecurrent, Py_None, Py_None); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 280, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_9 = PyTuple_New(2); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 280, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_1);
      PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_1);
      __Pyx_INCREF(__pyx_slice__24);
      __Pyx_GIVEREF(__pyx_slice__24);
      PyTuple_SET_ITEM(__pyx_t_9, 1, __pyx_slice__24);
      __pyx_t_1 = 0;
      if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_9, __pyx_t_3) < 0)) __PYX_ERR(0, 280, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

      /* "nngt/generation/cconnect.pyx":281
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges             # <<<<<<<<<<<<<<
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 */
      __Pyx_INCREF(__pyx_v_edges);
      __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_v_edges);

      /* "nngt/generation/cconnect.pyx":282
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 *             if not multigraph:             # <<<<<<<<<<<<<<
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 */
      __pyx_t_11 = __Pyx_PyObject_IsTrue(__pyx_v_multigraph); if (unlikely(__pyx_t_11 < 0)) __PYX_ERR(0, 282, __pyx_L1_error)
      __pyx_t_12 = ((!__pyx_t_11) != 0);
      if (__pyx_t_12) {

        /* "nngt/generation/cconnect.pyx":283
 *             num_ecurrent = edges
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 */
        __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 283, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_1 = NULL;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
          __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_9);
          if (likely(__pyx_t_1)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
            __Pyx_INCREF(__pyx_t_1);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_9, function);
          }
        }
        if (!__pyx_t_1) {
          __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_v_ia_edges); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 283, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_9)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_ia_edges};
            __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 283, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_3);
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
            PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_ia_edges};
            __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 283, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_GOTREF(__pyx_t_3);
          } else
          #endif
          {
            __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 283, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1); __pyx_t_1 = NULL;
            __Pyx_INCREF(__pyx_v_ia_edges);
            __Pyx_GIVEREF(__pyx_v_ia_edges);
            PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_ia_edges);
            __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 283, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_XDECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_3);
        __pyx_t_3 = 0;

        /* "nngt/generation/cconnect.pyx":284
 *             if not multigraph:
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]             # <<<<<<<<<<<<<<
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 */
        __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_ia_edges_tmp, __pyx_n_s_shape); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 284, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_9 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 284, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_9);
        __pyx_t_9 = 0;

        /* "nngt/generation/cconnect.pyx":285
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *             num_test += 1
 *     if not directed:
 */
        __pyx_t_9 = PySlice_New(Py_None, __pyx_v_num_ecurrent, Py_None); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 285, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_9);
        __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 285, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_9);
        PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_9);
        __Pyx_INCREF(__pyx_slice__25);
        __Pyx_GIVEREF(__pyx_slice__25);
        PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_slice__25);
        __pyx_t_9 = 0;
        if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_3, __pyx_v_ia_edges_tmp) < 0)) __PYX_ERR(0, 285, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

        /* "nngt/generation/cconnect.pyx":282
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]
 *             num_ecurrent = edges
 *             if not multigraph:             # <<<<<<<<<<<<<<
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 */
      }

      /* "nngt/generation/cconnect.pyx":286
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1             # <<<<<<<<<<<<<<
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 */
      __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_num_test, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 286, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF_SET(__pyx_v_num_test, __pyx_t_3);
      __pyx_t_3 = 0;
    }

    /* "nngt/generation/cconnect.pyx":276
 *         num_test += 1
 * 
 *     if directed and reciprocity > 0:             # <<<<<<<<<<<<<<
 *         while num_ecurrent != edges and num_test < MAXTESTS:
 *             ia_indices = randint(0, pre_recip_edges,
 */
  }

  /* "nngt/generation/cconnect.pyx":287
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_12 < 0)) __PYX_ERR(0, 287, __pyx_L1_error)
  __pyx_t_11 = ((!__pyx_t_12) != 0);
  if (__pyx_t_11) {

    /* "nngt/generation/cconnect.pyx":288
 *             num_test += 1
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_9, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __pyx_t_9 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_tuple__28); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_v_ia_edges);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_t_9);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_9);
    __pyx_t_9 = 0;
    __pyx_t_9 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_9) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 288, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_1};
        __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 288, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_9, __pyx_t_1};
        __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 288, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      {
        __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 288, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_5);
        __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_9); __pyx_t_9 = NULL;
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_5, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 288, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":289
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_5)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_5);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_5) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_ia_edges); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 289, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_ia_edges};
        __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_GOTREF(__pyx_t_3);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_v_ia_edges};
        __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_GOTREF(__pyx_t_3);
      } else
      #endif
      {
        __pyx_t_1 = PyTuple_New(1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_5); __pyx_t_5 = NULL;
        __Pyx_INCREF(__pyx_v_ia_edges);
        __Pyx_GIVEREF(__pyx_v_ia_edges);
        PyTuple_SET_ITEM(__pyx_t_1, 0+1, __pyx_v_ia_edges);
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":287
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp
 *             num_test += 1
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":290
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_ia_edges);
  __pyx_r = __pyx_v_ia_edges;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":246
 * 
 * 
 * def _erdos_renyi(source_ids, target_ids, density, edges, avg_deg, reciprocity,             # <<<<<<<<<<<<<<
 *                  directed, multigraph, **kwargs):
 *     '''
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("nngt.generation.cconnect._erdos_renyi", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_pre_recip_edges);
  __Pyx_XDECREF(__pyx_v_b_one_pop);
  __Pyx_XDECREF(__pyx_v_ia_edges);
  __Pyx_XDECREF(__pyx_v_num_test);
  __Pyx_XDECREF(__pyx_v_num_ecurrent);
  __Pyx_XDECREF(__pyx_v_ia_sources);
  __Pyx_XDECREF(__pyx_v_ia_targets);
  __Pyx_XDECREF(__pyx_v_ia_edges_tmp);
  __Pyx_XDECREF(__pyx_v_ia_indices);
  __Pyx_XDECREF(__pyx_v_source_ids);
  __Pyx_XDECREF(__pyx_v_target_ids);
  __Pyx_XDECREF(__pyx_v_edges);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":293
 * 
 * 
 * def _price_scale_free():             # <<<<<<<<<<<<<<
 *     pass
 * 
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_15_price_scale_free(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_15_price_scale_free = {"_price_scale_free", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_15_price_scale_free, METH_NOARGS, 0};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_15_price_scale_free(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_price_scale_free (wrapper)", 0);
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_14_price_scale_free(__pyx_self);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_14_price_scale_free(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_price_scale_free", 0);

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":297
 * 
 * 
 * def _circular_graph(node_ids, coord_nb):             # <<<<<<<<<<<<<<
 *     '''
 *     Connect every node `i` to its `coord_nb` nearest neighbours on a circle
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_17_circular_graph(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_16_circular_graph[] = "\n    Connect every node `i` to its `coord_nb` nearest neighbours on a circle\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_17_circular_graph = {"_circular_graph", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_17_circular_graph, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_16_circular_graph};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_17_circular_graph(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_node_ids = 0;
  PyObject *__pyx_v_coord_nb = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_circular_graph (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_node_ids,&__pyx_n_s_coord_nb,0};
    PyObject* values[2] = {0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_node_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_coord_nb)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_circular_graph", 1, 2, 2, 1); __PYX_ERR(0, 297, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "_circular_graph") < 0)) __PYX_ERR(0, 297, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 2) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
    }
    __pyx_v_node_ids = values[0];
    __pyx_v_coord_nb = values[1];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_circular_graph", 1, 2, 2, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 297, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_AddTraceback("nngt.generation.cconnect._circular_graph", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_16_circular_graph(__pyx_self, __pyx_v_node_ids, __pyx_v_coord_nb);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_16_circular_graph(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_node_ids, PyObject *__pyx_v_coord_nb) {
  PyObject *__pyx_v_nodes = NULL;
  PyObject *__pyx_v_ia_sources = NULL;
  PyObject *__pyx_v_ia_targets = NULL;
  PyObject *__pyx_v_dist = NULL;
  PyObject *__pyx_v_neg_dist = NULL;
  PyObject *__pyx_v_pos_dist = NULL;
  PyObject *__pyx_v_ia_base = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  __Pyx_RefNannySetupContext("_circular_graph", 0);

  /* "nngt/generation/cconnect.pyx":301
 *     Connect every node `i` to its `coord_nb` nearest neighbours on a circle
 *     '''
 *     nodes = len(node_ids)             # <<<<<<<<<<<<<<
 *     ia_sources, ia_targets = np.zeros(nodes*coord_nb), np.zeros(nodes*coord_nb)
 *     ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)
 */
  __pyx_t_1 = PyObject_Length(__pyx_v_node_ids); if (unlikely(__pyx_t_1 == -1)) __PYX_ERR(0, 301, __pyx_L1_error)
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 301, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_nodes = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":302
 *     '''
 *     nodes = len(node_ids)
 *     ia_sources, ia_targets = np.zeros(nodes*coord_nb), np.zeros(nodes*coord_nb)             # <<<<<<<<<<<<<<
 *     ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)
 *     dist = coord_nb/2.
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_zeros); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyNumber_Multiply(__pyx_v_nodes, __pyx_v_coord_nb); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_3};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_3};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    {
      __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_6, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_zeros); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyNumber_Multiply(__pyx_v_nodes, __pyx_v_coord_nb); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_5 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_5) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_6); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_6};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_5, __pyx_t_6};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    {
      __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_5); __pyx_t_5 = NULL;
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_7, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 302, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_ia_sources = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_v_ia_targets = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":303
 *     nodes = len(node_ids)
 *     ia_sources, ia_targets = np.zeros(nodes*coord_nb), np.zeros(nodes*coord_nb)
 *     ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)             # <<<<<<<<<<<<<<
 *     dist = coord_nb/2.
 *     neg_dist = -int(np.floor(dist))
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 303, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_repeat); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 303, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 303, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_arange); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 303, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_6)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_int_0, __pyx_v_nodes};
    __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_7);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_int_0, __pyx_v_nodes};
    __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_7);
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_6) {
      __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_6); __pyx_t_6 = NULL;
    }
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_GIVEREF(__pyx_int_0);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_int_0);
    __Pyx_INCREF(__pyx_v_nodes);
    __Pyx_GIVEREF(__pyx_v_nodes);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_v_nodes);
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_9, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_astype); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 303, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_7 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
    }
  }
  if (!__pyx_t_7) {
    __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_5, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_5)) {
      PyObject *__pyx_temp[2] = {__pyx_t_7, ((PyObject *)(&PyInt_Type))};
      __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 303, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
      PyObject *__pyx_temp[2] = {__pyx_t_7, ((PyObject *)(&PyInt_Type))};
      __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 303, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_2);
    } else
    #endif
    {
      __pyx_t_9 = PyTuple_New(1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 303, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_7); __pyx_t_7 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_9, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_9, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 303, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_5 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_5)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_5);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_t_2, __pyx_v_coord_nb};
    __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_5, __pyx_t_2, __pyx_v_coord_nb};
    __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else
  #endif
  {
    __pyx_t_9 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_5) {
      __Pyx_GIVEREF(__pyx_t_5); PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_5); __pyx_t_5 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_8, __pyx_t_2);
    __Pyx_INCREF(__pyx_v_coord_nb);
    __Pyx_GIVEREF(__pyx_v_coord_nb);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_8, __pyx_v_coord_nb);
    __pyx_t_2 = 0;
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_9, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 303, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF_SET(__pyx_v_ia_sources, __pyx_t_4);
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":304
 *     ia_sources, ia_targets = np.zeros(nodes*coord_nb), np.zeros(nodes*coord_nb)
 *     ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)
 *     dist = coord_nb/2.             # <<<<<<<<<<<<<<
 *     neg_dist = -int(np.floor(dist))
 *     pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist
 */
  __pyx_t_4 = __Pyx_PyFloat_DivideObjC(__pyx_v_coord_nb, __pyx_float_2_, 2., 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 304, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_v_dist = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":305
 *     ia_sources = np.repeat(np.arange(0,nodes).astype(int),coord_nb)
 *     dist = coord_nb/2.
 *     neg_dist = -int(np.floor(dist))             # <<<<<<<<<<<<<<
 *     pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist
 *     ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 305, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_floor); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 305, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
    }
  }
  if (!__pyx_t_3) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_v_dist); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 305, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_dist};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 305, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_dist};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 305, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else
    #endif
    {
      __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 305, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3); __pyx_t_3 = NULL;
      __Pyx_INCREF(__pyx_v_dist);
      __Pyx_GIVEREF(__pyx_v_dist);
      PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_dist);
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_2, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 305, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = __Pyx_PyNumber_Int(__pyx_t_4); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 305, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyNumber_Negative(__pyx_t_9); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 305, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_v_neg_dist = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":306
 *     dist = coord_nb/2.
 *     neg_dist = -int(np.floor(dist))
 *     pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist             # <<<<<<<<<<<<<<
 *     ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))
 *     ia_targets = np.tile(ia_base, nodes)+ia_sources
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_floor); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_9 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_dist); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 306, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_9);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_dist};
      __pyx_t_9 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 306, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_dist};
      __pyx_t_9 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 306, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_9);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 306, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_INCREF(__pyx_v_dist);
      __Pyx_GIVEREF(__pyx_v_dist);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_v_dist);
      __pyx_t_9 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_5, NULL); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 306, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyNumber_Subtract(__pyx_v_dist, __pyx_t_9); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = PyFloat_FromDouble(__pyx_v_4nngt_10generation_8cconnect_EPS); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_5 = PyObject_RichCompare(__pyx_t_3, __pyx_t_9, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_5); if (unlikely(__pyx_t_10 < 0)) __PYX_ERR(0, 306, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (__pyx_t_10) {
    __pyx_t_5 = __Pyx_PyInt_SubtractCObj(__pyx_int_1, __pyx_v_neg_dist, 1, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 306, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_4 = __pyx_t_5;
    __pyx_t_5 = 0;
  } else {
    __pyx_t_5 = __Pyx_PyInt_SubtractCObj(__pyx_int_2, __pyx_v_neg_dist, 2, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 306, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __pyx_t_4 = __pyx_t_5;
    __pyx_t_5 = 0;
  }
  __pyx_v_pos_dist = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":307
 *     neg_dist = -int(np.floor(dist))
 *     pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist
 *     ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))             # <<<<<<<<<<<<<<
 *     ia_targets = np.tile(ia_base, nodes)+ia_sources
 *     ia_targets[ia_targets<-0.5] += nodes
 */
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_arange); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_neg_dist, __pyx_int_0};
    __pyx_t_5 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_v_neg_dist, __pyx_int_0};
    __pyx_t_5 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_5);
  } else
  #endif
  {
    __pyx_t_7 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (__pyx_t_3) {
      __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_3); __pyx_t_3 = NULL;
    }
    __Pyx_INCREF(__pyx_v_neg_dist);
    __Pyx_GIVEREF(__pyx_v_neg_dist);
    PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_8, __pyx_v_neg_dist);
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_GIVEREF(__pyx_int_0);
    PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_8, __pyx_int_0);
    __pyx_t_5 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_7, NULL); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_7 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_arange); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __pyx_t_7 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_int_1, __pyx_v_pos_dist};
    __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_int_1, __pyx_v_pos_dist};
    __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_2);
  } else
  #endif
  {
    __pyx_t_6 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_int_1);
    __Pyx_GIVEREF(__pyx_int_1);
    PyTuple_SET_ITEM(__pyx_t_6, 0+__pyx_t_8, __pyx_int_1);
    __Pyx_INCREF(__pyx_v_pos_dist);
    __Pyx_GIVEREF(__pyx_v_pos_dist);
    PyTuple_SET_ITEM(__pyx_t_6, 1+__pyx_t_8, __pyx_v_pos_dist);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_6, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 307, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_2);
  __pyx_t_5 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 307, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_3};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 307, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_3};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 307, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 307, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 307, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_v_ia_base = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":308
 *     pos_dist = 1-neg_dist if dist-np.floor(dist) < EPS else 2-neg_dist
 *     ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))
 *     ia_targets = np.tile(ia_base, nodes)+ia_sources             # <<<<<<<<<<<<<<
 *     ia_targets[ia_targets<-0.5] += nodes
 *     ia_targets[ia_targets>nodes-0.5] -= nodes
 */
  __pyx_t_9 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 308, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_9, __pyx_n_s_tile); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 308, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_5))) {
    __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_5);
    if (likely(__pyx_t_9)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_5);
      __Pyx_INCREF(__pyx_t_9);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_5, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_9, __pyx_v_ia_base, __pyx_v_nodes};
    __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 308, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_5)) {
    PyObject *__pyx_temp[3] = {__pyx_t_9, __pyx_v_ia_base, __pyx_v_nodes};
    __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_5, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 308, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
  #endif
  {
    __pyx_t_3 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 308, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (__pyx_t_9) {
      __Pyx_GIVEREF(__pyx_t_9); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_9); __pyx_t_9 = NULL;
    }
    __Pyx_INCREF(__pyx_v_ia_base);
    __Pyx_GIVEREF(__pyx_v_ia_base);
    PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_8, __pyx_v_ia_base);
    __Pyx_INCREF(__pyx_v_nodes);
    __Pyx_GIVEREF(__pyx_v_nodes);
    PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_8, __pyx_v_nodes);
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_5, __pyx_t_3, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 308, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyNumber_Add(__pyx_t_4, __pyx_v_ia_sources); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 308, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF_SET(__pyx_v_ia_targets, __pyx_t_5);
  __pyx_t_5 = 0;

  /* "nngt/generation/cconnect.pyx":309
 *     ia_base = np.concatenate((np.arange(neg_dist,0),np.arange(1,pos_dist)))
 *     ia_targets = np.tile(ia_base, nodes)+ia_sources
 *     ia_targets[ia_targets<-0.5] += nodes             # <<<<<<<<<<<<<<
 *     ia_targets[ia_targets>nodes-0.5] -= nodes
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 */
  __pyx_t_5 = PyObject_RichCompare(__pyx_v_ia_targets, __pyx_float_neg_0_5, Py_LT); __Pyx_XGOTREF(__pyx_t_5); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 309, __pyx_L1_error)
  __pyx_t_4 = PyObject_GetItem(__pyx_v_ia_targets, __pyx_t_5); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 309, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_t_4, __pyx_v_nodes); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 309, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (unlikely(PyObject_SetItem(__pyx_v_ia_targets, __pyx_t_5, __pyx_t_3) < 0)) __PYX_ERR(0, 309, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;

  /* "nngt/generation/cconnect.pyx":310
 *     ia_targets = np.tile(ia_base, nodes)+ia_sources
 *     ia_targets[ia_targets<-0.5] += nodes
 *     ia_targets[ia_targets>nodes-0.5] -= nodes             # <<<<<<<<<<<<<<
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 * 
 */
  __pyx_t_5 = __Pyx_PyFloat_SubtractObjC(__pyx_v_nodes, __pyx_float_0_5, 0.5, 0); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 310, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_3 = PyObject_RichCompare(__pyx_v_ia_targets, __pyx_t_5, Py_GT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 310, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_GetItem(__pyx_v_ia_targets, __pyx_t_3); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 310, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_4 = PyNumber_InPlaceSubtract(__pyx_t_5, __pyx_v_nodes); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 310, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  if (unlikely(PyObject_SetItem(__pyx_v_ia_targets, __pyx_t_3, __pyx_t_4) < 0)) __PYX_ERR(0, 310, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":311
 *     ia_targets[ia_targets<-0.5] += nodes
 *     ia_targets[ia_targets>nodes-0.5] -= nodes
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T             # <<<<<<<<<<<<<<
 * 
 * def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s_array); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
  __pyx_t_5 = PyObject_GetItem(__pyx_v_node_ids, __pyx_v_ia_sources); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_5);
  __pyx_t_2 = PyObject_GetItem(__pyx_v_node_ids, __pyx_v_ia_targets); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = PyList_New(2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_5);
  PyList_SET_ITEM(__pyx_t_6, 0, __pyx_t_5);
  __Pyx_GIVEREF(__pyx_t_2);
  PyList_SET_ITEM(__pyx_t_6, 1, __pyx_t_2);
  __pyx_t_5 = 0;
  __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_9, __pyx_t_6); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 311, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_5, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_astype); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_9))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_9);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_9);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_9, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_9, ((PyObject *)(&PyInt_Type))); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 311, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_9)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, ((PyObject *)(&PyInt_Type))};
      __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_9, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else
    #endif
    {
      __pyx_t_5 = PyTuple_New(1+1); if (unlikely(!__pyx_t_5)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(((PyObject *)(&PyInt_Type)));
      __Pyx_GIVEREF(((PyObject *)(&PyInt_Type)));
      PyTuple_SET_ITEM(__pyx_t_5, 0+1, ((PyObject *)(&PyInt_Type)));
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_9, __pyx_t_5, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 311, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_T); if (unlikely(!__pyx_t_9)) __PYX_ERR(0, 311, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_9);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_9;
  __pyx_t_9 = 0;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":297
 * 
 * 
 * def _circular_graph(node_ids, coord_nb):             # <<<<<<<<<<<<<<
 *     '''
 *     Connect every node `i` to its `coord_nb` nearest neighbours on a circle
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("nngt.generation.cconnect._circular_graph", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_nodes);
  __Pyx_XDECREF(__pyx_v_ia_sources);
  __Pyx_XDECREF(__pyx_v_ia_targets);
  __Pyx_XDECREF(__pyx_v_dist);
  __Pyx_XDECREF(__pyx_v_neg_dist);
  __Pyx_XDECREF(__pyx_v_pos_dist);
  __Pyx_XDECREF(__pyx_v_ia_base);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":313
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 * 
 * def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,             # <<<<<<<<<<<<<<
 *                   directed, multigraph, **kwargs):
 *     '''
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_19_newman_watts(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_18_newman_watts[] = "\n    Returns a numpy array of dimension (num_edges,2) that describes the edge \n    list of a Newmaan-Watts graph.\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_19_newman_watts = {"_newman_watts", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_19_newman_watts, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_18_newman_watts};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_19_newman_watts(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_source_ids = 0;
  PyObject *__pyx_v_target_ids = 0;
  PyObject *__pyx_v_coord_nb = 0;
  PyObject *__pyx_v_proba_shortcut = 0;
  PyObject *__pyx_v_directed = 0;
  PyObject *__pyx_v_multigraph = 0;
  CYTHON_UNUSED PyObject *__pyx_v_kwargs = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_newman_watts (wrapper)", 0);
  __pyx_v_kwargs = PyDict_New(); if (unlikely(!__pyx_v_kwargs)) return NULL;
  __Pyx_GOTREF(__pyx_v_kwargs);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_coord_nb,&__pyx_n_s_proba_shortcut,&__pyx_n_s_directed,&__pyx_n_s_multigraph,0};
    PyObject* values[6] = {0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, 1); __PYX_ERR(0, 313, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_coord_nb)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, 2); __PYX_ERR(0, 313, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_proba_shortcut)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, 3); __PYX_ERR(0, 313, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, 4); __PYX_ERR(0, 313, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, 5); __PYX_ERR(0, 313, __pyx_L3_error)
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, __pyx_v_kwargs, values, pos_args, "_newman_watts") < 0)) __PYX_ERR(0, 313, __pyx_L3_error)
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 6) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
    }
    __pyx_v_source_ids = values[0];
    __pyx_v_target_ids = values[1];
    __pyx_v_coord_nb = values[2];
    __pyx_v_proba_shortcut = values[3];
    __pyx_v_directed = values[4];
    __pyx_v_multigraph = values[5];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_newman_watts", 1, 6, 6, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 313, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
  __Pyx_AddTraceback("nngt.generation.cconnect._newman_watts", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_18_newman_watts(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_coord_nb, __pyx_v_proba_shortcut, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_kwargs);

  /* function exit code */
  __Pyx_XDECREF(__pyx_v_kwargs);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_18_newman_watts(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_source_ids, PyObject *__pyx_v_target_ids, PyObject *__pyx_v_coord_nb, PyObject *__pyx_v_proba_shortcut, PyObject *__pyx_v_directed, PyObject *__pyx_v_multigraph, CYTHON_UNUSED PyObject *__pyx_v_kwargs) {
  PyObject *__pyx_v_node_ids = NULL;
  PyObject *__pyx_v_nodes = NULL;
  PyObject *__pyx_v_circular_edges = NULL;
  PyObject *__pyx_v_num_edges = NULL;
  PyObject *__pyx_v_b_one_pop = NULL;
  PyObject *__pyx_v_ia_edges = NULL;
  PyObject *__pyx_v_num_test = NULL;
  PyObject *__pyx_v_num_ecurrent = NULL;
  PyObject *__pyx_v_ia_sources = NULL;
  PyObject *__pyx_v_ia_targets = NULL;
  PyObject *__pyx_v_ia_edges_tmp = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  Py_ssize_t __pyx_t_5;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  int __pyx_t_8;
  int __pyx_t_9;
  PyObject *(*__pyx_t_10)(PyObject *);
  __Pyx_RefNannySetupContext("_newman_watts", 0);
  __Pyx_INCREF(__pyx_v_target_ids);

  /* "nngt/generation/cconnect.pyx":319
 *     list of a Newmaan-Watts graph.
 *     '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     node_ids = np.array(source_ids, dtype=int)
 *     target_ids = np.array(target_ids, dtype=int)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 319, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 319, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 319, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 319, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 319, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":320
 *     '''
 *     np.random.seed()
 *     node_ids = np.array(source_ids, dtype=int)             # <<<<<<<<<<<<<<
 *     target_ids = np.array(target_ids, dtype=int)
 *     nodes = len(node_ids)
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 320, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 320, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 320, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_v_source_ids);
  __Pyx_GIVEREF(__pyx_v_source_ids);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_source_ids);
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 320, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  if (PyDict_SetItem(__pyx_t_3, __pyx_n_s_dtype, ((PyObject *)(&PyInt_Type))) < 0) __PYX_ERR(0, 320, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 320, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_node_ids = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":321
 *     np.random.seed()
 *     node_ids = np.array(source_ids, dtype=int)
 *     target_ids = np.array(target_ids, dtype=int)             # <<<<<<<<<<<<<<
 *     nodes = len(node_ids)
 *     circular_edges = nodes*coord_nb
 */
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 321, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_array); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 321, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 321, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_INCREF(__pyx_v_target_ids);
  __Pyx_GIVEREF(__pyx_v_target_ids);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_target_ids);
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 321, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_dtype, ((PyObject *)(&PyInt_Type))) < 0) __PYX_ERR(0, 321, __pyx_L1_error)
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_4, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 321, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF_SET(__pyx_v_target_ids, __pyx_t_2);
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":322
 *     node_ids = np.array(source_ids, dtype=int)
 *     target_ids = np.array(target_ids, dtype=int)
 *     nodes = len(node_ids)             # <<<<<<<<<<<<<<
 *     circular_edges = nodes*coord_nb
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 */
  __pyx_t_5 = PyObject_Length(__pyx_v_node_ids); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 322, __pyx_L1_error)
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_5); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 322, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_nodes = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":323
 *     target_ids = np.array(target_ids, dtype=int)
 *     nodes = len(node_ids)
 *     circular_edges = nodes*coord_nb             # <<<<<<<<<<<<<<
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 *     num_edges, circular_edges = (num_edges, circular_edges if directed
 */
  __pyx_t_2 = PyNumber_Multiply(__pyx_v_nodes, __pyx_v_coord_nb); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 323, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_circular_edges = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":324
 *     nodes = len(node_ids)
 *     circular_edges = nodes*coord_nb
 *     num_edges = int(circular_edges*(1+proba_shortcut))             # <<<<<<<<<<<<<<
 *     num_edges, circular_edges = (num_edges, circular_edges if directed
 *                              else (int(num_edges/2), int(circular_edges/2)))
 */
  __pyx_t_2 = __Pyx_PyInt_AddCObj(__pyx_int_1, __pyx_v_proba_shortcut, 1, 0); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 324, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyNumber_Multiply(__pyx_v_circular_edges, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 324, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyNumber_Int(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 324, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_num_edges = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":325
 *     circular_edges = nodes*coord_nb
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 *     num_edges, circular_edges = (num_edges, circular_edges if directed             # <<<<<<<<<<<<<<
 *                              else (int(num_edges/2), int(circular_edges/2)))
 * 
 */
  __pyx_t_2 = __pyx_v_num_edges;
  __Pyx_INCREF(__pyx_t_2);

  /* "nngt/generation/cconnect.pyx":326
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 *     num_edges, circular_edges = (num_edges, circular_edges if directed
 *                              else (int(num_edges/2), int(circular_edges/2)))             # <<<<<<<<<<<<<<
 * 
 *     b_one_pop = _check_num_edges(
 */
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 326, __pyx_L1_error)
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":325
 *     circular_edges = nodes*coord_nb
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 *     num_edges, circular_edges = (num_edges, circular_edges if directed             # <<<<<<<<<<<<<<
 *                              else (int(num_edges/2), int(circular_edges/2)))
 * 
 */
    __Pyx_INCREF(__pyx_v_circular_edges);
    __pyx_t_1 = __pyx_v_circular_edges;
  } else {

    /* "nngt/generation/cconnect.pyx":326
 *     num_edges = int(circular_edges*(1+proba_shortcut))
 *     num_edges, circular_edges = (num_edges, circular_edges if directed
 *                              else (int(num_edges/2), int(circular_edges/2)))             # <<<<<<<<<<<<<<
 * 
 *     b_one_pop = _check_num_edges(
 */
    __pyx_t_4 = __Pyx_PyNumber_Divide(__pyx_v_num_edges, __pyx_int_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 326, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_3 = __Pyx_PyNumber_Int(__pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 326, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = __Pyx_PyNumber_Divide(__pyx_v_circular_edges, __pyx_int_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 326, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_7 = __Pyx_PyNumber_Int(__pyx_t_4); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 326, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 326, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_7);
    __pyx_t_3 = 0;
    __pyx_t_7 = 0;
    __pyx_t_1 = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __Pyx_DECREF_SET(__pyx_v_num_edges, __pyx_t_2);
  __pyx_t_2 = 0;
  __Pyx_DECREF_SET(__pyx_v_circular_edges, __pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":328
 *                              else (int(num_edges/2), int(circular_edges/2)))
 * 
 *     b_one_pop = _check_num_edges(             # <<<<<<<<<<<<<<
 *         source_ids, target_ids, num_edges, directed, multigraph)
 *     if not b_one_pop:
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_check_num_edges); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 328, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);

  /* "nngt/generation/cconnect.pyx":329
 * 
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, num_edges, directed, multigraph)             # <<<<<<<<<<<<<<
 *     if not b_one_pop:
 *         raise InvalidArgument("This graph model can only be used if source \
 */
  __pyx_t_4 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[6] = {__pyx_t_4, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_num_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 328, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[6] = {__pyx_t_4, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_num_edges, __pyx_v_directed, __pyx_v_multigraph};
    __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 328, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else
  #endif
  {
    __pyx_t_7 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 328, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    if (__pyx_t_4) {
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_4); __pyx_t_4 = NULL;
    }
    __Pyx_INCREF(__pyx_v_source_ids);
    __Pyx_GIVEREF(__pyx_v_source_ids);
    PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_8, __pyx_v_source_ids);
    __Pyx_INCREF(__pyx_v_target_ids);
    __Pyx_GIVEREF(__pyx_v_target_ids);
    PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_8, __pyx_v_target_ids);
    __Pyx_INCREF(__pyx_v_num_edges);
    __Pyx_GIVEREF(__pyx_v_num_edges);
    PyTuple_SET_ITEM(__pyx_t_7, 2+__pyx_t_8, __pyx_v_num_edges);
    __Pyx_INCREF(__pyx_v_directed);
    __Pyx_GIVEREF(__pyx_v_directed);
    PyTuple_SET_ITEM(__pyx_t_7, 3+__pyx_t_8, __pyx_v_directed);
    __Pyx_INCREF(__pyx_v_multigraph);
    __Pyx_GIVEREF(__pyx_v_multigraph);
    PyTuple_SET_ITEM(__pyx_t_7, 4+__pyx_t_8, __pyx_v_multigraph);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_7, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 328, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_b_one_pop = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":330
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, num_edges, directed, multigraph)
 *     if not b_one_pop:             # <<<<<<<<<<<<<<
 *         raise InvalidArgument("This graph model can only be used if source \
 *                               and target populations are the same")
 */
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_v_b_one_pop); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 330, __pyx_L1_error)
  __pyx_t_9 = ((!__pyx_t_6) != 0);
  if (__pyx_t_9) {

    /* "nngt/generation/cconnect.pyx":331
 *         source_ids, target_ids, num_edges, directed, multigraph)
 *     if not b_one_pop:
 *         raise InvalidArgument("This graph model can only be used if source \             # <<<<<<<<<<<<<<
 *                               and target populations are the same")
 *     # generate the initial circular graph
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_InvalidArgument); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 331, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__29, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 331, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_Raise(__pyx_t_2, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __PYX_ERR(0, 331, __pyx_L1_error)

    /* "nngt/generation/cconnect.pyx":330
 *     b_one_pop = _check_num_edges(
 *         source_ids, target_ids, num_edges, directed, multigraph)
 *     if not b_one_pop:             # <<<<<<<<<<<<<<
 *         raise InvalidArgument("This graph model can only be used if source \
 *                               and target populations are the same")
 */
  }

  /* "nngt/generation/cconnect.pyx":334
 *                               and target populations are the same")
 *     # generate the initial circular graph
 *     ia_edges = np.zeros((num_edges,2),dtype=int)             # <<<<<<<<<<<<<<
 *     ia_edges[:circular_edges,:] = _circular_graph(node_ids, coord_nb)
 *     # add the random connections
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_zeros); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_v_num_edges);
  __Pyx_GIVEREF(__pyx_v_num_edges);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_num_edges);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_int_2);
  __pyx_t_7 = PyTuple_New(1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_dtype, ((PyObject *)(&PyInt_Type))) < 0) __PYX_ERR(0, 334, __pyx_L1_error)
  __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_7, __pyx_t_2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 334, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_ia_edges = __pyx_t_4;
  __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":335
 *     # generate the initial circular graph
 *     ia_edges = np.zeros((num_edges,2),dtype=int)
 *     ia_edges[:circular_edges,:] = _circular_graph(node_ids, coord_nb)             # <<<<<<<<<<<<<<
 *     # add the random connections
 *     num_test, num_ecurrent = 0, circular_edges
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_circular_graph); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = NULL;
  __pyx_t_8 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_7)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_7);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_8 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_v_node_ids, __pyx_v_coord_nb};
    __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 335, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
    PyObject *__pyx_temp[3] = {__pyx_t_7, __pyx_v_node_ids, __pyx_v_coord_nb};
    __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-__pyx_t_8, 2+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 335, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_GOTREF(__pyx_t_4);
  } else
  #endif
  {
    __pyx_t_1 = PyTuple_New(2+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 335, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    if (__pyx_t_7) {
      __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_7); __pyx_t_7 = NULL;
    }
    __Pyx_INCREF(__pyx_v_node_ids);
    __Pyx_GIVEREF(__pyx_v_node_ids);
    PyTuple_SET_ITEM(__pyx_t_1, 0+__pyx_t_8, __pyx_v_node_ids);
    __Pyx_INCREF(__pyx_v_coord_nb);
    __Pyx_GIVEREF(__pyx_v_coord_nb);
    PyTuple_SET_ITEM(__pyx_t_1, 1+__pyx_t_8, __pyx_v_coord_nb);
    __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_1, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 335, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PySlice_New(Py_None, __pyx_v_circular_edges, Py_None); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2);
  __Pyx_INCREF(__pyx_slice__30);
  __Pyx_GIVEREF(__pyx_slice__30);
  PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_slice__30);
  __pyx_t_2 = 0;
  if (unlikely(PyObject_SetItem(__pyx_v_ia_edges, __pyx_t_1, __pyx_t_4) < 0)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "nngt/generation/cconnect.pyx":337
 *     ia_edges[:circular_edges,:] = _circular_graph(node_ids, coord_nb)
 *     # add the random connections
 *     num_test, num_ecurrent = 0, circular_edges             # <<<<<<<<<<<<<<
 *     while num_ecurrent != num_edges and num_test < MAXTESTS:
 *         ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 */
  __pyx_t_4 = __pyx_int_0;
  __Pyx_INCREF(__pyx_t_4);
  __pyx_t_1 = __pyx_v_circular_edges;
  __Pyx_INCREF(__pyx_t_1);
  __pyx_v_num_test = __pyx_t_4;
  __pyx_t_4 = 0;
  __pyx_v_num_ecurrent = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":338
 *     # add the random connections
 *     num_test, num_ecurrent = 0, circular_edges
 *     while num_ecurrent != num_edges and num_test < MAXTESTS:             # <<<<<<<<<<<<<<
 *         ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 */
  while (1) {
    __pyx_t_1 = PyObject_RichCompare(__pyx_v_num_ecurrent, __pyx_v_num_edges, Py_NE); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 338, __pyx_L1_error)
    __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 338, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (__pyx_t_6) {
    } else {
      __pyx_t_9 = __pyx_t_6;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_1 = __Pyx_PyInt_From_int(__pyx_v_4nngt_10generation_8cconnect_MAXTESTS); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 338, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyObject_RichCompare(__pyx_v_num_test, __pyx_t_1, Py_LT); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 338, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(0, 338, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_9 = __pyx_t_6;
    __pyx_L6_bool_binop_done:;
    if (!__pyx_t_9) break;

    /* "nngt/generation/cconnect.pyx":339
 *     num_test, num_ecurrent = 0, circular_edges
 *     while num_ecurrent != num_edges and num_test < MAXTESTS:
 *         ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]             # <<<<<<<<<<<<<<
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = PyNumber_Subtract(__pyx_v_num_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 339, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_7 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_7)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_7);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[4] = {__pyx_t_7, __pyx_int_0, __pyx_v_nodes, __pyx_t_2};
      __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 339, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[4] = {__pyx_t_7, __pyx_int_0, __pyx_v_nodes, __pyx_t_2};
      __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 339, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    {
      __pyx_t_3 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 339, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      if (__pyx_t_7) {
        __Pyx_GIVEREF(__pyx_t_7); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_7); __pyx_t_7 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_INCREF(__pyx_v_nodes);
      __Pyx_GIVEREF(__pyx_v_nodes);
      PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_8, __pyx_v_nodes);
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_3, 2+__pyx_t_8, __pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 339, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_GetItem(__pyx_v_node_ids, __pyx_t_4); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_sources, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":340
 *     while num_ecurrent != num_edges and num_test < MAXTESTS:
 *         ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]             # <<<<<<<<<<<<<<
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_randint); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 340, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_3 = PyNumber_Subtract(__pyx_v_num_edges, __pyx_v_num_ecurrent); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 340, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[4] = {__pyx_t_2, __pyx_int_0, __pyx_v_nodes, __pyx_t_3};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 340, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[4] = {__pyx_t_2, __pyx_int_0, __pyx_v_nodes, __pyx_t_3};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-__pyx_t_8, 3+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 340, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else
    #endif
    {
      __pyx_t_7 = PyTuple_New(3+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 340, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      if (__pyx_t_2) {
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2); __pyx_t_2 = NULL;
      }
      __Pyx_INCREF(__pyx_int_0);
      __Pyx_GIVEREF(__pyx_int_0);
      PyTuple_SET_ITEM(__pyx_t_7, 0+__pyx_t_8, __pyx_int_0);
      __Pyx_INCREF(__pyx_v_nodes);
      __Pyx_GIVEREF(__pyx_v_nodes);
      PyTuple_SET_ITEM(__pyx_t_7, 1+__pyx_t_8, __pyx_v_nodes);
      __Pyx_GIVEREF(__pyx_t_3);
      PyTuple_SET_ITEM(__pyx_t_7, 2+__pyx_t_8, __pyx_t_3);
      __pyx_t_3 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_7, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 340, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_4 = PyObject_GetItem(__pyx_v_node_ids, __pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 340, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_targets, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "nngt/generation/cconnect.pyx":341
 *         ia_sources = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T             # <<<<<<<<<<<<<<
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 341, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_array); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 341, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 341, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_ia_sources);
    __Pyx_GIVEREF(__pyx_v_ia_sources);
    PyList_SET_ITEM(__pyx_t_1, 0, __pyx_v_ia_sources);
    __Pyx_INCREF(__pyx_v_ia_targets);
    __Pyx_GIVEREF(__pyx_v_ia_targets);
    PyList_SET_ITEM(__pyx_t_1, 1, __pyx_v_ia_targets);
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_7))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_7);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_7);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_7, function);
      }
    }
    if (!__pyx_t_3) {
      __pyx_t_4 = __Pyx_PyObject_CallOneArg(__pyx_t_7, __pyx_t_1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 341, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_GOTREF(__pyx_t_4);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_7)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_1};
        __pyx_t_4 = __Pyx_PyFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 341, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_7)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_1};
        __pyx_t_4 = __Pyx_PyCFunction_FastCall(__pyx_t_7, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 341, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else
      #endif
      {
        __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 341, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_7, __pyx_t_2, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 341, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __pyx_t_7 = __Pyx_PyObject_GetAttrStr(__pyx_t_4, __pyx_n_s_T); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 341, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __Pyx_XDECREF_SET(__pyx_v_ia_edges_tmp, __pyx_t_7);
    __pyx_t_7 = 0;

    /* "nngt/generation/cconnect.pyx":342
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_filter); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 342, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);

    /* "nngt/generation/cconnect.pyx":343
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)             # <<<<<<<<<<<<<<
 *         num_test += 1
 *     ia_edges = _no_self_loops(ia_edges)
 */
    __pyx_t_2 = NULL;
    __pyx_t_8 = 0;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_8 = 1;
      }
    }
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_4, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_4)) {
      PyObject *__pyx_temp[6] = {__pyx_t_2, __pyx_v_ia_edges, __pyx_v_ia_edges_tmp, __pyx_v_num_ecurrent, __pyx_v_b_one_pop, __pyx_v_multigraph};
      __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_4, __pyx_temp+1-__pyx_t_8, 5+__pyx_t_8); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else
    #endif
    {
      __pyx_t_1 = PyTuple_New(5+__pyx_t_8); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      if (__pyx_t_2) {
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2); __pyx_t_2 = NULL;
      }
      __Pyx_INCREF(__pyx_v_ia_edges);
      __Pyx_GIVEREF(__pyx_v_ia_edges);
      PyTuple_SET_ITEM(__pyx_t_1, 0+__pyx_t_8, __pyx_v_ia_edges);
      __Pyx_INCREF(__pyx_v_ia_edges_tmp);
      __Pyx_GIVEREF(__pyx_v_ia_edges_tmp);
      PyTuple_SET_ITEM(__pyx_t_1, 1+__pyx_t_8, __pyx_v_ia_edges_tmp);
      __Pyx_INCREF(__pyx_v_num_ecurrent);
      __Pyx_GIVEREF(__pyx_v_num_ecurrent);
      PyTuple_SET_ITEM(__pyx_t_1, 2+__pyx_t_8, __pyx_v_num_ecurrent);
      __Pyx_INCREF(__pyx_v_b_one_pop);
      __Pyx_GIVEREF(__pyx_v_b_one_pop);
      PyTuple_SET_ITEM(__pyx_t_1, 3+__pyx_t_8, __pyx_v_b_one_pop);
      __Pyx_INCREF(__pyx_v_multigraph);
      __Pyx_GIVEREF(__pyx_v_multigraph);
      PyTuple_SET_ITEM(__pyx_t_1, 4+__pyx_t_8, __pyx_v_multigraph);
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_1, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    if ((likely(PyTuple_CheckExact(__pyx_t_7))) || (PyList_CheckExact(__pyx_t_7))) {
      PyObject* sequence = __pyx_t_7;
      #if !CYTHON_COMPILING_IN_PYPY
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(0, 342, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      if (likely(PyTuple_CheckExact(sequence))) {
        __pyx_t_4 = PyTuple_GET_ITEM(sequence, 0); 
        __pyx_t_1 = PyTuple_GET_ITEM(sequence, 1); 
      } else {
        __pyx_t_4 = PyList_GET_ITEM(sequence, 0); 
        __pyx_t_1 = PyList_GET_ITEM(sequence, 1); 
      }
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_1);
      #else
      __pyx_t_4 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_1 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      #endif
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    } else {
      Py_ssize_t index = -1;
      __pyx_t_2 = PyObject_GetIter(__pyx_t_7); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 342, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_10 = Py_TYPE(__pyx_t_2)->tp_iternext;
      index = 0; __pyx_t_4 = __pyx_t_10(__pyx_t_2); if (unlikely(!__pyx_t_4)) goto __pyx_L8_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_4);
      index = 1; __pyx_t_1 = __pyx_t_10(__pyx_t_2); if (unlikely(!__pyx_t_1)) goto __pyx_L8_unpacking_failed;
      __Pyx_GOTREF(__pyx_t_1);
      if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_2), 2) < 0) __PYX_ERR(0, 342, __pyx_L1_error)
      __pyx_t_10 = NULL;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      goto __pyx_L9_unpacking_done;
      __pyx_L8_unpacking_failed:;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_10 = NULL;
      if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
      __PYX_ERR(0, 342, __pyx_L1_error)
      __pyx_L9_unpacking_done:;
    }

    /* "nngt/generation/cconnect.pyx":342
 *         ia_targets = node_ids[randint(0, nodes, num_edges-num_ecurrent)]
 *         ia_edges_tmp = np.array([ia_sources,ia_targets]).T
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,             # <<<<<<<<<<<<<<
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 */
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_4);
    __pyx_t_4 = 0;
    __Pyx_DECREF_SET(__pyx_v_num_ecurrent, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":344
 *         ia_edges, num_ecurrent = _filter(ia_edges, ia_edges_tmp, num_ecurrent,
 *                                          b_one_pop, multigraph)
 *         num_test += 1             # <<<<<<<<<<<<<<
 *     ia_edges = _no_self_loops(ia_edges)
 *     if not directed:
 */
    __pyx_t_7 = __Pyx_PyInt_AddObjC(__pyx_v_num_test, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 344, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF_SET(__pyx_v_num_test, __pyx_t_7);
    __pyx_t_7 = 0;
  }

  /* "nngt/generation/cconnect.pyx":345
 *                                          b_one_pop, multigraph)
 *         num_test += 1
 *     ia_edges = _no_self_loops(ia_edges)             # <<<<<<<<<<<<<<
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_no_self_loops); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 345, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
    }
  }
  if (!__pyx_t_4) {
    __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_ia_edges); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 345, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_edges};
      __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 345, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
      PyObject *__pyx_temp[2] = {__pyx_t_4, __pyx_v_ia_edges};
      __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 345, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else
    #endif
    {
      __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 345, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_4); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_4); __pyx_t_4 = NULL;
      __Pyx_INCREF(__pyx_v_ia_edges);
      __Pyx_GIVEREF(__pyx_v_ia_edges);
      PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_ia_edges);
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_2, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 345, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_7);
  __pyx_t_7 = 0;

  /* "nngt/generation/cconnect.pyx":346
 *         num_test += 1
 *     ia_edges = _no_self_loops(ia_edges)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_v_directed); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 346, __pyx_L1_error)
  __pyx_t_6 = ((!__pyx_t_9) != 0);
  if (__pyx_t_6) {

    /* "nngt/generation/cconnect.pyx":347
 *     ia_edges = _no_self_loops(ia_edges)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 347, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 347, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyObject_GetItem(__pyx_v_ia_edges, __pyx_tuple__33); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 347, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 347, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_INCREF(__pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_v_ia_edges);
    PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_v_ia_edges);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_1) {
      __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_4); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 347, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __Pyx_GOTREF(__pyx_t_7);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_4};
        __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 347, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_4};
        __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 347, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      } else
      #endif
      {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 347, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_1); __pyx_t_1 = NULL;
        __Pyx_GIVEREF(__pyx_t_4);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_4);
        __pyx_t_4 = 0;
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 347, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_7);
    __pyx_t_7 = 0;

    /* "nngt/generation/cconnect.pyx":348
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 348, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_3) {
      __pyx_t_7 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_v_ia_edges); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 348, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_ia_edges};
        __pyx_t_7 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 348, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_7);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_ia_edges};
        __pyx_t_7 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 348, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_7);
      } else
      #endif
      {
        __pyx_t_4 = PyTuple_New(1+1); if (unlikely(!__pyx_t_4)) __PYX_ERR(0, 348, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_INCREF(__pyx_v_ia_edges);
        __Pyx_GIVEREF(__pyx_v_ia_edges);
        PyTuple_SET_ITEM(__pyx_t_4, 0+1, __pyx_v_ia_edges);
        __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_4, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 348, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, __pyx_t_7);
    __pyx_t_7 = 0;

    /* "nngt/generation/cconnect.pyx":346
 *         num_test += 1
 *     ia_edges = _no_self_loops(ia_edges)
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":349
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(__pyx_v_ia_edges);
  __pyx_r = __pyx_v_ia_edges;
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":313
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 * 
 * def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,             # <<<<<<<<<<<<<<
 *                   directed, multigraph, **kwargs):
 *     '''
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("nngt.generation.cconnect._newman_watts", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_node_ids);
  __Pyx_XDECREF(__pyx_v_nodes);
  __Pyx_XDECREF(__pyx_v_circular_edges);
  __Pyx_XDECREF(__pyx_v_num_edges);
  __Pyx_XDECREF(__pyx_v_b_one_pop);
  __Pyx_XDECREF(__pyx_v_ia_edges);
  __Pyx_XDECREF(__pyx_v_num_test);
  __Pyx_XDECREF(__pyx_v_num_ecurrent);
  __Pyx_XDECREF(__pyx_v_ia_sources);
  __Pyx_XDECREF(__pyx_v_ia_targets);
  __Pyx_XDECREF(__pyx_v_ia_edges_tmp);
  __Pyx_XDECREF(__pyx_v_target_ids);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":352
 * 
 * 
 * def _distance_rule(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                    np.ndarray[size_t, ndim=1] target_ids,
 *                    density, edges, avg_deg, double scale,
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_21_distance_rule(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4nngt_10generation_8cconnect_20_distance_rule[] = "\n    Returns a distance-rule graph\n    ";
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_21_distance_rule = {"_distance_rule", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_21_distance_rule, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4nngt_10generation_8cconnect_20_distance_rule};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_21_distance_rule(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyArrayObject *__pyx_v_source_ids = 0;
  PyArrayObject *__pyx_v_target_ids = 0;
  PyObject *__pyx_v_density = 0;
  PyObject *__pyx_v_edges = 0;
  PyObject *__pyx_v_avg_deg = 0;
  double __pyx_v_scale;
  PyObject *__pyx_v_rule = 0;
  PyObject *__pyx_v_shape = 0;
  PyArrayObject *__pyx_v_positions = 0;
  bool __pyx_v_directed;
  bool __pyx_v_multigraph;
  PyObject *__pyx_v_num_neurons = 0;
  CYTHON_UNUSED PyObject *__pyx_v_kwargs = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("_distance_rule (wrapper)", 0);
  __pyx_v_kwargs = PyDict_New(); if (unlikely(!__pyx_v_kwargs)) return NULL;
  __Pyx_GOTREF(__pyx_v_kwargs);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s_source_ids,&__pyx_n_s_target_ids,&__pyx_n_s_density,&__pyx_n_s_edges,&__pyx_n_s_avg_deg,&__pyx_n_s_scale,&__pyx_n_s_rule,&__pyx_n_s_shape,&__pyx_n_s_positions,&__pyx_n_s_directed,&__pyx_n_s_multigraph,&__pyx_n_s_num_neurons,0};
    PyObject* values[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    /* "nngt/generation/cconnect.pyx":356
 *                    density, edges, avg_deg, double scale,
 *                    str rule, shape, np.ndarray[double, ndim=2] positions,
 *                    bool directed, bool multigraph, num_neurons=None, **kwargs):             # <<<<<<<<<<<<<<
 *     '''
 *     Returns a distance-rule graph
 */
    values[11] = ((PyObject *)Py_None);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case 12: values[11] = PyTuple_GET_ITEM(__pyx_args, 11);
        case 11: values[10] = PyTuple_GET_ITEM(__pyx_args, 10);
        case 10: values[9] = PyTuple_GET_ITEM(__pyx_args, 9);
        case  9: values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        case  8: values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_source_ids)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_target_ids)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 1); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_density)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 2); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_edges)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 3); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_avg_deg)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 4); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_scale)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 5); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_rule)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 6); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  7:
        if (likely((values[7] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_shape)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 7); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  8:
        if (likely((values[8] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_positions)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 8); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case  9:
        if (likely((values[9] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_directed)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 9); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case 10:
        if (likely((values[10] = PyDict_GetItem(__pyx_kwds, __pyx_n_s_multigraph)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, 10); __PYX_ERR(0, 352, __pyx_L3_error)
        }
        case 11:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s_num_neurons);
          if (value) { values[11] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, __pyx_v_kwargs, values, pos_args, "_distance_rule") < 0)) __PYX_ERR(0, 352, __pyx_L3_error)
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case 12: values[11] = PyTuple_GET_ITEM(__pyx_args, 11);
        case 11: values[10] = PyTuple_GET_ITEM(__pyx_args, 10);
        values[9] = PyTuple_GET_ITEM(__pyx_args, 9);
        values[8] = PyTuple_GET_ITEM(__pyx_args, 8);
        values[7] = PyTuple_GET_ITEM(__pyx_args, 7);
        values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_source_ids = ((PyArrayObject *)values[0]);
    __pyx_v_target_ids = ((PyArrayObject *)values[1]);
    __pyx_v_density = values[2];
    __pyx_v_edges = values[3];
    __pyx_v_avg_deg = values[4];
    __pyx_v_scale = __pyx_PyFloat_AsDouble(values[5]); if (unlikely((__pyx_v_scale == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 354, __pyx_L3_error)
    __pyx_v_rule = ((PyObject*)values[6]);
    __pyx_v_shape = values[7];
    __pyx_v_positions = ((PyArrayObject *)values[8]);
    __pyx_v_directed = __Pyx_PyObject_IsTrue(values[9]); if (unlikely((__pyx_v_directed == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 356, __pyx_L3_error)
    __pyx_v_multigraph = __Pyx_PyObject_IsTrue(values[10]); if (unlikely((__pyx_v_multigraph == ((bool)-1)) && PyErr_Occurred())) __PYX_ERR(0, 356, __pyx_L3_error)
    __pyx_v_num_neurons = values[11];
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("_distance_rule", 0, 11, 12, PyTuple_GET_SIZE(__pyx_args)); __PYX_ERR(0, 352, __pyx_L3_error)
  __pyx_L3_error:;
  __Pyx_DECREF(__pyx_v_kwargs); __pyx_v_kwargs = 0;
  __Pyx_AddTraceback("nngt.generation.cconnect._distance_rule", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_source_ids), __pyx_ptype_5numpy_ndarray, 1, "source_ids", 0))) __PYX_ERR(0, 352, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_target_ids), __pyx_ptype_5numpy_ndarray, 1, "target_ids", 0))) __PYX_ERR(0, 353, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_rule), (&PyString_Type), 1, "rule", 1))) __PYX_ERR(0, 355, __pyx_L1_error)
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_positions), __pyx_ptype_5numpy_ndarray, 1, "positions", 0))) __PYX_ERR(0, 355, __pyx_L1_error)
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_20_distance_rule(__pyx_self, __pyx_v_source_ids, __pyx_v_target_ids, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_v_scale, __pyx_v_rule, __pyx_v_shape, __pyx_v_positions, __pyx_v_directed, __pyx_v_multigraph, __pyx_v_num_neurons, __pyx_v_kwargs);

  /* "nngt/generation/cconnect.pyx":352
 * 
 * 
 * def _distance_rule(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                    np.ndarray[size_t, ndim=1] target_ids,
 *                    density, edges, avg_deg, double scale,
 */

  /* function exit code */
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_kwargs);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_20_distance_rule(CYTHON_UNUSED PyObject *__pyx_self, PyArrayObject *__pyx_v_source_ids, PyArrayObject *__pyx_v_target_ids, PyObject *__pyx_v_density, PyObject *__pyx_v_edges, PyObject *__pyx_v_avg_deg, double __pyx_v_scale, PyObject *__pyx_v_rule, PyObject *__pyx_v_shape, PyArrayObject *__pyx_v_positions, bool __pyx_v_directed, bool __pyx_v_multigraph, PyObject *__pyx_v_num_neurons, CYTHON_UNUSED PyObject *__pyx_v_kwargs) {
  size_t __pyx_v_cnum_neurons;
  size_t __pyx_v_num_source;
  size_t __pyx_v_num_target;
  std::string __pyx_v_crule;
  unsigned int __pyx_v_omp;
  std::vector<std::vector<size_t> >  __pyx_v_old_edges;
  std::vector<double>  __pyx_v_x;
  std::vector<double>  __pyx_v_y;
  PyObject *__pyx_v_edge_num = NULL;
  CYTHON_UNUSED PyObject *__pyx_v__ = NULL;
  PyObject *__pyx_v_existing = NULL;
  long __pyx_v_msd;
  double __pyx_v_area;
  size_t __pyx_v_cedges;
  PyArrayObject *__pyx_v_ia_edges = 0;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_ia_edges;
  __Pyx_Buffer __pyx_pybuffer_ia_edges;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_positions;
  __Pyx_Buffer __pyx_pybuffer_positions;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_source_ids;
  __Pyx_Buffer __pyx_pybuffer_source_ids;
  __Pyx_LocalBuf_ND __pyx_pybuffernd_target_ids;
  __Pyx_Buffer __pyx_pybuffer_target_ids;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  Py_ssize_t __pyx_t_8;
  size_t __pyx_t_9;
  std::string __pyx_t_10;
  unsigned int __pyx_t_11;
  std::vector<std::vector<size_t> >  __pyx_t_12;
  std::vector<double>  __pyx_t_13;
  PyObject *__pyx_t_14 = NULL;
  int __pyx_t_15;
  PyObject *__pyx_t_16 = NULL;
  PyObject *(*__pyx_t_17)(PyObject *);
  long __pyx_t_18;
  double __pyx_t_19;
  PyArrayObject *__pyx_t_20 = NULL;
  Py_ssize_t __pyx_t_21;
  Py_ssize_t __pyx_t_22;
  std::vector<size_t>  __pyx_t_23;
  std::vector<size_t>  __pyx_t_24;
  PyObject *__pyx_t_25 = NULL;
  PyObject *__pyx_t_26 = NULL;
  PyObject *__pyx_t_27 = NULL;
  __Pyx_RefNannySetupContext("_distance_rule", 0);
  __Pyx_INCREF(__pyx_v_num_neurons);
  __pyx_pybuffer_ia_edges.pybuffer.buf = NULL;
  __pyx_pybuffer_ia_edges.refcount = 0;
  __pyx_pybuffernd_ia_edges.data = NULL;
  __pyx_pybuffernd_ia_edges.rcbuffer = &__pyx_pybuffer_ia_edges;
  __pyx_pybuffer_source_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_source_ids.refcount = 0;
  __pyx_pybuffernd_source_ids.data = NULL;
  __pyx_pybuffernd_source_ids.rcbuffer = &__pyx_pybuffer_source_ids;
  __pyx_pybuffer_target_ids.pybuffer.buf = NULL;
  __pyx_pybuffer_target_ids.refcount = 0;
  __pyx_pybuffernd_target_ids.data = NULL;
  __pyx_pybuffernd_target_ids.rcbuffer = &__pyx_pybuffer_target_ids;
  __pyx_pybuffer_positions.pybuffer.buf = NULL;
  __pyx_pybuffer_positions.refcount = 0;
  __pyx_pybuffernd_positions.data = NULL;
  __pyx_pybuffernd_positions.rcbuffer = &__pyx_pybuffer_positions;
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_source_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 352, __pyx_L1_error)
  }
  __pyx_pybuffernd_source_ids.diminfo[0].strides = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_source_ids.diminfo[0].shape = __pyx_pybuffernd_source_ids.rcbuffer->pybuffer.shape[0];
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer, (PyObject*)__pyx_v_target_ids, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_STRIDES, 1, 0, __pyx_stack) == -1)) __PYX_ERR(0, 352, __pyx_L1_error)
  }
  __pyx_pybuffernd_target_ids.diminfo[0].strides = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_target_ids.diminfo[0].shape = __pyx_pybuffernd_target_ids.rcbuffer->pybuffer.shape[0];
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_positions.rcbuffer->pybuffer, (PyObject*)__pyx_v_positions, &__Pyx_TypeInfo_double, PyBUF_FORMAT| PyBUF_STRIDES, 2, 0, __pyx_stack) == -1)) __PYX_ERR(0, 352, __pyx_L1_error)
  }
  __pyx_pybuffernd_positions.diminfo[0].strides = __pyx_pybuffernd_positions.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_positions.diminfo[0].shape = __pyx_pybuffernd_positions.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_positions.diminfo[1].strides = __pyx_pybuffernd_positions.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_positions.diminfo[1].shape = __pyx_pybuffernd_positions.rcbuffer->pybuffer.shape[1];

  /* "nngt/generation/cconnect.pyx":360
 *     Returns a distance-rule graph
 *     '''
 *     np.random.seed()             # <<<<<<<<<<<<<<
 *     if num_neurons is None:
 *         num_neurons = len(set(np.concatenate((source_ids, target_ids))))
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 360, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_random); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 360, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_seed); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 360, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_3) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 360, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 360, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":361
 *     '''
 *     np.random.seed()
 *     if num_neurons is None:             # <<<<<<<<<<<<<<
 *         num_neurons = len(set(np.concatenate((source_ids, target_ids))))
 *     cdef:
 */
  __pyx_t_4 = (__pyx_v_num_neurons == Py_None);
  __pyx_t_5 = (__pyx_t_4 != 0);
  if (__pyx_t_5) {

    /* "nngt/generation/cconnect.pyx":362
 *     np.random.seed()
 *     if num_neurons is None:
 *         num_neurons = len(set(np.concatenate((source_ids, target_ids))))             # <<<<<<<<<<<<<<
 *     cdef:
 *         size_t cnum_neurons = num_neurons
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(((PyObject *)__pyx_v_source_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_source_ids));
    PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_source_ids));
    __Pyx_INCREF(((PyObject *)__pyx_v_target_ids));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_target_ids));
    PyTuple_SET_ITEM(__pyx_t_2, 1, ((PyObject *)__pyx_v_target_ids));
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_6) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 362, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 362, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_6, __pyx_t_2};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 362, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      } else
      #endif
      {
        __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 362, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_6); __pyx_t_6 = NULL;
        __Pyx_GIVEREF(__pyx_t_2);
        PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_2);
        __pyx_t_2 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_7, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 362, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PySet_New(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_8 = PySet_GET_SIZE(__pyx_t_3); if (unlikely(__pyx_t_8 == -1)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyInt_FromSsize_t(__pyx_t_8); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 362, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF_SET(__pyx_v_num_neurons, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "nngt/generation/cconnect.pyx":361
 *     '''
 *     np.random.seed()
 *     if num_neurons is None:             # <<<<<<<<<<<<<<
 *         num_neurons = len(set(np.concatenate((source_ids, target_ids))))
 *     cdef:
 */
  }

  /* "nngt/generation/cconnect.pyx":364
 *         num_neurons = len(set(np.concatenate((source_ids, target_ids))))
 *     cdef:
 *         size_t cnum_neurons = num_neurons             # <<<<<<<<<<<<<<
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 */
  __pyx_t_9 = __Pyx_PyInt_As_size_t(__pyx_v_num_neurons); if (unlikely((__pyx_t_9 == (size_t)-1) && PyErr_Occurred())) __PYX_ERR(0, 364, __pyx_L1_error)
  __pyx_v_cnum_neurons = __pyx_t_9;

  /* "nngt/generation/cconnect.pyx":365
 *     cdef:
 *         size_t cnum_neurons = num_neurons
 *         size_t num_source = source_ids.shape[0]             # <<<<<<<<<<<<<<
 *         size_t num_target = target_ids.shape[0]
 *         string crule = _to_bytes(rule)
 */
  __pyx_v_num_source = (__pyx_v_source_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":366
 *         size_t cnum_neurons = num_neurons
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]             # <<<<<<<<<<<<<<
 *         string crule = _to_bytes(rule)
 *         unsigned int omp = nngt.config["omp"]
 */
  __pyx_v_num_target = (__pyx_v_target_ids->dimensions[0]);

  /* "nngt/generation/cconnect.pyx":367
 *         size_t num_source = source_ids.shape[0]
 *         size_t num_target = target_ids.shape[0]
 *         string crule = _to_bytes(rule)             # <<<<<<<<<<<<<<
 *         unsigned int omp = nngt.config["omp"]
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 */
  __pyx_t_3 = __pyx_f_4nngt_10generation_8cconnect__to_bytes(__pyx_v_rule); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 367, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_10 = __pyx_convert_string_from_py_std__in_string(__pyx_t_3); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 367, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_crule = __pyx_t_10;

  /* "nngt/generation/cconnect.pyx":368
 *         size_t num_target = target_ids.shape[0]
 *         string crule = _to_bytes(rule)
 *         unsigned int omp = nngt.config["omp"]             # <<<<<<<<<<<<<<
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 *         vector[double] x = positions[0]
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_nngt); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 368, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_config); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 368, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_GetItem(__pyx_t_1, __pyx_n_s_omp); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 368, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_11 = __Pyx_PyInt_As_unsigned_int(__pyx_t_3); if (unlikely((__pyx_t_11 == (unsigned int)-1) && PyErr_Occurred())) __PYX_ERR(0, 368, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_omp = __pyx_t_11;

  /* "nngt/generation/cconnect.pyx":369
 *         string crule = _to_bytes(rule)
 *         unsigned int omp = nngt.config["omp"]
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()             # <<<<<<<<<<<<<<
 *         vector[double] x = positions[0]
 *         vector[double] y = positions[1]
 */
  try {
    __pyx_t_12 = std::vector<std::vector<size_t> > ();
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 369, __pyx_L1_error)
  }
  __pyx_v_old_edges = __pyx_t_12;

  /* "nngt/generation/cconnect.pyx":370
 *         unsigned int omp = nngt.config["omp"]
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 *         vector[double] x = positions[0]             # <<<<<<<<<<<<<<
 *         vector[double] y = positions[1]
 *     # compute the required values
 */
  __pyx_t_3 = __Pyx_GetItemInt(((PyObject *)__pyx_v_positions), 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 370, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_13 = __pyx_convert_vector_from_py_double(__pyx_t_3); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 370, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_x = __pyx_t_13;

  /* "nngt/generation/cconnect.pyx":371
 *         vector[ vector[size_t] ] old_edges = vector[ vector[size_t] ]()
 *         vector[double] x = positions[0]
 *         vector[double] y = positions[1]             # <<<<<<<<<<<<<<
 *     # compute the required values
 *     edge_num, _ = _compute_connections(
 */
  __pyx_t_3 = __Pyx_GetItemInt(((PyObject *)__pyx_v_positions), 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 371, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_13 = __pyx_convert_vector_from_py_double(__pyx_t_3); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 371, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_y = __pyx_t_13;

  /* "nngt/generation/cconnect.pyx":373
 *         vector[double] y = positions[1]
 *     # compute the required values
 *     edge_num, _ = _compute_connections(             # <<<<<<<<<<<<<<
 *         num_source, num_target, density, edges, avg_deg, directed)
 *     existing = 0  # for now
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_compute_connections); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);

  /* "nngt/generation/cconnect.pyx":374
 *     # compute the required values
 *     edge_num, _ = _compute_connections(
 *         num_source, num_target, density, edges, avg_deg, directed)             # <<<<<<<<<<<<<<
 *     existing = 0  # for now
 *     #~ b_one_pop = _check_num_edges(
 */
  __pyx_t_7 = __Pyx_PyInt_FromSize_t(__pyx_v_num_source); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 374, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_2 = __Pyx_PyInt_FromSize_t(__pyx_v_num_target); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 374, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_6 = __Pyx_PyBool_FromLong(__pyx_v_directed); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 374, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_14 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
    __pyx_t_14 = PyMethod_GET_SELF(__pyx_t_1);
    if (likely(__pyx_t_14)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
      __Pyx_INCREF(__pyx_t_14);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_1, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[7] = {__pyx_t_14, __pyx_t_7, __pyx_t_2, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_t_6};
    __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_15, 6+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
    PyObject *__pyx_temp[7] = {__pyx_t_14, __pyx_t_7, __pyx_t_2, __pyx_v_density, __pyx_v_edges, __pyx_v_avg_deg, __pyx_t_6};
    __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_15, 6+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  } else
  #endif
  {
    __pyx_t_16 = PyTuple_New(6+__pyx_t_15); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    if (__pyx_t_14) {
      __Pyx_GIVEREF(__pyx_t_14); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_14); __pyx_t_14 = NULL;
    }
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_16, 0+__pyx_t_15, __pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_16, 1+__pyx_t_15, __pyx_t_2);
    __Pyx_INCREF(__pyx_v_density);
    __Pyx_GIVEREF(__pyx_v_density);
    PyTuple_SET_ITEM(__pyx_t_16, 2+__pyx_t_15, __pyx_v_density);
    __Pyx_INCREF(__pyx_v_edges);
    __Pyx_GIVEREF(__pyx_v_edges);
    PyTuple_SET_ITEM(__pyx_t_16, 3+__pyx_t_15, __pyx_v_edges);
    __Pyx_INCREF(__pyx_v_avg_deg);
    __Pyx_GIVEREF(__pyx_v_avg_deg);
    PyTuple_SET_ITEM(__pyx_t_16, 4+__pyx_t_15, __pyx_v_avg_deg);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_16, 5+__pyx_t_15, __pyx_t_6);
    __pyx_t_7 = 0;
    __pyx_t_2 = 0;
    __pyx_t_6 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_16, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if ((likely(PyTuple_CheckExact(__pyx_t_3))) || (PyList_CheckExact(__pyx_t_3))) {
    PyObject* sequence = __pyx_t_3;
    #if !CYTHON_COMPILING_IN_PYPY
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 2)) {
      if (size > 2) __Pyx_RaiseTooManyValuesError(2);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      __PYX_ERR(0, 373, __pyx_L1_error)
    }
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (likely(PyTuple_CheckExact(sequence))) {
      __pyx_t_1 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_16 = PyTuple_GET_ITEM(sequence, 1); 
    } else {
      __pyx_t_1 = PyList_GET_ITEM(sequence, 0); 
      __pyx_t_16 = PyList_GET_ITEM(sequence, 1); 
    }
    __Pyx_INCREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_t_16);
    #else
    __pyx_t_1 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_16 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    #endif
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else {
    Py_ssize_t index = -1;
    __pyx_t_6 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_17 = Py_TYPE(__pyx_t_6)->tp_iternext;
    index = 0; __pyx_t_1 = __pyx_t_17(__pyx_t_6); if (unlikely(!__pyx_t_1)) goto __pyx_L4_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_1);
    index = 1; __pyx_t_16 = __pyx_t_17(__pyx_t_6); if (unlikely(!__pyx_t_16)) goto __pyx_L4_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_16);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_17(__pyx_t_6), 2) < 0) __PYX_ERR(0, 373, __pyx_L1_error)
    __pyx_t_17 = NULL;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    goto __pyx_L5_unpacking_done;
    __pyx_L4_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_17 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    __PYX_ERR(0, 373, __pyx_L1_error)
    __pyx_L5_unpacking_done:;
  }

  /* "nngt/generation/cconnect.pyx":373
 *         vector[double] y = positions[1]
 *     # compute the required values
 *     edge_num, _ = _compute_connections(             # <<<<<<<<<<<<<<
 *         num_source, num_target, density, edges, avg_deg, directed)
 *     existing = 0  # for now
 */
  __pyx_v_edge_num = __pyx_t_1;
  __pyx_t_1 = 0;
  __pyx_v__ = __pyx_t_16;
  __pyx_t_16 = 0;

  /* "nngt/generation/cconnect.pyx":375
 *     edge_num, _ = _compute_connections(
 *         num_source, num_target, density, edges, avg_deg, directed)
 *     existing = 0  # for now             # <<<<<<<<<<<<<<
 *     #~ b_one_pop = _check_num_edges(
 *         #~ source_ids, target_ids, edges, directed, multigraph)
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_existing = __pyx_int_0;

  /* "nngt/generation/cconnect.pyx":380
 *     # create the edges
 *     cdef:
 *         long msd = np.random.randint(0, edge_num + 1)             # <<<<<<<<<<<<<<
 *         double area = shape.area
 *         size_t cedges = edge_num
 */
  __pyx_t_16 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 380, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_16, __pyx_n_s_random); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 380, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_randint); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 380, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_edge_num, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 380, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = NULL;
  __pyx_t_15 = 0;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_16))) {
    __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_16);
    if (likely(__pyx_t_6)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_16);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_16, function);
      __pyx_t_15 = 1;
    }
  }
  #if CYTHON_FAST_PYCALL
  if (PyFunction_Check(__pyx_t_16)) {
    PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_int_0, __pyx_t_1};
    __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_16, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 380, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else
  #endif
  #if CYTHON_FAST_PYCCALL
  if (__Pyx_PyFastCFunction_Check(__pyx_t_16)) {
    PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_int_0, __pyx_t_1};
    __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_16, __pyx_temp+1-__pyx_t_15, 2+__pyx_t_15); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 380, __pyx_L1_error)
    __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else
  #endif
  {
    __pyx_t_2 = PyTuple_New(2+__pyx_t_15); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 380, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    if (__pyx_t_6) {
      __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_6); __pyx_t_6 = NULL;
    }
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_GIVEREF(__pyx_int_0);
    PyTuple_SET_ITEM(__pyx_t_2, 0+__pyx_t_15, __pyx_int_0);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_2, 1+__pyx_t_15, __pyx_t_1);
    __pyx_t_1 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 380, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  __pyx_t_18 = __Pyx_PyInt_As_long(__pyx_t_3); if (unlikely((__pyx_t_18 == (long)-1) && PyErr_Occurred())) __PYX_ERR(0, 380, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_msd = __pyx_t_18;

  /* "nngt/generation/cconnect.pyx":381
 *     cdef:
 *         long msd = np.random.randint(0, edge_num + 1)
 *         double area = shape.area             # <<<<<<<<<<<<<<
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 */
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_shape, __pyx_n_s_area); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 381, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_19 = __pyx_PyFloat_AsDouble(__pyx_t_3); if (unlikely((__pyx_t_19 == (double)-1) && PyErr_Occurred())) __PYX_ERR(0, 381, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_area = __pyx_t_19;

  /* "nngt/generation/cconnect.pyx":382
 *         long msd = np.random.randint(0, edge_num + 1)
 *         double area = shape.area
 *         size_t cedges = edge_num             # <<<<<<<<<<<<<<
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edge_num, 2), dtype=DTYPE)
 */
  __pyx_t_9 = __Pyx_PyInt_As_size_t(__pyx_v_edge_num); if (unlikely((__pyx_t_9 == (size_t)-1) && PyErr_Occurred())) __PYX_ERR(0, 382, __pyx_L1_error)
  __pyx_v_cedges = __pyx_t_9;

  /* "nngt/generation/cconnect.pyx":383
 *         double area = shape.area
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edge_num, 2), dtype=DTYPE)
 * 
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 383, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_16 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_zeros); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 383, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_16);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":384
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edge_num, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 * 
 *     _cdistance_rule(&ia_edges[0,0], source_ids, target_ids, crule, scale, x, y,
 */
  __pyx_t_3 = PyNumber_Add(__pyx_v_existing, __pyx_v_edge_num); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 384, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 384, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
  __Pyx_INCREF(__pyx_int_2);
  __Pyx_GIVEREF(__pyx_int_2);
  PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_int_2);
  __pyx_t_3 = 0;

  /* "nngt/generation/cconnect.pyx":383
 *         double area = shape.area
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edge_num, 2), dtype=DTYPE)
 * 
 */
  __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 383, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_2);
  __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":384
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(
 *             (existing + edge_num, 2), dtype=DTYPE)             # <<<<<<<<<<<<<<
 * 
 *     _cdistance_rule(&ia_edges[0,0], source_ids, target_ids, crule, scale, x, y,
 */
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 384, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_DTYPE); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 384, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_2, __pyx_n_s_dtype, __pyx_t_1) < 0) __PYX_ERR(0, 384, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":383
 *         double area = shape.area
 *         size_t cedges = edge_num
 *         np.ndarray[size_t, ndim=2, mode="c"] ia_edges = np.zeros(             # <<<<<<<<<<<<<<
 *             (existing + edge_num, 2), dtype=DTYPE)
 * 
 */
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_16, __pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 383, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 383, __pyx_L1_error)
  __pyx_t_20 = ((PyArrayObject *)__pyx_t_1);
  {
    __Pyx_BufFmt_StackElem __pyx_stack[1];
    if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_20, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
      __pyx_v_ia_edges = ((PyArrayObject *)Py_None); __Pyx_INCREF(Py_None); __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf = NULL;
      __PYX_ERR(0, 383, __pyx_L1_error)
    } else {__pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
    }
  }
  __pyx_t_20 = 0;
  __pyx_v_ia_edges = ((PyArrayObject *)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":386
 *             (existing + edge_num, 2), dtype=DTYPE)
 * 
 *     _cdistance_rule(&ia_edges[0,0], source_ids, target_ids, crule, scale, x, y,             # <<<<<<<<<<<<<<
 *                     area, cnum_neurons, cedges, old_edges, multigraph, msd,
 *                     omp)
 */
  __pyx_t_21 = 0;
  __pyx_t_22 = 0;
  __pyx_t_23 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_source_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 386, __pyx_L1_error)
  __pyx_t_24 = __pyx_convert_vector_from_py_size_t(((PyObject *)__pyx_v_target_ids)); if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 386, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":388
 *     _cdistance_rule(&ia_edges[0,0], source_ids, target_ids, crule, scale, x, y,
 *                     area, cnum_neurons, cedges, old_edges, multigraph, msd,
 *                     omp)             # <<<<<<<<<<<<<<
 * 
 *     if not directed:
 */
  try {
    generation::_cdistance_rule((&(*__Pyx_BufPtrCContig2d(size_t *, __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.buf, __pyx_t_21, __pyx_pybuffernd_ia_edges.diminfo[0].strides, __pyx_t_22, __pyx_pybuffernd_ia_edges.diminfo[1].strides))), __pyx_t_23, __pyx_t_24, __pyx_v_crule, __pyx_v_scale, __pyx_v_x, __pyx_v_y, __pyx_v_area, __pyx_v_cnum_neurons, __pyx_v_cedges, __pyx_v_old_edges, __pyx_v_multigraph, __pyx_v_msd, __pyx_v_omp);
  } catch(...) {
    __Pyx_CppExn2PyErr();
    __PYX_ERR(0, 386, __pyx_L1_error)
  }

  /* "nngt/generation/cconnect.pyx":390
 *                     omp)
 * 
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  __pyx_t_5 = ((!(__pyx_v_directed != 0)) != 0);
  if (__pyx_t_5) {

    /* "nngt/generation/cconnect.pyx":391
 * 
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 391, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_concatenate); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 391, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_GetItem(((PyObject *)__pyx_v_ia_edges), __pyx_tuple__36); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 391, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_16 = PyTuple_New(2); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 391, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_16);
    __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
    PyTuple_SET_ITEM(__pyx_t_16, 0, ((PyObject *)__pyx_v_ia_edges));
    __Pyx_GIVEREF(__pyx_t_2);
    PyTuple_SET_ITEM(__pyx_t_16, 1, __pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_16); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 391, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_16};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 391, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_16};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 391, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      } else
      #endif
      {
        __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 391, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2); __pyx_t_2 = NULL;
        __Pyx_GIVEREF(__pyx_t_16);
        PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_16);
        __pyx_t_16 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_6, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 391, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 391, __pyx_L1_error)
    __pyx_t_20 = ((PyArrayObject *)__pyx_t_1);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_15 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_20, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_15 < 0)) {
        PyErr_Fetch(&__pyx_t_25, &__pyx_t_26, &__pyx_t_27);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_25); Py_XDECREF(__pyx_t_26); Py_XDECREF(__pyx_t_27);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_25, __pyx_t_26, __pyx_t_27);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_15 < 0)) __PYX_ERR(0, 391, __pyx_L1_error)
    }
    __pyx_t_20 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_1));
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":392
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)             # <<<<<<<<<<<<<<
 *     return ia_edges
 * 
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_unique_rows); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 392, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_6) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, ((PyObject *)__pyx_v_ia_edges)); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 392, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_6, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 392, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_6, ((PyObject *)__pyx_v_ia_edges)};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 392, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      {
        __pyx_t_16 = PyTuple_New(1+1); if (unlikely(!__pyx_t_16)) __PYX_ERR(0, 392, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_16);
        __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_16, 0, __pyx_t_6); __pyx_t_6 = NULL;
        __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
        __Pyx_GIVEREF(((PyObject *)__pyx_v_ia_edges));
        PyTuple_SET_ITEM(__pyx_t_16, 0+1, ((PyObject *)__pyx_v_ia_edges));
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_16, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 392, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!(likely(((__pyx_t_1) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_1, __pyx_ptype_5numpy_ndarray))))) __PYX_ERR(0, 392, __pyx_L1_error)
    __pyx_t_20 = ((PyArrayObject *)__pyx_t_1);
    {
      __Pyx_BufFmt_StackElem __pyx_stack[1];
      __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
      __pyx_t_15 = __Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_t_20, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack);
      if (unlikely(__pyx_t_15 < 0)) {
        PyErr_Fetch(&__pyx_t_27, &__pyx_t_26, &__pyx_t_25);
        if (unlikely(__Pyx_GetBufferAndValidate(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer, (PyObject*)__pyx_v_ia_edges, &__Pyx_TypeInfo_size_t, PyBUF_FORMAT| PyBUF_C_CONTIGUOUS, 2, 0, __pyx_stack) == -1)) {
          Py_XDECREF(__pyx_t_27); Py_XDECREF(__pyx_t_26); Py_XDECREF(__pyx_t_25);
          __Pyx_RaiseBufferFallbackError();
        } else {
          PyErr_Restore(__pyx_t_27, __pyx_t_26, __pyx_t_25);
        }
      }
      __pyx_pybuffernd_ia_edges.diminfo[0].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[0]; __pyx_pybuffernd_ia_edges.diminfo[0].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[0]; __pyx_pybuffernd_ia_edges.diminfo[1].strides = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.strides[1]; __pyx_pybuffernd_ia_edges.diminfo[1].shape = __pyx_pybuffernd_ia_edges.rcbuffer->pybuffer.shape[1];
      if (unlikely(__pyx_t_15 < 0)) __PYX_ERR(0, 392, __pyx_L1_error)
    }
    __pyx_t_20 = 0;
    __Pyx_DECREF_SET(__pyx_v_ia_edges, ((PyArrayObject *)__pyx_t_1));
    __pyx_t_1 = 0;

    /* "nngt/generation/cconnect.pyx":390
 *                     omp)
 * 
 *     if not directed:             # <<<<<<<<<<<<<<
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 */
  }

  /* "nngt/generation/cconnect.pyx":393
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges             # <<<<<<<<<<<<<<
 * 
 * def price_network():
 */
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_ia_edges));
  __pyx_r = ((PyObject *)__pyx_v_ia_edges);
  goto __pyx_L0;

  /* "nngt/generation/cconnect.pyx":352
 * 
 * 
 * def _distance_rule(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                    np.ndarray[size_t, ndim=1] target_ids,
 *                    density, edges, avg_deg, double scale,
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_14);
  __Pyx_XDECREF(__pyx_t_16);
  { PyObject *__pyx_type, *__pyx_value, *__pyx_tb;
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ErrFetch(&__pyx_type, &__pyx_value, &__pyx_tb);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_positions.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
    __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __Pyx_ErrRestore(__pyx_type, __pyx_value, __pyx_tb);}
  __Pyx_AddTraceback("nngt.generation.cconnect._distance_rule", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  goto __pyx_L2;
  __pyx_L0:;
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_ia_edges.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_positions.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_source_ids.rcbuffer->pybuffer);
  __Pyx_SafeReleaseBuffer(&__pyx_pybuffernd_target_ids.rcbuffer->pybuffer);
  __pyx_L2:;
  __Pyx_XDECREF(__pyx_v_edge_num);
  __Pyx_XDECREF(__pyx_v__);
  __Pyx_XDECREF(__pyx_v_existing);
  __Pyx_XDECREF((PyObject *)__pyx_v_ia_edges);
  __Pyx_XDECREF(__pyx_v_num_neurons);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "nngt/generation/cconnect.pyx":395
 *     return ia_edges
 * 
 * def price_network():             # <<<<<<<<<<<<<<
 *     #@todo: do it for other libraries
 *     pass
 */

/* Python wrapper */
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_23price_network(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused); /*proto*/
static PyMethodDef __pyx_mdef_4nngt_10generation_8cconnect_23price_network = {"price_network", (PyCFunction)__pyx_pw_4nngt_10generation_8cconnect_23price_network, METH_NOARGS, 0};
static PyObject *__pyx_pw_4nngt_10generation_8cconnect_23price_network(PyObject *__pyx_self, CYTHON_UNUSED PyObject *unused) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("price_network (wrapper)", 0);
  __pyx_r = __pyx_pf_4nngt_10generation_8cconnect_22price_network(__pyx_self);

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_4nngt_10generation_8cconnect_22price_network(CYTHON_UNUSED PyObject *__pyx_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("price_network", 0);

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":197
 *         # experimental exception made for __getbuffer__ and __releasebuffer__
 *         # -- the details of this may change.
 *         def __getbuffer__(ndarray self, Py_buffer* info, int flags):             # <<<<<<<<<<<<<<
 *             # This implementation of getbuffer is geared towards Cython
 *             # requirements, and does not yet fullfill the PEP.
 */

/* Python wrapper */
static CYTHON_UNUSED int __pyx_pw_5numpy_7ndarray_1__getbuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags); /*proto*/
static CYTHON_UNUSED int __pyx_pw_5numpy_7ndarray_1__getbuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__getbuffer__ (wrapper)", 0);
  __pyx_r = __pyx_pf_5numpy_7ndarray___getbuffer__(((PyArrayObject *)__pyx_v_self), ((Py_buffer *)__pyx_v_info), ((int)__pyx_v_flags));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_5numpy_7ndarray___getbuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info, int __pyx_v_flags) {
  int __pyx_v_copy_shape;
  int __pyx_v_i;
  int __pyx_v_ndim;
  int __pyx_v_endian_detector;
  int __pyx_v_little_endian;
  int __pyx_v_t;
  char *__pyx_v_f;
  PyArray_Descr *__pyx_v_descr = 0;
  int __pyx_v_offset;
  int __pyx_v_hasfields;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  char *__pyx_t_7;
  __Pyx_RefNannySetupContext("__getbuffer__", 0);
  if (__pyx_v_info != NULL) {
    __pyx_v_info->obj = Py_None; __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(__pyx_v_info->obj);
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":203
 *             # of flags
 * 
 *             if info == NULL: return             # <<<<<<<<<<<<<<
 * 
 *             cdef int copy_shape, i, ndim
 */
  __pyx_t_1 = ((__pyx_v_info == NULL) != 0);
  if (__pyx_t_1) {
    __pyx_r = 0;
    goto __pyx_L0;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":206
 * 
 *             cdef int copy_shape, i, ndim
 *             cdef int endian_detector = 1             # <<<<<<<<<<<<<<
 *             cdef bint little_endian = ((<char*>&endian_detector)[0] != 0)
 * 
 */
  __pyx_v_endian_detector = 1;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":207
 *             cdef int copy_shape, i, ndim
 *             cdef int endian_detector = 1
 *             cdef bint little_endian = ((<char*>&endian_detector)[0] != 0)             # <<<<<<<<<<<<<<
 * 
 *             ndim = PyArray_NDIM(self)
 */
  __pyx_v_little_endian = ((((char *)(&__pyx_v_endian_detector))[0]) != 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":209
 *             cdef bint little_endian = ((<char*>&endian_detector)[0] != 0)
 * 
 *             ndim = PyArray_NDIM(self)             # <<<<<<<<<<<<<<
 * 
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 */
  __pyx_v_ndim = PyArray_NDIM(__pyx_v_self);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":211
 *             ndim = PyArray_NDIM(self)
 * 
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):             # <<<<<<<<<<<<<<
 *                 copy_shape = 1
 *             else:
 */
  __pyx_t_1 = (((sizeof(npy_intp)) != (sizeof(Py_ssize_t))) != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":212
 * 
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 *                 copy_shape = 1             # <<<<<<<<<<<<<<
 *             else:
 *                 copy_shape = 0
 */
    __pyx_v_copy_shape = 1;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":211
 *             ndim = PyArray_NDIM(self)
 * 
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):             # <<<<<<<<<<<<<<
 *                 copy_shape = 1
 *             else:
 */
    goto __pyx_L4;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":214
 *                 copy_shape = 1
 *             else:
 *                 copy_shape = 0             # <<<<<<<<<<<<<<
 * 
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)
 */
  /*else*/ {
    __pyx_v_copy_shape = 0;
  }
  __pyx_L4:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":216
 *                 copy_shape = 0
 * 
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not C contiguous")
 */
  __pyx_t_2 = (((__pyx_v_flags & PyBUF_C_CONTIGUOUS) == PyBUF_C_CONTIGUOUS) != 0);
  if (__pyx_t_2) {
  } else {
    __pyx_t_1 = __pyx_t_2;
    goto __pyx_L6_bool_binop_done;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":217
 * 
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):             # <<<<<<<<<<<<<<
 *                 raise ValueError(u"ndarray is not C contiguous")
 * 
 */
  __pyx_t_2 = ((!(PyArray_CHKFLAGS(__pyx_v_self, NPY_C_CONTIGUOUS) != 0)) != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L6_bool_binop_done:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":216
 *                 copy_shape = 0
 * 
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not C contiguous")
 */
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":218
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not C contiguous")             # <<<<<<<<<<<<<<
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)
 */
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__37, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 218, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 218, __pyx_L1_error)

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":216
 *                 copy_shape = 0
 * 
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not C contiguous")
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":220
 *                 raise ValueError(u"ndarray is not C contiguous")
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not Fortran contiguous")
 */
  __pyx_t_2 = (((__pyx_v_flags & PyBUF_F_CONTIGUOUS) == PyBUF_F_CONTIGUOUS) != 0);
  if (__pyx_t_2) {
  } else {
    __pyx_t_1 = __pyx_t_2;
    goto __pyx_L9_bool_binop_done;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":221
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):             # <<<<<<<<<<<<<<
 *                 raise ValueError(u"ndarray is not Fortran contiguous")
 * 
 */
  __pyx_t_2 = ((!(PyArray_CHKFLAGS(__pyx_v_self, NPY_F_CONTIGUOUS) != 0)) != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L9_bool_binop_done:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":220
 *                 raise ValueError(u"ndarray is not C contiguous")
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not Fortran contiguous")
 */
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":222
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not Fortran contiguous")             # <<<<<<<<<<<<<<
 * 
 *             info.buf = PyArray_DATA(self)
 */
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__38, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 222, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 222, __pyx_L1_error)

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":220
 *                 raise ValueError(u"ndarray is not C contiguous")
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)             # <<<<<<<<<<<<<<
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not Fortran contiguous")
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":224
 *                 raise ValueError(u"ndarray is not Fortran contiguous")
 * 
 *             info.buf = PyArray_DATA(self)             # <<<<<<<<<<<<<<
 *             info.ndim = ndim
 *             if copy_shape:
 */
  __pyx_v_info->buf = PyArray_DATA(__pyx_v_self);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":225
 * 
 *             info.buf = PyArray_DATA(self)
 *             info.ndim = ndim             # <<<<<<<<<<<<<<
 *             if copy_shape:
 *                 # Allocate new buffer for strides and shape info.
 */
  __pyx_v_info->ndim = __pyx_v_ndim;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":226
 *             info.buf = PyArray_DATA(self)
 *             info.ndim = ndim
 *             if copy_shape:             # <<<<<<<<<<<<<<
 *                 # Allocate new buffer for strides and shape info.
 *                 # This is allocated as one block, strides first.
 */
  __pyx_t_1 = (__pyx_v_copy_shape != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":229
 *                 # Allocate new buffer for strides and shape info.
 *                 # This is allocated as one block, strides first.
 *                 info.strides = <Py_ssize_t*>stdlib.malloc(sizeof(Py_ssize_t) * <size_t>ndim * 2)             # <<<<<<<<<<<<<<
 *                 info.shape = info.strides + ndim
 *                 for i in range(ndim):
 */
    __pyx_v_info->strides = ((Py_ssize_t *)malloc((((sizeof(Py_ssize_t)) * ((size_t)__pyx_v_ndim)) * 2)));

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":230
 *                 # This is allocated as one block, strides first.
 *                 info.strides = <Py_ssize_t*>stdlib.malloc(sizeof(Py_ssize_t) * <size_t>ndim * 2)
 *                 info.shape = info.strides + ndim             # <<<<<<<<<<<<<<
 *                 for i in range(ndim):
 *                     info.strides[i] = PyArray_STRIDES(self)[i]
 */
    __pyx_v_info->shape = (__pyx_v_info->strides + __pyx_v_ndim);

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":231
 *                 info.strides = <Py_ssize_t*>stdlib.malloc(sizeof(Py_ssize_t) * <size_t>ndim * 2)
 *                 info.shape = info.strides + ndim
 *                 for i in range(ndim):             # <<<<<<<<<<<<<<
 *                     info.strides[i] = PyArray_STRIDES(self)[i]
 *                     info.shape[i] = PyArray_DIMS(self)[i]
 */
    __pyx_t_4 = __pyx_v_ndim;
    for (__pyx_t_5 = 0; __pyx_t_5 < __pyx_t_4; __pyx_t_5+=1) {
      __pyx_v_i = __pyx_t_5;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":232
 *                 info.shape = info.strides + ndim
 *                 for i in range(ndim):
 *                     info.strides[i] = PyArray_STRIDES(self)[i]             # <<<<<<<<<<<<<<
 *                     info.shape[i] = PyArray_DIMS(self)[i]
 *             else:
 */
      (__pyx_v_info->strides[__pyx_v_i]) = (PyArray_STRIDES(__pyx_v_self)[__pyx_v_i]);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":233
 *                 for i in range(ndim):
 *                     info.strides[i] = PyArray_STRIDES(self)[i]
 *                     info.shape[i] = PyArray_DIMS(self)[i]             # <<<<<<<<<<<<<<
 *             else:
 *                 info.strides = <Py_ssize_t*>PyArray_STRIDES(self)
 */
      (__pyx_v_info->shape[__pyx_v_i]) = (PyArray_DIMS(__pyx_v_self)[__pyx_v_i]);
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":226
 *             info.buf = PyArray_DATA(self)
 *             info.ndim = ndim
 *             if copy_shape:             # <<<<<<<<<<<<<<
 *                 # Allocate new buffer for strides and shape info.
 *                 # This is allocated as one block, strides first.
 */
    goto __pyx_L11;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":235
 *                     info.shape[i] = PyArray_DIMS(self)[i]
 *             else:
 *                 info.strides = <Py_ssize_t*>PyArray_STRIDES(self)             # <<<<<<<<<<<<<<
 *                 info.shape = <Py_ssize_t*>PyArray_DIMS(self)
 *             info.suboffsets = NULL
 */
  /*else*/ {
    __pyx_v_info->strides = ((Py_ssize_t *)PyArray_STRIDES(__pyx_v_self));

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":236
 *             else:
 *                 info.strides = <Py_ssize_t*>PyArray_STRIDES(self)
 *                 info.shape = <Py_ssize_t*>PyArray_DIMS(self)             # <<<<<<<<<<<<<<
 *             info.suboffsets = NULL
 *             info.itemsize = PyArray_ITEMSIZE(self)
 */
    __pyx_v_info->shape = ((Py_ssize_t *)PyArray_DIMS(__pyx_v_self));
  }
  __pyx_L11:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":237
 *                 info.strides = <Py_ssize_t*>PyArray_STRIDES(self)
 *                 info.shape = <Py_ssize_t*>PyArray_DIMS(self)
 *             info.suboffsets = NULL             # <<<<<<<<<<<<<<
 *             info.itemsize = PyArray_ITEMSIZE(self)
 *             info.readonly = not PyArray_ISWRITEABLE(self)
 */
  __pyx_v_info->suboffsets = NULL;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":238
 *                 info.shape = <Py_ssize_t*>PyArray_DIMS(self)
 *             info.suboffsets = NULL
 *             info.itemsize = PyArray_ITEMSIZE(self)             # <<<<<<<<<<<<<<
 *             info.readonly = not PyArray_ISWRITEABLE(self)
 * 
 */
  __pyx_v_info->itemsize = PyArray_ITEMSIZE(__pyx_v_self);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":239
 *             info.suboffsets = NULL
 *             info.itemsize = PyArray_ITEMSIZE(self)
 *             info.readonly = not PyArray_ISWRITEABLE(self)             # <<<<<<<<<<<<<<
 * 
 *             cdef int t
 */
  __pyx_v_info->readonly = (!(PyArray_ISWRITEABLE(__pyx_v_self) != 0));

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":242
 * 
 *             cdef int t
 *             cdef char* f = NULL             # <<<<<<<<<<<<<<
 *             cdef dtype descr = self.descr
 *             cdef int offset
 */
  __pyx_v_f = NULL;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":243
 *             cdef int t
 *             cdef char* f = NULL
 *             cdef dtype descr = self.descr             # <<<<<<<<<<<<<<
 *             cdef int offset
 * 
 */
  __pyx_t_3 = ((PyObject *)__pyx_v_self->descr);
  __Pyx_INCREF(__pyx_t_3);
  __pyx_v_descr = ((PyArray_Descr *)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":246
 *             cdef int offset
 * 
 *             cdef bint hasfields = PyDataType_HASFIELDS(descr)             # <<<<<<<<<<<<<<
 * 
 *             if not hasfields and not copy_shape:
 */
  __pyx_v_hasfields = PyDataType_HASFIELDS(__pyx_v_descr);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":248
 *             cdef bint hasfields = PyDataType_HASFIELDS(descr)
 * 
 *             if not hasfields and not copy_shape:             # <<<<<<<<<<<<<<
 *                 # do not call releasebuffer
 *                 info.obj = None
 */
  __pyx_t_2 = ((!(__pyx_v_hasfields != 0)) != 0);
  if (__pyx_t_2) {
  } else {
    __pyx_t_1 = __pyx_t_2;
    goto __pyx_L15_bool_binop_done;
  }
  __pyx_t_2 = ((!(__pyx_v_copy_shape != 0)) != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L15_bool_binop_done:;
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":250
 *             if not hasfields and not copy_shape:
 *                 # do not call releasebuffer
 *                 info.obj = None             # <<<<<<<<<<<<<<
 *             else:
 *                 # need to call releasebuffer
 */
    __Pyx_INCREF(Py_None);
    __Pyx_GIVEREF(Py_None);
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj);
    __pyx_v_info->obj = Py_None;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":248
 *             cdef bint hasfields = PyDataType_HASFIELDS(descr)
 * 
 *             if not hasfields and not copy_shape:             # <<<<<<<<<<<<<<
 *                 # do not call releasebuffer
 *                 info.obj = None
 */
    goto __pyx_L14;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":253
 *             else:
 *                 # need to call releasebuffer
 *                 info.obj = self             # <<<<<<<<<<<<<<
 * 
 *             if not hasfields:
 */
  /*else*/ {
    __Pyx_INCREF(((PyObject *)__pyx_v_self));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_self));
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj);
    __pyx_v_info->obj = ((PyObject *)__pyx_v_self);
  }
  __pyx_L14:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":255
 *                 info.obj = self
 * 
 *             if not hasfields:             # <<<<<<<<<<<<<<
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or
 */
  __pyx_t_1 = ((!(__pyx_v_hasfields != 0)) != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":256
 * 
 *             if not hasfields:
 *                 t = descr.type_num             # <<<<<<<<<<<<<<
 *                 if ((descr.byteorder == c'>' and little_endian) or
 *                     (descr.byteorder == c'<' and not little_endian)):
 */
    __pyx_t_4 = __pyx_v_descr->type_num;
    __pyx_v_t = __pyx_t_4;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":257
 *             if not hasfields:
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")
 */
    __pyx_t_2 = ((__pyx_v_descr->byteorder == '>') != 0);
    if (!__pyx_t_2) {
      goto __pyx_L20_next_or;
    } else {
    }
    __pyx_t_2 = (__pyx_v_little_endian != 0);
    if (!__pyx_t_2) {
    } else {
      __pyx_t_1 = __pyx_t_2;
      goto __pyx_L19_bool_binop_done;
    }
    __pyx_L20_next_or:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":258
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or
 *                     (descr.byteorder == c'<' and not little_endian)):             # <<<<<<<<<<<<<<
 *                     raise ValueError(u"Non-native byte order not supported")
 *                 if   t == NPY_BYTE:        f = "b"
 */
    __pyx_t_2 = ((__pyx_v_descr->byteorder == '<') != 0);
    if (__pyx_t_2) {
    } else {
      __pyx_t_1 = __pyx_t_2;
      goto __pyx_L19_bool_binop_done;
    }
    __pyx_t_2 = ((!(__pyx_v_little_endian != 0)) != 0);
    __pyx_t_1 = __pyx_t_2;
    __pyx_L19_bool_binop_done:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":257
 *             if not hasfields:
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")
 */
    if (__pyx_t_1) {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":259
 *                 if ((descr.byteorder == c'>' and little_endian) or
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")             # <<<<<<<<<<<<<<
 *                 if   t == NPY_BYTE:        f = "b"
 *                 elif t == NPY_UBYTE:       f = "B"
 */
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__39, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 259, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_Raise(__pyx_t_3, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __PYX_ERR(1, 259, __pyx_L1_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":257
 *             if not hasfields:
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")
 */
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":260
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")
 *                 if   t == NPY_BYTE:        f = "b"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_UBYTE:       f = "B"
 *                 elif t == NPY_SHORT:       f = "h"
 */
    switch (__pyx_v_t) {
      case NPY_BYTE:
      __pyx_v_f = ((char *)"b");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":261
 *                     raise ValueError(u"Non-native byte order not supported")
 *                 if   t == NPY_BYTE:        f = "b"
 *                 elif t == NPY_UBYTE:       f = "B"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_SHORT:       f = "h"
 *                 elif t == NPY_USHORT:      f = "H"
 */
      case NPY_UBYTE:
      __pyx_v_f = ((char *)"B");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":262
 *                 if   t == NPY_BYTE:        f = "b"
 *                 elif t == NPY_UBYTE:       f = "B"
 *                 elif t == NPY_SHORT:       f = "h"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_USHORT:      f = "H"
 *                 elif t == NPY_INT:         f = "i"
 */
      case NPY_SHORT:
      __pyx_v_f = ((char *)"h");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":263
 *                 elif t == NPY_UBYTE:       f = "B"
 *                 elif t == NPY_SHORT:       f = "h"
 *                 elif t == NPY_USHORT:      f = "H"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_INT:         f = "i"
 *                 elif t == NPY_UINT:        f = "I"
 */
      case NPY_USHORT:
      __pyx_v_f = ((char *)"H");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":264
 *                 elif t == NPY_SHORT:       f = "h"
 *                 elif t == NPY_USHORT:      f = "H"
 *                 elif t == NPY_INT:         f = "i"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_UINT:        f = "I"
 *                 elif t == NPY_LONG:        f = "l"
 */
      case NPY_INT:
      __pyx_v_f = ((char *)"i");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":265
 *                 elif t == NPY_USHORT:      f = "H"
 *                 elif t == NPY_INT:         f = "i"
 *                 elif t == NPY_UINT:        f = "I"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_LONG:        f = "l"
 *                 elif t == NPY_ULONG:       f = "L"
 */
      case NPY_UINT:
      __pyx_v_f = ((char *)"I");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":266
 *                 elif t == NPY_INT:         f = "i"
 *                 elif t == NPY_UINT:        f = "I"
 *                 elif t == NPY_LONG:        f = "l"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_ULONG:       f = "L"
 *                 elif t == NPY_LONGLONG:    f = "q"
 */
      case NPY_LONG:
      __pyx_v_f = ((char *)"l");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":267
 *                 elif t == NPY_UINT:        f = "I"
 *                 elif t == NPY_LONG:        f = "l"
 *                 elif t == NPY_ULONG:       f = "L"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_LONGLONG:    f = "q"
 *                 elif t == NPY_ULONGLONG:   f = "Q"
 */
      case NPY_ULONG:
      __pyx_v_f = ((char *)"L");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":268
 *                 elif t == NPY_LONG:        f = "l"
 *                 elif t == NPY_ULONG:       f = "L"
 *                 elif t == NPY_LONGLONG:    f = "q"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_ULONGLONG:   f = "Q"
 *                 elif t == NPY_FLOAT:       f = "f"
 */
      case NPY_LONGLONG:
      __pyx_v_f = ((char *)"q");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":269
 *                 elif t == NPY_ULONG:       f = "L"
 *                 elif t == NPY_LONGLONG:    f = "q"
 *                 elif t == NPY_ULONGLONG:   f = "Q"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_FLOAT:       f = "f"
 *                 elif t == NPY_DOUBLE:      f = "d"
 */
      case NPY_ULONGLONG:
      __pyx_v_f = ((char *)"Q");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":270
 *                 elif t == NPY_LONGLONG:    f = "q"
 *                 elif t == NPY_ULONGLONG:   f = "Q"
 *                 elif t == NPY_FLOAT:       f = "f"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_DOUBLE:      f = "d"
 *                 elif t == NPY_LONGDOUBLE:  f = "g"
 */
      case NPY_FLOAT:
      __pyx_v_f = ((char *)"f");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":271
 *                 elif t == NPY_ULONGLONG:   f = "Q"
 *                 elif t == NPY_FLOAT:       f = "f"
 *                 elif t == NPY_DOUBLE:      f = "d"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_LONGDOUBLE:  f = "g"
 *                 elif t == NPY_CFLOAT:      f = "Zf"
 */
      case NPY_DOUBLE:
      __pyx_v_f = ((char *)"d");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":272
 *                 elif t == NPY_FLOAT:       f = "f"
 *                 elif t == NPY_DOUBLE:      f = "d"
 *                 elif t == NPY_LONGDOUBLE:  f = "g"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_CFLOAT:      f = "Zf"
 *                 elif t == NPY_CDOUBLE:     f = "Zd"
 */
      case NPY_LONGDOUBLE:
      __pyx_v_f = ((char *)"g");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":273
 *                 elif t == NPY_DOUBLE:      f = "d"
 *                 elif t == NPY_LONGDOUBLE:  f = "g"
 *                 elif t == NPY_CFLOAT:      f = "Zf"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_CDOUBLE:     f = "Zd"
 *                 elif t == NPY_CLONGDOUBLE: f = "Zg"
 */
      case NPY_CFLOAT:
      __pyx_v_f = ((char *)"Zf");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":274
 *                 elif t == NPY_LONGDOUBLE:  f = "g"
 *                 elif t == NPY_CFLOAT:      f = "Zf"
 *                 elif t == NPY_CDOUBLE:     f = "Zd"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_CLONGDOUBLE: f = "Zg"
 *                 elif t == NPY_OBJECT:      f = "O"
 */
      case NPY_CDOUBLE:
      __pyx_v_f = ((char *)"Zd");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":275
 *                 elif t == NPY_CFLOAT:      f = "Zf"
 *                 elif t == NPY_CDOUBLE:     f = "Zd"
 *                 elif t == NPY_CLONGDOUBLE: f = "Zg"             # <<<<<<<<<<<<<<
 *                 elif t == NPY_OBJECT:      f = "O"
 *                 else:
 */
      case NPY_CLONGDOUBLE:
      __pyx_v_f = ((char *)"Zg");
      break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":276
 *                 elif t == NPY_CDOUBLE:     f = "Zd"
 *                 elif t == NPY_CLONGDOUBLE: f = "Zg"
 *                 elif t == NPY_OBJECT:      f = "O"             # <<<<<<<<<<<<<<
 *                 else:
 *                     raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)
 */
      case NPY_OBJECT:
      __pyx_v_f = ((char *)"O");
      break;
      default:

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":278
 *                 elif t == NPY_OBJECT:      f = "O"
 *                 else:
 *                     raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)             # <<<<<<<<<<<<<<
 *                 info.format = f
 *                 return
 */
      __pyx_t_3 = __Pyx_PyInt_From_int(__pyx_v_t); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 278, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_6 = PyUnicode_Format(__pyx_kp_u_unknown_dtype_code_in_numpy_pxd, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(1, 278, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = PyTuple_New(1); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 278, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_GIVEREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_6);
      __pyx_t_6 = 0;
      __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_t_3, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(1, 278, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __Pyx_Raise(__pyx_t_6, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __PYX_ERR(1, 278, __pyx_L1_error)
      break;
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":279
 *                 else:
 *                     raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)
 *                 info.format = f             # <<<<<<<<<<<<<<
 *                 return
 *             else:
 */
    __pyx_v_info->format = __pyx_v_f;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":280
 *                     raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)
 *                 info.format = f
 *                 return             # <<<<<<<<<<<<<<
 *             else:
 *                 info.format = <char*>stdlib.malloc(_buffer_format_string_len)
 */
    __pyx_r = 0;
    goto __pyx_L0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":255
 *                 info.obj = self
 * 
 *             if not hasfields:             # <<<<<<<<<<<<<<
 *                 t = descr.type_num
 *                 if ((descr.byteorder == c'>' and little_endian) or
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":282
 *                 return
 *             else:
 *                 info.format = <char*>stdlib.malloc(_buffer_format_string_len)             # <<<<<<<<<<<<<<
 *                 info.format[0] = c'^' # Native data types, manual alignment
 *                 offset = 0
 */
  /*else*/ {
    __pyx_v_info->format = ((char *)malloc(0xFF));

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":283
 *             else:
 *                 info.format = <char*>stdlib.malloc(_buffer_format_string_len)
 *                 info.format[0] = c'^' # Native data types, manual alignment             # <<<<<<<<<<<<<<
 *                 offset = 0
 *                 f = _util_dtypestring(descr, info.format + 1,
 */
    (__pyx_v_info->format[0]) = '^';

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":284
 *                 info.format = <char*>stdlib.malloc(_buffer_format_string_len)
 *                 info.format[0] = c'^' # Native data types, manual alignment
 *                 offset = 0             # <<<<<<<<<<<<<<
 *                 f = _util_dtypestring(descr, info.format + 1,
 *                                       info.format + _buffer_format_string_len,
 */
    __pyx_v_offset = 0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":285
 *                 info.format[0] = c'^' # Native data types, manual alignment
 *                 offset = 0
 *                 f = _util_dtypestring(descr, info.format + 1,             # <<<<<<<<<<<<<<
 *                                       info.format + _buffer_format_string_len,
 *                                       &offset)
 */
    __pyx_t_7 = __pyx_f_5numpy__util_dtypestring(__pyx_v_descr, (__pyx_v_info->format + 1), (__pyx_v_info->format + 0xFF), (&__pyx_v_offset)); if (unlikely(__pyx_t_7 == NULL)) __PYX_ERR(1, 285, __pyx_L1_error)
    __pyx_v_f = __pyx_t_7;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":288
 *                                       info.format + _buffer_format_string_len,
 *                                       &offset)
 *                 f[0] = c'\0' # Terminate format string             # <<<<<<<<<<<<<<
 * 
 *         def __releasebuffer__(ndarray self, Py_buffer* info):
 */
    (__pyx_v_f[0]) = '\x00';
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":197
 *         # experimental exception made for __getbuffer__ and __releasebuffer__
 *         # -- the details of this may change.
 *         def __getbuffer__(ndarray self, Py_buffer* info, int flags):             # <<<<<<<<<<<<<<
 *             # This implementation of getbuffer is geared towards Cython
 *             # requirements, and does not yet fullfill the PEP.
 */

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_AddTraceback("numpy.ndarray.__getbuffer__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  if (__pyx_v_info != NULL && __pyx_v_info->obj != NULL) {
    __Pyx_GOTREF(__pyx_v_info->obj);
    __Pyx_DECREF(__pyx_v_info->obj); __pyx_v_info->obj = NULL;
  }
  goto __pyx_L2;
  __pyx_L0:;
  if (__pyx_v_info != NULL && __pyx_v_info->obj == Py_None) {
    __Pyx_GOTREF(Py_None);
    __Pyx_DECREF(Py_None); __pyx_v_info->obj = NULL;
  }
  __pyx_L2:;
  __Pyx_XDECREF((PyObject *)__pyx_v_descr);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":290
 *                 f[0] = c'\0' # Terminate format string
 * 
 *         def __releasebuffer__(ndarray self, Py_buffer* info):             # <<<<<<<<<<<<<<
 *             if PyArray_HASFIELDS(self):
 *                 stdlib.free(info.format)
 */

/* Python wrapper */
static CYTHON_UNUSED void __pyx_pw_5numpy_7ndarray_3__releasebuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info); /*proto*/
static CYTHON_UNUSED void __pyx_pw_5numpy_7ndarray_3__releasebuffer__(PyObject *__pyx_v_self, Py_buffer *__pyx_v_info) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__releasebuffer__ (wrapper)", 0);
  __pyx_pf_5numpy_7ndarray_2__releasebuffer__(((PyArrayObject *)__pyx_v_self), ((Py_buffer *)__pyx_v_info));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
}

static void __pyx_pf_5numpy_7ndarray_2__releasebuffer__(PyArrayObject *__pyx_v_self, Py_buffer *__pyx_v_info) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("__releasebuffer__", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":291
 * 
 *         def __releasebuffer__(ndarray self, Py_buffer* info):
 *             if PyArray_HASFIELDS(self):             # <<<<<<<<<<<<<<
 *                 stdlib.free(info.format)
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 */
  __pyx_t_1 = (PyArray_HASFIELDS(__pyx_v_self) != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":292
 *         def __releasebuffer__(ndarray self, Py_buffer* info):
 *             if PyArray_HASFIELDS(self):
 *                 stdlib.free(info.format)             # <<<<<<<<<<<<<<
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 *                 stdlib.free(info.strides)
 */
    free(__pyx_v_info->format);

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":291
 * 
 *         def __releasebuffer__(ndarray self, Py_buffer* info):
 *             if PyArray_HASFIELDS(self):             # <<<<<<<<<<<<<<
 *                 stdlib.free(info.format)
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":293
 *             if PyArray_HASFIELDS(self):
 *                 stdlib.free(info.format)
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):             # <<<<<<<<<<<<<<
 *                 stdlib.free(info.strides)
 *                 # info.shape was stored after info.strides in the same block
 */
  __pyx_t_1 = (((sizeof(npy_intp)) != (sizeof(Py_ssize_t))) != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":294
 *                 stdlib.free(info.format)
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):
 *                 stdlib.free(info.strides)             # <<<<<<<<<<<<<<
 *                 # info.shape was stored after info.strides in the same block
 * 
 */
    free(__pyx_v_info->strides);

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":293
 *             if PyArray_HASFIELDS(self):
 *                 stdlib.free(info.format)
 *             if sizeof(npy_intp) != sizeof(Py_ssize_t):             # <<<<<<<<<<<<<<
 *                 stdlib.free(info.strides)
 *                 # info.shape was stored after info.strides in the same block
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":290
 *                 f[0] = c'\0' # Terminate format string
 * 
 *         def __releasebuffer__(ndarray self, Py_buffer* info):             # <<<<<<<<<<<<<<
 *             if PyArray_HASFIELDS(self):
 *                 stdlib.free(info.format)
 */

  /* function exit code */
  __Pyx_RefNannyFinishContext();
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":770
 * ctypedef npy_cdouble     complex_t
 * 
 * cdef inline object PyArray_MultiIterNew1(a):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(1, <void*>a)
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew1(PyObject *__pyx_v_a) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew1", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":771
 * 
 * cdef inline object PyArray_MultiIterNew1(a):
 *     return PyArray_MultiIterNew(1, <void*>a)             # <<<<<<<<<<<<<<
 * 
 * cdef inline object PyArray_MultiIterNew2(a, b):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(1, ((void *)__pyx_v_a)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 771, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":770
 * ctypedef npy_cdouble     complex_t
 * 
 * cdef inline object PyArray_MultiIterNew1(a):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(1, <void*>a)
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew1", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":773
 *     return PyArray_MultiIterNew(1, <void*>a)
 * 
 * cdef inline object PyArray_MultiIterNew2(a, b):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(2, <void*>a, <void*>b)
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew2(PyObject *__pyx_v_a, PyObject *__pyx_v_b) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew2", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":774
 * 
 * cdef inline object PyArray_MultiIterNew2(a, b):
 *     return PyArray_MultiIterNew(2, <void*>a, <void*>b)             # <<<<<<<<<<<<<<
 * 
 * cdef inline object PyArray_MultiIterNew3(a, b, c):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(2, ((void *)__pyx_v_a), ((void *)__pyx_v_b)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 774, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":773
 *     return PyArray_MultiIterNew(1, <void*>a)
 * 
 * cdef inline object PyArray_MultiIterNew2(a, b):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(2, <void*>a, <void*>b)
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew2", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":776
 *     return PyArray_MultiIterNew(2, <void*>a, <void*>b)
 * 
 * cdef inline object PyArray_MultiIterNew3(a, b, c):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(3, <void*>a, <void*>b, <void*> c)
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew3(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew3", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":777
 * 
 * cdef inline object PyArray_MultiIterNew3(a, b, c):
 *     return PyArray_MultiIterNew(3, <void*>a, <void*>b, <void*> c)             # <<<<<<<<<<<<<<
 * 
 * cdef inline object PyArray_MultiIterNew4(a, b, c, d):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(3, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 777, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":776
 *     return PyArray_MultiIterNew(2, <void*>a, <void*>b)
 * 
 * cdef inline object PyArray_MultiIterNew3(a, b, c):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(3, <void*>a, <void*>b, <void*> c)
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew3", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":779
 *     return PyArray_MultiIterNew(3, <void*>a, <void*>b, <void*> c)
 * 
 * cdef inline object PyArray_MultiIterNew4(a, b, c, d):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(4, <void*>a, <void*>b, <void*>c, <void*> d)
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew4(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew4", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":780
 * 
 * cdef inline object PyArray_MultiIterNew4(a, b, c, d):
 *     return PyArray_MultiIterNew(4, <void*>a, <void*>b, <void*>c, <void*> d)             # <<<<<<<<<<<<<<
 * 
 * cdef inline object PyArray_MultiIterNew5(a, b, c, d, e):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(4, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 780, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":779
 *     return PyArray_MultiIterNew(3, <void*>a, <void*>b, <void*> c)
 * 
 * cdef inline object PyArray_MultiIterNew4(a, b, c, d):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(4, <void*>a, <void*>b, <void*>c, <void*> d)
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew4", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":782
 *     return PyArray_MultiIterNew(4, <void*>a, <void*>b, <void*>c, <void*> d)
 * 
 * cdef inline object PyArray_MultiIterNew5(a, b, c, d, e):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(5, <void*>a, <void*>b, <void*>c, <void*> d, <void*> e)
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_PyArray_MultiIterNew5(PyObject *__pyx_v_a, PyObject *__pyx_v_b, PyObject *__pyx_v_c, PyObject *__pyx_v_d, PyObject *__pyx_v_e) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  __Pyx_RefNannySetupContext("PyArray_MultiIterNew5", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":783
 * 
 * cdef inline object PyArray_MultiIterNew5(a, b, c, d, e):
 *     return PyArray_MultiIterNew(5, <void*>a, <void*>b, <void*>c, <void*> d, <void*> e)             # <<<<<<<<<<<<<<
 * 
 * cdef inline char* _util_dtypestring(dtype descr, char* f, char* end, int* offset) except NULL:
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyArray_MultiIterNew(5, ((void *)__pyx_v_a), ((void *)__pyx_v_b), ((void *)__pyx_v_c), ((void *)__pyx_v_d), ((void *)__pyx_v_e)); if (unlikely(!__pyx_t_1)) __PYX_ERR(1, 783, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":782
 *     return PyArray_MultiIterNew(4, <void*>a, <void*>b, <void*>c, <void*> d)
 * 
 * cdef inline object PyArray_MultiIterNew5(a, b, c, d, e):             # <<<<<<<<<<<<<<
 *     return PyArray_MultiIterNew(5, <void*>a, <void*>b, <void*>c, <void*> d, <void*> e)
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("numpy.PyArray_MultiIterNew5", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":785
 *     return PyArray_MultiIterNew(5, <void*>a, <void*>b, <void*>c, <void*> d, <void*> e)
 * 
 * cdef inline char* _util_dtypestring(dtype descr, char* f, char* end, int* offset) except NULL:             # <<<<<<<<<<<<<<
 *     # Recursive utility function used in __getbuffer__ to get format
 *     # string. The new location in the format string is returned.
 */

static CYTHON_INLINE char *__pyx_f_5numpy__util_dtypestring(PyArray_Descr *__pyx_v_descr, char *__pyx_v_f, char *__pyx_v_end, int *__pyx_v_offset) {
  PyArray_Descr *__pyx_v_child = 0;
  int __pyx_v_endian_detector;
  int __pyx_v_little_endian;
  PyObject *__pyx_v_fields = 0;
  PyObject *__pyx_v_childname = NULL;
  PyObject *__pyx_v_new_offset = NULL;
  PyObject *__pyx_v_t = NULL;
  char *__pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_t_5;
  int __pyx_t_6;
  int __pyx_t_7;
  long __pyx_t_8;
  char *__pyx_t_9;
  __Pyx_RefNannySetupContext("_util_dtypestring", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":790
 * 
 *     cdef dtype child
 *     cdef int endian_detector = 1             # <<<<<<<<<<<<<<
 *     cdef bint little_endian = ((<char*>&endian_detector)[0] != 0)
 *     cdef tuple fields
 */
  __pyx_v_endian_detector = 1;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":791
 *     cdef dtype child
 *     cdef int endian_detector = 1
 *     cdef bint little_endian = ((<char*>&endian_detector)[0] != 0)             # <<<<<<<<<<<<<<
 *     cdef tuple fields
 * 
 */
  __pyx_v_little_endian = ((((char *)(&__pyx_v_endian_detector))[0]) != 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":794
 *     cdef tuple fields
 * 
 *     for childname in descr.names:             # <<<<<<<<<<<<<<
 *         fields = descr.fields[childname]
 *         child, new_offset = fields
 */
  if (unlikely(__pyx_v_descr->names == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    __PYX_ERR(1, 794, __pyx_L1_error)
  }
  __pyx_t_1 = __pyx_v_descr->names; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
  for (;;) {
    if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
    #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_3); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(1, 794, __pyx_L1_error)
    #else
    __pyx_t_3 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 794, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    #endif
    __Pyx_XDECREF_SET(__pyx_v_childname, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":795
 * 
 *     for childname in descr.names:
 *         fields = descr.fields[childname]             # <<<<<<<<<<<<<<
 *         child, new_offset = fields
 * 
 */
    if (unlikely(__pyx_v_descr->fields == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      __PYX_ERR(1, 795, __pyx_L1_error)
    }
    __pyx_t_3 = __Pyx_PyDict_GetItem(__pyx_v_descr->fields, __pyx_v_childname); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 795, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    if (!(likely(PyTuple_CheckExact(__pyx_t_3))||((__pyx_t_3) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "tuple", Py_TYPE(__pyx_t_3)->tp_name), 0))) __PYX_ERR(1, 795, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_fields, ((PyObject*)__pyx_t_3));
    __pyx_t_3 = 0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":796
 *     for childname in descr.names:
 *         fields = descr.fields[childname]
 *         child, new_offset = fields             # <<<<<<<<<<<<<<
 * 
 *         if (end - f) - <int>(new_offset - offset[0]) < 15:
 */
    if (likely(__pyx_v_fields != Py_None)) {
      PyObject* sequence = __pyx_v_fields;
      #if !CYTHON_COMPILING_IN_PYPY
      Py_ssize_t size = Py_SIZE(sequence);
      #else
      Py_ssize_t size = PySequence_Size(sequence);
      #endif
      if (unlikely(size != 2)) {
        if (size > 2) __Pyx_RaiseTooManyValuesError(2);
        else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
        __PYX_ERR(1, 796, __pyx_L1_error)
      }
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_3 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_4 = PyTuple_GET_ITEM(sequence, 1); 
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_4);
      #else
      __pyx_t_3 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 796, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 796, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      #endif
    } else {
      __Pyx_RaiseNoneNotIterableError(); __PYX_ERR(1, 796, __pyx_L1_error)
    }
    if (!(likely(((__pyx_t_3) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_3, __pyx_ptype_5numpy_dtype))))) __PYX_ERR(1, 796, __pyx_L1_error)
    __Pyx_XDECREF_SET(__pyx_v_child, ((PyArray_Descr *)__pyx_t_3));
    __pyx_t_3 = 0;
    __Pyx_XDECREF_SET(__pyx_v_new_offset, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":798
 *         child, new_offset = fields
 * 
 *         if (end - f) - <int>(new_offset - offset[0]) < 15:             # <<<<<<<<<<<<<<
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")
 * 
 */
    __pyx_t_4 = __Pyx_PyInt_From_int((__pyx_v_offset[0])); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 798, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_3 = PyNumber_Subtract(__pyx_v_new_offset, __pyx_t_4); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 798, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_5 = __Pyx_PyInt_As_int(__pyx_t_3); if (unlikely((__pyx_t_5 == (int)-1) && PyErr_Occurred())) __PYX_ERR(1, 798, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_6 = ((((__pyx_v_end - __pyx_v_f) - ((int)__pyx_t_5)) < 15) != 0);
    if (__pyx_t_6) {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":799
 * 
 *         if (end - f) - <int>(new_offset - offset[0]) < 15:
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")             # <<<<<<<<<<<<<<
 * 
 *         if ((child.byteorder == c'>' and little_endian) or
 */
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_RuntimeError, __pyx_tuple__40, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 799, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_Raise(__pyx_t_3, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __PYX_ERR(1, 799, __pyx_L1_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":798
 *         child, new_offset = fields
 * 
 *         if (end - f) - <int>(new_offset - offset[0]) < 15:             # <<<<<<<<<<<<<<
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")
 * 
 */
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":801
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")
 * 
 *         if ((child.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *             (child.byteorder == c'<' and not little_endian)):
 *             raise ValueError(u"Non-native byte order not supported")
 */
    __pyx_t_7 = ((__pyx_v_child->byteorder == '>') != 0);
    if (!__pyx_t_7) {
      goto __pyx_L8_next_or;
    } else {
    }
    __pyx_t_7 = (__pyx_v_little_endian != 0);
    if (!__pyx_t_7) {
    } else {
      __pyx_t_6 = __pyx_t_7;
      goto __pyx_L7_bool_binop_done;
    }
    __pyx_L8_next_or:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":802
 * 
 *         if ((child.byteorder == c'>' and little_endian) or
 *             (child.byteorder == c'<' and not little_endian)):             # <<<<<<<<<<<<<<
 *             raise ValueError(u"Non-native byte order not supported")
 *             # One could encode it in the format string and have Cython
 */
    __pyx_t_7 = ((__pyx_v_child->byteorder == '<') != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_6 = __pyx_t_7;
      goto __pyx_L7_bool_binop_done;
    }
    __pyx_t_7 = ((!(__pyx_v_little_endian != 0)) != 0);
    __pyx_t_6 = __pyx_t_7;
    __pyx_L7_bool_binop_done:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":801
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")
 * 
 *         if ((child.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *             (child.byteorder == c'<' and not little_endian)):
 *             raise ValueError(u"Non-native byte order not supported")
 */
    if (__pyx_t_6) {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":803
 *         if ((child.byteorder == c'>' and little_endian) or
 *             (child.byteorder == c'<' and not little_endian)):
 *             raise ValueError(u"Non-native byte order not supported")             # <<<<<<<<<<<<<<
 *             # One could encode it in the format string and have Cython
 *             # complain instead, BUT: < and > in format strings also imply
 */
      __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_tuple__41, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 803, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __Pyx_Raise(__pyx_t_3, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __PYX_ERR(1, 803, __pyx_L1_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":801
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")
 * 
 *         if ((child.byteorder == c'>' and little_endian) or             # <<<<<<<<<<<<<<
 *             (child.byteorder == c'<' and not little_endian)):
 *             raise ValueError(u"Non-native byte order not supported")
 */
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":813
 * 
 *         # Output padding bytes
 *         while offset[0] < new_offset:             # <<<<<<<<<<<<<<
 *             f[0] = 120 # "x"; pad byte
 *             f += 1
 */
    while (1) {
      __pyx_t_3 = __Pyx_PyInt_From_int((__pyx_v_offset[0])); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 813, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_t_3, __pyx_v_new_offset, Py_LT); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 813, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 813, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (!__pyx_t_6) break;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":814
 *         # Output padding bytes
 *         while offset[0] < new_offset:
 *             f[0] = 120 # "x"; pad byte             # <<<<<<<<<<<<<<
 *             f += 1
 *             offset[0] += 1
 */
      (__pyx_v_f[0]) = 0x78;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":815
 *         while offset[0] < new_offset:
 *             f[0] = 120 # "x"; pad byte
 *             f += 1             # <<<<<<<<<<<<<<
 *             offset[0] += 1
 * 
 */
      __pyx_v_f = (__pyx_v_f + 1);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":816
 *             f[0] = 120 # "x"; pad byte
 *             f += 1
 *             offset[0] += 1             # <<<<<<<<<<<<<<
 * 
 *         offset[0] += child.itemsize
 */
      __pyx_t_8 = 0;
      (__pyx_v_offset[__pyx_t_8]) = ((__pyx_v_offset[__pyx_t_8]) + 1);
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":818
 *             offset[0] += 1
 * 
 *         offset[0] += child.itemsize             # <<<<<<<<<<<<<<
 * 
 *         if not PyDataType_HASFIELDS(child):
 */
    __pyx_t_8 = 0;
    (__pyx_v_offset[__pyx_t_8]) = ((__pyx_v_offset[__pyx_t_8]) + __pyx_v_child->elsize);

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":820
 *         offset[0] += child.itemsize
 * 
 *         if not PyDataType_HASFIELDS(child):             # <<<<<<<<<<<<<<
 *             t = child.type_num
 *             if end - f < 5:
 */
    __pyx_t_6 = ((!(PyDataType_HASFIELDS(__pyx_v_child) != 0)) != 0);
    if (__pyx_t_6) {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":821
 * 
 *         if not PyDataType_HASFIELDS(child):
 *             t = child.type_num             # <<<<<<<<<<<<<<
 *             if end - f < 5:
 *                 raise RuntimeError(u"Format string allocated too short.")
 */
      __pyx_t_4 = __Pyx_PyInt_From_int(__pyx_v_child->type_num); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 821, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_XDECREF_SET(__pyx_v_t, __pyx_t_4);
      __pyx_t_4 = 0;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":822
 *         if not PyDataType_HASFIELDS(child):
 *             t = child.type_num
 *             if end - f < 5:             # <<<<<<<<<<<<<<
 *                 raise RuntimeError(u"Format string allocated too short.")
 * 
 */
      __pyx_t_6 = (((__pyx_v_end - __pyx_v_f) < 5) != 0);
      if (__pyx_t_6) {

        /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":823
 *             t = child.type_num
 *             if end - f < 5:
 *                 raise RuntimeError(u"Format string allocated too short.")             # <<<<<<<<<<<<<<
 * 
 *             # Until ticket #99 is fixed, use integers to avoid warnings
 */
        __pyx_t_4 = __Pyx_PyObject_Call(__pyx_builtin_RuntimeError, __pyx_tuple__42, NULL); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 823, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_Raise(__pyx_t_4, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        __PYX_ERR(1, 823, __pyx_L1_error)

        /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":822
 *         if not PyDataType_HASFIELDS(child):
 *             t = child.type_num
 *             if end - f < 5:             # <<<<<<<<<<<<<<
 *                 raise RuntimeError(u"Format string allocated too short.")
 * 
 */
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":826
 * 
 *             # Until ticket #99 is fixed, use integers to avoid warnings
 *             if   t == NPY_BYTE:        f[0] =  98 #"b"             # <<<<<<<<<<<<<<
 *             elif t == NPY_UBYTE:       f[0] =  66 #"B"
 *             elif t == NPY_SHORT:       f[0] = 104 #"h"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_BYTE); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 826, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 826, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 826, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 98;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":827
 *             # Until ticket #99 is fixed, use integers to avoid warnings
 *             if   t == NPY_BYTE:        f[0] =  98 #"b"
 *             elif t == NPY_UBYTE:       f[0] =  66 #"B"             # <<<<<<<<<<<<<<
 *             elif t == NPY_SHORT:       f[0] = 104 #"h"
 *             elif t == NPY_USHORT:      f[0] =  72 #"H"
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_UBYTE); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 827, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 827, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 827, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 66;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":828
 *             if   t == NPY_BYTE:        f[0] =  98 #"b"
 *             elif t == NPY_UBYTE:       f[0] =  66 #"B"
 *             elif t == NPY_SHORT:       f[0] = 104 #"h"             # <<<<<<<<<<<<<<
 *             elif t == NPY_USHORT:      f[0] =  72 #"H"
 *             elif t == NPY_INT:         f[0] = 105 #"i"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_SHORT); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 828, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 828, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 828, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x68;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":829
 *             elif t == NPY_UBYTE:       f[0] =  66 #"B"
 *             elif t == NPY_SHORT:       f[0] = 104 #"h"
 *             elif t == NPY_USHORT:      f[0] =  72 #"H"             # <<<<<<<<<<<<<<
 *             elif t == NPY_INT:         f[0] = 105 #"i"
 *             elif t == NPY_UINT:        f[0] =  73 #"I"
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_USHORT); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 829, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 829, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 829, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 72;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":830
 *             elif t == NPY_SHORT:       f[0] = 104 #"h"
 *             elif t == NPY_USHORT:      f[0] =  72 #"H"
 *             elif t == NPY_INT:         f[0] = 105 #"i"             # <<<<<<<<<<<<<<
 *             elif t == NPY_UINT:        f[0] =  73 #"I"
 *             elif t == NPY_LONG:        f[0] = 108 #"l"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_INT); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 830, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 830, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 830, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x69;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":831
 *             elif t == NPY_USHORT:      f[0] =  72 #"H"
 *             elif t == NPY_INT:         f[0] = 105 #"i"
 *             elif t == NPY_UINT:        f[0] =  73 #"I"             # <<<<<<<<<<<<<<
 *             elif t == NPY_LONG:        f[0] = 108 #"l"
 *             elif t == NPY_ULONG:       f[0] = 76  #"L"
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_UINT); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 831, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 831, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 831, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 73;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":832
 *             elif t == NPY_INT:         f[0] = 105 #"i"
 *             elif t == NPY_UINT:        f[0] =  73 #"I"
 *             elif t == NPY_LONG:        f[0] = 108 #"l"             # <<<<<<<<<<<<<<
 *             elif t == NPY_ULONG:       f[0] = 76  #"L"
 *             elif t == NPY_LONGLONG:    f[0] = 113 #"q"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_LONG); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 832, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 832, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 832, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x6C;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":833
 *             elif t == NPY_UINT:        f[0] =  73 #"I"
 *             elif t == NPY_LONG:        f[0] = 108 #"l"
 *             elif t == NPY_ULONG:       f[0] = 76  #"L"             # <<<<<<<<<<<<<<
 *             elif t == NPY_LONGLONG:    f[0] = 113 #"q"
 *             elif t == NPY_ULONGLONG:   f[0] = 81  #"Q"
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_ULONG); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 833, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 833, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 833, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 76;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":834
 *             elif t == NPY_LONG:        f[0] = 108 #"l"
 *             elif t == NPY_ULONG:       f[0] = 76  #"L"
 *             elif t == NPY_LONGLONG:    f[0] = 113 #"q"             # <<<<<<<<<<<<<<
 *             elif t == NPY_ULONGLONG:   f[0] = 81  #"Q"
 *             elif t == NPY_FLOAT:       f[0] = 102 #"f"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_LONGLONG); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 834, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 834, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 834, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x71;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":835
 *             elif t == NPY_ULONG:       f[0] = 76  #"L"
 *             elif t == NPY_LONGLONG:    f[0] = 113 #"q"
 *             elif t == NPY_ULONGLONG:   f[0] = 81  #"Q"             # <<<<<<<<<<<<<<
 *             elif t == NPY_FLOAT:       f[0] = 102 #"f"
 *             elif t == NPY_DOUBLE:      f[0] = 100 #"d"
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_ULONGLONG); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 835, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 835, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 835, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 81;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":836
 *             elif t == NPY_LONGLONG:    f[0] = 113 #"q"
 *             elif t == NPY_ULONGLONG:   f[0] = 81  #"Q"
 *             elif t == NPY_FLOAT:       f[0] = 102 #"f"             # <<<<<<<<<<<<<<
 *             elif t == NPY_DOUBLE:      f[0] = 100 #"d"
 *             elif t == NPY_LONGDOUBLE:  f[0] = 103 #"g"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_FLOAT); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 836, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 836, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 836, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x66;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":837
 *             elif t == NPY_ULONGLONG:   f[0] = 81  #"Q"
 *             elif t == NPY_FLOAT:       f[0] = 102 #"f"
 *             elif t == NPY_DOUBLE:      f[0] = 100 #"d"             # <<<<<<<<<<<<<<
 *             elif t == NPY_LONGDOUBLE:  f[0] = 103 #"g"
 *             elif t == NPY_CFLOAT:      f[0] = 90; f[1] = 102; f += 1 # Zf
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_DOUBLE); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 837, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 837, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 837, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x64;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":838
 *             elif t == NPY_FLOAT:       f[0] = 102 #"f"
 *             elif t == NPY_DOUBLE:      f[0] = 100 #"d"
 *             elif t == NPY_LONGDOUBLE:  f[0] = 103 #"g"             # <<<<<<<<<<<<<<
 *             elif t == NPY_CFLOAT:      f[0] = 90; f[1] = 102; f += 1 # Zf
 *             elif t == NPY_CDOUBLE:     f[0] = 90; f[1] = 100; f += 1 # Zd
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_LONGDOUBLE); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 838, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 838, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 838, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 0x67;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":839
 *             elif t == NPY_DOUBLE:      f[0] = 100 #"d"
 *             elif t == NPY_LONGDOUBLE:  f[0] = 103 #"g"
 *             elif t == NPY_CFLOAT:      f[0] = 90; f[1] = 102; f += 1 # Zf             # <<<<<<<<<<<<<<
 *             elif t == NPY_CDOUBLE:     f[0] = 90; f[1] = 100; f += 1 # Zd
 *             elif t == NPY_CLONGDOUBLE: f[0] = 90; f[1] = 103; f += 1 # Zg
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_CFLOAT); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 839, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 839, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 839, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 0x66;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":840
 *             elif t == NPY_LONGDOUBLE:  f[0] = 103 #"g"
 *             elif t == NPY_CFLOAT:      f[0] = 90; f[1] = 102; f += 1 # Zf
 *             elif t == NPY_CDOUBLE:     f[0] = 90; f[1] = 100; f += 1 # Zd             # <<<<<<<<<<<<<<
 *             elif t == NPY_CLONGDOUBLE: f[0] = 90; f[1] = 103; f += 1 # Zg
 *             elif t == NPY_OBJECT:      f[0] = 79 #"O"
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_CDOUBLE); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 840, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 840, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 840, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 0x64;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":841
 *             elif t == NPY_CFLOAT:      f[0] = 90; f[1] = 102; f += 1 # Zf
 *             elif t == NPY_CDOUBLE:     f[0] = 90; f[1] = 100; f += 1 # Zd
 *             elif t == NPY_CLONGDOUBLE: f[0] = 90; f[1] = 103; f += 1 # Zg             # <<<<<<<<<<<<<<
 *             elif t == NPY_OBJECT:      f[0] = 79 #"O"
 *             else:
 */
      __pyx_t_3 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_CLONGDOUBLE); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 841, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_4 = PyObject_RichCompare(__pyx_v_t, __pyx_t_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_4); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 841, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 841, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 90;
        (__pyx_v_f[1]) = 0x67;
        __pyx_v_f = (__pyx_v_f + 1);
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":842
 *             elif t == NPY_CDOUBLE:     f[0] = 90; f[1] = 100; f += 1 # Zd
 *             elif t == NPY_CLONGDOUBLE: f[0] = 90; f[1] = 103; f += 1 # Zg
 *             elif t == NPY_OBJECT:      f[0] = 79 #"O"             # <<<<<<<<<<<<<<
 *             else:
 *                 raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)
 */
      __pyx_t_4 = __Pyx_PyInt_From_enum__NPY_TYPES(NPY_OBJECT); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 842, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_4);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_t, __pyx_t_4, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 842, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_6 < 0)) __PYX_ERR(1, 842, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_6) {
        (__pyx_v_f[0]) = 79;
        goto __pyx_L15;
      }

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":844
 *             elif t == NPY_OBJECT:      f[0] = 79 #"O"
 *             else:
 *                 raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)             # <<<<<<<<<<<<<<
 *             f += 1
 *         else:
 */
      /*else*/ {
        __pyx_t_3 = PyUnicode_Format(__pyx_kp_u_unknown_dtype_code_in_numpy_pxd, __pyx_v_t); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 844, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) __PYX_ERR(1, 844, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        __Pyx_GIVEREF(__pyx_t_3);
        PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
        __pyx_t_3 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_ValueError, __pyx_t_4, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 844, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        __Pyx_Raise(__pyx_t_3, 0, 0, 0);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __PYX_ERR(1, 844, __pyx_L1_error)
      }
      __pyx_L15:;

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":845
 *             else:
 *                 raise ValueError(u"unknown dtype code in numpy.pxd (%d)" % t)
 *             f += 1             # <<<<<<<<<<<<<<
 *         else:
 *             # Cython ignores struct boundary information ("T{...}"),
 */
      __pyx_v_f = (__pyx_v_f + 1);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":820
 *         offset[0] += child.itemsize
 * 
 *         if not PyDataType_HASFIELDS(child):             # <<<<<<<<<<<<<<
 *             t = child.type_num
 *             if end - f < 5:
 */
      goto __pyx_L13;
    }

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":849
 *             # Cython ignores struct boundary information ("T{...}"),
 *             # so don't output it
 *             f = _util_dtypestring(child, f, end, offset)             # <<<<<<<<<<<<<<
 *     return f
 * 
 */
    /*else*/ {
      __pyx_t_9 = __pyx_f_5numpy__util_dtypestring(__pyx_v_child, __pyx_v_f, __pyx_v_end, __pyx_v_offset); if (unlikely(__pyx_t_9 == NULL)) __PYX_ERR(1, 849, __pyx_L1_error)
      __pyx_v_f = __pyx_t_9;
    }
    __pyx_L13:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":794
 *     cdef tuple fields
 * 
 *     for childname in descr.names:             # <<<<<<<<<<<<<<
 *         fields = descr.fields[childname]
 *         child, new_offset = fields
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":850
 *             # so don't output it
 *             f = _util_dtypestring(child, f, end, offset)
 *     return f             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_r = __pyx_v_f;
  goto __pyx_L0;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":785
 *     return PyArray_MultiIterNew(5, <void*>a, <void*>b, <void*>c, <void*> d, <void*> e)
 * 
 * cdef inline char* _util_dtypestring(dtype descr, char* f, char* end, int* offset) except NULL:             # <<<<<<<<<<<<<<
 *     # Recursive utility function used in __getbuffer__ to get format
 *     # string. The new location in the format string is returned.
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("numpy._util_dtypestring", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_child);
  __Pyx_XDECREF(__pyx_v_fields);
  __Pyx_XDECREF(__pyx_v_childname);
  __Pyx_XDECREF(__pyx_v_new_offset);
  __Pyx_XDECREF(__pyx_v_t);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":966
 * 
 * 
 * cdef inline void set_array_base(ndarray arr, object base):             # <<<<<<<<<<<<<<
 *      cdef PyObject* baseptr
 *      if base is None:
 */

static CYTHON_INLINE void __pyx_f_5numpy_set_array_base(PyArrayObject *__pyx_v_arr, PyObject *__pyx_v_base) {
  PyObject *__pyx_v_baseptr;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  __Pyx_RefNannySetupContext("set_array_base", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":968
 * cdef inline void set_array_base(ndarray arr, object base):
 *      cdef PyObject* baseptr
 *      if base is None:             # <<<<<<<<<<<<<<
 *          baseptr = NULL
 *      else:
 */
  __pyx_t_1 = (__pyx_v_base == Py_None);
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":969
 *      cdef PyObject* baseptr
 *      if base is None:
 *          baseptr = NULL             # <<<<<<<<<<<<<<
 *      else:
 *          Py_INCREF(base) # important to do this before decref below!
 */
    __pyx_v_baseptr = NULL;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":968
 * cdef inline void set_array_base(ndarray arr, object base):
 *      cdef PyObject* baseptr
 *      if base is None:             # <<<<<<<<<<<<<<
 *          baseptr = NULL
 *      else:
 */
    goto __pyx_L3;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":971
 *          baseptr = NULL
 *      else:
 *          Py_INCREF(base) # important to do this before decref below!             # <<<<<<<<<<<<<<
 *          baseptr = <PyObject*>base
 *      Py_XDECREF(arr.base)
 */
  /*else*/ {
    Py_INCREF(__pyx_v_base);

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":972
 *      else:
 *          Py_INCREF(base) # important to do this before decref below!
 *          baseptr = <PyObject*>base             # <<<<<<<<<<<<<<
 *      Py_XDECREF(arr.base)
 *      arr.base = baseptr
 */
    __pyx_v_baseptr = ((PyObject *)__pyx_v_base);
  }
  __pyx_L3:;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":973
 *          Py_INCREF(base) # important to do this before decref below!
 *          baseptr = <PyObject*>base
 *      Py_XDECREF(arr.base)             # <<<<<<<<<<<<<<
 *      arr.base = baseptr
 * 
 */
  Py_XDECREF(__pyx_v_arr->base);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":974
 *          baseptr = <PyObject*>base
 *      Py_XDECREF(arr.base)
 *      arr.base = baseptr             # <<<<<<<<<<<<<<
 * 
 * cdef inline object get_array_base(ndarray arr):
 */
  __pyx_v_arr->base = __pyx_v_baseptr;

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":966
 * 
 * 
 * cdef inline void set_array_base(ndarray arr, object base):             # <<<<<<<<<<<<<<
 *      cdef PyObject* baseptr
 *      if base is None:
 */

  /* function exit code */
  __Pyx_RefNannyFinishContext();
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":976
 *      arr.base = baseptr
 * 
 * cdef inline object get_array_base(ndarray arr):             # <<<<<<<<<<<<<<
 *     if arr.base is NULL:
 *         return None
 */

static CYTHON_INLINE PyObject *__pyx_f_5numpy_get_array_base(PyArrayObject *__pyx_v_arr) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("get_array_base", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":977
 * 
 * cdef inline object get_array_base(ndarray arr):
 *     if arr.base is NULL:             # <<<<<<<<<<<<<<
 *         return None
 *     else:
 */
  __pyx_t_1 = ((__pyx_v_arr->base == NULL) != 0);
  if (__pyx_t_1) {

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":978
 * cdef inline object get_array_base(ndarray arr):
 *     if arr.base is NULL:
 *         return None             # <<<<<<<<<<<<<<
 *     else:
 *         return <object>arr.base
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(Py_None);
    __pyx_r = Py_None;
    goto __pyx_L0;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":977
 * 
 * cdef inline object get_array_base(ndarray arr):
 *     if arr.base is NULL:             # <<<<<<<<<<<<<<
 *         return None
 *     else:
 */
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":980
 *         return None
 *     else:
 *         return <object>arr.base             # <<<<<<<<<<<<<<
 * 
 * 
 */
  /*else*/ {
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(((PyObject *)__pyx_v_arr->base));
    __pyx_r = ((PyObject *)__pyx_v_arr->base);
    goto __pyx_L0;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":976
 *      arr.base = baseptr
 * 
 * cdef inline object get_array_base(ndarray arr):             # <<<<<<<<<<<<<<
 *     if arr.base is NULL:
 *         return None
 */

  /* function exit code */
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":985
 * # Versions of the import_* functions which are more suitable for
 * # Cython code.
 * cdef inline int import_array() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_array()
 */

static CYTHON_INLINE int __pyx_f_5numpy_import_array(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  __Pyx_RefNannySetupContext("import_array", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":986
 * # Cython code.
 * cdef inline int import_array() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_array()
 *     except Exception:
 */
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
    /*try:*/ {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":987
 * cdef inline int import_array() except -1:
 *     try:
 *         _import_array()             # <<<<<<<<<<<<<<
 *     except Exception:
 *         raise ImportError("numpy.core.multiarray failed to import")
 */
      __pyx_t_4 = _import_array(); if (unlikely(__pyx_t_4 == -1)) __PYX_ERR(1, 987, __pyx_L3_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":986
 * # Cython code.
 * cdef inline int import_array() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_array()
 *     except Exception:
 */
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L10_try_end;
    __pyx_L3_error:;
    __Pyx_PyThreadState_assign

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":988
 *     try:
 *         _import_array()
 *     except Exception:             # <<<<<<<<<<<<<<
 *         raise ImportError("numpy.core.multiarray failed to import")
 * 
 */
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_array", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 988, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":989
 *         _import_array()
 *     except Exception:
 *         raise ImportError("numpy.core.multiarray failed to import")             # <<<<<<<<<<<<<<
 * 
 * cdef inline int import_umath() except -1:
 */
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__43, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 989, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 989, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":986
 * # Cython code.
 * cdef inline int import_array() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_array()
 *     except Exception:
 */
    __Pyx_PyThreadState_assign
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L10_try_end:;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":985
 * # Versions of the import_* functions which are more suitable for
 * # Cython code.
 * cdef inline int import_array() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_array()
 */

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_array", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":991
 *         raise ImportError("numpy.core.multiarray failed to import")
 * 
 * cdef inline int import_umath() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_umath()
 */

static CYTHON_INLINE int __pyx_f_5numpy_import_umath(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  __Pyx_RefNannySetupContext("import_umath", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":992
 * 
 * cdef inline int import_umath() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
    /*try:*/ {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":993
 * cdef inline int import_umath() except -1:
 *     try:
 *         _import_umath()             # <<<<<<<<<<<<<<
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")
 */
      __pyx_t_4 = _import_umath(); if (unlikely(__pyx_t_4 == -1)) __PYX_ERR(1, 993, __pyx_L3_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":992
 * 
 * cdef inline int import_umath() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L10_try_end;
    __pyx_L3_error:;
    __Pyx_PyThreadState_assign

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":994
 *     try:
 *         _import_umath()
 *     except Exception:             # <<<<<<<<<<<<<<
 *         raise ImportError("numpy.core.umath failed to import")
 * 
 */
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_umath", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 994, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":995
 *         _import_umath()
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")             # <<<<<<<<<<<<<<
 * 
 * cdef inline int import_ufunc() except -1:
 */
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__44, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 995, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 995, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":992
 * 
 * cdef inline int import_umath() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
    __Pyx_PyThreadState_assign
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L10_try_end:;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":991
 *         raise ImportError("numpy.core.multiarray failed to import")
 * 
 * cdef inline int import_umath() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_umath()
 */

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_umath", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":997
 *         raise ImportError("numpy.core.umath failed to import")
 * 
 * cdef inline int import_ufunc() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_umath()
 */

static CYTHON_INLINE int __pyx_f_5numpy_import_ufunc(void) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  __Pyx_RefNannySetupContext("import_ufunc", 0);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":998
 * 
 * cdef inline int import_ufunc() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
  {
    __Pyx_PyThreadState_declare
    __Pyx_PyThreadState_assign
    __Pyx_ExceptionSave(&__pyx_t_1, &__pyx_t_2, &__pyx_t_3);
    __Pyx_XGOTREF(__pyx_t_1);
    __Pyx_XGOTREF(__pyx_t_2);
    __Pyx_XGOTREF(__pyx_t_3);
    /*try:*/ {

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":999
 * cdef inline int import_ufunc() except -1:
 *     try:
 *         _import_umath()             # <<<<<<<<<<<<<<
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")
 */
      __pyx_t_4 = _import_umath(); if (unlikely(__pyx_t_4 == -1)) __PYX_ERR(1, 999, __pyx_L3_error)

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":998
 * 
 * cdef inline int import_ufunc() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
    }
    __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L10_try_end;
    __pyx_L3_error:;
    __Pyx_PyThreadState_assign

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":1000
 *     try:
 *         _import_umath()
 *     except Exception:             # <<<<<<<<<<<<<<
 *         raise ImportError("numpy.core.umath failed to import")
 */
    __pyx_t_4 = __Pyx_PyErr_ExceptionMatches(((PyObject *)(&((PyTypeObject*)PyExc_Exception)[0])));
    if (__pyx_t_4) {
      __Pyx_AddTraceback("numpy.import_ufunc", __pyx_clineno, __pyx_lineno, __pyx_filename);
      if (__Pyx_GetException(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7) < 0) __PYX_ERR(1, 1000, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GOTREF(__pyx_t_7);

      /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":1001
 *         _import_umath()
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")             # <<<<<<<<<<<<<<
 */
      __pyx_t_8 = __Pyx_PyObject_Call(__pyx_builtin_ImportError, __pyx_tuple__45, NULL); if (unlikely(!__pyx_t_8)) __PYX_ERR(1, 1001, __pyx_L5_except_error)
      __Pyx_GOTREF(__pyx_t_8);
      __Pyx_Raise(__pyx_t_8, 0, 0, 0);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
      __PYX_ERR(1, 1001, __pyx_L5_except_error)
    }
    goto __pyx_L5_except_error;
    __pyx_L5_except_error:;

    /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":998
 * 
 * cdef inline int import_ufunc() except -1:
 *     try:             # <<<<<<<<<<<<<<
 *         _import_umath()
 *     except Exception:
 */
    __Pyx_PyThreadState_assign
    __Pyx_XGIVEREF(__pyx_t_1);
    __Pyx_XGIVEREF(__pyx_t_2);
    __Pyx_XGIVEREF(__pyx_t_3);
    __Pyx_ExceptionReset(__pyx_t_1, __pyx_t_2, __pyx_t_3);
    goto __pyx_L1_error;
    __pyx_L10_try_end:;
  }

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":997
 *         raise ImportError("numpy.core.umath failed to import")
 * 
 * cdef inline int import_ufunc() except -1:             # <<<<<<<<<<<<<<
 *     try:
 *         _import_umath()
 */

  /* function exit code */
  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_AddTraceback("numpy.import_ufunc", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vector.from_py":49
 * 
 * @cname("__pyx_convert_vector_from_py_size_t")
 * cdef vector[X] __pyx_convert_vector_from_py_size_t(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef vector[X] v
 *     for item in o:
 */

static std::vector<size_t>  __pyx_convert_vector_from_py_size_t(PyObject *__pyx_v_o) {
  std::vector<size_t>  __pyx_v_v;
  PyObject *__pyx_v_item = NULL;
  std::vector<size_t>  __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *(*__pyx_t_3)(PyObject *);
  PyObject *__pyx_t_4 = NULL;
  size_t __pyx_t_5;
  __Pyx_RefNannySetupContext("__pyx_convert_vector_from_py_size_t", 0);

  /* "vector.from_py":51
 * cdef vector[X] __pyx_convert_vector_from_py_size_t(object o) except *:
 *     cdef vector[X] v
 *     for item in o:             # <<<<<<<<<<<<<<
 *         v.push_back(X_from_py(item))
 *     return v
 */
  if (likely(PyList_CheckExact(__pyx_v_o)) || PyTuple_CheckExact(__pyx_v_o)) {
    __pyx_t_1 = __pyx_v_o; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
    __pyx_t_3 = NULL;
  } else {
    __pyx_t_2 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_v_o); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 51, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 51, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_3)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 51, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 51, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      } else {
        if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 51, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 51, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      }
    } else {
      __pyx_t_4 = __pyx_t_3(__pyx_t_1);
      if (unlikely(!__pyx_t_4)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(2, 51, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_4);
    }
    __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "vector.from_py":52
 *     cdef vector[X] v
 *     for item in o:
 *         v.push_back(X_from_py(item))             # <<<<<<<<<<<<<<
 *     return v
 * 
 */
    __pyx_t_5 = __Pyx_PyInt_As_size_t(__pyx_v_item); if (unlikely(__pyx_t_5 == -1L && PyErr_Occurred())) __PYX_ERR(2, 52, __pyx_L1_error)
    __pyx_v_v.push_back(__pyx_t_5);

    /* "vector.from_py":51
 * cdef vector[X] __pyx_convert_vector_from_py_size_t(object o) except *:
 *     cdef vector[X] v
 *     for item in o:             # <<<<<<<<<<<<<<
 *         v.push_back(X_from_py(item))
 *     return v
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vector.from_py":53
 *     for item in o:
 *         v.push_back(X_from_py(item))
 *     return v             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_r = __pyx_v_v;
  goto __pyx_L0;

  /* "vector.from_py":49
 * 
 * @cname("__pyx_convert_vector_from_py_size_t")
 * cdef vector[X] __pyx_convert_vector_from_py_size_t(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef vector[X] v
 *     for item in o:
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("vector.from_py.__pyx_convert_vector_from_py_size_t", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_item);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vector.to_py":67
 * 
 * @cname("__pyx_convert_vector_to_py_size_t")
 * cdef object __pyx_convert_vector_to_py_size_t(vector[X]& v):             # <<<<<<<<<<<<<<
 *     return [X_to_py(v[i]) for i in range(v.size())]
 * 
 */

static PyObject *__pyx_convert_vector_to_py_size_t(const std::vector<size_t>  &__pyx_v_v) {
  size_t __pyx_v_i;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  size_t __pyx_t_2;
  size_t __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  __Pyx_RefNannySetupContext("__pyx_convert_vector_to_py_size_t", 0);

  /* "vector.to_py":68
 * @cname("__pyx_convert_vector_to_py_size_t")
 * cdef object __pyx_convert_vector_to_py_size_t(vector[X]& v):
 *     return [X_to_py(v[i]) for i in range(v.size())]             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 68, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __pyx_v_v.size();
  for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
    __pyx_v_i = __pyx_t_3;
    __pyx_t_4 = __Pyx_PyInt_FromSize_t((__pyx_v_v[__pyx_v_i])); if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 68, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_4);
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_1, (PyObject*)__pyx_t_4))) __PYX_ERR(2, 68, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  }
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "vector.to_py":67
 * 
 * @cname("__pyx_convert_vector_to_py_size_t")
 * cdef object __pyx_convert_vector_to_py_size_t(vector[X]& v):             # <<<<<<<<<<<<<<
 *     return [X_to_py(v[i]) for i in range(v.size())]
 * 
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("vector.to_py.__pyx_convert_vector_to_py_size_t", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "string.from_py":13
 * 
 * @cname("__pyx_convert_string_from_py_std__in_string")
 * cdef string __pyx_convert_string_from_py_std__in_string(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef Py_ssize_t length
 *     cdef char* data = __Pyx_PyObject_AsStringAndSize(o, &length)
 */

static std::string __pyx_convert_string_from_py_std__in_string(PyObject *__pyx_v_o) {
  Py_ssize_t __pyx_v_length;
  char *__pyx_v_data;
  std::string __pyx_r;
  __Pyx_RefNannyDeclarations
  char *__pyx_t_1;
  __Pyx_RefNannySetupContext("__pyx_convert_string_from_py_std__in_string", 0);

  /* "string.from_py":15
 * cdef string __pyx_convert_string_from_py_std__in_string(object o) except *:
 *     cdef Py_ssize_t length
 *     cdef char* data = __Pyx_PyObject_AsStringAndSize(o, &length)             # <<<<<<<<<<<<<<
 *     return string(data, length)
 * 
 */
  __pyx_t_1 = __Pyx_PyObject_AsStringAndSize(__pyx_v_o, (&__pyx_v_length)); if (unlikely(__pyx_t_1 == NULL)) __PYX_ERR(2, 15, __pyx_L1_error)
  __pyx_v_data = __pyx_t_1;

  /* "string.from_py":16
 *     cdef Py_ssize_t length
 *     cdef char* data = __Pyx_PyObject_AsStringAndSize(o, &length)
 *     return string(data, length)             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_r = std::string(__pyx_v_data, __pyx_v_length);
  goto __pyx_L0;

  /* "string.from_py":13
 * 
 * @cname("__pyx_convert_string_from_py_std__in_string")
 * cdef string __pyx_convert_string_from_py_std__in_string(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef Py_ssize_t length
 *     cdef char* data = __Pyx_PyObject_AsStringAndSize(o, &length)
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_AddTraceback("string.from_py.__pyx_convert_string_from_py_std__in_string", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "vector.from_py":49
 * 
 * @cname("__pyx_convert_vector_from_py_double")
 * cdef vector[X] __pyx_convert_vector_from_py_double(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef vector[X] v
 *     for item in o:
 */

static std::vector<double>  __pyx_convert_vector_from_py_double(PyObject *__pyx_v_o) {
  std::vector<double>  __pyx_v_v;
  PyObject *__pyx_v_item = NULL;
  std::vector<double>  __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  PyObject *(*__pyx_t_3)(PyObject *);
  PyObject *__pyx_t_4 = NULL;
  double __pyx_t_5;
  __Pyx_RefNannySetupContext("__pyx_convert_vector_from_py_double", 0);

  /* "vector.from_py":51
 * cdef vector[X] __pyx_convert_vector_from_py_double(object o) except *:
 *     cdef vector[X] v
 *     for item in o:             # <<<<<<<<<<<<<<
 *         v.push_back(X_from_py(item))
 *     return v
 */
  if (likely(PyList_CheckExact(__pyx_v_o)) || PyTuple_CheckExact(__pyx_v_o)) {
    __pyx_t_1 = __pyx_v_o; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
    __pyx_t_3 = NULL;
  } else {
    __pyx_t_2 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_v_o); if (unlikely(!__pyx_t_1)) __PYX_ERR(2, 51, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_3)) __PYX_ERR(2, 51, __pyx_L1_error)
  }
  for (;;) {
    if (likely(!__pyx_t_3)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_4 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 51, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 51, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      } else {
        if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_4 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_4); __pyx_t_2++; if (unlikely(0 < 0)) __PYX_ERR(2, 51, __pyx_L1_error)
        #else
        __pyx_t_4 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_4)) __PYX_ERR(2, 51, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_4);
        #endif
      }
    } else {
      __pyx_t_4 = __pyx_t_3(__pyx_t_1);
      if (unlikely(!__pyx_t_4)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(2, 51, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_4);
    }
    __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_4);
    __pyx_t_4 = 0;

    /* "vector.from_py":52
 *     cdef vector[X] v
 *     for item in o:
 *         v.push_back(X_from_py(item))             # <<<<<<<<<<<<<<
 *     return v
 * 
 */
    __pyx_t_5 = __pyx_PyFloat_AsDouble(__pyx_v_item); if (unlikely(__pyx_t_5 == -1.0 && PyErr_Occurred())) __PYX_ERR(2, 52, __pyx_L1_error)
    __pyx_v_v.push_back(__pyx_t_5);

    /* "vector.from_py":51
 * cdef vector[X] __pyx_convert_vector_from_py_double(object o) except *:
 *     cdef vector[X] v
 *     for item in o:             # <<<<<<<<<<<<<<
 *         v.push_back(X_from_py(item))
 *     return v
 */
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "vector.from_py":53
 *     for item in o:
 *         v.push_back(X_from_py(item))
 *     return v             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_r = __pyx_v_v;
  goto __pyx_L0;

  /* "vector.from_py":49
 * 
 * @cname("__pyx_convert_vector_from_py_double")
 * cdef vector[X] __pyx_convert_vector_from_py_double(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef vector[X] v
 *     for item in o:
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("vector.from_py.__pyx_convert_vector_from_py_double", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_item);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

static int __pyx_import_star_set(PyObject *o, PyObject* py_name, char *name) {
  static const char* internal_type_names[] = {
    "X",
    "__pyx_ctuple_7f172__unsigned__space_int__and_unsigned__space_int__and_unsigned__space_int__etc",
    "__pyx_ctuple_7f172__unsigned__space_int__and_unsigned__space_int__and_unsigned__space_int__etc_struct",
    "__pyx_ctuple___dunderpyx_ctuple_size_t__dunderand_long",
    "__pyx_ctuple___dunderpyx_ctuple_size_t__dunderand_long_struct",
    "__pyx_ctuple_long__and_size_t",
    "__pyx_ctuple_long__and_size_t_struct",
    "__pyx_ctuple_size_t",
    "__pyx_ctuple_size_t__and_long",
    "__pyx_ctuple_size_t__and_long_struct",
    "__pyx_ctuple_size_t__and_unsigned__space_int",
    "__pyx_ctuple_size_t__and_unsigned__space_int_struct",
    "__pyx_ctuple_size_t_struct",
    "__pyx_ctuple_std__in_vector__lAngsize_t__rAng",
    "__pyx_ctuple_std__in_vector__lAngsize_t__rAng_struct",
    "bool",
    "string",
    "vector",
    0
  };
  const char** type_name = internal_type_names;
  while (*type_name) {
    if (__Pyx_StrEq(name, *type_name)) {
      PyErr_Format(PyExc_TypeError, "Cannot overwrite C type %s", name);
      goto bad;
    }
    type_name++;
  }
  if (0);
  else if (__Pyx_StrEq(name, "EPS")) {
    __pyx_v_4nngt_10generation_8cconnect_EPS = __pyx_PyFloat_AsFloat(o); if (unlikely((__pyx_v_4nngt_10generation_8cconnect_EPS == (float)-1) && PyErr_Occurred())) __PYX_ERR(0, 37, __pyx_L2_error)
  }
  else if (__Pyx_StrEq(name, "MAXTESTS")) {
    __pyx_v_4nngt_10generation_8cconnect_MAXTESTS = __Pyx_PyInt_As_int(o); if (unlikely((__pyx_v_4nngt_10generation_8cconnect_MAXTESTS == (int)-1) && PyErr_Occurred())) __PYX_ERR(0, 36, __pyx_L2_error)
  }
  else {
    if (PyObject_SetAttr(__pyx_m, py_name, o) < 0) goto bad;
  }
  return 0;
  __pyx_L2_error:;
  __Pyx_AddTraceback("nngt.generation.cconnect", __pyx_clineno, __pyx_lineno, __pyx_filename);
  bad:
  return -1;
}

























































































































static int
__Pyx_import_all_from(PyObject *locals, PyObject *v)
{
    PyObject *all = PyObject_GetAttrString(v, "__all__");
    PyObject *dict, *name, *value;
    int skip_leading_underscores = 0;
    int pos, err;

    if (all == NULL) {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError))
            return -1;
        PyErr_Clear();
        dict = PyObject_GetAttrString(v, "__dict__");
        if (dict == NULL) {
            if (!PyErr_ExceptionMatches(PyExc_AttributeError))
                return -1;
            PyErr_SetString(PyExc_ImportError,
            "from-import-* object has no __dict__ and no __all__");
            return -1;
        }
#if PY_MAJOR_VERSION < 3
        all = PyObject_CallMethod(dict, (char *)"keys", NULL);
#else
        all = PyMapping_Keys(dict);
#endif
        Py_DECREF(dict);
        if (all == NULL)
            return -1;
        skip_leading_underscores = 1;
    }

    for (pos = 0, err = 0; ; pos++) {
        name = PySequence_GetItem(all, pos);
        if (name == NULL) {
            if (!PyErr_ExceptionMatches(PyExc_IndexError))
                err = -1;
            else
                PyErr_Clear();
            break;
        }
        if (skip_leading_underscores &&
#if PY_MAJOR_VERSION < 3
            PyString_Check(name) &&
            PyString_AS_STRING(name)[0] == '_')
#else
            PyUnicode_Check(name) &&
            PyUnicode_AS_UNICODE(name)[0] == '_')
#endif
        {
            Py_DECREF(name);
            continue;
        }
        value = PyObject_GetAttr(v, name);
        if (value == NULL)
            err = -1;
        else if (PyDict_CheckExact(locals))
            err = PyDict_SetItem(locals, name, value);
        else
            err = PyObject_SetItem(locals, name, value);
        Py_DECREF(name);
        Py_XDECREF(value);
        if (err != 0)
            break;
    }
    Py_DECREF(all);
    return err;
}


static int __pyx_import_star(PyObject* m) {

    int i;
    int ret = -1;
    char* s;
    PyObject *locals = 0;
    PyObject *list = 0;
#if PY_MAJOR_VERSION >= 3
    PyObject *utf8_name = 0;
#endif
    PyObject *name;
    PyObject *item;

    locals = PyDict_New();              if (!locals) goto bad;
    if (__Pyx_import_all_from(locals, m) < 0) goto bad;
    list = PyDict_Items(locals);        if (!list) goto bad;

    for(i=0; i<PyList_GET_SIZE(list); i++) {
        name = PyTuple_GET_ITEM(PyList_GET_ITEM(list, i), 0);
        item = PyTuple_GET_ITEM(PyList_GET_ITEM(list, i), 1);
#if PY_MAJOR_VERSION >= 3
        utf8_name = PyUnicode_AsUTF8String(name);
        if (!utf8_name) goto bad;
        s = PyBytes_AS_STRING(utf8_name);
        if (__pyx_import_star_set(item, name, s) < 0) goto bad;
        Py_DECREF(utf8_name); utf8_name = 0;
#else
        s = PyString_AsString(name);
        if (!s) goto bad;
        if (__pyx_import_star_set(item, name, s) < 0) goto bad;
#endif
    }
    ret = 0;

bad:
    Py_XDECREF(locals);
    Py_XDECREF(list);
#if PY_MAJOR_VERSION >= 3
    Py_XDECREF(utf8_name);
#endif
    return ret;
}



#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    "cconnect",
    __pyx_k_Generation_tools_for_NNGT, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_n_s_DTYPE, __pyx_k_DTYPE, sizeof(__pyx_k_DTYPE), 0, 0, 1, 1},
  {&__pyx_kp_u_Format_string_allocated_too_shor, __pyx_k_Format_string_allocated_too_shor, sizeof(__pyx_k_Format_string_allocated_too_shor), 0, 1, 0, 0},
  {&__pyx_kp_u_Format_string_allocated_too_shor_2, __pyx_k_Format_string_allocated_too_shor_2, sizeof(__pyx_k_Format_string_allocated_too_shor_2), 0, 1, 0, 0},
  {&__pyx_n_s_ImportError, __pyx_k_ImportError, sizeof(__pyx_k_ImportError), 0, 0, 1, 1},
  {&__pyx_n_s_InvalidArgument, __pyx_k_InvalidArgument, sizeof(__pyx_k_InvalidArgument), 0, 0, 1, 1},
  {&__pyx_kp_u_Non_native_byte_order_not_suppor, __pyx_k_Non_native_byte_order_not_suppor, sizeof(__pyx_k_Non_native_byte_order_not_suppor), 0, 1, 0, 0},
  {&__pyx_n_s_RuntimeError, __pyx_k_RuntimeError, sizeof(__pyx_k_RuntimeError), 0, 0, 1, 1},
  {&__pyx_n_s_T, __pyx_k_T, sizeof(__pyx_k_T), 0, 0, 1, 1},
  {&__pyx_kp_s_This_graph_model_can_only_be_use, __pyx_k_This_graph_model_can_only_be_use, sizeof(__pyx_k_This_graph_model_can_only_be_use), 0, 0, 1, 0},
  {&__pyx_kp_s_UTF_8, __pyx_k_UTF_8, sizeof(__pyx_k_UTF_8), 0, 0, 1, 0},
  {&__pyx_n_s_ValueError, __pyx_k_ValueError, sizeof(__pyx_k_ValueError), 0, 0, 1, 1},
  {&__pyx_n_s__46, __pyx_k__46, sizeof(__pyx_k__46), 0, 0, 1, 1},
  {&__pyx_n_s__66, __pyx_k__66, sizeof(__pyx_k__66), 0, 0, 1, 1},
  {&__pyx_n_s_abs, __pyx_k_abs, sizeof(__pyx_k_abs), 0, 0, 1, 1},
  {&__pyx_n_s_all, __pyx_k_all, sizeof(__pyx_k_all), 0, 0, 1, 1},
  {&__pyx_n_s_arange, __pyx_k_arange, sizeof(__pyx_k_arange), 0, 0, 1, 1},
  {&__pyx_n_s_area, __pyx_k_area, sizeof(__pyx_k_area), 0, 0, 1, 1},
  {&__pyx_n_s_around, __pyx_k_around, sizeof(__pyx_k_around), 0, 0, 1, 1},
  {&__pyx_n_s_arr, __pyx_k_arr, sizeof(__pyx_k_arr), 0, 0, 1, 1},
  {&__pyx_n_s_array, __pyx_k_array, sizeof(__pyx_k_array), 0, 0, 1, 1},
  {&__pyx_n_s_ascontiguousarray, __pyx_k_ascontiguousarray, sizeof(__pyx_k_ascontiguousarray), 0, 0, 1, 1},
  {&__pyx_n_s_astype, __pyx_k_astype, sizeof(__pyx_k_astype), 0, 0, 1, 1},
  {&__pyx_n_s_avg, __pyx_k_avg, sizeof(__pyx_k_avg), 0, 0, 1, 1},
  {&__pyx_n_s_avg_deg, __pyx_k_avg_deg, sizeof(__pyx_k_avg_deg), 0, 0, 1, 1},
  {&__pyx_n_s_b, __pyx_k_b, sizeof(__pyx_k_b), 0, 0, 1, 1},
  {&__pyx_n_s_b_one_pop, __pyx_k_b_one_pop, sizeof(__pyx_k_b_one_pop), 0, 0, 1, 1},
  {&__pyx_n_s_b_out, __pyx_k_b_out, sizeof(__pyx_k_b_out), 0, 0, 1, 1},
  {&__pyx_n_s_b_total, __pyx_k_b_total, sizeof(__pyx_k_b_total), 0, 0, 1, 1},
  {&__pyx_n_s_cedges, __pyx_k_cedges, sizeof(__pyx_k_cedges), 0, 0, 1, 1},
  {&__pyx_n_s_check_num_edges, __pyx_k_check_num_edges, sizeof(__pyx_k_check_num_edges), 0, 0, 1, 1},
  {&__pyx_n_s_circular_edges, __pyx_k_circular_edges, sizeof(__pyx_k_circular_edges), 0, 0, 1, 1},
  {&__pyx_n_s_circular_graph, __pyx_k_circular_graph, sizeof(__pyx_k_circular_graph), 0, 0, 1, 1},
  {&__pyx_n_s_cnum_neurons, __pyx_k_cnum_neurons, sizeof(__pyx_k_cnum_neurons), 0, 0, 1, 1},
  {&__pyx_n_s_compute_connections, __pyx_k_compute_connections, sizeof(__pyx_k_compute_connections), 0, 0, 1, 1},
  {&__pyx_n_s_concatenate, __pyx_k_concatenate, sizeof(__pyx_k_concatenate), 0, 0, 1, 1},
  {&__pyx_n_s_config, __pyx_k_config, sizeof(__pyx_k_config), 0, 0, 1, 1},
  {&__pyx_n_s_connect_tools, __pyx_k_connect_tools, sizeof(__pyx_k_connect_tools), 0, 0, 1, 1},
  {&__pyx_n_s_coord_nb, __pyx_k_coord_nb, sizeof(__pyx_k_coord_nb), 0, 0, 1, 1},
  {&__pyx_n_s_crule, __pyx_k_crule, sizeof(__pyx_k_crule), 0, 0, 1, 1},
  {&__pyx_n_s_degree, __pyx_k_degree, sizeof(__pyx_k_degree), 0, 0, 1, 1},
  {&__pyx_n_s_degree_type, __pyx_k_degree_type, sizeof(__pyx_k_degree_type), 0, 0, 1, 1},
  {&__pyx_n_s_degrees, __pyx_k_degrees, sizeof(__pyx_k_degrees), 0, 0, 1, 1},
  {&__pyx_n_s_density, __pyx_k_density, sizeof(__pyx_k_density), 0, 0, 1, 1},
  {&__pyx_n_s_diff_in, __pyx_k_diff_in, sizeof(__pyx_k_diff_in), 0, 0, 1, 1},
  {&__pyx_n_s_diff_out, __pyx_k_diff_out, sizeof(__pyx_k_diff_out), 0, 0, 1, 1},
  {&__pyx_n_s_directed, __pyx_k_directed, sizeof(__pyx_k_directed), 0, 0, 1, 1},
  {&__pyx_n_s_dist, __pyx_k_dist, sizeof(__pyx_k_dist), 0, 0, 1, 1},
  {&__pyx_n_s_distance_rule, __pyx_k_distance_rule, sizeof(__pyx_k_distance_rule), 0, 0, 1, 1},
  {&__pyx_n_s_dtype, __pyx_k_dtype, sizeof(__pyx_k_dtype), 0, 0, 1, 1},
  {&__pyx_n_s_edge_num, __pyx_k_edge_num, sizeof(__pyx_k_edge_num), 0, 0, 1, 1},
  {&__pyx_n_s_edges, __pyx_k_edges, sizeof(__pyx_k_edges), 0, 0, 1, 1},
  {&__pyx_n_s_erdos_renyi, __pyx_k_erdos_renyi, sizeof(__pyx_k_erdos_renyi), 0, 0, 1, 1},
  {&__pyx_n_s_existing, __pyx_k_existing, sizeof(__pyx_k_existing), 0, 0, 1, 1},
  {&__pyx_n_s_existing_edges, __pyx_k_existing_edges, sizeof(__pyx_k_existing_edges), 0, 0, 1, 1},
  {&__pyx_n_s_filter, __pyx_k_filter, sizeof(__pyx_k_filter), 0, 0, 1, 1},
  {&__pyx_n_s_fixed_degree, __pyx_k_fixed_degree, sizeof(__pyx_k_fixed_degree), 0, 0, 1, 1},
  {&__pyx_n_s_floor, __pyx_k_floor, sizeof(__pyx_k_floor), 0, 0, 1, 1},
  {&__pyx_n_s_gaussian_degree, __pyx_k_gaussian_degree, sizeof(__pyx_k_gaussian_degree), 0, 0, 1, 1},
  {&__pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_k_home_tfardet_Documents_NNGT_nng, sizeof(__pyx_k_home_tfardet_Documents_NNGT_nng), 0, 0, 1, 0},
  {&__pyx_n_s_ia_base, __pyx_k_ia_base, sizeof(__pyx_k_ia_base), 0, 0, 1, 1},
  {&__pyx_n_s_ia_edges, __pyx_k_ia_edges, sizeof(__pyx_k_ia_edges), 0, 0, 1, 1},
  {&__pyx_n_s_ia_edges_tmp, __pyx_k_ia_edges_tmp, sizeof(__pyx_k_ia_edges_tmp), 0, 0, 1, 1},
  {&__pyx_n_s_ia_in_deg, __pyx_k_ia_in_deg, sizeof(__pyx_k_ia_in_deg), 0, 0, 1, 1},
  {&__pyx_n_s_ia_indices, __pyx_k_ia_indices, sizeof(__pyx_k_ia_indices), 0, 0, 1, 1},
  {&__pyx_n_s_ia_out_deg, __pyx_k_ia_out_deg, sizeof(__pyx_k_ia_out_deg), 0, 0, 1, 1},
  {&__pyx_n_s_ia_sources, __pyx_k_ia_sources, sizeof(__pyx_k_ia_sources), 0, 0, 1, 1},
  {&__pyx_n_s_ia_sources_tmp, __pyx_k_ia_sources_tmp, sizeof(__pyx_k_ia_sources_tmp), 0, 0, 1, 1},
  {&__pyx_n_s_ia_targets, __pyx_k_ia_targets, sizeof(__pyx_k_ia_targets), 0, 0, 1, 1},
  {&__pyx_n_s_ia_targets_tmp, __pyx_k_ia_targets_tmp, sizeof(__pyx_k_ia_targets_tmp), 0, 0, 1, 1},
  {&__pyx_n_s_idx, __pyx_k_idx, sizeof(__pyx_k_idx), 0, 0, 1, 1},
  {&__pyx_n_s_idx_correct_in, __pyx_k_idx_correct_in, sizeof(__pyx_k_idx_correct_in), 0, 0, 1, 1},
  {&__pyx_n_s_idx_correct_out, __pyx_k_idx_correct_out, sizeof(__pyx_k_idx_correct_out), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_in_exp, __pyx_k_in_exp, sizeof(__pyx_k_in_exp), 0, 0, 1, 1},
  {&__pyx_n_s_itemsize, __pyx_k_itemsize, sizeof(__pyx_k_itemsize), 0, 0, 1, 1},
  {&__pyx_n_s_kwargs, __pyx_k_kwargs, sizeof(__pyx_k_kwargs), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_maximum, __pyx_k_maximum, sizeof(__pyx_k_maximum), 0, 0, 1, 1},
  {&__pyx_n_s_msd, __pyx_k_msd, sizeof(__pyx_k_msd), 0, 0, 1, 1},
  {&__pyx_n_s_multigraph, __pyx_k_multigraph, sizeof(__pyx_k_multigraph), 0, 0, 1, 1},
  {&__pyx_n_s_multiply, __pyx_k_multiply, sizeof(__pyx_k_multiply), 0, 0, 1, 1},
  {&__pyx_kp_u_ndarray_is_not_C_contiguous, __pyx_k_ndarray_is_not_C_contiguous, sizeof(__pyx_k_ndarray_is_not_C_contiguous), 0, 1, 0, 0},
  {&__pyx_kp_u_ndarray_is_not_Fortran_contiguou, __pyx_k_ndarray_is_not_Fortran_contiguou, sizeof(__pyx_k_ndarray_is_not_Fortran_contiguou), 0, 1, 0, 0},
  {&__pyx_n_s_neg_dist, __pyx_k_neg_dist, sizeof(__pyx_k_neg_dist), 0, 0, 1, 1},
  {&__pyx_n_s_newman_watts, __pyx_k_newman_watts, sizeof(__pyx_k_newman_watts), 0, 0, 1, 1},
  {&__pyx_n_s_nngt, __pyx_k_nngt, sizeof(__pyx_k_nngt), 0, 0, 1, 1},
  {&__pyx_n_s_nngt_generation_cconnect, __pyx_k_nngt_generation_cconnect, sizeof(__pyx_k_nngt_generation_cconnect), 0, 0, 1, 1},
  {&__pyx_n_s_nngt_lib, __pyx_k_nngt_lib, sizeof(__pyx_k_nngt_lib), 0, 0, 1, 1},
  {&__pyx_n_s_no_self_loops, __pyx_k_no_self_loops, sizeof(__pyx_k_no_self_loops), 0, 0, 1, 1},
  {&__pyx_n_s_node_ids, __pyx_k_node_ids, sizeof(__pyx_k_node_ids), 0, 0, 1, 1},
  {&__pyx_n_s_nodes, __pyx_k_nodes, sizeof(__pyx_k_nodes), 0, 0, 1, 1},
  {&__pyx_n_s_normal, __pyx_k_normal, sizeof(__pyx_k_normal), 0, 0, 1, 1},
  {&__pyx_n_s_np, __pyx_k_np, sizeof(__pyx_k_np), 0, 0, 1, 1},
  {&__pyx_n_s_num_added, __pyx_k_num_added, sizeof(__pyx_k_num_added), 0, 0, 1, 1},
  {&__pyx_n_s_num_desired, __pyx_k_num_desired, sizeof(__pyx_k_num_desired), 0, 0, 1, 1},
  {&__pyx_n_s_num_ecurrent, __pyx_k_num_ecurrent, sizeof(__pyx_k_num_ecurrent), 0, 0, 1, 1},
  {&__pyx_n_s_num_edges, __pyx_k_num_edges, sizeof(__pyx_k_num_edges), 0, 0, 1, 1},
  {&__pyx_n_s_num_neurons, __pyx_k_num_neurons, sizeof(__pyx_k_num_neurons), 0, 0, 1, 1},
  {&__pyx_n_s_num_node, __pyx_k_num_node, sizeof(__pyx_k_num_node), 0, 0, 1, 1},
  {&__pyx_n_s_num_source, __pyx_k_num_source, sizeof(__pyx_k_num_source), 0, 0, 1, 1},
  {&__pyx_n_s_num_target, __pyx_k_num_target, sizeof(__pyx_k_num_target), 0, 0, 1, 1},
  {&__pyx_n_s_num_test, __pyx_k_num_test, sizeof(__pyx_k_num_test), 0, 0, 1, 1},
  {&__pyx_n_s_numpy, __pyx_k_numpy, sizeof(__pyx_k_numpy), 0, 0, 1, 1},
  {&__pyx_kp_s_numpy_core_multiarray_failed_to, __pyx_k_numpy_core_multiarray_failed_to, sizeof(__pyx_k_numpy_core_multiarray_failed_to), 0, 0, 1, 0},
  {&__pyx_kp_s_numpy_core_umath_failed_to_impor, __pyx_k_numpy_core_umath_failed_to_impor, sizeof(__pyx_k_numpy_core_umath_failed_to_impor), 0, 0, 1, 0},
  {&__pyx_n_s_numpy_random, __pyx_k_numpy_random, sizeof(__pyx_k_numpy_random), 0, 0, 1, 1},
  {&__pyx_n_s_old_edges, __pyx_k_old_edges, sizeof(__pyx_k_old_edges), 0, 0, 1, 1},
  {&__pyx_n_s_omp, __pyx_k_omp, sizeof(__pyx_k_omp), 0, 0, 1, 1},
  {&__pyx_n_s_out, __pyx_k_out, sizeof(__pyx_k_out), 0, 0, 1, 1},
  {&__pyx_n_s_out_exp, __pyx_k_out_exp, sizeof(__pyx_k_out_exp), 0, 0, 1, 1},
  {&__pyx_n_s_pareto, __pyx_k_pareto, sizeof(__pyx_k_pareto), 0, 0, 1, 1},
  {&__pyx_n_s_pos_dist, __pyx_k_pos_dist, sizeof(__pyx_k_pos_dist), 0, 0, 1, 1},
  {&__pyx_n_s_positions, __pyx_k_positions, sizeof(__pyx_k_positions), 0, 0, 1, 1},
  {&__pyx_n_s_pre_recip_edges, __pyx_k_pre_recip_edges, sizeof(__pyx_k_pre_recip_edges), 0, 0, 1, 1},
  {&__pyx_n_s_price_network, __pyx_k_price_network, sizeof(__pyx_k_price_network), 0, 0, 1, 1},
  {&__pyx_n_s_price_scale_free, __pyx_k_price_scale_free, sizeof(__pyx_k_price_scale_free), 0, 0, 1, 1},
  {&__pyx_n_s_proba_shortcut, __pyx_k_proba_shortcut, sizeof(__pyx_k_proba_shortcut), 0, 0, 1, 1},
  {&__pyx_n_s_randint, __pyx_k_randint, sizeof(__pyx_k_randint), 0, 0, 1, 1},
  {&__pyx_n_s_random, __pyx_k_random, sizeof(__pyx_k_random), 0, 0, 1, 1},
  {&__pyx_n_s_random_scale_free, __pyx_k_random_scale_free, sizeof(__pyx_k_random_scale_free), 0, 0, 1, 1},
  {&__pyx_n_s_range, __pyx_k_range, sizeof(__pyx_k_range), 0, 0, 1, 1},
  {&__pyx_n_s_reciprocity, __pyx_k_reciprocity, sizeof(__pyx_k_reciprocity), 0, 0, 1, 1},
  {&__pyx_n_s_repeat, __pyx_k_repeat, sizeof(__pyx_k_repeat), 0, 0, 1, 1},
  {&__pyx_n_s_reshape, __pyx_k_reshape, sizeof(__pyx_k_reshape), 0, 0, 1, 1},
  {&__pyx_n_s_rule, __pyx_k_rule, sizeof(__pyx_k_rule), 0, 0, 1, 1},
  {&__pyx_n_s_scale, __pyx_k_scale, sizeof(__pyx_k_scale), 0, 0, 1, 1},
  {&__pyx_n_s_scipy_sparse, __pyx_k_scipy_sparse, sizeof(__pyx_k_scipy_sparse), 0, 0, 1, 1},
  {&__pyx_n_s_seed, __pyx_k_seed, sizeof(__pyx_k_seed), 0, 0, 1, 1},
  {&__pyx_n_s_shape, __pyx_k_shape, sizeof(__pyx_k_shape), 0, 0, 1, 1},
  {&__pyx_n_s_shuffle, __pyx_k_shuffle, sizeof(__pyx_k_shuffle), 0, 0, 1, 1},
  {&__pyx_n_s_sign, __pyx_k_sign, sizeof(__pyx_k_sign), 0, 0, 1, 1},
  {&__pyx_n_s_source_ids, __pyx_k_source_ids, sizeof(__pyx_k_source_ids), 0, 0, 1, 1},
  {&__pyx_n_s_ssp, __pyx_k_ssp, sizeof(__pyx_k_ssp), 0, 0, 1, 1},
  {&__pyx_n_s_std, __pyx_k_std, sizeof(__pyx_k_std), 0, 0, 1, 1},
  {&__pyx_n_s_sum, __pyx_k_sum, sizeof(__pyx_k_sum), 0, 0, 1, 1},
  {&__pyx_n_s_sum_in, __pyx_k_sum_in, sizeof(__pyx_k_sum_in), 0, 0, 1, 1},
  {&__pyx_n_s_sum_out, __pyx_k_sum_out, sizeof(__pyx_k_sum_out), 0, 0, 1, 1},
  {&__pyx_n_s_target_ids, __pyx_k_target_ids, sizeof(__pyx_k_target_ids), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_tile, __pyx_k_tile, sizeof(__pyx_k_tile), 0, 0, 1, 1},
  {&__pyx_n_s_total, __pyx_k_total, sizeof(__pyx_k_total), 0, 0, 1, 1},
  {&__pyx_n_s_uint, __pyx_k_uint, sizeof(__pyx_k_uint), 0, 0, 1, 1},
  {&__pyx_n_s_unique, __pyx_k_unique, sizeof(__pyx_k_unique), 0, 0, 1, 1},
  {&__pyx_n_s_unique_rows, __pyx_k_unique_rows, sizeof(__pyx_k_unique_rows), 0, 0, 1, 1},
  {&__pyx_kp_u_unknown_dtype_code_in_numpy_pxd, __pyx_k_unknown_dtype_code_in_numpy_pxd, sizeof(__pyx_k_unknown_dtype_code_in_numpy_pxd), 0, 1, 0, 0},
  {&__pyx_n_s_view, __pyx_k_view, sizeof(__pyx_k_view), 0, 0, 1, 1},
  {&__pyx_n_s_void, __pyx_k_void, sizeof(__pyx_k_void), 0, 0, 1, 1},
  {&__pyx_n_s_warnings, __pyx_k_warnings, sizeof(__pyx_k_warnings), 0, 0, 1, 1},
  {&__pyx_n_s_x, __pyx_k_x, sizeof(__pyx_k_x), 0, 0, 1, 1},
  {&__pyx_n_s_y, __pyx_k_y, sizeof(__pyx_k_y), 0, 0, 1, 1},
  {&__pyx_n_s_zeros, __pyx_k_zeros, sizeof(__pyx_k_zeros), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_ValueError = __Pyx_GetBuiltinName(__pyx_n_s_ValueError); if (!__pyx_builtin_ValueError) __PYX_ERR(1, 218, __pyx_L1_error)
  __pyx_builtin_range = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_range) __PYX_ERR(1, 231, __pyx_L1_error)
  __pyx_builtin_RuntimeError = __Pyx_GetBuiltinName(__pyx_n_s_RuntimeError); if (!__pyx_builtin_RuntimeError) __PYX_ERR(1, 799, __pyx_L1_error)
  __pyx_builtin_ImportError = __Pyx_GetBuiltinName(__pyx_n_s_ImportError); if (!__pyx_builtin_ImportError) __PYX_ERR(1, 989, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "nngt/generation/cconnect.pyx":62
 * 
 * def _no_self_loops(array):
 *     return array[array[:,0] != array[:,1],:]             # <<<<<<<<<<<<<<
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,
 */
  __pyx_slice_ = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice_)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice_);
  __Pyx_GIVEREF(__pyx_slice_);
  __pyx_tuple__2 = PyTuple_Pack(2, __pyx_slice_, __pyx_int_0); if (unlikely(!__pyx_tuple__2)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__2);
  __Pyx_GIVEREF(__pyx_tuple__2);
  __pyx_slice__3 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__3)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__3);
  __Pyx_GIVEREF(__pyx_slice__3);
  __pyx_tuple__4 = PyTuple_Pack(2, __pyx_slice__3, __pyx_int_1); if (unlikely(!__pyx_tuple__4)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__4);
  __Pyx_GIVEREF(__pyx_tuple__4);
  __pyx_slice__5 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__5)) __PYX_ERR(0, 62, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__5);
  __Pyx_GIVEREF(__pyx_slice__5);

  /* "nngt/generation/cconnect.pyx":73
 *         ia_edges_tmp = _no_self_loops(ia_edges_tmp)
 *     num_added = ia_edges_tmp.shape[0]
 *     ia_edges[num_ecurrent:num_ecurrent+num_added,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *     num_ecurrent += num_added
 *     if not multigraph:
 */
  __pyx_slice__6 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__6)) __PYX_ERR(0, 73, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__6);
  __Pyx_GIVEREF(__pyx_slice__6);

  /* "nngt/generation/cconnect.pyx":76
 *     num_ecurrent += num_added
 *     if not multigraph:
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])             # <<<<<<<<<<<<<<
 *         num_ecurrent = ia_edges_tmp.shape[0]
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp
 */
  __pyx_slice__7 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__7)) __PYX_ERR(0, 76, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__7);
  __Pyx_GIVEREF(__pyx_slice__7);

  /* "nngt/generation/cconnect.pyx":78
 *         ia_edges_tmp = _unique_rows(ia_edges[:num_ecurrent,:])
 *         num_ecurrent = ia_edges_tmp.shape[0]
 *         ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *     return ia_edges, num_ecurrent
 * 
 */
  __pyx_slice__8 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__8)) __PYX_ERR(0, 78, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__8);
  __Pyx_GIVEREF(__pyx_slice__8);

  /* "nngt/generation/cconnect.pyx":108
 *             (existing+edges, 2), dtype=DTYPE)
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges             # <<<<<<<<<<<<<<
 *     cdef:
 *         unsigned int idx = 0 if b_out else 1 # differenciate source / target
 */
  __pyx_slice__9 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__9)) __PYX_ERR(0, 108, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__9);
  __Pyx_GIVEREF(__pyx_slice__9);

  /* "nngt/generation/cconnect.pyx":124
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__10 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__10)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__10);
  __Pyx_GIVEREF(__pyx_slice__10);
  __pyx_slice__11 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__11)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__11);
  __Pyx_GIVEREF(__pyx_slice__11);
  __pyx_tuple__12 = PyTuple_Pack(2, __pyx_slice__10, __pyx_slice__11); if (unlikely(!__pyx_tuple__12)) __PYX_ERR(0, 124, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__12);
  __Pyx_GIVEREF(__pyx_tuple__12);

  /* "nngt/generation/cconnect.pyx":163
 *             (existing + edges, 2), dtype=DTYPE)
 *     if existing:
 *         ia_edges[:existing,:] = existing_edges             # <<<<<<<<<<<<<<
 * 
 *     if b_out:
 */
  __pyx_slice__13 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__13)) __PYX_ERR(0, 163, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__13);
  __Pyx_GIVEREF(__pyx_slice__13);

  /* "nngt/generation/cconnect.pyx":172
 *             idx, multigraph, directed, msd, omp)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__14 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__14)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__14);
  __Pyx_GIVEREF(__pyx_slice__14);
  __pyx_slice__15 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__15)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__15);
  __Pyx_GIVEREF(__pyx_slice__15);
  __pyx_tuple__16 = PyTuple_Pack(2, __pyx_slice__14, __pyx_slice__15); if (unlikely(!__pyx_tuple__16)) __PYX_ERR(0, 172, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__16);
  __Pyx_GIVEREF(__pyx_tuple__16);

  /* "nngt/generation/cconnect.pyx":233
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]             # <<<<<<<<<<<<<<
 *             num_ecurrent = edges
 *             if not multigraph:
 */
  __pyx_slice__17 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__17)) __PYX_ERR(0, 233, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__17);
  __Pyx_GIVEREF(__pyx_slice__17);
  __pyx_slice__18 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__18)) __PYX_ERR(0, 233, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__18);
  __Pyx_GIVEREF(__pyx_slice__18);

  /* "nngt/generation/cconnect.pyx":238
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *             num_test += 1
 *     if not directed:
 */
  __pyx_slice__19 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__19)) __PYX_ERR(0, 238, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__19);
  __Pyx_GIVEREF(__pyx_slice__19);

  /* "nngt/generation/cconnect.pyx":241
 *             num_test += 1
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__20 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__20)) __PYX_ERR(0, 241, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__20);
  __Pyx_GIVEREF(__pyx_slice__20);
  __pyx_slice__21 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__21)) __PYX_ERR(0, 241, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__21);
  __Pyx_GIVEREF(__pyx_slice__21);
  __pyx_tuple__22 = PyTuple_Pack(2, __pyx_slice__20, __pyx_slice__21); if (unlikely(!__pyx_tuple__22)) __PYX_ERR(0, 241, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__22);
  __Pyx_GIVEREF(__pyx_tuple__22);

  /* "nngt/generation/cconnect.pyx":280
 *             ia_indices = randint(0, pre_recip_edges,
 *                                            edges-num_ecurrent)
 *             ia_edges[num_ecurrent:,:] = ia_edges[ia_indices,::-1]             # <<<<<<<<<<<<<<
 *             num_ecurrent = edges
 *             if not multigraph:
 */
  __pyx_slice__23 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__23)) __PYX_ERR(0, 280, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__23);
  __Pyx_GIVEREF(__pyx_slice__23);
  __pyx_slice__24 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__24)) __PYX_ERR(0, 280, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__24);
  __Pyx_GIVEREF(__pyx_slice__24);

  /* "nngt/generation/cconnect.pyx":285
 *                 ia_edges_tmp = _unique_rows(ia_edges)
 *                 num_ecurrent = ia_edges_tmp.shape[0]
 *                 ia_edges[:num_ecurrent,:] = ia_edges_tmp             # <<<<<<<<<<<<<<
 *             num_test += 1
 *     if not directed:
 */
  __pyx_slice__25 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__25)) __PYX_ERR(0, 285, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__25);
  __Pyx_GIVEREF(__pyx_slice__25);

  /* "nngt/generation/cconnect.pyx":288
 *             num_test += 1
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__26 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__26)) __PYX_ERR(0, 288, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__26);
  __Pyx_GIVEREF(__pyx_slice__26);
  __pyx_slice__27 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__27)) __PYX_ERR(0, 288, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__27);
  __Pyx_GIVEREF(__pyx_slice__27);
  __pyx_tuple__28 = PyTuple_Pack(2, __pyx_slice__26, __pyx_slice__27); if (unlikely(!__pyx_tuple__28)) __PYX_ERR(0, 288, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__28);
  __Pyx_GIVEREF(__pyx_tuple__28);

  /* "nngt/generation/cconnect.pyx":331
 *         source_ids, target_ids, num_edges, directed, multigraph)
 *     if not b_one_pop:
 *         raise InvalidArgument("This graph model can only be used if source \             # <<<<<<<<<<<<<<
 *                               and target populations are the same")
 *     # generate the initial circular graph
 */
  __pyx_tuple__29 = PyTuple_Pack(1, __pyx_kp_s_This_graph_model_can_only_be_use); if (unlikely(!__pyx_tuple__29)) __PYX_ERR(0, 331, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__29);
  __Pyx_GIVEREF(__pyx_tuple__29);

  /* "nngt/generation/cconnect.pyx":335
 *     # generate the initial circular graph
 *     ia_edges = np.zeros((num_edges,2),dtype=int)
 *     ia_edges[:circular_edges,:] = _circular_graph(node_ids, coord_nb)             # <<<<<<<<<<<<<<
 *     # add the random connections
 *     num_test, num_ecurrent = 0, circular_edges
 */
  __pyx_slice__30 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__30)) __PYX_ERR(0, 335, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__30);
  __Pyx_GIVEREF(__pyx_slice__30);

  /* "nngt/generation/cconnect.pyx":347
 *     ia_edges = _no_self_loops(ia_edges)
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__31 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__31)) __PYX_ERR(0, 347, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__31);
  __Pyx_GIVEREF(__pyx_slice__31);
  __pyx_slice__32 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__32)) __PYX_ERR(0, 347, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__32);
  __Pyx_GIVEREF(__pyx_slice__32);
  __pyx_tuple__33 = PyTuple_Pack(2, __pyx_slice__31, __pyx_slice__32); if (unlikely(!__pyx_tuple__33)) __PYX_ERR(0, 347, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__33);
  __Pyx_GIVEREF(__pyx_tuple__33);

  /* "nngt/generation/cconnect.pyx":391
 * 
 *     if not directed:
 *         ia_edges = np.concatenate((ia_edges, ia_edges[:,::-1]))             # <<<<<<<<<<<<<<
 *         ia_edges = _unique_rows(ia_edges)
 *     return ia_edges
 */
  __pyx_slice__34 = PySlice_New(Py_None, Py_None, Py_None); if (unlikely(!__pyx_slice__34)) __PYX_ERR(0, 391, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__34);
  __Pyx_GIVEREF(__pyx_slice__34);
  __pyx_slice__35 = PySlice_New(Py_None, Py_None, __pyx_int_neg_1); if (unlikely(!__pyx_slice__35)) __PYX_ERR(0, 391, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__35);
  __Pyx_GIVEREF(__pyx_slice__35);
  __pyx_tuple__36 = PyTuple_Pack(2, __pyx_slice__34, __pyx_slice__35); if (unlikely(!__pyx_tuple__36)) __PYX_ERR(0, 391, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__36);
  __Pyx_GIVEREF(__pyx_tuple__36);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":218
 *             if ((flags & pybuf.PyBUF_C_CONTIGUOUS == pybuf.PyBUF_C_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_C_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not C contiguous")             # <<<<<<<<<<<<<<
 * 
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)
 */
  __pyx_tuple__37 = PyTuple_Pack(1, __pyx_kp_u_ndarray_is_not_C_contiguous); if (unlikely(!__pyx_tuple__37)) __PYX_ERR(1, 218, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__37);
  __Pyx_GIVEREF(__pyx_tuple__37);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":222
 *             if ((flags & pybuf.PyBUF_F_CONTIGUOUS == pybuf.PyBUF_F_CONTIGUOUS)
 *                 and not PyArray_CHKFLAGS(self, NPY_F_CONTIGUOUS)):
 *                 raise ValueError(u"ndarray is not Fortran contiguous")             # <<<<<<<<<<<<<<
 * 
 *             info.buf = PyArray_DATA(self)
 */
  __pyx_tuple__38 = PyTuple_Pack(1, __pyx_kp_u_ndarray_is_not_Fortran_contiguou); if (unlikely(!__pyx_tuple__38)) __PYX_ERR(1, 222, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__38);
  __Pyx_GIVEREF(__pyx_tuple__38);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":259
 *                 if ((descr.byteorder == c'>' and little_endian) or
 *                     (descr.byteorder == c'<' and not little_endian)):
 *                     raise ValueError(u"Non-native byte order not supported")             # <<<<<<<<<<<<<<
 *                 if   t == NPY_BYTE:        f = "b"
 *                 elif t == NPY_UBYTE:       f = "B"
 */
  __pyx_tuple__39 = PyTuple_Pack(1, __pyx_kp_u_Non_native_byte_order_not_suppor); if (unlikely(!__pyx_tuple__39)) __PYX_ERR(1, 259, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__39);
  __Pyx_GIVEREF(__pyx_tuple__39);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":799
 * 
 *         if (end - f) - <int>(new_offset - offset[0]) < 15:
 *             raise RuntimeError(u"Format string allocated too short, see comment in numpy.pxd")             # <<<<<<<<<<<<<<
 * 
 *         if ((child.byteorder == c'>' and little_endian) or
 */
  __pyx_tuple__40 = PyTuple_Pack(1, __pyx_kp_u_Format_string_allocated_too_shor); if (unlikely(!__pyx_tuple__40)) __PYX_ERR(1, 799, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__40);
  __Pyx_GIVEREF(__pyx_tuple__40);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":803
 *         if ((child.byteorder == c'>' and little_endian) or
 *             (child.byteorder == c'<' and not little_endian)):
 *             raise ValueError(u"Non-native byte order not supported")             # <<<<<<<<<<<<<<
 *             # One could encode it in the format string and have Cython
 *             # complain instead, BUT: < and > in format strings also imply
 */
  __pyx_tuple__41 = PyTuple_Pack(1, __pyx_kp_u_Non_native_byte_order_not_suppor); if (unlikely(!__pyx_tuple__41)) __PYX_ERR(1, 803, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__41);
  __Pyx_GIVEREF(__pyx_tuple__41);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":823
 *             t = child.type_num
 *             if end - f < 5:
 *                 raise RuntimeError(u"Format string allocated too short.")             # <<<<<<<<<<<<<<
 * 
 *             # Until ticket #99 is fixed, use integers to avoid warnings
 */
  __pyx_tuple__42 = PyTuple_Pack(1, __pyx_kp_u_Format_string_allocated_too_shor_2); if (unlikely(!__pyx_tuple__42)) __PYX_ERR(1, 823, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__42);
  __Pyx_GIVEREF(__pyx_tuple__42);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":989
 *         _import_array()
 *     except Exception:
 *         raise ImportError("numpy.core.multiarray failed to import")             # <<<<<<<<<<<<<<
 * 
 * cdef inline int import_umath() except -1:
 */
  __pyx_tuple__43 = PyTuple_Pack(1, __pyx_kp_s_numpy_core_multiarray_failed_to); if (unlikely(!__pyx_tuple__43)) __PYX_ERR(1, 989, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__43);
  __Pyx_GIVEREF(__pyx_tuple__43);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":995
 *         _import_umath()
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")             # <<<<<<<<<<<<<<
 * 
 * cdef inline int import_ufunc() except -1:
 */
  __pyx_tuple__44 = PyTuple_Pack(1, __pyx_kp_s_numpy_core_umath_failed_to_impor); if (unlikely(!__pyx_tuple__44)) __PYX_ERR(1, 995, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__44);
  __Pyx_GIVEREF(__pyx_tuple__44);

  /* "../../../../usr/lib/python3.6/site-packages/Cython/Includes/numpy/__init__.pxd":1001
 *         _import_umath()
 *     except Exception:
 *         raise ImportError("numpy.core.umath failed to import")             # <<<<<<<<<<<<<<
 */
  __pyx_tuple__45 = PyTuple_Pack(1, __pyx_kp_s_numpy_core_umath_failed_to_impor); if (unlikely(!__pyx_tuple__45)) __PYX_ERR(1, 1001, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__45);
  __Pyx_GIVEREF(__pyx_tuple__45);

  /* "nngt/generation/cconnect.pyx":56
 *     return string
 * 
 * def _unique_rows(arr):             # <<<<<<<<<<<<<<
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))
 */
  __pyx_tuple__47 = PyTuple_Pack(2, __pyx_n_s_arr, __pyx_n_s_b); if (unlikely(!__pyx_tuple__47)) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__47);
  __Pyx_GIVEREF(__pyx_tuple__47);
  __pyx_codeobj__48 = (PyObject*)__Pyx_PyCode_New(1, 0, 2, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__47, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_unique_rows, 56, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__48)) __PYX_ERR(0, 56, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":61
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 * 
 * def _no_self_loops(array):             # <<<<<<<<<<<<<<
 *     return array[array[:,0] != array[:,1],:]
 * 
 */
  __pyx_tuple__49 = PyTuple_Pack(1, __pyx_n_s_array); if (unlikely(!__pyx_tuple__49)) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__49);
  __Pyx_GIVEREF(__pyx_tuple__49);
  __pyx_codeobj__50 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__49, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_no_self_loops, 61, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__50)) __PYX_ERR(0, 61, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":64
 *     return array[array[:,0] != array[:,1],:]
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,             # <<<<<<<<<<<<<<
 *                             multigraph):
 *     '''
 */
  __pyx_tuple__51 = PyTuple_Pack(6, __pyx_n_s_ia_edges, __pyx_n_s_ia_edges_tmp, __pyx_n_s_num_ecurrent, __pyx_n_s_b_one_pop, __pyx_n_s_multigraph, __pyx_n_s_num_added); if (unlikely(!__pyx_tuple__51)) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__51);
  __Pyx_GIVEREF(__pyx_tuple__51);
  __pyx_codeobj__52 = (PyObject*)__Pyx_PyCode_New(5, 0, 6, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__51, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_filter, 64, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__52)) __PYX_ERR(0, 64, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":87
 * #
 * 
 * def _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 */
  __pyx_tuple__53 = PyTuple_Pack(22, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_degree, __pyx_n_s_degree_type, __pyx_n_s_reciprocity, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_existing_edges, __pyx_n_s_b_out, __pyx_n_s_b_total, __pyx_n_s_num_source, __pyx_n_s_num_target, __pyx_n_s_edges, __pyx_n_s_b_one_pop, __pyx_n_s_existing, __pyx_n_s_ia_edges, __pyx_n_s_idx, __pyx_n_s_omp, __pyx_n_s_num_node, __pyx_n_s_msd, __pyx_n_s_degrees, __pyx_n_s_old_edges); if (unlikely(!__pyx_tuple__53)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__53);
  __Pyx_GIVEREF(__pyx_tuple__53);
  __pyx_codeobj__54 = (PyObject*)__Pyx_PyCode_New(8, 0, 22, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__53, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_fixed_degree, 87, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__54)) __PYX_ERR(0, 87, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":129
 * 
 * 
 * def _gaussian_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 */
  __pyx_tuple__55 = PyTuple_Pack(23, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_avg, __pyx_n_s_std, __pyx_n_s_degree_type, __pyx_n_s_reciprocity, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_existing_edges, __pyx_n_s_b_out, __pyx_n_s_b_total, __pyx_n_s_num_source, __pyx_n_s_num_target, __pyx_n_s_idx, __pyx_n_s_omp, __pyx_n_s_num_node, __pyx_n_s_degrees, __pyx_n_s_old_edges, __pyx_n_s_edges, __pyx_n_s_b_one_pop, __pyx_n_s_msd, __pyx_n_s_existing, __pyx_n_s_ia_edges); if (unlikely(!__pyx_tuple__55)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__55);
  __Pyx_GIVEREF(__pyx_tuple__55);
  __pyx_codeobj__56 = (PyObject*)__Pyx_PyCode_New(9, 0, 23, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__55, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_gaussian_degree, 129, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__56)) __PYX_ERR(0, 129, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":177
 * 
 * 
 * def _random_scale_free(source_ids, target_ids, in_exp, out_exp, density,             # <<<<<<<<<<<<<<
 *                        edges, avg_deg, reciprocity, directed, multigraph,
 *                        **kwargs):
 */
  __pyx_tuple__57 = PyTuple_Pack(33, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_in_exp, __pyx_n_s_out_exp, __pyx_n_s_density, __pyx_n_s_edges, __pyx_n_s_avg_deg, __pyx_n_s_reciprocity, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_kwargs, __pyx_n_s_num_source, __pyx_n_s_num_target, __pyx_n_s_pre_recip_edges, __pyx_n_s_b_one_pop, __pyx_n_s_ia_edges, __pyx_n_s_num_ecurrent, __pyx_n_s_num_test, __pyx_n_s_ia_in_deg, __pyx_n_s_ia_out_deg, __pyx_n_s_sum_in, __pyx_n_s_sum_out, __pyx_n_s_diff_in, __pyx_n_s_diff_out, __pyx_n_s_idx_correct_in, __pyx_n_s_idx_correct_out, __pyx_n_s_ia_sources, __pyx_n_s_ia_targets, __pyx_n_s_ia_edges_tmp, __pyx_n_s_num_desired, __pyx_n_s_ia_sources_tmp, __pyx_n_s_ia_targets_tmp, __pyx_n_s_ia_indices); if (unlikely(!__pyx_tuple__57)) __PYX_ERR(0, 177, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__57);
  __Pyx_GIVEREF(__pyx_tuple__57);
  __pyx_codeobj__58 = (PyObject*)__Pyx_PyCode_New(10, 0, 33, 0, CO_VARKEYWORDS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__57, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_random_scale_free, 177, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__58)) __PYX_ERR(0, 177, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":246
 * 
 * 
 * def _erdos_renyi(source_ids, target_ids, density, edges, avg_deg, reciprocity,             # <<<<<<<<<<<<<<
 *                  directed, multigraph, **kwargs):
 *     '''
 */
  __pyx_tuple__59 = PyTuple_Pack(20, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_density, __pyx_n_s_edges, __pyx_n_s_avg_deg, __pyx_n_s_reciprocity, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_kwargs, __pyx_n_s_num_source, __pyx_n_s_num_target, __pyx_n_s_pre_recip_edges, __pyx_n_s_b_one_pop, __pyx_n_s_ia_edges, __pyx_n_s_num_test, __pyx_n_s_num_ecurrent, __pyx_n_s_ia_sources, __pyx_n_s_ia_targets, __pyx_n_s_ia_edges_tmp, __pyx_n_s_ia_indices); if (unlikely(!__pyx_tuple__59)) __PYX_ERR(0, 246, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__59);
  __Pyx_GIVEREF(__pyx_tuple__59);
  __pyx_codeobj__60 = (PyObject*)__Pyx_PyCode_New(8, 0, 20, 0, CO_VARKEYWORDS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__59, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_erdos_renyi, 246, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__60)) __PYX_ERR(0, 246, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":293
 * 
 * 
 * def _price_scale_free():             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
  __pyx_codeobj__61 = (PyObject*)__Pyx_PyCode_New(0, 0, 0, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_price_scale_free, 293, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__61)) __PYX_ERR(0, 293, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":297
 * 
 * 
 * def _circular_graph(node_ids, coord_nb):             # <<<<<<<<<<<<<<
 *     '''
 *     Connect every node `i` to its `coord_nb` nearest neighbours on a circle
 */
  __pyx_tuple__62 = PyTuple_Pack(9, __pyx_n_s_node_ids, __pyx_n_s_coord_nb, __pyx_n_s_nodes, __pyx_n_s_ia_sources, __pyx_n_s_ia_targets, __pyx_n_s_dist, __pyx_n_s_neg_dist, __pyx_n_s_pos_dist, __pyx_n_s_ia_base); if (unlikely(!__pyx_tuple__62)) __PYX_ERR(0, 297, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__62);
  __Pyx_GIVEREF(__pyx_tuple__62);
  __pyx_codeobj__63 = (PyObject*)__Pyx_PyCode_New(2, 0, 9, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__62, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_circular_graph, 297, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__63)) __PYX_ERR(0, 297, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":313
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 * 
 * def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,             # <<<<<<<<<<<<<<
 *                   directed, multigraph, **kwargs):
 *     '''
 */
  __pyx_tuple__64 = PyTuple_Pack(18, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_coord_nb, __pyx_n_s_proba_shortcut, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_kwargs, __pyx_n_s_node_ids, __pyx_n_s_nodes, __pyx_n_s_circular_edges, __pyx_n_s_num_edges, __pyx_n_s_b_one_pop, __pyx_n_s_ia_edges, __pyx_n_s_num_test, __pyx_n_s_num_ecurrent, __pyx_n_s_ia_sources, __pyx_n_s_ia_targets, __pyx_n_s_ia_edges_tmp); if (unlikely(!__pyx_tuple__64)) __PYX_ERR(0, 313, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__64);
  __Pyx_GIVEREF(__pyx_tuple__64);
  __pyx_codeobj__65 = (PyObject*)__Pyx_PyCode_New(6, 0, 18, 0, CO_VARKEYWORDS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__64, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_newman_watts, 313, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__65)) __PYX_ERR(0, 313, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":352
 * 
 * 
 * def _distance_rule(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                    np.ndarray[size_t, ndim=1] target_ids,
 *                    density, edges, avg_deg, double scale,
 */
  __pyx_tuple__67 = PyTuple_Pack(28, __pyx_n_s_source_ids, __pyx_n_s_target_ids, __pyx_n_s_density, __pyx_n_s_edges, __pyx_n_s_avg_deg, __pyx_n_s_scale, __pyx_n_s_rule, __pyx_n_s_shape, __pyx_n_s_positions, __pyx_n_s_directed, __pyx_n_s_multigraph, __pyx_n_s_num_neurons, __pyx_n_s_kwargs, __pyx_n_s_cnum_neurons, __pyx_n_s_num_source, __pyx_n_s_num_target, __pyx_n_s_crule, __pyx_n_s_omp, __pyx_n_s_old_edges, __pyx_n_s_x, __pyx_n_s_y, __pyx_n_s_edge_num, __pyx_n_s__66, __pyx_n_s_existing, __pyx_n_s_msd, __pyx_n_s_area, __pyx_n_s_cedges, __pyx_n_s_ia_edges); if (unlikely(!__pyx_tuple__67)) __PYX_ERR(0, 352, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__67);
  __Pyx_GIVEREF(__pyx_tuple__67);
  __pyx_codeobj__68 = (PyObject*)__Pyx_PyCode_New(12, 0, 28, 0, CO_VARKEYWORDS, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__67, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_distance_rule, 352, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__68)) __PYX_ERR(0, 352, __pyx_L1_error)

  /* "nngt/generation/cconnect.pyx":395
 *     return ia_edges
 * 
 * def price_network():             # <<<<<<<<<<<<<<
 *     #@todo: do it for other libraries
 *     pass
 */
  __pyx_codeobj__69 = (PyObject*)__Pyx_PyCode_New(0, 0, 0, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_home_tfardet_Documents_NNGT_nng, __pyx_n_s_price_network, 395, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__69)) __PYX_ERR(0, 395, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  /* InitThreads.init */
  #ifdef WITH_THREAD
PyEval_InitThreads();
#endif

if (unlikely(PyErr_Occurred())) __PYX_ERR(0, 1, __pyx_L1_error)

  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  __pyx_float_0_ = PyFloat_FromDouble(0.); if (unlikely(!__pyx_float_0_)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_2_ = PyFloat_FromDouble(2.); if (unlikely(!__pyx_float_2_)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_5 = PyFloat_FromDouble(0.5); if (unlikely(!__pyx_float_0_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_neg_0_5 = PyFloat_FromDouble(-0.5); if (unlikely(!__pyx_float_neg_0_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_1 = PyInt_FromLong(-1); if (unlikely(!__pyx_int_neg_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initcconnect(void); /*proto*/
PyMODINIT_FUNC initcconnect(void)
#else
PyMODINIT_FUNC PyInit_cconnect(void); /*proto*/
PyMODINIT_FUNC PyInit_cconnect(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_cconnect(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(0, 1, __pyx_L1_error)
  #ifdef __Pyx_CyFunction_USED
  if (__pyx_CyFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Coroutine_USED
  if (__pyx_Coroutine_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("cconnect", __pyx_methods, __pyx_k_Generation_tools_for_NNGT, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) __PYX_ERR(0, 1, __pyx_L1_error)
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  /*--- Initialize various global constants etc. ---*/
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  if (__pyx_module_is_main_nngt__generation__cconnect) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "nngt.generation.cconnect")) {
      if (unlikely(PyDict_SetItemString(modules, "nngt.generation.cconnect", __pyx_m) < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Constants init code ---*/
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  /*--- Type import code ---*/
  __pyx_ptype_7cpython_4type_type = __Pyx_ImportType(__Pyx_BUILTIN_MODULE_NAME, "type", 
  #if CYTHON_COMPILING_IN_PYPY
  sizeof(PyTypeObject),
  #else
  sizeof(PyHeapTypeObject),
  #endif
  0); if (unlikely(!__pyx_ptype_7cpython_4type_type)) __PYX_ERR(3, 9, __pyx_L1_error)
  __pyx_ptype_5numpy_dtype = __Pyx_ImportType("numpy", "dtype", sizeof(PyArray_Descr), 0); if (unlikely(!__pyx_ptype_5numpy_dtype)) __PYX_ERR(1, 155, __pyx_L1_error)
  __pyx_ptype_5numpy_flatiter = __Pyx_ImportType("numpy", "flatiter", sizeof(PyArrayIterObject), 0); if (unlikely(!__pyx_ptype_5numpy_flatiter)) __PYX_ERR(1, 168, __pyx_L1_error)
  __pyx_ptype_5numpy_broadcast = __Pyx_ImportType("numpy", "broadcast", sizeof(PyArrayMultiIterObject), 0); if (unlikely(!__pyx_ptype_5numpy_broadcast)) __PYX_ERR(1, 172, __pyx_L1_error)
  __pyx_ptype_5numpy_ndarray = __Pyx_ImportType("numpy", "ndarray", sizeof(PyArrayObject), 0); if (unlikely(!__pyx_ptype_5numpy_ndarray)) __PYX_ERR(1, 181, __pyx_L1_error)
  __pyx_ptype_5numpy_ufunc = __Pyx_ImportType("numpy", "ufunc", sizeof(PyUFuncObject), 0); if (unlikely(!__pyx_ptype_5numpy_ufunc)) __PYX_ERR(1, 861, __pyx_L1_error)
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/
  #if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif

  /* "nngt/generation/cconnect.pyx":7
 * """ Generation tools for NNGT """
 * 
 * import warnings             # <<<<<<<<<<<<<<
 * 
 * from cython.parallel import parallel, prange
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_warnings, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_warnings, __pyx_t_1) < 0) __PYX_ERR(0, 7, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":13
 * cimport numpy as np
 * 
 * import numpy as np             # <<<<<<<<<<<<<<
 * import scipy.sparse as ssp
 * from numpy.random import randint
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_np, __pyx_t_1) < 0) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":14
 * 
 * import numpy as np
 * import scipy.sparse as ssp             # <<<<<<<<<<<<<<
 * from numpy.random import randint
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s__46);
  __Pyx_GIVEREF(__pyx_n_s__46);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s__46);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_scipy_sparse, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_ssp, __pyx_t_2) < 0) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":15
 * import numpy as np
 * import scipy.sparse as ssp
 * from numpy.random import randint             # <<<<<<<<<<<<<<
 * 
 * import nngt
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_randint);
  __Pyx_GIVEREF(__pyx_n_s_randint);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_randint);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_numpy_random, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_randint); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_randint, __pyx_t_2) < 0) __PYX_ERR(0, 15, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":17
 * from numpy.random import randint
 * 
 * import nngt             # <<<<<<<<<<<<<<
 * from nngt.lib import InvalidArgument
 * from .connect_tools import *
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_nngt, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 17, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_nngt, __pyx_t_1) < 0) __PYX_ERR(0, 17, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":18
 * 
 * import nngt
 * from nngt.lib import InvalidArgument             # <<<<<<<<<<<<<<
 * from .connect_tools import *
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_InvalidArgument);
  __Pyx_GIVEREF(__pyx_n_s_InvalidArgument);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_InvalidArgument);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_nngt_lib, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_InvalidArgument); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_InvalidArgument, __pyx_t_1) < 0) __PYX_ERR(0, 18, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":19
 * import nngt
 * from nngt.lib import InvalidArgument
 * from .connect_tools import *             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s__46);
  __Pyx_GIVEREF(__pyx_n_s__46);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s__46);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_connect_tools, __pyx_t_2, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_import_star(__pyx_t_1) < 0) __PYX_ERR(0, 19, __pyx_L1_error);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":22
 * 
 * 
 * __all__ = [             # <<<<<<<<<<<<<<
 *     "_distance_rule",
 *     "_erdos_renyi",
 */
  __pyx_t_1 = PyList_New(10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 22, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_distance_rule);
  __Pyx_GIVEREF(__pyx_n_s_distance_rule);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_distance_rule);
  __Pyx_INCREF(__pyx_n_s_erdos_renyi);
  __Pyx_GIVEREF(__pyx_n_s_erdos_renyi);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_erdos_renyi);
  __Pyx_INCREF(__pyx_n_s_filter);
  __Pyx_GIVEREF(__pyx_n_s_filter);
  PyList_SET_ITEM(__pyx_t_1, 2, __pyx_n_s_filter);
  __Pyx_INCREF(__pyx_n_s_fixed_degree);
  __Pyx_GIVEREF(__pyx_n_s_fixed_degree);
  PyList_SET_ITEM(__pyx_t_1, 3, __pyx_n_s_fixed_degree);
  __Pyx_INCREF(__pyx_n_s_gaussian_degree);
  __Pyx_GIVEREF(__pyx_n_s_gaussian_degree);
  PyList_SET_ITEM(__pyx_t_1, 4, __pyx_n_s_gaussian_degree);
  __Pyx_INCREF(__pyx_n_s_newman_watts);
  __Pyx_GIVEREF(__pyx_n_s_newman_watts);
  PyList_SET_ITEM(__pyx_t_1, 5, __pyx_n_s_newman_watts);
  __Pyx_INCREF(__pyx_n_s_no_self_loops);
  __Pyx_GIVEREF(__pyx_n_s_no_self_loops);
  PyList_SET_ITEM(__pyx_t_1, 6, __pyx_n_s_no_self_loops);
  __Pyx_INCREF(__pyx_n_s_price_scale_free);
  __Pyx_GIVEREF(__pyx_n_s_price_scale_free);
  PyList_SET_ITEM(__pyx_t_1, 7, __pyx_n_s_price_scale_free);
  __Pyx_INCREF(__pyx_n_s_random_scale_free);
  __Pyx_GIVEREF(__pyx_n_s_random_scale_free);
  PyList_SET_ITEM(__pyx_t_1, 8, __pyx_n_s_random_scale_free);
  __Pyx_INCREF(__pyx_n_s_unique_rows);
  __Pyx_GIVEREF(__pyx_n_s_unique_rows);
  PyList_SET_ITEM(__pyx_t_1, 9, __pyx_n_s_unique_rows);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_all, __pyx_t_1) < 0) __PYX_ERR(0, 22, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "nngt/generation/cconnect.pyx":36
 * 
 * 
 * cdef int MAXTESTS = 1000 # ensure that generation will finish             # <<<<<<<<<<<<<<
 * cdef float EPS = 0.00001
 * 
 */
  __pyx_v_4nngt_10generation_8cconnect_MAXTESTS = 0x3E8;

  /* "nngt/generation/cconnect.pyx":37
 * 
 * cdef int MAXTESTS = 1000 # ensure that generation will finish
 * cdef float EPS = 0.00001             # <<<<<<<<<<<<<<
 * 
 * # We now need to fix a datatype for our arrays. I've used the variable
 */
  __pyx_v_4nngt_10generation_8cconnect_EPS = 0.00001;

  /* "nngt/generation/cconnect.pyx":42
 * # DTYPE for this, which is assigned to the usual NumPy runtime
 * # type info object.
 * DTYPE = np.uint             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_np); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_uint); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_DTYPE, __pyx_t_2) < 0) __PYX_ERR(0, 42, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":56
 *     return string
 * 
 * def _unique_rows(arr):             # <<<<<<<<<<<<<<
 *     b = np.ascontiguousarray(arr).view(np.dtype((np.void,
 *         arr.dtype.itemsize * arr.shape[1])))
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_1_unique_rows, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_unique_rows, __pyx_t_2) < 0) __PYX_ERR(0, 56, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":61
 *     return np.unique(b).view(arr.dtype).reshape(-1,arr.shape[1])
 * 
 * def _no_self_loops(array):             # <<<<<<<<<<<<<<
 *     return array[array[:,0] != array[:,1],:]
 * 
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_3_no_self_loops, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_no_self_loops, __pyx_t_2) < 0) __PYX_ERR(0, 61, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":64
 *     return array[array[:,0] != array[:,1],:]
 * 
 * def _filter(ia_edges, ia_edges_tmp, num_ecurrent, b_one_pop,             # <<<<<<<<<<<<<<
 *                             multigraph):
 *     '''
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_5_filter, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_filter, __pyx_t_2) < 0) __PYX_ERR(0, 64, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":87
 * #
 * 
 * def _fixed_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                   np.ndarray[size_t, ndim=1] target_ids, size_t degree,
 *                   degree_type, float reciprocity, bool directed,
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_7_fixed_degree, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_fixed_degree, __pyx_t_2) < 0) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":129
 * 
 * 
 * def _gaussian_degree(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                      np.ndarray[size_t, ndim=1] target_ids, unsigned int avg,
 *                      unsigned int std, degree_type, float reciprocity,
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_9_gaussian_degree, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_gaussian_degree, __pyx_t_2) < 0) __PYX_ERR(0, 129, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":177
 * 
 * 
 * def _random_scale_free(source_ids, target_ids, in_exp, out_exp, density,             # <<<<<<<<<<<<<<
 *                        edges, avg_deg, reciprocity, directed, multigraph,
 *                        **kwargs):
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_11_random_scale_free, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 177, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_random_scale_free, __pyx_t_2) < 0) __PYX_ERR(0, 177, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":246
 * 
 * 
 * def _erdos_renyi(source_ids, target_ids, density, edges, avg_deg, reciprocity,             # <<<<<<<<<<<<<<
 *                  directed, multigraph, **kwargs):
 *     '''
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_13_erdos_renyi, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 246, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_erdos_renyi, __pyx_t_2) < 0) __PYX_ERR(0, 246, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":293
 * 
 * 
 * def _price_scale_free():             # <<<<<<<<<<<<<<
 *     pass
 * 
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_15_price_scale_free, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 293, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_price_scale_free, __pyx_t_2) < 0) __PYX_ERR(0, 293, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":297
 * 
 * 
 * def _circular_graph(node_ids, coord_nb):             # <<<<<<<<<<<<<<
 *     '''
 *     Connect every node `i` to its `coord_nb` nearest neighbours on a circle
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_17_circular_graph, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 297, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_circular_graph, __pyx_t_2) < 0) __PYX_ERR(0, 297, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":313
 *     return np.array([node_ids[ia_sources], node_ids[ia_targets]]).astype(int).T
 * 
 * def _newman_watts(source_ids, target_ids, coord_nb, proba_shortcut,             # <<<<<<<<<<<<<<
 *                   directed, multigraph, **kwargs):
 *     '''
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_19_newman_watts, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 313, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_newman_watts, __pyx_t_2) < 0) __PYX_ERR(0, 313, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":352
 * 
 * 
 * def _distance_rule(np.ndarray[size_t, ndim=1] source_ids,             # <<<<<<<<<<<<<<
 *                    np.ndarray[size_t, ndim=1] target_ids,
 *                    density, edges, avg_deg, double scale,
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_21_distance_rule, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 352, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_distance_rule, __pyx_t_2) < 0) __PYX_ERR(0, 352, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":395
 *     return ia_edges
 * 
 * def price_network():             # <<<<<<<<<<<<<<
 *     #@todo: do it for other libraries
 *     pass
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_4nngt_10generation_8cconnect_23price_network, NULL, __pyx_n_s_nngt_generation_cconnect); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 395, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_price_network, __pyx_t_2) < 0) __PYX_ERR(0, 395, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "nngt/generation/cconnect.pyx":1
 * #cython: boundscheck=False, wraparound=False, initializedcheck=False, cdivision=True             # <<<<<<<<<<<<<<
 * #!/usr/bin/env cython
 * #-*- coding:utf-8 -*-
 */
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_2) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "vector.from_py":49
 * 
 * @cname("__pyx_convert_vector_from_py_double")
 * cdef vector[X] __pyx_convert_vector_from_py_double(object o) except *:             # <<<<<<<<<<<<<<
 *     cdef vector[X] v
 *     for item in o:
 */

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init nngt.generation.cconnect", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init nngt.generation.cconnect");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* --- Runtime support code --- */
/* Refnanny */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

/* PyObjectCall */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* GetBuiltinName */
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

/* GetModuleGlobalName */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if !CYTHON_AVOID_BORROWED_REFS
    result = PyDict_GetItem(__pyx_d, name);
    if (likely(result)) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

/* PyCFunctionFastCall */
  #if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject * __Pyx_PyCFunction_FastCall(PyObject *func_obj, PyObject **args, Py_ssize_t nargs) {
    PyCFunctionObject *func = (PyCFunctionObject*)func_obj;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    assert(PyCFunction_Check(func));
    assert(METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)));
    assert(nargs >= 0);
    assert(nargs == 0 || args != NULL);
    /* _PyCFunction_FastCallDict() must not be called with an exception set,
       because it may clear it (directly or indirectly) and so the
       caller loses its exception */
    assert(!PyErr_Occurred());
    return (*((__Pyx_PyCFunctionFast)meth)) (self, args, nargs, NULL);
}
#endif  // CYTHON_FAST_PYCCALL

/* PyFunctionFastCall */
  #if CYTHON_FAST_PYCALL
#include "frameobject.h"
static PyObject* __Pyx_PyFunction_FastCallNoKw(PyCodeObject *co, PyObject **args, Py_ssize_t na,
                                               PyObject *globals) {
    PyFrameObject *f;
    PyThreadState *tstate = PyThreadState_GET();
    PyObject **fastlocals;
    Py_ssize_t i;
    PyObject *result;
    assert(globals != NULL);
    /* XXX Perhaps we should create a specialized
       PyFrame_New() that doesn't take locals, but does
       take builtins without sanity checking them.
       */
    assert(tstate != NULL);
    f = PyFrame_New(tstate, co, globals, NULL);
    if (f == NULL) {
        return NULL;
    }
    fastlocals = f->f_localsplus;
    for (i = 0; i < na; i++) {
        Py_INCREF(*args);
        fastlocals[i] = *args++;
    }
    result = PyEval_EvalFrameEx(f,0);
    ++tstate->recursion_depth;
    Py_DECREF(f);
    --tstate->recursion_depth;
    return result;
}
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, int nargs, PyObject *kwargs) {
    PyCodeObject *co = (PyCodeObject *)PyFunction_GET_CODE(func);
    PyObject *globals = PyFunction_GET_GLOBALS(func);
    PyObject *argdefs = PyFunction_GET_DEFAULTS(func);
    PyObject *closure;
#if PY_MAJOR_VERSION >= 3
    PyObject *kwdefs;
#endif
    PyObject *kwtuple, **k;
    PyObject **d;
    Py_ssize_t nd;
    Py_ssize_t nk;
    PyObject *result;
    assert(kwargs == NULL || PyDict_Check(kwargs));
    nk = kwargs ? PyDict_Size(kwargs) : 0;
    if (Py_EnterRecursiveCall((char*)" while calling a Python object")) {
        return NULL;
    }
    if (
#if PY_MAJOR_VERSION >= 3
            co->co_kwonlyargcount == 0 &&
#endif
            likely(kwargs == NULL || nk == 0) &&
            co->co_flags == (CO_OPTIMIZED | CO_NEWLOCALS | CO_NOFREE)) {
        if (argdefs == NULL && co->co_argcount == nargs) {
            result = __Pyx_PyFunction_FastCallNoKw(co, args, nargs, globals);
            goto done;
        }
        else if (nargs == 0 && argdefs != NULL
                 && co->co_argcount == Py_SIZE(argdefs)) {
            /* function called with no arguments, but all parameters have
               a default value: use default values as arguments .*/
            args = &PyTuple_GET_ITEM(argdefs, 0);
            result =__Pyx_PyFunction_FastCallNoKw(co, args, Py_SIZE(argdefs), globals);
            goto done;
        }
    }
    if (kwargs != NULL) {
        Py_ssize_t pos, i;
        kwtuple = PyTuple_New(2 * nk);
        if (kwtuple == NULL) {
            result = NULL;
            goto done;
        }
        k = &PyTuple_GET_ITEM(kwtuple, 0);
        pos = i = 0;
        while (PyDict_Next(kwargs, &pos, &k[i], &k[i+1])) {
            Py_INCREF(k[i]);
            Py_INCREF(k[i+1]);
            i += 2;
        }
        nk = i / 2;
    }
    else {
        kwtuple = NULL;
        k = NULL;
    }
    closure = PyFunction_GET_CLOSURE(func);
#if PY_MAJOR_VERSION >= 3
    kwdefs = PyFunction_GET_KW_DEFAULTS(func);
#endif
    if (argdefs != NULL) {
        d = &PyTuple_GET_ITEM(argdefs, 0);
        nd = Py_SIZE(argdefs);
    }
    else {
        d = NULL;
        nd = 0;
    }
#if PY_MAJOR_VERSION >= 3
    result = PyEval_EvalCodeEx((PyObject*)co, globals, (PyObject *)NULL,
                               args, nargs,
                               k, (int)nk,
                               d, (int)nd, kwdefs, closure);
#else
    result = PyEval_EvalCodeEx(co, globals, (PyObject *)NULL,
                               args, nargs,
                               k, (int)nk,
                               d, (int)nd, closure);
#endif
    Py_XDECREF(kwtuple);
done:
    Py_LeaveRecursiveCall();
    return result;
}
#endif  // CPython < 3.6
#endif  // CYTHON_FAST_PYCALL

/* PyObjectCallMethO */
  #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallOneArg */
  #if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, &arg, 1);
    }
#endif
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
#if CYTHON_FAST_PYCCALL
        } else if (PyCFunction_GET_FLAGS(func) & METH_FASTCALL) {
            return __Pyx_PyCFunction_FastCall(func, &arg, 1);
#endif
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_Pack(1, arg);
    if (unlikely(!args)) return NULL;
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
#endif

/* GetItemInt */
    static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (wraparound & unlikely(i < 0)) i += PyList_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (wraparound & unlikely(i < 0)) i += PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i, int is_list,
                                                     CYTHON_NCP_UNUSED int wraparound,
                                                     CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS && CYTHON_USE_TYPE_SLOTS
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                        return NULL;
                    PyErr_Clear();
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

/* RaiseArgTupleInvalid */
    static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%.200s() takes %.8s %" CYTHON_FORMAT_SSIZE_T "d positional argument%.1s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

/* RaiseDoubleKeywords */
    static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

/* ParseKeywords */
    static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (PyUnicode_GET_SIZE(**argname) != PyUnicode_GET_SIZE(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%.200s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%.200s() got an unexpected keyword argument '%.200s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

/* ArgTypeTest */
    static void __Pyx_RaiseArgumentTypeInvalid(const char* name, PyObject *obj, PyTypeObject *type) {
    PyErr_Format(PyExc_TypeError,
        "Argument '%.200s' has incorrect type (expected %.200s, got %.200s)",
        name, type->tp_name, Py_TYPE(obj)->tp_name);
}
static CYTHON_INLINE int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact)
{
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (none_allowed && obj == Py_None) return 1;
    else if (exact) {
        if (likely(Py_TYPE(obj) == type)) return 1;
        #if PY_MAJOR_VERSION == 2
        else if ((type == &PyBaseString_Type) && likely(__Pyx_PyBaseString_CheckExact(obj))) return 1;
        #endif
    }
    else {
        if (likely(PyObject_TypeCheck(obj, type))) return 1;
    }
    __Pyx_RaiseArgumentTypeInvalid(name, obj, type);
    return 0;
}

/* BufferFormatCheck */
    static CYTHON_INLINE int __Pyx_IsLittleEndian(void) {
  unsigned int n = 1;
  return *(unsigned char*)(&n) != 0;
}
static void __Pyx_BufFmt_Init(__Pyx_BufFmt_Context* ctx,
                              __Pyx_BufFmt_StackElem* stack,
                              __Pyx_TypeInfo* type) {
  stack[0].field = &ctx->root;
  stack[0].parent_offset = 0;
  ctx->root.type = type;
  ctx->root.name = "buffer dtype";
  ctx->root.offset = 0;
  ctx->head = stack;
  ctx->head->field = &ctx->root;
  ctx->fmt_offset = 0;
  ctx->head->parent_offset = 0;
  ctx->new_packmode = '@';
  ctx->enc_packmode = '@';
  ctx->new_count = 1;
  ctx->enc_count = 0;
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  ctx->is_valid_array = 0;
  ctx->struct_alignment = 0;
  while (type->typegroup == 'S') {
    ++ctx->head;
    ctx->head->field = type->fields;
    ctx->head->parent_offset = 0;
    type = type->fields->type;
  }
}
static int __Pyx_BufFmt_ParseNumber(const char** ts) {
    int count;
    const char* t = *ts;
    if (*t < '0' || *t > '9') {
      return -1;
    } else {
        count = *t++ - '0';
        while (*t >= '0' && *t < '9') {
            count *= 10;
            count += *t++ - '0';
        }
    }
    *ts = t;
    return count;
}
static int __Pyx_BufFmt_ExpectNumber(const char **ts) {
    int number = __Pyx_BufFmt_ParseNumber(ts);
    if (number == -1)
        PyErr_Format(PyExc_ValueError,\
                     "Does not understand character buffer dtype format string ('%c')", **ts);
    return number;
}
static void __Pyx_BufFmt_RaiseUnexpectedChar(char ch) {
  PyErr_Format(PyExc_ValueError,
               "Unexpected format string character: '%c'", ch);
}
static const char* __Pyx_BufFmt_DescribeTypeChar(char ch, int is_complex) {
  switch (ch) {
    case 'c': return "'char'";
    case 'b': return "'signed char'";
    case 'B': return "'unsigned char'";
    case 'h': return "'short'";
    case 'H': return "'unsigned short'";
    case 'i': return "'int'";
    case 'I': return "'unsigned int'";
    case 'l': return "'long'";
    case 'L': return "'unsigned long'";
    case 'q': return "'long long'";
    case 'Q': return "'unsigned long long'";
    case 'f': return (is_complex ? "'complex float'" : "'float'");
    case 'd': return (is_complex ? "'complex double'" : "'double'");
    case 'g': return (is_complex ? "'complex long double'" : "'long double'");
    case 'T': return "a struct";
    case 'O': return "Python object";
    case 'P': return "a pointer";
    case 's': case 'p': return "a string";
    case 0: return "end";
    default: return "unparseable format string";
  }
}
static size_t __Pyx_BufFmt_TypeCharToStandardSize(char ch, int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return 2;
    case 'i': case 'I': case 'l': case 'L': return 4;
    case 'q': case 'Q': return 8;
    case 'f': return (is_complex ? 8 : 4);
    case 'd': return (is_complex ? 16 : 8);
    case 'g': {
      PyErr_SetString(PyExc_ValueError, "Python does not define a standard format string size for long double ('g')..");
      return 0;
    }
    case 'O': case 'P': return sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static size_t __Pyx_BufFmt_TypeCharToNativeSize(char ch, int is_complex) {
  switch (ch) {
    case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(short);
    case 'i': case 'I': return sizeof(int);
    case 'l': case 'L': return sizeof(long);
    #ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(PY_LONG_LONG);
    #endif
    case 'f': return sizeof(float) * (is_complex ? 2 : 1);
    case 'd': return sizeof(double) * (is_complex ? 2 : 1);
    case 'g': return sizeof(long double) * (is_complex ? 2 : 1);
    case 'O': case 'P': return sizeof(void*);
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
typedef struct { char c; short x; } __Pyx_st_short;
typedef struct { char c; int x; } __Pyx_st_int;
typedef struct { char c; long x; } __Pyx_st_long;
typedef struct { char c; float x; } __Pyx_st_float;
typedef struct { char c; double x; } __Pyx_st_double;
typedef struct { char c; long double x; } __Pyx_st_longdouble;
typedef struct { char c; void *x; } __Pyx_st_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { char c; PY_LONG_LONG x; } __Pyx_st_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToAlignment(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_st_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_st_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_st_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_st_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_st_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_st_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_st_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_st_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
/* These are for computing the padding at the end of the struct to align
   on the first member of the struct. This will probably the same as above,
   but we don't have any guarantees.
 */
typedef struct { short x; char c; } __Pyx_pad_short;
typedef struct { int x; char c; } __Pyx_pad_int;
typedef struct { long x; char c; } __Pyx_pad_long;
typedef struct { float x; char c; } __Pyx_pad_float;
typedef struct { double x; char c; } __Pyx_pad_double;
typedef struct { long double x; char c; } __Pyx_pad_longdouble;
typedef struct { void *x; char c; } __Pyx_pad_void_p;
#ifdef HAVE_LONG_LONG
typedef struct { PY_LONG_LONG x; char c; } __Pyx_pad_longlong;
#endif
static size_t __Pyx_BufFmt_TypeCharToPadding(char ch, CYTHON_UNUSED int is_complex) {
  switch (ch) {
    case '?': case 'c': case 'b': case 'B': case 's': case 'p': return 1;
    case 'h': case 'H': return sizeof(__Pyx_pad_short) - sizeof(short);
    case 'i': case 'I': return sizeof(__Pyx_pad_int) - sizeof(int);
    case 'l': case 'L': return sizeof(__Pyx_pad_long) - sizeof(long);
#ifdef HAVE_LONG_LONG
    case 'q': case 'Q': return sizeof(__Pyx_pad_longlong) - sizeof(PY_LONG_LONG);
#endif
    case 'f': return sizeof(__Pyx_pad_float) - sizeof(float);
    case 'd': return sizeof(__Pyx_pad_double) - sizeof(double);
    case 'g': return sizeof(__Pyx_pad_longdouble) - sizeof(long double);
    case 'P': case 'O': return sizeof(__Pyx_pad_void_p) - sizeof(void*);
    default:
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
}
static char __Pyx_BufFmt_TypeCharToGroup(char ch, int is_complex) {
  switch (ch) {
    case 'c':
        return 'H';
    case 'b': case 'h': case 'i':
    case 'l': case 'q': case 's': case 'p':
        return 'I';
    case 'B': case 'H': case 'I': case 'L': case 'Q':
        return 'U';
    case 'f': case 'd': case 'g':
        return (is_complex ? 'C' : 'R');
    case 'O':
        return 'O';
    case 'P':
        return 'P';
    default: {
      __Pyx_BufFmt_RaiseUnexpectedChar(ch);
      return 0;
    }
  }
}
static void __Pyx_BufFmt_RaiseExpected(__Pyx_BufFmt_Context* ctx) {
  if (ctx->head == NULL || ctx->head->field == &ctx->root) {
    const char* expected;
    const char* quote;
    if (ctx->head == NULL) {
      expected = "end";
      quote = "";
    } else {
      expected = ctx->head->field->type->name;
      quote = "'";
    }
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected %s%s%s but got %s",
                 quote, expected, quote,
                 __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex));
  } else {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_StructField* parent = (ctx->head - 1)->field;
    PyErr_Format(PyExc_ValueError,
                 "Buffer dtype mismatch, expected '%s' but got %s in '%s.%s'",
                 field->type->name, __Pyx_BufFmt_DescribeTypeChar(ctx->enc_type, ctx->is_complex),
                 parent->type->name, field->name);
  }
}
static int __Pyx_BufFmt_ProcessTypeChunk(__Pyx_BufFmt_Context* ctx) {
  char group;
  size_t size, offset, arraysize = 1;
  if (ctx->enc_type == 0) return 0;
  if (ctx->head->field->type->arraysize[0]) {
    int i, ndim = 0;
    if (ctx->enc_type == 's' || ctx->enc_type == 'p') {
        ctx->is_valid_array = ctx->head->field->type->ndim == 1;
        ndim = 1;
        if (ctx->enc_count != ctx->head->field->type->arraysize[0]) {
            PyErr_Format(PyExc_ValueError,
                         "Expected a dimension of size %zu, got %zu",
                         ctx->head->field->type->arraysize[0], ctx->enc_count);
            return -1;
        }
    }
    if (!ctx->is_valid_array) {
      PyErr_Format(PyExc_ValueError, "Expected %d dimensions, got %d",
                   ctx->head->field->type->ndim, ndim);
      return -1;
    }
    for (i = 0; i < ctx->head->field->type->ndim; i++) {
      arraysize *= ctx->head->field->type->arraysize[i];
    }
    ctx->is_valid_array = 0;
    ctx->enc_count = 1;
  }
  group = __Pyx_BufFmt_TypeCharToGroup(ctx->enc_type, ctx->is_complex);
  do {
    __Pyx_StructField* field = ctx->head->field;
    __Pyx_TypeInfo* type = field->type;
    if (ctx->enc_packmode == '@' || ctx->enc_packmode == '^') {
      size = __Pyx_BufFmt_TypeCharToNativeSize(ctx->enc_type, ctx->is_complex);
    } else {
      size = __Pyx_BufFmt_TypeCharToStandardSize(ctx->enc_type, ctx->is_complex);
    }
    if (ctx->enc_packmode == '@') {
      size_t align_at = __Pyx_BufFmt_TypeCharToAlignment(ctx->enc_type, ctx->is_complex);
      size_t align_mod_offset;
      if (align_at == 0) return -1;
      align_mod_offset = ctx->fmt_offset % align_at;
      if (align_mod_offset > 0) ctx->fmt_offset += align_at - align_mod_offset;
      if (ctx->struct_alignment == 0)
          ctx->struct_alignment = __Pyx_BufFmt_TypeCharToPadding(ctx->enc_type,
                                                                 ctx->is_complex);
    }
    if (type->size != size || type->typegroup != group) {
      if (type->typegroup == 'C' && type->fields != NULL) {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        ++ctx->head;
        ctx->head->field = type->fields;
        ctx->head->parent_offset = parent_offset;
        continue;
      }
      if ((type->typegroup == 'H' || group == 'H') && type->size == size) {
      } else {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
      }
    }
    offset = ctx->head->parent_offset + field->offset;
    if (ctx->fmt_offset != offset) {
      PyErr_Format(PyExc_ValueError,
                   "Buffer dtype mismatch; next field is at offset %" CYTHON_FORMAT_SSIZE_T "d but %" CYTHON_FORMAT_SSIZE_T "d expected",
                   (Py_ssize_t)ctx->fmt_offset, (Py_ssize_t)offset);
      return -1;
    }
    ctx->fmt_offset += size;
    if (arraysize)
      ctx->fmt_offset += (arraysize - 1) * size;
    --ctx->enc_count;
    while (1) {
      if (field == &ctx->root) {
        ctx->head = NULL;
        if (ctx->enc_count != 0) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return -1;
        }
        break;
      }
      ctx->head->field = ++field;
      if (field->type == NULL) {
        --ctx->head;
        field = ctx->head->field;
        continue;
      } else if (field->type->typegroup == 'S') {
        size_t parent_offset = ctx->head->parent_offset + field->offset;
        if (field->type->fields->type == NULL) continue;
        field = field->type->fields;
        ++ctx->head;
        ctx->head->field = field;
        ctx->head->parent_offset = parent_offset;
        break;
      } else {
        break;
      }
    }
  } while (ctx->enc_count);
  ctx->enc_type = 0;
  ctx->is_complex = 0;
  return 0;
}
static CYTHON_INLINE PyObject *
__pyx_buffmt_parse_array(__Pyx_BufFmt_Context* ctx, const char** tsp)
{
    const char *ts = *tsp;
    int i = 0, number;
    int ndim = ctx->head->field->type->ndim;
;
    ++ts;
    if (ctx->new_count != 1) {
        PyErr_SetString(PyExc_ValueError,
                        "Cannot handle repeated arrays in format string");
        return NULL;
    }
    if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
    while (*ts && *ts != ')') {
        switch (*ts) {
            case ' ': case '\f': case '\r': case '\n': case '\t': case '\v':  continue;
            default:  break;
        }
        number = __Pyx_BufFmt_ExpectNumber(&ts);
        if (number == -1) return NULL;
        if (i < ndim && (size_t) number != ctx->head->field->type->arraysize[i])
            return PyErr_Format(PyExc_ValueError,
                        "Expected a dimension of size %zu, got %d",
                        ctx->head->field->type->arraysize[i], number);
        if (*ts != ',' && *ts != ')')
            return PyErr_Format(PyExc_ValueError,
                                "Expected a comma in format string, got '%c'", *ts);
        if (*ts == ',') ts++;
        i++;
    }
    if (i != ndim)
        return PyErr_Format(PyExc_ValueError, "Expected %d dimension(s), got %d",
                            ctx->head->field->type->ndim, i);
    if (!*ts) {
        PyErr_SetString(PyExc_ValueError,
                        "Unexpected end of format string, expected ')'");
        return NULL;
    }
    ctx->is_valid_array = 1;
    ctx->new_count = 1;
    *tsp = ++ts;
    return Py_None;
}
static const char* __Pyx_BufFmt_CheckString(__Pyx_BufFmt_Context* ctx, const char* ts) {
  int got_Z = 0;
  while (1) {
    switch(*ts) {
      case 0:
        if (ctx->enc_type != 0 && ctx->head == NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        if (ctx->head != NULL) {
          __Pyx_BufFmt_RaiseExpected(ctx);
          return NULL;
        }
        return ts;
      case ' ':
      case '\r':
      case '\n':
        ++ts;
        break;
      case '<':
        if (!__Pyx_IsLittleEndian()) {
          PyErr_SetString(PyExc_ValueError, "Little-endian buffer not supported on big-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '>':
      case '!':
        if (__Pyx_IsLittleEndian()) {
          PyErr_SetString(PyExc_ValueError, "Big-endian buffer not supported on little-endian compiler");
          return NULL;
        }
        ctx->new_packmode = '=';
        ++ts;
        break;
      case '=':
      case '@':
      case '^':
        ctx->new_packmode = *ts++;
        break;
      case 'T':
        {
          const char* ts_after_sub;
          size_t i, struct_count = ctx->new_count;
          size_t struct_alignment = ctx->struct_alignment;
          ctx->new_count = 1;
          ++ts;
          if (*ts != '{') {
            PyErr_SetString(PyExc_ValueError, "Buffer acquisition: Expected '{' after 'T'");
            return NULL;
          }
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0;
          ctx->enc_count = 0;
          ctx->struct_alignment = 0;
          ++ts;
          ts_after_sub = ts;
          for (i = 0; i != struct_count; ++i) {
            ts_after_sub = __Pyx_BufFmt_CheckString(ctx, ts);
            if (!ts_after_sub) return NULL;
          }
          ts = ts_after_sub;
          if (struct_alignment) ctx->struct_alignment = struct_alignment;
        }
        break;
      case '}':
        {
          size_t alignment = ctx->struct_alignment;
          ++ts;
          if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
          ctx->enc_type = 0;
          if (alignment && ctx->fmt_offset % alignment) {
            ctx->fmt_offset += alignment - (ctx->fmt_offset % alignment);
          }
        }
        return ts;
      case 'x':
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        ctx->fmt_offset += ctx->new_count;
        ctx->new_count = 1;
        ctx->enc_count = 0;
        ctx->enc_type = 0;
        ctx->enc_packmode = ctx->new_packmode;
        ++ts;
        break;
      case 'Z':
        got_Z = 1;
        ++ts;
        if (*ts != 'f' && *ts != 'd' && *ts != 'g') {
          __Pyx_BufFmt_RaiseUnexpectedChar('Z');
          return NULL;
        }
      case 'c': case 'b': case 'B': case 'h': case 'H': case 'i': case 'I':
      case 'l': case 'L': case 'q': case 'Q':
      case 'f': case 'd': case 'g':
      case 'O': case 'p':
        if (ctx->enc_type == *ts && got_Z == ctx->is_complex &&
            ctx->enc_packmode == ctx->new_packmode) {
          ctx->enc_count += ctx->new_count;
          ctx->new_count = 1;
          got_Z = 0;
          ++ts;
          break;
        }
      case 's':
        if (__Pyx_BufFmt_ProcessTypeChunk(ctx) == -1) return NULL;
        ctx->enc_count = ctx->new_count;
        ctx->enc_packmode = ctx->new_packmode;
        ctx->enc_type = *ts;
        ctx->is_complex = got_Z;
        ++ts;
        ctx->new_count = 1;
        got_Z = 0;
        break;
      case ':':
        ++ts;
        while(*ts != ':') ++ts;
        ++ts;
        break;
      case '(':
        if (!__pyx_buffmt_parse_array(ctx, &ts)) return NULL;
        break;
      default:
        {
          int number = __Pyx_BufFmt_ExpectNumber(&ts);
          if (number == -1) return NULL;
          ctx->new_count = (size_t)number;
        }
    }
  }
}
static CYTHON_INLINE void __Pyx_ZeroBuffer(Py_buffer* buf) {
  buf->buf = NULL;
  buf->obj = NULL;
  buf->strides = __Pyx_zeros;
  buf->shape = __Pyx_zeros;
  buf->suboffsets = __Pyx_minusones;
}
static CYTHON_INLINE int __Pyx_GetBufferAndValidate(
        Py_buffer* buf, PyObject* obj,  __Pyx_TypeInfo* dtype, int flags,
        int nd, int cast, __Pyx_BufFmt_StackElem* stack)
{
  if (obj == Py_None || obj == NULL) {
    __Pyx_ZeroBuffer(buf);
    return 0;
  }
  buf->buf = NULL;
  if (__Pyx_GetBuffer(obj, buf, flags) == -1) goto fail;
  if (buf->ndim != nd) {
    PyErr_Format(PyExc_ValueError,
                 "Buffer has wrong number of dimensions (expected %d, got %d)",
                 nd, buf->ndim);
    goto fail;
  }
  if (!cast) {
    __Pyx_BufFmt_Context ctx;
    __Pyx_BufFmt_Init(&ctx, stack, dtype);
    if (!__Pyx_BufFmt_CheckString(&ctx, buf->format)) goto fail;
  }
  if ((unsigned)buf->itemsize != dtype->size) {
    PyErr_Format(PyExc_ValueError,
      "Item size of buffer (%" CYTHON_FORMAT_SSIZE_T "d byte%s) does not match size of '%s' (%" CYTHON_FORMAT_SSIZE_T "d byte%s)",
      buf->itemsize, (buf->itemsize > 1) ? "s" : "",
      dtype->name, (Py_ssize_t)dtype->size, (dtype->size > 1) ? "s" : "");
    goto fail;
  }
  if (buf->suboffsets == NULL) buf->suboffsets = __Pyx_minusones;
  return 0;
fail:;
  __Pyx_ZeroBuffer(buf);
  return -1;
}
static CYTHON_INLINE void __Pyx_SafeReleaseBuffer(Py_buffer* info) {
  if (info->buf == NULL) return;
  if (info->suboffsets == __Pyx_minusones) info->suboffsets = NULL;
  __Pyx_ReleaseBuffer(info);
}

/* PyObjectCallNoArg */
      #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, NULL, 0);
    }
#endif
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

/* BytesEquals */
        static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
    if (s1 == s2) {
        return (equals == Py_EQ);
    } else if (PyBytes_CheckExact(s1) & PyBytes_CheckExact(s2)) {
        const char *ps1, *ps2;
        Py_ssize_t length = PyBytes_GET_SIZE(s1);
        if (length != PyBytes_GET_SIZE(s2))
            return (equals == Py_NE);
        ps1 = PyBytes_AS_STRING(s1);
        ps2 = PyBytes_AS_STRING(s2);
        if (ps1[0] != ps2[0]) {
            return (equals == Py_NE);
        } else if (length == 1) {
            return (equals == Py_EQ);
        } else {
            int result = memcmp(ps1, ps2, (size_t)length);
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & PyBytes_CheckExact(s2)) {
        return (equals == Py_NE);
    } else if ((s2 == Py_None) & PyBytes_CheckExact(s1)) {
        return (equals == Py_NE);
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
#endif
}

/* UnicodeEquals */
        static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
#if PY_MAJOR_VERSION < 3
    PyObject* owned_ref = NULL;
#endif
    int s1_is_unicode, s2_is_unicode;
    if (s1 == s2) {
        goto return_eq;
    }
    s1_is_unicode = PyUnicode_CheckExact(s1);
    s2_is_unicode = PyUnicode_CheckExact(s2);
#if PY_MAJOR_VERSION < 3
    if ((s1_is_unicode & (!s2_is_unicode)) && PyString_CheckExact(s2)) {
        owned_ref = PyUnicode_FromObject(s2);
        if (unlikely(!owned_ref))
            return -1;
        s2 = owned_ref;
        s2_is_unicode = 1;
    } else if ((s2_is_unicode & (!s1_is_unicode)) && PyString_CheckExact(s1)) {
        owned_ref = PyUnicode_FromObject(s1);
        if (unlikely(!owned_ref))
            return -1;
        s1 = owned_ref;
        s1_is_unicode = 1;
    } else if (((!s2_is_unicode) & (!s1_is_unicode))) {
        return __Pyx_PyBytes_Equals(s1, s2, equals);
    }
#endif
    if (s1_is_unicode & s2_is_unicode) {
        Py_ssize_t length;
        int kind;
        void *data1, *data2;
        if (unlikely(__Pyx_PyUnicode_READY(s1) < 0) || unlikely(__Pyx_PyUnicode_READY(s2) < 0))
            return -1;
        length = __Pyx_PyUnicode_GET_LENGTH(s1);
        if (length != __Pyx_PyUnicode_GET_LENGTH(s2)) {
            goto return_ne;
        }
        kind = __Pyx_PyUnicode_KIND(s1);
        if (kind != __Pyx_PyUnicode_KIND(s2)) {
            goto return_ne;
        }
        data1 = __Pyx_PyUnicode_DATA(s1);
        data2 = __Pyx_PyUnicode_DATA(s2);
        if (__Pyx_PyUnicode_READ(kind, data1, 0) != __Pyx_PyUnicode_READ(kind, data2, 0)) {
            goto return_ne;
        } else if (length == 1) {
            goto return_eq;
        } else {
            int result = memcmp(data1, data2, (size_t)(length * kind));
            #if PY_MAJOR_VERSION < 3
            Py_XDECREF(owned_ref);
            #endif
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & s2_is_unicode) {
        goto return_ne;
    } else if ((s2 == Py_None) & s1_is_unicode) {
        goto return_ne;
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
return_eq:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_EQ);
return_ne:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_NE);
#endif
}

/* ExtTypeTest */
        static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type) {
    if (unlikely(!type)) {
        PyErr_SetString(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (likely(PyObject_TypeCheck(obj, type)))
        return 1;
    PyErr_Format(PyExc_TypeError, "Cannot convert %.200s to %.200s",
                 Py_TYPE(obj)->tp_name, type->tp_name);
    return 0;
}

/* BufferFallbackError */
        static void __Pyx_RaiseBufferFallbackError(void) {
  PyErr_SetString(PyExc_ValueError,
     "Buffer acquisition failed on assignment; and then reacquiring the old buffer failed too!");
}

/* PyErrFetchRestore */
        #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
}
#endif

/* PyIntBinop */
        #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long x;
        long a = PyInt_AS_LONG(op1);
            x = (long)((unsigned long)a + b);
            if (likely((x^a) >= 0 || (x^b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_add(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG llb = intval;
        PY_LONG_LONG lla, llx;
#endif
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            a = likely(size) ? digits[0] : 0;
            if (size == -1) a = -a;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                default: return PyLong_Type.tp_as_number->nb_add(op1, op2);
            }
        }
                x = a + b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla + llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            double result;
            PyFPE_START_PROTECT("add", return NULL)
            result = ((double)a) + (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

/* RaiseTooManyValuesToUnpack */
        static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
}

/* RaiseNeedMoreValuesToUnpack */
        static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%.1s to unpack",
                 index, (index == 1) ? "" : "s");
}

/* IterFinish */
        static CYTHON_INLINE int __Pyx_IterFinish(void) {
#if CYTHON_FAST_THREAD_STATE
    PyThreadState *tstate = PyThreadState_GET();
    PyObject* exc_type = tstate->curexc_type;
    if (unlikely(exc_type)) {
        if (likely(exc_type == PyExc_StopIteration) || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)) {
            PyObject *exc_value, *exc_tb;
            exc_value = tstate->curexc_value;
            exc_tb = tstate->curexc_traceback;
            tstate->curexc_type = 0;
            tstate->curexc_value = 0;
            tstate->curexc_traceback = 0;
            Py_DECREF(exc_type);
            Py_XDECREF(exc_value);
            Py_XDECREF(exc_tb);
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#else
    if (unlikely(PyErr_Occurred())) {
        if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) {
            PyErr_Clear();
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#endif
}

/* UnpackItemEndCheck */
        static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected) {
    if (unlikely(retval)) {
        Py_DECREF(retval);
        __Pyx_RaiseTooManyValuesError(expected);
        return -1;
    } else {
        return __Pyx_IterFinish();
    }
    return 0;
}

/* PyFloatBinop */
        #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_DivideObjC(PyObject *op1, PyObject *op2, double floatval, CYTHON_UNUSED int inplace) {
    const double b = floatval;
    double a, result;
    if (likely(PyFloat_CheckExact(op1))) {
        a = PyFloat_AS_DOUBLE(op1);
    } else
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        a = (double) PyInt_AS_LONG(op1);
    } else
    #endif
    if (likely(PyLong_CheckExact(op1))) {
        #if CYTHON_USE_PYLONG_INTERNALS
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        switch (size) {
            case  0: a = 0.0; break;
            case -1: a = -(double) digits[0]; break;
            case  1: a = (double) digits[0]; break;
            case -2:
            case 2:
                if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (1 * PyLong_SHIFT < 53))) {
                    a = (double) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -2)
                            a = -a;
                        break;
                    }
                }
            case -3:
            case 3:
                if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53))) {
                    a = (double) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -3)
                            a = -a;
                        break;
                    }
                }
            case -4:
            case 4:
                if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53))) {
                    a = (double) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (4 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -4)
                            a = -a;
                        break;
                    }
                }
            default:
        #else
        {
        #endif
            a = PyLong_AsDouble(op1);
            if (unlikely(a == -1.0 && PyErr_Occurred())) return NULL;
        }
    } else {
        return (inplace ? __Pyx_PyNumber_InPlaceDivide(op1, op2) : __Pyx_PyNumber_Divide(op1, op2));
    }
        PyFPE_START_PROTECT("divide", return NULL)
        result = a / b;
        PyFPE_END_PROTECT(result)
        return PyFloat_FromDouble(result);
}
#endif

/* PyIntBinop */
          #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_SubtractCObj(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op2))) {
        const long a = intval;
        long x;
        long b = PyInt_AS_LONG(op2);
            x = (long)((unsigned long)a - b);
            if (likely((x^a) >= 0 || (x^~b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_subtract(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op2))) {
        const long a = intval;
        long b, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG lla = intval;
        PY_LONG_LONG llb, llx;
#endif
        const digit* digits = ((PyLongObject*)op2)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op2);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            b = likely(size) ? digits[0] : 0;
            if (size == -1) b = -b;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        b = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        b = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        b = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        b = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        b = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        b = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                default: return PyLong_Type.tp_as_number->nb_subtract(op1, op2);
            }
        }
                x = a - b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla - llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op2)) {
        const long a = intval;
        double b = PyFloat_AS_DOUBLE(op2);
            double result;
            PyFPE_START_PROTECT("subtract", return NULL)
            result = ((double)a) - (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceSubtract : PyNumber_Subtract)(op1, op2);
}
#endif

/* PyFloatBinop */
          #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyFloat_SubtractObjC(PyObject *op1, PyObject *op2, double floatval, CYTHON_UNUSED int inplace) {
    const double b = floatval;
    double a, result;
    if (likely(PyFloat_CheckExact(op1))) {
        a = PyFloat_AS_DOUBLE(op1);
    } else
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        a = (double) PyInt_AS_LONG(op1);
    } else
    #endif
    if (likely(PyLong_CheckExact(op1))) {
        #if CYTHON_USE_PYLONG_INTERNALS
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        switch (size) {
            case  0: a = 0.0; break;
            case -1: a = -(double) digits[0]; break;
            case  1: a = (double) digits[0]; break;
            case -2:
            case 2:
                if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (1 * PyLong_SHIFT < 53))) {
                    a = (double) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -2)
                            a = -a;
                        break;
                    }
                }
            case -3:
            case 3:
                if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (2 * PyLong_SHIFT < 53))) {
                    a = (double) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -3)
                            a = -a;
                        break;
                    }
                }
            case -4:
            case 4:
                if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT && ((8 * sizeof(unsigned long) < 53) || (3 * PyLong_SHIFT < 53))) {
                    a = (double) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                    if ((8 * sizeof(unsigned long) < 53) || (4 * PyLong_SHIFT < 53) || (a < (double) (1L<<53))) {
                        if (size == -4)
                            a = -a;
                        break;
                    }
                }
            default:
        #else
        {
        #endif
            a = PyLong_AsDouble(op1);
            if (unlikely(a == -1.0 && PyErr_Occurred())) return NULL;
        }
    } else {
        return (inplace ? PyNumber_InPlaceSubtract : PyNumber_Subtract)(op1, op2);
    }
        PyFPE_START_PROTECT("subtract", return NULL)
        result = a - b;
        PyFPE_END_PROTECT(result)
        return PyFloat_FromDouble(result);
}
#endif

/* PyIntBinop */
            #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddCObj(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op2))) {
        const long a = intval;
        long x;
        long b = PyInt_AS_LONG(op2);
            x = (long)((unsigned long)a + b);
            if (likely((x^a) >= 0 || (x^b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_add(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op2))) {
        const long a = intval;
        long b, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG lla = intval;
        PY_LONG_LONG llb, llx;
#endif
        const digit* digits = ((PyLongObject*)op2)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op2);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            b = likely(size) ? digits[0] : 0;
            if (size == -1) b = -b;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        b = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        b = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        b = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        b = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        b = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        llb = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        b = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        llb = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                default: return PyLong_Type.tp_as_number->nb_add(op1, op2);
            }
        }
                x = a + b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla + llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op2)) {
        const long a = intval;
        double b = PyFloat_AS_DOUBLE(op2);
            double result;
            PyFPE_START_PROTECT("add", return NULL)
            result = ((double)a) + (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

/* RaiseException */
            #if PY_MAJOR_VERSION < 3
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb,
                        CYTHON_UNUSED PyObject *cause) {
    __Pyx_PyThreadState_declare
    Py_XINCREF(type);
    if (!value || value == Py_None)
        value = NULL;
    else
        Py_INCREF(value);
    if (!tb || tb == Py_None)
        tb = NULL;
    else {
        Py_INCREF(tb);
        if (!PyTraceBack_Check(tb)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: arg 3 must be a traceback or None");
            goto raise_error;
        }
    }
    if (PyType_Check(type)) {
#if CYTHON_COMPILING_IN_PYPY
        if (!value) {
            Py_INCREF(Py_None);
            value = Py_None;
        }
#endif
        PyErr_NormalizeException(&type, &value, &tb);
    } else {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        value = type;
        type = (PyObject*) Py_TYPE(type);
        Py_INCREF(type);
        if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
            PyErr_SetString(PyExc_TypeError,
                "raise: exception class must be a subclass of BaseException");
            goto raise_error;
        }
    }
    __Pyx_PyThreadState_assign
    __Pyx_ErrRestore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}
#else
static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb, PyObject *cause) {
    PyObject* owned_instance = NULL;
    if (tb == Py_None) {
        tb = 0;
    } else if (tb && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto bad;
    }
    if (value == Py_None)
        value = 0;
    if (PyExceptionInstance_Check(type)) {
        if (value) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto bad;
        }
        value = type;
        type = (PyObject*) Py_TYPE(value);
    } else if (PyExceptionClass_Check(type)) {
        PyObject *instance_class = NULL;
        if (value && PyExceptionInstance_Check(value)) {
            instance_class = (PyObject*) Py_TYPE(value);
            if (instance_class != type) {
                int is_subclass = PyObject_IsSubclass(instance_class, type);
                if (!is_subclass) {
                    instance_class = NULL;
                } else if (unlikely(is_subclass == -1)) {
                    goto bad;
                } else {
                    type = instance_class;
                }
            }
        }
        if (!instance_class) {
            PyObject *args;
            if (!value)
                args = PyTuple_New(0);
            else if (PyTuple_Check(value)) {
                Py_INCREF(value);
                args = value;
            } else
                args = PyTuple_Pack(1, value);
            if (!args)
                goto bad;
            owned_instance = PyObject_Call(type, args, NULL);
            Py_DECREF(args);
            if (!owned_instance)
                goto bad;
            value = owned_instance;
            if (!PyExceptionInstance_Check(value)) {
                PyErr_Format(PyExc_TypeError,
                             "calling %R should have returned an instance of "
                             "BaseException, not %R",
                             type, Py_TYPE(value));
                goto bad;
            }
        }
    } else {
        PyErr_SetString(PyExc_TypeError,
            "raise: exception class must be a subclass of BaseException");
        goto bad;
    }
#if PY_VERSION_HEX >= 0x03030000
    if (cause) {
#else
    if (cause && cause != Py_None) {
#endif
        PyObject *fixed_cause;
        if (cause == Py_None) {
            fixed_cause = NULL;
        } else if (PyExceptionClass_Check(cause)) {
            fixed_cause = PyObject_CallObject(cause, NULL);
            if (fixed_cause == NULL)
                goto bad;
        } else if (PyExceptionInstance_Check(cause)) {
            fixed_cause = cause;
            Py_INCREF(fixed_cause);
        } else {
            PyErr_SetString(PyExc_TypeError,
                            "exception causes must derive from "
                            "BaseException");
            goto bad;
        }
        PyException_SetCause(value, fixed_cause);
    }
    PyErr_SetObject(type, value);
    if (tb) {
#if CYTHON_COMPILING_IN_PYPY
        PyObject *tmp_type, *tmp_value, *tmp_tb;
        PyErr_Fetch(&tmp_type, &tmp_value, &tmp_tb);
        Py_INCREF(tb);
        PyErr_Restore(tmp_type, tmp_value, tb);
        Py_XDECREF(tmp_tb);
#else
        PyThreadState *tstate = PyThreadState_GET();
        PyObject* tmp_tb = tstate->curexc_traceback;
        if (tb != tmp_tb) {
            Py_INCREF(tb);
            tstate->curexc_traceback = tb;
            Py_XDECREF(tmp_tb);
        }
#endif
    }
bad:
    Py_XDECREF(owned_instance);
    return;
}
#endif

/* RaiseNoneIterError */
              static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
}

/* SaveResetException */
              #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
}
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
#endif

/* PyErrExceptionMatches */
              #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE int __Pyx_PyErr_ExceptionMatchesInState(PyThreadState* tstate, PyObject* err) {
    PyObject *exc_type = tstate->curexc_type;
    if (exc_type == err) return 1;
    if (unlikely(!exc_type)) return 0;
    return PyErr_GivenExceptionMatches(exc_type, err);
}
#endif

/* GetException */
              #if CYTHON_FAST_THREAD_STATE
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
#endif
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_FAST_THREAD_STATE
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_FAST_THREAD_STATE
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (local_tb) {
        if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
            goto bad;
    }
    #endif
    Py_XINCREF(local_tb);
    Py_XINCREF(local_type);
    Py_XINCREF(local_value);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_FAST_THREAD_STATE
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

/* Import */
                static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

/* ImportFrom */
                static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

/* CodeObjectCache */
                static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = start + (end - start) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

/* AddTraceback */
                #include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        __pyx_d,      /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    __Pyx_PyFrame_SetLineNumber(py_frame, py_line);
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

#if PY_MAJOR_VERSION < 3
static int __Pyx_GetBuffer(PyObject *obj, Py_buffer *view, int flags) {
    if (PyObject_CheckBuffer(obj)) return PyObject_GetBuffer(obj, view, flags);
        if (PyObject_TypeCheck(obj, __pyx_ptype_5numpy_ndarray)) return __pyx_pw_5numpy_7ndarray_1__getbuffer__(obj, view, flags);
    PyErr_Format(PyExc_TypeError, "'%.200s' does not have the buffer interface", Py_TYPE(obj)->tp_name);
    return -1;
}
static void __Pyx_ReleaseBuffer(Py_buffer *view) {
    PyObject *obj = view->obj;
    if (!obj) return;
    if (PyObject_CheckBuffer(obj)) {
        PyBuffer_Release(view);
        return;
    }
        if (PyObject_TypeCheck(obj, __pyx_ptype_5numpy_ndarray)) { __pyx_pw_5numpy_7ndarray_3__releasebuffer__(obj, view); return; }
    Py_DECREF(obj);
    view->obj = NULL;
}
#endif


                /* CIntFromPyVerify */
                #define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc)\
    {\
        func_type value = func_value;\
        if (sizeof(target_type) < sizeof(func_type)) {\
            if (unlikely(value != (func_type) (target_type) value)) {\
                func_type zero = 0;\
                if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))\
                    return (target_type) -1;\
                if (is_unsigned && unlikely(value < zero))\
                    goto raise_neg_overflow;\
                else\
                    goto raise_overflow;\
            }\
        }\
        return (target_type) value;\
    }

/* CIntToPy */
                static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

/* CIntToPy */
                static CYTHON_INLINE PyObject* __Pyx_PyInt_From_unsigned_int(unsigned int value) {
    const unsigned int neg_one = (unsigned int) -1, const_zero = (unsigned int) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(unsigned int) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(unsigned int) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(unsigned int) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(unsigned int) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(unsigned int) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(unsigned int),
                                     little, !is_unsigned);
    }
}

/* CIntToPy */
                static CYTHON_INLINE PyObject* __Pyx_PyInt_From_int(int value) {
    const int neg_one = (int) -1, const_zero = (int) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(int) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(int) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(int) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(int),
                                     little, !is_unsigned);
    }
}

/* Declarations */
                #if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return ::std::complex< float >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      return x + y*(__pyx_t_float_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_float_complex __pyx_t_float_complex_from_parts(float x, float y) {
      __pyx_t_float_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

/* Arithmetic */
                #if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eq_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_sum_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_diff_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_prod_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        __pyx_t_float_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    #if 1
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        if (b.imag == 0) {
            return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else if (fabsf(b.real) >= fabsf(b.imag)) {
            if (b.real == 0 && b.imag == 0) {
                return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.imag);
            } else {
                float r = b.imag / b.real;
                float s = 1.0 / (b.real + b.imag * r);
                return __pyx_t_float_complex_from_parts(
                    (a.real + a.imag * r) * s, (a.imag - a.real * r) * s);
            }
        } else {
            float r = b.real / b.imag;
            float s = 1.0 / (b.imag + b.real * r);
            return __pyx_t_float_complex_from_parts(
                (a.real * r + a.imag) * s, (a.imag * r - a.real) * s);
        }
    }
    #else
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_quot_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
        if (b.imag == 0) {
            return __pyx_t_float_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else {
            float denom = b.real * b.real + b.imag * b.imag;
            return __pyx_t_float_complex_from_parts(
                (a.real * b.real + a.imag * b.imag) / denom,
                (a.imag * b.real - a.real * b.imag) / denom);
        }
    }
    #endif
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_neg_float(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zero_float(__pyx_t_float_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_conj_float(__pyx_t_float_complex a) {
        __pyx_t_float_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE float __Pyx_c_abs_float(__pyx_t_float_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrtf(z.real*z.real + z.imag*z.imag);
          #else
            return hypotf(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_float_complex __Pyx_c_pow_float(__pyx_t_float_complex a, __pyx_t_float_complex b) {
            __pyx_t_float_complex z;
            float r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    float denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        z = __Pyx_c_prod_float(a, a);
                        return __Pyx_c_prod_float(a, a);
                    case 3:
                        z = __Pyx_c_prod_float(a, a);
                        return __Pyx_c_prod_float(z, a);
                    case 4:
                        z = __Pyx_c_prod_float(a, a);
                        return __Pyx_c_prod_float(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                } else if (b.imag == 0) {
                    z.real = powf(a.real, b.real);
                    z.imag = 0;
                    return z;
                } else if (a.real > 0) {
                    r = a.real;
                    theta = 0;
                } else {
                    r = -a.real;
                    theta = atan2f(0, -1);
                }
            } else {
                r = __Pyx_c_abs_float(a);
                theta = atan2f(a.imag, a.real);
            }
            lnr = logf(r);
            z_r = expf(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cosf(z_theta);
            z.imag = z_r * sinf(z_theta);
            return z;
        }
    #endif
#endif

/* Declarations */
                #if CYTHON_CCOMPLEX
  #ifdef __cplusplus
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return ::std::complex< double >(x, y);
    }
  #else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      return x + y*(__pyx_t_double_complex)_Complex_I;
    }
  #endif
#else
    static CYTHON_INLINE __pyx_t_double_complex __pyx_t_double_complex_from_parts(double x, double y) {
      __pyx_t_double_complex z;
      z.real = x;
      z.imag = y;
      return z;
    }
#endif

/* Arithmetic */
                #if CYTHON_CCOMPLEX
#else
    static CYTHON_INLINE int __Pyx_c_eq_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
       return (a.real == b.real) && (a.imag == b.imag);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_sum_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real + b.real;
        z.imag = a.imag + b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_diff_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real - b.real;
        z.imag = a.imag - b.imag;
        return z;
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_prod_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        __pyx_t_double_complex z;
        z.real = a.real * b.real - a.imag * b.imag;
        z.imag = a.real * b.imag + a.imag * b.real;
        return z;
    }
    #if 1
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        if (b.imag == 0) {
            return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else if (fabs(b.real) >= fabs(b.imag)) {
            if (b.real == 0 && b.imag == 0) {
                return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.imag);
            } else {
                double r = b.imag / b.real;
                double s = 1.0 / (b.real + b.imag * r);
                return __pyx_t_double_complex_from_parts(
                    (a.real + a.imag * r) * s, (a.imag - a.real * r) * s);
            }
        } else {
            double r = b.real / b.imag;
            double s = 1.0 / (b.imag + b.real * r);
            return __pyx_t_double_complex_from_parts(
                (a.real * r + a.imag) * s, (a.imag * r - a.real) * s);
        }
    }
    #else
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_quot_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
        if (b.imag == 0) {
            return __pyx_t_double_complex_from_parts(a.real / b.real, a.imag / b.real);
        } else {
            double denom = b.real * b.real + b.imag * b.imag;
            return __pyx_t_double_complex_from_parts(
                (a.real * b.real + a.imag * b.imag) / denom,
                (a.imag * b.real - a.real * b.imag) / denom);
        }
    }
    #endif
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_neg_double(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real = -a.real;
        z.imag = -a.imag;
        return z;
    }
    static CYTHON_INLINE int __Pyx_c_is_zero_double(__pyx_t_double_complex a) {
       return (a.real == 0) && (a.imag == 0);
    }
    static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_conj_double(__pyx_t_double_complex a) {
        __pyx_t_double_complex z;
        z.real =  a.real;
        z.imag = -a.imag;
        return z;
    }
    #if 1
        static CYTHON_INLINE double __Pyx_c_abs_double(__pyx_t_double_complex z) {
          #if !defined(HAVE_HYPOT) || defined(_MSC_VER)
            return sqrt(z.real*z.real + z.imag*z.imag);
          #else
            return hypot(z.real, z.imag);
          #endif
        }
        static CYTHON_INLINE __pyx_t_double_complex __Pyx_c_pow_double(__pyx_t_double_complex a, __pyx_t_double_complex b) {
            __pyx_t_double_complex z;
            double r, lnr, theta, z_r, z_theta;
            if (b.imag == 0 && b.real == (int)b.real) {
                if (b.real < 0) {
                    double denom = a.real * a.real + a.imag * a.imag;
                    a.real = a.real / denom;
                    a.imag = -a.imag / denom;
                    b.real = -b.real;
                }
                switch ((int)b.real) {
                    case 0:
                        z.real = 1;
                        z.imag = 0;
                        return z;
                    case 1:
                        return a;
                    case 2:
                        z = __Pyx_c_prod_double(a, a);
                        return __Pyx_c_prod_double(a, a);
                    case 3:
                        z = __Pyx_c_prod_double(a, a);
                        return __Pyx_c_prod_double(z, a);
                    case 4:
                        z = __Pyx_c_prod_double(a, a);
                        return __Pyx_c_prod_double(z, z);
                }
            }
            if (a.imag == 0) {
                if (a.real == 0) {
                    return a;
                } else if (b.imag == 0) {
                    z.real = pow(a.real, b.real);
                    z.imag = 0;
                    return z;
                } else if (a.real > 0) {
                    r = a.real;
                    theta = 0;
                } else {
                    r = -a.real;
                    theta = atan2(0, -1);
                }
            } else {
                r = __Pyx_c_abs_double(a);
                theta = atan2(a.imag, a.real);
            }
            lnr = log(r);
            z_r = exp(lnr * b.real - theta * b.imag);
            z_theta = theta * b.real + lnr * b.imag;
            z.real = z_r * cos(z_theta);
            z.imag = z_r * sin(z_theta);
            return z;
        }
    #endif
#endif

/* CIntToPy */
                static CYTHON_INLINE PyObject* __Pyx_PyInt_From_enum__NPY_TYPES(enum NPY_TYPES value) {
    const enum NPY_TYPES neg_one = (enum NPY_TYPES) -1, const_zero = (enum NPY_TYPES) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(enum NPY_TYPES) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(enum NPY_TYPES) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(enum NPY_TYPES) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(enum NPY_TYPES) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(enum NPY_TYPES) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(enum NPY_TYPES),
                                     little, !is_unsigned);
    }
}

/* CIntFromPy */
                static CYTHON_INLINE size_t __Pyx_PyInt_As_size_t(PyObject *x) {
    const size_t neg_one = (size_t) -1, const_zero = (size_t) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(size_t) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(size_t, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (size_t) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (size_t) 0;
                case  1: __PYX_VERIFY_RETURN_INT(size_t, digit, digits[0])
                case 2:
                    if (8 * sizeof(size_t) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) >= 2 * PyLong_SHIFT) {
                            return (size_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(size_t) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) >= 3 * PyLong_SHIFT) {
                            return (size_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(size_t) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) >= 4 * PyLong_SHIFT) {
                            return (size_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (size_t) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(size_t) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(size_t, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(size_t) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(size_t, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (size_t) 0;
                case -1: __PYX_VERIFY_RETURN_INT(size_t, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(size_t,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(size_t) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 2 * PyLong_SHIFT) {
                            return (size_t) (((size_t)-1)*(((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(size_t) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 2 * PyLong_SHIFT) {
                            return (size_t) ((((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(size_t) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 3 * PyLong_SHIFT) {
                            return (size_t) (((size_t)-1)*(((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(size_t) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 3 * PyLong_SHIFT) {
                            return (size_t) ((((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(size_t) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 4 * PyLong_SHIFT) {
                            return (size_t) (((size_t)-1)*(((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(size_t) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(size_t, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(size_t) - 1 > 4 * PyLong_SHIFT) {
                            return (size_t) ((((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(size_t) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(size_t, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(size_t) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(size_t, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            size_t val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (size_t) -1;
        }
    } else {
        size_t val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (size_t) -1;
        val = __Pyx_PyInt_As_size_t(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to size_t");
    return (size_t) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to size_t");
    return (size_t) -1;
}

/* CIntFromPy */
                static CYTHON_INLINE unsigned int __Pyx_PyInt_As_unsigned_int(PyObject *x) {
    const unsigned int neg_one = (unsigned int) -1, const_zero = (unsigned int) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(unsigned int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(unsigned int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (unsigned int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (unsigned int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(unsigned int, digit, digits[0])
                case 2:
                    if (8 * sizeof(unsigned int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) >= 2 * PyLong_SHIFT) {
                            return (unsigned int) (((((unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(unsigned int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) >= 3 * PyLong_SHIFT) {
                            return (unsigned int) (((((((unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(unsigned int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) >= 4 * PyLong_SHIFT) {
                            return (unsigned int) (((((((((unsigned int)digits[3]) << PyLong_SHIFT) | (unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (unsigned int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(unsigned int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(unsigned int, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(unsigned int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(unsigned int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (unsigned int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(unsigned int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(unsigned int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(unsigned int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 2 * PyLong_SHIFT) {
                            return (unsigned int) (((unsigned int)-1)*(((((unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(unsigned int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 2 * PyLong_SHIFT) {
                            return (unsigned int) ((((((unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(unsigned int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 3 * PyLong_SHIFT) {
                            return (unsigned int) (((unsigned int)-1)*(((((((unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(unsigned int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 3 * PyLong_SHIFT) {
                            return (unsigned int) ((((((((unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(unsigned int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 4 * PyLong_SHIFT) {
                            return (unsigned int) (((unsigned int)-1)*(((((((((unsigned int)digits[3]) << PyLong_SHIFT) | (unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(unsigned int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(unsigned int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(unsigned int) - 1 > 4 * PyLong_SHIFT) {
                            return (unsigned int) ((((((((((unsigned int)digits[3]) << PyLong_SHIFT) | (unsigned int)digits[2]) << PyLong_SHIFT) | (unsigned int)digits[1]) << PyLong_SHIFT) | (unsigned int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(unsigned int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(unsigned int, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(unsigned int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(unsigned int, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            unsigned int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (unsigned int) -1;
        }
    } else {
        unsigned int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (unsigned int) -1;
        val = __Pyx_PyInt_As_unsigned_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to unsigned int");
    return (unsigned int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to unsigned int");
    return (unsigned int) -1;
}

/* CIntFromPy */
                static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
                            return (long) (((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
                            return (long) (((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
                            return (long) (((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) ((((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) ((((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) ((((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

/* CIntFromPy */
                static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = (int) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
                            return (int) (((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
                            return (int) (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
                            return (int) (((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) ((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) ((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) ((((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

/* CStringEquals */
                static CYTHON_INLINE int __Pyx_StrEq(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) { s1++; s2++; }
    return *s1 == *s2;
}

/* CheckBinaryVersion */
                static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

/* ModuleImport */
                #ifndef __PYX_HAVE_RT_ImportModule
#define __PYX_HAVE_RT_ImportModule
static PyObject *__Pyx_ImportModule(const char *name) {
    PyObject *py_name = 0;
    PyObject *py_module = 0;
    py_name = __Pyx_PyIdentifier_FromString(name);
    if (!py_name)
        goto bad;
    py_module = PyImport_Import(py_name);
    Py_DECREF(py_name);
    return py_module;
bad:
    Py_XDECREF(py_name);
    return 0;
}
#endif

/* TypeImport */
                #ifndef __PYX_HAVE_RT_ImportType
#define __PYX_HAVE_RT_ImportType
static PyTypeObject *__Pyx_ImportType(const char *module_name, const char *class_name,
    size_t size, int strict)
{
    PyObject *py_module = 0;
    PyObject *result = 0;
    PyObject *py_name = 0;
    char warning[200];
    Py_ssize_t basicsize;
#ifdef Py_LIMITED_API
    PyObject *py_basicsize;
#endif
    py_module = __Pyx_ImportModule(module_name);
    if (!py_module)
        goto bad;
    py_name = __Pyx_PyIdentifier_FromString(class_name);
    if (!py_name)
        goto bad;
    result = PyObject_GetAttr(py_module, py_name);
    Py_DECREF(py_name);
    py_name = 0;
    Py_DECREF(py_module);
    py_module = 0;
    if (!result)
        goto bad;
    if (!PyType_Check(result)) {
        PyErr_Format(PyExc_TypeError,
            "%.200s.%.200s is not a type object",
            module_name, class_name);
        goto bad;
    }
#ifndef Py_LIMITED_API
    basicsize = ((PyTypeObject *)result)->tp_basicsize;
#else
    py_basicsize = PyObject_GetAttrString(result, "__basicsize__");
    if (!py_basicsize)
        goto bad;
    basicsize = PyLong_AsSsize_t(py_basicsize);
    Py_DECREF(py_basicsize);
    py_basicsize = 0;
    if (basicsize == (Py_ssize_t)-1 && PyErr_Occurred())
        goto bad;
#endif
    if (!strict && (size_t)basicsize > size) {
        PyOS_snprintf(warning, sizeof(warning),
            "%s.%s size changed, may indicate binary incompatibility. Expected %zd, got %zd",
            module_name, class_name, basicsize, size);
        if (PyErr_WarnEx(NULL, warning, 0) < 0) goto bad;
    }
    else if ((size_t)basicsize != size) {
        PyErr_Format(PyExc_ValueError,
            "%.200s.%.200s has the wrong size, try recompiling. Expected %zd, got %zd",
            module_name, class_name, basicsize, size);
        goto bad;
    }
    return (PyTypeObject *)result;
bad:
    Py_XDECREF(py_module);
    Py_XDECREF(result);
    return NULL;
}
#endif

/* InitStrings */
                static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if CYTHON_COMPILING_IN_CPYTHON && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else
        if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else
        return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
    } else
#endif
#if (!CYTHON_COMPILING_IN_PYPY) || (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x) {
#if CYTHON_USE_TYPE_SLOTS
  PyNumberMethods *m;
#endif
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return __Pyx_NewRef(x);
#if CYTHON_USE_TYPE_SLOTS
  m = Py_TYPE(x)->tp_as_number;
  #if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
  #else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
  #endif
#else
  res = PyNumber_Int(x);
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
        return PyInt_AS_LONG(b);
    else
        return PyInt_AsSsize_t(x);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_USE_PYLONG_INTERNALS
    const digit* digits = ((PyLongObject*)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
        ival = likely(size) ? digits[0] : 0;
        if (size == -1) ival = -ival;
        return ival;
    } else {
      switch (size) {
         case 2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
      }
    }
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
