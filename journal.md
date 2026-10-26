# Desk Buddy — Journal Export

- Exported at: 2026-10-26T16:03:59Z
- Project ID: 4761
- Entries: 6

## Entry 1
- ID: 16270
- Author: Aryan Rao
- Created At: 2026-06-26T18:36:12Z

### Content

I started my project researching & penning down my ideas and what really i could build, with the base being a tamagotchi as the inspo. i feel the tamagotchi in it's self is very interesting, but i wanted to add a real use case to it. 

i first thought of making it a AI agent using a mic & poke.com webhook, which made me realise that is not really the best idea cus i could do that on a phone & it would be bettter off. I also researched about the esp32 c3, turns out the xiao one is very vfm & feature packed. 

I also started wiring this up, looking at the fallout guide & making sure i'm doing it right. i also did not find a footprint for the mic so i ended up making a footprint using a 01x07
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mzk5NTIsInB1ciI6ImJsb2JfaWQifX0=--63c1e7c22e4a818efc979b19799fac1697535dc8/image.png)


### Recording Links

- https://lookout.hackclub.com/api/media/d7e79544-4398-4ece-a314-87128b447bc1/video.mp4
- https://lookout.hackclub.com/api/media/53f6123b-16f5-4612-8b4b-510824af4be5/video.mp4

## Entry 2
- ID: 16273
- Author: Aryan Rao
- Created At: 2026-06-26T18:51:12Z

### Content

I then found a very intresting sensor & i got flashed an idea on what to do. I found a temperature from bosch that is p accurate in it's readings & can be used for really nice automations like if my room too hot switch on fan, tooo too too hot switch on ac, use it to turn of my lights. if too distracted by tv turn of tv etc..

could be a tamagotchi aswell hmm.. really intresting.. 
I also decided to do some reasearch on IR blasters & app they have certain waves they match up to and use the frequency to power it down. 

I looked & reffered to the datasheet to map the schematic out to the smallest details since there were little to no projects that used this PCB / module as much. 

i furthur learnt more on what i can do / what i need & how the IR diodes should be wired up. i also found out the xiao esp32 c3 has inbuilt charging and can charge a battery w/o a tp4056 yay. I also followed the easyeda2kicad python script to acquire the OLED footprint. 

I then was trying to find similar projects to mine that i can use some inspo of which i really could not find any that used this combo of parts lmao. 

I also started designing how the case / layout should look. I then started to make my schematic better i also looked into neo pixels & decided to include them in this project. Tried diff layouts and finally settled on one of em, i put the screw holes in the starting so that it wil not be a issue to worry about later & i would have the exact dimensions i needed. then i started the boom boom wiring yeet
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mzk5NjEsInB1ciI6ImJsb2JfaWQifX0=--85258bd67a3d741db9f0ea149913fc694ec49ea5/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/qncK0rti_osP/timelapse-qncK0rti_osP.mp4
- https://public.lapse-hackclub.link/timelapses/JMe2G-XaFAze/timelapse-JMe2G-XaFAze.mp4

## Entry 3
- ID: 16277
- Author: Aryan Rao
- Created At: 2026-06-26T19:24:50Z

### Content

continuned on doing PCB work & really struggling lmaoo to make proper edges for the PCB cus i reallyyy wanted my PCB to be round & not be squared even if is boxy tbbhh. 

i then continnued wirinng pcb and did a lot of more wirinng. I made sure it was clean routing. I also imported the 3D model into KiCAD & it did not render it / set position properly. 

I then started grounding the PCB to make sure it was grounded properly. I then realised that i overestimated the size of the temprature sensor. I then made the edges of the PCB smaller & tried to leave some space while still trynna make it compact (i could not make it compact yes. i struggled w making the edges round lmaoo
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mzk5NzUsInB1ciI6ImJsb2JfaWQifX0=--4f1862590748b827b7b99db8e518494adaa1502f/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/NgE7DbrH43fw/timelapse-NgE7DbrH43fw.mp4
- https://public.lapse-hackclub.link/timelapses/ieIhqddySaaO/timelapse-ieIhqddySaaO.mp4

## Entry 4
- ID: 16279
- Author: Aryan Rao
- Created At: 2026-06-26T20:01:10Z

### Content

I started work on my PCB & cleaned up my routing cus i moved components up & made sure all the wires were going to the right switch. It was really a mess after i adjusted all the components to go up, the wires went all hay wire & decided to create 67 wiring errors. 

i then started working on my case for this project, laying out the PCB & the components out in fusion placing them to make sure it does not float in the air like a bird. I then rewired the IR diode cus idk what i did there before, but one was to gnd other was to a resistor, which did not send nun signals to esp32 lmaoo.. I then got a model of esp32 c3 which was amazing to see. imported a battery connector (JST) since i plan on using a 500 mAh battery w/ this project. I then started making the PCB even smaller since i realised i can, it'll imporve holdability a bit & some ascethics, maybe! 

i was trynna fillet my case to match my pcb, I WAS USING THE WRONG FILLET, i had to use the sketch fillet & i was using the build fillet! lmao,. 

Then made case more round, nice looking. Took some inspo from my other case how it really was, i extruded it into 2 diff parts so i could really tell which side is which and is js easier to print in general. I then sketched out vents & left holes for the temp sensor to pick up tempratures & also sketched out the switches so they could be cut in the 3D printed case. 

Then, made a small rounded square for my screen to fit in & look good! I really struggled getting the holes cut out when extruding using the sketch, this was def a diffcult task to do. I then cut out a hole for the USB-C from the esp32-c3. after doing & trying so much i finally did it yay!
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mzk5ODEsInB1ciI6ImJsb2JfaWQifX0=--4a1861f472f23b652670e6e63b27ff127fd4902a/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/pboANT2GfgbY/timelapse-pboANT2GfgbY.mp4

## Entry 5
- ID: 16302
- Author: Aryan Rao
- Created At: 2026-06-27T09:19:37Z

### Content

I learnt better on how to do renders & more! I spent time getting the perfect renders & also trying to perfect the color i really want for the buttons

I also was trynna figure out how do make a firmware for ts device, since that was gna be a huge issue. 

I also made my zine & i think it was decent! 
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDAxNzEsInB1ciI6ImJsb2JfaWQifX0=--a7179f5ff8758705c47dc93aedc84ec3558d2e8d/image.png)


### Recording Links

- https://www.youtube.com/watch?v=Guu1wu9cZ4Q
- https://www.youtube.com/watch?v=ngU1OIbDdik
- https://lookout.hackclub.com/api/media/6b6a0e21-c95d-41c3-a45d-1a6b0cb3addc/video.mp4
- https://lookout.hackclub.com/api/media/6912120b-9265-439f-b38d-1e731b7d83c2/video.mp4

## Entry 6
- ID: 16305
- Author: Aryan Rao
- Created At: 2026-06-27T09:24:18Z

### Content

Oops! i forgot to log this one! This was a timelapse of me wiring my microphone on my old idea, that did not age well! 

I had to make my own footprint for it as no one really had made it in the community! 
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDAxNzQsInB1ciI6ImJsb2JfaWQifX0=--56ec4b4d64fd83c6fa8d9308fe4e56a55eee7e13/image.png)


### Recording Links

- https://lookout.hackclub.com/api/media/78d56a34-3bea-4d9a-a119-6804dde8467a/video.mp4
