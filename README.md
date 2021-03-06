# Dad, can you text my friend's dad to see if my friend can play video games online with me?

Sure, **3 or 4 times a day, every day, of the Covid-19 pandemic**, until I probably spent more time texting his dad than my own partner. The Mothers of Invention wasnt just a great band, its also a Necessity!

Then I thought, aren't thinking engines supposed to do this type of drudgery for us? What if there was a device where you could push a button or two, and another device far, far away would light up and make sounds. I bet everyone and their mother would want one. You could probably sell these things by the bushel. But they would need a catchy name. Sell... Sell... sell what? Sell.. why? Sell for... not enterrupting. Sell for not enterrupting. Too long, shorten it to Sell FO-NE... perfect!

All kidding aside, I thought wouldn't it be neat if my son has a button he could push that would alert his friends he wanted to play. And if they wanted to play too, they could hit a button on their side that let my son know they wanted to play also. I imagined it sending out a call like OCTONAUTS TO THE LAUNCH BAY, or PAW PATROL TO THE LOOKOUT. Hell even my buddies would probably want one...   
![meandtheboys](/images/meandtheboys.jpg) <br>

I also had watched a couple great online workshops about IoT using these cheap little developer boards and thought it would be a great opportunity to stretch my knowledge. **A big thankyou to jimbobbennet and wduraes for their workshops on IoT and arduino.**  
1. https://github.com/wduraes/Workshops/tree/master/IoT%20101%20for%20Makers - Start here for a great explanation of how mqtt works and free to use Adafruit.io
2. https://github.com/jimbobbennett/BusyLight - Here for more sophisticated Azure IoT Central approach

# Define the Problem
  So the use case is: Device sits minding its own business until someone wants to play. They push a button, sending a request to play. All connected devices make some kind of an alert for a short period of time. If anyone wants to play,  they push a button on their device and all other devices play a different type of alert to let every know there is a response. You won't know who answered your call until you fire up your game, but you know someone will be there to join. 
  I want this device to be as cheap as possible (since Im going to be giving them out to my son's friends families), be plug and play, and be interesting enough to the target demographic that they don't lose/destroy it in the first few days.
<br>*image for state diagram*

## How are we going to solve this?
Through a luckly alignment of the stars I had learned almost everything I needed in the last few months to almost know what I was doing. And even more lucky, this particular project was not dangerous enough that my little bit of knowledge was going to get anyone hurt. Basically, using the ESP8266 NodeMCU Dev board, and Adafruit.io I had a platform for MQTT. Add your basic buttons, LEDs and buzzers and that is all we need. Package it all on a prototyping board for the high tech look and that should be enough to keep it interesting. (And accomodate my numerous mistakes. :) )
1. [Hardware - ESP8266/ESP32](/steps/hardware.md)
2. [Software - Arduino](/steps/software.md)

![Shazam!](/images/final_pager.jpg)
# next Steps
1. device has been ringing the system even when no button push, figure out why
3. add button interrupt
2. figure out public feeds to see if multiple people can use devices without having to pre-populate 
