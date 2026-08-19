#pragma once

namespace il2cpp {

	class c_class : public sdk::c_base_class {
	public:
		declare_member( u64, name_pointer, 0x10 );
		declare_member( u64, namespace_pointer, 0x10 );

	public:
		std::string get_name( ) const
		{
			return g_vm->read_string( name_pointer( ) );
		}

		std::string get_namespace( ) const
		{
			return g_vm->read_string( namespace_pointer( ) );
		}
	};
}