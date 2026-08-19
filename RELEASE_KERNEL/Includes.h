#pragma once
#define DEBUGPRINT TRUE
#define ADVANCEDPRINT TRUE

// KMDF0
#include <ntifs.h>
#include <ntddk.h>
#include <ntdef.h>
#include <ntimage.h>
#include <minwindef.h>
#include <stdarg.h>

// KMDF1
#include "static/encrypt.h"
#include "static/imports.h"
#include "static/oxorany/oxorany.h"

// IAT
#include "module/ia32/ia32.h"
#include "module/module.h"
#include "interface/interface.h"

// PAGE
#include "methods/page/page1.h"
#include "methods/page/page2.h"


// METHODS
#include "methods/rwx/rwx.h"
#include "methods/write/write.h"
#include "methods/read/read.h"
#include "methods/moduleaddress/moduleaddress.h"

#include "module/exports.h"

extern uintptr_t ntos_image_base;
extern uintptr_t kernel_base;
extern UINT64 SavedCR3;

// DATA0
#define win_1803 17134
#define win_1809 17763
#define win_1903 18362
#define win_1909 18363
#define win_2004 19041
#define win_20H2 19569
#define win_21H1 20180