# Sonic 2
This is a recreation of sonic the hedgehog 2 using C++ and SDL. Made completely from scratch and including a level editor.

# Level Editor
The level editor can be used to create & edit custom levels for the game. The levels are saved in a `.zone` format.

Clicking the `Save` Button will save the zone under 

> /Zones/XXN.zone

Where `X` is the first letter of each word of the zone and `N` is the act number.

## Controls
### Editor Window
- Left Click: Place a tile, hold LShift to flip a tile horizontally, and LCtrl to flip vertically.
- Right Click: Remove a tile.
- Middle Click: Hold to pan the screen when dragging the mouse.
- Scroll Wheel: Zoom In/Out.
- WASD/Arrow Keys: Pan the screen.
- +/-: Zoom In/Out.

### Options Window
- Left click on a tile in the menu to select it to be placed.
- Click on a text box to edit it.
- Press Enter or click out of a text box to confirm changes.
- Press Escape when a text box is selected to discard changes.