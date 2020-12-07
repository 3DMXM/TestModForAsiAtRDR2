/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "script.h"
#include <string>
#include <vector>
#include "keyboard.h"

void update()
{
	// 我们的主代码将写在这里

	if (IsKeyDown(120))
	{
		// 如果玩家按下键值为120的键（F9）时，执行代码
		if (RADAR::IS_WAYPOINT_ACTIVE())
		{
			//如果玩家已添加标记点

			Vector3 coords = RADAR::GET_WAYPOINT_COORDS_3D();	// 获取标记点的3D坐标

			Entity entity = PLAYER::PLAYER_PED_ID();	// 获取玩家实体
			if (PED::IS_PED_ON_MOUNT(entity)) {			// 玩家是否在坐马上
				entity = PED::GET_MOUNT(entity);		// 如果在则获取玩家正在使用的马
			}
			else if (PED::IS_PED_IN_ANY_VEHICLE(entity, FALSE)) {	// 如果没在则继续判断是否在载具中
				entity = PED::GET_VEHICLE_PED_IS_USING(entity);		// 如果在则获取玩家正在使用的载具
			}

			if (!GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 100.0, &coords.z, FALSE))	// 获取标记点中的地面Z轴坐标
			{
				static const float groundCheckHeight[] = {
					100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
					450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
				};
				for each (float height in groundCheckHeight)
				{
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, height, 0, 0, 1);
					WAIT(100);
					if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, height, &coords.z, FALSE))
					{
						coords.z += 3.0;
						break;
					}
				}
			}

			ENTITY::SET_ENTITY_COORDS(entity, coords.x, coords.y, coords.z, 0, 0, 1, FALSE);	// 传送玩家到指定坐标
		}
	}
}

void main()
{		
	while (true)
	{
		update();
		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
