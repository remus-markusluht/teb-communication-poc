#pragma once
#include "../Includes.h"
#define _QWORD unsigned long long

namespace exports {
	[[ nodiscard ]]
	void rtl_init_unicode_string(
		PUNICODE_STRING destination_string,
		PCWSTR source_string
	);

	BOOLEAN rtl_delete_element_generic_table_avl(PRTL_AVL_TABLE Table, PVOID Buffer);
	PVOID rtl_lookup_element_generic_table_avl(PRTL_AVL_TABLE Table, PVOID Buffer);
	PPEB ps_get_process_peb(PEPROCESS Process);
	LONG_PTR ob_dereference_object(PVOID Object);

	BOOLEAN ex_acquire_exclusive_lite(PERESOURCE PiDDBLock, BOOL Wait);

	PKTHREAD ke_get_current_thread();

	void ex_release_resource_lite(PERESOURCE Resource);

	IA32::ethread* ps_get_next_process_thread(PEPROCESS Process, PETHREAD Thread);

	void* ps_get_process_section_base_address(
		PEPROCESS Process
	);

	void mm_unmap_io_space(
		PVOID BaseAddress,
		SIZE_T NumberOfBytes
	);

	void* mm_map_io_space_ex(
		PHYSICAL_ADDRESS PhysicalAddress,
		SIZE_T NumberOfBytes,
		ULONG Protect
	);

	NTSTATUS ps_lookup_thread_by_thread_id(
		std::uint32_t ThreadId,
		IA32::ethread** Thread
	);

	uintptr_t get_physical_address(
		uintptr_t virtual_address
	);

	NTSTATUS ps_lookup_process_by_process_id(HANDLE ProcessID,
		PEPROCESS* Process
	);

	void ke_query_system_time_precise(PLARGE_INTEGER CurrentTime);

	PVOID mm_get_system_routine_address(
		PUNICODE_STRING SystemRoutineName
	);

	NTSTATUS zw_query_system_information(
		SYSTEM_INFORMATION_CLASS SystemInformationClass,
		PVOID                    SystemInformation,
		ULONG                    SystemInformationLength,
		PULONG                   ReturnLength
	);

	PERESOURCE GetPsLoaded();

	PEPROCESS io_get_current_process();

	BOOLEAN ps_is_system_thread(
		IA32::ethread* Thread
	);

	IA32::ethread* ps_get_current_thread();

	IA32::ethread* get_system_thread();

	
	NTSTATUS zw_close(
		HANDLE handle
	);

	
	NTSTATUS zw_open_key(
		PHANDLE key_handle,
		ACCESS_MASK desired_access,
		POBJECT_ATTRIBUTES object_attributes
	);

	
	NTSTATUS zw_query_value_key(
		HANDLE key_handle,
		PUNICODE_STRING value_name,
		KEY_VALUE_INFORMATION_CLASS key_value_information_class,
		void* key_value_information,
		ULONG length,
		PULONG result_length
	);

	NTSTATUS ps_create_system_thread(
		PHANDLE ThreadHandle,
		ULONG DesiredAccess,
		POBJECT_ATTRIBUTES ObjectAttributes,
		HANDLE ProcessHandle,
		PCLIENT_ID ClientId,
		PKSTART_ROUTINE StartRoutine,
		void* StartContext
	);

	NTSTATUS mm_copy_memory(
		void* target_address,
		MM_COPY_ADDRESS source_address,
		SIZE_T number_of_bytes,
		ULONG flags,
		PSIZE_T number_of_bytes_transferred
	);

	void* map_io_space_ex(
		PHYSICAL_ADDRESS physical_address,
		SIZE_T number_of_bytes,
		ULONG protect
	);

	void mm_free_contiguous_memory(
		void* BaseAddress
	);

	uintptr_t get_virtual_for_physical(
		uintptr_t physical_address
	);

	void* mm_map_io_space(
		uintptr_t physical_address,
		SIZE_T number_of_bytes
	);

	
	void* mm_allocate_contiguous_memory(
		SIZE_T NumberOfBytes
	);

	PPHYSICAL_MEMORY_RANGE mm_get_physical_memory_ranges();

	NTSTATUS mm_copy_virtual_memory(
		PEPROCESS source_process,
		void* source_address,
		PEPROCESS target_process,
		void* target_address,
		SIZE_T buffer_size,
		KPROCESSOR_MODE previous_mode,
		PSIZE_T return_size
	);
	
	
	void* ex_allocate_pool(
		POOL_TYPE pool_type,
		SIZE_T number_of_bytes
	);

	
	void ex_free_pool_with_tag(
		void* base_address,
		ULONG tag
	);


	bool ps_get_process_exit_status(
		uintptr_t Process
	);

	uintptr_t ps_initial_system_process();

	unicode_string_t* ps_query_full_process_image_name(
		std::uintptr_t process
	);


}

using namespace exports;