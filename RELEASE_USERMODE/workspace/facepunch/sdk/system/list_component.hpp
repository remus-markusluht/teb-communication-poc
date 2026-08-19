#pragma once

namespace system_collections {

	template<typename T>
	class list_component : public sdk::c_base_class {
	public:
		declare_member( list_hash_set<T>*, instance_list, 0x0 );
	};
}