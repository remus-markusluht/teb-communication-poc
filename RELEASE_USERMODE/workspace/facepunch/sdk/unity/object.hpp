#pragma once

namespace unity {

	template<typename T>
	struct c_int_ptr {
		T m_value;
		c_int_ptr* zero;
	};

	class c_component;

	class c_object : public il2cpp::c_object {
	public:
		declare_member( c_int_ptr<c_component*>, native_component, 0x0 );
	};
}