#pragma once

namespace system_collections {

	class c_singleton_component_base : public sdk::c_base_class {
	public:
	};

	template<typename T>
	class c_singleton_component : public c_singleton_component_base {
	public:
		declare_member( T, instance, 0x0 );
	};
}