
#include <tclap/CmdLine.h>

#include <catch2/catch_session.hpp>

#include "ProblemRegistry.h"

#include <iostream>
#include <string>
#include <cstring>
#include <memory>

namespace
{
    void call_problem_fn(std::string problem)
    {
        // Get designated problem function from registry singleton
        ProblemRegistry reg = ProblemRegistry::get_instance();
        std::function<void()> problem_fn = reg.get_fn(problem);

        // Call the core function for the problem
        std::cout << "============================" << std::endl;
        std::cout << "|         Problem          |" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << std::endl;
        problem_fn();
    }

    int do_unit_tests(int argc, char **argv)
    {
        std::vector<char *> catch_argv;

        // Create new argv to pass to Catch2 cmd line
        for (int i = 0; i < argc; i++)
            catch_argv.push_back(argv[i]);

        // Sandwich problem name in brackets to filter unit tests
        size_t br_len = strlen(argv[1]) + 3; // Brackets (2) and null-terminator (1)
        std::unique_ptr<char> bracketed_arg(new char[br_len]);
        snprintf(bracketed_arg.get(), br_len, "[%s]", argv[1]);
        catch_argv[1] = bracketed_arg.get(); // Replace ptr to 'arg' w/ ptr to '[arg]'

        // Run tests with modified argv and return code
        std::cout << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "|        Unit Tests        |" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << std::endl;
        return Catch::Session().run(catch_argv.size(), catch_argv.data());
    }
}

int main(int argc, char **argv)
{
    try
    {
        // Create CLI
        TCLAP::CmdLine cmd("Dynamic programming examples.", ' ', "1.0");

        // Add arguments
        TCLAP::UnlabeledValueArg<std::string> problem_arg("problem", "Problem/file name", true, "", "string");
        cmd.add(problem_arg);

        // Parse and get values
        cmd.parse(argc, argv);
        std::string problem = problem_arg.getValue();

        // Get and call problem function from registry
        call_problem_fn(problem);

        // Unit testing (add bracket to problem name and run tests)
        return do_unit_tests(argc, argv);
    }
    catch (TCLAP::ArgException &e)
    {
        std::cerr << "Error: " << e.error() << " for argument " << e.argId() << std::endl;
        return 1;
    }

    return 0;
}
