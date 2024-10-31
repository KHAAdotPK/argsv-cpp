/*
    lib/parser/parser.hh 
    Written by, Q@khaa.pk	   
 */

#include "../../../csv/parser.hh"

#ifndef		CC_TOKENIZER_ARGSV_CPP_PARSER_HH
#define		CC_TOKENIZER_ARGSV_CPP_PARSER_HH

#ifndef HELP_STR_START
#define HELP_STR_START    "("
#endif
#ifndef HELP_STR_END
#define HELP_STR_END      ")"
#endif

#define ALL               "ALL"

/* 
    Get ready for the code bloat or...
    Eventually the rest of the file below this comment should be built/made into a composite
 */

typedef struct arg
{
    cc_tokenizer::string_character_traits<char>::size_type i; // argv start index
    cc_tokenizer::string_character_traits<char>::size_type j; // argv end index  
    int argc; // as the name suggests, argument count for this one specific command alone
    struct arg* previous; // link to list
    struct arg* next; // link to list
    cc_tokenizer::string_character_traits<char>::int_type ln; // line number 
    cc_tokenizer::string_character_traits<char>::int_type tn; // token number    
} ARG;
typedef ARG* ARG_PTR;


/* 
   @p, is for an instance of parser
   @ith,  
 */   
#define GET_TOTAL_NUMBER_OF_TOKENS(p, ith) {\
                                        p.reset(TOKENS);\
                                        for (cc_tokenizer::string_character_traits<char>::size_type ii = p.get_total_number_of_tokens(); ii > 0; ii--)\
                                        {\
                                            if (cc_tokenizer::string_character_traits<char>::eq(p.get_token_by_number(ii)[0], cc_tokenizer::String<char>(HELP_STR_START)[0]))\
                                            {\
                                                ith = ii;\
                                                break;\
                                            }\
                                        }\
                                      }\

/* 
    a = argv
    n = argc
    p = parser
    r = ARG
 */
#define GET_FIRST_ARG_INDEX(a, n, p, r) {\
                                            int j=n;\
                                            ARG* ptr = &r;\
                                            *ptr = {1, 0, 0, NULL, NULL, 0, 0};\
                                            p.reset(LINES);\
                                            p.reset(TOKENS);\
                                            while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
                                            {\
                                                while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
                                                {\
                                                    for (int i = 1; i < argc; i++)\
                                                    {\
                                                       if (p.get_current_token().compare(a[i]) == 0)\
                                                       {\
                                                            if (j > i)\
                                                            {\
                                                                j = i;\
                                                            }\
                                                       }\
                                                    }\
                                                }\
                                            }\
                                            ptr->j = j;\
                                            if (ptr->j)\
                                            {\
                                                ptr->argc = ptr->j - ptr->i;\
                                            }\
}\

#define TRAVERSE_ARGV(a, n)  {\
                                 for (int i = 1; i < n; i++)\
                                 {\
                                     std::cout<<a[i]<<" ";\
                                 }\
                                 std::cout<<std::endl;\
                             }\

/* 
    a = argv
    n = argc
    p = parser
    b = token like "v" or "h"
    r = ARG
 */
#define FIND_ARG(a, n, p, b, r)   {\
                                      cc_tokenizer::allocator<char> alloc_obj;\
                                      bool found = false;\
                                      ARG* ptr = &r;\
                                      /* previous, next */\
                                      *ptr = {0, 0, 0, NULL, NULL, 0, 0};\
                                      p.reset(LINES);\
                                      p.reset(TOKENS);\
                                      while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
                                      {\
                                          p.reset(TOKENS);\
                                          /*std::cout<<p.get_current_line_number()<<" -> "<<p.get_current_line().c_str()<<std::endl;*/\
                                          while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof() && p.get_current_token().find(HELP_STR_START, 0) == cc_tokenizer::String<char>::npos)\
                                          {\
                                              if (p.get_current_token().compare(b) == 0)\
                                              {\
                                                  ptr->ln = p.get_current_line_number();\
                                                  /*ptr->tn = p.get_current_token_number();*/\
                                                  found = true;\
                                                  break;\
                                              }\
                                              else\
                                              {\
                                              }\
                                          }\
                                          if (found == true)\
                                          {\
                                              break;\
                                          }\
                                      }\
                                      if (found == false)\
                                      {\
                                      }\
                                      else\
                                      {\
                                          /*found = false;*/\
                                          /*p.reset(TOKENS);*/\
                                          for (cc_tokenizer::string_character_traits<char>::size_type i = 1; i < n; i++)\
                                          {\
                                               p.reset(TOKENS);\
                                               while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof() && p.get_current_token().find(HELP_STR_START, 0) == cc_tokenizer::String<char>::npos)\
                                               {\
                                                   if (p.get_current_token().compare(a[i]) == 0)\
                                                   {\
                                                       /*std::cout<<a[i]<<" ---> "<<p.get_current_token().c_str()<<std::endl;*/\
                                                       if (found == false)\
                                                       {\
                                                           ptr->next = (ARG*)alloc_obj.allocate(sizeof(ARG));\
                                                           *(ptr->next) = {i, 0, 0, ptr, NULL, p.get_current_line_number(), p.get_current_token_number()};\
                                                           ptr = ptr->next;\
                                                       }\
                                                       else if (found == true)\
                                                       {\
                                                           found = false;\
                                                           ptr->i = i;\
                                                           /*ptr->ln = p.get_current_line_number();*/\
                                                           ptr->tn = p.get_current_token_number();\
                                                           ptr->next = NULL;\
                                                           /*ptr->next = (ARG*)alloc_obj.allocate(sizeof(ARG));*/\
                                                           /**(ptr->next) = {0, 0, 0, ptr, NULL, ptr->ln, 0};*/\
                                                           /*ptr = ptr->next;*/\
                                                       }\
                                                   }\
                                               }\
                                          }\
                                      }\
                                  }\

/* 
    a = argv
    n = argc
    p = parser
    r = ARG
 */
#define FIND_ARG_BLOCK(a, n, p, r)  {\
                                        ARG* ptr = &r;\
                                        while (ptr != NULL && ptr->i)\
                                        {\
                                            p.reset(LINES);\
                                            p.reset(TOKENS);\
                                            while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
                                            {\
                                                while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
                                                {\
                                                    for (int i = ptr->i + 1; i < n; i++)\
                                                    {\
                                                        if (p.get_current_token().compare(a[i]) == 0)\
                                                        {\
                                                            if (!ptr->j)\
                                                            {\
                                                                ptr->j = i - 1;\
                                                                ptr->argc = ptr->j - ptr->i;\
                                                            }\
                                                            else if (i < ptr->j)\
                                                            {\
                                                                ptr->j = i;\
                                                                ptr->argc = ptr->j - ptr->i - 1;\
                                                            }\
                                                        }\
                                                    }\
                                                }\
                                            }\
                                            if (!ptr->j)\
                                            {\
                                                ptr->j = n - 1;\
                                                ptr->argc = ptr->j - ptr->i;\
                                            }\
                                            ptr = ptr->next;\
                                        }\
                                    }\

/* 
   p is for an instance of parser
   r is where the found values will be returned or stored... it has to be an instance of type ARG 
   t is for token, which can be any thing it can be all in any caps as well
 */
#define HELP(p, r, t)     {\
                                ARG* ptr = &r;\
                                *ptr = {0, 0, 0, NULL, NULL, 0, 0};\
                                cc_tokenizer::String<char> str = cc_tokenizer::String<char>(t);\
                                cc_tokenizer::allocator<char> alloc_obj;\
                                str.toUpper();\
                                p.reset(LINES);\
                                p.reset(TOKENS);\
                                if (str.compare(ALL) == 0)\
                                {\
                                    while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
                                    {\
                                        cc_tokenizer::string_character_traits<char>::int_type ith = 0;\
                                        GET_TOTAL_NUMBER_OF_TOKENS(argsv_parser, ith);\
                                        /*for (cc_tokenizer::string_character_traits<char>::int_type i = 1; i < ith; i++)*/\
                                        {\
                                            if (ptr->ln && ptr->tn)\
                                            {\
                                                ptr->next = (ARG*)alloc_obj.allocate(sizeof(ARG));\
                                                *(ptr->next) = {0, 0, 0, ptr, NULL, 0, 0};\
                                                ptr = ptr->next;\
                                            }\
                                            ptr->i = cc_tokenizer::String<char>(HELP_STR_START).size();\
                                            ptr->j = p.get_current_line().find(HELP_STR_START);\
                                            ptr->argc = p.get_current_line().find(HELP_STR_END) - ptr->j;\
                                            ptr->ln = p.get_current_line_number();\
                                            ptr->tn = ith;\
                                        }\
                                        /*while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
                                        {\
                                            if (p.get_current_token().find(HELP_STR_START) == 0)\
                                            {\
                                                cc_tokenizer::string_character_traits<char>::size_type pos = p.get_current_token().find(HELP_STR_END);\
                                                if (pos != cc_tokenizer::String<char>::npos && pos == (p.get_current_token().size() - cc_tokenizer::String<char>(HELP_STR_END).size()))\
                                                {\
                                                    if (ptr->ln && ptr->tn)\
                                                    {\
                                                        ptr->next = (ARG*)alloc_obj.allocate(sizeof(ARG));\
                                                        *(ptr->next) = {0, 0, 0, ptr, NULL, 0, 0};\
                                                        ptr = ptr->next;\
                                                    }\
                                                    ptr->i = cc_tokenizer::String<char>(HELP_STR_START).size();\
                                                    ptr->j = pos;\
                                                    ptr->argc = ptr->j - ptr->i;\
                                                    ptr->ln = p.get_current_line_number();\
                                                    ptr->tn = p.get_current_token_number();\
                                                }\
                                            }\
                                        }*/\
                                    }\
                                }\
                                else\
                                {\
                                    /* code */\
                                    for (cc_tokenizer::string_character_traits<char>::int_type i = 1; i <= p.get_total_number_of_lines(); i++)\
                                    {\
                                        /*std::cout<< "-->>>>> " << p.get_total_number_of_lines() << std::endl;*/\
                                        /*std::cout<< p.get_line_by_number(i).c_str() << std::endl;*/\
                                        cc_tokenizer::string_character_traits<char>::int_type ith = 0;\
                                        p.get_line_by_number(i);\
                                        GET_TOTAL_NUMBER_OF_TOKENS(p, ith);\
                                        for (cc_tokenizer::string_character_traits<char>::int_type j = 1; j <= p.get_total_number_of_tokens(); j++)\
                                        {\
                                            cc_tokenizer::string_character_traits<char>::size_type pos = p.get_token_by_number(j).find(HELP_STR_START);\
                                            if (pos == cc_tokenizer::String<char>::npos)\
                                            {\
                                                if (p.get_token_by_number(j).compare(t) == 0)\
                                                {\
                                                    /*cc_tokenizer::string_character_traits<char>::int_type ith = 0;*/\
                                                    /*GET_TOTAL_NUMBER_OF_TOKENS(p, ith);*/\
                                                    /* ln =, tn =  p.get_total_number_of_tokens() */\
                                                    *ptr = {0, 0, 0, NULL, NULL, i, /*p.get_total_number_of_tokens()*/ ith};\
                                                    break;\
                                                }\
                                            }\
                                            else\
                                            {\
                                                j = p.get_total_number_of_tokens() + 1;\
                                            }\
                                        }\
                                        if (ptr->ln && ptr->tn /* provided token was valid command line option */)\
                                        {\
                                            cc_tokenizer::string_character_traits<char>::size_type pos = p.get_current_line().find(HELP_STR_START);\
                                            if (pos != cc_tokenizer::String<char>::npos)\
                                            {\
                                                /*ptr->i = pos + 1;*/\
                                                ptr->i = cc_tokenizer::String<char>(HELP_STR_START).size();\
                                                ptr->j = pos;\
                                                pos = p.get_current_line().find(HELP_STR_END);\
                                                if (pos != cc_tokenizer::String<char>::npos)\
                                                {\
                                                    /*ptr->j = pos ;*/\
                                                    /*ptr->argc = ptr->j - ptr->i;*/\
                                                    ptr->argc = pos - ptr->j;\
                                                }\
                                            }\
                                            break;\
                                        }\
                                    }\
                                }\
                          }\

/*
typedef struct arg
{
    cc_tokenizer::string_character_traits<char>::size_type i; // argv start index
    cc_tokenizer::string_character_traits<char>::size_type j; // argv end index  
    int argc; // as the name suggests, argument count for this one specific command alone
    struct arg* previous; // link to list
    struct arg* next; // link to list
    cc_tokenizer::string_character_traits<char>::int_type ln; // line number 
    cc_tokenizer::string_character_traits<char>::int_type tn; // token number    
} ARG;
typedef ARG* ARG_PTR;
 */


/*
    p is for an instance of parser
    r is where the found values will be returned or stored...it has to be an instance of type ARG
 */ 

#define HELP_DUMP(p, r) {\
                            p.reset(LINES);\
                            p.reset(TOKENS);\
                            ARG* current_arg_help = &r;\
                            /*if (r.i != 0 && r.j != 0 && r.argc != 0 && r.previous != NULL && r.next != NULL && r.ln != 0 && r.tn != 0)*/\
                            {\
                            std::cout<<"List of command line options..."<<std::endl;\
                            do\
                            {\
                                for (cc_tokenizer::string_character_traits<char>::size_type i = (current_arg_help->i + current_arg_help->j); i < (current_arg_help->j + current_arg_help->argc); i++)\
                                {\
                                    std::cout<<*(p.get_line_by_number(current_arg_help->ln).c_str() + i);\
                                }\
                                /*p.get_line_by_number(current_arg_help->ln);*/\
                                /*for (cc_tokenizer::string_character_traits<char>::size_type i = 0; i < current_arg_help->argc; i++)*/\
                                /*{*/\
                                    /*std::cout<<p.get_token_by_number(current_arg_help->tn)[current_arg_help->i + i];*/\
                                /*}*/\
                                std::cout<<" [ ";\
                                for (cc_tokenizer::string_character_traits<char>::size_type i = 1; i < current_arg_help->tn; i++)\
                                {\
                                    std::cout<<p.get_token_by_number(i).c_str()<<" ";\
                                }\
                                std::cout<<"]"<<std::endl;\
                                \
                                current_arg_help = current_arg_help->next;\
                            }\
                            while (current_arg_help != NULL);\
                            }\
                        }\
                        

/* 
    Bubble sort
    r = ARG
    r is where the found values will be returned or stored...it has to be an instance of type ARG
 */
#define SORT_ARG(r) {\
                        ARG* ptr_outer = &r;\
                        while (ptr_outer->next != NULL)\
                        {\
                            ARG* ptr_inner = &r;\
                            while (ptr_inner->next != NULL)\
                            {\
                                if (ptr_inner->i > (ptr_inner->next)->i)\
                                {\
                                    ARG foo;\
                                    foo.i = (ptr_inner->next)->i;\
                                    foo.j = (ptr_inner->next)->j;\
                                    foo.argc = (ptr_inner->next)->argc;\
                                    foo.ln = (ptr_inner->next)->ln;\
                                    foo.tn = (ptr_inner->next)->tn;\
                                    \
                                    \
                                    (ptr_inner->next)->i = ptr_inner->i;\
                                    (ptr_inner->next)->j = ptr_inner->j;\
                                    (ptr_inner->next)->argc = ptr_inner->argc;\
                                    (ptr_inner->next)->ln = ptr_inner->ln;\
                                    (ptr_inner->next)->tn = ptr_inner->tn;\
                                    \
                                    \
                                    ptr_inner->i = foo.i;\
                                    ptr_inner->j = foo.j;\
                                    ptr_inner->argc = foo.argc;\
                                    ptr_inner->ln = foo.ln;\
                                    ptr_inner->tn = foo.tn;\
                                }\
                                ptr_inner = ptr_inner->next;\
                            }\
                            ptr_outer = ptr_outer->next;\
                        }\
                    }\

#endif