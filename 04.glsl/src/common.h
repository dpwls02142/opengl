// main에서 include하기 위해 header 파일은 무조건 ifdef, define, endif 쌍으로 이뤄져야 함.

#ifndef __COMMON_H__ // define 매크로의 이름을 지정. 이는 중복되면 안됨.
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;
// ## -> klassName과 ptr 사이를 붙여주는 역할

/*
pointer를 사용하면 파일 안에 내용이 있든 없든 간에 memory에 계속 동적할당이 됨.
따라서 pointer를 직접 다루는 것 보단,
optional을 사용해 파일을 읽었는데 안에 내용이 있을 때만 문자열을 반환하는 것이 좋음.
*/
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__