#pragma once

namespace sdk {

	class c_main_camera : public c_rust_camera<c_main_camera> {
	public:
		inline static c_main_camera* klass( )
		{
			static c_main_camera* ins = nullptr;
			if ( !ins )
				ins = g_vm->read_chain<c_main_camera*>( g_vm->game_assembly, { 0x0, 0xB8 } );

			return ins;
		}

		declare_member( c_camera*, main_camera, 0x0 );
	};
}