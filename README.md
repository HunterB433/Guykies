# Guykies
Like Cookie Clicker, but worse!

### How does it work?
There isn't too much game right now. There is a button you can click to cause Guys (The Kitty) to appear and have your score go up. They also spawn naturally.
There is also a Slideshow of the Guy for you to peruse at your leisure.

### How does it satisfy requirements?

At least two new features that are developed by extending Sprite2D into a new Node (4 points)
- I extend Sprite2D into the nodes Slideshow and EmitSprite
- The former cycles through 4 different photos; the latter can emit copies of itself in varying ways
Each of these features should have at least 1 parameter that can be manipulated via the editor (2 points)
- Slideshow has 4 photos and a transition time for parameters
- EmitSprite has EmitSpeed, Scale, and Direction (Though it's random rn, I figure I can override it in the future with some changed code)
- Also has Velocity(controlls the speed of spawned code, currently calculated bu EmitSpeed, But I can use this in the future as well)
- Also has 2 bools which decide if it stays stationary / can emit (and also not die)
One signal that is emitted by this node that triggers a method in one of the existing nodes in your Scene (2 points)
- There is a signal in EmitSprite, "scored()", which increases the scoreboard label node with "increase_score()"
One method in this node that is triggered by emitting a signal in one of the existing nodes in your Scene (2 points)
- The button node has a signal, "spawnGuy()", which spawns a guy with the method "emit_copy()" from EmitSprite

For the animation, you see it in a few places
- In the background, which moves around
- In the mini Guys, as they spawn and move across the screen
- And in the SlideShow
