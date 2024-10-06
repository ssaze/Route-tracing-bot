
I developed this project to create a robust pathfinding algorithm for a robotic companion attempting to escape a complex moon-like space station. After breaking out of the detention level, the robot must navigate a 3D maze comprised of multiple levels and varying terrain, all while avoiding obstacles and leveraging the station's elevator system to reach the hangar.

## Features

This project incorporates several advanced features:

- **Search Algorithms**: Implementations of both Breadth-First Search (BFS) and Depth-First Search (DFS) enable the robot to explore the maze efficiently, selecting the optimal path to the hangar based on user-defined search strategies.
  
- **Dynamic Input Handling**: The program supports two distinct input modes:
  - **Map Mode**: A 2D grid representation of the space station levels, where characters represent various terrain types, including walls, floor spaces, and key locations (starting point and hangar).
  - **Coordinate List Mode**: A compact format that specifies coordinates for non-floor characters, allowing for rapid parsing of large maps.

- **Flexible Command-Line Interface**: Users can specify their preferred routing method (stack for DFS or queue for BFS) and output format (map or coordinate list) through intuitive command-line options.

- **Robust Error Checking**: The program performs comprehensive validation on input files and command-line arguments, ensuring that only valid configurations are processed. This includes checks for illegal characters, coordinate validity, and ensuring exactly one search option is selected.
