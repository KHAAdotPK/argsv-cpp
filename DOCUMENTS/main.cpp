/*
    Note: The delimiter used to separate the elements in the COMMAND macro can be customized.
    The first definition uses commas (,) as delimiters, while the second definition uses whitespace. 
    If you wish to change the delimiter or adjust its size, you can modify the corresponding settings in the file...
    lib/csv/parser.h or in your CMakeLists.txt.
    Alternatively, you can undefine and redefine the delimiter after including the lib/argsv-cpp/lib/parser/parser.hh 
    file according to your specific requirements.

    Please note that the macros mentioned below are by default or originally defined in the file lib/csv/parser.h
    #define GRAMMAR_END_OF_TOKEN_MARKER ","
    #define GRAMMAR_END_OF_TOKEN_MARKER_SIZE 1
    #define GRAMMAR_END_OF_LINE_MARKER "\n"
    #define GRAMMAR_END_OF_LINE_MARKER_SIZE 1

    The following two macros are defined in file  lib\argsv-cpp\lib\parser\parser.hh
    #define HELP_STR_START    "("
    #define HELP_STR_END      ")"
 */
/*
    To change the default parsing behaviour of the CSV parser
        
    Snippet from CMakeLists.txt file
    # Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro
    #add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER=" ")
    #add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)

    Snippet from CMakeLists.txt file
    # Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro for the replika target
    #target_compile_definitions(replika PRIVATE GRAMMAR_END_OF_TOKEN_MARKER=" ")
    #target_compile_definitions(replika PRIVATE GRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)
 */
/*
    To change the default parsing behaviour of the CSV parser

    Snippet from the msbuild project file(named here project.xml)
    <ItemDefinitionGroup>
        <ClCompile>
            <PreprocessorDefinitions Condition="'$(CSVPreprocessorDefinitions)'=='yes'">CSV_EXAMPLE_APPLICATION;CSV_NOT_ALLOW_EMPTY_TOKENS;GRAMMAR_END_OF_TOKEN_MARKER=" "</PreprocessorDefinitions>
        </ClCompile>
    </ItemDefinitionGroup>  

    and then youe compile...
    @msbuild project.xml /p:CSVPreprocessorDefinitions=yes
 */

#define COMMAND "h -h help --help ? /? (Displays help screen)\n\
                 v -v version --version /v (Displays version number)\n\
                 e epoch --epoch /e (Sets epoch or number of times the training loop would run)\n\
                 corpus --corpus (Path to the file which has the training data)\n\
                 verbose --verbose (Display of output, verbosly)\n\
                 lr --lr (Set learning rate)"


#include "../lib/argsv-cpp/lib/parser/parser.hh"

int main(int argc, char *argv[])
{
    ARG arg_epoch, arg_help;

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
    if (arg_epoch.i)
    {        
        ARG_PTR arg = arg_epoch.next;
        FIND_ARG_BLOCK(argv, argc, argsv_parser, arg_epoch);
        
        arg = &arg_epoch;
        do 
        {
            std::cout<<"i = "<<arg->i<<", j = "<<arg->j<<", argc = "<<arg->argc<<std::endl;
            arg = arg->next;
        } while (arg != NULL);         
    }
    
    return 0;
}
