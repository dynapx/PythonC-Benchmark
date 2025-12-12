
#include <Python.h>
#include <stddef.h>

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py
   and cffi/_cffi_include.h */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
#  ifndef __cplusplus
    typedef unsigned char _Bool;
#  endif
# endif
# define _cffi_float_complex_t   _Fcomplex    /* include <complex.h> for it */
# define _cffi_double_complex_t  _Dcomplex    /* include <complex.h> for it */
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
# define _cffi_float_complex_t   float _Complex
# define _cffi_double_complex_t  double _Complex
#endif

#if PY_MAJOR_VERSION < 3
# undef PyCapsule_CheckExact
# undef PyCapsule_GetPointer
# define PyCapsule_CheckExact(capsule) (PyCObject_Check(capsule))
# define PyCapsule_GetPointer(capsule, name) \
    (PyCObject_AsVoidPtr(capsule))
#endif

#if PY_MAJOR_VERSION >= 3
# define PyInt_FromLong PyLong_FromLong
#endif

#define _cffi_from_c_double PyFloat_FromDouble
#define _cffi_from_c_float PyFloat_FromDouble
#define _cffi_from_c_long PyInt_FromLong
#define _cffi_from_c_ulong PyLong_FromUnsignedLong
#define _cffi_from_c_longlong PyLong_FromLongLong
#define _cffi_from_c_ulonglong PyLong_FromUnsignedLongLong
#define _cffi_from_c__Bool PyBool_FromLong

#define _cffi_to_c_double PyFloat_AsDouble
#define _cffi_to_c_float PyFloat_AsDouble

#define _cffi_from_c_int_const(x)                                        \
    (((x) > 0) ?                                                         \
        ((unsigned long long)(x) <= (unsigned long long)LONG_MAX) ?      \
            PyInt_FromLong((long)(x)) :                                  \
            PyLong_FromUnsignedLongLong((unsigned long long)(x)) :       \
        ((long long)(x) >= (long long)LONG_MIN) ?                        \
            PyInt_FromLong((long)(x)) :                                  \
            PyLong_FromLongLong((long long)(x)))

#define _cffi_from_c_int(x, type)                                        \
    (((type)-1) > 0 ? /* unsigned */                                     \
        (sizeof(type) < sizeof(long) ?                                   \
            PyInt_FromLong((long)x) :                                    \
         sizeof(type) == sizeof(long) ?                                  \
            PyLong_FromUnsignedLong((unsigned long)x) :                  \
            PyLong_FromUnsignedLongLong((unsigned long long)x)) :        \
        (sizeof(type) <= sizeof(long) ?                                  \
            PyInt_FromLong((long)x) :                                    \
            PyLong_FromLongLong((long long)x)))

#define _cffi_to_c_int(o, type)                                          \
    ((type)(                                                             \
     sizeof(type) == 1 ? (((type)-1) > 0 ? (type)_cffi_to_c_u8(o)        \
                                         : (type)_cffi_to_c_i8(o)) :     \
     sizeof(type) == 2 ? (((type)-1) > 0 ? (type)_cffi_to_c_u16(o)       \
                                         : (type)_cffi_to_c_i16(o)) :    \
     sizeof(type) == 4 ? (((type)-1) > 0 ? (type)_cffi_to_c_u32(o)       \
                                         : (type)_cffi_to_c_i32(o)) :    \
     sizeof(type) == 8 ? (((type)-1) > 0 ? (type)_cffi_to_c_u64(o)       \
                                         : (type)_cffi_to_c_i64(o)) :    \
     (Py_FatalError("unsupported size for type " #type), (type)0)))

#define _cffi_to_c_i8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[1])
#define _cffi_to_c_u8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[2])
#define _cffi_to_c_i16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[3])
#define _cffi_to_c_u16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[4])
#define _cffi_to_c_i32                                                   \
                 ((int(*)(PyObject *))_cffi_exports[5])
#define _cffi_to_c_u32                                                   \
                 ((unsigned int(*)(PyObject *))_cffi_exports[6])
#define _cffi_to_c_i64                                                   \
                 ((long long(*)(PyObject *))_cffi_exports[7])
#define _cffi_to_c_u64                                                   \
                 ((unsigned long long(*)(PyObject *))_cffi_exports[8])
#define _cffi_to_c_char                                                  \
                 ((int(*)(PyObject *))_cffi_exports[9])
#define _cffi_from_c_pointer                                             \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[10])
#define _cffi_to_c_pointer                                               \
    ((char *(*)(PyObject *, CTypeDescrObject *))_cffi_exports[11])
#define _cffi_get_struct_layout                                          \
    ((PyObject *(*)(Py_ssize_t[]))_cffi_exports[12])
#define _cffi_restore_errno                                              \
    ((void(*)(void))_cffi_exports[13])
#define _cffi_save_errno                                                 \
    ((void(*)(void))_cffi_exports[14])
#define _cffi_from_c_char                                                \
    ((PyObject *(*)(char))_cffi_exports[15])
#define _cffi_from_c_deref                                               \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[16])
#define _cffi_to_c                                                       \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[17])
#define _cffi_from_c_struct                                              \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[18])
#define _cffi_to_c_wchar_t                                               \
    ((wchar_t(*)(PyObject *))_cffi_exports[19])
#define _cffi_from_c_wchar_t                                             \
    ((PyObject *(*)(wchar_t))_cffi_exports[20])
#define _cffi_to_c_long_double                                           \
    ((long double(*)(PyObject *))_cffi_exports[21])
#define _cffi_to_c__Bool                                                 \
    ((_Bool(*)(PyObject *))_cffi_exports[22])
#define _cffi_prepare_pointer_call_argument                              \
    ((Py_ssize_t(*)(CTypeDescrObject *, PyObject *, char **))_cffi_exports[23])
#define _cffi_convert_array_from_object                                  \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[24])
#define _CFFI_NUM_EXPORTS 25

typedef struct _ctypedescr CTypeDescrObject;

static void *_cffi_exports[_CFFI_NUM_EXPORTS];
static PyObject *_cffi_types, *_cffi_VerificationError;

static int _cffi_setup_custom(PyObject *lib);   /* forward */

static PyObject *_cffi_setup(PyObject *self, PyObject *args)
{
    PyObject *library;
    int was_alive = (_cffi_types != NULL);
    (void)self; /* unused */
    if (!PyArg_ParseTuple(args, "OOO", &_cffi_types, &_cffi_VerificationError,
                                       &library))
        return NULL;
    Py_INCREF(_cffi_types);
    Py_INCREF(_cffi_VerificationError);
    if (_cffi_setup_custom(library) < 0)
        return NULL;
    return PyBool_FromLong(was_alive);
}

union _cffi_union_alignment_u {
    unsigned char m_char;
    unsigned short m_short;
    unsigned int m_int;
    unsigned long m_long;
    unsigned long long m_longlong;
    float m_float;
    double m_double;
    long double m_longdouble;
};

struct _cffi_freeme_s {
    struct _cffi_freeme_s *next;
    union _cffi_union_alignment_u alignment;
};

#ifdef __GNUC__
  __attribute__((unused))
#endif
static int _cffi_convert_array_argument(CTypeDescrObject *ctptr, PyObject *arg,
                                        char **output_data, Py_ssize_t datasize,
                                        struct _cffi_freeme_s **freeme)
{
    char *p;
    if (datasize < 0)
        return -1;

    p = *output_data;
    if (p == NULL) {
        struct _cffi_freeme_s *fp = (struct _cffi_freeme_s *)PyObject_Malloc(
            offsetof(struct _cffi_freeme_s, alignment) + (size_t)datasize);
        if (fp == NULL)
            return -1;
        fp->next = *freeme;
        *freeme = fp;
        p = *output_data = (char *)&fp->alignment;
    }
    memset((void *)p, 0, (size_t)datasize);
    return _cffi_convert_array_from_object(p, ctptr, arg);
}

#ifdef __GNUC__
  __attribute__((unused))
#endif
static void _cffi_free_array_arguments(struct _cffi_freeme_s *freeme)
{
    do {
        void *p = (void *)freeme;
        freeme = freeme->next;
        PyObject_Free(p);
    } while (freeme != NULL);
}

static int _cffi_init(void)
{
    PyObject *module, *c_api_object = NULL;

    module = PyImport_ImportModule("_cffi_backend");
    if (module == NULL)
        goto failure;

    c_api_object = PyObject_GetAttrString(module, "_C_API");
    if (c_api_object == NULL)
        goto failure;
    if (!PyCapsule_CheckExact(c_api_object)) {
        PyErr_SetNone(PyExc_ImportError);
        goto failure;
    }
    memcpy(_cffi_exports, PyCapsule_GetPointer(c_api_object, "cffi"),
           _CFFI_NUM_EXPORTS * sizeof(void *));

    Py_DECREF(module);
    Py_DECREF(c_api_object);
    return 0;

  failure:
    Py_XDECREF(module);
    Py_XDECREF(c_api_object);
    return -1;
}

#define _cffi_type(num) ((CTypeDescrObject *)PyList_GET_ITEM(_cffi_types, num))

/**********/


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define _CFFI_INTERNAL
#include "../cffi/parse_c_type.h"


enum token_e {
    TOK_STAR='*',
    TOK_OPEN_PAREN='(',
    TOK_CLOSE_PAREN=')',
    TOK_OPEN_BRACKET='[',
    TOK_CLOSE_BRACKET=']',
    TOK_COMMA=',',

    TOK_START=256,
    TOK_END,
    TOK_ERROR,
    TOK_IDENTIFIER,
    TOK_INTEGER,
    TOK_DOTDOTDOT,

    /* keywords */
    TOK__BOOL,
    TOK_CHAR,
    TOK__COMPLEX,
    TOK_CONST,
    TOK_DOUBLE,
    TOK_ENUM,
    TOK_FLOAT,
    //TOK__IMAGINARY,
    TOK_INT,
    TOK_LONG,
    TOK_SHORT,
    TOK_SIGNED,
    TOK_STRUCT,
    TOK_UNION,
    TOK_UNSIGNED,
    TOK_VOID,
    TOK_VOLATILE,

    TOK_CDECL,
    TOK_STDCALL,
};

typedef struct {
    struct _cffi_parse_info_s *info;
    const char *input, *p;
    size_t size;              // the next token is at 'p' and of length 'size'
    enum token_e kind;
    _cffi_opcode_t *output;
    size_t output_index;
} token_t;

static int is_space(char x)
{
    return (x == ' ' || x == '\f' || x == '\n' || x == '\r' ||
            x == '\t' || x == '\v');
}

static int is_ident_first(char x)
{
    return (('A' <= x && x <= 'Z') || ('a' <= x && x <= 'z') || x == '_' ||
            x == '$');   /* '$' in names is supported here, for the struct
                            names invented by cparser */
}

static int is_digit(char x)
{
    return ('0' <= x && x <= '9');
}

static int is_hex_digit(char x)
{
    return (('0' <= x && x <= '9') ||
            ('A' <= x && x <= 'F') ||
            ('a' <= x && x <= 'f'));
}

static int is_ident_next(char x)
{
    return (is_ident_first(x) || is_digit(x));
}

static char get_following_char(token_t *tok)
{
    const char *p = tok->p + tok->size;
    if (tok->kind == TOK_ERROR)
        return 0;
    while (is_space(*p))
        p++;
    return *p;
}

static int number_of_commas(token_t *tok)
{
    const char *p = tok->p;
    int result = 0;
    int nesting = 0;
    while (1) {
        switch (*p++) {
        case ',': result += !nesting; break;
        case '(': nesting++; break;
        case ')': if ((--nesting) < 0) return result; break;
        case 0:   return result;
        default:  break;
        }
    }
}

static void next_token(token_t *tok)
{
    const char *p = tok->p + tok->size;
    if (tok->kind == TOK_ERROR)
        return;
    while (!is_ident_first(*p)) {
        if (is_space(*p)) {
            p++;
        }
        else if (is_digit(*p)) {
            tok->kind = TOK_INTEGER;
            tok->p = p;
            tok->size = 1;
            if (p[1] == 'x' || p[1] == 'X')
                tok->size = 2;
            while (is_hex_digit(p[tok->size]))
                tok->size++;
            return;
        }
        else if (p[0] == '.' && p[1] == '.' && p[2] == '.') {
            tok->kind = TOK_DOTDOTDOT;
            tok->p = p;
            tok->size = 3;
            return;
        }
        else if (*p) {
            tok->kind = *p;
            tok->p = p;
            tok->size = 1;
            return;
        }
        else {
            tok->kind = TOK_END;
            tok->p = p;
            tok->size = 0;
            return;
        }
    }
    tok->kind = TOK_IDENTIFIER;
    tok->p = p;
    tok->size = 1;
    while (is_ident_next(p[tok->size]))
        tok->size++;

    switch (*p) {
    case '_':
        if (tok->size == 5 && !memcmp(p, "_Bool", 5))  tok->kind = TOK__BOOL;
        if (tok->size == 7 && !memcmp(p,"__cdecl",7))  tok->kind = TOK_CDECL;
        if (tok->size == 9 && !memcmp(p,"__stdcall",9))tok->kind = TOK_STDCALL;
        if (tok->size == 8 && !memcmp(p,"_Complex",8)) tok->kind = TOK__COMPLEX;
        break;
    case 'c':
        if (tok->size == 4 && !memcmp(p, "char", 4))   tok->kind = TOK_CHAR;
        if (tok->size == 5 && !memcmp(p, "const", 5))  tok->kind = TOK_CONST;
        break;
    case 'd':
        if (tok->size == 6 && !memcmp(p, "double", 6)) tok->kind = TOK_DOUBLE;
        break;
    case 'e':
        if (tok->size == 4 && !memcmp(p, "enum", 4))   tok->kind = TOK_ENUM;
        break;
    case 'f':
        if (tok->size == 5 && !memcmp(p, "float", 5))  tok->kind = TOK_FLOAT;
        break;
    case 'i':
        if (tok->size == 3 && !memcmp(p, "int", 3))    tok->kind = TOK_INT;
        break;
    case 'l':
        if (tok->size == 4 && !memcmp(p, "long", 4))   tok->kind = TOK_LONG;
        break;
    case 's':
        if (tok->size == 5 && !memcmp(p, "short", 5))  tok->kind = TOK_SHORT;
        if (tok->size == 6 && !memcmp(p, "signed", 6)) tok->kind = TOK_SIGNED;
        if (tok->size == 6 && !memcmp(p, "struct", 6)) tok->kind = TOK_STRUCT;
        break;
    case 'u':
        if (tok->size == 5 && !memcmp(p, "union", 5))  tok->kind = TOK_UNION;
        if (tok->size == 8 && !memcmp(p,"unsigned",8)) tok->kind = TOK_UNSIGNED;
        break;
    case 'v':
        if (tok->size == 4 && !memcmp(p, "void", 4))   tok->kind = TOK_VOID;
        if (tok->size == 8 && !memcmp(p,"volatile",8)) tok->kind = TOK_VOLATILE;
        break;
    }
}

static int parse_error(token_t *tok, const char *msg)
{
    if (tok->kind != TOK_ERROR) {
        tok->kind = TOK_ERROR;
        tok->info->error_location = tok->p - tok->input;
        tok->info->error_message = msg;
    }
    return -1;
}

static int write_ds(token_t *tok, _cffi_opcode_t ds)
{
    size_t index = tok->output_index;
    if (index >= tok->info->output_size) {
        parse_error(tok, "internal type complexity limit reached");
        return -1;
    }
    tok->output[index] = ds;
    tok->output_index = index + 1;
    return index;
}

#define MAX_SSIZE_T  (((size_t)-1) >> 1)

static int parse_complete(token_t *tok);
static const char *get_common_type(const char *search, size_t search_len);
static int parse_common_type_replacement(token_t *tok, const char *replacement);

static int parse_sequel(token_t *tok, int outer)
{
    /* Emit opcodes for the "sequel", which is the optional part of a
       type declaration that follows the type name, i.e. everything
       with '*', '[ ]', '( )'.  Returns the entry point index pointing
       the innermost opcode (the one that corresponds to the complete
       type).  The 'outer' argument is the index of the opcode outside
       this "sequel".
     */
    int check_for_grouping, abi=0;
    _cffi_opcode_t result, *p_current;

 header:
    switch (tok->kind) {
    case TOK_STAR:
        outer = write_ds(tok, _CFFI_OP(_CFFI_OP_POINTER, outer));
        next_token(tok);
        goto header;
    case TOK_CONST:
        /* ignored for now */
        next_token(tok);
        goto header;
    case TOK_VOLATILE:
        /* ignored for now */
        next_token(tok);
        goto header;
    case TOK_CDECL:
    case TOK_STDCALL:
        /* must be in a function; checked below */
        abi = tok->kind;
        next_token(tok);
        goto header;
    default:
        break;
    }

    check_for_grouping = 1;
    if (tok->kind == TOK_IDENTIFIER) {
        next_token(tok);    /* skip a potential variable name */
        check_for_grouping = 0;
    }

    result = 0;
    p_current = &result;

    while (tok->kind == TOK_OPEN_PAREN) {
        next_token(tok);

        if (tok->kind == TOK_CDECL || tok->kind == TOK_STDCALL) {
            abi = tok->kind;
            next_token(tok);
        }

        if ((check_for_grouping--) == 1 && (tok->kind == TOK_STAR ||
                                            tok->kind == TOK_CONST ||
                                            tok->kind == TOK_VOLATILE ||
                                            tok->kind == TOK_OPEN_BRACKET)) {
            /* just parentheses for grouping.  Use a OP_NOOP to simplify */
            int x;
            assert(p_current == &result);
            x = tok->output_index;
            p_current = tok->output + x;

            write_ds(tok, _CFFI_OP(_CFFI_OP_NOOP, 0));

            x = parse_sequel(tok, x);
            result = _CFFI_OP(_CFFI_GETOP(0), x);
        }
        else {
            /* function type */
            int arg_total, base_index, arg_next, flags=0;

            if (abi == TOK_STDCALL) {
                flags = 2;
                /* note that an ellipsis below will overwrite this flags,
                   which is the goal: variadic functions are always cdecl */
            }
            abi = 0;

            if (tok->kind == TOK_VOID && get_following_char(tok) == ')') {
                next_token(tok);
            }

            /* (over-)estimate 'arg_total'.  May return 1 when it is really 0 */
            arg_total = number_of_commas(tok) + 1;

            *p_current = _CFFI_OP(_CFFI_GETOP(*p_current), tok->output_index);
            p_current = tok->output + tok->output_index;

            base_index = write_ds(tok, _CFFI_OP(_CFFI_OP_FUNCTION, 0));
            if (base_index < 0)
                return -1;
            /* reserve (arg_total + 1) slots for the arguments and the
               final FUNCTION_END */
            for (arg_next = 0; arg_next <= arg_total; arg_next++)
                if (write_ds(tok, _CFFI_OP(0, 0)) < 0)
                    return -1;

            arg_next = base_index + 1;

            if (tok->kind != TOK_CLOSE_PAREN) {
                while (1) {
                    int arg;
                    _cffi_opcode_t oarg;

                    if (tok->kind == TOK_DOTDOTDOT) {
                        flags = 1;   /* ellipsis */
                        next_token(tok);
                        break;
                    }
                    arg = parse_complete(tok);
                    switch (_CFFI_GETOP(tok->output[arg])) {
                    case _CFFI_OP_ARRAY:
                    case _CFFI_OP_OPEN_ARRAY:
                        arg = _CFFI_GETARG(tok->output[arg]);
                        /* fall-through */
                    case _CFFI_OP_FUNCTION:
                        oarg = _CFFI_OP(_CFFI_OP_POINTER, arg);
                        break;
                    default:
                        oarg = _CFFI_OP(_CFFI_OP_NOOP, arg);
                        break;
                    }
                    assert(arg_next - base_index <= arg_total);
                    tok->output[arg_next++] = oarg;
                    if (tok->kind != TOK_COMMA)
                        break;
                    next_token(tok);
                }
            }
            tok->output[arg_next] = _CFFI_OP(_CFFI_OP_FUNCTION_END, flags);
        }

        if (tok->kind != TOK_CLOSE_PAREN)
            return parse_error(tok, "expected ')'");
        next_token(tok);
    }

    if (abi != 0)
        return parse_error(tok, "expected '('");

    while (tok->kind == TOK_OPEN_BRACKET) {
        *p_current = _CFFI_OP(_CFFI_GETOP(*p_current), tok->output_index);
        p_current = tok->output + tok->output_index;

        next_token(tok);
        if (tok->kind != TOK_CLOSE_BRACKET) {
            size_t length;
            int gindex;
            char *endptr;

            switch (tok->kind) {

            case TOK_INTEGER:
                errno = 0;
                if (sizeof(length) > sizeof(unsigned long)) {
#ifdef MS_WIN32
# ifdef _WIN64
                    length = _strtoui64(tok->p, &endptr, 0);
# else
                    abort();  /* unreachable */
# endif
#else
                    length = strtoull(tok->p, &endptr, 0);
#endif
                }
                else
                    length = strtoul(tok->p, &endptr, 0);
                if (endptr != tok->p + tok->size)
                    return parse_error(tok, "invalid number");
                if (errno == ERANGE || length > MAX_SSIZE_T)
                    return parse_error(tok, "number too large");
                break;

            case TOK_IDENTIFIER:
                gindex = search_in_globals(tok->info->ctx, tok->p, tok->size);
                if (gindex >= 0) {
                    const struct _cffi_global_s *g;
                    g = &tok->info->ctx->globals[gindex];
                    if (_CFFI_GETOP(g->type_op) == _CFFI_OP_CONSTANT_INT ||
                        _CFFI_GETOP(g->type_op) == _CFFI_OP_ENUM) {
                        int neg;
                        struct _cffi_getconst_s gc;
                        gc.ctx = tok->info->ctx;
                        gc.gindex = gindex;
                        neg = ((int(*)(struct _cffi_getconst_s*))g->address)
                            (&gc);
                        if (neg == 0 && gc.value > MAX_SSIZE_T)
                            return parse_error(tok,
                                               "integer constant too large");
                        if (neg == 0 || gc.value == 0) {
                            length = (size_t)gc.value;
                            break;
                        }
                        if (neg != 1)
                            return parse_error(tok, "disagreement about"
                                               " this constant's value");
                    }
                }
                /* fall-through to the default case */
            default:
                return parse_error(tok, "expected a positive integer constant");
            }

            next_token(tok);

            write_ds(tok, _CFFI_OP(_CFFI_OP_ARRAY, 0));
            write_ds(tok, (_cffi_opcode_t)length);
        }
        else
            write_ds(tok, _CFFI_OP(_CFFI_OP_OPEN_ARRAY, 0));

        if (tok->kind != TOK_CLOSE_BRACKET)
            return parse_error(tok, "expected ']'");
        next_token(tok);
    }

    *p_current = _CFFI_OP(_CFFI_GETOP(*p_current), outer);
    return _CFFI_GETARG(result);
}

static int search_sorted(const char *const *base,
                         size_t item_size, int array_len,
                         const char *search, size_t search_len)
{
    int left = 0, right = array_len;
    const char *baseptr = (const char *)base;

    while (left < right) {
        int middle = (left + right) / 2;
        const char *src = *(const char *const *)(baseptr + middle * item_size);
        int diff = strncmp(src, search, search_len);
        if (diff == 0 && src[search_len] == '\0')
            return middle;
        else if (diff >= 0)
            right = middle;
        else
            left = middle + 1;
    }
    return -1;
}

#define MAKE_SEARCH_FUNC(FIELD)                                         \
  static                                                                \
  int search_in_##FIELD(const struct _cffi_type_context_s *ctx,         \
                        const char *search, size_t search_len)          \
  {                                                                     \
      return search_sorted(&ctx->FIELD->name, sizeof(*ctx->FIELD),      \
                           ctx->num_##FIELD, search, search_len);       \
  }

MAKE_SEARCH_FUNC(globals)
MAKE_SEARCH_FUNC(struct_unions)
MAKE_SEARCH_FUNC(typenames)
MAKE_SEARCH_FUNC(enums)

#undef MAKE_SEARCH_FUNC


static
int search_standard_typename(const char *p, size_t size)
{
    if (size < 6 || p[size-2] != '_' || p[size-1] != 't')
        return -1;

    switch (p[4]) {

    case '1':
        if (size == 8 && !memcmp(p, "uint16", 6)) return _CFFI_PRIM_UINT16;
        if (size == 8 && !memcmp(p, "char16", 6)) return _CFFI_PRIM_CHAR16;
        break;

    case '2':
        if (size == 7 && !memcmp(p, "int32", 5)) return _CFFI_PRIM_INT32;
        break;

    case '3':
        if (size == 8 && !memcmp(p, "uint32", 6)) return _CFFI_PRIM_UINT32;
        if (size == 8 && !memcmp(p, "char32", 6)) return _CFFI_PRIM_CHAR32;
        break;

    case '4':
        if (size == 7 && !memcmp(p, "int64", 5)) return _CFFI_PRIM_INT64;
        break;

    case '6':
        if (size == 8 && !memcmp(p, "uint64", 6)) return _CFFI_PRIM_UINT64;
        if (size == 7 && !memcmp(p, "int16", 5)) return _CFFI_PRIM_INT16;
        break;

    case '8':
        if (size == 7 && !memcmp(p, "uint8", 5)) return _CFFI_PRIM_UINT8;
        break;

    case 'a':
        if (size == 8 && !memcmp(p, "intmax", 6)) return _CFFI_PRIM_INTMAX;
        break;

    case 'e':
        if (size == 7 && !memcmp(p, "ssize", 5)) return _CFFI_PRIM_SSIZE;
        break;

    case 'f':
        if (size == 11 && !memcmp(p, "int_fast8",   9)) return _CFFI_PRIM_INT_FAST8;
        if (size == 12 && !memcmp(p, "int_fast16", 10)) return _CFFI_PRIM_INT_FAST16;
        if (size == 12 && !memcmp(p, "int_fast32", 10)) return _CFFI_PRIM_INT_FAST32;
        if (size == 12 && !memcmp(p, "int_fast64", 10)) return _CFFI_PRIM_INT_FAST64;
        break;

    case 'i':
        if (size == 9 && !memcmp(p, "ptrdiff", 7)) return _CFFI_PRIM_PTRDIFF;
        if (size == 21 && !memcmp(p, "_cffi_float_complex", 19)) return _CFFI_PRIM_FLOATCOMPLEX;
        if (size == 22 && !memcmp(p, "_cffi_double_complex", 20)) return _CFFI_PRIM_DOUBLECOMPLEX;
        break;

    case 'l':
        if (size == 12 && !memcmp(p, "int_least8",  10)) return _CFFI_PRIM_INT_LEAST8;
        if (size == 13 && !memcmp(p, "int_least16", 11)) return _CFFI_PRIM_INT_LEAST16;
        if (size == 13 && !memcmp(p, "int_least32", 11)) return _CFFI_PRIM_INT_LEAST32;
        if (size == 13 && !memcmp(p, "int_least64", 11)) return _CFFI_PRIM_INT_LEAST64;
        break;

    case 'm':
        if (size == 9 && !memcmp(p, "uintmax", 7)) return _CFFI_PRIM_UINTMAX;
        break;

    case 'p':
        if (size == 9 && !memcmp(p, "uintptr", 7)) return _CFFI_PRIM_UINTPTR;
        break;

    case 'r':
        if (size == 7 && !memcmp(p, "wchar", 5)) return _CFFI_PRIM_WCHAR;
        break;

    case 't':
        if (size == 8 && !memcmp(p, "intptr", 6)) return _CFFI_PRIM_INTPTR;
        break;

    case '_':
        if (size == 6 && !memcmp(p, "size", 4)) return _CFFI_PRIM_SIZE;
        if (size == 6 && !memcmp(p, "int8", 4)) return _CFFI_PRIM_INT8;
        if (size >= 12) {
            switch (p[10]) {
            case '1':
                if (size == 14 && !memcmp(p, "uint_least16", 12)) return _CFFI_PRIM_UINT_LEAST16;
                break;
            case '2':
                if (size == 13 && !memcmp(p, "uint_fast32", 11)) return _CFFI_PRIM_UINT_FAST32;
                break;
            case '3':
                if (size == 14 && !memcmp(p, "uint_least32", 12)) return _CFFI_PRIM_UINT_LEAST32;
                break;
            case '4':
                if (size == 13 && !memcmp(p, "uint_fast64", 11)) return _CFFI_PRIM_UINT_FAST64;
                break;
            case '6':
                if (size == 14 && !memcmp(p, "uint_least64", 12)) return _CFFI_PRIM_UINT_LEAST64;
                if (size == 13 && !memcmp(p, "uint_fast16", 11)) return _CFFI_PRIM_UINT_FAST16;
                break;
            case '8':
                if (size == 13 && !memcmp(p, "uint_least8", 11)) return _CFFI_PRIM_UINT_LEAST8;
                break;
            case '_':
                if (size == 12 && !memcmp(p, "uint_fast8", 10)) return _CFFI_PRIM_UINT_FAST8;
                break;
            default:
                break;
            }
        }
        break;

    default:
        break;
    }
    return -1;
}


static int parse_complete(token_t *tok)
{
    unsigned int t0;
    _cffi_opcode_t t1;
    _cffi_opcode_t t1complex;
    int modifiers_length, modifiers_sign;

 qualifiers:
    switch (tok->kind) {
    case TOK_CONST:
        /* ignored for now */
        next_token(tok);
        goto qualifiers;
    case TOK_VOLATILE:
        /* ignored for now */
        next_token(tok);
        goto qualifiers;
    default:
        ;
    }

    modifiers_length = 0;
    modifiers_sign = 0;
 modifiers:
    switch (tok->kind) {

    case TOK_SHORT:
        if (modifiers_length != 0)
            return parse_error(tok, "'short' after another 'short' or 'long'");
        modifiers_length--;
        next_token(tok);
        goto modifiers;

    case TOK_LONG:
        if (modifiers_length < 0)
            return parse_error(tok, "'long' after 'short'");
        if (modifiers_length >= 2)
            return parse_error(tok, "'long long long' is too long");
        modifiers_length++;
        next_token(tok);
        goto modifiers;

    case TOK_SIGNED:
        if (modifiers_sign)
            return parse_error(tok, "multiple 'signed' or 'unsigned'");
        modifiers_sign++;
        next_token(tok);
        goto modifiers;

    case TOK_UNSIGNED:
        if (modifiers_sign)
            return parse_error(tok, "multiple 'signed' or 'unsigned'");
        modifiers_sign--;
        next_token(tok);
        goto modifiers;

    default:
        break;
    }

    t1complex = 0;

    if (modifiers_length || modifiers_sign) {

        switch (tok->kind) {

        case TOK_VOID:
        case TOK__BOOL:
        case TOK_FLOAT:
        case TOK_STRUCT:
        case TOK_UNION:
        case TOK_ENUM:
        case TOK__COMPLEX:
            return parse_error(tok, "invalid combination of types");

        case TOK_DOUBLE:
            if (modifiers_sign != 0 || modifiers_length != 1)
                return parse_error(tok, "invalid combination of types");
            next_token(tok);
            t0 = _CFFI_PRIM_LONGDOUBLE;
            break;

        case TOK_CHAR:
            if (modifiers_length != 0)
                return parse_error(tok, "invalid combination of types");
            modifiers_length = -2;
            /* fall-through */
        case TOK_INT:
            next_token(tok);
            /* fall-through */
        default:
            if (modifiers_sign >= 0)
                switch (modifiers_length) {
                case -2: t0 = _CFFI_PRIM_SCHAR; break;
                case -1: t0 = _CFFI_PRIM_SHORT; break;
                case 1:  t0 = _CFFI_PRIM_LONG; break;
                case 2:  t0 = _CFFI_PRIM_LONGLONG; break;
                default: t0 = _CFFI_PRIM_INT; break;
                }
            else
                switch (modifiers_length) {
                case -2: t0 = _CFFI_PRIM_UCHAR; break;
                case -1: t0 = _CFFI_PRIM_USHORT; break;
                case 1:  t0 = _CFFI_PRIM_ULONG; break;
                case 2:  t0 = _CFFI_PRIM_ULONGLONG; break;
                default: t0 = _CFFI_PRIM_UINT; break;
                }
        }
        t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, t0);
    }
    else {
        switch (tok->kind) {
        case TOK_INT:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_INT);
            break;
        case TOK_CHAR:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_CHAR);
            break;
        case TOK_VOID:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_VOID);
            break;
        case TOK__BOOL:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_BOOL);
            break;
        case TOK_FLOAT:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_FLOAT);
            t1complex = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_FLOATCOMPLEX);
            break;
        case TOK_DOUBLE:
            t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_DOUBLE);
            t1complex = _CFFI_OP(_CFFI_OP_PRIMITIVE, _CFFI_PRIM_DOUBLECOMPLEX);
            break;
        case TOK_IDENTIFIER:
        {
            const char *replacement;
            int n = search_in_typenames(tok->info->ctx, tok->p, tok->size);
            if (n >= 0) {
                t1 = _CFFI_OP(_CFFI_OP_TYPENAME, n);
                break;
            }
            n = search_standard_typename(tok->p, tok->size);
            if (n >= 0) {
                t1 = _CFFI_OP(_CFFI_OP_PRIMITIVE, n);
                break;
            }
            replacement = get_common_type(tok->p, tok->size);
            if (replacement != NULL) {
                n = parse_common_type_replacement(tok, replacement);
                if (n < 0)
                    return parse_error(tok, "internal error, please report!");
                t1 = _CFFI_OP(_CFFI_OP_NOOP, n);
                break;
            }
            return parse_error(tok, "undefined type name");
        }
        case TOK_STRUCT:
        case TOK_UNION:
        {
            int n, kind = tok->kind;
            next_token(tok);
            if (tok->kind != TOK_IDENTIFIER)
                return parse_error(tok, "struct or union name expected");

            n = search_in_struct_unions(tok->info->ctx, tok->p, tok->size);
            if (n < 0) {
                if (kind == TOK_STRUCT && tok->size == 8 &&
                        !memcmp(tok->p, "_IO_FILE", 8))
                    n = _CFFI__IO_FILE_STRUCT;
                else
                    return parse_error(tok, "undefined struct/union name");
            }
            else if (((tok->info->ctx->struct_unions[n].flags & _CFFI_F_UNION)
                      != 0) ^ (kind == TOK_UNION))
                return parse_error(tok, "wrong kind of tag: struct vs union");

            t1 = _CFFI_OP(_CFFI_OP_STRUCT_UNION, n);
            break;
        }
        case TOK_ENUM:
        {
            int n;
            next_token(tok);
            if (tok->kind != TOK_IDENTIFIER)
                return parse_error(tok, "enum name expected");

            n = search_in_enums(tok->info->ctx, tok->p, tok->size);
            if (n < 0)
                return parse_error(tok, "undefined enum name");

            t1 = _CFFI_OP(_CFFI_OP_ENUM, n);
            break;
        }
        default:
            return parse_error(tok, "identifier expected");
        }
        next_token(tok);
    }
    if (tok->kind == TOK__COMPLEX)
    {
        if (t1complex == 0)
            return parse_error(tok, "_Complex type combination unsupported");
        t1 = t1complex;
        next_token(tok);
    }

    return parse_sequel(tok, write_ds(tok, t1));
}


static
int parse_c_type_from(struct _cffi_parse_info_s *info, size_t *output_index,
                      const char *input)
{
    int result;
    token_t token;

    token.info = info;
    token.kind = TOK_START;
    token.input = input;
    token.p = input;
    token.size = 0;
    token.output = info->output;
    token.output_index = *output_index;

    next_token(&token);
    result = parse_complete(&token);

    *output_index = token.output_index;
    if (token.kind != TOK_END)
        return parse_error(&token, "unexpected symbol");
    return result;
}

static
int parse_c_type(struct _cffi_parse_info_s *info, const char *input)
{
    size_t output_index = 0;
    return parse_c_type_from(info, &output_index, input);
}

static
int parse_common_type_replacement(token_t *tok, const char *replacement)
{
    return parse_c_type_from(tok->info, &tok->output_index, replacement);
}

static const char *get_common_type(const char *search, size_t search_len) {
    return NULL;
}


static PyObject *
_cffi_f_parse_c_type(PyObject *self, PyObject *args)
{
  struct _cffi_parse_info_s * x0;
  char const * x1;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  int result;
  PyObject *pyresult;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_ParseTuple(args, "OO:parse_c_type", &arg0, &arg1))
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(0), arg0, (char **)&x0);
  if (datasize != 0) {
    x0 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(0), arg0, (char **)&x0,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(1), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = parse_c_type(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  pyresult = _cffi_from_c_int(result, int);
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  return pyresult;
}

static PyObject *
_cffi_f_search_in_globals(PyObject *self, PyObject *args)
{
  struct _cffi_type_context_s const * x0;
  char const * x1;
  size_t x2;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  int result;
  PyObject *pyresult;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;

  if (!PyArg_ParseTuple(args, "OOO:search_in_globals", &arg0, &arg1, &arg2))
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg0, (char **)&x0);
  if (datasize != 0) {
    x0 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg0, (char **)&x0,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(1), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  x2 = _cffi_to_c_int(arg2, size_t);
  if (x2 == (size_t)-1 && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = search_in_globals(x0, x1, x2); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  pyresult = _cffi_from_c_int(result, int);
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  return pyresult;
}

static PyObject *
_cffi_f_search_in_struct_unions(PyObject *self, PyObject *args)
{
  struct _cffi_type_context_s const * x0;
  char const * x1;
  size_t x2;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  int result;
  PyObject *pyresult;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;

  if (!PyArg_ParseTuple(args, "OOO:search_in_struct_unions", &arg0, &arg1, &arg2))
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg0, (char **)&x0);
  if (datasize != 0) {
    x0 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg0, (char **)&x0,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(1), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  x2 = _cffi_to_c_int(arg2, size_t);
  if (x2 == (size_t)-1 && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = search_in_struct_unions(x0, x1, x2); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  pyresult = _cffi_from_c_int(result, int);
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  return pyresult;
}

static int _cffi_const__CFFI_F_CHECK_FIELDS(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_F_CHECK_FIELDS);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_F_CHECK_FIELDS", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return ((void)lib,0);
}

static int _cffi_const__CFFI_F_EXTERNAL(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_F_EXTERNAL);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_F_EXTERNAL", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_F_CHECK_FIELDS(lib);
}

static int _cffi_const__CFFI_F_OPAQUE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_F_OPAQUE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_F_OPAQUE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_F_EXTERNAL(lib);
}

static int _cffi_const__CFFI_F_PACKED(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_F_PACKED);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_F_PACKED", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_F_OPAQUE(lib);
}

static int _cffi_const__CFFI_F_UNION(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_F_UNION);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_F_UNION", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_F_PACKED(lib);
}

static int _cffi_const__CFFI_OP_ARRAY(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_ARRAY);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_ARRAY", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_F_UNION(lib);
}

static int _cffi_const__CFFI_OP_BITFIELD(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_BITFIELD);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_BITFIELD", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_ARRAY(lib);
}

static int _cffi_const__CFFI_OP_CONSTANT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_CONSTANT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_CONSTANT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_BITFIELD(lib);
}

static int _cffi_const__CFFI_OP_CONSTANT_INT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_CONSTANT_INT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_CONSTANT_INT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_CONSTANT(lib);
}

static int _cffi_const__CFFI_OP_CPYTHON_BLTN_N(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_CPYTHON_BLTN_N);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_CPYTHON_BLTN_N", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_CONSTANT_INT(lib);
}

static int _cffi_const__CFFI_OP_CPYTHON_BLTN_O(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_CPYTHON_BLTN_O);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_CPYTHON_BLTN_O", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_CPYTHON_BLTN_N(lib);
}

static int _cffi_const__CFFI_OP_CPYTHON_BLTN_V(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_CPYTHON_BLTN_V);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_CPYTHON_BLTN_V", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_CPYTHON_BLTN_O(lib);
}

static int _cffi_const__CFFI_OP_DLOPEN_CONST(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_DLOPEN_CONST);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_DLOPEN_CONST", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_CPYTHON_BLTN_V(lib);
}

static int _cffi_const__CFFI_OP_DLOPEN_FUNC(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_DLOPEN_FUNC);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_DLOPEN_FUNC", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_DLOPEN_CONST(lib);
}

static int _cffi_const__CFFI_OP_ENUM(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_ENUM);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_ENUM", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_DLOPEN_FUNC(lib);
}

static int _cffi_const__CFFI_OP_EXTERN_PYTHON(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_EXTERN_PYTHON);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_EXTERN_PYTHON", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_ENUM(lib);
}

static int _cffi_const__CFFI_OP_FUNCTION(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_FUNCTION);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_FUNCTION", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_EXTERN_PYTHON(lib);
}

static int _cffi_const__CFFI_OP_FUNCTION_END(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_FUNCTION_END);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_FUNCTION_END", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_FUNCTION(lib);
}

static int _cffi_const__CFFI_OP_GLOBAL_VAR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_GLOBAL_VAR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_GLOBAL_VAR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_FUNCTION_END(lib);
}

static int _cffi_const__CFFI_OP_GLOBAL_VAR_F(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_GLOBAL_VAR_F);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_GLOBAL_VAR_F", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_GLOBAL_VAR(lib);
}

static int _cffi_const__CFFI_OP_NOOP(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_NOOP);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_NOOP", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_GLOBAL_VAR_F(lib);
}

static int _cffi_const__CFFI_OP_OPEN_ARRAY(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_OPEN_ARRAY);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_OPEN_ARRAY", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_NOOP(lib);
}

static int _cffi_const__CFFI_OP_POINTER(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_POINTER);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_POINTER", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_OPEN_ARRAY(lib);
}

static int _cffi_const__CFFI_OP_PRIMITIVE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_PRIMITIVE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_PRIMITIVE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_POINTER(lib);
}

static int _cffi_const__CFFI_OP_STRUCT_UNION(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_STRUCT_UNION);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_STRUCT_UNION", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_PRIMITIVE(lib);
}

static int _cffi_const__CFFI_OP_TYPENAME(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_OP_TYPENAME);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_OP_TYPENAME", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_STRUCT_UNION(lib);
}

static int _cffi_const__CFFI_PRIM_BOOL(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_BOOL);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_BOOL", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_OP_TYPENAME(lib);
}

static int _cffi_const__CFFI_PRIM_CHAR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_CHAR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_CHAR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_BOOL(lib);
}

static int _cffi_const__CFFI_PRIM_CHAR16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_CHAR16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_CHAR16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_CHAR(lib);
}

static int _cffi_const__CFFI_PRIM_CHAR32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_CHAR32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_CHAR32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_CHAR16(lib);
}

static int _cffi_const__CFFI_PRIM_DOUBLE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_DOUBLE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_DOUBLE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_CHAR32(lib);
}

static int _cffi_const__CFFI_PRIM_DOUBLECOMPLEX(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_DOUBLECOMPLEX);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_DOUBLECOMPLEX", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_DOUBLE(lib);
}

static int _cffi_const__CFFI_PRIM_FLOAT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_FLOAT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_FLOAT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_DOUBLECOMPLEX(lib);
}

static int _cffi_const__CFFI_PRIM_FLOATCOMPLEX(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_FLOATCOMPLEX);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_FLOATCOMPLEX", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_FLOAT(lib);
}

static int _cffi_const__CFFI_PRIM_INT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_FLOATCOMPLEX(lib);
}

static int _cffi_const__CFFI_PRIM_INT16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT(lib);
}

static int _cffi_const__CFFI_PRIM_INT32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT16(lib);
}

static int _cffi_const__CFFI_PRIM_INT64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT32(lib);
}

static int _cffi_const__CFFI_PRIM_INT8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT64(lib);
}

static int _cffi_const__CFFI_PRIM_INTMAX(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INTMAX);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INTMAX", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT8(lib);
}

static int _cffi_const__CFFI_PRIM_INTPTR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INTPTR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INTPTR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INTMAX(lib);
}

static int _cffi_const__CFFI_PRIM_INT_FAST16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_FAST16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_FAST16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INTPTR(lib);
}

static int _cffi_const__CFFI_PRIM_INT_FAST32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_FAST32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_FAST32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_FAST16(lib);
}

static int _cffi_const__CFFI_PRIM_INT_FAST64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_FAST64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_FAST64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_FAST32(lib);
}

static int _cffi_const__CFFI_PRIM_INT_FAST8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_FAST8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_FAST8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_FAST64(lib);
}

static int _cffi_const__CFFI_PRIM_INT_LEAST16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_LEAST16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_LEAST16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_FAST8(lib);
}

static int _cffi_const__CFFI_PRIM_INT_LEAST32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_LEAST32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_LEAST32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_LEAST16(lib);
}

static int _cffi_const__CFFI_PRIM_INT_LEAST64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_LEAST64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_LEAST64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_LEAST32(lib);
}

static int _cffi_const__CFFI_PRIM_INT_LEAST8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_INT_LEAST8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_INT_LEAST8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_LEAST64(lib);
}

static int _cffi_const__CFFI_PRIM_LONG(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_LONG);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_LONG", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_INT_LEAST8(lib);
}

static int _cffi_const__CFFI_PRIM_LONGDOUBLE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_LONGDOUBLE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_LONGDOUBLE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_LONG(lib);
}

static int _cffi_const__CFFI_PRIM_LONGLONG(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_LONGLONG);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_LONGLONG", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_LONGDOUBLE(lib);
}

static int _cffi_const__CFFI_PRIM_PTRDIFF(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_PTRDIFF);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_PTRDIFF", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_LONGLONG(lib);
}

static int _cffi_const__CFFI_PRIM_SCHAR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_SCHAR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_SCHAR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_PTRDIFF(lib);
}

static int _cffi_const__CFFI_PRIM_SHORT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_SHORT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_SHORT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_SCHAR(lib);
}

static int _cffi_const__CFFI_PRIM_SIZE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_SIZE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_SIZE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_SHORT(lib);
}

static int _cffi_const__CFFI_PRIM_SSIZE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_SSIZE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_SSIZE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_SIZE(lib);
}

static int _cffi_const__CFFI_PRIM_UCHAR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UCHAR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UCHAR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_SSIZE(lib);
}

static int _cffi_const__CFFI_PRIM_UINT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UCHAR(lib);
}

static int _cffi_const__CFFI_PRIM_UINT16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT(lib);
}

static int _cffi_const__CFFI_PRIM_UINT32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT16(lib);
}

static int _cffi_const__CFFI_PRIM_UINT64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT32(lib);
}

static int _cffi_const__CFFI_PRIM_UINT8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT64(lib);
}

static int _cffi_const__CFFI_PRIM_UINTMAX(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINTMAX);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINTMAX", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT8(lib);
}

static int _cffi_const__CFFI_PRIM_UINTPTR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINTPTR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINTPTR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINTMAX(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_FAST16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_FAST16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_FAST16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINTPTR(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_FAST32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_FAST32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_FAST32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_FAST16(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_FAST64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_FAST64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_FAST64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_FAST32(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_FAST8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_FAST8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_FAST8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_FAST64(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_LEAST16(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_LEAST16);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_LEAST16", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_FAST8(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_LEAST32(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_LEAST32);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_LEAST32", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_LEAST16(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_LEAST64(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_LEAST64);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_LEAST64", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_LEAST32(lib);
}

static int _cffi_const__CFFI_PRIM_UINT_LEAST8(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_UINT_LEAST8);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_UINT_LEAST8", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_LEAST64(lib);
}

static int _cffi_const__CFFI_PRIM_ULONG(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_ULONG);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_ULONG", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_UINT_LEAST8(lib);
}

static int _cffi_const__CFFI_PRIM_ULONGLONG(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_ULONGLONG);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_ULONGLONG", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_ULONG(lib);
}

static int _cffi_const__CFFI_PRIM_USHORT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_USHORT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_USHORT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_ULONGLONG(lib);
}

static int _cffi_const__CFFI_PRIM_VOID(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_VOID);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_VOID", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_USHORT(lib);
}

static int _cffi_const__CFFI_PRIM_WCHAR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI_PRIM_WCHAR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI_PRIM_WCHAR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_VOID(lib);
}

static int _cffi_const__CFFI__IO_FILE_STRUCT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI__IO_FILE_STRUCT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI__IO_FILE_STRUCT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI_PRIM_WCHAR(lib);
}

static int _cffi_const__CFFI__NUM_PRIM(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI__NUM_PRIM);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI__NUM_PRIM", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI__IO_FILE_STRUCT(lib);
}

static int _cffi_const__CFFI__UNKNOWN_FLOAT_PRIM(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI__UNKNOWN_FLOAT_PRIM);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI__UNKNOWN_FLOAT_PRIM", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI__NUM_PRIM(lib);
}

static int _cffi_const__CFFI__UNKNOWN_LONG_DOUBLE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI__UNKNOWN_LONG_DOUBLE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI__UNKNOWN_LONG_DOUBLE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI__UNKNOWN_FLOAT_PRIM(lib);
}

static int _cffi_const__CFFI__UNKNOWN_PRIM(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(_CFFI__UNKNOWN_PRIM);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "_CFFI__UNKNOWN_PRIM", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const__CFFI__UNKNOWN_LONG_DOUBLE(lib);
}

static void _cffi_check_struct__cffi_enum_s(struct _cffi_enum_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  (void)((p->type_index) << 1);
  (void)((p->type_prim) << 1);
  { char const * *tmp = &p->enumerators; (void)tmp; }
}
static PyObject *
_cffi_layout_struct__cffi_enum_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_enum_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_enum_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_enum_s, name),
    sizeof(((struct _cffi_enum_s *)0)->name),
    offsetof(struct _cffi_enum_s, type_index),
    sizeof(((struct _cffi_enum_s *)0)->type_index),
    offsetof(struct _cffi_enum_s, type_prim),
    sizeof(((struct _cffi_enum_s *)0)->type_prim),
    offsetof(struct _cffi_enum_s, enumerators),
    sizeof(((struct _cffi_enum_s *)0)->enumerators),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_enum_s(0);
}

static void _cffi_check_struct__cffi_externpy_s(struct _cffi_externpy_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  (void)((p->size_of_result) << 1);
  { void * *tmp = &p->reserved1; (void)tmp; }
  { void * *tmp = &p->reserved2; (void)tmp; }
}
static PyObject *
_cffi_layout_struct__cffi_externpy_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_externpy_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_externpy_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_externpy_s, name),
    sizeof(((struct _cffi_externpy_s *)0)->name),
    offsetof(struct _cffi_externpy_s, size_of_result),
    sizeof(((struct _cffi_externpy_s *)0)->size_of_result),
    offsetof(struct _cffi_externpy_s, reserved1),
    sizeof(((struct _cffi_externpy_s *)0)->reserved1),
    offsetof(struct _cffi_externpy_s, reserved2),
    sizeof(((struct _cffi_externpy_s *)0)->reserved2),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_externpy_s(0);
}

static void _cffi_check_struct__cffi_field_s(struct _cffi_field_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  (void)((p->field_offset) << 1);
  (void)((p->field_size) << 1);
  { void * *tmp = &p->field_type_op; (void)tmp; }
}
static PyObject *
_cffi_layout_struct__cffi_field_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_field_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_field_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_field_s, name),
    sizeof(((struct _cffi_field_s *)0)->name),
    offsetof(struct _cffi_field_s, field_offset),
    sizeof(((struct _cffi_field_s *)0)->field_offset),
    offsetof(struct _cffi_field_s, field_size),
    sizeof(((struct _cffi_field_s *)0)->field_size),
    offsetof(struct _cffi_field_s, field_type_op),
    sizeof(((struct _cffi_field_s *)0)->field_type_op),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_field_s(0);
}

static void _cffi_check_struct__cffi_getconst_s(struct _cffi_getconst_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  (void)((p->value) << 1);
  { struct _cffi_type_context_s const * *tmp = &p->ctx; (void)tmp; }
  (void)((p->gindex) << 1);
}
static PyObject *
_cffi_layout_struct__cffi_getconst_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_getconst_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_getconst_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_getconst_s, value),
    sizeof(((struct _cffi_getconst_s *)0)->value),
    offsetof(struct _cffi_getconst_s, ctx),
    sizeof(((struct _cffi_getconst_s *)0)->ctx),
    offsetof(struct _cffi_getconst_s, gindex),
    sizeof(((struct _cffi_getconst_s *)0)->gindex),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_getconst_s(0);
}

static void _cffi_check_struct__cffi_global_s(struct _cffi_global_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  { void * *tmp = &p->address; (void)tmp; }
  { void * *tmp = &p->type_op; (void)tmp; }
  { void * *tmp = &p->size_or_direct_fn; (void)tmp; }
}
static PyObject *
_cffi_layout_struct__cffi_global_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_global_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_global_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_global_s, name),
    sizeof(((struct _cffi_global_s *)0)->name),
    offsetof(struct _cffi_global_s, address),
    sizeof(((struct _cffi_global_s *)0)->address),
    offsetof(struct _cffi_global_s, type_op),
    sizeof(((struct _cffi_global_s *)0)->type_op),
    offsetof(struct _cffi_global_s, size_or_direct_fn),
    sizeof(((struct _cffi_global_s *)0)->size_or_direct_fn),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_global_s(0);
}

static void _cffi_check_struct__cffi_parse_info_s(struct _cffi_parse_info_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { struct _cffi_type_context_s const * *tmp = &p->ctx; (void)tmp; }
  { void * * *tmp = &p->output; (void)tmp; }
  (void)((p->output_size) << 1);
  (void)((p->error_location) << 1);
  { char const * *tmp = &p->error_message; (void)tmp; }
}
static PyObject *
_cffi_layout_struct__cffi_parse_info_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_parse_info_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_parse_info_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_parse_info_s, ctx),
    sizeof(((struct _cffi_parse_info_s *)0)->ctx),
    offsetof(struct _cffi_parse_info_s, output),
    sizeof(((struct _cffi_parse_info_s *)0)->output),
    offsetof(struct _cffi_parse_info_s, output_size),
    sizeof(((struct _cffi_parse_info_s *)0)->output_size),
    offsetof(struct _cffi_parse_info_s, error_location),
    sizeof(((struct _cffi_parse_info_s *)0)->error_location),
    offsetof(struct _cffi_parse_info_s, error_message),
    sizeof(((struct _cffi_parse_info_s *)0)->error_message),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_parse_info_s(0);
}

static void _cffi_check_struct__cffi_struct_union_s(struct _cffi_struct_union_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  (void)((p->type_index) << 1);
  (void)((p->flags) << 1);
  (void)((p->size) << 1);
  (void)((p->alignment) << 1);
  (void)((p->first_field_index) << 1);
  (void)((p->num_fields) << 1);
}
static PyObject *
_cffi_layout_struct__cffi_struct_union_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_struct_union_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_struct_union_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_struct_union_s, name),
    sizeof(((struct _cffi_struct_union_s *)0)->name),
    offsetof(struct _cffi_struct_union_s, type_index),
    sizeof(((struct _cffi_struct_union_s *)0)->type_index),
    offsetof(struct _cffi_struct_union_s, flags),
    sizeof(((struct _cffi_struct_union_s *)0)->flags),
    offsetof(struct _cffi_struct_union_s, size),
    sizeof(((struct _cffi_struct_union_s *)0)->size),
    offsetof(struct _cffi_struct_union_s, alignment),
    sizeof(((struct _cffi_struct_union_s *)0)->alignment),
    offsetof(struct _cffi_struct_union_s, first_field_index),
    sizeof(((struct _cffi_struct_union_s *)0)->first_field_index),
    offsetof(struct _cffi_struct_union_s, num_fields),
    sizeof(((struct _cffi_struct_union_s *)0)->num_fields),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_struct_union_s(0);
}

static void _cffi_check_struct__cffi_type_context_s(struct _cffi_type_context_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { void * * *tmp = &p->types; (void)tmp; }
  { struct _cffi_global_s const * *tmp = &p->globals; (void)tmp; }
  { struct _cffi_field_s const * *tmp = &p->fields; (void)tmp; }
  { struct _cffi_struct_union_s const * *tmp = &p->struct_unions; (void)tmp; }
  { struct _cffi_enum_s const * *tmp = &p->enums; (void)tmp; }
  { struct _cffi_typename_s const * *tmp = &p->typenames; (void)tmp; }
  (void)((p->num_globals) << 1);
  (void)((p->num_struct_unions) << 1);
  (void)((p->num_enums) << 1);
  (void)((p->num_typenames) << 1);
  { char const * const * *tmp = &p->includes; (void)tmp; }
  (void)((p->num_types) << 1);
  (void)((p->flags) << 1);
}
static PyObject *
_cffi_layout_struct__cffi_type_context_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_type_context_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_type_context_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_type_context_s, types),
    sizeof(((struct _cffi_type_context_s *)0)->types),
    offsetof(struct _cffi_type_context_s, globals),
    sizeof(((struct _cffi_type_context_s *)0)->globals),
    offsetof(struct _cffi_type_context_s, fields),
    sizeof(((struct _cffi_type_context_s *)0)->fields),
    offsetof(struct _cffi_type_context_s, struct_unions),
    sizeof(((struct _cffi_type_context_s *)0)->struct_unions),
    offsetof(struct _cffi_type_context_s, enums),
    sizeof(((struct _cffi_type_context_s *)0)->enums),
    offsetof(struct _cffi_type_context_s, typenames),
    sizeof(((struct _cffi_type_context_s *)0)->typenames),
    offsetof(struct _cffi_type_context_s, num_globals),
    sizeof(((struct _cffi_type_context_s *)0)->num_globals),
    offsetof(struct _cffi_type_context_s, num_struct_unions),
    sizeof(((struct _cffi_type_context_s *)0)->num_struct_unions),
    offsetof(struct _cffi_type_context_s, num_enums),
    sizeof(((struct _cffi_type_context_s *)0)->num_enums),
    offsetof(struct _cffi_type_context_s, num_typenames),
    sizeof(((struct _cffi_type_context_s *)0)->num_typenames),
    offsetof(struct _cffi_type_context_s, includes),
    sizeof(((struct _cffi_type_context_s *)0)->includes),
    offsetof(struct _cffi_type_context_s, num_types),
    sizeof(((struct _cffi_type_context_s *)0)->num_types),
    offsetof(struct _cffi_type_context_s, flags),
    sizeof(((struct _cffi_type_context_s *)0)->flags),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_type_context_s(0);
}

static void _cffi_check_struct__cffi_typename_s(struct _cffi_typename_s *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->name; (void)tmp; }
  (void)((p->type_index) << 1);
}
static PyObject *
_cffi_layout_struct__cffi_typename_s(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; struct _cffi_typename_s y; };
  static Py_ssize_t nums[] = {
    sizeof(struct _cffi_typename_s),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(struct _cffi_typename_s, name),
    sizeof(((struct _cffi_typename_s *)0)->name),
    offsetof(struct _cffi_typename_s, type_index),
    sizeof(((struct _cffi_typename_s *)0)->type_index),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check_struct__cffi_typename_s(0);
}

static int _cffi_setup_custom(PyObject *lib)
{
  return _cffi_const__CFFI__UNKNOWN_PRIM(lib);
}

static PyMethodDef _cffi_methods[] = {
  {"parse_c_type", _cffi_f_parse_c_type, METH_VARARGS, NULL},
  {"search_in_globals", _cffi_f_search_in_globals, METH_VARARGS, NULL},
  {"search_in_struct_unions", _cffi_f_search_in_struct_unions, METH_VARARGS, NULL},
  {"_cffi_layout_struct__cffi_enum_s", _cffi_layout_struct__cffi_enum_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_externpy_s", _cffi_layout_struct__cffi_externpy_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_field_s", _cffi_layout_struct__cffi_field_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_getconst_s", _cffi_layout_struct__cffi_getconst_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_global_s", _cffi_layout_struct__cffi_global_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_parse_info_s", _cffi_layout_struct__cffi_parse_info_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_struct_union_s", _cffi_layout_struct__cffi_struct_union_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_type_context_s", _cffi_layout_struct__cffi_type_context_s, METH_NOARGS, NULL},
  {"_cffi_layout_struct__cffi_typename_s", _cffi_layout_struct__cffi_typename_s, METH_NOARGS, NULL},
  {"_cffi_setup", _cffi_setup, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}    /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef _cffi_module_def = {
  PyModuleDef_HEAD_INIT,
  "_cffi__xafff6ea4x326b0e33",
  NULL,
  -1,
  _cffi_methods,
  NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit__cffi__xafff6ea4x326b0e33(void)
{
  PyObject *lib;
  lib = PyModule_Create(&_cffi_module_def);
  if (lib == NULL)
    return NULL;
  if (((void)lib,0) < 0 || _cffi_init() < 0) {
    Py_DECREF(lib);
    return NULL;
  }
  return lib;
}

#else

PyMODINIT_FUNC
init_cffi__xafff6ea4x326b0e33(void)
{
  PyObject *lib;
  lib = Py_InitModule("_cffi__xafff6ea4x326b0e33", _cffi_methods);
  if (lib == NULL)
    return;
  if (((void)lib,0) < 0 || _cffi_init() < 0)
    return;
  return;
}

#endif
