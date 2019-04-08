## How To Run
```bash
mkdir output
cd output
cmake ..
make
./graphics_asgn1
```

## Controls
- `Left` and `Right` Arrow Keys to move horizontally
- `Space` to propel upwards, `Down` to propel downwards
- `Left Click` to throw a water balloon in the direction of cursor
- `Scroll` to zoom in and out

## Obstacles
- **Fire Lines**: Can be cleared with water balloons or a sword powerup
- **Fire Beams**: Randomly spawn from the bottom or the top, cleared by a sword
- **Boomerangs**: Follow a parabolic path, cleared by a sword
- **Dragon**: Spits balls of fire at random intervals, and follows the player's height, damaged by a sword
- **Magnets**: Pulls the player towards it, rotate towards the player, cleared by a sword

## Shelter and Powerups and Coins
- **Semi-Circular Ring Shelter**: Immune while inside, but must follow its path and exit on the other side
- **Shield**: Temporarily protects from all damage, spawns as a projectile
- **Sword**: Temporarily protects from all damage and clears obstacles, damages dragons
- **Hourglass**: Slows down time to make dodging obstacles easier, spawns as a projectile
- **Coins**: 3 different types each with different value and colour

## Features
- **Score and Lives**: Displayed on the screen as well as on the window
- **Status**: Window displays the current status of the player, for example "Shielded"
- **Balloon Direction**: Balloon is fired in the direction of mouse click
- **Models**: The player,the dragon and the powerups are modelled decently using primitives
- **Propulsion effect**: The jetpack displays a propulsion effect when it propels upwards
