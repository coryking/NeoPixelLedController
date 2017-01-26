#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include "patterns.h"

#include <TimeLib.h>
#include <TimeAlarms.h>
#include "WifiConfig.h"
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

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

CRGB leds[NUM_LEDS];
CRGB targetLeds[NUM_LEDS];

ulong startTransitionTime;

// List of patterns to cycle through.  Each is defined as a separate function below.
std::vector<AbstractPattern *> gPatterns;
AbstractPattern * gCurrentPattern = NULL;
AbstractPattern * gTargetPattern = NULL;

AbstractPattern* nextPattern()
{
    static uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

    // add one to the current pattern number, and wrap around at the end
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % gPatterns.size();

    gPatterns[gCurrentPatternNumber]->resetRuntime();
    return gPatterns[gCurrentPatternNumber];
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

void setup() {
    Serial.begin(9600);
    setupWiFi();
    delay(3000); // 3 second delay for recovery
    //gPatterns.push_back(new MotionLight(NUM_LEDS));
    gPatterns.push_back(new Rainbow(NUM_LEDS));
    gPatterns.push_back(new FireOnFireEscape(NUM_LEDS));
    //gPatterns.push_back(new Sinelon(NUM_LEDS));
    //gPatterns.push_back(new Confetti(NUM_LEDS));
    gPatterns.push_back(new Noise(NUM_LEDS));

    // tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

    // set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
    gCurrentPattern = new TestPattern(NUM_LEDS);
    setAlarms();
}

void loop()
{
    ulong currentTime = millis();
    if(!gCurrentPattern) gCurrentPattern = nextPattern();

    // Call the current pattern function once, updating the 'leds' array
    gCurrentPattern->readFrame(leds, currentTime);

    if(gTargetPattern) {
        const ulong blend_amount = map(currentTime, startTransitionTime, startTransitionTime + TRANSITION_DURATION, 0, 255);
        gTargetPattern->readFrame(targetLeds, currentTime);
        nblend(leds, targetLeds, NUM_LEDS, blend_amount);
        if(currentTime > startTransitionTime + TRANSITION_DURATION) {
            gCurrentPattern = gTargetPattern;
            gCurrentPattern->resetRuntime();
            gTargetPattern = NULL;
        }
    } else if(gCurrentPattern->canStop()) {
        startTransitionTime = currentTime;
        gTargetPattern = nextPattern();
        fill_solid(targetLeds, NUM_LEDS, CRGB::Black);
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();

    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND);
}
