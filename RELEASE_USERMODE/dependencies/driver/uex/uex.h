#pragma once
#include "../../Includes.h"

typedef enum uex_error {
	SUCCESS = 0x0,
	ERR = 0x1
};

namespace interface_thread {
	typedef enum request_type {
		GETBASE = 0x22,
		GETDTB = 0x31,
		READ = 0x14,
		WRITE = 0x15,
		READ_BATCH = 0x16,
		KBOOT = 0x92,
		GETMODULE = 0x57,

		UNLOAD = 0x54,
		RESTORE = 0x77,
		HEARTBEAT = 0x82
	};

	static constexpr unsigned int max_batch_entries = 64;

	typedef struct _batch_read_entry
	{
		uintptr_t address;
		uintptr_t buffer;
		uintptr_t size;
	} batch_read_entry, * pbatch_read_entry;

	typedef struct _commargsd
	{
		bool is_client_running;
		bool is_operation_completed;
		UINT64 request_id;
		UINT64 completed_request_id;

		interface_thread::request_type operation_type;
		NTSTATUS operation_status;

		int target_pid;
		uintptr_t address;
		uintptr_t address2;

		uintptr_t buffer;
		uintptr_t size;
		unsigned int flags;
		unsigned int protection;
		unsigned int batch_count;
		unsigned int reserved0;
	} commargs, * pcommargs;

};

class UEX {
private:
	struct telemetry_stats {
		UINT64 total_commands = 0;
		UINT64 total_wait_us = 0;
		UINT64 max_wait_us = 0;
		UINT64 total_wait_loops = 0;
		UINT64 read_ops = 0;
		UINT64 read_bytes = 0;
		UINT64 write_ops = 0;
		UINT64 write_bytes = 0;
		UINT64 last_commands = 0;
		UINT64 last_wait_us = 0;
		UINT64 last_wait_loops = 0;
		UINT64 last_read_bytes = 0;
		UINT64 last_write_bytes = 0;
		std::chrono::steady_clock::time_point window_start = std::chrono::steady_clock::now();
	};

	telemetry_stats Telemetry{};
	PTEB CurrentTeb;
	int TlsIndexHooked;
	PVOID OriginalTls;
	UINT64 NextRequestId = 0;

	void update_metrics(const interface_thread::commargs& request, UINT64 wait_us, UINT32 wait_loops);
	void maybe_log_metrics(bool force = false);
public:
	int target_pid;
	PVOID CommArgs;
	uintptr_t base;
	UINT64 dtb;

	bool MenuOpen;
	template <typename type>
	bool set_registry_qword(const char* value_name, type request, const char* registry_path);

	//template <typename type>
	bool set_registry_dword(const char* value_name, DWORD request, const char* registry_path);

	bool set_registry_string(const char* value_name, const char* request, const char* registry_path);

	bool delete_registry_key(const char* subkey_path, const char* registry_path);

	uintptr_t GetBaseAddress();
	uintptr_t GetModuleBase(std::string module);

	bool get_process_pid(std::wstring module_name, std::uint32_t* process_id);

	void send_cmd(interface_thread::commargs& request);
	void send_heartbeat();
	void send_restore();
	void send_kboot();

	bool read_physical(uintptr_t address, void* buffer, size_t size);
	bool write_physical(uintptr_t address, void* buffer, size_t size);
	bool read_batch(const interface_thread::batch_read_entry* entries, size_t count);
	void dump_metrics(bool force = false);

	template <typename type>
	type read(uintptr_t address)
	{
		type return_value = { };
		read_physical(address, &return_value, sizeof(type));
		return return_value;
	}

	template <typename type>
	bool write(uintptr_t address, type value)
	{
		return write_physical(address, &value, sizeof(value));
	}

public:
	PTEB GetTEB();
	UINT64 GetDTB(uintptr_t BaseAddress);

	uex_error SetupRegistry();
	uex_error InitTebHook();
	uex_error RestoreTebHook();

	UEX* operator->()
	{
		return this;
	}
};

extern UEX client;