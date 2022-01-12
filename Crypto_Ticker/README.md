## Introduction    

![github-small](https://content.instructables.com/ORIG/FR7/OVXJ/KY9E5966/FR7OVXJKY9E5966.png?auto=webp&width=1600&height=900&fit=bounds&md=193a71943e042312d45a5e0692ee3034)    

<p>When you are trading Cryptos it is always itching to constantly look at the prevailing rate. I wanted a gadget that could display the live Crypto rate without constantly refreshing the browser.</p><p>I have incorporated a slideshow effect for better appeal. The first slide will be an image of the Crypto logo, the second slide will be the live Crypto trading rate and the last slide will be the rate of change, that is it shows whether the price of Crypto has decreased or increased and by how much.</p><p>My first thought was to 3D print a case for this project and then when I saw a plastic box on my table, decided to recycle the old plastic instead of adding to the global plastic woes by 3D printing a new one.</p><p>I have got all the files in the git project page. You can get access to all the related files by clicking <a href="https://github.com/shivasiddharth/iotwemos/tree/master/Crypto_Ticker" rel="nofollow">here</a>.</p>    


## Supplies     

<p>Hardware:</p><ol><li>Wemos D1 Mini (any other NodeMCU will do as well).</li><li>SSD1306 Monochrome OLED display.</li></ol><p>Tools:</p><ol><li>Box cutter.</li><li>Electrical tape.</li><li>A plastic box (optional)</li></ol>     


## Getting The Enclosure Ready     

![github-small](https://content.instructables.com/ORIG/FW2/10RY/KY9E595K/FW210RYKY9E595K.png?auto=webp&width=1600&height=900&fit=bounds&md=954d0c953259a519a7d804d4787b6629)   
![github-small](https://content.instructables.com/ORIG/F7X/UC8S/KY9E595S/F7XUC8SKY9E595S.png?auto=webp&width=1600&height=900&fit=bounds&md=a6e99f3b8485c87252205aa839139cdf)   
![github-small](https://content.instructables.com/ORIG/FS8/VQ9C/KY9E595T/FS8VQ9CKY9E595T.png?auto=webp&width=1600&height=900&fit=bounds&md=c18c5871853fcf6c8c5200ef30f240b9)   
![github-small](https://content.instructables.com/ORIG/FOX/KQF5/KY9E595V/FOXKQF5KY9E595V.png?auto=webp&width=1600&height=900&fit=bounds&md=089d788bd3f7f8a1233aca26bc1118e6)     

<p>My first idea was to add a Micro USB female connector to the enclosure and then connect the Wemos to it. But on second thought, decided to partially expose the Wemos's USB connector and RESET button outside the enclosure. This way, I need not take out the Wemos out of the enclosure for updating the code or re-purposing the setup for some other display based project. This will also allow me to RESET the Wemos when desired.</p><ol><li>First I inspected the plastic enclosure for any defects. While inspecting the enclosure, I saw that the plastic was partially translucent.<li>The partial translucency in fact helped my cause. I placed the Wemos inside in the desired position and I could see it's outline from outside.<li>With the Wemos's outline as reference, I used a piece of electrical tape to mark the dimensions of the cutout.<li>In the last image, you can actually see the tape's border matching the Wemos's height.</ol>


## Cutting Through       

![github-small](https://content.instructables.com/ORIG/FM9/ZPZB/KY9E595W/FM9ZPZBKY9E595W.png?auto=webp&width=1600&height=900&fit=bounds&md=933b29a95cdb575978960530253b9ae9)   
![github-small](https://content.instructables.com/ORIG/FO3/JF1Z/KY9E595Z/FO3JF1ZKY9E595Z.png?auto=webp&width=1600&height=900&fit=bounds&md=dc535488637ba38ee1e0fcbec2ffc0d4)     

<ol><li>Using a box cutter, I cutout the plastic to make room for the Wemos.<li>Similarly, made a cutout for the OLED display on the plastic enclosure's cover.</ol>


## Fixing The Wemos Tight    

![github-small](https://content.instructables.com/ORIG/FTZ/0JAN/KY9E595Y/FTZ0JANKY9E595Y.png?auto=webp&width=1600&height=900&fit=bounds&md=0965fbcf8202b8aa7e14eb97df3752d3)     

<p>I slid the Wemos through the cutout on the side just enough to partially expose the USB connector and the RESET button of the Wemos.</p><p>To hold the Wemos tight in its place, used a fair bit of hot glue to affix the Wemos to its plastic enclosure.</p><p>Now it is ready to be tossed around.</p>


## Putting It All Together    

![github-small](https://content.instructables.com/ORIG/F8B/2XMK/KY9E5962/F8B2XMKKY9E5962.png?auto=webp&width=1600&height=900&fit=bounds&md=a96d457b86d5ee1486ae368527bb916a)   
![github-small](https://content.instructables.com/ORIG/FY8/CI57/KY9E596D/FY8CI57KY9E596D.jpg?auto=webp&width=1600&height=900&fit=bounds&md=d75676925b69e50516f12e0aeb6f87ab)   
![github-small](https://content.instructables.com/ORIG/FG0/S73T/KY9E595J/FG0S73TKY9E595J.jpg?auto=webp&width=1600&height=900&fit=bounds&md=f32e69d80022e9458f730b26200da535)   

<p>For the OLED display, I used strips of electrical tape to hold it against the cutout on the plastic lid.</p><p>The OLED display uses I2C protocol for communicating with the Wemos. So its just four wires, VCC, GND, SDA and SCL. You can use attached wiring diagram as a reference for the connection.</p><p>Alternately, you can prepare your own OLED shield for Wemos and get rid of the wires. I have designed a simple board and have generated the Gerber file. You can download the Gerber from <a href="https://github.com/shivasiddharth/iotwemos/blob/master/Crypto_Ticker/Wemos%20SSD1306.rar" rel="nofollow">here</a>. You can get your PCB printed using JLCPCB's PCB printing service. With their online Gerber viewer, you can verify the PCB design before ordering. Use this link <a href="https://jlcpcb.com/IAT" rel="nofollow">https://jlcpcb.com/IAT</a> for great discounts and minimal PCB fabrication costs.</p>


## Brining The Ticker To Life    

![github-small](https://content.instructables.com/ORIG/F1Q/NX1N/KY9E598X/F1QNX1NKY9E598X.jpg?auto=webp&width=1600&height=900&fit=bounds&md=cc5f2408336db684b6b7d441cb10471b)   
![github-small](https://content.instructables.com/ORIG/F8K/5QS9/KY9E595E/F8K5QS9KY9E595E.jpg?auto=webp&width=1600&height=900&fit=bounds&md=52976d68f6d0e94120f17185567cd740)   
![github-small](https://content.instructables.com/ORIG/FIL/X8HO/KY9E595F/FILX8HOKY9E595F.jpg?auto=webp&width=1600&height=900&fit=bounds&md=67b99f46a57d1682e81419a1a936c748)   
![github-small](https://content.instructables.com/ORIG/FRJ/ODOP/KY9E595H/FRJODOPKY9E595H.jpg?auto=webp&width=1600&height=900&fit=bounds&md=a7fef0a372d0a8c6275773e1c5b30d5f)   
![github-small](https://content.instructables.com/ORIG/FNI/PVIT/KY9E595G/FNIPVITKY9E595G.jpg?auto=webp&width=1600&height=900&fit=bounds&md=1c38d442d8d2782414e63dbedf29f137)   
![github-small](https://content.instructables.com/ORIG/F54/T8NH/KY9E5965/F54T8NHKY9E5965.png?auto=webp&width=1600&height=900&fit=bounds&md=89f7be7706f72d25cda4607bc8c852e2)   

<blockquote>This project uses <a href="https://www.coindesk.com" rel="nofollow">Coindesk's</a> API for getting the crypto rates. Its a free API, so I urge the users to use that with caution and fairly. Please do not bombard the server with multiple requests constantly. We may end up loosing the only free API we have.</blockquote><p>With the disclaimer done, lets continue with the instructions.</p><h3>Preparing the Image</h3><p>Coindesk also has great images to go with their data. Replace the ISO name of the Crypto in this link <a href="https://downloads.coindesk.com/arc-hosted-images/eth.png" rel="nofollow">https://downloads.coindesk.com/arc-hosted-images/eth.png</a> with your desired Crypto's ISO value.</p><p>Couple of ISOs for popular Cryptos:</p><ol><li>btc for Bitcoin<li>sol for Solana<li>luna for Terra<li>bch for Bitcoin Cash</ol><p>Get more ISOs info <a href="https://www.coindesk.com/data/" rel="nofollow">here</a>.</p><p>Once you have got the desired image, open that using Microsoft's Paint and resize it to 60x60 pixels. Save that as PNG itself. Please do not change the format.</p><p>Next you need a service to change the PNG to values that the microcontroller can decipher. Use <a href="https://convertio.co/png-xbm/" rel="nofollow">this</a> online PNG to XBM converter. The conversion will result in the creation of a XBM file that you need to download to your computer.</p><p>Time to download the Arduino code. Get your Arduino code from <a href="https://github.com/shivasiddharth/iotwemos/tree/master/Crypto_Ticker/SSD1306UiDemo-One-Currency" rel="nofollow">here</a>. Mind the images.h file it is required as well.</p><h3>Customize the Code</h3><p>By default, the script or code or sketch is for displaying Bitcoin values. If you wish to replace that to some other currency, Press <strong>Ctrl + F </strong>on your keyboard and replace BTC with the desired ISO of your currency. For example, if you need Ethereum, replace BTC with ETH.</p><blockquote>Mind the lettering case. For the PNG images it was lower case, but it is upper case here.</blockquote><p>If you don't change the Boot logo in the images.h file, irrespective of the Crypto changed in the code, Bitcoin logo will be displayed by default.</p><p>Remember the XBM file that you just created using the first step ? Now Open the XBM file with Notepad or Notepad++ in Windows. Copy the values within the first curly &quot;{}&quot; brackets and replace the existing values in the images.h with that.</p><p>Set your Wifi SSID and Password in the place provided in the code.</p><blockquote>By default, I have set the sketch to get the Crypto values every 2 minutes. This is to honor the Coindesk's free API. If you scroll through the code you should be able to figure the variable declaration. But please do not touch that, we may loose the only free and reliable API.</blockquote><p>Now compile the sketch and upload it to the Wemos.</p>


## All Done    

![github-small](https://content.instructables.com/ORIG/F6V/3X1V/KY9E5967/F6V3X1VKY9E5967.png?auto=webp&width=1600&height=900&fit=bounds&md=b23abbde1b348cee2b899385967e12d4)  
![github-small](https://content.instructables.com/ORIG/FCZ/H27T/KY9E5ANG/FCZH27TKY9E5ANG.png?auto=webp&width=1600&height=900&fit=bounds&md=677bbc384b42f9381fddbeb7de838f5b)  

<p>Wow !! After the initial wait period of 2 minutes, we should have the Crypto values show up.</p>






