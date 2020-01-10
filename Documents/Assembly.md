# Hardware Assembly
This is what the fully assembled kit will look like when we are finished

![Final Assembly](./images/AssemblyV3/IMG_2986.jpg)

## Unpack your kit
Layout the contents on a table, putting like things together

![Knolled parts](./images/AssemblyV3/IMG_2961.jpg)

## Solenoid and pump preparation. Preparation

First perpare your gas solenoid (electronically controlled air release valve).
Take off the blue caps from the inputs/outputs of the valve
![Caps Off](./images/AssemblyV2/IMG_1573.jpg)

Attach the leads to the contact tabs on the back of the valve. They are tight so some force is required, but be careful not o bend or break the connectors.
![leads on](./images/AssemblyV2/IMG_1575.jpg)

Feed the Zip ties through the channels in the bottom of one of the 3D printed holders. Note the orientation of the zip tie. Do this for both channels (x2)
![zipit](./images/AssemblyV2/IMG_1578.jpg)

Place the Solenoid valve in the cradle, and fasten the zip ties around it, tighten and clip off the excess.
![zipit good](./images/AssemblyV2/IMG_1579.jpg)
![zipit good](./images/AssemblyV2/IMG_1580.jpg)

Prepare the other cradle the same way and fasten the pump to it.
![zip pump](./images/AssemblyV2/IMG_1581.jpg)

## Barrel assembly
Remove the plunger from the 5ml Syringe. Discard (unless you can think of a cool use...)
![plunger removal](./images/AssemblyV2/IMG_1584.jpg)

Slip the syringe into the barrel holder 3D printed part and snap into the Pan-tilt mechanism. Note that the "handle end" of the syringe (front of the barrel) points away from where the leads come out of the pan-tilt.
![Barrel assembly](./images/AssemblyV2/IMG_1585.jpg)

If you have a Luer style syringe, install the Luer to hose barb adapter. It screws in
![luer](./images/AssemblyV2/IMG_1586.jpg)

Cut approximately 5-6" of tubing and connect between the barb on the syringe and the front (axial) valve of the solenoid valve. If you dont have the Luer-barb, or have a syringe with a slip on style end, just slide the tubing over that.
![first tubing](./images/AssemblyV2/IMG_1587.jpg)

## Pressure Vessel
Unscrew the two caps from the "two barb" bottle cap. These slip over the tubing, the tubing over the barb and then screw the caps down over the tubing.
![cap prep](./images/AssemblyV2/IMG_1588.jpg)
Attach approximately 8" of tubing to the other barb of the solenoid valve, slide the retaining cap over the other end, and fasten to the bottle cap barb.
![tubing attach](./images/AssemblyV2/IMG_1589.jpg)
![solenoid attach](./images/AssemblyV2/IMG_1590.jpg)

Take another 8" piece and cut it in two pieces (one can be shorter, it doesn't matter) we'll be putting a 1-way valve inline here and connecting the pump to the pressure vessel
![tubing cut](./images/AssemblyV2/IMG_1591.jpg)

Slide the tubing over the ends of the oneway valve. The disk part (shown here with a short tube attached) goes toward the pump.
![valve attach](./images/AssemblyV2/IMG_1592.jpg)

Attach the other end (away from the disk) to the pressure cap
![tubing attach](./images/AssemblyV2/IMG_1593.jpg)

Finally Attach the remaining end to the pump output. If your pump has two barbs it's the one on the end (not the side) axially aligned with the length of the pump.
![pump attach](./images/AssemblyV2/IMG_1594.jpg)

Next screw on your pressure vessel (soda bottle) this completes the Pneumatic assembly. This picture also gives you a good view of all the connections. make sure yours looks like this.
![bottle](./images/AssemblyV2/IMG_1595.jpg)

## Electronics assembly
Take the RAF shield from the antistatic bag (it's the board with a joystick). Also remove the Arduino from it's packaging, and line up the pins from shield to the Arduino. Note that there are more pins on one side than the other, make sure you have the right headers on both sides. Carefully press them together straight down.
![Shield alignment](./images/AssemblyV2/IMG_1596.jpg)
![Shield alignment](./images/AssemblyV2/IMG_1597.jpg)

Attach the leads from the pump to the screw terminals (inside set, near the middle of the end of the shield) labeled PUMP. Make sure the screws are screwed out first to reveal a little hole to stick the wires in. Stick a wire in and tighten by screwing clockwise. Note that polarity doesn't matter.
![pump attach](./images/AssemblyV2/IMG_1598.jpg)
Repeat for the solenoid.
![sol attach](./images/AssemblyV2/IMG_1599.jpg)

Attach the Servo extension cables to the servo leads from the pan tilt mechanism. These are supplied to give you more flexibility in laying out your whole machine.
Line up the wires so they are similarly colored. In the example here, orange goes to white, red to red and brown to black.
(white is signal, Red is servo positive voltage, Black is Ground.) The middle one is alway voltage, and usually the darkest one is ground.
![Servo Extensions](./images/AssemblyV2/IMG_1600.jpg)
Attach the extension leads to the shield. Attach the bottom servo (azimuth) to the header labeled 3 (closest to the edge of the board) and the upper (elevation) servo to the header marked 5. Each header is also labeled on the side, W R B. Line these up to the Signal (W) Voltage (R) and GND (B). Note the female headers on the leads are oriented perpendicular to the long edge of the board.
![Servo Connections](./images/AssemblyV2/IMG_1603.jpg)

## Make it easier to move around and keep together.
Now we'll fasten everything to the foam core. Lay out your components in a way you feel convenient. You don't have to match this picture. Later if you want to tidy even more you can adjust the lengths of the leads and tubing.
![Final Assembly](./images/AssemblyV2/IMG_1605.jpg)

You can use the brass paper fasteners to attach the 3D printed parts, and the two sided foam tape to attach the pan-tilt and the arduino.
The brass fasteners can be pushed through the holes and through the foam core. If you have trouble, you can pre-punch holes with an x-acto knife in the foam core.
![fasteners](./images/AssemblyV2/IMG_1604.jpg)

And here's a closeup (the bottle is out of the pic) of the final assembly:
![final-final](./images/AssemblyV2/IMG_1606.jpg)







