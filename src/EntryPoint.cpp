#include <iostream>
#include <Core/Base.hpp>
#include <exception>
#include <Core/Utility/Logger.hpp>

int main()
{
    mt::Base gameBase;
    try{
        gameBase.initialize();
        gameBase.run();
        gameBase.cleanup();
    }
    catch (std::runtime_error& e){
        mt::Logger::log(e.what(), mt::LogError);
    }
}

