// Copyright [2021] <Wojtek>"
#ifndef BABLIB_SYSTEM_HPP_
#define BABLIB_SYSTEM_HPP_

#include "must_have.hpp"

namespace babel::SYSTEM{

    /**
*  @brief  Return number of threads
*  \Example_1 return 16
*  \Example_2 return 8
*  @return Number of processor thread
*/
    [[nodiscard]] auto number_of_threads() noexcept
    {
        if constexpr( babel::COMPILER_IS_64B )
        {
            return std::thread::hardware_concurrency();
        } else
        {
#ifdef _WIN32
            SYSTEM_INFO SysInfo;
            GetSystemInfo(&SysInfo);
            return SysInfo.dwNumberOfProcessors;
#endif
#ifdef linux
            return sysconf(_SC_NPROCESSORS_ONLN);
#endif
        }
    }


    /**
*  @brief  Return thread id as string (default this_thread)
*  \Example_1 return 1
*  \Example_2 return 2
*  @return Return std::string
*/
    [[nodiscard]] std::string threadID_as_string(const std::thread::id ID = std::this_thread::get_id()) noexcept
    {
        std::stringstream StringStream;
        StringStream << ID;
        return StringStream.str();
    }

    /**
*  @brief  Call function in another thread (Function must be void)
*  @param  Func Function to call
*  @param  Args Arguments to function
*  @return Return std::thread, remember to join this thread before end program
*/
    template< typename Func, typename ... Args >
    requires(babel::CONCEPTS::IS_VOID_RETURN<Func, Args...>)
    [[nodiscard]] std::thread call_function_on_another_thread(Func
    function,
    Args &&... args
    ) noexcept{
    std::thread TemporaryThread(function, std::forward<Args>(args)...);
    return
    TemporaryThread;
}


}  // namespace babel::SYSTEM
#endif  // BABLIB_SYSTEM_HPP_
