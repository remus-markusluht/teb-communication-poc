#pragma once

namespace system_collections {

	template<typename TKey, typename TVal>
	class list_dictionary : public sdk::c_base_class {
	public:
		declare_member( buffer_list<TKey>*, keys, 0x0 );
		declare_member( buffer_list<TVal>*, vals, 0x0 );
	};
}
