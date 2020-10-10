# Logic simulator
I thought i could do something great of it but i realized that 2d is too bad and 3d is better, so i'm trying to make something with 3d right now. This project is abandoned.
## Bugs
* When you try to place many components with shift and go negative coordinates, it will crash (it uses unsigned coordinates for simpler math).
* You can start wire dragging and then remove this component. If you try to connect this dangling wire it will crash.

## Controls
* Movement - Right mouse button
* Place a component - Left mouse button
* Place multiple components - Shift + Left mouse button (drag)
* Make a wire - Left mouse button
* Remove a wire - Repeat "make a wire"
* Flip a switch - press it without active component
* Select a component - 1-5
* Leave the game - Esc

## Components
1. Nothing
2. Peg
3. Inverter
4. Blotter
5. Switch
