# CharlonPractice

This is an excercise for students of the 1st year of GD of DAE. This excercise focuses on:
- `new` & `delete` / memory management
- Inheritance and polymorphism
- Templates

## ProjectileManager

You may assume that if you receive a projectile pointer that you become owner of said memory.
Add functionality:
- Making projectiles (push back methods)
- Deleting projectiles (when projectilemanager is destroyed)
- Drawing projectiles
- Updating projectiles (and deleting them when the 'HasHit' function returns true)

## Projectiles

We have `LockOnProjectile` and `SkillshotProjectile`. Rework the project so that both have a common **baseclass** making so that the projectile manager is simplified.
Hopefully, you will only need one container holding all projectiles in the game.

## AutoAttack

Make it inherit from an interface class (no data only pure virtual functions) called `IClone`.
This interace must be [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) (Curiously Repeating Template Pattern, google for more info).

## Ability

Implement Ashe's W from league of legends for the Hoover Champion. Your new ability is not designed to be inherited.
You should inherit from `Ability`.

### EXTRA
## Custom Container

Make a templated container similar to `std::vector` that remembers how long an element is in the container.
When the container is full, instead of expanding it **overwrites** the oldest element and gives that oldest element back to the user that called a function to add an element. 
When overriding `operator[]` it will not return the oldest element but will delete it if it is a pointer *AND* if a boolean in the container is set (this can be set by the user). Otherwise it will discard it.
Demonstrate that this container works.
**TIP**: Make this container without templates first and add the template component as last. Feel free to use a seperate project (console application for example) for this if you prefer so.
