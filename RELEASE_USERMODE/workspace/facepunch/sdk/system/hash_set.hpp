#pragma once

namespace system_collections {

	template<typename T>
	struct slot {
		int hash_code;
		int next;
		T value;
	};

	template<typename T>
	class hash_set : public sdk::c_base_class {
	public:
		declare_member( array<slot<T>>*, _slots, 0x10 );
		declare_member( int, _count, 0x20 );
	};
}