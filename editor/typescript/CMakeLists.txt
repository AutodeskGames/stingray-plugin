cmake_minimum_required(VERSION 3.6)
project(editor_typescript)

add_typescript_project(${PROJECT_NAME} ${PROJECT_SOURCE_DIR} tsconfig.json)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${EDITOR_PLUGINS_FOLDER_NAME}")
