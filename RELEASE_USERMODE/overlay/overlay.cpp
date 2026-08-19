#include "overlay.h"

auto get_process_wnd(uint32_t pid) -> HWND
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}

auto set_window_target() -> void
{
	while (true) {
		GameWnd = get_process_wnd(client->target_pid);
		if (GameWnd) {
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);
			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX2 = Width / 2;
			ScreenCenterY2 = Height / 2;
			MoveWindow(my_wnd, GameRect.left, GameRect.top, Width, Height, true);
		}
	}
}

auto setup_window() -> void
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)set_window_target, 0, 0, 0);
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		DefWindowProcA,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		xorstr_("Windows Explorer"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	my_wnd = CreateWindowExA(NULL, xorstr_("Windows Explorer"), xorstr_("Windows Explorer"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(my_wnd, &margin);

	ShowWindow(my_wnd, SW_SHOW);
	UpdateWindow(my_wnd);
}

HRESULT directx_init() {
	std::cout << xorstr_("Initializing DirectX...") << std::endl;

	// Create the swap chain description
	DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};

	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

	swap_chain_desc.BufferCount = 2;
	swap_chain_desc.BufferDesc.Width = Width;
	swap_chain_desc.BufferDesc.Height = Height;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = my_wnd;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	D3D_FEATURE_LEVEL d3d_feature_lvl;
	const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_desc, &d3d_swap_chain, &p_device, &d3d_feature_lvl, &d3d_device_ctx);

	// Create the Direct3D device and swap chain

	std::cout << xorstr_("Direct3D device and swap chain created successfully.") << std::endl;

	// Create render target view

	ID3D11Texture2D* back_buffer;
	d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
	p_device->CreateRenderTargetView(back_buffer, NULL, &d3d_render_target);
	back_buffer->Release();

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	io.IniFilename = nullptr; // Disable ImGui INI file saving




	ImGui_ImplWin32_Init(my_wnd);
	ImGui_ImplDX11_Init(p_device, d3d_device_ctx);



	/* FONTS HERE */

	std::cout << xorstr_("DirectX initialization completed successfully.") << std::endl;
	return S_OK; // Return success
}

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	p_device->CreateRenderTargetView(pBackBuffer, nullptr, &d3d_render_target);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (d3d_render_target) { d3d_render_target->Release(); d3d_render_target = nullptr; }
}






void display_fps() {
	static int frame_count = 0;
	static float fps = 0.0f;
	static auto last_time = std::chrono::high_resolution_clock::now();

	// Increment frame count
	frame_count++;

	// Get the current time
	auto now = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);

	// Update FPS every second
	if (elapsed.count() >= 1000) {
		fps = frame_count / (elapsed.count() / 1000.0f);
		frame_count = 0;
		last_time = now;
	}

	// Render FPS using ImGui
	ImGui::SetNextWindowPos(ImVec2(10, 10)); // Top-left corner with 10px margin
	ImGui::SetNextWindowBgAlpha(0.5f);       // Semi-transparent background

	if (ImGui::Begin("FPS Counter", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
		ImGui::Text("FPS: %.1f", fps);
	}
	ImGui::End();
}

WPARAM render_loop() {
	bool last_streamproof_state = FALSE;
	HWND last_foreground_window = nullptr;
	const int target_fps = 1250; // Adjust as needed
	const auto target_frame_time = std::chrono::microseconds(1000000 / target_fps);

	ZeroMemory(&messager, sizeof(MSG));
	std::cout << xorstr_("Starting render loop...") << std::endl;

	for (;;) {
		auto frame_start = std::chrono::high_resolution_clock::now();

		while (PeekMessage(&messager, nullptr, 0, 0, PM_REMOVE)) {
			if (messager.message == WM_QUIT) {

			}
			TranslateMessage(&messager);
			DispatchMessage(&messager);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(my_wnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		ImGuiIO& io = ImGui::GetIO();
		POINT p;
		if (GetCursorPos(&p)) {
			ScreenToClient(my_wnd, &p);
			io.MousePos = ImVec2(static_cast<float>(p.x), static_cast<float>(p.y));
		}
		io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (client->MenuOpen) {
			ImGui::GetIO().MouseDrawCursor = true;
			while (ShowCursor(TRUE) < 0); // Ensure cursor is shown
		}
		else {
			ImGui::GetIO().MouseDrawCursor = false;
			while (ShowCursor(FALSE) >= 0); // Ensure cursor is hidden
		}

		/* RENDER PAGE */
		display_fps();
		drawLoop();


		ImGui::Render();
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		const float clear_color3[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
		d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color3);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		d3d_swap_chain->Present(0, 0);

		auto frame_end = std::chrono::high_resolution_clock::now();
		auto frame_duration = frame_end - frame_start;

		// Maintain target frame time without Sleep
		if (frame_duration < target_frame_time) {
			while (std::chrono::high_resolution_clock::now() - frame_start < target_frame_time) {
				std::this_thread::yield(); // Reduce CPU usage
			}
		}
	}

	// Cleanup ImGui and Direct3D
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (d3d_render_target) {
		d3d_render_target->Release();
	}
	if (d3d_swap_chain) {
		d3d_swap_chain->Release();
	}
	if (d3d_device_ctx) {
		d3d_device_ctx->Release();
	}
	if (p_device) {
		p_device->Release();
	}
	DestroyWindow(my_wnd);

	std::cout << xorstr_("Render loop ended.") << std::endl;
	return messager.wParam;
}