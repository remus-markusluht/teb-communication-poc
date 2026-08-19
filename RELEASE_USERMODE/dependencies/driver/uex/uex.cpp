#include "uex.h"
#include "../../utils/utils.h"
#include <sstream>

typedef void* (*RtlGetCurrentTeb_t)(void);
template <typename type>
bool UEX::set_registry_qword(const char* value_name, type request, const char* registry_path)
{
	HKEY handle_key = 0;
	auto result = RegCreateKeyExA(HKEY_LOCAL_MACHINE, registry_path, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr, &handle_key, nullptr);
	if (result != ERROR_SUCCESS) {
		return false;
	}

	result = RegSetValueExA(handle_key, value_name, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&request), sizeof(request));
	if (result != ERROR_SUCCESS) {
		return false;
	}

	RegCloseKey(handle_key);
	return true;
}

//template <typename type>
bool UEX::set_registry_dword(const char* value_name, DWORD request, const char* registry_path)
{
	HKEY handle_key = 0;
	auto result = RegCreateKeyExA(HKEY_LOCAL_MACHINE, registry_path, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr, &handle_key, nullptr);
	if (result != ERROR_SUCCESS) {
		return false;
	}

	result = RegSetValueExA(handle_key, value_name, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&request), sizeof(DWORD));
	if (result != ERROR_SUCCESS) {
		return false;
	}

	RegCloseKey(handle_key);
	return true;
}

bool UEX::set_registry_string(const char* value_name, const char* request, const char* registry_path)
{
	HKEY handle_key = 0;
	auto result = RegCreateKeyExA(HKEY_LOCAL_MACHINE, registry_path, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr, &handle_key, nullptr);
	if (result != ERROR_SUCCESS) {
		return false;
	}

	result = RegSetValueExA(handle_key, value_name, 0, REG_EXPAND_SZ, reinterpret_cast<const BYTE*>(&request), sizeof(request));
	if (result != ERROR_SUCCESS) {
		return false;
	}

	RegCloseKey(handle_key);
	return true;
}

bool UEX::delete_registry_key(const char* subkey_path, const char* registry_path)
{
	HKEY handle_key = 0;

	// Open the registry key with the required permissions
	auto result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, registry_path, 0, KEY_WRITE, &handle_key);
	if (result != ERROR_SUCCESS) {
		return false;
	}

	// Attempt to delete the specified subkey
	result = RegDeleteKeyA(handle_key, subkey_path);
	if (result != ERROR_SUCCESS) {
		RegCloseKey(handle_key);
		return false;
	}

	// Close the handle to the registry key
	RegCloseKey(handle_key);
	return true;
}



PTEB UEX::GetTEB() {
	PTEB teb = NtCurrentTeb();
	if (teb == nullptr) {
		return 0;
	}
	return teb;
}

bool UEX::get_process_pid(std::wstring module_name, std::uint32_t* process_id)
{
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!snapshot || snapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	PROCESSENTRY32W process_entry{ };
	process_entry.dwSize = sizeof(process_entry);
	Process32FirstW(snapshot, &process_entry);
	do {
		if (!module_name.compare(process_entry.szExeFile)) {
			*process_id = process_entry.th32ProcessID;
			return true;
		}
	} while (Process32NextW(snapshot, &process_entry));

	return false;
}


uex_error UEX::SetupRegistry() {
	if (this->set_registry_qword(xorstr_("rax1"), this->TlsIndexHooked, xorstr_("SOFTWARE\\NVIDIA Corporation\\Partners")) != true) {
		return uex_error::ERR;
	}

	if (this->set_registry_qword(xorstr_("rax2"), this->CurrentTeb, xorstr_("SOFTWARE\\NVIDIA Corporation\\Partners")) != true) {
		return uex_error::ERR;
	}

	if (this->set_registry_qword(xorstr_("rax3"), GetCurrentProcessId(), xorstr_("SOFTWARE\\NVIDIA Corporation\\Partners")) != true) {
		return uex_error::ERR;
	}
	return uex_error::SUCCESS;
}

uex_error UEX::InitTebHook() {
	this->CurrentTeb = nullptr;
	this->CommArgs = nullptr;
	this->NextRequestId = 0;

	/* Random TLS Slot for Hook */

	this->TlsIndexHooked = utils::generateRandomInteger(42, 59);

	this->CommArgs = VirtualAlloc(
		nullptr,
		sizeof(interface_thread::commargs),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (this->CommArgs == NULL) {
		return uex_error::ERR;
	}

	interface_thread::commargs baseargs;
	memset(&baseargs, 0, sizeof(baseargs));
	baseargs.is_client_running = TRUE;
	baseargs.is_operation_completed = TRUE;
	memcpy(this->CommArgs, &baseargs, sizeof(interface_thread::commargs));

	this->CurrentTeb = GetTEB();
	if (this->CurrentTeb == nullptr) {
		return uex_error::ERR;
	}

	PVOID OriginalTls_com = this->CurrentTeb->TlsSlots[this->TlsIndexHooked];
	this->OriginalTls = OriginalTls_com;

	this->CurrentTeb->TlsSlots[this->TlsIndexHooked] = this->CommArgs;
	if (this->CurrentTeb->TlsSlots[this->TlsIndexHooked] != OriginalTls_com) {

	}
	else {
		return uex_error::ERR;
	}

	return uex_error::SUCCESS;
}

uex_error UEX::RestoreTebHook() {
	this->CurrentTeb = GetTEB();
	if (this->CurrentTeb == nullptr) {
		return uex_error::ERR;
	}
	this->CurrentTeb->TlsSlots[this->TlsIndexHooked] = this->OriginalTls;
	return uex_error::SUCCESS;
}

void UEX::update_metrics(const interface_thread::commargs& request, UINT64 wait_us, UINT32 wait_loops) {
	this->Telemetry.total_commands++;
	this->Telemetry.total_wait_us += wait_us;
	this->Telemetry.total_wait_loops += wait_loops;
	if (wait_us > this->Telemetry.max_wait_us) {
		this->Telemetry.max_wait_us = wait_us;
	}

	switch (request.operation_type) {
	case interface_thread::request_type::READ:
		this->Telemetry.read_ops++;
		this->Telemetry.read_bytes += request.size;
		break;
	case interface_thread::request_type::WRITE:
		this->Telemetry.write_ops++;
		this->Telemetry.write_bytes += request.size;
		break;
	case interface_thread::request_type::READ_BATCH:
		this->Telemetry.read_ops += request.batch_count;
		this->Telemetry.read_bytes += request.address2;
		break;
	default:
		break;
	}
}

void UEX::maybe_log_metrics(bool force) {
	if (this->Telemetry.total_commands == 0) {
		return;
	}

	const auto now = std::chrono::steady_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->Telemetry.window_start).count();
	const bool window_ready = elapsed >= 1000;
	const bool count_ready = (this->Telemetry.total_commands % 250) == 0;

	if (!force && !window_ready && !count_ready) {
		return;
	}

	const UINT64 cmd_delta = this->Telemetry.total_commands - this->Telemetry.last_commands;
	const UINT64 wait_delta = this->Telemetry.total_wait_us - this->Telemetry.last_wait_us;
	const UINT64 read_bytes_delta = this->Telemetry.read_bytes - this->Telemetry.last_read_bytes;
	const UINT64 write_bytes_delta = this->Telemetry.write_bytes - this->Telemetry.last_write_bytes;
	const UINT64 wait_loop_delta = this->Telemetry.total_wait_loops - this->Telemetry.last_wait_loops;
	const double elapsed_seconds = elapsed > 0 ? static_cast<double>(elapsed) / 1000.0 : 0.001;
	const double avg_wait_us = cmd_delta > 0 ? static_cast<double>(wait_delta) / static_cast<double>(cmd_delta) : 0.0;
	const double read_mb_s = (static_cast<double>(read_bytes_delta) / (1024.0 * 1024.0)) / elapsed_seconds;
	const double write_mb_s = (static_cast<double>(write_bytes_delta) / (1024.0 * 1024.0)) / elapsed_seconds;

	std::ostringstream stream;
	stream << "[uex::telemetry] cmds=" << this->Telemetry.total_commands
		<< " delta_cmds=" << cmd_delta
		<< " avg_wait_us=" << static_cast<UINT64>(avg_wait_us)
		<< " max_wait_us=" << this->Telemetry.max_wait_us
		<< " wait_loops=" << wait_loop_delta
		<< " read_ops=" << this->Telemetry.read_ops
		<< " read_mb_s=" << std::fixed << std::setprecision(2) << read_mb_s
		<< " write_ops=" << this->Telemetry.write_ops
		<< " write_mb_s=" << std::fixed << std::setprecision(2) << write_mb_s
		<< "\n";

	silence(stream.str());
	this->Telemetry.last_commands = this->Telemetry.total_commands;
	this->Telemetry.last_wait_us = this->Telemetry.total_wait_us;
	this->Telemetry.last_wait_loops = this->Telemetry.total_wait_loops;
	this->Telemetry.last_read_bytes = this->Telemetry.read_bytes;
	this->Telemetry.last_write_bytes = this->Telemetry.write_bytes;
	this->Telemetry.window_start = now;
}

void UEX::dump_metrics(bool force) {
	this->maybe_log_metrics(force);
}

void UEX::send_cmd(interface_thread::commargs& request) {
	request.is_operation_completed = false;
	request.request_id = ++this->NextRequestId;
	request.completed_request_id = 0;

	auto started_at = std::chrono::steady_clock::now();
	std::memcpy(this->CommArgs, &request, sizeof(request));

	interface_thread::commargs* out_request = reinterpret_cast<interface_thread::commargs*>(this->CommArgs);
	UINT32 wait_loops = 0;
	while (!(out_request->is_operation_completed && out_request->completed_request_id == request.request_id)) {
		++wait_loops;
		if (wait_loops < 800) {
			YieldProcessor();
			continue;
		}

		if (wait_loops < 2400) {
			if (!SwitchToThread()) {
				YieldProcessor();
			}
			continue;
		}

		const DWORD backoff = wait_loops < 5000 ? 0 : 1;
		Sleep(backoff);
	}

	request = *out_request;
	const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - started_at).count();
	this->update_metrics(request, static_cast<UINT64>(elapsed), wait_loops);
	this->maybe_log_metrics();
}

void UEX::send_heartbeat() {

	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = 0x2A;
	request.buffer = 0x2A;
	request.size = 0x2A;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::HEARTBEAT;
	this->send_cmd(request);
}

void UEX::send_restore() {
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = 0x0;
	request.buffer = 0x0;
	request.size = 0;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::RESTORE;
	this->send_cmd(request);
}

void UEX::send_kboot() {
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = 0x0;
	request.buffer = 0x0;
	request.size = 0;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::KBOOT;
	this->send_cmd(request);
}

uintptr_t UEX::GetBaseAddress()
{
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = 0x0;
	request.buffer = 0x0;
	request.size = 0x0;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::GETBASE;
	this->send_cmd(request);
	return request.address2;
}

UINT64 UEX::GetDTB(uintptr_t BaseAddress)
{
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = BaseAddress;
	request.buffer = 0x0;
	request.size = 0x0;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::GETDTB;
	this->send_cmd(request);
	return request.address2;
}

bool UEX::read_physical(uintptr_t address, void* buffer, size_t size)
{
	void* rBuffer = VirtualAlloc(
		nullptr,
		size,
		MEM_COMMIT,
		PAGE_READWRITE
	);
	memset(rBuffer, 0x2A, size);
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = address;
	request.buffer = reinterpret_cast<uintptr_t>(rBuffer);
	request.size = size;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::READ;
	this->send_cmd(request);
	memcpy(buffer, rBuffer, size);
	VirtualFree(rBuffer, size, MEM_RELEASE);
	return true;
}

bool UEX::read_batch(const interface_thread::batch_read_entry* entries, size_t count) {
	if (!entries || count == 0) {
		return false;
	}

	size_t offset = 0;
	while (offset < count) {
		const size_t chunk_count = min(static_cast<size_t>(interface_thread::max_batch_entries), count - offset);
		interface_thread::commargs request{};
		request.is_client_running = true;
		request.address = 0;
		request.buffer = reinterpret_cast<uintptr_t>(&entries[offset]);
		request.size = chunk_count;
		request.batch_count = static_cast<unsigned int>(chunk_count);
		request.target_pid = this->target_pid;
		request.operation_type = interface_thread::request_type::READ_BATCH;
		this->send_cmd(request);
		if (!NT_SUCCESS(request.operation_status)) {
			return false;
		}
		offset += chunk_count;
	}

	return true;
}

uintptr_t UEX::GetModuleBase(std::string module)
{
	size_t bufferSize = module.size() + 1;
	void* rBuffer = VirtualAlloc(
		nullptr,
		bufferSize,
		MEM_COMMIT,
		PAGE_READWRITE
	);
	memcpy(rBuffer, module.c_str(), bufferSize);
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = 0x0;
	request.buffer = reinterpret_cast<uintptr_t>(rBuffer);
	request.size = bufferSize;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::GETMODULE;
	this->send_cmd(request);
	VirtualFree(rBuffer, bufferSize, MEM_RELEASE);
	return request.address2;
}

bool UEX::write_physical(uintptr_t address, void* buffer, size_t size)
{
	void* wBuffer = VirtualAlloc(
		nullptr,
		size,
		MEM_COMMIT,
		PAGE_READWRITE
	);
	memcpy(wBuffer, buffer, size);
	interface_thread::commargs request{};
	request.is_client_running = true;
	request.is_operation_completed = false;
	request.address = address;
	request.buffer = reinterpret_cast<uintptr_t>(wBuffer);
	request.size = size;
	request.target_pid = this->target_pid;
	request.operation_type = interface_thread::request_type::WRITE;
	this->send_cmd(request);
	memcpy(buffer, wBuffer, size);
	VirtualFree(wBuffer, size, MEM_RELEASE);
	return true;
}

UEX client;