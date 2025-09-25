**The goal of this is to make a box that you can put something in and make that thing experience a magnetic field.**

**The Arduino board is there to drive a signal of your choosing. In this example it's just making a sinusoid.**

1. rp2040 propmaker from adafruit goes in the bottom
2. 24 AWG magnet wire is wrapped around the top pocket
3. put the device under test in the box
4. blue light goes on when coil is on

Other pro tips
1. The spindle is there so you can wrap your magnet wire aroudn that spindle, and then thread through the box.  Probably the spindle the magnet wire came on is too small.  Or, in "params" in the CAD program you can just change "flange top height" and "flange bottom height" to be larger and print it larger so that your magnet wire spindle can fit.
2. jig2 is the name of the FreeCAD file that has the coil box 
3. I did probably 100 wraps of 24 AWG and got about 5 ohms, and easily got over +/-400 uT of field in the box.  This was most of the 4 oz roll of 24 AWG magnet wire. 
4. I ended up drilling and tapping M2.5 threads into the holes in the back.  I recommend getting a kit of this stuff.  In the end I used 4x M2.5 * 12mm screws, M2.5 * 10mm female-female spacers, and M2.5 * 6mm screws to attach the propmaker.  And... the two holes near the terminal of the propmaker is too narrow to get the screws in. oops.
5. IDE setup -- follow the [adafruit instructions](https://learn.adafruit.com/adafruit-rp2040-prop-maker-feather/arduino-ide-setup) for the rp2040 prop maker.

![looking into the box](PXL_20240624_233743795.jpg?raw=true "Looking into the box")
![side view](PXL_20240624_233732530.jpg?raw=true "Side View")
![rear view](PXL_20240624_233807952.jpg?raw=true "Rear View")


