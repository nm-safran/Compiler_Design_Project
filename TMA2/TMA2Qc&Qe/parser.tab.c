/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
    char* type;
    char* lexeme;
    int line;
    int column;
};

FILE* derivation_file;
int production_num = 1;

void write_production(const char* production) {
    fprintf(derivation_file, "%d. %s\n", production_num++, production);
    printf("%s\n", production);  // Also print to console
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

extern int yylex();
extern FILE* yyin;

#line 99 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTLIT = 4,                     /* INTLIT  */
  YYSYMBOL_FLOATLIT = 5,                   /* FLOATLIT  */
  YYSYMBOL_CLASS = 6,                      /* CLASS  */
  YYSYMBOL_ISA = 7,                        /* ISA  */
  YYSYMBOL_IMPLEMENT = 8,                  /* IMPLEMENT  */
  YYSYMBOL_FUNC = 9,                       /* FUNC  */
  YYSYMBOL_CONSTRUCTOR = 10,               /* CONSTRUCTOR  */
  YYSYMBOL_PUBLIC = 11,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 12,                   /* PRIVATE  */
  YYSYMBOL_ATTRIBUTE = 13,                 /* ATTRIBUTE  */
  YYSYMBOL_LOCAL = 14,                     /* LOCAL  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_THEN = 16,                      /* THEN  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_READ = 19,                      /* READ  */
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_INTEGER_TYPE = 22,              /* INTEGER_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 23,                /* FLOAT_TYPE  */
  YYSYMBOL_VOID = 24,                      /* VOID  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_SELF = 28,                      /* SELF  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NE = 31,                        /* NE  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GE = 33,                        /* GE  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_PLUS = 36,                      /* PLUS  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_MULT = 38,                      /* MULT  */
  YYSYMBOL_DIV = 39,                       /* DIV  */
  YYSYMBOL_ARROW = 40,                     /* ARROW  */
  YYSYMBOL_LPAREN = 41,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 42,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 43,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 44,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 45,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 46,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_SEMI = 48,                      /* SEMI  */
  YYSYMBOL_DOT = 49,                       /* DOT  */
  YYSYMBOL_COLON = 50,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_prog = 52,                      /* prog  */
  YYSYMBOL_classOrImplOrFunc_list = 53,    /* classOrImplOrFunc_list  */
  YYSYMBOL_classOrImplOrFunc = 54,         /* classOrImplOrFunc  */
  YYSYMBOL_classDecl = 55,                 /* classDecl  */
  YYSYMBOL_isa_opt = 56,                   /* isa_opt  */
  YYSYMBOL_id_list_opt = 57,               /* id_list_opt  */
  YYSYMBOL_implDef = 58,                   /* implDef  */
  YYSYMBOL_func_list_opt = 59,             /* func_list_opt  */
  YYSYMBOL_funcDef = 60,                   /* funcDef  */
  YYSYMBOL_member_list_opt = 61,           /* member_list_opt  */
  YYSYMBOL_visibility = 62,                /* visibility  */
  YYSYMBOL_memberDecl = 63,                /* memberDecl  */
  YYSYMBOL_funcDecl = 64,                  /* funcDecl  */
  YYSYMBOL_funcHead = 65,                  /* funcHead  */
  YYSYMBOL_funcBody = 66,                  /* funcBody  */
  YYSYMBOL_stmt_list_opt = 67,             /* stmt_list_opt  */
  YYSYMBOL_varDeclOrStmt = 68,             /* varDeclOrStmt  */
  YYSYMBOL_attributeDecl = 69,             /* attributeDecl  */
  YYSYMBOL_localVarDecl = 70,              /* localVarDecl  */
  YYSYMBOL_varDecl = 71,                   /* varDecl  */
  YYSYMBOL_array_list_opt = 72,            /* array_list_opt  */
  YYSYMBOL_statement = 73,                 /* statement  */
  YYSYMBOL_assignStat = 74,                /* assignStat  */
  YYSYMBOL_statBlock = 75,                 /* statBlock  */
  YYSYMBOL_statement_list_opt = 76,        /* statement_list_opt  */
  YYSYMBOL_expr = 77,                      /* expr  */
  YYSYMBOL_rel_expr_opt = 78,              /* rel_expr_opt  */
  YYSYMBOL_arithExpr = 79,                 /* arithExpr  */
  YYSYMBOL_arith_expr_tail = 80,           /* arith_expr_tail  */
  YYSYMBOL_term = 81,                      /* term  */
  YYSYMBOL_term_tail = 82,                 /* term_tail  */
  YYSYMBOL_factor = 83,                    /* factor  */
  YYSYMBOL_primary_factor = 84,            /* primary_factor  */
  YYSYMBOL_simple_variable = 85,           /* simple_variable  */
  YYSYMBOL_simple_functionCall = 86,       /* simple_functionCall  */
  YYSYMBOL_qualified_id = 87,              /* qualified_id  */
  YYSYMBOL_variable = 88,                  /* variable  */
  YYSYMBOL_functionCall = 89,              /* functionCall  */
  YYSYMBOL_indices_opt = 90,               /* indices_opt  */
  YYSYMBOL_arraySize = 91,                 /* arraySize  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_returnType = 93,                /* returnType  */
  YYSYMBOL_fParams_opt = 94,               /* fParams_opt  */
  YYSYMBOL_fParams_tail_opt = 95,          /* fParams_tail_opt  */
  YYSYMBOL_aParams_opt = 96,               /* aParams_opt  */
  YYSYMBOL_aParams_tail_opt = 97,          /* aParams_tail_opt  */
  YYSYMBOL_relOp = 98,                     /* relOp  */
  YYSYMBOL_addOp = 99,                     /* addOp  */
  YYSYMBOL_multOp = 100,                   /* multOp  */
  YYSYMBOL_sign = 101                      /* sign  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    44,    44,    48,    50,    54,    56,    58,    62,    66,
      69,    72,    75,    78,    82,    85,    88,    92,    95,    98,
     100,   104,   106,   110,   114,   116,   120,   124,   127,   130,
     132,   136,   140,   144,   148,   151,   154,   156,   158,   160,
     162,   164,   166,   170,   174,   176,   179,   182,   185,   188,
     192,   195,   198,   202,   205,   208,   212,   215,   218,   220,
     222,   226,   228,   230,   232,   234,   238,   242,   246,   248,
     250,   252,   254,   258,   262,   266,   269,   272,   274,   278,
     280,   282,   286,   288,   292,   295,   298,   301,   304,   307,
     310,   313,   316,   317,   318,   319,   320,   321,   324,   325,
     326,   329,   330,   331,   334,   335
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTLIT",
  "FLOATLIT", "CLASS", "ISA", "IMPLEMENT", "FUNC", "CONSTRUCTOR", "PUBLIC",
  "PRIVATE", "ATTRIBUTE", "LOCAL", "IF", "THEN", "ELSE", "WHILE", "READ",
  "WRITE", "RETURN", "INTEGER_TYPE", "FLOAT_TYPE", "VOID", "NOT", "AND",
  "OR", "SELF", "ASSIGN", "EQ", "NE", "LE", "GE", "LT", "GT", "PLUS",
  "MINUS", "MULT", "DIV", "ARROW", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "COMMA", "SEMI", "DOT", "COLON", "$accept",
  "prog", "classOrImplOrFunc_list", "classOrImplOrFunc", "classDecl",
  "isa_opt", "id_list_opt", "implDef", "func_list_opt", "funcDef",
  "member_list_opt", "visibility", "memberDecl", "funcDecl", "funcHead",
  "funcBody", "stmt_list_opt", "varDeclOrStmt", "attributeDecl",
  "localVarDecl", "varDecl", "array_list_opt", "statement", "assignStat",
  "statBlock", "statement_list_opt", "expr", "rel_expr_opt", "arithExpr",
  "arith_expr_tail", "term", "term_tail", "factor", "primary_factor",
  "simple_variable", "simple_functionCall", "qualified_id", "variable",
  "functionCall", "indices_opt", "arraySize", "type", "returnType",
  "fParams_opt", "fParams_tail_opt", "aParams_opt", "aParams_tail_opt",
  "relOp", "addOp", "multOp", "sign", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-149)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      93,    17,    18,    25,     8,    71,  -149,    93,  -149,  -149,
    -149,    53,    84,    57,    70,   109,  -149,  -149,    55,  -149,
     110,    72,    97,   109,    66,    76,  -149,   111,    79,    82,
      83,    85,    86,  -149,    81,    55,  -149,  -149,    80,  -149,
    -149,    48,   100,    87,    89,    98,    88,    97,    91,    41,
    -149,    90,  -149,    20,    20,    31,    20,    20,  -149,  -149,
    -149,    20,    20,   127,  -149,    20,  -149,   128,  -149,  -149,
    -149,    94,    95,  -149,  -149,    99,  -149,  -149,  -149,    92,
      41,  -149,  -149,    20,  -149,  -149,    20,   101,    47,     6,
      46,  -149,  -149,  -149,    20,   102,    49,   105,   106,   112,
     108,   114,    96,  -149,  -149,    89,   104,   111,    98,  -149,
     113,  -149,    64,     9,   115,    92,    92,  -149,   116,   118,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,    20,  -149,  -149,
    -149,  -149,    20,  -149,  -149,  -149,  -149,    20,  -149,    11,
      20,   117,   122,   123,    20,  -149,   124,    -9,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,   107,  -149,   138,  -149,
    -149,   126,  -149,    11,  -149,     6,    46,    32,  -149,   130,
     121,  -149,  -149,  -149,   108,   154,    20,   156,  -149,  -149,
     125,  -149,   143,  -149,  -149,    32,   120,  -149,   124,  -149,
    -149,   133,  -149,    41,    11,  -149,  -149,   135,    92,   134,
     115,  -149,  -149
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     4,     5,     6,
       7,     0,    10,     0,     0,    85,     1,     3,    28,    16,
       0,     0,    15,    85,     0,     0,    68,     0,     0,     0,
       0,     0,     0,    69,     0,    28,    29,    30,     0,    73,
      74,    76,     0,     0,    12,    18,     0,    15,     0,     0,
      25,     0,    32,     0,     0,     0,     0,     0,    26,    27,
      36,    89,     0,     0,    66,     0,    42,     0,     9,    19,
      20,     0,     0,    13,    14,     0,    81,    79,    80,    35,
       0,    63,    64,     0,   104,   105,     0,     0,    51,    54,
      57,    58,    61,    62,     0,     0,    76,     0,     0,     0,
      91,     0,     0,    70,    43,    12,     0,     0,    18,    21,
       0,    22,     0,     0,    87,    35,    35,    59,     0,     0,
      92,    93,    96,    97,    94,    95,    49,     0,   100,    98,
      99,    52,     0,   103,   101,   102,    55,     0,    60,    46,
      89,     0,     0,     0,     0,    88,    67,    76,    11,     8,
      31,    17,    23,    83,    82,    24,     0,    78,     0,    84,
      34,     0,    65,    46,    50,    54,    57,    48,    45,     0,
       0,    39,    40,    41,    91,     0,     0,     0,    75,    77,
       0,    33,     0,    53,    56,    48,     0,    38,     0,    90,
      72,     0,    71,     0,    46,    47,    44,    76,    35,     0,
      87,    37,    86
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -149,  -149,   159,  -149,  -149,  -149,    67,  -149,   136,    19,
      73,  -149,  -149,  -149,   119,  -149,   149,  -149,  -149,  -149,
      78,  -106,   -16,  -149,  -148,     1,   -49,  -149,   -59,    22,
      56,    23,   -72,  -149,   -18,   -17,   137,   139,  -149,  -135,
    -149,   -74,  -149,   167,    -7,    58,    21,  -149,  -149,  -149,
    -149
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    21,    68,     9,    46,    10,
      71,    72,   108,   109,    11,    19,    34,    35,   111,    36,
      52,   114,   168,    38,   169,   186,   100,   126,    88,   131,
      89,   136,    90,    91,    92,    93,    41,    42,    43,    64,
     115,    79,   155,    25,   159,   101,   145,   127,   132,   137,
      94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    40,    37,   102,    87,    95,   116,    98,    99,   160,
     161,   117,   178,   156,    26,   182,   104,    39,    40,    37,
      12,    13,   138,    26,    81,    82,    28,   118,    14,    29,
      30,    31,    32,   128,    26,    26,   176,    39,   154,    33,
     177,    47,   129,   130,    76,    83,   199,    28,    33,    15,
      29,    30,    31,    32,   167,   157,    84,    85,    26,    33,
      33,    86,   178,    77,    78,   166,    47,    76,   164,    27,
      28,    16,   133,    29,    30,    31,    32,   120,   121,   122,
     123,   124,   125,    33,   134,   135,    77,    78,   153,    61,
     140,    20,   200,    62,    62,   174,    18,    63,    63,     1,
      22,     2,     3,     4,     3,     4,     3,     4,   107,    69,
      70,    23,    24,    44,    51,    45,    49,   191,    50,   198,
      53,    39,    40,    54,    55,    58,    56,    57,    60,    65,
     103,   105,    73,    75,   163,    66,    67,   113,   106,   112,
      80,   180,   147,   119,   139,    39,    40,   141,   142,    39,
      40,   185,   149,   179,   143,   144,   146,   190,   162,   192,
     194,   152,   158,   188,   196,   171,    17,    39,    40,   185,
     172,   173,   148,   175,   181,   193,    39,    40,   187,   197,
     176,   151,   201,    74,    59,   150,   195,   183,   165,   184,
      48,   110,    96,   202,    97,   189,     0,     0,   170
};

static const yytype_int16 yycheck[] =
{
      18,    18,    18,    62,    53,    54,    80,    56,    57,   115,
     116,    83,   147,     4,     3,   163,    65,    35,    35,    35,
       3,     3,    94,     3,     4,     5,    15,    86,     3,    18,
      19,    20,    21,    27,     3,     3,    45,    55,   112,    28,
      49,    22,    36,    37,     3,    25,   194,    15,    28,    41,
      18,    19,    20,    21,    43,    46,    36,    37,     3,    28,
      28,    41,   197,    22,    23,   137,    47,     3,   127,    14,
      15,     0,    26,    18,    19,    20,    21,    30,    31,    32,
      33,    34,    35,    28,    38,    39,    22,    23,    24,    41,
      41,     7,   198,    45,    45,   144,    43,    49,    49,     6,
      43,     8,     9,    10,     9,    10,     9,    10,    13,    11,
      12,    41,     3,     3,     3,    43,    50,   176,    42,   193,
      41,   139,   139,    41,    41,    44,    41,    41,    48,    29,
       3,     3,    44,    42,    16,    48,    47,    45,    44,    40,
      50,     3,    46,    42,    42,   163,   163,    42,    42,   167,
     167,   167,    48,    46,    42,    47,    42,     3,    42,     3,
      17,    48,    47,    42,    44,    48,     7,   185,   185,   185,
      48,    48,   105,    49,    48,    50,   194,   194,    48,    46,
      45,   108,    48,    47,    35,   107,   185,   165,   132,   166,
      23,    72,    55,   200,    55,   174,    -1,    -1,   140
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     8,     9,    10,    52,    53,    54,    55,    58,
      60,    65,     3,     3,     3,    41,     0,    53,    43,    66,
       7,    56,    43,    41,     3,    94,     3,    14,    15,    18,
      19,    20,    21,    28,    67,    68,    70,    73,    74,    85,
      86,    87,    88,    89,     3,    43,    59,    60,    94,    50,
      42,     3,    71,    41,    41,    41,    41,    41,    44,    67,
      48,    41,    45,    49,    90,    29,    48,    47,    57,    11,
      12,    61,    62,    44,    59,    42,     3,    22,    23,    92,
      50,     4,     5,    25,    36,    37,    41,    77,    79,    81,
      83,    84,    85,    86,   101,    77,    87,    88,    77,    77,
      77,    96,    79,     3,    77,     3,    44,    13,    63,    64,
      65,    69,    40,    45,    72,    91,    92,    83,    79,    42,
      30,    31,    32,    33,    34,    35,    78,    98,    27,    36,
      37,    80,    99,    26,    38,    39,    82,   100,    83,    42,
      41,    42,    42,    42,    47,    97,    42,    46,    57,    48,
      71,    61,    48,    24,    92,    93,     4,    46,    47,    95,
      72,    72,    42,    16,    79,    81,    83,    43,    73,    75,
      96,    48,    48,    48,    77,    49,    45,    49,    90,    46,
       3,    48,    75,    80,    82,    73,    76,    48,    42,    97,
       3,    79,     3,    50,    17,    76,    44,    46,    92,    75,
      72,    48,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    55,    56,
      56,    57,    57,    58,    59,    59,    60,    61,    61,    62,
      62,    63,    63,    64,    65,    65,    66,    67,    67,    68,
      68,    69,    70,    71,    72,    72,    73,    73,    73,    73,
      73,    73,    73,    74,    75,    75,    75,    76,    76,    77,
      78,    78,    79,    80,    80,    81,    82,    82,    83,    83,
      83,    84,    84,    84,    84,    84,    85,    86,    87,    87,
      87,    87,    87,    88,    89,    90,    90,    91,    91,    92,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   101,   101
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     7,     3,
       0,     3,     0,     5,     2,     0,     2,     3,     0,     1,
       1,     1,     1,     2,     7,     4,     3,     2,     0,     1,
       1,     2,     2,     5,     2,     0,     2,     9,     6,     5,
       5,     5,     2,     3,     3,     1,     0,     2,     0,     2,
       2,     0,     2,     3,     0,     2,     3,     0,     1,     2,
       2,     1,     1,     1,     1,     3,     2,     4,     1,     1,
       3,     6,     6,     1,     1,     4,     0,     3,     2,     1,
       1,     1,     1,     1,     5,     0,     6,     0,     2,     0,
       3,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: classOrImplOrFunc_list  */
#line 45 "parser.y"
    { write_production("prog -> classOrImplOrFunc_list"); }
#line 1332 "parser.tab.c"
    break;

  case 3: /* classOrImplOrFunc_list: classOrImplOrFunc classOrImplOrFunc_list  */
#line 49 "parser.y"
                      { write_production("classOrImplOrFunc_list -> classOrImplOrFunc classOrImplOrFunc_list"); }
#line 1338 "parser.tab.c"
    break;

  case 4: /* classOrImplOrFunc_list: classOrImplOrFunc  */
#line 51 "parser.y"
                      { write_production("classOrImplOrFunc_list -> classOrImplOrFunc"); }
#line 1344 "parser.tab.c"
    break;

  case 5: /* classOrImplOrFunc: classDecl  */
#line 55 "parser.y"
                 { write_production("classOrImplOrFunc -> classDecl"); }
#line 1350 "parser.tab.c"
    break;

  case 6: /* classOrImplOrFunc: implDef  */
#line 57 "parser.y"
                 { write_production("classOrImplOrFunc -> implDef"); }
#line 1356 "parser.tab.c"
    break;

  case 7: /* classOrImplOrFunc: funcDef  */
#line 59 "parser.y"
                 { write_production("classOrImplOrFunc -> funcDef"); }
#line 1362 "parser.tab.c"
    break;

  case 8: /* classDecl: CLASS ID isa_opt LBRACE member_list_opt RBRACE SEMI  */
#line 63 "parser.y"
         { write_production("classDecl -> class id isa_opt { member_list_opt } ;"); }
#line 1368 "parser.tab.c"
    break;

  case 9: /* isa_opt: ISA ID id_list_opt  */
#line 67 "parser.y"
       { write_production("isa_opt -> isa id id_list_opt"); }
#line 1374 "parser.tab.c"
    break;

  case 10: /* isa_opt: %empty  */
#line 69 "parser.y"
       { write_production("isa_opt -> ε"); }
#line 1380 "parser.tab.c"
    break;

  case 11: /* id_list_opt: COMMA ID id_list_opt  */
#line 73 "parser.y"
           { write_production("id_list_opt -> , id id_list_opt"); }
#line 1386 "parser.tab.c"
    break;

  case 12: /* id_list_opt: %empty  */
#line 75 "parser.y"
           { write_production("id_list_opt -> ε"); }
#line 1392 "parser.tab.c"
    break;

  case 13: /* implDef: IMPLEMENT ID LBRACE func_list_opt RBRACE  */
#line 79 "parser.y"
       { write_production("implDef -> implement id { func_list_opt }"); }
#line 1398 "parser.tab.c"
    break;

  case 14: /* func_list_opt: funcDef func_list_opt  */
#line 83 "parser.y"
             { write_production("func_list_opt -> funcDef func_list_opt"); }
#line 1404 "parser.tab.c"
    break;

  case 15: /* func_list_opt: %empty  */
#line 85 "parser.y"
             { write_production("func_list_opt -> ε"); }
#line 1410 "parser.tab.c"
    break;

  case 16: /* funcDef: funcHead funcBody  */
#line 89 "parser.y"
       { write_production("funcDef -> funcHead funcBody"); }
#line 1416 "parser.tab.c"
    break;

  case 17: /* member_list_opt: visibility memberDecl member_list_opt  */
#line 93 "parser.y"
               { write_production("member_list_opt -> visibility memberDecl member_list_opt"); }
#line 1422 "parser.tab.c"
    break;

  case 18: /* member_list_opt: %empty  */
#line 95 "parser.y"
               { write_production("member_list_opt -> ε"); }
#line 1428 "parser.tab.c"
    break;

  case 19: /* visibility: PUBLIC  */
#line 99 "parser.y"
          { write_production("visibility -> public"); }
#line 1434 "parser.tab.c"
    break;

  case 20: /* visibility: PRIVATE  */
#line 101 "parser.y"
          { write_production("visibility -> private"); }
#line 1440 "parser.tab.c"
    break;

  case 21: /* memberDecl: funcDecl  */
#line 105 "parser.y"
          { write_production("memberDecl -> funcDecl"); }
#line 1446 "parser.tab.c"
    break;

  case 22: /* memberDecl: attributeDecl  */
#line 107 "parser.y"
          { write_production("memberDecl -> attributeDecl"); }
#line 1452 "parser.tab.c"
    break;

  case 23: /* funcDecl: funcHead SEMI  */
#line 111 "parser.y"
        { write_production("funcDecl -> funcHead ;"); }
#line 1458 "parser.tab.c"
    break;

  case 24: /* funcHead: FUNC ID LPAREN fParams_opt RPAREN ARROW returnType  */
#line 115 "parser.y"
        { write_production("funcHead -> func id ( fParams_opt ) => returnType"); }
#line 1464 "parser.tab.c"
    break;

  case 25: /* funcHead: CONSTRUCTOR LPAREN fParams_opt RPAREN  */
#line 117 "parser.y"
        { write_production("funcHead -> constructor ( fParams_opt )"); }
#line 1470 "parser.tab.c"
    break;

  case 26: /* funcBody: LBRACE stmt_list_opt RBRACE  */
#line 121 "parser.y"
        { write_production("funcBody -> { stmt_list_opt }"); }
#line 1476 "parser.tab.c"
    break;

  case 27: /* stmt_list_opt: varDeclOrStmt stmt_list_opt  */
#line 125 "parser.y"
             { write_production("stmt_list_opt -> varDeclOrStmt stmt_list_opt"); }
#line 1482 "parser.tab.c"
    break;

  case 28: /* stmt_list_opt: %empty  */
#line 127 "parser.y"
             { write_production("stmt_list_opt -> ε"); }
#line 1488 "parser.tab.c"
    break;

  case 29: /* varDeclOrStmt: localVarDecl  */
#line 131 "parser.y"
             { write_production("varDeclOrStmt -> localVarDecl"); }
#line 1494 "parser.tab.c"
    break;

  case 30: /* varDeclOrStmt: statement  */
#line 133 "parser.y"
             { write_production("varDeclOrStmt -> statement"); }
#line 1500 "parser.tab.c"
    break;

  case 31: /* attributeDecl: ATTRIBUTE varDecl  */
#line 137 "parser.y"
             { write_production("attributeDecl -> attribute varDecl"); }
#line 1506 "parser.tab.c"
    break;

  case 32: /* localVarDecl: LOCAL varDecl  */
#line 141 "parser.y"
            { write_production("localVarDecl -> local varDecl"); }
#line 1512 "parser.tab.c"
    break;

  case 33: /* varDecl: ID COLON type array_list_opt SEMI  */
#line 145 "parser.y"
       { write_production("varDecl -> id : type array_list_opt ;"); }
#line 1518 "parser.tab.c"
    break;

  case 34: /* array_list_opt: arraySize array_list_opt  */
#line 149 "parser.y"
              { write_production("array_list_opt -> arraySize array_list_opt"); }
#line 1524 "parser.tab.c"
    break;

  case 35: /* array_list_opt: %empty  */
#line 151 "parser.y"
              { write_production("array_list_opt -> ε"); }
#line 1530 "parser.tab.c"
    break;

  case 36: /* statement: assignStat SEMI  */
#line 155 "parser.y"
         { write_production("statement -> assignStat ;"); }
#line 1536 "parser.tab.c"
    break;

  case 37: /* statement: IF LPAREN expr RPAREN THEN statBlock ELSE statBlock SEMI  */
#line 157 "parser.y"
         { write_production("statement -> if ( expr ) then statBlock else statBlock ;"); }
#line 1542 "parser.tab.c"
    break;

  case 38: /* statement: WHILE LPAREN expr RPAREN statBlock SEMI  */
#line 159 "parser.y"
         { write_production("statement -> while ( expr ) statBlock ;"); }
#line 1548 "parser.tab.c"
    break;

  case 39: /* statement: READ LPAREN variable RPAREN SEMI  */
#line 161 "parser.y"
         { write_production("statement -> read ( variable ) ;"); }
#line 1554 "parser.tab.c"
    break;

  case 40: /* statement: WRITE LPAREN expr RPAREN SEMI  */
#line 163 "parser.y"
         { write_production("statement -> write ( expr ) ;"); }
#line 1560 "parser.tab.c"
    break;

  case 41: /* statement: RETURN LPAREN expr RPAREN SEMI  */
#line 165 "parser.y"
         { write_production("statement -> return ( expr ) ;"); }
#line 1566 "parser.tab.c"
    break;

  case 42: /* statement: functionCall SEMI  */
#line 167 "parser.y"
         { write_production("statement -> functionCall ;"); }
#line 1572 "parser.tab.c"
    break;

  case 43: /* assignStat: variable ASSIGN expr  */
#line 171 "parser.y"
          { write_production("assignStat -> variable := expr"); }
#line 1578 "parser.tab.c"
    break;

  case 44: /* statBlock: LBRACE statement_list_opt RBRACE  */
#line 175 "parser.y"
         { write_production("statBlock -> { statement_list_opt }"); }
#line 1584 "parser.tab.c"
    break;

  case 45: /* statBlock: statement  */
#line 177 "parser.y"
         { write_production("statBlock -> statement"); }
#line 1590 "parser.tab.c"
    break;

  case 46: /* statBlock: %empty  */
#line 179 "parser.y"
         { write_production("statBlock -> ε"); }
#line 1596 "parser.tab.c"
    break;

  case 47: /* statement_list_opt: statement statement_list_opt  */
#line 183 "parser.y"
                  { write_production("statement_list_opt -> statement statement_list_opt"); }
#line 1602 "parser.tab.c"
    break;

  case 48: /* statement_list_opt: %empty  */
#line 185 "parser.y"
                  { write_production("statement_list_opt -> ε"); }
#line 1608 "parser.tab.c"
    break;

  case 49: /* expr: arithExpr rel_expr_opt  */
#line 189 "parser.y"
    { write_production("expr -> arithExpr rel_expr_opt"); }
#line 1614 "parser.tab.c"
    break;

  case 50: /* rel_expr_opt: relOp arithExpr  */
#line 193 "parser.y"
            { write_production("rel_expr_opt -> relOp arithExpr"); }
#line 1620 "parser.tab.c"
    break;

  case 51: /* rel_expr_opt: %empty  */
#line 195 "parser.y"
            { write_production("rel_expr_opt -> ε"); }
#line 1626 "parser.tab.c"
    break;

  case 52: /* arithExpr: term arith_expr_tail  */
#line 199 "parser.y"
         { write_production("arithExpr -> term arith_expr_tail"); }
#line 1632 "parser.tab.c"
    break;

  case 53: /* arith_expr_tail: addOp term arith_expr_tail  */
#line 203 "parser.y"
               { write_production("arith_expr_tail -> addOp term arith_expr_tail"); }
#line 1638 "parser.tab.c"
    break;

  case 54: /* arith_expr_tail: %empty  */
#line 205 "parser.y"
               { write_production("arith_expr_tail -> ε"); }
#line 1644 "parser.tab.c"
    break;

  case 55: /* term: factor term_tail  */
#line 209 "parser.y"
    { write_production("term -> factor term_tail"); }
#line 1650 "parser.tab.c"
    break;

  case 56: /* term_tail: multOp factor term_tail  */
#line 213 "parser.y"
         { write_production("term_tail -> multOp factor term_tail"); }
#line 1656 "parser.tab.c"
    break;

  case 57: /* term_tail: %empty  */
#line 215 "parser.y"
         { write_production("term_tail -> ε"); }
#line 1662 "parser.tab.c"
    break;

  case 58: /* factor: primary_factor  */
#line 219 "parser.y"
      { write_production("factor -> primary_factor"); }
#line 1668 "parser.tab.c"
    break;

  case 59: /* factor: NOT factor  */
#line 221 "parser.y"
      { write_production("factor -> not factor"); }
#line 1674 "parser.tab.c"
    break;

  case 60: /* factor: sign factor  */
#line 223 "parser.y"
      { write_production("factor -> sign factor"); }
#line 1680 "parser.tab.c"
    break;

  case 61: /* primary_factor: simple_variable  */
#line 227 "parser.y"
              { write_production("primary_factor -> simple_variable"); }
#line 1686 "parser.tab.c"
    break;

  case 62: /* primary_factor: simple_functionCall  */
#line 229 "parser.y"
              { write_production("primary_factor -> simple_functionCall"); }
#line 1692 "parser.tab.c"
    break;

  case 63: /* primary_factor: INTLIT  */
#line 231 "parser.y"
              { write_production("primary_factor -> intLit"); }
#line 1698 "parser.tab.c"
    break;

  case 64: /* primary_factor: FLOATLIT  */
#line 233 "parser.y"
              { write_production("primary_factor -> floatLit"); }
#line 1704 "parser.tab.c"
    break;

  case 65: /* primary_factor: LPAREN arithExpr RPAREN  */
#line 235 "parser.y"
              { write_production("primary_factor -> ( arithExpr )"); }
#line 1710 "parser.tab.c"
    break;

  case 66: /* simple_variable: qualified_id indices_opt  */
#line 239 "parser.y"
               { write_production("simple_variable -> qualified_id indices_opt"); }
#line 1716 "parser.tab.c"
    break;

  case 67: /* simple_functionCall: qualified_id LPAREN aParams_opt RPAREN  */
#line 243 "parser.y"
                   { write_production("simple_functionCall -> qualified_id ( aParams_opt )"); }
#line 1722 "parser.tab.c"
    break;

  case 68: /* qualified_id: ID  */
#line 247 "parser.y"
            { write_production("qualified_id -> id"); }
#line 1728 "parser.tab.c"
    break;

  case 69: /* qualified_id: SELF  */
#line 249 "parser.y"
            { write_production("qualified_id -> self"); }
#line 1734 "parser.tab.c"
    break;

  case 70: /* qualified_id: qualified_id DOT ID  */
#line 251 "parser.y"
            { write_production("qualified_id -> qualified_id . id"); }
#line 1740 "parser.tab.c"
    break;

  case 71: /* qualified_id: qualified_id LBRACKET arithExpr RBRACKET DOT ID  */
#line 253 "parser.y"
            { write_production("qualified_id -> qualified_id [ arithExpr ] . id"); }
#line 1746 "parser.tab.c"
    break;

  case 72: /* qualified_id: qualified_id LPAREN aParams_opt RPAREN DOT ID  */
#line 255 "parser.y"
            { write_production("qualified_id -> qualified_id ( aParams_opt ) . id"); }
#line 1752 "parser.tab.c"
    break;

  case 73: /* variable: simple_variable  */
#line 259 "parser.y"
        { write_production("variable -> simple_variable"); }
#line 1758 "parser.tab.c"
    break;

  case 74: /* functionCall: simple_functionCall  */
#line 263 "parser.y"
            { write_production("functionCall -> simple_functionCall"); }
#line 1764 "parser.tab.c"
    break;

  case 75: /* indices_opt: LBRACKET arithExpr RBRACKET indices_opt  */
#line 267 "parser.y"
           { write_production("indices_opt -> [ arithExpr ] indices_opt"); }
#line 1770 "parser.tab.c"
    break;

  case 76: /* indices_opt: %empty  */
#line 269 "parser.y"
           { write_production("indices_opt -> ε"); }
#line 1776 "parser.tab.c"
    break;

  case 77: /* arraySize: LBRACKET INTLIT RBRACKET  */
#line 273 "parser.y"
         { write_production("arraySize -> [ intLit ]"); }
#line 1782 "parser.tab.c"
    break;

  case 78: /* arraySize: LBRACKET RBRACKET  */
#line 275 "parser.y"
         { write_production("arraySize -> [ ]"); }
#line 1788 "parser.tab.c"
    break;

  case 79: /* type: INTEGER_TYPE  */
#line 279 "parser.y"
    { write_production("type -> integer"); }
#line 1794 "parser.tab.c"
    break;

  case 80: /* type: FLOAT_TYPE  */
#line 281 "parser.y"
    { write_production("type -> float"); }
#line 1800 "parser.tab.c"
    break;

  case 81: /* type: ID  */
#line 283 "parser.y"
    { write_production("type -> id"); }
#line 1806 "parser.tab.c"
    break;

  case 82: /* returnType: type  */
#line 287 "parser.y"
          { write_production("returnType -> type"); }
#line 1812 "parser.tab.c"
    break;

  case 83: /* returnType: VOID  */
#line 289 "parser.y"
          { write_production("returnType -> void"); }
#line 1818 "parser.tab.c"
    break;

  case 84: /* fParams_opt: ID COLON type array_list_opt fParams_tail_opt  */
#line 293 "parser.y"
           { write_production("fParams_opt -> id : type array_list_opt fParams_tail_opt"); }
#line 1824 "parser.tab.c"
    break;

  case 85: /* fParams_opt: %empty  */
#line 295 "parser.y"
           { write_production("fParams_opt -> ε"); }
#line 1830 "parser.tab.c"
    break;

  case 86: /* fParams_tail_opt: COMMA ID COLON type array_list_opt fParams_tail_opt  */
#line 299 "parser.y"
                { write_production("fParams_tail_opt -> , id : type array_list_opt fParams_tail_opt"); }
#line 1836 "parser.tab.c"
    break;

  case 87: /* fParams_tail_opt: %empty  */
#line 301 "parser.y"
                { write_production("fParams_tail_opt -> ε"); }
#line 1842 "parser.tab.c"
    break;

  case 88: /* aParams_opt: expr aParams_tail_opt  */
#line 305 "parser.y"
           { write_production("aParams_opt -> expr aParams_tail_opt"); }
#line 1848 "parser.tab.c"
    break;

  case 89: /* aParams_opt: %empty  */
#line 307 "parser.y"
           { write_production("aParams_opt -> ε"); }
#line 1854 "parser.tab.c"
    break;

  case 90: /* aParams_tail_opt: COMMA expr aParams_tail_opt  */
#line 311 "parser.y"
                { write_production("aParams_tail_opt -> , expr aParams_tail_opt"); }
#line 1860 "parser.tab.c"
    break;

  case 91: /* aParams_tail_opt: %empty  */
#line 313 "parser.y"
                { write_production("aParams_tail_opt -> ε"); }
#line 1866 "parser.tab.c"
    break;

  case 92: /* relOp: EQ  */
#line 316 "parser.y"
          { write_production("relOp -> =="); }
#line 1872 "parser.tab.c"
    break;

  case 93: /* relOp: NE  */
#line 317 "parser.y"
          { write_production("relOp -> <>"); }
#line 1878 "parser.tab.c"
    break;

  case 94: /* relOp: LT  */
#line 318 "parser.y"
          { write_production("relOp -> <"); }
#line 1884 "parser.tab.c"
    break;

  case 95: /* relOp: GT  */
#line 319 "parser.y"
          { write_production("relOp -> >"); }
#line 1890 "parser.tab.c"
    break;

  case 96: /* relOp: LE  */
#line 320 "parser.y"
          { write_production("relOp -> <="); }
#line 1896 "parser.tab.c"
    break;

  case 97: /* relOp: GE  */
#line 321 "parser.y"
          { write_production("relOp -> >="); }
#line 1902 "parser.tab.c"
    break;

  case 98: /* addOp: PLUS  */
#line 324 "parser.y"
            { write_production("addOp -> +"); }
#line 1908 "parser.tab.c"
    break;

  case 99: /* addOp: MINUS  */
#line 325 "parser.y"
             { write_production("addOp -> -"); }
#line 1914 "parser.tab.c"
    break;

  case 100: /* addOp: OR  */
#line 326 "parser.y"
          { write_production("addOp -> or"); }
#line 1920 "parser.tab.c"
    break;

  case 101: /* multOp: MULT  */
#line 329 "parser.y"
             { write_production("multOp -> *"); }
#line 1926 "parser.tab.c"
    break;

  case 102: /* multOp: DIV  */
#line 330 "parser.y"
            { write_production("multOp -> /"); }
#line 1932 "parser.tab.c"
    break;

  case 103: /* multOp: AND  */
#line 331 "parser.y"
            { write_production("multOp -> and"); }
#line 1938 "parser.tab.c"
    break;

  case 104: /* sign: PLUS  */
#line 334 "parser.y"
           { write_production("sign -> +"); }
#line 1944 "parser.tab.c"
    break;

  case 105: /* sign: MINUS  */
#line 335 "parser.y"
            { write_production("sign -> -"); }
#line 1950 "parser.tab.c"
    break;


#line 1954 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 338 "parser.y"


int main(int argc, char* argv[]) {
    // Open derivation file
    derivation_file = fopen("derivation.txt", "w");
    if (!derivation_file) {
        fprintf(stderr, "Error: Cannot create derivation.txt file\n");
        return 1;
    }

    // Handle input file if provided
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
            fclose(derivation_file);
            return 1;
        }
    }

    printf("Starting parse...\n");
    printf("Derivation steps:\n");
    printf("================\n");

    fprintf(derivation_file, "Derivation of the source program from start symbol 'prog':\n");
    fprintf(derivation_file, "=========================================================\n");

    int result = yyparse();

    if (result == 0) {
        printf("\n=== Parse completed successfully! ===\n");
        printf("Derivation has been written to 'derivation.txt'\n");
        fprintf(derivation_file, "\nParse completed successfully.\n");
    } else {
        printf("\n=== Parse failed with errors ===\n");
        fprintf(derivation_file, "\nParse failed with errors.\n");
    }

    fclose(derivation_file);
    if (yyin != stdin) fclose(yyin);

    return result;
}
