cmake_minimum_required(VERSION 3.2 FATAL_ERROR)


set(TARGET_NAME 3DEngine)

project(${TARGET_NAME} CXX C)

include(settings.cmake)

add_executable(${TARGET_NAME}
	"src/main.cpp"
)

target_sources(${TARGET_NAME}
PUBLIC
	"includes/Application.h"
	"includes/components/Component.h"
	"includes/components/Transform.h"
	"includes/components/Mesh.h"
	"includes/components/Material.h"
	"includes/components/Animation.h"
	"includes/engine/Entity.h"
	"includes/engine/GameInstance.h"
	"includes/engine/Scene.h"
	"includes/helper/Clock.h"
	"includes/helper/Matrix4x4.h"
	"includes/helper/Singleton.h"
	"includes/helper/Types.h"
	"includes/helper/Utils.h"
	"includes/helper/Vector3.h"
	"includes/helper/Quaternion.h"
	"includes/rendering/Renderer.h"
	"includes/rendering/Window.h"
PRIVATE
	"src/Animation.cpp"
	"src/Application.cpp"
	"src/Clock.cpp"
	"src/Component.cpp"
	"src/Entity.cpp"
	"src/GameInstance.cpp"
	"src/Matrix4x4.cpp"
	"src/Quaternion.cpp"
	"src/Renderer.cpp"
	"src/Scene.cpp"
	"src/Transform.cpp"
	"src/Utils.cpp"
	"src/Vector3.cpp"
	"src/Window.cpp"
)

target_include_directories(${TARGET_NAME}
PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

target_link_libraries(${TARGET_NAME}
	D3D11
	DXGI
	D3DCompiler
)

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
