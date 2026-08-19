#include "uex.h"
#include "../../utils/utils.h"

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

void UEX::send_cmd(interface_thread::commargs& request) {
	std::memcpy(this->CommArgs, &request, sizeof(request));

	interface_thread::commargs* out_request = reinterpret_cast<interface_thread::commargs*>(this->CommArgs);
	while (!out_request->is_operation_completed) {
		Sleep(2);
	}

	request = *out_request;
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