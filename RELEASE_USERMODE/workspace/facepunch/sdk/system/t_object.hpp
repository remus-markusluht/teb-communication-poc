#pragma once

namespace system_collections {

	template<typename T>
	class t_object : public sdk::c_base_class {
	public:
		// protected TObject[] method
		declare_member( array<T>*, objects_array, 0x0 );
	};
}