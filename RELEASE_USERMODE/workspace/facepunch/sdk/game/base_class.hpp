#pragma once

namespace sdk {

	class c_base_class {
	public:
		static bool is_valid_address( u64 ptr ) {
			if ( ( ptr < 0xFFFFFFFFFF ) || ( ptr > 0x2FFFFFFFFFF ) || !memory::is_valid( ptr ) )
				return false;
			return true;
		}

		static bool is_class( const std::string& class_name, const std::string& name ) { return class_name == name; }
		static bool is_prefab( const std::string& prefab_name, const std::string& prefab ) { return prefab_name == prefab; }

		u64 get_current_class( ) const { return current_address; }

		bool is_valid( ) const {
			return is_valid_address( current_address );
		}

		template <typename T>
		T cast( ) const {
			return reinterpret_cast< T >( current_address );
		}
	};
}