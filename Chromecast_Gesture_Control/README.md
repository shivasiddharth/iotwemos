## Introduction     

![github-small](https://content.instructables.com/ORIG/FKE/BFJ3/KZ6ZPQTP/FKEBFJ3KZ6ZPQTP.jpg?auto=webp&width=1600&height=900&fit=bounds&md=88b1e10ed9e10ee04de462521dc22d67) 

<p>Ages back, when Google's Chromecast was without the Android TV, I came up an <a href="https://www.hackster.io/shiva-siddharth/make-your-own-remote-control-for-google-home-and-chromecasts-3206be" rel="nofollow">idea</a> to control the Chromecast with a Raspberry Pi. This was for those who wanted a tactile experience and who did not mind tossing their device to their children. But there was an issue with that. Raspberry Pi had an OS running and had to be booted which naturally took time and can't be shutdown abruptly which would corrupt the OS installation.</p><p>So here is Version 2 of the project and its a Covid-19 special. Non-contact based remote control for your Chromecast. That is, you can control your Chromecast with hand gestures. No more shouting &quot;Hey, Goooogle&quot; or getting distracted with your phone forgetting to pause your Chromecast. This overcomes the disadvantages of the Pi based remote control that I just mentioned above. This will serve as a good activity time project for the tiny tots in your home and they will surely have fun interacting with the device.</p>     


## Supplies    

<p>Hardware:</p><ol><li>Wemos D1 Mini (any other NodeMCU will do as well).</li><li>APDS9960 Sensor.</li><li>Jumper wires.</li><li>3mm LED (any color).</li><li>220 Ohm 1/4 W resistor.</li></ol><p>Tools (if you are going to enclose the hardware in a case):</p><ol><li>Box cutter.</li><li>Electrical tape.</li><li>A plastic box.</li><li>Electric hand drill.</li><li>A piece of MDF/Wood.</li><li>General purpose PCB (4cm x 2.5cm).</li><li>M2.5 screws.</li></ol>    


## Hurdle No1 - Wemos And APDS9960 Sensor Integration   

![github-small](https://content.instructables.com/ORIG/FZD/UTQA/KZ6ZPQU4/FZDUTQAKZ6ZPQU4.png?auto=webp&width=1600&height=900&fit=bounds&md=a9a496a0f29b5d8c934c33f5fce510b3)   
![github-small](https://content.instructables.com/ORIG/F50/Q7VJ/KZ6ZR6I7/F50Q7VJKZ6ZR6I7.jpg?auto=webp&width=1600&height=900&fit=bounds&md=f5ed2b0d5e31ba4a7102298f46e08312)   
![github-small](https://content.instructables.com/ORIG/F2P/LU9P/KZ6ZR6I6/F2PLU9PKZ6ZR6I6.jpg?auto=webp&width=1600&height=900&fit=bounds&md=b68dabd503932d30a21197eafb58b6ec)   
![github-small](https://content.instructables.com/ORIG/FB4/XSF6/KZ6ZRFUK/FB4XSF6KZ6ZRFUK.png?auto=webp&width=1600&height=900&fit=bounds&md=c6b7fb9e49d2da6a3cc0bab8444d2aad)  
![github-small](https://content.instructables.com/ORIG/FWS/A0BV/KZ6ZRGL3/FWSA0BVKZ6ZRGL3.png?auto=webp&width=1600&height=900&fit=bounds&md=3e279383f1a090b976d87e88d25cf241)    

<p>There were hardly any working references available for using Wemos D1 Mini/NodeMCU with ADPS9960 sensor in the internet. So I knew that I was venturing into the unknown territory. </p><ol><li>So to start with, I first connected the APDS9960 sensor to the Wemos as per the attached wiring diagram to check if the Wemos detected the sensor at all. I used the I2Cdetect library and check for the APDS9960 Sensor's address. I could see that the sensor was at 0x39 I2C address. That was a positive start.<li>Next step was to check the if the Wemos read the gestures. So I downloaded the Sparkfun's APDS9960 sensor library and use the built-in example. It was a bummer. The code would not even compile. Going through various forums, the issue was likely IRAM related. None of the suggested solutions worked. That was when I came across a fork of the Sparkfun's official library. That was tailored to work with Wemos and when I tested it out it did work, but had to do some minor changes. You can download the copy of the modified library from <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Chromecast_Gesture_Control/Modified%20Libraries/APDS-9960_Gesture_Sensor_esp8266_Library-master.zip" rel="nofollow">here</a>.<li>I gave the Wemos a test run with the modified library and it did work. I was able see the gestures getting detected in the serial monitor.</ol><p>That was one huge hurdle that was crossed.</p>    


## Preparing The Project Enclosure - The Cutting   

![github-small](https://content.instructables.com/ORIG/FC7/C8ER/KZ6ZPQTQ/FC7C8ERKZ6ZPQTQ.png?auto=webp&width=1600&height=900&fit=bounds&md=38227a2724a3051dcdbe9080f9fff5c8)   
![github-small](https://content.instructables.com/ORIG/FEK/VUE0/KZ6ZPQTR/FEKVUE0KZ6ZPQTR.png?auto=webp&width=1600&height=900&fit=bounds&md=30ac18dcb4985413187c67bdd1597a50)   
![github-small](https://content.instructables.com/ORIG/FK4/FN0N/KZ6ZPQTU/FK4FN0NKZ6ZPQTU.png?auto=webp&width=1600&height=900&fit=bounds&md=261d656ae20432fcf71e22b1abd69512)   
![github-small](https://content.instructables.com/ORIG/FR2/BI69/KZ6ZPQTX/FR2BI69KZ6ZPQTX.png?auto=webp&width=1600&height=900&fit=bounds&md=6d01e9ef6cd40dc3ace8d2bbbebd9c06)  
![github-small](https://content.instructables.com/ORIG/FZW/5M61/KZ6ZPQTY/FZW5M61KZ6ZPQTY.png?auto=webp&width=1600&height=900&fit=bounds&md=ffe221a73452d2a2abeb1cdc73aee440)  
![github-small](https://content.instructables.com/ORIG/F6H/4P6G/KZ6ZPQTZ/F6H4P6GKZ6ZPQTZ.png?auto=webp&width=1600&height=900&fit=bounds&md=c6d3f6ccd040dd4c0415051220f242dd)   
![github-small](https://content.instructables.com/ORIG/FRA/4DDJ/KZ6ZPQU3/FRA4DDJKZ6ZPQU3.png?auto=webp&width=1600&height=900&fit=bounds&md=4057c07c15899ad0592fc2be880f42bd)   
![github-small](https://content.instructables.com/ORIG/FU7/J4VR/KZ6ZPQU5/FU7J4VRKZ6ZPQU5.png?auto=webp&width=1600&height=900&fit=bounds&md=69cfebd856242e28b41f6addfe0af4a7)   
![github-small](https://content.instructables.com/ORIG/FYM/53AY/KZ6ZPQU6/FYM53AYKZ6ZPQU6.png?auto=webp&width=1600&height=900&fit=bounds&md=3bc0e956ca0307bec7e5c0b1c925504c)  
 
<p>I did not want to add new and more plastic waste in this world by 3D printing something. Instead I decided to recycle a sweatbox that I had in plenty with me. This was the same box that I used in my previous<a href="https://www.instructables.com/Live-Desktop-Crypto-Ticker/" rel="nofollow"> Crypto Ticker project</a>.</p><p>I decided to partially expose the Wemos's USB connector and RESET button outside the enclosure. This way, I need not take out the Wemos out of the enclosure for updating the code or re-purposing the setup for some other display based project. This will also allow me to RESET the Wemos when desired.</p><ol><li>First I inspected the plastic enclosure for any defects. While inspecting the enclosure, I saw that the plastic was partially translucent.<li>The partial translucency in fact helped my cause. I placed the Wemos inside in the desired position and I could see it's outline from outside.<li>With the Wemos's outline as reference, I used a piece of electrical tape to mark the dimensions of the cutout.<li>In the fourth image, you can actually see the tape's border matching the Wemos's height.<li>Using a box cutter, I cutout the plastic to make room for the Wemos.<li>Similarly, made a cutout on the lid for the gesture sensor.<li>I hot-glued the Wemos in its place and stuck some paper tape on the exposed Wemos to temporarily protect it from dust and other elements<li>On the back of the lid, I stuck a piece of small wood and held it in place with some electrical tape. On a hindsight, I could have used a duct tape here, my bad.</ol><p><br></p><p><br></p>     
     
      
## Preparing The Project Enclosure - The Drilling    

![github-small](https://content.instructables.com/ORIG/FGE/4O6J/KZ6ZPQUK/FGE4O6JKZ6ZPQUK.png?auto=webp&width=1600&height=900&fit=bounds&md=d3490bb845ebf056d71e72b14356ac10)   
![github-small](https://content.instructables.com/ORIG/F4M/WDJ9/KZ6ZPQUR/F4MWDJ9KZ6ZPQUR.png?auto=webp&width=1600&height=900&fit=bounds&md=ada2952f624da1f1c318627d48f5fd00)   
![github-small](https://content.instructables.com/ORIG/FXK/JSNH/KZ6ZPQUU/FXKJSNHKZ6ZPQUU.png?auto=webp&width=1600&height=900&fit=bounds&md=7dacdd3321ca0623c2579bb045085b23)   
![github-small](https://content.instructables.com/ORIG/F3D/46IV/KZ6ZPQUV/F3D46IVKZ6ZPQUV.png?auto=webp&width=1600&height=900&fit=bounds&md=b3bec6d1674972808fe7c37a00b5d046)  
![github-small](https://content.instructables.com/ORIG/FO6/4PNL/KZ6ZPQV2/FO64PNLKZ6ZPQV2.png?auto=webp&width=1600&height=900&fit=bounds&md=64a33e9b585300f64c62c4fabf56fc62)  
![github-small](https://content.instructables.com/ORIG/FIN/OD96/KZ6ZPQV4/FINOD96KZ6ZPQV4.png?auto=webp&width=1600&height=900&fit=bounds&md=21e311abeb75b1471ee3af7e71c6ac8e)   
![github-small](https://content.instructables.com/ORIG/FZR/ECNC/KZ6ZPQV9/FZRECNCKZ6ZPQV9.png?auto=webp&width=1600&height=900&fit=bounds&md=6ecdf4e45cfad635ef9109d21bfc0307)   
 
<blockquote><strong>This part involves the use of power tools. Always take the necessary precautions and wear the required safety gear while operating the electric power tools. Also, pay full attention and do not get distracted.</strong></blockquote><p>Drilled the following holes.</p><ol><li>2 holes on the lid for two M2.5 Screws to hold the backplate in place.<li>1 hole of approximately 5mm diameter for the sensor.<li>1 hole of approximately 3mm diameter for the 3mm indicator LED.</ol><p>After drilling the front two holes, secured the backplate with two M2.5 screws and then removed the temporary electrical tape that was holding it in place.</p>    


## Preparing The Project Enclosure - The Paint Job    

![github-small](https://content.instructables.com/ORIG/FMG/7TKF/KZ6ZPQU8/FMG7TKFKZ6ZPQU8.png?auto=webp&width=1600&height=900&fit=bounds&md=be1bc45be2122df923f2223bde4c4d73)   
![github-small](https://content.instructables.com/ORIG/F76/ZHIV/KZ6ZPQUG/F76ZHIVKZ6ZPQUG.png?auto=webp&width=1600&height=900&fit=bounds&md=60c7ff5b3e163876a98db646f566cd51)   
![github-small](https://content.instructables.com/ORIG/F76/ZHIV/KZ6ZPQUG/F76ZHIVKZ6ZPQUG.png?auto=webp&width=1600&height=900&fit=bounds&md=60c7ff5b3e163876a98db646f566cd51)   
![github-small](https://content.instructables.com/ORIG/FT4/S6Q2/KZ6ZPQUJ/FT4S6Q2KZ6ZPQUJ.png?auto=webp&width=1600&height=900&fit=bounds&md=b5da4519b7b8b97fd7f72b2127392bb0)  
![github-small](https://content.instructables.com/ORIG/F19/XINT/KZ6ZPQVA/F19XINTKZ6ZPQVA.png?auto=webp&width=1600&height=900&fit=bounds&md=c8a9e3602130d7843ac3aac949a8c047)  

<p>First, I buffed up the plastic surface with some sand paper to make the surface rough. This was to make sure that the enclosure would hold the paint well.</p><p>Then, I masked the parts of Wemos that was protruding with some paper tape.</p><p>After roughing up the enclosure surfaces, gave it a good dose of black spay paint and left it to dry for 48 hours. The paint could have dried earlier, but did not want to check just in case.</p><p><br></p>    


## Hurdle No 2 - My Mistake   

![github-small](https://content.instructables.com/ORIG/F5L/HPE0/KZ7C5546/F5LHPE0KZ7C5546.png?auto=webp&width=1600&height=900&fit=bounds&md=75c7d3f39048c532379740a286c2e9cf)   
![github-small](https://content.instructables.com/ORIG/FJ2/XK2M/KZ6ZPQVC/FJ2XK2MKZ6ZPQVC.png?auto=webp&width=1600&height=900&fit=bounds&md=506b4e0eb5ff6b6dbf72a9f8cf04df60)   
![github-small](https://content.instructables.com/ORIG/FF2/N9X0/KZ6ZPQVE/FF2N9X0KZ6ZPQVE.png?auto=webp&width=1600&height=900&fit=bounds&md=97d0664364c6eae44f5f43f5a460d01d)   
![github-small](https://content.instructables.com/ORIG/FUY/WFSE/KZ7C59RI/FUYWFSEKZ7C59RI.png?auto=webp&width=1600&height=900&fit=bounds&md=cc872073d4d6e4343084eedb5c57e833)  

<p>After putting altogether as per the attached schematic, tried to see if the device could pickup any gestures with sample code previously used. The sensor was working, as you could clearly see the infrared light from the sensor. But there was nothing on the Serial Monitor. </p><p>Tried to see if I could figure out anything from the <a href="https://docs.broadcom.com/doc/AV02-4191EN" rel="nofollow">datasheet</a> and it was a dead end. At this point, I had two probable causes:</p><ol><li>The indicator light was interfering with the detector, or<li>The hole was not large enough for the detection cone of the sensor</ol><p>Just to check on both, took out the LED and the sensor out of the enclosure and while holding the LED just above the sensor, tried some gestures and it was working. So the culprit was the hole. </p><p>So i decided to fully expose the sensor just to not run into similar issues again.</p>   


## Putting It Together The Second Time And Properly   

![github-small](https://content.instructables.com/ORIG/FDC/Y360/KZ6ZPQVF/FDCY360KZ6ZPQVF.png?auto=webp&width=1600&height=900&fit=bounds&md=df0fff8d4f157813c1bc22c9768dc5ec)   
![github-small](https://content.instructables.com/ORIG/F7N/UH3J/KZ7C5F8G/F7NUH3JKZ7C5F8G.jpg?auto=webp&width=1600&height=900&fit=bounds&md=e6e7e14c9885f203c10da38dc5c40136)   
![github-small](https://content.instructables.com/ORIG/FJW/7YDE/KZ7C5FDB/FJW7YDEKZ7C5FDB.png?auto=webp&width=1600&height=900&fit=bounds&md=b0eb7093c12292f7ab2ecc45d78c5ad1)   
![github-small](https://content.instructables.com/ORIG/FKJ/L4W1/KZ7C5FDF/FKJL4W1KZ7C5FDF.png?auto=webp&width=1600&height=900&fit=bounds&md=d6dd0fd8d7e4a2ee68c7ab2340bde546)  
![github-small](https://content.instructables.com/ORIG/FLJ/TYGL/KZ7C5FDG/FLJTYGLKZ7C5FDG.png?auto=webp&width=1600&height=900&fit=bounds&md=1996a906da932b97fc5343b614fac0ec)    

<p>I measured the seize of the wooden backplate that was previously used and replaced it with a double sided PCB. Drilled the matching holes on the PCB and held them in place securely using two M2.5 screws. The LED and the connections to the sensor were bonded to the backplate with some hot glue.</p><p>The connections were made using just the jumper wires. Not clean, but I did not mind as they going to be unseen inside the enclosure. Instead if you want something neat, I have prepared a gesture sensor shield for the Wemos. You can find the Gerber files <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Chromecast_Gesture_Control/Schematic/ADPS9960-Wemos-Breakout.rar" rel="nofollow">here</a>. For PCB fabrication, you can use JLCPCB's service. With their online Gerber viewer, you can verify the PCB design before ordering and they have different PCB colors to choose from. Use this link <a href="https://jlcpcb.com/IAT" rel="nofollow">https://jlcpcb.com/IAT</a> for great discounts and minimal PCB fabrication costs. If you want to create your own design, you can modify the board design with the Fritzing file I have provided <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Chromecast_Gesture_Control/Schematic/Wemos-ADPS9960-Breakout.fzz" rel="nofollow">here</a>.</p><p>I modified the sample code from the <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Chromecast_Gesture_Control/Modified%20Libraries/ArduCastControl-main.zip" rel="nofollow">ArduCastControl</a> library and combined it with the modified gesture sensor code. You can find the <a href="https://github.com/shivasiddharth/iotwemos/tree/master/Chromecast_Gesture_Control/Modified%20Libraries" rel="nofollow">modified libraries here</a> and the <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Chromecast_Gesture_Control/Arduino_IDE_Code/ESP8266_Chromecast_Control/ESP8266_Chromecast_Control.ino" rel="nofollow">sample code here</a>.</p><p>There something else you need to mind. The code is dependent on other libraries as well. </p><ul><li>ArduinoJson version=6.18.5<li>Arduino_JSON version=0.1.0<li>SnappyProto version=0.1.2</ul><p>For your own use, make sure to declare the IP address of your Chromecast and also your WiFi SSID and WiFi password in the code/script. The locations for these declarations have marked clearly.</p><p>After compiling and verification, I decided to power the setup with a power bank. I could place this easily on the sofa armrest and control the Chromecast.</p>    


## Purpose Of The Indicator LED    

![image alt text]([img]https://i.imgur.com/t0xGlhg.jpg[/img])](https://www.youtube.com/watch?v=996fY4w48jY "Remote Control Chromecast with Gestures Using ESP8266 NodeMCU LED Status Indication")      

<p>I have assigned specific behavioral patterns to the indicator LED.</p><ul><li>If the LED blinks every 1 second, it means that the WiFi connection has got disconnected.<li>If the LED blinks in long intervals, it means that it is unable to shake hands with the Chromecast.<li>If the LED pulses constantly, it means that its constantly communicating with the Chromecast.<li>If the LED momentarily blinks while pulsing, it means that it has picked up a gesture.</ul>    


## Demo: And The Controls    

![image alt text]([img]https://i.imgur.com/bBZJQ8A.jpg[/img])](https://www.youtube.com/watch?v=0buSCjYbQNg "Remote Control Chromecast with Gestures Using ESP8266 NodeMCU  Gestures Working Demo")    

<p>The gesture sensor can inherently detect 4 gestures:</p><ul><li>Right swipe.<li>Left swipe.<li>Top swipe and<li>Bottom swipe.</ul><p>Thanks to Sparkfun, we have two additional gestures:</p><ul><li>Far swipe and<li>Near swipe.</ul><p>For Far swipe, you need to start close to the sensor and take your hand away and for Near swipe, its the opposite, you need to start Far away and bring your hand close to the sensor.</p><p>I have integrated these 6 gestures with 6 different Chromecast controls.</p><ol><li>Right swipe will Seek or move the video forward by 10 seconds.<li>Left swipe will Seek or move the video backward by 10 seconds.<li>Top swipe will increase the volume by 1 unit.<li>Bottom swipe will reduce the volume by 1 unit<li>Far swipe will Pause/Unpause the video.<li>Near swipe will Mute/Unmute the video.</ol><p>I have shown the working of the gadget in the attached video. Hope you do create your own device and have fun.</p>    



