include_directories(${cpp-chat_SOURCE_DIR})

file(GLOB_RECURSE cpp-chat_HEADERS "${cpp-chat_SOURCE_DIR}/dapps/ip/tcp/chat/*.hpp")

add_custom_target(cpp-chat SOURCES ${cpp-chat_HEADERS})
