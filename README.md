A simple timing library based on: https://github.com/jfturcot/SimpleTimer

This library has a few minor improvements and provides some working examples in ./Examples/blinky_nrf52840

One important improvement is making sure that when a timer event occurs that the next event is set to occur after the proper interval from *now* vs the time that the event should have occurred at. This prevents a small cornercase issue where you have work being done that takes longer than your specified interval creating a bad scenario where your code can never catch up. This choice of starting from *now*, is a compromise from an exact interval timing perspective, but overall probably produces a more expected behavior.

The goal here is to provide timing functions that behave like Javascript's setInterval and setTimeout