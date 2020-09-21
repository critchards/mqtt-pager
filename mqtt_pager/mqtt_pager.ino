  //some parts of this have been copied from adafruit, and some from wduraes. You can tell from the {convention}
  
  #include <ESP8266WiFi.h>					//use this one if you have an ESP8266
  //#include <Wifi.h>						    //use this one if you have an ESP32
  //#include <Tone32.h>						  //Tone is not implemented on the ESP32, need to manually install this library
  #include "Adafruit_MQTT.h"
  #include "Adafruit_MQTT_Client.h"

  #define WLAN_SSID       "THE WIFI NAME GOES HERE"					//for whichever house this device is going to live at
  #define WLAN_PASS       "THE WIFI PASSWORD GOES HERE"				//for whichever house this device is going to live at
  #define AIO_SERVER      "io.adafruit.com"
  #define AIO_USERNAME    "YOUR ADAFRUIT USER NAME GOES HERE"
  #define AIO_KEY         "COPY YOUR ADAFRUIT.IO KEY HERE"
  #define AIO_SERVERPORT  1883
  #define BUZZER_CHANNEL 0                                  //needed for Tone32 implementation
                     
  WiFiClient client;
  //#define AIO_SERVERPORT  8883     // use 8883 for SSL
  //WiFiClientSecure client;  // use WiFiFlientSecure for SSL

  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
  Adafruit_MQTT_Publish request = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/YOUR FEED NAME");			//change YOUR FEED NAME
  Adafruit_MQTT_Subscribe response = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/YOUR FEED NAME");		//change YOUR FEED NAME

  void MQTT_connect();

  const int BUTTONPIN = 9;    //set button output pin
  const int LEDPIN = 16;       //set status LED To pin number
  const int TONEPIN = 5;     //set buzzer to pin number, for DOIT ESP32 boards use 12
  const int MAXRINGS = 7;    //max number of rings  

  int ledState = LOW;         //for LED SM
  int toneState = LOW;        //for tone SM
  int lastButtonState = 0;  //for button edge detect
  int buttonState = 0;		//for current button state
  int numRings = 0;     //count number of times I have rung

  bool Ringing = false;		//am i ringing or not

  unsigned long currentTime = 0;      //SM global timer
  unsigned long prePing = 0;          //SM timer for ping
  unsigned long preSubscribe = 0;     //SM timer for subscription check
  unsigned long lastRing = 0;         //SM for LED and tone on during ring
  unsigned long lastTone = 0;         //SM timer for tone
  unsigned long lastDebounceTime = 0; //SM timer for button debounce
     
  void setup() 
  {       
    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);
    pinMode(BUTTONPIN, INPUT);
  
    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
  
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) 
    {
      digitalWrite(LED_BUILTIN, LOW);   //turn onboard LED ON
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);    //turn onboard LED OFF
      Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
    
    // Setup MQTT subscriptions for all feeds.
    mqtt.subscribe(&response);

    digitalWrite(LEDPIN, ledState);
  }
     
  void loop() 
  {
    currentTime = millis();
    MQTT_connect();
   
    Adafruit_MQTT_Subscribe *subscription;
    if((currentTime - preSubscribe) > 5000)             //check for subscriptions only every few seconds, adafruit.io doesnt like being pinged continuously
    {
      //Serial.println("checking for subscriptions");
      preSubscribe = currentTime;
      while ((subscription = mqtt.readSubscription(500))) 		//keep subscription window open for a short period so that button pushes dont get lost. OR, fix buttons to be interrupts
      {
        if (subscription == &response)
        {
          Serial.print(F("Subscription Got: "));
          Serial.println((char *)response.lastread);
        }
        if (strcmp((char *)response.lastread, "WAITING") == 0) 
        {
          //if you see waiting, dont do anything
          Ringing = false;
        } 
        if (strcmp((char *)response.lastread, "RINGING") == 0) 
        {
          //if someone sent a request, ring the device
          Ringing = true;
        }
        if (strcmp((char *)response.lastread, "CONFIRM") == 0) 
        {
          //if someone answered the ring, play a merry tune, then go back to waiting
		  celebrate();
          Ringing = false;
        }       
      }
    }           

    int reading = digitalRead(BUTTONPIN);				//check the status of the pushbutton
    if(reading != lastButtonState)						//only do something if the button has changed. May need to debounce?
    {
      if(reading == 1)      //if button is high, set to high
      {
        buttonState = 1;
      }
    }
    else                    //if the button state hasnt changed, set button to low. This handles extra long presses.
    {
      buttonState = 0;
    }
    lastButtonState = reading;
    
    if(buttonState == 1)	//if the button is truly being pressed, after removing long presses
    {
      if(!Ringing)			//if the device is not already ringing then this must be the first device sending a request
      {
        if(request.publish("RINGING"))		//publish ringing so that all devices know they should be ringing
        {
          numRings = 0;						//keep track of number of rings so it doesnt go on for ever
          Ringing = true;				
          Serial.print("sending request to play as: ");
          Serial.print("RINGING");
          Serial.println("...");
        }  
      }
      else if(Ringing)						//if the device is alraedy ringing then this must be an answer
      {
          request.publish("CONFIRM");		//publish confirm so all devices know someone answered
          Ringing = false;					//stop ringing
      }
      buttonState = 0;						//set button back to off, again in case of extra long presses
    }

    if(Ringing)               //when ringing, flash lights and play tone, all on different periods, NON BLOCKING
    {
      if((toneState == HIGH) && (currentTime - lastTone > 100))		//SM for shutting buzzer off
      {
        toneState = LOW;
        lastTone = currentTime;
        noTone(TONEPIN);                                          //if using ESP8266
        //noTone(TONEPIN, BUZZER_CHANNEL);                        //if using ESP32
      }
      if((toneState == LOW) && (currentTime - lastTone > 500))		//SM for turning buzzer on
      {
        toneState = HIGH;
        lastTone = currentTime;
        tone(TONEPIN, 1000);                                      //ESP8266
        //tone(TONEPIN, 1000, 0, BUZZER_CHANNEL);                 //ESP32
      }
      if((ledState == LOW) && (currentTime - lastRing > 1000))		//SM for turning LED off
      {
        ledState = HIGH;
        lastRing = currentTime;
        digitalWrite(LEDPIN, ledState);
      }
      if((ledState == HIGH) && (currentTime - lastRing > 1000))		//SM for turning LED on
      {
        ledState = LOW;
        lastRing = currentTime;
        digitalWrite(LEDPIN, ledState);
        numRings++;													//number of rings is defined as number of times LED turns on
      }
    }

    if(numRings > MAXRINGS)             //if it has been ringing for too long, stop and reset
    {
      if(request.publish("WAITING"))     //publish WAITING so that system knows no request in progress
      {
        Serial.println("max rings, send waiting");
        digitalWrite(LEDPIN, LOW);
        noTone(TONEPIN);                        //ESP8266
        //noTone(TONEPIN, BUZZER_CHANNEL);        //ESP32           
        Ringing = false;                
        numRings = 0;
      }
    }
     
    if((currentTime - prePing) > 290000)        //ping the broker every keep alive duration, configurable in settings     
    {
        Serial.println("ping mqtt");
        prePing = currentTime;
        if(! mqtt.ping())
        {
          Serial.println("ping not work, kill mqtt");
          mqtt.disconnect();
        }
    }
  }  

  // Function to connect and reconnect as necessary to the MQTT server.
  // Should be called in the loop function and it will take care if connecting.
  // copied directly from wduraes IoT_101_Online.ino
  void MQTT_connect() {
    
    int8_t ret;
    if (mqtt.connected()) {      // Stop if already connected.
      return;
      }
    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
         Serial.println(mqtt.connectErrorString(ret));
         Serial.println("Retrying MQTT connection in 5 seconds...");
         mqtt.disconnect();
         delay(5000);  // wait 5 seconds
         retries--;
         if (retries == 0) {
           // basically die and wait for WDT to reset me
           while (1);
         }
    }
    Serial.println("MQTT Connected!");
  }

  void celebrate()
  //flash lights and play merry tone to indicate a request has been answered and play will commence.
  //BLOCKING
  {
    for(int j = 0; j<3; j++)
    {
      for(int i = 0; i<3; i++)
      {
        digitalWrite(LEDPIN, HIGH);
        tone(TONEPIN, 500);
        //tone(TONEPIN, 500, 0, BUZZER_CHANNEL);    //ESP32
        delay(100);
        tone(TONEPIN, 650);
        //tone(TONEPIN, 650, 0, BUZZER_CHANNEL);    //ESP32
        delay(100);
        tone(TONEPIN, 1000);
        //tone(TONEPIN, 1000, 0, BUZZER_CHANNEL);    //ESP32
        delay(100);
        noTone(TONEPIN);
        //noTone(TONEPIN, BUZZER_CHANNEL);           //ESP32
        digitalWrite(LEDPIN, LOW);
        delay(300);
      }
      delay(600);
    }
    request.publish("WAITING");
    Ringing = false;
  }
