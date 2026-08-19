#include "Includes.h"

#include <cstdlib>
#define CURL_STATICLIB
#include "Lib/curl/curl/curl.h"
#pragma comment(lib, "Lib/curl/curl/libcurl_a.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "AdvAPI32.lib")

PWCHAR ACToPWCHAR(const std::string& String)
{
	int BufferSize = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, nullptr, 0);
	if (BufferSize == 0)
	{
		return nullptr;
	}
	PWCHAR Buffer = new WCHAR[BufferSize];
	if (!MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, Buffer, BufferSize))
	{
		delete[] Buffer;
		return nullptr;
	}
	return Buffer;
}

int main() {
	SetConsoleTitleA(utils::generateRandomString(utils::generateRandomInteger(4, 8)).c_str());
	client->target_pid = GetCurrentProcessId();

	/* DUMP GDRV */
	/*
	for (size_t i = 0; i < sizeof(rawGdrvData); ++i) {
		rawGdrvData[i] = static_cast<unsigned char>(i % 256); // Example values
	}
	std::ofstream file(xorstr_("C:\\Windows\\System32\\Drivers\\gdrv.sys"), std::ios::binary);
	if (!file) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1;
	}
	file.write(reinterpret_cast<const char*>(rawGdrvData), sizeof(rawGdrvData));
	file.close();
	try {
		WindLoadDriver(ACToPWCHAR(xorstr_("C:\\Windows\\System32\\Drivers\\gdrv.sys")), ACToPWCHAR(xorstr_("C:\\Windows\\System32\\Drivers\\amdvmx86.sys")), TRUE);
	}
	catch (...) {
		silence(xorstr_("[+] Driver Already Loaded"));
	}

	*/

	silence(xorstr_("[+] Hooking Usermode TEB for Communication\n"));
	if (client->InitTebHook() != uex_error::SUCCESS) {
		silence(xorstr_("[+] Failed to exploit Usermode TEB\n"));
		instrict();
		*static_cast<int*>(nullptr) = TRUE; // Cause Deref Crash
	}
	silence(xorstr_("[+] Hooked Self Usermode TEB\n"));

	if (client->SetupRegistry() != uex_error::SUCCESS) {
		silence(xorstr_("[+] Failed to setup Registry Information\n"));
		instrict();
		*static_cast<int*>(nullptr) = TRUE; // Cause Deref Crash
	}
	silence(xorstr_("[+] Hooked Self Usermode Registry\n"));

	silence(xorstr_("[+] Waiting On Driver...\n"));
	client->send_heartbeat();
	silence(xorstr_("[+] Driver Responded To Heartbeat\n"));
	silence(xorstr_("[+] Restoring Self Usermode TEB\n"));
	if (client->RestoreTebHook() != uex_error::SUCCESS) {
		silence(xorstr_("[+] Failed to restore TEB Information\n"));
		instrict();
		*static_cast<int*>(nullptr) = TRUE; // Cause Deref Crash
	}

	client->delete_registry_key(xorstr_("Partners"), xorstr_("SOFTWARE\\NVIDIA Corporation"));
	// client->set_registry_string(xorstr_("ImagePath"), xorstr_("System32\\drivers\\amdvmx86.sys"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_string(xorstr_("Owners"), xorstr_("amdvmx86.inf"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_string(xorstr_("wdk.installers"), xorstr_("MSI"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_string(xorstr_("Group"), xorstr_("System Bus Extender"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_dword(xorstr_("ErrorControl"), DWORD(0x0), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_string(xorstr_("DisplayName"), xorstr_("AMD vmx86"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));
	// client->set_registry_string(xorstr_("ObjectName"), xorstr_("LocalSystem"), xorstr_("SYSTEM\\CurrentControlSet\\Services\\amdvmx86"));

	silence(xorstr_("[+] Sending Kboot Request for Driver Exploit\n"));
	silence(xorstr_("[--- hope you dont blue screen :3 ---]\n"));
	client->send_kboot(); // removed for safety
	silence(xorstr_("[+] Driver Recieved and Processed Kboot Request\n"));

	silence(xorstr_("[+] Getting Process Base Information\n"));
	uint32_t PIDA = NULL;
	while (PIDA == NULL) {
		client->get_process_pid(xorstr_(L"Spotify.exe"), &PIDA);
		Sleep(250);
	}
	client->target_pid = PIDA;
	silence(xorstr_("[+] Process pid [") + std::to_string(PIDA) + xorstr_("]\n"));

	client->base = client->GetBaseAddress();
	if (client->base == NULL) {
		silence(xorstr_("[+] Failed to get BaseAddress\n"));
		instrict();
		*static_cast<int*>(nullptr) = TRUE; // Cause Deref Crash
	}
	silence(xorstr_("[+] Cached Executable Base Address [") + std::to_string(client->base) + xorstr_("]\n"));

	client->dtb = client->GetDTB(client->base);
	if (client->dtb == NULL) {
		silence(xorstr_("[+] Failed to get DTB\n"));
		instrict();
		*static_cast<int*>(nullptr) = TRUE; // Cause Deref Crash
	}
	silence(xorstr_("[+] Cached Executable DTB [") + std::to_string(client->dtb) + xorstr_("]\n"));

	while (true) {
		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			__int64 rdd = client->read<__int64>(client->base);
			silence(xorstr_("read operation @ ") + std::to_string(rdd) + "\n");
		}
		else {
			Sleep(5);
		}
	}

	/*
	setup_window();
	Sleep(100);
	directx_init();
	Sleep(100);
	render_loop();
	*/
	return 0;
}