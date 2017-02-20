#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include "patterns.h"
#include <Hash.h>

#include <TimeAlarms.h>
#include "WifiConfig.h"
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    D2
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    171
#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  120

#define TRANSITION_DURATION 2000

#define MAX_TIME_BETWEEN_GLITTER 300
#define MIN_TIME_BETWEEN_GLITTER 5
#define MAX_TIME_FOR_GLITTER_SEC 45
#define MIN_TIME_FOR_GLITTER_SEC 5

void startGlitterMode();

bool gIsPowerOn = true;
bool gIsPoweredOff = false;

char hostString[16] = {0};

CRGB leds[NUM_LEDS];
CRGB targetLeds[NUM_LEDS];

ulong startTransitionTime;

// List of patterns to cycle through.  Each is defined as a separate function below.
std::vector<AbstractPattern *> gPatterns;
AbstractPattern * gCurrentPattern = NULL;
AbstractPattern * gTargetPattern = NULL;

AsyncWebServer server(80);


AbstractPattern* nextPattern()
{
    uint8_t pattern = random(0, gPatterns.size());
    gPatterns[pattern]->resetRuntime();
    return gPatterns[pattern];
}


void announceHour() {
    gCurrentPattern = new AnnounceHour(NUM_LEDS);
    gTargetPattern = NULL;
}

void setAlarms() {
    Serial.println("Setting alarms...");
    for(int i = 0; i < 24; i++) {
        Alarm.alarmRepeat(i,0,0,announceHour);
        Alarm.alarmRepeat(i,30,0, announceHour);
    }
    Alarm.alarmRepeat(12,0,0, [](){
        FastLED.setBrightness(255);
    });
    Alarm.alarmRepeat(22,0,0, [](){
        FastLED.setBrightness(128);
    });
    Alarm.timerOnce(random(1, 10), startGlitterMode);

}

void onSTAGotIP(WiFiEventStationModeGotIP ipInfo) {
    Serial.printf("Got IP: %s\r\n", ipInfo.ip.toString().c_str());
    NTP.begin("pool.ntp.org", 1, true);
    NTP.setInterval(63, 6300);
}

void onSTADisconnected(WiFiEventStationModeDisconnected event_info) {
    Serial.printf("Disconnected from SSID: %s\n", event_info.ssid.c_str());
    Serial.printf("Reason: %d\n", event_info.reason);
}

void onNTPSyncEvent(NTPSyncEvent_t ntpEvent) {
    if (ntpEvent) {
        Serial.print("Time Sync error: ");
        if (ntpEvent == noResponse)
            Serial.println("NTP server not reachable");
        else if (ntpEvent == invalidAddress)
            Serial.println("Invalid NTP server address");
    }
    else {
        Serial.print("Got NTP time: ");
        Serial.println(NTP.getTimeDateString(NTP.getLastNTPSync()));
    }
}

void setupWebServer() {

    Serial.println("Setting up Web Server...");
    ArRequestHandlerFunction onPowerOnHandler = [](AsyncWebServerRequest *request){
        gIsPowerOn = true;
        request->send(200, "text/json", "{'power':true}");
    };
    server.on("/power/on", HTTP_GET, onPowerOnHandler);

    ArRequestHandlerFunction onPowerOffHandler = [](AsyncWebServerRequest *request){
        gIsPowerOn = false;
        request->send(200, "text/json", "{'power':false}");
    };
    server.on("/power/off", HTTP_GET, onPowerOffHandler);

    ArRequestHandlerFunction onBrightnessHandler = [](AsyncWebServerRequest *request){
        AsyncWebParameter* param = request->getParam("brightness");
        FastLED.setBrightness(param->value().toInt());
        request->send(200, "text/json", "{}");
    };
    server.on("/brightness", HTTP_GET, onBrightnessHandler);
    server.begin();
    Serial.println("Web Server Running...");
}

void setupWiFi() {
    static WiFiEventHandler e1, e2;

    WiFi.mode(WIFI_STA);
    WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);

    onSyncEvent_t onSyncHandler = onNTPSyncEvent;
    NTP.onNTPSyncEvent(onSyncHandler);
    WiFi.onEvent([](WiFiEvent_t e) {
        Serial.printf("Event wifi -----> %d\n", e);
    });
    e1 = WiFi.onStationModeGotIP(onSTAGotIP);// As soon WiFi is connected, start NTP Client
    e2 = WiFi.onStationModeDisconnected(onSTADisconnected);

}

bool gGlitterMode = false;

void endGlitterMode() {
    Serial.println("End Glitter Mode");
    gGlitterMode = false;
    Alarm.timerOnce(random(MIN_TIME_BETWEEN_GLITTER, MAX_TIME_BETWEEN_GLITTER), startGlitterMode);
}

void startGlitterMode() {
    Serial.println("Start Glitter mode");
    gGlitterMode = true;
    Alarm.timerOnce(random(MIN_TIME_FOR_GLITTER_SEC, MAX_TIME_FOR_GLITTER_SEC), endGlitterMode);
}

void addGlitter( fract8 chanceOfGlitter)
{
    if( random8() < chanceOfGlitter) {
        leds[ random16(NUM_LEDS) ] += CRGB::White;
    }
}

void setupMDNS() {
    if (!MDNS.begin(hostString)) {
        Serial.println("Error setting up MDNS responder!");
    }
    Serial.println("mDNS responder started");

    char instanceName[30] = {0};
    sprintf(instanceName, "LED Controller@%06X", ESP.getChipId());
    MDNS.setInstanceName(instanceName);
    MDNS.addService("http","tcp",80);
    MDNS.addService("stripled", "tcp", 8080);
    MDNS.addServiceTxt("http", "tcp", "type", "strip_led");

}

void setupFastLed() {//gPatterns.push_back(new MotionLight(NUM_LEDS));

    gPatterns.push_back(new Rainbow(NUM_LEDS));
    gPatterns.push_back(new FireOnFireEscape<FirePattern>(NUM_LEDS));
    gPatterns.push_back(new Sinelon(NUM_LEDS));
    gPatterns.push_back(new Confetti(NUM_LEDS));
    gPatterns.push_back(new FireOnFireEscape<PalettePattern>(NUM_LEDS));
    gPatterns.push_back(new FireOnFireEscape<RainbowFirePattern>(NUM_LEDS));
    gPatterns.push_back(new Noise(NUM_LEDS));
    gPatterns.push_back(new JugglePattern(NUM_LEDS));
    gPatterns.push_back(new RollingPattern(NUM_LEDS));

    // tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

    // set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
    gCurrentPattern = new TestPattern(NUM_LEDS);
}

void setup() {
    sprintf(hostString, "ESP_%06X", ESP.getChipId());

    Serial.begin(9600);
    setupWiFi();

    Serial.print("Waiting for Wifi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    delay(3000);

    setupMDNS();
    setupWebServer();
    setupFastLed();
    ArduinoOTA.begin();
    setAlarms();
    NTP.setTimeZone(-8);
    setSyncProvider([]()->time_t {
        NTP.getTime();
    });

}

void renderFrame() {
    ulong currentTime = millis();
    if(!gCurrentPattern) gCurrentPattern = nextPattern();

    // Call the current pattern function once, updating the 'leds' array
    gCurrentPattern->readFrame(leds, currentTime);

    if(gTargetPattern) {
        if(currentTime > startTransitionTime + TRANSITION_DURATION) {
            // we are at the end of the transition...
            // gotta black out the buffer....
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            gTargetPattern->readFrame(leds, currentTime);
            gCurrentPattern = gTargetPattern;
            gCurrentPattern->resetRuntime();
            gTargetPattern = NULL;
        } else {
            gTargetPattern->readFrame(targetLeds, currentTime);

            if(currentTime > startTransitionTime + TRANSITION_DURATION / 2) {
                // we need to fade out the original...
                const ulong fade_out_amount = map(currentTime + TRANSITION_DURATION / 2, startTransitionTime, startTransitionTime + TRANSITION_DURATION /2 , 0, 255);
                fadeToBlackBy(leds, NUM_LEDS, fade_out_amount);
            } else {
                // we need to fade in the new guy....
                const ulong fade_in_amount = map(currentTime, startTransitionTime, startTransitionTime + TRANSITION_DURATION /2 , 0, 255);
                fadeToBlackBy(targetLeds, NUM_LEDS, 255 - fade_in_amount);
            }

            nblend(leds, targetLeds, NUM_LEDS, 255);
        }
    } else if(gCurrentPattern->canStop()) {
        AbstractPattern* theNextPattern = nextPattern();
        if(theNextPattern != gCurrentPattern) {
            startTransitionTime = currentTime;
            gTargetPattern = theNextPattern;
            fill_solid(targetLeds, NUM_LEDS, CRGB::Black);
        }
    }

    if(gGlitterMode) {
        addGlitter(80);
    }
}

void loop()
{
    Alarm.delay(0);
    if(gIsPowerOn) {
        gIsPoweredOff=false;
        renderFrame();

        // send the 'leds' array out to the actual LED strip
        FastLED.show();

    } else {
        if(!gIsPoweredOff) {
            fill_solid(leds,NUM_LEDS,CRGB::Black);
            FastLED.show();
            gIsPoweredOff = true;
        }
    }

    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND);
}
