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
	// ���ǵ������뽫д������

	if (IsKeyDown(120))
	{
		// �����Ұ��¼�ֵΪ120�ļ���F9��ʱ��ִ�д���
		if (RADAR::IS_WAYPOINT_ACTIVE())
		{
			//����������ӱ�ǵ�

			Vector3 coords = RADAR::GET_WAYPOINT_COORDS_3D();	// ��ȡ��ǵ��3D����

			Entity entity = PLAYER::PLAYER_PED_ID();	// ��ȡ���ʵ��
			if (PED::IS_PED_ON_MOUNT(entity)) {			// ����Ƿ���������
				entity = PED::GET_MOUNT(entity);		// ��������ȡ�������ʹ�õ���
			}
			else if (PED::IS_PED_IN_ANY_VEHICLE(entity, FALSE)) {	// ���û��������ж��Ƿ����ؾ���
				entity = PED::GET_VEHICLE_PED_IS_USING(entity);		// ��������ȡ�������ʹ�õ��ؾ�
			}

			if (!GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 100.0, &coords.z, FALSE))	// ��ȡ��ǵ��еĵ���Z������
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

			ENTITY::SET_ENTITY_COORDS(entity, coords.x, coords.y, coords.z, 0, 0, 1, FALSE);	// ������ҵ�ָ������
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
