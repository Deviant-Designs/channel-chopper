# Channel-Chopper
A Fire button for any estim device. Perfect for BDSM play 

## Quick Disclaimer
I am neither an electrical engineer or a software developer. I made this for fun. There are probably many many flaws in this. But that being said, it works and works well for what I want. I don't mind constructive critiscm at all (actually I'll be greatful for it) but please be nice with it. It sucks when you put lots of effort into something and people just hammer it for its flaws :)

## What is it
this is a inline controller to turn on and off estim signals. You attach it between the estim unit and the bipolar electrode. it has 4 buttons on it which when depressed allow the estim signals to passthrough to the electrodes. It also works via serial comunication so you can link it up to other equipment if you wish. 

## You said 4 Channels, Why 5 inputs/Outputs?
channel 5 in the channel chopper is actually controlled by channel 4. the idea behind this is if you have 2 bipolar nipple clamps. One on each nipple. If you press the channel 4 button they will both fire at the same time

## BOM
11 - 3.5mm Panel Mount Stereo Jacks
10 - MOC 3023
1 - pro Micro
14 - 220Ω Resistors
4 - 5mm LEDS
4 - Buttons/swtiches

## Serial Format
This is done through the USB cable. Basic serial comunication at 9600. The format is as follows

`shock¬"channel"¬"state"`

There are 4 channels and the states are either `1` for on or `0` for off. So if we wanted to turn channel 2 on we would send

`shock¬2¬1`

and if we wanted to turn channel 2 off it would be 

`shock¬2¬0`

## why is there another serial connection linked to a 3.5mm jack
this hasn't been implemented in software yet, but I put this there in case I wanted to setup software serial to control the box from another arduino. or maybe use this box to trigger other devices. The tip is connected to pin A1 and the ring to A0

### If you like what we do and want to support us then please consider the following options
[Patreon](https://www.patreon.com/deviantdesigns)

[Ko-Fi - if you'd rather a one off donation](https://www.Ko-fi.com/deviantdesigns)

[Twitter - sharing our work helps lots too if you can't afford to support financially](https://twitter.com/_DeviantDesigns)
