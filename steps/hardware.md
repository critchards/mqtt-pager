## Materials List ##
Its all Amazon links, becuase thats easiest for me to find. I bought most of this stuff from [Adafruit](https://www.adafruit.com/) though and I suggest you go there if you have the option.
1. 2x [NodeMCU ESP8266 EDP 12-E Development board](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES) These boards should be gettable for less than $5 each. You can also use [DOIT ESP32 DevBoard](https://www.amazon.ca/dp/B07HG5XHLB/ref=sspa_dk_detail_1?psc=1&pd_rd_i=B07HG5XHLB&pd_rd_w=LNoOI&pf_rd_p=60f4d8bb-ce34-4daf-9823-4864ac29e442&pd_rd_wg=Qj67a&pf_rd_r=1XWYJPARYGW8EZZACDAD&pd_rd_r=9f8b112e-68a4-4a71-9525-3acd41b21943&smid=A2KRDQ1AI5Y5G6&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzRU1SWDVKUExEU0FZJmVuY3J5cHRlZElkPUEwNjMxNTg0NDZHQ0IzTkpNS1FVJmVuY3J5cHRlZEFkSWQ9QTA4MzIwMTNQSTZPS1dHTk9EUzcmd2lkZ2V0TmFtZT1zcF9kZXRhaWwmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) if you have them. They are more expensive but have BLE for other projects down the line. A couple of changes are noted in the .ino file though if you use the ESP32.
2. 2x [Half sized breadboard](https://www.amazon.com/Breadboard-Solderless-Prototype-PCB-Board/dp/B077DN2PS1/ref=sr_1_4?crid=2DCFCPTVZCZ1X&dchild=1&keywords=half+size+breadboard&qid=1599005853&s=electronics&sprefix=half+sized+bre%2Celectronics%2C201&sr=1-4)
3. 2x [12mm tactile button](https://www.amazon.com/TWTADE-Momentary-Tactile-Button-Switch/dp/B07CG6HVY9/ref=sr_1_5?dchild=1&keywords=12mm+tactile+button&qid=1599005975&sr=8-5)
4. 2x [5V 2 terminal buzzer](https://www.amazon.com/Cylewet-Terminals-Electronic-Electromagnetic-Impedance/dp/B01NCOXB2Q/ref=sr_1_1_sspa?dchild=1&keywords=piezo+buzzer&qid=1599006085&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzSE82VUZZMjVKMElYJmVuY3J5cHRlZElkPUEwODcyMTQ5MU41VzFMNEQ0S1dKMCZlbmNyeXB0ZWRBZElkPUEwNTk2MDYzM1BCNDlXWUM5WUc5JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==) You can go with bigger/louder if you want. These ones are not going to be audible from the other side of the house but you should be able to hear them in the same room even with background noise.
5. 2x [5mm LED](https://www.amazon.com/eBoot-Pieces-Emitting-Diodes-Assorted/dp/B06XPV4CSH/ref=sr_1_6?dchild=1&keywords=LED+arduino&qid=1599006200&sr=8-6) Whichever color you want.
6. 2x [300Ohm resistor](https://www.amazon.com/Elegoo-Values-Resistor-Assortment-Compliant/dp/B072BL2VX1/ref=sr_1_1_sspa?dchild=1&keywords=resistor+kit&qid=1599006274&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzNjBWVUVOVFMxVVNIJmVuY3J5cHRlZElkPUEwNzQyNzMxM1ZINlBJV1E4OFdRSSZlbmNyeXB0ZWRBZElkPUEwNjU3NDA1SERVSFVJN1MxRkgxJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==) just buy a kit.
7. 2x 4.7kOhm resistor - from the same kit. Strictly speaking this is not necessary since you can use the built in pulldown function of the board but this is how I was taught...
8. And some jumper wires.

Wire it up as so
![Fritz](https://github.com/critchards/mqtt-pager/blob/master/images/mqtt-pager-fritzing_bb.png)


Note this is with the DOIT ESP32 Board which doesnt exactly fit on the half sized breadboard.
