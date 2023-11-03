# include "Controller.hpp"

Array<int8> getWherePush()
{
    Array<int8> result = {-1, -1};
    int8 size = System::EnumerateGamepads().size();
    ClearPrint();
    
    for(int8 i : step(size))
    {
        if (const auto gamepad = Gamepad(i))
        {
            for (auto [j, button] : Indexed(gamepad.buttons))
            {
                if(button.pressed()){
                    result = {i, (int8)j};
                    break;
                }
            }
        }
        if(result[0] != -1) break;
    }

    return result;
}
