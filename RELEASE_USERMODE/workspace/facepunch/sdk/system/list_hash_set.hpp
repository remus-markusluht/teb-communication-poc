#pragma once

namespace system_collections {

	template<typename T>
	class list_hash_set : public sdk::c_base_class {
	public:
		using _val2idx = dictionary<T, int>*;
		declare_member( _val2idx, val2idx, 0x0 );

		using _idx2val = dictionary<int, T>*;
		declare_member( _idx2val, idx2val, 0x0 );

		declare_member( buffer_list<T>*, vals, 0x0 );
	};
}