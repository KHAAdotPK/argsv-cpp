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