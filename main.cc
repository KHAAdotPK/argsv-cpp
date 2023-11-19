/*
    main.cc
    Written by, Q@khaa.pk
 */

#include <iostream>
/*
    To change the default parsing behaviour of the CSV parser
    //#define GRAMMAR_END_OF_TOKEN_MARKER     ","
    //#define GRAMMAR_END_OF_TOKEN_MARKER_SIZE    1
 */
#define COMMAND "d,-d,dir,--dir,(displays a list of files and subdirectories in a directory)\nh,-h,help,--help,?,/?,(displays help screen)\nv,-v,version,--version,(displays version number)"

#include "lib/parser/parser.hh"

int main(int argc, char* argv[])
{     
    ARG arg_d;
    ARG arg_v;
    ARG arg_h;
    ARG help_str;     
    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> parser(cc_tokenizer::String<char>(COMMAND));
    
    /*TRAVERSE_ARGV(argv, argc)*/

    FIND_ARG(argv, argc, parser, "dir", arg_d)
    /* TODO 
       Haven't yet tested, do not use */
    /*SORT_ARG(arg_d)*/ 
    if (arg_d.i)
    {
        /* TODO 
           Haven't yet tested, do not use */    
        /*SORT_ARG(arg_d)*/
        ARG* ptr = &arg_d;
        FIND_ARG_BLOCK(argv, argc, parser, arg_d)
        /* TODO 
           Haven't yet tested, do not use */
        /*SORT_ARG(arg_d)*/
        while (ptr->next != NULL)
        {
            if (ptr->argc == (ptr->j - ptr->i))
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<"(last command at CLI) [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            else 
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<" [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            /*
                Both of them would work as well
                //for (int i = ptr->i + 1; i < ptr->argc + ptr->i + 1; i++)
                //for (int i = ptr->i + 1; i < ptr->j; i++)
             */
            for (int i = 0; i < ptr->argc; i++)
            {
                /*
                    //std::cout<<argv[i]<<", ";
                 */
                std::cout<<argv[ptr->i + i + 1]<<", ";
            }
            std::cout<<"]"<<std::endl;
            ptr = ptr->next;            
        }
    }

    FIND_ARG(argv, argc, parser, "v", arg_v)    
    /* TODO 
       Haven't yet tested, do not use */
    /*SORT_ARG(arg)*/
    if (arg_v.i)
    {
        ARG* ptr = &arg_v;
        FIND_ARG_BLOCK(argv, argc, parser, arg_v)
        /* TODO 
        /* Haven't yet tested, do not use */
        /*SORT_ARG(arg_v)*/
        while (ptr->next != NULL)
        {            
            if (ptr->argc == (ptr->j - ptr->i))
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<"(last command at CLI) [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            else 
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<" [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            /*
                Both of them would work as well
                //for (int i = ptr->i + 1; i < ptr->argc + ptr->i + 1; i++)
                //for (int i = ptr->i + 1; i < ptr->j; i++)
             */   
            for (int i = 0; i < ptr->argc; i++)
            {
                /*       
                    //std::cout<<argv[i]<<", ";
                 */                    
                std::cout<<argv[ptr->i + i + 1]<<", ";
            }            
            std::cout<<"]"<<std::endl;
            ptr = ptr->next;
        }
    }

    FIND_ARG(argv, argc, parser, "?", arg_h)    
    /* TODO 
       Haven't yet tested, do not use */
    /*SORT_ARG(arg_h)*/
    if (arg_h.i)
    {
        ARG* ptr = &arg_h;
        FIND_ARG_BLOCK(argv, argc, parser, arg_h)
        /* TODO 
           Haven't yet tested, do not use */
        /*SORT_ARG(arg_h)*/
        while (ptr->next != NULL)
        {
            if (ptr->argc == (ptr->j - ptr->i))
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<"(last command at CLI) [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            else 
            {
                std::cout<<"* "<<argv[ptr->i]<<" --> "<<argv[ptr->j]<<" [ln = "<<ptr->ln<<", tn = "<<ptr->tn<<"]"<<", argc = "<<ptr->argc<<", j - i = "<<ptr->j - ptr->i<<", arguments[";
            }
            /*
                Both of them would work as well
                //for (int i = ptr->i + 1; i < ptr->argc + ptr->i + 1; i++)
                //for (int i = ptr->i + 1; i < ptr->j; i++)
             */
            for (int i = 0; i < ptr->argc; i++)
            {
                /*
                    //std::cout<<argv[i]<<", ";
                 */
                std::cout<<argv[ptr->i + i + 1]<<", ";
            }   
            std::cout<<"]"<<std::endl;
            ptr = ptr->next;
        }
    }

    HELP(parser, help_str, ALL)
    ARG* ptr = &help_str;
    while (1)
    {
        parser.reset(LINES);
        parser.reset(TOKENS);
        
        /* 
            The parser.get_cuttent_line_number() should return 0 instead it is returning the actual line number of the line returned by the parser.get_line_number(ptr->lin) 
            It is due to the obvious reason that parser.get_line_by_number() is getting called before the parser.get_current_line_number()

            std::cout<<"--> (Line# "<<parser.get_current_line_number()<<") --> "<<parser.get_line_by_number(ptr->ln).c_str()<<std::endl;

            Now, the above line is commented and replaced by the following line
         */
        std::cout<<"--> (Line# "<<ptr->ln<<") --> "<<parser.get_line_by_number(ptr->ln).c_str()<<std::endl;                      
        while (parser.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())
        {
            if (parser.get_current_token_number() != ptr->tn)
            {
                std::cout<<"   -> (token# "<<parser.get_current_token_number()<<") -> "<<parser.get_current_token().c_str()<<std::endl;
            }
            else
            {
                std::cout<<"   -> (help string) "<<parser.get_token_by_number(ptr->tn).substr(ptr->i, ptr->j - ptr->i).c_str()<<std::endl;     
            }            
        }

        if (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        else
        {
            break;
        }
    }

    HELP(parser, help_str, "h")
    if (help_str.ln)
    {
        std::cout<<std::endl<<"--> (Line# "<<help_str.ln<<") --> "<<parser.get_line_by_number(help_str.ln).c_str()<<std::endl;
        std::cout<<"   -> (Help string of token# "<<help_str.tn<<") -> "<<parser.get_line_by_number(help_str.ln).substr(help_str.i, help_str.argc).c_str()<<std::endl;
    }
                 
    return 0;
}