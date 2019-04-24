CollectIncludeDirectories(
  ${KARGATUM_SYSTEM_DIR}
  PUBLIC_INCLUDES)

target_include_directories(game-interface
  INTERFACE
    ${PUBLIC_INCLUDES})