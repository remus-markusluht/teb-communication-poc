#pragma once

namespace unity {

	namespace physx {

		class np_scene;

		class np_physics : public sdk::c_base_class {
		public:
			// physx::NpPhysics::getScenes
			// v9 = (char *)this[1] + 8 * v5 - (char *)a2
			// itterates at +0x8
			declare_member( unity::native_array<np_scene*>, scenes, 0x8 );
		};

		class np_actor : public sdk::c_base_class {
		public:
			declare_member( ::physx::NpRigidDynamic, rigid_dynamic, 0x0 );
		};

		class np_scene : public sdk::c_base_class {
		public:
			// physx::NpScene::getPhysics
			static np_physics* get_physics( )
			{
				static np_physics* ins = nullptr;
				if ( !ins )
					ins = g_vm->read<np_physics*>( g_vm->unity_player + 0x1C3B3D0 );

				return ins;
			}

			// physx::NpScene::getActors(__int64 a1, _WORD *a2, __int64 a3, unsigned int a4, unsigned int a5)
			// v14 = *(_QWORD *)(v13 + *(_QWORD *)(a1 + 0x23C8)); accessing array of actors
			// only accessiable from a scene not from physics ptr
			declare_member( unity::native_array<np_actor*>, actors, 0x23C8 );
		};
	}
}