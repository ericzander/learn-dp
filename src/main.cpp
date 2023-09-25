
#include "ProblemRegistry.h"
#include <tclap/CmdLine.h>

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    try
    {
        // Create CLI
        TCLAP::CmdLine cmd("Dynamic programming examples.", ' ', "1.0");

        // Add arguments
        TCLAP::UnlabeledValueArg<std::string> folder_arg("folder", "Folder of dp implementations", true, "", "string");
        cmd.add(folder_arg);
        TCLAP::UnlabeledValueArg<std::string> problem_arg("problem", "Problem/file name", true, "", "string");
        cmd.add(problem_arg);

        // Parse and get values
        cmd.parse(argc, argv);
        std::string folder = folder_arg.getValue();
        std::string problem = problem_arg.getValue();

        // Get and call function from registry
        ProblemRegistry reg = ProblemRegistry::get_instance();
        std::function<void()> fn = reg.get_fn(folder, problem);
        fn();
    }
    catch (TCLAP::ArgException &e)
    {
        std::cerr << "Error: " << e.error() << " for argument " << e.argId() << std::endl;
        return 1;
    }
}
