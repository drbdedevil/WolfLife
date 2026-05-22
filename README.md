# WolfLife
Project for demonstration how works autonomous agents.

<img width="1276" height="720" alt="image" src="https://github.com/user-attachments/assets/4353ae5b-d999-4daa-8e29-0b426afe33f7" />

The simulation implements Craig Reynolds' steering behaviors. All entities inherit storing position, velocity, acceleration, max_force and max_speed.

🐺 Wolf (player‑controlled)
Does not use autonomous steeringб its target position is forced to mouse coordinates (GetMousePosition()). Moves via kinematic easing or arrive steering.

🐑 Sheep (flocking)
Three weighted rules applied:
- Separation: avoid nearby sheep
- Alignment: match velocity with neighbors
- Cohesion: steer toward flock center
No predator avoidance: pure flocking.

🐕 Dogs (pursuers)
Finite State Machine (FSM):
- Patrol: follow a predefined path (array of waypoints)
- Pursuit: triggered when wolf eats a sheep or enters dog's vision cone. Pursuit predicts wolf's future position: future_pos = wolf.pos + wolf.vel * factor.
- Collision with wolf reduces its lives; dog returns to patrol.

🛠 Tech stack
- C++
- Raylib (rendering, input, collisions)
- CMake + Conan (dependency management)

Full info: https://natureofcode.com/autonomous-agents/
