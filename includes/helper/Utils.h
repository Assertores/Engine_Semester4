#pragma once

#define SAFE_DELETE(x) { if (x) { delete(x); (x) = nullptr; } }
#define SAFE_RELEASE(x) { if (x) { (x)->Release(); (x) = nullptr; } }
#define SAFE_DELETE_ARR(x) { if (x) { delete[](x); (x) = nullptr; } }

#define BYTE_TO_MEGABYTE 9.5367e-7f
