# include "Controller.hpp"

Array<int32> getWherePush()
{
    Array<int32> result = {-1, -1};
    int32 size = System::EnumerateGamepads().size();
    ClearPrint();
    
    for(int32 i : step(size))
    {
        if (const auto gamepad = Gamepad(i))
        {
            for (auto [j, button] : Indexed(gamepad.buttons))
            {
                if(button.pressed()){
                    result = {i, (int32)j};
                    break;
                }
            }
        }
        if(result[0] != -1) break;
    }

    return result;
}
