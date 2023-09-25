#include <iostream>

#include <map>
#include <string>
#include <functional>

class ProblemRegistry
{
public:
    using String = std::string;
    using FunctionType = std::function<void()>;
    using NestedMap = std::map<String, std::map<String, FunctionType>>;

    /* Returns instance of singleton */
    static ProblemRegistry &get_instance()
    {
        static ProblemRegistry instance;
        return instance;
    }

    /* Add a function to the registry (ie registry[folder_name][problem_name]) */
    void register_fn(const String &folder, const String &problem, FunctionType func)
    {
        // Init empty inner map for folder if new
        if (functions.find(folder) == functions.end())
            functions[folder];

        // Add function for folder and problem
        functions[folder][problem] = func;
    }

    /* Function getter */
    FunctionType get_fn(const String &folder, const String &problem)
    {
        return functions[folder][problem];
    }

private:
    NestedMap functions;
};

// Creates a local object to register problem function in constructor ahead of time
#define REGISTER_PROBLEM(folder, func)                                            \
    namespace                                                                     \
    {                                                                             \
        struct ProblemRegistrar_##func                                            \
        {                                                                         \
            ProblemRegistrar_##func()                                             \
            {                                                                     \
                ProblemRegistry::get_instance().register_fn(folder, #func, func); \
            }                                                                     \
        };                                                                        \
                                                                                  \
        ProblemRegistrar_##func g_functionRegistrar_##func;                       \
    }
