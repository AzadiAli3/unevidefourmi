BFS (Breadth-First Search)
# Fourmiliere Algorithms - Ant Colony Pathfinding

This project implements C++ algorithms for moving ants through different colony structures from source (`Sv`) to destination (`Sd`).

## Project Structure

```
algorithms/
├── fourmiliere.h           # Common header with base classes
├── fourmiliere_0.cpp       # Algorithm for fourmiliere zero (2 ants, parallel paths)
├── fourmiliere_1.cpp       # Algorithm for fourmiliere un (5 ants, linear path)
├── fourmiliere_2.cpp       # Algorithm for fourmiliere deux (5 ants, path with cycle)
├── fourmiliere_3.cpp       # Algorithm for fourmiliere trois (5 ants, branching paths)
├── fourmiliere_4.cpp       # Algorithm for fourmiliere quatre (10 ants, capacity constraints)
├── fourmiliere_5.cpp       # Algorithm for fourmiliere cinq (50 ants, complex network)
├── fourmiliere_6.cpp       # Algorithm for fourmiliere cinq (50 ants, complex network)
├── Makefile               # Build configuration
└── README.md              # This documentation
```

## Class Structure

### Base Classes

**Fourmi (Ant) Class:**
- `id`: Unique ant identifier
- `current_position`: Current station location
- `path`: Complete path taken by the ant
- `reached_destination`: Boolean flag for completion status
- `move_to(station)`: Move ant to specified station
- `print_path()`: Display the ant's complete journey

**Fourmiliere (Colony) Base Class:**
- `total_ants`: Number of ants in the colony
- `ants`: Vector of all ant objects
- `graph`: Adjacency list representation of the colony network
- `station_capacity`: Maximum capacity for each station
- `current_occupancy`: Current number of ants at each station
- `add_connection()`: Add path between stations
- `set_capacity()`: Set capacity limit for stations
- `can_move_to()`: Check if ant can move to station (capacity-aware)
- `find_shortest_path()`: BFS pathfinding algorithm
- `move()`: Pure virtual method for ant movement strategy
- `print_results()`: Display final results and statistics

## Algorithm Descriptions

### Fourmiliere 0 - Simple Parallel Paths
- **Ants:** 2
- **Strategy:** Direct parallel routing
- **Paths:** 
  - Ant 1: Sv → S1 → Sd
  - Ant 2: Sv → S2 → Sd
- **Complexity:** O(1) - Trivial parallel execution

### Fourmiliere 1 - Linear Sequential Path
- **Ants:** 5
- **Strategy:** Sequential movement through single path
- **Path:** Sv → S1 → S2 → Sd
- **Complexity:** O(n) where n is number of ants
- **Notes:** All ants follow same route sequentially

### Fourmiliere 2 - Cycle Avoidance
- **Ants:** 5
- **Strategy:** Shortest path avoiding cycles
- **Path:** Sv → S1 → S2 → Sd (ignoring Sd → Sv cycle)
- **Complexity:** O(n)
- **Notes:** Demonstrates cycle detection and avoidance

### Fourmiliere 3 - Optimal Path Selection
- **Ants:** 5
- **Strategy:** Choose shortest viable path
- **Optimal Path:** Sv → S1 → S4 → Sd (3 steps)
- **Alternative:** Sv → S1 → S2 → S3 (dead end)
- **Complexity:** O(n)
- **Notes:** Pathfinding with dead-end avoidance

### Fourmiliere 4 - Capacity-Constrained Routing
- **Ants:** 10
- **Strategy:** Multi-path routing with capacity management
- **Constraints:** S1 (capacity: 2), S4 (capacity: 2)
- **Paths:** Multiple routes through S5/S6 branches
- **Complexity:** O(n×t) where t is number of turns
- **Notes:** First implementation with capacity constraints

### Fourmiliere 5 - Complex Network Optimization
- **Ants:** 50
- **Strategy:** Multi-route load balancing
- **Network:** 14 stations with various capacities
- **Routes:** 6 different paths to distribute load
- **Complexity:** O(n×t×r) where r is number of routes
- **Features:**
  - Capacity management for all stations
  - Load balancing across multiple paths
  - Deadlock detection and prevention
  - Route assignment based on ant ID

## Pathfinding Strategies

1. **Direct Routing** (Fourmiliere 0): Simple parallel paths
2. **Sequential Processing** (Fourmiliere 1-3): Turn-based movement
3. **Capacity-Aware Routing** (Fourmiliere 4-5): Resource-constrained pathfinding
4. **Load Balancing** (Fourmiliere 5): Distribute ants across multiple routes

## Compilation and Execution

### Build All Algorithms
```bash
make all
```

### Run Individual Algorithm
```bash
make fourmiliere_0    # Compile specific algorithm
./fourmiliere_0       # Execute
```

### Run All Tests
```bash
make test             # Compile and run all algorithms
```

### Clean Build Files
```bash
make clean
```

## Algorithm Features

### Capacity Management
- Stations have maximum occupancy limits
- Ants blocked when capacity exceeded
- Dynamic occupancy tracking during movement

### Pathfinding
- Breadth-First Search (BFS) for shortest paths
- Cycle detection and avoidance
- Dead-end identification

### Load Balancing
- Multiple route assignment
- Ant distribution strategies
- Bottleneck identification and mitigation

### Deadlock Prevention
- Turn-based movement with blocking detection
- Alternative path exploration
- Maximum iteration limits

## Performance Characteristics

| Algorithm | Ants | Stations | Paths | Time Complexity | Space Complexity |
|-----------|------|----------|-------|----------------|------------------|
| 0         | 2    | 4        | 2     | O(1)           | O(1)             |
| 1         | 5    | 4        | 1     | O(n)           | O(n)             |
| 2         | 5    | 4        | 1     | O(n)           | O(n)             |
| 3         | 5    | 5        | 2     | O(n)           | O(n)             |
| 4         | 10   | 7        | 4     | O(n×t)         | O(n+v)           |
| 5         | 50   | 16       | 6     | O(n×t×r)       | O(n+v+e)         |

Where: n=ants, t=turns, r=routes, v=vertices, e=edges

## Extension Points

The modular design allows for easy extension:

1. **New Pathfinding Algorithms:** Implement different routing strategies
2. **Dynamic Capacity:** Add time-varying station capacities
3. **Priority Systems:** Implement ant priority levels
4. **Real-time Visualization:** Add graphical representation
5. **Performance Metrics:** Add detailed timing and efficiency measurements

## Usage Examples

```cpp
// Create and run a specific fourmiliere
Fourmiliere4 colony;
colony.move();                    // Execute movement algorithm
colony.print_results();           // Display results

// Access individual ant information
for (const auto& ant : colony.ants) {
    ant.print_path();            // Show ant's journey
}
```

This implementation provides a robust foundation for ant colony optimization problems and can be adapted for various graph traversal and resource allocation scenarios.