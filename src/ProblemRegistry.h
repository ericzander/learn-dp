#include <iostream>

#include <map>
#include <string>
#include <functional>

class ProblemRegistry
{
public:
    using String = std::string;
    using FunctionType = std::function<void()>;
    using Registry = std::map<String, FunctionType>;

    /* Returns instance of singleton */
    static ProblemRegistry &get_instance()
    {
        static ProblemRegistry instance;
        return instance;
    }

    /* Add a function to the registry (ie registry[folder_name][problem_name]) */
    void register_fn(const String &problem, FunctionType func)
    {
        // Add function for folder and problem
        functions[problem] = func;
    }

    /* Function getter */
    FunctionType get_fn(const String &problem)
    {
        return functions[problem];
    }

private:
    Registry functions;
};

// Creates a local object to register problem function in constructor ahead of time
#define REGISTER_PROBLEM(func)                                            \
    namespace                                                             \
    {                                                                     \
        struct ProblemRegistrar_##func                                    \
        {                                                                 \
            ProblemRegistrar_##func()                                     \
            {                                                             \
                ProblemRegistry::get_instance().register_fn(#func, func); \
            }                                                             \
        };                                                                \
                                                                          \
        ProblemRegistrar_##func g_functionRegistrar_##func;               \
    }
