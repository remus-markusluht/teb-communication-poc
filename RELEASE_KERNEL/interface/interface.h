#pragma once
#include "../Includes.h"

bool copy_thread_flags();

namespace scan
{
	bool check_mask(
		const char* base,
		const char* pattern,
		const char* mask
	);

	uintptr_t find_pattern(
		uintptr_t base_address,
		uint64_t size_of_address,
		const char* pattern,
		const char* mask
	);


	void* split_memory(
		void* start,
		size_t size,
		const void* pattern
	);

}

namespace interface_thread {
	typedef enum request_type {
		GETBASE = 0x22,
		GETDTB = 0x31,
		READ = 0x14,
		WRITE = 0x15,
		KBOOT = 0x92,
		GETMODULE = 0x57,

		UNLOAD = 0x54,
		RESTORE = 0x77,
		HEARTBEAT = 0x82
	};

	typedef struct _commargsd
	{
		bool is_client_running;
		bool is_operation_completed;

		interface_thread::request_type operation_type;
		NTSTATUS operation_status;

		int target_pid;
		uintptr_t address;
		uintptr_t address2;

		uintptr_t buffer;
		uintptr_t size;
		unsigned int flags;
		unsigned int protection;
	} commargs, * pcommargs;
}

class interface {
private:
	cr3 process_cr3{ };
	unsigned int client_id = 0;
	const wchar_t* key_path = nullptr;
public:
	PVOID CommBufferCached;
	UINT64 ProcessDTB;
	void* ProcessBase;

	PEPROCESS client_process{ };
	static inline HANDLE thread_handle = nullptr;

	int TlsIndex;
	PVOID TEBAddress;
public:
	NTSTATUS GetMEM(interface_thread::pcommargs out_request);

	NTSTATUS SendMEM(interface_thread::pcommargs request);
	NTSTATUS WriteBUFFER(PVOID Buffer);

	NTSTATUS setup();
	bool find_gadget(uintptr_t driver_base_address, uintptr_t* used_jmp_rcx_gadget);
	NTSTATUS create_gadget(uintptr_t driver_base_address, void* thread_function);

	template <typename T>
	[[ nodiscard ]]
	bool GetRegistryValue(const wchar_t* valueName, T& outValue);

	void set_registry_key_path(wchar_t* registry_key_path) {
		this->key_path = registry_key_path;
	};

	void set_client_id(unsigned int c_client_id) {
		this->client_id = c_client_id;
	}

	PEPROCESS get_client_process() {
		return this->client_process;
	}

	interface* operator->()
	{
		return this;
	}
};

extern interface c_client;