**argsv-cpp**    
_README, last updated on :- 14th of November, 2024_

argsv for C++. An effort to process the command line arguments with ease and style.
---

"Command-line options represent the \"face\" of the program, and tools for options parsing should be convenient and easy to use.". C/C++ Users Journal November, 2004.

This argsv-cpp is capable of handling short and long commands. It is capable of handling multiple instances of same short or long command. argsv-cpp allows many command names for the same command e.g "?,/?,h,-h,help,--help"(This comma delimited list represents few names of the one single command). argsv-cpp can also process/parse the help text of each command line option. 

The repository contains an example application. Please use it to understand how to use and work with argsv-cpp to process command line arguments.  

## Dependencies...

- [github.com/KHAAdotPK/parser.git](https://github.com/KHAAdotPK/parser.git)
- [github.com/KHAAdotPK/String.git](https://github.com/KHAAdotPK/String.git)
- [github.com/KHAAdotPK/csv.git](https://github.com/KHAAdotPK/csv.git)
- [github.com/KHAAdotPK/ala_exception.git](https://github.com/KHAAdotPK/ala_exception.git)

## Usage

### Example 1

```C++
#include <iostream>
#include "./../lib/argsv-cpp/lib/parser/parser.hh"

#define COMMAND "h -h help --help ? /? (Displays the help screen)\n\
v -v version --version /v (Displays the version number)\n\
average --average (Acts as a flag to be used with the [w1 | --w1] command-line option; when used, the specified file is an average of w1 and w2 trained weights)\n"

#define SUB_COMMAND_average "do (Used with the \"average\" command; optionally expects a numeric argument. This command implies that the \"W1\" and \"W2\" matrices will be averaged, and the program will proceed with processing the resulting matrix. If an optional numeric argument is provided, it acts as a multiplier, with the \"W2\" matrix as the multiplicand before averaging)\n"

ARG arg_common, arg_words, arg_w1, arg_w2, arg_help, arg_vocab, arg_average;
cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> argsv_parser(cc_tokenizer::String<char>(COMMAND));
cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> argsv_parser_average(cc_tokenizer::String<char>(SUB_COMMAND_average));

/* 
    Processes all arguments that are common to all commands listed in the \"COMMAND\" string.
    Starts at index 1, and end at an index corresponding to the first command-line argument in the \"COMMAND\" string.
 */
GET_FIRST_ARG_INDEX(argv, argc, argsv_parser,  arg_common);            s
if (arg_common.argc)
{  
    /*                       
        argv[1:arg_common.argc] 
    */
}

/*
    In argv array, index 0 is an anchor index for COMMAND string, when you process the COMMAND string using argsv-c++.
    By default at index 0 in argv array of main() function, the pointer to program name gets stored.     
 */
FIND_ARG(argv, argc, argsv_parser, "average", arg_average);
FIND_ARG_BLOCK(argv, argc, argsv_parser, arg_average);
if (arg_average.argc)
{
    /*
        When a command-line option includes sub-commands, as in this case where \"average\" has a sub-command,
        the keyword \"average |--average\" serves as an anchor, similar to the program name in the argv array of the C main() function.
     */
    ARG arg_average_do; 
    
    FIND_ARG((argv + arg_average.i) /* Anchor index 0 for \"SUB_COMMAND_average\" strng */, arg_average.argc, argsv_parser_average, "do", arg_average_do); 
    FIND_ARG_BLOCK((argv + arg_average.i) /* Anchor index 0 for \"SUB_COMMAND_average\" strng */, (arg_average.argc + 1) /* Adjusted to replicate the behavior of argc in the main() function in C */, argsv_parser_average, arg_average_do); 
}
```

### Example 2

More evolved.

```C++
/*
    src/main.cpp
    Written by, Q@khaa.pk
 */

#include <iostream>
#include "./../lib/argsv-cpp/lib/parser/parser.hh"

#define COMMAND "h -h help --help ? /? (Displays help screen)\n\
                 v -v version --version /v (Displays version number)\n\
                 e epoch --epoch /e (Its a hyperparameter, sets epoch or number of times the training loop would run)\n\
                 corpus --corpus (Path to the file which has the training data)\n\
                 dmodel --dmodel (Its a hperparameter, the dimension of the model)\n\
                 verbose --verbose (Display of output, verbosly)\n\
                 lr --lr (Its a hperparameter, sets learning rate)\n\
                 sfc --sfc (Scaling factor constant)\n\
                 bs batchsize --batchsize (Its a hyperparameter, sets batch size)\n\
                 bs_line (Set batch size hyperparameter to line)\n\
                 bs_paragraph bs_para (Sets batch size hyperparameter to paragraph)"                 

#define COMMAND_CORPUS "i I -i -I input --input (Path to file which contains input sequences)\n\
                        t T -t -T target --target (Path to file which contains target sequences)"

int main(int argc, char *argv[])
{
    ARG arg_corpus, arg_epoch, arg_help;

    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> argsv_parser(cc_tokenizer::String<char>(COMMAND));

    if (argc < 2)
    {        
        HELP(argsv_parser, arg_help, "help");                
        HELP_DUMP(argsv_parser, arg_help); 

        return 0;                    
    }

    FIND_ARG(argv, argc, argsv_parser, "?", arg_help);
    if (arg_help.i)
    {
        HELP(argsv_parser, arg_help, ALL);
        HELP_DUMP(argsv_parser, arg_help);

        return 0;
    }

    FIND_ARG(argv, argc, argsv_parser, "epoch", arg_epoch);
    FIND_ARG_BLOCK(argv, argc, argsv_parser, arg_epoch); 
    if (arg_epoch.i && !arg_epoch.argc)
    {
        HELP(argsv_parser, arg_epoch, "/e");                
        HELP_DUMP(argsv_parser, arg_epoch); 

        return 0;
    } 

    FIND_ARG(argv, argc, argsv_parser, "--corpus", arg_corpus);
    FIND_ARG_BLOCK(argv, argc, argsv_parser, arg_corpus);
    if (arg_corpus.i && !arg_corpus.argc)
    {
        HELP(argsv_parser, arg_corpus, "--corpus");                
        HELP_DUMP(argsv_parser, arg_corpus); 

        return 0;
    }
    else
    {
        ARG arg_input, arg_target;

        cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> argsv_parser(cc_tokenizer::String<char>(COMMAND_CORPUS));

        FIND_ARG((argv + arg_corpus.i), (arg_corpus.argc + 1), argsv_parser, "input", arg_input);
        FIND_ARG_BLOCK((argv + arg_corpus.i), arg_corpus.argc + 1, argsv_parser, arg_input);
        FIND_ARG((argv + arg_corpus.i) , (arg_corpus.argc + 1), argsv_parser, "target", arg_target);
        FIND_ARG_BLOCK((argv + arg_corpus.i), (arg_corpus.argc + 1), argsv_parser, arg_target);

        if (arg_input.argc)
        {
            std::cout<< argv[arg_corpus.i + arg_input.i + 1] << std::endl;
        }
        else if (arg_input.i) 
        {
            HELP(argsv_parser, arg_input, "input");                
            HELP_DUMP(argsv_parser, arg_input); 

            return 0;
        }

        if (arg_target.argc)
        {
            std::cout<< argv[arg_corpus.i + arg_target.i + 1] << std::endl;
        }
        else if (arg_target.i)
        {
            HELP(argsv_parser, arg_target, "target");                
            HELP_DUMP(argsv_parser, arg_target); 

            return 0;
        }
    } 

    return 0;
}  
```

### License
This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.' Please refer to this file for comprehensive information.



