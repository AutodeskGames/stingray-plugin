-- @adoc lua
-- @exa my_sample Sample Title
-- @des My sample description.

function pick_unit(world, camera)
    if SimpleProject then
        world = world or SimpleProject.world
        camera = camera or stingray.Unit.camera(SimpleProject.camera_unit, 1)
    end
    -- get the X and Y screen coordinates to pick from.
    local width, height = stingray.Application.back_buffer_size()
    local pick_x_pos = math.floor(width / 2)
    local pick_y_pos = math.floor(height / 2)
    if stingray.Window and stingray.Window.show_cursor() then
        pick_x_pos = stingray.Mouse.axis(stingray.Mouse.axis_id("cursor"), stingray.Mouse.RAW, 3).x
        pick_y_pos = stingray.Mouse.axis(stingray.Mouse.axis_id("cursor"), stingray.Mouse.RAW, 3).y
    end
    local depth = 0.5

    -- translate the screen coordinates to a position in 3D world space.
    local screen_pos_in_scene = stingray.Camera.screen_to_world(camera, stingray.Vector3(pick_x_pos, pick_y_pos, 0), depth)
    local camera_position = stingray.Camera.world_position(camera)

    -- get the direction from the camera position to the 3D starting coordinates.
    local camera_to_mouse_direction = stingray.Vector3.normalize(screen_pos_in_scene  - camera_position);

    -- cast a physics ray into the scene, starting from the camera position, in the
    -- direction toward the picked screen position.
    local physics_world = stingray.World.physics_world(world)
    local foundCollision, collisionPos, distance, normal, actor =
            stingray.PhysicsWorld.raycast(
                physics_world, camera_position, camera_to_mouse_direction, "closest"
                )

    local actor_obj = nil
    if (foundCollision) then -- we have hit a unit.
        actor_obj = stingray.Actor.unit(actor)
    end
    return actor_obj, collisionPos, distance, normal, actor
end
-- @adoc lua
-- @exa my_sample Sample Title
