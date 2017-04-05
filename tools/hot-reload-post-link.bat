@echo OFF

if "%~1"=="" (
	goto usage
)

if "%~2"=="" (
	goto usage
)

if "%~3"=="" (
	goto usage
)

setlocal enableExtensions enableDelayedExpansion

set plugin_build_folder=%1
set plugin_output_folder=%2
set plugin_base_name=%3

rem Try to clean out previously moved loaded dll

set old_dll_plugin_wildcard=%plugin_output_folder%%plugin_base_name%.*.dll.old
set old_pdb_plugin_wildcard=%plugin_output_folder%%plugin_base_name%.*.pdb.old

del %old_dll_plugin_wildcard% >nul 2>nul
del %old_pdb_plugin_wildcard% >nul 2>nul

rem Try to copy the newly built plugins to the plugin folder

set dll_build_path=%plugin_build_folder%%plugin_base_name%.dll
set pdb_build_path=%plugin_build_folder%%plugin_base_name%.pdb

set dll_plugin_path=%plugin_output_folder%%plugin_base_name%.dll
set pdb_plugin_path=%plugin_output_folder%%plugin_base_name%.pdb

robocopy /XO /r:0 /ns /nc /nfl /ndl /np %plugin_build_folder% %plugin_output_folder% %plugin_base_name%.dll %plugin_base_name%.pdb  >nul

if %ERRORLEVEL% LSS 8 goto :end

rem Moving currently loaded plugin so we can copy in our new build of the plugin

set clean_time=%TIME::=_%
set clean_time=%clean_time:,=_%

set old_dll_plugin_name=%plugin_base_name%.%clean_time%.dll.old
set old_pdb_plugin_name=%plugin_base_name%.%clean_time%.pdb.old

set old_dll_plugin_path=%plugin_output_folder%%old_dll_plugin_name%
set old_pdb_plugin_path=%plugin_output_folder%%old_pdb_plugin_name%

rem Move the loaded plugins out of the way for our newly built plugin

if exist %dll_plugin_path% (
	rename %dll_plugin_path% %old_dll_plugin_name%
)

if exist %pdb_plugin_path% (
	rename %pdb_plugin_path% %old_pdb_plugin_name%
)

rem Copy the newly built plugins to the plugin folder

copy %plugin_build_folder%%plugin_base_name%.dll %plugin_output_folder%
copy %plugin_build_folder%%plugin_base_name%.pdb %plugin_output_folder%

goto :end

:usage
    echo Usage: %~nn0 plugin_build_folder plugin_output_folder plugin_base_name
    goto :end

:end

exit /b 0
