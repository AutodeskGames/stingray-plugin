Project = Project or {}

Project.level_names = { default = "sample" }

-- Can provide a config for the basic project, or it will use a default if not.
local SimpleProject = require 'core/appkit/lua/simple_project'
SimpleProject.config = {
	standalone_init_level_name = Project.level_names.default,
	camera_unit = "core/appkit/units/camera/camera",
	camera_index = 1,
	shading_environment = nil, -- Will override levels that have env set in editor.
	create_free_cam_player = true, -- Project will provide its own player.
	exit_standalone_with_esc_key = true,
	dont_capture_mouse_at_startup = true
}

function Project.on_init_complete() end
function Project.update(dt) end
function Project.render() end
function Project.shutdown() end

return Project
